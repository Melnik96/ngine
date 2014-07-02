/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_hdr_bright.shader
 * Desc:    Render hdr bright shader
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

/* s_texture_0 is sample texture
 * s_texture_1 is luminance texture
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

uniform half threshold;

/*
 */
void main() {
	
	half3 color = texture2D(s_texture_0,gl_TexCoord[0].xy).xyz;
	
	half luminance = texture2D(s_texture_1,float2(0.5f,0.5f)).x;
	
	color *= luminance;
	
	half value = max(max(color.x,color.y),color.z);
	color *= saturate(value - threshold);
	
	gl_FragColor = half4(color,max(max(color.x,color.y),color.z) * 4.0f);
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

half threshold;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 color = tex2D(s_texture_0,IN.texcoord_0).xyz;
	
	half luminance = tex2D(s_texture_1,float2(0.5f,0.5f)).x;
	
	color *= luminance;
	
	half value = max(max(color.x,color.y),color.z);
	color *= saturate(value - threshold);
	
	return half4(color,max(max(color.x,color.y),color.z) * 4.0f);
}

/******************************************************************************\
*
* Direct3D1
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
Texture2D s_texture_1 : register(t1);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
};

float threshold;

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	float3 color = s_texture_0.Sample(s_sampler_0,IN.texcoord_0).xyz;
	
	float luminance = s_texture_1.Sample(s_sampler_1,float2(0.5f,0.5f)).x;
	
	color *= luminance;
	
	float value = max(max(color.x,color.y),color.z);
	color *= saturate(value - threshold);
	
	return float4(color,max(max(color.x,color.y),color.z) * 4.0f);
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

##pragma disablepc all

uniform sampler2D s_texture_0 : TEXUNIT0;
uniform sampler2D s_texture_1 : TEXUNIT1;
uniform sampler2D s_texture_2 : TEXUNIT2;

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
};

uniform half threshold;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 color = h3tex2D(s_texture_0,IN.texcoord_0);
	
	half luminance = h1tex2D(s_texture_1,float2(0.5f,0.5f));
	
	color *= luminance;
	
	half value = max(max(color.x,color.y),color.z);
	color *= saturate(value - threshold);
	
	return half4(color,max(max(color.x,color.y),color.z) * 4.0f);
}

#endif
