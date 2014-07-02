/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    terrain_base.shader
 * Desc:    Terrain base shader
 * Version: 1.05
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
#include <core/shaders/terrains/vertex_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

attribute float4 s_attribute_0;
attribute float4 s_attribute_1;

uniform float2 s_terrain_position;
uniform float4 s_terrain_parameters;
uniform float s_terrain_ilod_distance;

uniform float3 s_terrain_normal;
uniform float3 s_terrain_tangent;
uniform float3 s_terrain_binormal;

/*
 */
void main() {
	
	s_attribute_0 += 32768.0f;
	s_attribute_1 += 32768.0f;
	
	float4 texcoord;
	
	#ifdef PATCH
		
		float4 vertex = s_attribute_0;
		vertex.xyz *= s_terrain_parameters.xxy;
		vertex.xy += s_terrain_position * (s_terrain_parameters.x * 256.0f);
		
		float4 vertex_1 = s_attribute_1 * s_terrain_parameters.y;
		float4 vertex_0 = float4(vertex.z,vertex_1.xyz);
		
		float3 vertex_position;
		vertex_position.x = dot(vertex,s_transform[0]);
		vertex_position.y = dot(vertex,s_transform[1]);
		vertex_position.z = dot(vertex,s_transform[2]);
		
		float distance = length(s_camera_position - vertex_position) * s_terrain_ilod_distance;
		float4 k = saturate((distance - float4(0.5f,1.0f,3.0f,7.0f)) * float4(2.0f,0.5f,0.25f,0.125f));
		float4 lods = lerp(vertex_0,vertex_1,k);
		
		if(distance < 1.0f) vertex.z = lods.x;
		else if(distance < 3.0f) vertex.z = lods.y;
		else if(distance < 7.0f) vertex.z = lods.z;
		else vertex.z = lods.w;
		
		texcoord.xy = s_attribute_0.xy * (1.0f / 256.0f);
		texcoord.zw = (texcoord.xy + s_terrain_position.xy) * s_terrain_parameters.zw;
		
		float2 patch_parameters;
		patch_parameters.x = saturate(1.0f - distance * (1.0 / 15.0f));
		patch_parameters.y = vertex.z / s_terrain_parameters.x * (1.0f / 256.0f);
		
	#elif SURFACE
		
		float4 vertex = s_attribute_0;
		vertex.xyz *= s_terrain_parameters.xxy;
		vertex.xy += s_terrain_position * (s_terrain_parameters.x * 16.0f);
		
		float4 vertex_1 = s_attribute_1 * s_terrain_parameters.y;
		float4 vertex_0 = float4(vertex.z,vertex_1.xyz);
		
		float3 vertex_position;
		vertex_position.x = dot(vertex,s_transform[0]);
		vertex_position.y = dot(vertex,s_transform[1]);
		vertex_position.z = dot(vertex,s_transform[2]);
		
		float distance = length(s_camera_position - vertex_position) * s_terrain_ilod_distance;
		float4 k = saturate((distance - float4(31.0f,63.0f,127.0f,255.0f)) * float4(1.0f,0.5f,0.25f,0.125f) * (1.0f / 32.0f));
		float4 lods = lerp(vertex_0,vertex_1,k);
		
		if(distance < 63.0f) vertex.z = lods.x;
		else if(distance < 127.0f) vertex.z = lods.y;
		else if(distance < 255.0f) vertex.z = lods.z;
		else vertex.z = lods.w;
		
		texcoord.xy = s_attribute_0.xy * (1.0f / 16.0f);
		texcoord.zw = (texcoord.xy + s_terrain_position.xy) * s_terrain_parameters.zw;
		
	#elif COARSE
		
		float4 vertex = s_attribute_0;
		vertex.xyz *= s_terrain_parameters.xxy;
		
		texcoord.xy = s_attribute_0.xy * s_terrain_parameters.zw;
		texcoord.zw = texcoord.xy;
		
	#endif
	
	vertex = float4(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]),1.0f);
	
	float3 normal = s_terrain_normal;
	float3 tangent = s_terrain_tangent;
	float3 binormal = s_terrain_binormal;	
	
	#include <core/shaders/terrains/vertex_base.h>
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
};

