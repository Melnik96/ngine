/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_surface.shader
 * Desc:    Water surface shader
 * Version: 1.10
 * Author:  Alexander Zaprjagaev <frustum@unigine.com>
 *
 * This file is part of the Unigine engine (http://unigine.com/).
 *
 * Your use and or redistribution of this software in source and / or
 * binary form, with or without modification, is subject to: (i) your
 * ongoing acceptance of and compliance with the terms and conditions of
 * the Unigine License Agreement; and (ii) your inclusion of this notice
 * in any version of this software that you use or redistribute.
 * A copy of the Unigine License Agreement is available by contacting
 * Unigine Corp. at http://unigine.com/
 */

#include <core/shaders/common/vertex_base.h>
#include <core/shaders/water/vertex_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

attribute float4 s_attribute_0;

uniform float4x4 s_water_projection;
uniform float3 s_water_position;
uniform float3 s_water_normal;
uniform float3 s_water_tangent;
uniform float3 s_water_binormal;
uniform float4 s_water_plane;
uniform float4 s_water_waves[4];
uniform float s_water_time;

uniform float waves_radius;
uniform float surface_density;

/*
 */
void main() {
	
	float4 vertex = s_water_projection * float4(s_attribute_0.xy,1.0f,1.0f);
	vertex.xyz = vertex.xyz / vertex.w - s_water_position;
	
	float numerator = -dot(s_water_plane,float4(s_water_position,1.0f));
	float denominator = dot(s_water_plane.xyz,vertex.xyz);
	float distance = numerator / ((s_water_plane.w > 0.0f) ? min(denominator,0.0f) : max(denominator,0.0f));
	vertex = float4(vertex.xyz * distance + s_camera_position + s_water_position,1.0f);
	
	float3 normal = s_water_normal;
	float3 tangent = s_water_tangent;
	float3 binormal = -s_water_binormal;
	
	float3 position = vertex.xyz - float3(s_transform[0].w,s_transform[1].w,s_transform[2].w);
	float2 texcoord = float2(dot(tangent,position),dot(binormal,position));
	
	#ifdef WAVES
		
		float radius = length(vertex.xyz - s_camera_position);
		float scale = saturate(1.0f - radius / waves_radius) * saturate(radius - s_depth_range.x * 16.0f);
		
		float wave_height = 0.0f;
		float2 wave_normal = float2(0.0f);
		
		#define WAVE(NUMBER) { \
			float distance = dot(s_water_waves[NUMBER].xy,texcoord.xy); \
			float phase = (distance + s_water_time) * s_water_waves[NUMBER].z; \
			wave_height += sin(phase) * s_water_waves[NUMBER].w * scale; \
			wave_normal -= s_water_waves[NUMBER].xy * (cos(phase) * s_water_waves[NUMBER].w * s_water_waves[NUMBER].z * scale); \
		}
		
		WAVE(0)
		WAVE(1)
		WAVE(2)
		WAVE(3)
		
		vertex.xyz = vertex.xyz + normal * wave_height - tangent * wave_normal.x - binormal * wave_normal.y;
		normal = normalize(normal + tangent * wave_normal.x + binormal * wave_normal.y);
		
	#endif
	
	float4 direction;
	direction.xyz = (vertex.xyz - s_camera_position) / s_depth_range.y;
	direction.w = s_depth_range.y * surface_density;
	
	#include <core/shaders/water/vertex_base.h>
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct VERTEX_IN {
	float4 position : POSITION;
};

float4x4 s_water_projection;
float3 s_water_position;
float3 s_water_normal;
float3 s_water_tangent;
float3 s_water_binormal;
float4 s_water_plane;
float4 s_water_waves[4];
float s_water_time;

float waves_radius;
float surface_density;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = mul(s_water_projection,float4(IN.position.xy,1.0f,1.0f));
	vertex.xyz = vertex.xyz / vertex.w - s_water_position;
	
	float numerator = -dot(s_water_plane,float4(s_water_position,1.0f));
	float denominator = dot(s_water_plane.xyz,vertex.xyz);
	float distance = numerator / ((s_water_plane.w > 0.0f) ? min(denominator,0.0f) : max(denominator,0.0f));
	vertex = float4(vertex.xyz * distance + s_camera_position + s_water_position,1.0f);
	
	float3 normal = s_water_normal;
	float3 tangent = s_water_tangent;
	float3 binormal = s_water_binormal;
	
	float3 position = vertex.xyz - float3(s_transform[0].w,s_transform[1].w,s_transform[2].w);
	float2 texcoord = float2(dot(tangent,position),dot(binormal,position));
	
	#ifdef WAVES
		
		float radius = length(vertex.xyz - s_camera_position);
		float scale = saturate(1.0f - radius / waves_radius) * saturate(radius - s_depth_range.x * 16.0f);
		
		float wave_height = 0.0f;
		float2 wave_normal = 0.0f;
		
		#define WAVE(NUMBER) { \
			float distance = dot(s_water_waves[NUMBER].xy,texcoord.xy); \
			float phase = (distance + s_water_time) * s_water_waves[NUMBER].z; \
			wave_height += sin(phase) * s_water_waves[NUMBER].w * scale; \
			wave_normal -= s_water_waves[NUMBER].xy * (cos(phase) * s_water_waves[NUMBER].w * s_water_waves[NUMBER].z * scale); \
		}
		
		WAVE(0)
		WAVE(1)
		WAVE(2)
		WAVE(3)
		
		vertex.xyz = vertex.xyz + normal * wave_height - tangent * wave_normal.x - binormal * wave_normal.y;
		normal = normalize(normal + tangent * wave_normal.x + binormal * wave_normal.y);
		
	#endif
	
	float4 direction;
	direction.xyz = (vertex.xyz - s_camera_position) / s_depth_range.y;
	direction.w = s_depth_range.y * surface_density;
	
	#include <core/shaders/water/vertex_base.h>
	
	return OUT;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

