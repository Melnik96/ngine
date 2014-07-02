/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_deferred.shader
 * Desc:    Gui base deferred shader
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

/* s_texture_0 is color texture
 * s_texture_1 is normal texture
 * 
 * s_texture_10 is alpha fade texture
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

uniform half glow_scale;
uniform half specular_power;
uniform half4 color_scale;

/*
 */
void main() {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texture2DAlphaFadeDiscard(s_texture_10,gl_TexCoord[7].z);
	#endif
	
	gl_FragData[0] = setDeferredDepth(length(gl_TexCoord[1].xyz),0.0f);
	
	half4 color = texture2DAlphaDiscard(s_texture_0,gl_TexCoord[0].zw,1.0f);
	
	#ifdef YUV
		half2 uv = color.yz - 0.5f;
		color.xyz = saturate(half3(1.40200f * uv.y,-0.71414f * uv.y - 0.34414f * uv.x,1.77200f * uv.x) + color.x);
	#endif
	
	gl_FragData[1] = setDeferredColor(color.xyz * color_scale.xyz,glow_scale);
	
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
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_1),0.0f);
	
	half4 color = tex2DAlphaDiscard(s_texture_0,IN.texcoord_0.xy,1.0f);
	
	#ifdef YUV
		half2 uv = color.yz - 0.5f;
		color.xyz = saturate(half3(1.40200f * uv.y,-0.71414f * uv.y - 0.34414f * uv.x,1.77200f * uv.x) + color.x);
	#endif
	
	OUT.color_1 = setDeferredColor(color.xyz * color_scale.xyz,glow_scale);
	
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
	float glow_scale;
	float specular_power;
	float4 color_scale;
};

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texture2DAlphaFadeDiscard(s_texture_10,s_sampler_10,IN.position.xy,IN.texcoord_9.x);
	#endif
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_1),0.0f);
	
	FRAGMENT_ALPHA_OUT ALPHA_OUT;
	ALPHA_OUT = texture2DAlphaDiscard(s_texture_0,s_sampler_0,IN.texcoord_0.xy,1.0f);
	#ifdef ALPHA && !MULTISAMPLE_0 && USE_ALPHA_TEST_LEVEL_10_1
		OUT.coverage = ALPHA_OUT.coverage;
	#endif
	
	half4 color = ALPHA_OUT.color;
	
	#ifdef YUV
		half2 uv = color.yz - 0.5f;
		color.xyz = saturate(half3(1.40200f * uv.y,-0.71414f * uv.y - 0.34414f * uv.x,1.77200f * uv.x) + color.x);
	#endif
	
	OUT.color_1 = setDeferredColor(color.xyz * color_scale.xyz,glow_scale);
	
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
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_1),0.0f);
	
	half4 color = tex2DAlphaDiscard(s_texture_0,IN.texcoord_0.xy,1.0f);
	
	#ifdef YUV
		half2 uv = color.yz - 0.5f;
		color.xyz = saturate(half3(1.40200f * uv.y,-0.71414f * uv.y - 0.34414f * uv.x,1.77200f * uv.x) + color.x);
	#endif
	
	OUT.color_1 = setDeferredColor(color.xyz * color_scale.xyz,glow_scale);
	
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
