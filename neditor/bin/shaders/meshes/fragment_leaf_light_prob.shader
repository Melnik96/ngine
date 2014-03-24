/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_leaf_light_prob.shader
 * Desc:    Mesh leaf light prob shader
 * Version: 1.02
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

/* s_texture_0 is diffuse texture
 * s_texture_2 is normal texture
 * s_texture_4 is noise texture
 * s_texture_5 is color texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;
uniform sampler2D s_texture_2;
uniform sampler3D s_texture_4;
uniform sampler2D s_texture_5;

uniform half noise_scale;
uniform half4 color_scale;

/*
 */
void main() {
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	half3 world_normal;
	#ifdef QUALITY_MEDIUM && PHONG
		half3 normal = texture2DNormal(s_texture_2,gl_TexCoord[0].xy);
		world_normal.x = dot(half3(gl_TexCoord[1].xyz),normal);
		world_normal.y = dot(half3(gl_TexCoord[2].xyz),normal);
		world_normal.z = dot(half3(gl_TexCoord[3].xyz),normal);
	#else
		world_normal = gl_TexCoord[1].xyz;
	#endif
	half3 color = diffuse.xyz * getEnvironment(world_normal) * s_material_shading.x;
	
	gl_FragColor = half4(color,diffuse.w) * color_scale;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	#ifdef QUALITY_MEDIUM && PHONG
		half3 texcoord_2 : TEXCOORD2;
		half3 texcoord_3 : TEXCOORD3;
	#endif
	#ifdef NOISE
		float3 texcoord_6 : TEXCOORD6;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		half1 texcoord_7 : TEXCOORD7;
	#endif
};

half noise_scale;
half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	half3 world_normal;
	#ifdef QUALITY_MEDIUM && PHONG
		half3 normal = tex2DNormal(s_texture_2,IN.texcoord_0.xy);
		world_normal.x = dot(IN.texcoord_1,normal);
		world_normal.y = dot(IN.texcoord_2,normal);
		world_normal.z = dot(IN.texcoord_3,normal);
	#else
		world_normal = IN.texcoord_1;
	#endif
	half3 color = diffuse.xyz * getEnvironment(world_normal) * s_material_shading.x;
	
	return half4(color,diffuse.w) * color_scale;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
Texture2D s_texture_2 : register(t2);
Texture3D s_texture_4 : register(t4);
Texture2D s_texture_5 : register(t5);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	#ifdef QUALITY_MEDIUM && PHONG
		float3 texcoord_2 : TEXCOORD2;
		float3 texcoord_3 : TEXCOORD3;
	#endif
	#ifdef NOISE
		float3 texcoord_6 : TEXCOORD6;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

cbuffer shader_parameters {
	#ifdef NOISE
		float noise_scale;
	#endif
	float4 color_scale;
};

/*
 */
FRAGMENT_ALPHA_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_ALPHA_OUT OUT;
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	half3 world_normal;
	#ifdef QUALITY_MEDIUM && PHONG
		float3 normal = texture2DNormal(s_texture_2,s_sampler_2,IN.texcoord_0.xy);
		world_normal.x = dot(IN.texcoord_1,normal);
		world_normal.y = dot(IN.texcoord_2,normal);
		world_normal.z = dot(IN.texcoord_3,normal);
	#else
		world_normal = IN.texcoord_1;
	#endif
	half3 color = diffuse.xyz * getEnvironment(world_normal) * s_material_shading.x;
	
	OUT.color = float4(color,diffuse.w) * color_scale;
	
	return OUT;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_0 : TEXUNIT0;
uniform sampler2D s_texture_2 : TEXUNIT2;
uniform sampler3D s_texture_4 : TEXUNIT4;
uniform sampler2D s_texture_5 : TEXUNIT5;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	#ifdef QUALITY_MEDIUM && PHONG
		half3 texcoord_2 : TEXCOORD2;
		half3 texcoord_3 : TEXCOORD3;
	#endif
	#ifdef NOISE
		float3 texcoord_8 : TEXCOORD8;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half noise_scale;
uniform half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	half3 world_normal;
	#ifdef QUALITY_MEDIUM && PHONG
		half3 normal = tex2DNormal(s_texture_2,IN.texcoord_0.xy);
		world_normal.x = dot(IN.texcoord_1,normal);
		world_normal.y = dot(IN.texcoord_2,normal);
		world_normal.z = dot(IN.texcoord_3,normal);
	#else
		world_normal = IN.texcoord_1;
	#endif
	half3 color = diffuse.xyz * getEnvironment(world_normal) * s_material_shading.x;
	
	return half4(color,diffuse.w) * color_scale;
}

#endif
