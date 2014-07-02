/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_stereo_replicate.shader
 * Desc:    Post stereo replicate shader
 * Version: 1.01
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
	
	half4 color = texture2D(s_texture_0,gl_TexCoord[0].xy);
	
	gl_FragData[0] = color;
	gl_FragData[1] = color;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
};

struct FRAGMENT_OUT {
	half4 color_0 : COLOR0;
	half4 color_1 : COLOR1;
};

/*
 */
FRAGMENT_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_OUT OUT;
	
	half4 color = tex2D(s_texture_0,IN.texcoord_0);
	
	OUT.color_0 = color;
	OUT.color_1 = color;
	
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
	float2 texcoord_0 : TEXCOORD0;
};

struct FRAGMENT_OUT {
	float3 color_0 : SV_TARGET0;
	float3 color_1 : SV_TARGET1;
};

/*
 */
FRAGMENT_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_OUT OUT;
	
	float3 color = s_texture_0.Sample(s_sampler_0,IN.texcoord_0).xyz;
	
	OUT.color_0 = color;
	OUT.color_1 = color;
	
	return OUT;
}

#endif