float2 s_terrain_position;
float4 s_terrain_parameters;
float s_terrain_ilod_distance;

float3 s_terrain_normal;
float3 s_terrain_tangent;
float3 s_terrain_binormal;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	IN.position += 32768.0f;
	IN.texcoord_0 += 32768.0f;
	
	float4 texcoord;
	
	#ifdef PATCH
		
		float4 vertex = IN.position;
		vertex.xyz *= s_terrain_parameters.xxy;
		vertex.xy += s_terrain_position * (s_terrain_parameters.x * 256.0f);
		
		float4 vertex_1 = IN.texcoord_0 * s_terrain_parameters.y;
		float4 vertex_0 = float4(vertex.z,vertex_1.xyz);
		
		float3 vertex_position;
		vertex_position.x = dot(vertex,s_transform[0]);
		vertex_position.y = dot(vertex,s_transform[1]);
		vertex_position.z = dot(vertex,s_transform[2]);
		
		float distance = length(s_camera_position - vertex_position) * s_terrain_ilod_distance;
		float4 k = saturate((distance - float4(0.5f,1.0f,3.0f,7.0f)) * float4(2.0f,0.5f,0.25f,0.125f));
		float4 lods = lerp(vertex_0,vertex_1,k);
		
		if(distance < 1.0f) vertex.z = lods.x;
		else if(distance < 3.0f) vertex.z = lods.y;
		else if(distance < 7.0f) vertex.z = lods.z;
		else vertex.z = lods.w;
		
		texcoord.xy = IN.position.xy * (1.0f / 256.0f);
		texcoord.zw = (texcoord.xy + s_terrain_position.xy) * s_terrain_parameters.zw;
		
		float2 patch_parameters;
		patch_parameters.x = saturate(1.0f - distance * (1.0 / 15.0f));
		patch_parameters.y = vertex.z / s_terrain_parameters.x * (1.0f / 256.0f);
		
	#elif SURFACE
		
		float4 vertex = IN.position;
		vertex.xyz *= s_terrain_parameters.xxy;
		vertex.xy += s_terrain_position * (s_terrain_parameters.x * 16.0f);
		
		float4 vertex_1 = IN.texcoord_0 * s_terrain_parameters.y;
		float4 vertex_0 = float4(vertex.z,vertex_1.xyz);
		
		float3 vertex_position;
		vertex_position.x = dot(vertex,s_transform[0]);
		vertex_position.y = dot(vertex,s_transform[1]);
		vertex_position.z = dot(vertex,s_transform[2]);
		
		float distance = length(s_camera_position - vertex_position) * s_terrain_ilod_distance;
		float4 k = saturate((distance - float4(31.0f,63.0f,127.0f,255.0f)) * float4(1.0f,0.5f,0.25f,0.125f) * (1.0f / 32.0f));
		float4 lods = lerp(vertex_0,vertex_1,k);
		
		if(distance < 63.0f) vertex.z = lods.x;
		else if(distance < 127.0f) vertex.z = lods.y;
		else if(distance < 255.0f) vertex.z = lods.z;
		else vertex.z = lods.w;
		
		texcoord.xy = IN.position.xy * (1.0f / 16.0f);
		texcoord.zw = (texcoord.xy + s_terrain_position.xy) * s_terrain_parameters.zw;
		
	#elif COARSE
		
		float4 vertex = IN.position;
		vertex.xyz *= s_terrain_parameters.xxy;
		
		texcoord.xy = IN.position.xy * s_terrain_parameters.zw;
		texcoord.zw = texcoord.xy;
		
	#endif
	
	vertex = float4(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]),1.0f);
	
	float3 normal = s_terrain_normal;
	float3 tangent = s_terrain_tangent;
	float3 binormal = s_terrain_binormal;	
	
	#include <core/shaders/terrains/vertex_base.h>
	
	return OUT;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

