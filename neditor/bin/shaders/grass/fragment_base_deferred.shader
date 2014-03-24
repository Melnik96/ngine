/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_deferred.shader
 * Desc:    Grass base deferred shader
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

uniform half noise_scale;

/*
 */
void main() {
	
	gl_FragData[0] = setDeferredDepth(gl_TexCoord[1].w,0.0f);
	
	half4 diffuse = texture2DAlphaDiscard(s_texture_0,gl_TexCoord[0].xy,gl_TexCoord[2].x);
	
	#ifdef NOISE
		half3 noise = texture2D(s_texture_1,gl_TexCoord[0].zw).xyz;
		diffuse.xyz = saturate(diffuse.xyz + (noise * 2.0f - 1.0f) * noise_scale);
	#endif
	
	gl_FragData[1] = setDeferredColor(diffuse.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		gl_FragData[2] = setDeferredNormal(gl_TexCoord[1].xyz,16.0f);
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
	float4 texcoord_1 : TEXCOORD1;
	half1 texcoord_2 : TEXCOORD2;
};

half noise_scale;

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	OUT.color_0 = setDeferredDepth(IN.texcoord_1.w,0.0f);
	
	half4 diffuse = tex2DAlphaDiscard(s_texture_0,IN.texcoord_0.xy,IN.texcoord_2.x);
	
	#ifdef NOISE
		half3 noise = tex2D(s_texture_1,IN.texcoord_0.zw).xyz;
		diffuse.xyz = saturate(diffuse.xyz + (noise * 2.0f - 1.0f) * noise_scale);
	#endif
	
	OUT.color_1 = setDeferredColor(diffuse.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		OUT.color_2 = setDeferredNormal(IN.texcoord_1.xyz,16.0f);
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

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float1 texcoord_2 : TEXCOORD2;
};

#ifdef NOISE
	cbuffer shader_parameters {
		float noise_scale;
	};
#endif

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	FRAGMENT_ALPHA_OUT ALPHA_OUT;
	
	OUT.color_0 = setDeferredDepth(IN.texcoord_1.w,0.0f);
	
	ALPHA_OUT = texture2DAlphaDiscard(s_texture_0,s_sampler_0,IN.texcoord_0.xy,IN.texcoord_2.x);
	#ifdef ALPHA && !MULTISAMPLE_0 && USE_ALPHA_TEST_LEVEL_10_1
		OUT.coverage = ALPHA_OUT.coverage;
	#endif
	
	half4 diffuse = ALPHA_OUT.color;
	
	#ifdef NOISE
		half3 noise = s_texture_1.Sample(s_sampler_1,IN.texcoord_0.zw).xyz;
		diffuse.xyz = saturate(diffuse.xyz + (noise * 2.0f - 1.0f) * noise_scale);
	#endif
	
	OUT.color_1 = setDeferredColor(diffuse.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		OUT.color_2 = setDeferredNormal(IN.texcoord_1.xyz,16.0f);
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

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	half1 texcoord_2 : TEXCOORD2;
};

uniform half noise_scale;

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	OUT.color_0 = setDeferredDepth(IN.texcoord_1.w,0.0f);
	
	half4 diffuse = tex2DAlphaDiscard(s_texture_0,IN.texcoord_0.xy,IN.texcoord_2.x);
	
	#ifdef NOISE
		half3 noise = h3tex2D(s_texture_1,IN.texcoord_0.zw);
		diffuse.xyz = saturate(diffuse.xyz + (noise * 2.0f - 1.0f) * noise_scale);
	#endif
	
	OUT.color_1 = setDeferredColor(diffuse.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		OUT.color_2 = setDeferredNormal(IN.texcoord_1.xyz,16.0f);
	#elif USE_PARALLAX
		OUT.color_2 = 0.0f;
	#endif
	
	#ifdef USE_PARALLAX
		OUT.color_3 = 0.0f;
	#endif
	
	return OUT;
}

#endif
