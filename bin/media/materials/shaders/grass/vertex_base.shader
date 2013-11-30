/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base.shader
 * Desc:    Grass base shader
 * Version: 1.11
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
#include <core/shaders/grass/vertex_base.h>

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

uniform float3 s_grass_position;
uniform float2 s_grass_isize;
uniform float4 s_grass_texcoord;

uniform float4 noise_transform;
uniform float slope_scale;
uniform float shadow_offset;
uniform float alpha_scale;

/*
 */
void main() {
	
	float4 position = float4(s_attribute_0.xyz + s_grass_position,1.0f);
	float4 vertex = float4(dot(s_transform[0],position),dot(s_transform[1],position),dot(s_transform[2],position),1.0f);
	
	#ifdef CLUTTER
		float3 tangent = s_attribute_2.xyz * 2.0f - 1.0f;
		float3 binormal = s_attribute_1.xyz * 2.0f - 1.0f;
		binormal = cross(binormal,tangent);
	#else
		#ifdef BILLBOARD
			float3 tangent = -normalize(float3(s_modelview[0][0],s_modelview[1][0],s_modelview[2][0]));
		#else
			float3 tangent = s_attribute_2.xyz * 2.0f - 1.0f;
		#endif
		float3 binormal_0 = -s_attribute_1.xyz * 2.0f + 1.0f;
		float3 binormal_1 = -normalize(float3(s_modelview[0][1],s_modelview[1][1],s_modelview[2][1]));
		float3 binormal = normalize(lerp(binormal_0,binormal_1,slope_scale));
		tangent = normalize(cross(binormal,cross(tangent,binormal)));
		#ifdef BASE_SHADOW
			vertex.xyz += normalize(float3(s_modelview[0][2],s_modelview[1][2],s_modelview[2][2])) * shadow_offset;
		#endif
	#endif
	
	float distance = length(s_camera_position - vertex.xyz);
	
	float width = (s_attribute_1.w * 2.0f - 1.0f) * s_attribute_0.w;
	float height = (s_attribute_2.w * 2.0f - 1.0f) * s_attribute_0.w;
	
	vertex.xyz -= tangent * ((s_attribute_3.x - 0.5f) * width);
	vertex.xyz -= binormal * (s_attribute_3.y * height);
	
	float2 texcoord = s_attribute_3.xy * s_grass_texcoord.xy + s_attribute_3.zw * s_grass_texcoord.zw;
	texcoord.y = 1.0f - texcoord.y;
	
	float2 lightmap = position.xy * s_grass_isize;
	float2 noise = lightmap * noise_transform.xy + noise_transform.zw;
	
	float3 direction = s_attribute_1.xyz * 2.0f - 1.0f;
	
	float fade_in = saturate((distance - s_surface_distances.x) / s_surface_distances.z);
	float fade_out = saturate((distance - s_surface_distances.y) / s_surface_distances.w);
	float fade = saturate(fade_in - fade_out);
	float alpha = fade * alpha_scale * 0.5f + 0.5f;
	
	#ifndef CLUTTER
		float stem_scale = max(s_attribute_3.y * height * s_material_animation_stem.y,0.0f);
		float stem_angle = dot(position.xy,float2(s_material_animation_stem.x)) + s_material_animation_stem.w;
		float2 stem_offset = getAnimationOffset(stem_angle) * (stem_scale * fade);
		vertex.z -= length(stem_offset) * s_material_animation_stem.z;
		vertex.xy += stem_offset;
	#endif
	
	#include <core/shaders/grass/vertex_base.h>
	
	if(fade < 1e-3f) gl_Position = float4(0.0f);
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

float3 s_grass_position;
float2 s_grass_isize;
float4 s_grass_texcoord;

float4 noise_transform;
float slope_scale;
float shadow_offset;
float alpha_scale;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 position = float4(IN.position.xyz + s_grass_position,1.0f);
	float4 vertex = float4(dot(s_transform[0],position),dot(s_transform[1],position),dot(s_transform[2],position),1.0f);
	
	#ifdef CLUTTER
		float3 tangent = IN.texcoord_1.xyz * 2.0f - 1.0f;
		float3 binormal = IN.texcoord_0.xyz * 2.0f - 1.0f;
		binormal = cross(binormal,tangent);
	#else
		#ifdef BILLBOARD
			float3 tangent = -normalize(s_modelview[0].xyz);
		#else
			float3 tangent = IN.texcoord_1.xyz * 2.0f - 1.0f;
		#endif
		float3 binormal_0 = -IN.texcoord_0.xyz * 2.0f + 1.0f;
		float3 binormal_1 = -normalize(s_modelview[1].xyz);
		#ifdef BASE_SHADOW
			binormal_1 = -binormal_1;
			vertex.xyz += normalize(s_modelview[2].xyz) * shadow_offset;
		#endif
		float3 binormal = normalize(lerp(binormal_0,binormal_1,slope_scale));
		tangent = normalize(cross(binormal,cross(tangent,binormal)));
	#endif
	
	float distance = length(s_camera_position - vertex.xyz);
	
	float width = (IN.texcoord_0.w * 2.0f - 1.0f) * IN.position.w;
	float height = (IN.texcoord_1.w * 2.0f - 1.0f) * IN.position.w;
	
	vertex.xyz -= tangent * (IN.texcoord_2.x - 0.5f) * width;
	vertex.xyz -= binormal * IN.texcoord_2.y * height;
	
	float2 texcoord = IN.texcoord_2.xy * s_grass_texcoord.xy + IN.texcoord_2.zw * s_grass_texcoord.zw;
	texcoord.y = 1.0f - texcoord.y;
	
	float2 lightmap = position.xy * s_grass_isize;
	float2 noise = lightmap * noise_transform.xy + noise_transform.zw;
	
	float3 direction = IN.texcoord_0.xyz * 2.0f - 1.0f;
	
	float fade_in = saturate((distance - s_surface_distances.x) / s_surface_distances.z);
	float fade_out = saturate((distance - s_surface_distances.y) / s_surface_distances.w);
	float fade = saturate(fade_in - fade_out);
	float alpha = fade * alpha_scale * 0.5f + 0.5f;
	
	#ifndef CLUTTER
		float stem_scale = max(IN.texcoord_2.y * height * s_material_animation_stem.y,0.0f);
		float stem_angle = dot(position.xy,s_material_animation_stem.x) + s_material_animation_stem.w;
		float2 stem_offset = getAnimationOffset(stem_angle) * (stem_scale * fade);
		vertex.z -= length(stem_offset) * s_material_animation_stem.z;
		vertex.xy += stem_offset;
	#endif
	
	#include <core/shaders/grass/vertex_base.h>
	
	if(fade < 1e-3f) OUT.position = 0.0f;
	
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

cbuffer shader_grass_parameters {
	float3 s_grass_position;
	float2 s_grass_isize;
	float4 s_grass_texcoord;
};

cbuffer shader_parameters {
	float4 noise_transform;
	float slope_scale;
	float shadow_offset;
	float alpha_scale;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 position = float4(IN.position.xyz + s_grass_position,1.0f);
	float4 vertex = float4(dot(s_transform[0],position),dot(s_transform[1],position),dot(s_transform[2],position),1.0f);
	
	#ifdef CLUTTER
		float3 tangent = IN.texcoord_1.xyz * 2.0f - 1.0f;
		float3 binormal = IN.texcoord_0.xyz * 2.0f - 1.0f;
		binormal = cross(binormal,tangent);
	#else
		#ifdef BILLBOARD
			float3 tangent = -normalize(s_modelview[0].xyz);
		#else
			float3 tangent = IN.texcoord_1.xyz * 2.0f - 1.0f;
		#endif
		float3 binormal_0 = -IN.texcoord_0.xyz * 2.0f + 1.0f;
		float3 binormal_1 = -normalize(s_modelview[1].xyz);
		#ifdef BASE_SHADOW
			binormal_1 = -binormal_1;
			vertex.xyz += normalize(s_modelview[2].xyz) * shadow_offset;
		#endif
		float3 binormal = normalize(lerp(binormal_0,binormal_1,slope_scale));
		tangent = normalize(cross(binormal,cross(tangent,binormal)));
	#endif
	
	float distance = length(s_camera_position - vertex.xyz);
	
	float width = (IN.texcoord_0.w * 2.0f - 1.0f) * IN.position.w;
	float height = (IN.texcoord_1.w * 2.0f - 1.0f) * IN.position.w;
	
	vertex.xyz -= tangent * (IN.texcoord_2.x - 0.5f) * width;
	vertex.xyz -= binormal * IN.texcoord_2.y * height;
	
	float2 texcoord = IN.texcoord_2.xy * s_grass_texcoord.xy + IN.texcoord_2.zw * s_grass_texcoord.zw;
	texcoord.y = 1.0f - texcoord.y;
	
	float2 lightmap = position.xy * s_grass_isize;
	float2 noise = lightmap * noise_transform.xy + noise_transform.zw;
	
	float3 direction = IN.texcoord_0.xyz * 2.0f - 1.0f;
	
	float fade_in = saturate((distance - s_surface_distances.x) / s_surface_distances.z);
	float fade_out = saturate((distance - s_surface_distances.y) / s_surface_distances.w);
	float fade = saturate(fade_in - fade_out);
	float alpha = fade * alpha_scale * 0.5f + 0.5f;
	
	#ifndef CLUTTER
		float stem_scale = max(IN.texcoord_2.y * height * s_material_animation_stem.y,0.0f);
		float stem_angle = dot(position.xy,s_material_animation_stem.x) + s_material_animation_stem.w;
		float2 stem_offset = getAnimationOffset(stem_angle) * (stem_scale * fade);
		vertex.z -= length(stem_offset) * s_material_animation_stem.z;
		vertex.xy += stem_offset;
	#endif
	
	#include <core/shaders/grass/vertex_base.h>
	
	if(fade < 1e-3f) OUT.position = 0.0f;
	
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

uniform float3 s_grass_position;
uniform float2 s_grass_isize;
uniform float4 s_grass_texcoord;

uniform float4 noise_transform;
uniform float slope_scale;
uniform float shadow_offset;
uniform float alpha_scale;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 position = float4(IN.position.xyz + s_grass_position,1.0f);
	float4 vertex = float4(dot(s_transform[0],position),dot(s_transform[1],position),dot(s_transform[2],position),1.0f);
	
	#ifdef CLUTTER
		float3 tangent = IN.texcoord_1.xyz * 2.0f - 1.0f;
		float3 binormal = IN.texcoord_0.xyz * 2.0f - 1.0f;
		binormal = cross(binormal,tangent);
	#else
		#ifdef BILLBOARD
			float3 tangent = -normalize(s_modelview[0].xyz);
		#else
			float3 tangent = IN.texcoord_1.xyz * 2.0f - 1.0f;
		#endif
		float3 binormal_0 = -IN.texcoord_0.xyz * 2.0f + 1.0f;
		float3 binormal_1 = -normalize(s_modelview[1].xyz);
		#ifdef BASE_SHADOW
			binormal_1 = -binormal_1;
			vertex.xyz += normalize(s_modelview[2].xyz) * shadow_offset;
		#endif
		float3 binormal = normalize(lerp(binormal_0,binormal_1,slope_scale));
		tangent = normalize(cross(binormal,cross(tangent,binormal)));
	#endif
	
	float distance = length(s_camera_position - vertex.xyz);
	
	float width = (IN.texcoord_0.w * 2.0f - 1.0f) * IN.position.w;
	float height = (IN.texcoord_1.w * 2.0f - 1.0f) * IN.position.w;
	
	vertex.xyz -= tangent * (IN.texcoord_2.x - 0.5f) * width;
	vertex.xyz -= binormal * IN.texcoord_2.y * height;
	
	float2 texcoord = IN.texcoord_2.xy * s_grass_texcoord.xy + IN.texcoord_2.zw * s_grass_texcoord.zw;
	texcoord.y = 1.0f - texcoord.y;
	
	float2 lightmap = position.xy * s_grass_isize;
	float2 noise = lightmap * noise_transform.xy + noise_transform.zw;
	
	float3 direction = IN.texcoord_0.xyz * 2.0f - 1.0f;
	
	float fade_in = saturate((distance - s_surface_distances.x) / s_surface_distances.z);
	float fade_out = saturate((distance - s_surface_distances.y) / s_surface_distances.w);
	float fade = saturate(fade_in - fade_out);
	float alpha = fade * alpha_scale * 0.5f + 0.5f;
	
	#ifndef CLUTTER
		float stem_scale = max(IN.texcoord_2.y * height * s_material_animation_stem.y,0.0f);
		float stem_angle = dot(position.xy,s_material_animation_stem.x) + s_material_animation_stem.w;
		float2 stem_offset = getAnimationOffset(stem_angle) * (stem_scale * fade);
		vertex.z -= length(stem_offset) * s_material_animation_stem.z;
		vertex.xy += stem_offset;
	#endif
	
	#include <core/shaders/grass/vertex_base.h>
	
	if(fade < 1e-3f) OUT.position = 0.0f;
	
	return OUT;
}

#endif