struct VERTEX_IN {
	uint4 position : POSITION;
	uint4 texcoord_0 : TEXCOORD0;
};

cbuffer shader_terrain_parameters {
	float2 s_terrain_position;
	float4 s_terrain_parameters;
	float s_terrain_ilod_distance;
	float3 s_terrain_normal;
	float3 s_terrain_tangent;
	float3 s_terrain_binormal;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 texcoord;
	
	#ifdef PATCH
		
		float4 vertex = IN.position;
		vertex.xyz *= s_terrain_parameters.xxy;
		vertex.xy += s_terrain_position * (s_terrain_parameters.x * 256.0f);
		
		float4 vertex_1 = IN.texcoord_0 * s_terrain_parameters.y;
		float4 vertex_0 = float4(vertex.z,vertex_1.xyz);
		
		float3 vertex_position;
		vertex_position.x = dot(vertex,s_transform[0]);
		vertex_position.y = dot(vertex,s_transform[1]);
		vertex_position.z = dot(vertex,s_transform[2]);
		
		float distance = length(s_camera_position - vertex_position) * s_terrain_ilod_distance;
		float4 k = saturate((distance - float4(0.5f,1.0f,3.0f,7.0f)) * float4(2.0f,0.5f,0.25f,0.125f));
		float4 lods = lerp(vertex_0,vertex_1,k);
		
		if(distance < 1.0f) vertex.z = lods.x;
		else if(distance < 3.0f) vertex.z = lods.y;
		else if(distance < 7.0f) vertex.z = lods.z;
		else vertex.z = lods.w;
		
		texcoord.xy = IN.position.xy * (1.0f / 256.0f);
		texcoord.zw = (texcoord.xy + s_terrain_position.xy) * s_terrain_parameters.zw;
		
		float2 patch_parameters;
		patch_parameters.x = saturate(1.0f - distance * (1.0 / 15.0f));
		patch_parameters.y = vertex.z / s_terrain_parameters.x * (1.0f / 256.0f);
		
	#elif SURFACE
		
		float4 vertex = IN.position;
		vertex.xyz *= s_terrain_parameters.xxy;
		vertex.xy += s_terrain_position * (s_terrain_parameters.x * 16.0f);
		
		float4 vertex_1 = IN.texcoord_0 * s_terrain_parameters.y;
		float4 vertex_0 = float4(vertex.z,vertex_1.xyz);
		
		float3 vertex_position;
		vertex_position.x = dot(vertex,s_transform[0]);
		vertex_position.y = dot(vertex,s_transform[1]);
		vertex_position.z = dot(vertex,s_transform[2]);
		
		float distance = length(s_camera_position - vertex_position) * s_terrain_ilod_distance;
		float4 k = saturate((distance - float4(31.0f,63.0f,127.0f,255.0f)) * float4(1.0f,0.5f,0.25f,0.125f) * (1.0f / 32.0f));
		float4 lods = lerp(vertex_0,vertex_1,k);
		
		if(distance < 63.0f) vertex.z = lods.x;
		else if(distance < 127.0f) vertex.z = lods.y;
		else if(distance < 255.0f) vertex.z = lods.z;
		else vertex.z = lods.w;
		
		texcoord.xy = IN.position.xy * (1.0f / 16.0f);
		texcoord.zw = (texcoord.xy + s_terrain_position.xy) * s_terrain_parameters.zw;
		
	#elif COARSE
		
		float4 vertex = IN.position;
		vertex.xyz *= s_terrain_parameters.xxy;
		
		texcoord.xy = IN.position.xy * s_terrain_parameters.zw;
		texcoord.zw = texcoord.xy;
		
	#endif
	
	vertex = float4(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]),1.0f);
	
	float3 normal = s_terrain_normal;
	float3 tangent = s_terrain_tangent;
	float3 binormal = s_terrain_binormal;	
	
	#include <core/shaders/terrains/vertex_base.h>
	
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
};

