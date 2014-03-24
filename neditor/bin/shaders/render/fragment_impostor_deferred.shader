/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_impostor_deferred.shader
 * Desc:    Render impostor deferred shader
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

/* s_texture_0 is impostor texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;

/*
 */
void main() {
	
	half4 impostor = texture2D(s_texture_0,gl_TexCoord[0].xy);
	if(impostor.w <= 0.5f) discard;
	
	gl_FragData[0] = setDeferredDepth(length(gl_TexCoord[1].xyz),0.0f);
	
	gl_FragData[1] = setDeferredColor(impostor.xyz,0.0f);
	
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
	float2 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
};

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	half4 impostor = tex2D(s_texture_0,IN.texcoord_0);
	if(impostor.w <= 0.5f) discard;
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_1),0.0f);
	
	OUT.color_1 = setDeferredColor(impostor.xyz,0.0f);
	
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

Texture2D s_texture_0 : register(t0);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
};

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	half4 impostor = s_texture_0.Sample(s_sampler_0,IN.texcoord_0);
	if(impostor.w <= 0.5f) discard;
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_1),0.0f);
	
	OUT.color_1 = setDeferredColor(impostor.xyz,0.0f);
	
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

uniform sampler2D s_texture_0 : TEXUNIT0;

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
};

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	half4 impostor = tex2D(s_texture_0,IN.texcoord_0);
	if(impostor.w <= 0.5f) discard;
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_1),0.0f);
	
	OUT.color_1 = setDeferredColor(impostor.xyz,0.0f);
	
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