struct VERTEX_IN {
	float4 position : POSITION;
};

cbuffer shader_water_parameters {
	float4x4 s_water_projection;
	float3 s_water_position;
	float3 s_water_normal;
	float3 s_water_tangent;
	float3 s_water_binormal;
	float4 s_water_plane;
	float4 s_water_waves[4];
	float s_water_time;
};

cbuffer shader_parameters {
	float waves_radius;
	float surface_density;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = mul(s_water_projection,float4(IN.position.xy,1.0f,1.0f));
	vertex.xyz = vertex.xyz / vertex.w - s_water_position;
	
	float numerator = -dot(s_water_plane,float4(s_water_position,1.0f));
	float denominator = dot(s_water_plane.xyz,vertex.xyz);
	float distance = numerator / ((s_water_plane.w > 0.0f) ? min(denominator,0.0f) : max(denominator,0.0f));
	vertex = float4(vertex.xyz * distance + s_camera_position + s_water_position,1.0f);
	
	float3 normal = s_water_normal;
	float3 tangent = s_water_tangent;
	float3 binormal = s_water_binormal;
	
	float3 position = vertex.xyz - float3(s_transform[0].w,s_transform[1].w,s_transform[2].w);
	float2 texcoord = float2(dot(tangent,position),dot(binormal,position));
	
	#ifdef WAVES
		
		float radius = length(vertex.xyz - s_camera_position);
		float scale = saturate(1.0f - radius / waves_radius) * saturate(radius - s_depth_range.x * 16.0f);
		
		float wave_height = 0.0f;
		float2 wave_normal = 0.0f;
		
		#define WAVE(NUMBER) { \
			float distance = dot(s_water_waves[NUMBER].xy,texcoord.xy); \
			float phase = (distance + s_water_time) * s_water_waves[NUMBER].z; \
			wave_height += sin(phase) * s_water_waves[NUMBER].w * scale; \
			wave_normal -= s_water_waves[NUMBER].xy * (cos(phase) * s_water_waves[NUMBER].w * s_water_waves[NUMBER].z * scale); \
		}
		
		WAVE(0)
		WAVE(1)
		WAVE(2)
		WAVE(3)
		
		vertex.xyz = vertex.xyz + normal * wave_height - tangent * wave_normal.x - binormal * wave_normal.y;
		normal = normalize(normal + tangent * wave_normal.x + binormal * wave_normal.y);
		
	#endif
	
	float4 direction;
	direction.xyz = (vertex.xyz - s_camera_position) / s_depth_range.y;
	direction.w = s_depth_range.y * surface_density;
	
	#include <core/shaders/water/vertex_base.h>
	
	return OUT;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

struct VERTEX_IN {
	float4 position : ATTR0;
};

uniform float4x4 s_water_projection;
uniform float3 s_water_position;
uniform float3 s_water_normal;
uniform float3 s_water_tangent;
uniform float3 s_water_binormal;
uniform float4 s_water_plane;
uniform float4 s_water_waves[4];
uniform float s_water_time;

uniform float waves_radius;
uniform float surface_density;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = mul(s_water_projection,float4(IN.position.xy,1.0f,1.0f));
	vertex.xyz = vertex.xyz / vertex.w - s_water_position;
	
	float numerator = -dot(s_water_plane,float4(s_water_position,1.0f));
	float denominator = dot(s_water_plane.xyz,vertex.xyz);
	float distance = numerator / ((s_water_plane.w > 0.0f) ? min(denominator,0.0f) : max(denominator,0.0f));
	vertex = float4(vertex.xyz * distance + s_camera_position + s_water_position,1.0f);
	
	float3 normal = s_water_normal;
	float3 tangent = s_water_tangent;
	float3 binormal = s_water_binormal;
	
	float3 position = vertex.xyz - float3(s_transform[0].w,s_transform[1].w,s_transform[2].w);
	float2 texcoord = float2(dot(tangent,position),dot(binormal,position));
	
	#ifdef WAVES
		
		float radius = length(vertex.xyz - s_camera_position);
		float scale = saturate(1.0f - radius / waves_radius) * saturate(radius - s_depth_range.x * 16.0f);
		
		float wave_height = 0.0f;
		float2 wave_normal = 0.0f;
		
		#define WAVE(NUMBER) { \
			float distance = dot(s_water_waves[NUMBER].xy,texcoord.xy); \
			float phase = (distance + s_water_time) * s_water_waves[NUMBER].z; \
			wave_height += sin(phase) * s_water_waves[NUMBER].w * scale; \
			wave_normal -= s_water_waves[NUMBER].xy * (cos(phase) * s_water_waves[NUMBER].w * s_water_waves[NUMBER].z * scale); \
		}
		
		WAVE(0)
		WAVE(1)
		WAVE(2)
		WAVE(3)
		
		vertex.xyz = vertex.xyz + normal * wave_height - tangent * wave_normal.x - binormal * wave_normal.y;
		normal = normalize(normal + tangent * wave_normal.x + binormal * wave_normal.y);
		
	#endif
	
	float4 direction;
	direction.xyz = (vertex.xyz - s_camera_position) / s_depth_range.y;
	direction.w = s_depth_range.y * surface_density;
	
	#include <core/shaders/water/vertex_base.h>
	
	return OUT;
}

#endif