uniform float2 s_terrain_position;
uniform float4 s_terrain_parameters;
uniform float s_terrain_ilod_distance;

uniform float3 s_terrain_normal;
uniform float3 s_terrain_tangent;
uniform float3 s_terrain_binormal;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	IN.position += 32768.0f;
	IN.texcoord_0 += 32768.0f;
	
	float4 texcoord;
	
	#ifdef PATCH
		
		float4 vertex = IN.position;
		vertex.xyz *= s_terrain_parameters.xxy;
		vertex.xy += s_terrain_position * (s_terrain_parameters.x * 256.0f);
		
		float4 vertex_1 = IN.texcoord_0 * s_terrain_parameters.y;
		float4 vertex_0 = float4(vertex.z,vertex_1.xyz);
		
		float3 vertex_position;
		vertex_position.x = dot(vertex,s_transform[0]);
		vertex_position.y = dot(vertex,s_transform[1]);
		vertex_position.z = dot(vertex,s_transform[2]);
		
		float distance = length(s_camera_position - vertex_position) * s_terrain_ilod_distance;
		float4 k = saturate((distance - float4(0.5f,1.0f,3.0f,7.0f)) * float4(2.0f,0.5f,0.25f,0.125f));
		float4 lods = lerp(vertex_0,vertex_1,k);
		
		if(distance < 1.0f) vertex.z = lods.x;
		else if(distance < 3.0f) vertex.z = lods.y;
		else if(distance < 7.0f) vertex.z = lods.z;
		else vertex.z = lods.w;
		
		texcoord.xy = IN.position.xy * (1.0f / 256.0f);
		texcoord.zw = (texcoord.xy + s_terrain_position.xy) * s_terrain_parameters.zw;
		
		float2 patch_parameters;
		patch_parameters.x = saturate(1.0f - distance * (1.0 / 15.0f));
		patch_parameters.y = vertex.z / s_terrain_parameters.x * (1.0f / 256.0f);
		
	#elif SURFACE
		
		float4 vertex = IN.position;
		vertex.xyz *= s_terrain_parameters.xxy;
		vertex.xy += s_terrain_position * (s_terrain_parameters.x * 16.0f);
		
		float4 vertex_1 = IN.texcoord_0 * s_terrain_parameters.y;
		float4 vertex_0 = float4(vertex.z,vertex_1.xyz);
		
		float3 vertex_position;
		vertex_position.x = dot(vertex,s_transform[0]);
		vertex_position.y = dot(vertex,s_transform[1]);
		vertex_position.z = dot(vertex,s_transform[2]);
		
		float distance = length(s_camera_position - vertex_position) * s_terrain_ilod_distance;
		float4 k = saturate((distance - float4(31.0f,63.0f,127.0f,255.0f)) * float4(1.0f,0.5f,0.25f,0.125f) * (1.0f / 32.0f));
		float4 lods = lerp(vertex_0,vertex_1,k);
		
		if(distance < 63.0f) vertex.z = lods.x;
		else if(distance < 127.0f) vertex.z = lods.y;
		else if(distance < 255.0f) vertex.z = lods.z;
		else vertex.z = lods.w;
		
		texcoord.xy = IN.position.xy * (1.0f / 16.0f);
		texcoord.zw = (texcoord.xy + s_terrain_position.xy) * s_terrain_parameters.zw;
		
	#elif COARSE
		
		float4 vertex = IN.position;
		vertex.xyz *= s_terrain_parameters.xxy;
		
		texcoord.xy = IN.position.xy * s_terrain_parameters.zw;
		texcoord.zw = texcoord.xy;
		
	#endif
	
	vertex = float4(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]),1.0f);
	
	float3 normal = s_terrain_normal;
	float3 tangent = s_terrain_tangent;
	float3 binormal = s_terrain_binormal;	
	
	#include <core/shaders/terrains/vertex_base.h>
	
	return OUT;
}

#endif
