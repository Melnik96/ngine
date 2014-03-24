/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_deferred.shader
 * Desc:    Particles base deferred shader
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

/* s_texture_0 is diffuse texture
 * s_texture_1 is attenuation texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

#ifdef ANIMATION
	uniform sampler3D s_texture_0;
#else
	uniform sampler2D s_texture_0;
#endif
uniform sampler2D s_texture_1;

uniform half animation_scale;
uniform half deferred_threshold;
uniform half glow_scale;

/*
 */
void main() {
	
	#include <core/shaders/particles/fragment_base_sample.h>
	
	half threshold = dot(color.xyz,half3(gl_TexCoord[1].xyz)) - deferred_threshold;
	if(threshold <= 0.0f) discard;
	
	gl_FragData[0] = setDeferredDepth(length(gl_TexCoord[2].xyz),0.0f);
	
	gl_FragData[1] = setDeferredColor(color.xyz * half3(gl_TexCoord[1].xyz),threshold * glow_scale);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		gl_FragData[2] = setDeferredNormal(half3(0.0f,0.0f,1.0f),16.0f);
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
	half4 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
};

half animation_scale;
half deferred_threshold;
half glow_scale;

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#include <core/shaders/particles/fragment_base_sample.h>
	
	half threshold = dot(color.xyz,IN.texcoord_1.xyz) - deferred_threshold;
	if(threshold <= 0.0f) discard;
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_2),0.0f);
	
	OUT.color_1 = setDeferredColor(color.xyz * IN.texcoord_1.xyz,threshold * glow_scale);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		OUT.color_2 = setDeferredNormal(half3(0.0f,0.0f,1.0f),16.0f);
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

#ifdef ANIMATION
	Texture3D s_texture_0 : register(t0);
#else
	Texture2D s_texture_0 : register(t0);
#endif
Texture2D s_texture_1 : register(t1);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
};

cbuffer shader_parameters {
	float animation_scale;
	float deferred_threshold;
	float glow_scale;
};

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#include <core/shaders/particles/fragment_base_sample.h>
	
	half threshold = dot(color.xyz,IN.texcoord_1.xyz) - deferred_threshold;
	if(threshold <= 0.0f) discard;
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_2),0.0f);
	
	OUT.color_1 = setDeferredColor(color.xyz * IN.texcoord_1.xyz,threshold * glow_scale);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		OUT.color_2 = setDeferredNormal(half3(0.0f,0.0f,1.0f),16.0f);
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

#ifdef ANIMATION
	uniform sampler3D s_texture_0 : TEXUNIT0;
#else
	uniform sampler2D s_texture_0 : TEXUNIT0;
#endif
uniform sampler2D s_texture_1 : TEXUNIT1;

struct FRAGMENT_IN {
	half4 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
};

uniform half animation_scale;
uniform half deferred_threshold;
uniform half glow_scale;

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#include <core/shaders/particles/fragment_base_sample.h>
	
	half threshold = dot(color.xyz,IN.texcoord_1.xyz) - deferred_threshold;
	if(threshold <= 0.0f) discard;
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_2),0.0f);
	
	OUT.color_1 = setDeferredColor(color.xyz * IN.texcoord_1.xyz,threshold * glow_scale);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		OUT.color_2 = setDeferredNormal(half3(0.0f,0.0f,1.0f),16.0f);
	#elif USE_PARALLAX
		OUT.color_2 = 0.0f;
	#endif
	
	#ifdef USE_PARALLAX
		OUT.color_3 = 0.0f;
	#endif
	
	return OUT;
}

#endif
