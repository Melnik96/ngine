/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_terrain_deferred.shader
 * Desc:    Mesh terrain deferred shader
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
 * s_texture_1 is normal texture
 * s_texture_2 is mask texture
 * s_texture_3 is detail_1 diffuse texture
 * s_texture_4 is detail_1 normal texture
 * s_texture_5 is detail_2 diffuse texture
 * s_texture_6 is detail_2 normal texture
 * s_texture_7 is detail_3 diffuse texture
 * s_texture_8 is detail_3 normal texture
 * s_texture_9 is detail_4 diffuse texture
 * s_texture_10 is detail_4 normal texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;
uniform sampler2D s_texture_1;
uniform sampler2D s_texture_2;
uniform sampler2D s_texture_3;
uniform sampler2D s_texture_4;
uniform sampler2D s_texture_5;
uniform sampler2D s_texture_6;
uniform sampler2D s_texture_7;
uniform sampler2D s_texture_8;
uniform sampler2D s_texture_9;
uniform sampler2D s_texture_10;

uniform half4 detail_1_transform;
uniform half4 detail_2_transform;
uniform half4 detail_3_transform;
uniform half4 detail_4_transform;
uniform half detail_1_diffuse;
uniform half detail_1_normal;
uniform half detail_2_diffuse;
uniform half detail_2_normal;
uniform half detail_3_diffuse;
uniform half detail_3_normal;
uniform half detail_4_diffuse;
uniform half detail_4_normal;

uniform half specular_power;

/*
 */
void main() {
	
	#include <core/shaders/meshes/fragment_terrain_sample.h>
	
	gl_FragData[0] = setDeferredDepth(length(gl_TexCoord[1].xyz),0.0f);
	
	gl_FragData[1] = setDeferredColor(diffuse.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 screen_normal;
		screen_normal.x = dot(half3(gl_TexCoord[2].xyz),normal);
		screen_normal.y = dot(half3(gl_TexCoord[3].xyz),normal);
		screen_normal.z = dot(half3(gl_TexCoord[4].xyz),normal);
		screen_normal = normalize(screen_normal);
		gl_FragData[2] = setDeferredNormal(screen_normal,specular_power);
	#elif USE_PARALLAX
		gl_FragData[2] = half4(0.0f);
	#endif
	
	#ifdef USE_PARALLAX
		gl_FragData[3] = half4(0.0f);
	#endif
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 texcoord_2 : TEXCOORD2;
		half3 texcoord_3 : TEXCOORD3;
		half3 texcoord_4 : TEXCOORD4;
	#endif
};

half4 detail_1_transform;
half4 detail_2_transform;
half4 detail_3_transform;
half4 detail_4_transform;
half detail_1_diffuse;
half detail_1_normal;
half detail_2_diffuse;
half detail_2_normal;
half detail_3_diffuse;
half detail_3_normal;
half detail_4_diffuse;
half detail_4_normal;

half specular_power;

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#include <core/shaders/meshes/fragment_terrain_sample.h>
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_1),0.0f);
	
	OUT.color_1 = setDeferredColor(diffuse.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 screen_normal;
		screen_normal.x = dot(IN.texcoord_2,normal);
		screen_normal.y = dot(IN.texcoord_3,normal);
		screen_normal.z = dot(IN.texcoord_4,normal);
		screen_normal = normalize(screen_normal);
		OUT.color_2 = setDeferredNormal(screen_normal,specular_power);
	#elif USE_PARALLAX
		OUT.color_2 = 0.0f;
	#endif
	
	#ifdef USE_PARALLAX
		OUT.color_3 = 0.0f;
	#endif
	
	return OUT;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
Texture2D s_texture_1 : register(t1);
Texture2D s_texture_2 : register(t2);
Texture2D s_texture_3 : register(t3);
Texture2D s_texture_4 : register(t4);
Texture2D s_texture_5 : register(t5);
Texture2D s_texture_6 : register(t6);
Texture2D s_texture_7 : register(t7);
Texture2D s_texture_8 : register(t8);
Texture2D s_texture_9 : register(t9);
Texture2D s_texture_10 : register(t10);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	#ifdef USE_DEFERRED || USE_OCCLUSION
		float3 texcoord_2 : TEXCOORD2;
		float3 texcoord_3 : TEXCOORD3;
		float3 texcoord_4 : TEXCOORD4;
	#endif
};

