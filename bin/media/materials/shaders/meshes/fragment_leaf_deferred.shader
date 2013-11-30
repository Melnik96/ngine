/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_leaf_deferred.shader
 * Desc:    Mesh leaf deferred shader
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
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;

uniform half specular_power;
uniform half4 color_scale;

/*
 */
void main() {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		half4 diffuse = texture2DAlphaDiscard(s_texture_0,gl_TexCoord[0].xy,gl_TexCoord[7].x);
	#else
		half4 diffuse = texture2DAlphaDiscard(s_texture_0,gl_TexCoord[0].xy,1.0f);
	#endif
	
	#ifdef VOLUMETRIC
		gl_FragData[0] = setDeferredDepth(gl_TexCoord[1].w,1.0f);
	#else
		gl_FragData[0] = setDeferredDepth(gl_TexCoord[1].w,0.0f);
	#endif
	
	gl_FragData[1] = setDeferredColor(diffuse.xyz * color_scale.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		gl_FragData[2] = setDeferredNormal(gl_TexCoord[1].xyz,specular_power);
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
	float2 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_7 : TEXCOORD7;
	#endif
};

half specular_power;
half4 color_scale;

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		half4 diffuse = tex2DAlphaDiscard(s_texture_0,IN.texcoord_0,IN.texcoord_7.x);
	#else
		half4 diffuse = tex2DAlphaDiscard(s_texture_0,IN.texcoord_0,1.0f);
	#endif
	
	#ifdef VOLUMETRIC
		OUT.color_0 = setDeferredDepth(IN.texcoord_1.w,1.0f);
	#else
		OUT.color_0 = setDeferredDepth(IN.texcoord_1.w,0.0f);
	#endif
	
	OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		OUT.color_2 = setDeferredNormal(IN.texcoord_1.xyz,specular_power);
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

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

cbuffer shader_parameters {
	#ifdef USE_DEFERRED || USE_OCCLUSION
		float specular_power;
	#endif
	float4 color_scale;
};

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	FRAGMENT_ALPHA_OUT ALPHA_OUT;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		ALPHA_OUT = texture2DAlphaDiscard(s_texture_0,s_sampler_0,IN.texcoord_0,IN.texcoord_9.x);
	#else
		ALPHA_OUT = texture2DAlphaDiscard(s_texture_0,s_sampler_0,IN.texcoord_0,1.0f);
	#endif
	
	#ifdef ALPHA && !MULTISAMPLE_0 && USE_ALPHA_TEST_LEVEL_10_1
		OUT.coverage = ALPHA_OUT.coverage;
	#endif
	
	half4 diffuse = ALPHA_OUT.color;
	
	#ifdef VOLUMETRIC
		OUT.color_0 = setDeferredDepth(IN.texcoord_1.w,1.0f);
	#else
		OUT.color_0 = setDeferredDepth(IN.texcoord_1.w,0.0f);
	#endif
	
	OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		OUT.color_2 = setDeferredNormal(IN.texcoord_1.xyz,specular_power);
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

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half specular_power;
uniform half4 color_scale;

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		half4 diffuse = tex2DAlphaDiscard(s_texture_0,IN.texcoord_0,IN.texcoord_9.x);
	#else
		half4 diffuse = tex2DAlphaDiscard(s_texture_0,IN.texcoord_0,1.0f);
	#endif
	
	#ifdef VOLUMETRIC
		OUT.color_0 = setDeferredDepth(IN.texcoord_1.w,1.0f);
	#else
		OUT.color_0 = setDeferredDepth(IN.texcoord_1.w,0.0f);
	#endif
	
	OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		OUT.color_2 = setDeferredNormal(IN.texcoord_1.xyz,specular_power);
	#elif USE_PARALLAX
		OUT.color_2 = 0.0f;
	#endif
	
	#ifdef USE_PARALLAX
		OUT.color_3 = 0.0f;
	#endif
	
	return OUT;
}

#endif
