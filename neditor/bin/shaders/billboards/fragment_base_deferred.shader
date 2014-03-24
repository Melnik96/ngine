/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_deferred.shader
 * Desc:    Billboard base deferred shader
 * Version: 1.06
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
 * 
 * s_texture_10 is alpha fade texture
 * s_texture_11 is emission texture
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

uniform sampler2D s_texture_10;
uniform sampler2D s_texture_11;

uniform half emission_scale;
uniform half glow_scale;
uniform half specular_power;
uniform half4 color_scale;

/*
 */
void main() {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texture2DAlphaFadeDiscard(s_texture_10,gl_TexCoord[7].z);
	#endif
	
	float distance = length(gl_TexCoord[1].xyz);
	
	#ifdef VOLUMETRIC
		gl_FragData[0] = setDeferredDepth(distance,1.0f);
	#else
		gl_FragData[0] = setDeferredDepth(distance,0.0f);
	#endif
	
	half4 diffuse = texture2DAlphaDiscard(s_texture_0,gl_TexCoord[0].xy,1.0f);
	
	#ifdef EMISSION
		half4 emission = texture2D(s_texture_11,gl_TexCoord[0].xy);
		diffuse.xyz += emission.xyz * emission_scale;
		gl_FragData[1] = setDeferredColor(diffuse.xyz * color_scale.xyz,emission.w * glow_scale);
	#else
		gl_FragData[1] = setDeferredColor(diffuse.xyz * color_scale.xyz,0.0f);
	#endif
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 screen_normal;
		half3 normal = texture2DNormal(s_texture_1,gl_TexCoord[0].xy);
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
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half emission_scale;
half glow_scale;
half specular_power;
half4 color_scale;

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_10,IN.texcoord_7,IN.texcoord_7.z);
	#endif
	
	float distance = length(IN.texcoord_1);
	
	#ifdef VOLUMETRIC
		OUT.color_0 = setDeferredDepth(distance,1.0f);
	#else
		OUT.color_0 = setDeferredDepth(distance,0.0f);
	#endif
	
	half4 diffuse = tex2DAlphaDiscard(s_texture_0,IN.texcoord_0.xy,1.0f);
	
	#ifdef EMISSION
		half4 emission = tex2D(s_texture_11,IN.texcoord_0.xy);
		diffuse.xyz += emission.xyz * emission_scale;
		OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,emission.w * glow_scale);
	#else
		OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,0.0f);
	#endif
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 screen_normal;
		half3 normal = tex2DNormal(s_texture_1,IN.texcoord_0.xy);
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

Texture2D s_texture_10 : register(t10);
Texture2D s_texture_11 : register(t11);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	#ifdef USE_DEFERRED || USE_OCCLUSION
		float3 texcoord_2 : TEXCOORD2;
		float3 texcoord_3 : TEXCOORD3;
		float3 texcoord_4 : TEXCOORD4;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

cbuffer shader_parameters {
	#ifdef EMISSION
		float emission_scale;
		float glow_scale;
	#endif
	#ifdef USE_DEFERRED || USE_OCCLUSION
		float specular_power;
	#endif
	float4 color_scale;
};

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texture2DAlphaFadeDiscard(s_texture_10,s_sampler_10,IN.position.xy,IN.texcoord_9.x);
	#endif
	
	float distance = length(IN.texcoord_1);
	
	#ifdef VOLUMETRIC
		OUT.color_0 = setDeferredDepth(distance,1.0f);
	#else
		OUT.color_0 = setDeferredDepth(distance,0.0f);
	#endif
	
	FRAGMENT_ALPHA_OUT ALPHA_OUT;
	ALPHA_OUT = texture2DAlphaDiscard(s_texture_0,s_sampler_0,IN.texcoord_0.xy,1.0f);
	#ifdef ALPHA && !MULTISAMPLE_0 && USE_ALPHA_TEST_LEVEL_10_1
		OUT.coverage = ALPHA_OUT.coverage;
	#endif
	
	half4 diffuse = ALPHA_OUT.color;
	
	#ifdef EMISSION
		half4 emission = s_texture_11.Sample(s_sampler_11,IN.texcoord_0.xy);
		diffuse.xyz += emission.xyz * emission_scale;
		OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,emission.w * glow_scale);
	#else
		OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,0.0f);
	#endif
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 screen_normal;
		half3 normal = texture2DNormal(s_texture_1,s_sampler_1,IN.texcoord_0.xy);
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

uniform sampler2D s_texture_10 : TEXUNIT10;
uniform sampler2D s_texture_11 : TEXUNIT11;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 texcoord_2 : TEXCOORD2;
		half3 texcoord_3 : TEXCOORD3;
		half3 texcoord_4 : TEXCOORD4;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half emission_scale;
uniform half glow_scale;
uniform half specular_power;
uniform half4 color_scale;

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_10,IN.texcoord_9,IN.texcoord_9.z);
	#endif
	
	float distance = length(IN.texcoord_1);
	
	#ifdef VOLUMETRIC
		OUT.color_0 = setDeferredDepth(distance,1.0f);
	#else
		OUT.color_0 = setDeferredDepth(distance,0.0f);
	#endif
	
	half4 diffuse = tex2DAlphaDiscard(s_texture_0,IN.texcoord_0.xy,1.0f);
	
	#ifdef EMISSION
		half4 emission = tex2D(s_texture_11,IN.texcoord_0.xy);
		diffuse.xyz += emission.xyz * emission_scale;
		OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,emission.w * glow_scale);
	#else
		OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,0.0f);
	#endif
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 screen_normal;
		half3 normal = tex2DNormal(s_texture_1,IN.texcoord_0.xy);
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