cbuffer shader_parameters {
	#ifdef DETAIL_1 || DETAIL_2 || DETAIL_3 || DETAIL_4
		float4 detail_1_transform;
		float detail_1_diffuse;
		float detail_1_normal;
	#endif
	#ifdef DETAIL_2 || DETAIL_3 || DETAIL_4
		float4 detail_2_transform;
		float detail_2_diffuse;
		float detail_2_normal;
	#endif
	#ifdef DETAIL_3 || DETAIL_4
		float4 detail_3_transform;
		float detail_3_diffuse;
		float detail_3_normal;
	#endif
	#ifdef DETAIL_4
		float4 detail_4_transform;
		float detail_4_diffuse;
		float detail_4_normal;
	#endif
	#ifdef USE_DEFERRED || USE_OCCLUSION
		float specular_power;
	#endif
};

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#include <core/shaders/meshes/fragment_terrain_sample.h>
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_1),0.0f);
	
	OUT.color_1 = setDeferredColor(diffuse.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 screen_normal;
		screen_normal.x = dot(IN.texcoord_2,normal);
		screen_normal.y = dot(IN.texcoord_3,normal);
		screen_normal.z = dot(IN.texcoord_4,normal);
		screen_normal = normalize(screen_normal);
		OUT.color_2 = setDeferredNormal(screen_normal,specular_power);
	#elif USE_PARALLAX
		OUT.color_2 = 0.0f;
	#endif
	
	#ifdef USE_PARALLAX
		OUT.color_3 = 0.0f;
	#endif
	
	return OUT;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_0 : TEXUNIT0;
uniform sampler2D s_texture_1 : TEXUNIT1;
uniform sampler2D s_texture_2 : TEXUNIT2;
uniform sampler2D s_texture_3 : TEXUNIT3;
uniform sampler2D s_texture_4 : TEXUNIT4;
uniform sampler2D s_texture_5 : TEXUNIT5;
uniform sampler2D s_texture_6 : TEXUNIT6;
uniform sampler2D s_texture_7 : TEXUNIT7;
uniform sampler2D s_texture_8 : TEXUNIT8;
uniform sampler2D s_texture_9 : TEXUNIT9;
uniform sampler2D s_texture_10 : TEXUNIT10;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 texcoord_2 : TEXCOORD2;
		half3 texcoord_3 : TEXCOORD3;
		half3 texcoord_4 : TEXCOORD4;
	#endif
};

uniform half4 detail_1_transform;
uniform half4 detail_2_transform;
uniform half4 detail_3_transform;
uniform half4 detail_4_transform;
uniform half detail_1_diffuse;
uniform half detail_1_normal;
uniform half detail_2_diffuse;
uniform half detail_2_normal;
uniform half detail_3_diffuse;
uniform half detail_3_normal;
uniform half detail_4_diffuse;
uniform half detail_4_normal;

uniform half specular_power;

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#include <core/shaders/meshes/fragment_terrain_sample.h>
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_1),0.0f);
	
	OUT.color_1 = setDeferredColor(diffuse.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 screen_normal;
		screen_normal.x = dot(IN.texcoord_2,normal);
		screen_normal.y = dot(IN.texcoord_3,normal);
		screen_normal.z = dot(IN.texcoord_4,normal);
		screen_normal = normalize(screen_normal);
		OUT.color_2 = setDeferredNormal(screen_normal,specular_power);
	#elif USE_PARALLAX
		OUT.color_2 = 0.0f;
	#endif
	
	#ifdef USE_PARALLAX
		OUT.color_3 = 0.0f;
	#endif
	
	return OUT;
}

#endif
