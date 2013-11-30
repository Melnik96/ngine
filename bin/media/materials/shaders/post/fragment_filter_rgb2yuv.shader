/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_filter_rgb2yuv.shader
 * Desc:    Post filter rgb2yuv shader
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
	
	half3 color = texture2D(s_texture_0,gl_TexCoord[0].xy).xyz;
	
	half3 y = half3( 0.2990f, 0.5870f, 0.1140f);
	half3 u = half3(-0.1687f,-0.3313f, 0.5000f);
	half3 v = half3( 0.5000f,-0.4187f,-0.0813f);
	
	color = saturate(half3(dot(color,y),dot(color,u) + 0.5f,dot(color,v) + 0.5f));
	
	gl_FragColor = half4(color,1.0f);
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

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 color = tex2D(s_texture_0,IN.texcoord_0).xyz;
	
	half3 y = half3( 0.2990f, 0.5870f, 0.1140f);
	half3 u = half3(-0.1687f,-0.3313f, 0.5000f);
	half3 v = half3( 0.5000f,-0.4187f,-0.0813f);
	
	color = saturate(half3(dot(color,y),dot(color,u) + 0.5f,dot(color,v) + 0.5f));
	
	return half4(color,1.0f);
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
};

/*
 */
float3 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half3 color = s_texture_0.Sample(s_sampler_0,IN.texcoord_0).xyz;
	
	half3 y = half3( 0.2990f, 0.5870f, 0.1140f);
	half3 u = half3(-0.1687f,-0.3313f, 0.5000f);
	half3 v = half3( 0.5000f,-0.4187f,-0.0813f);
	
	color = saturate(half3(dot(color,y),dot(color,u) + 0.5f,dot(color,v) + 0.5f));
	
	return color;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

##pragma disablepc all

uniform sampler2D s_texture_0 : TEXUNIT0;

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 color = h3tex2D(s_texture_0,IN.texcoord_0);
	
	half3 y = half3( 0.2990f, 0.5870f, 0.1140f);
	half3 u = half3(-0.1687f,-0.3313f, 0.5000f);
	half3 v = half3( 0.5000f,-0.4187f,-0.0813f);
	
	color = saturate(half3(dot(color,y),dot(color,u) + 0.5f,dot(color,v) + 0.5f));
	
	return half4(color,1.0f);
}

#endif
