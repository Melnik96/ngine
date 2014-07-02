/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    evaluate_base.shader
 * Desc:    Mesh base shader
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

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

#ifdef USE_TESSELLATION && TESSELLATION

#include <core/shaders/common/evaluate_base.h>
#include <core/shaders/meshes/evaluate_base.h>

layout(triangles,fractional_odd_spacing,ccw) in;

uniform sampler2D s_texture_20;

/*
 */
void main() {
	
	float4 vertex = gl_in[0].gl_Position * gl_TessCoord.x + gl_in[1].gl_Position * gl_TessCoord.y + gl_in[2].gl_Position * gl_TessCoord.z;
	float4 normal = gl_in[0].gl_TexCoord[7] * gl_TessCoord.x + gl_in[1].gl_TexCoord[7] * gl_TessCoord.y + gl_in[2].gl_TexCoord[7] * gl_TessCoord.z;
	float2 texcoord = gl_in[0].gl_TexCoord[0].xy * gl_TessCoord.x + gl_in[1].gl_TexCoord[0].xy * gl_TessCoord.y + gl_in[2].gl_TexCoord[0].xy * gl_TessCoord.z;
	float distance = length(vertex.xyz - s_camera_position);
	
	float lod = clamp((distance - s_material_tessellation_distance.x) * s_material_tessellation_distance.y,0.0f,8.0f);
	float offset = pow(saturate(1.0f - (distance - s_material_tessellation_distance.x) * s_material_tessellation_distance.y),s_material_tessellation_factor.y);
	offset *= (textureLod(s_texture_20,texcoord,lod).x - 127.0f / 255.0f) * s_material_tessellation_factor.x;
	vertex.xyz += normal.xyz * offset;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float alpha_fade = vertex.w;
		vertex.w = 1.0f;
	#endif
	
	#include <core/shaders/meshes/evaluate_base.h>
}

#endif

/******************************************************************************\
*
* Direct3D11
*
\******************************************************************************/

#elif DIRECT3D11

#ifdef USE_TESSELLATION && TESSELLATION

#include <core/shaders/common/evaluate_base.h>
#include <core/shaders/meshes/evaluate_base.h>

Texture2D s_texture_0 : register(t0);

struct EVALUATE_CONSTANT_IN {
	float edges[3] : SV_TESSFACTOR;
	float inside : SV_INSIDETESSFACTOR;
	float3 coords : SV_DOMAINLOCATION;
};

/*
 */
[domain("tri")]
EVALUATE_OUT main(EVALUATE_CONSTANT_IN IN,const OutputPatch<EVALUATE_IN,3> patch) {
	
	EVALUATE_OUT OUT;
	
	float4 vertex = patch[0].position * IN.coords.x + patch[1].position * IN.coords.y + patch[2].position * IN.coords.z;
	float4 normal = patch[0].texcoord_9 * IN.coords.x + patch[1].texcoord_9 * IN.coords.y + patch[2].texcoord_9 * IN.coords.z;
	float2 texcoord = patch[0].texcoord_0.xy * IN.coords.x + patch[1].texcoord_0.xy * IN.coords.y + patch[2].texcoord_0.xy * IN.coords.z;
	float distance = length(vertex.xyz - s_camera_position);
	
	float lod = clamp((distance - s_material_tessellation_distance.x) * s_material_tessellation_distance.y,0.0f,8.0f);
	float offset = pow(saturate(1.0f - (distance - s_material_tessellation_distance.x) * s_material_tessellation_distance.y),s_material_tessellation_factor.y);
	offset *= (s_texture_0.SampleLevel(s_sampler_0,texcoord,lod).x - 127.0f / 255.0f) * s_material_tessellation_factor.x;
	vertex.xyz += normal.xyz * offset;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float alpha_fade = vertex.w;
		vertex.w = 1.0f;
	#endif
	
	#include <core/shaders/meshes/evaluate_base.h>
	
	return OUT;
}

#endif

#endif
