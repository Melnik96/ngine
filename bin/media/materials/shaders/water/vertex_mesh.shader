/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_mesh.shader
 * Desc:    Water mesh shader
 * Version: 1.07
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
attribute float4 s_attribute_1;
attribute float4 s_attribute_2;
attribute float4 s_attribute_3;

uniform float4 s_water_waves[4];
uniform float s_water_time;

uniform float waves_radius;
uniform float surface_density;
uniform float volume_density;

/*
 */
void main() {
	
	float4 vertex = float4(s_attribute_0.x,s_attribute_0.y,s_attribute_2.w,1.0f);
	vertex.xyz = float3(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]));
	
	float3 normal = normalize(float3(dot(s_attribute_2.xyz,s_transform[0].xyz),dot(s_attribute_2.xyz,s_transform[1].xyz),dot(s_attribute_2.xyz,s_transform[2].xyz)));
	float3 tangent = normalize(float3(dot(s_attribute_3.xyz,s_transform[0].xyz),dot(s_attribute_3.xyz,s_transform[1].xyz),dot(s_attribute_3.xyz,s_transform[2].xyz)));
	float3 binormal = cross(normal,tangent) * s_attribute_3.w;
	
	float3 position = vertex.xyz - float3(s_transform[0].w,s_transform[1].w,s_transform[2].w);
	float2 wave = float2(dot(tangent,position),dot(binormal,position));
	float2 texcoord = s_attribute_1.xy;
	
	#ifdef WAVES
		
		float radius = length(vertex.xyz - s_camera_position);
		float scale = saturate(1.0f - radius / waves_radius);
		
		float wave_height = 0.0f;
		float2 wave_normal = float2(0.0f);
		
		#define WAVE(NUMBER) { \
			float distance = dot(s_water_waves[NUMBER].xy,wave); \
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
	
	#ifdef VOLUME_AMBIENT || VOLUME_LIGHT_WORLD
		direction.w = s_depth_range.y * volume_density;
	#else
		direction.w = s_depth_range.y * surface_density;
	#endif
	
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
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
};

float4 s_water_waves[4];
float s_water_time;

float waves_radius;
float surface_density;
float volume_density;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = float4(IN.position.x,IN.position.y,IN.texcoord_1.w,1.0f);
	vertex.xyz = float3(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]));
	
	float3 normal = normalize(float3(dot(IN.texcoord_1.xyz,s_transform[0].xyz),dot(IN.texcoord_1.xyz,s_transform[1].xyz),dot(IN.texcoord_1.xyz,s_transform[2].xyz)));
	float3 tangent = normalize(float3(dot(IN.texcoord_2.xyz,s_transform[0].xyz),dot(IN.texcoord_2.xyz,s_transform[1].xyz),dot(IN.texcoord_2.xyz,s_transform[2].xyz)));
	float3 binormal = cross(normal,tangent) * IN.texcoord_2.w;
	
	float3 position = vertex.xyz - float3(s_transform[0].w,s_transform[1].w,s_transform[2].w);
	float2 wave = float2(dot(tangent,position),dot(binormal,position));
	float2 texcoord = IN.texcoord_0.xy;
	
	#ifdef WAVES
		
		float radius = length(vertex.xyz - s_camera_position);
		float scale = saturate(1.0f - radius / waves_radius);
		
		float wave_height = 0.0f;
		float2 wave_normal = 0.0f;
		
		#define WAVE(NUMBER) { \
			float distance = dot(s_water_waves[NUMBER].xy,wave); \
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
	
	#ifdef VOLUME_AMBIENT || VOLUME_LIGHT_WORLD
		direction.w = s_depth_range.y * volume_density;
	#else
		direction.w = s_depth_range.y * surface_density;
	#endif
	
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
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
};

cbuffer shader_water_parameters {
	float4 s_water_waves[4];
	float s_water_time;
};

cbuffer shader_parameters {
	float waves_radius;
	float surface_density;
	float volume_density;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = float4(IN.position.x,IN.position.y,IN.texcoord_1.w,1.0f);
	vertex.xyz = float3(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]));
	
	float3 normal = normalize(float3(dot(IN.texcoord_1.xyz,s_transform[0].xyz),dot(IN.texcoord_1.xyz,s_transform[1].xyz),dot(IN.texcoord_1.xyz,s_transform[2].xyz)));
	float3 tangent = normalize(float3(dot(IN.texcoord_2.xyz,s_transform[0].xyz),dot(IN.texcoord_2.xyz,s_transform[1].xyz),dot(IN.texcoord_2.xyz,s_transform[2].xyz)));
	float3 binormal = cross(normal,tangent) * IN.texcoord_2.w;
	
	float3 position = vertex.xyz - float3(s_transform[0].w,s_transform[1].w,s_transform[2].w);
	float2 wave = float2(dot(tangent,position),dot(binormal,position));
	float2 texcoord = IN.texcoord_0.xy;
	
	#ifdef WAVES
		
		float radius = length(vertex.xyz - s_camera_position);
		float scale = saturate(1.0f - radius / waves_radius);
		
		float wave_height = 0.0f;
		float2 wave_normal = 0.0f;
		
		#define WAVE(NUMBER) { \
			float distance = dot(s_water_waves[NUMBER].xy,wave); \
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
	
	#ifdef VOLUME_AMBIENT || VOLUME_LIGHT_WORLD
		direction.w = s_depth_range.y * volume_density;
	#else
		direction.w = s_depth_range.y * surface_density;
	#endif
	
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
	float4 texcoord_0 : ATTR1;
	float4 texcoord_1 : ATTR2;
	float4 texcoord_2 : ATTR3;
};

uniform float4 s_water_waves[4];
uniform float s_water_time;

uniform float waves_radius;
uniform float surface_density;
uniform float volume_density;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = float4(IN.position.x,IN.position.y,IN.texcoord_1.w,1.0f);
	vertex.xyz = float3(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]));
	
	float3 normal = normalize(float3(dot(IN.texcoord_1.xyz,s_transform[0].xyz),dot(IN.texcoord_1.xyz,s_transform[1].xyz),dot(IN.texcoord_1.xyz,s_transform[2].xyz)));
	float3 tangent = normalize(float3(dot(IN.texcoord_2.xyz,s_transform[0].xyz),dot(IN.texcoord_2.xyz,s_transform[1].xyz),dot(IN.texcoord_2.xyz,s_transform[2].xyz)));
	float3 binormal = cross(normal,tangent) * IN.texcoord_2.w;
	
	float3 position = vertex.xyz - float3(s_transform[0].w,s_transform[1].w,s_transform[2].w);
	float2 wave = float2(dot(tangent,position),dot(binormal,position));
	float2 texcoord = IN.texcoord_0.xy;
	
	#ifdef WAVES
		
		float radius = length(vertex.xyz - s_camera_position);
		float scale = saturate(1.0f - radius / waves_radius);
		
		float wave_height = 0.0f;
		float2 wave_normal = 0.0f;
		
		#define WAVE(NUMBER) { \
			float distance = dot(s_water_waves[NUMBER].xy,wave); \
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
	
	#ifdef VOLUME_AMBIENT || VOLUME_LIGHT_WORLD
		direction.w = s_depth_range.y * volume_density;
	#else
		direction.w = s_depth_range.y * surface_density;
	#endif
	
	#include <core/shaders/water/vertex_base.h>
	
	return OUT;
}

#endif
