/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_blur_2d.shader
 * Desc:    Post blur 2d shader
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
	
	half3 color = texture2D(s_texture_0,gl_TexCoord[0].xy).xyz * 0.142300f +
		texture2D(s_texture_0,gl_TexCoord[1].xy).xyz * 0.134610f + texture2D(s_texture_0,gl_TexCoord[1].zw).xyz * 0.134610f +
		texture2D(s_texture_0,gl_TexCoord[2].xy).xyz * 0.113945f + texture2D(s_texture_0,gl_TexCoord[2].zw).xyz * 0.113945f +
		texture2D(s_texture_0,gl_TexCoord[3].xy).xyz * 0.086310f + texture2D(s_texture_0,gl_TexCoord[3].zw).xyz * 0.086310f +
		texture2D(s_texture_0,gl_TexCoord[4].xy).xyz * 0.058501f + texture2D(s_texture_0,gl_TexCoord[4].zw).xyz * 0.058501f +
		texture2D(s_texture_0,gl_TexCoord[5].xy).xyz * 0.035483f + texture2D(s_texture_0,gl_TexCoord[5].zw).xyz * 0.035483f;
	
	gl_FragColor = half4(color,1.0f);
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
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	float4 texcoord_4 : TEXCOORD4;
	float4 texcoord_5 : TEXCOORD5;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 color = tex2D(s_texture_0,IN.texcoord_0.xy).xyz * 0.142300f +
		tex2D(s_texture_0,IN.texcoord_1.xy).xyz * 0.134610f + tex2D(s_texture_0,IN.texcoord_1.zw).xyz * 0.134610f +
		tex2D(s_texture_0,IN.texcoord_2.xy).xyz * 0.113945f + tex2D(s_texture_0,IN.texcoord_2.zw).xyz * 0.113945f +
		tex2D(s_texture_0,IN.texcoord_3.xy).xyz * 0.086310f + tex2D(s_texture_0,IN.texcoord_3.zw).xyz * 0.086310f +
		tex2D(s_texture_0,IN.texcoord_4.xy).xyz * 0.058501f + tex2D(s_texture_0,IN.texcoord_4.zw).xyz * 0.058501f +
		tex2D(s_texture_0,IN.texcoord_5.xy).xyz * 0.035483f + tex2D(s_texture_0,IN.texcoord_5.zw).xyz * 0.035483f;
	
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
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	float4 texcoord_4 : TEXCOORD4;
	float4 texcoord_5 : TEXCOORD5;
};

/*
 */
float3 main(FRAGMENT_IN IN) : SV_TARGET {
	
	float3 color = s_texture_0.Sample(s_sampler_0,IN.texcoord_0.xy).xyz * 0.142300f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_1.xy).xyz * 0.134610f + s_texture_0.Sample(s_sampler_0,IN.texcoord_1.zw).xyz * 0.134610f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_2.xy).xyz * 0.113945f + s_texture_0.Sample(s_sampler_0,IN.texcoord_2.zw).xyz * 0.113945f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_3.xy).xyz * 0.086310f + s_texture_0.Sample(s_sampler_0,IN.texcoord_3.zw).xyz * 0.086310f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_4.xy).xyz * 0.058501f + s_texture_0.Sample(s_sampler_0,IN.texcoord_4.zw).xyz * 0.058501f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_5.xy).xyz * 0.035483f + s_texture_0.Sample(s_sampler_0,IN.texcoord_5.zw).xyz * 0.035483f;
	
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
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	float4 texcoord_4 : TEXCOORD4;
	float4 texcoord_5 : TEXCOORD5;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 color = h4tex2D(s_texture_0,IN.texcoord_0.xy) * 0.142300f +
		h4tex2D(s_texture_0,IN.texcoord_1.xy) * 0.134610f + h4tex2D(s_texture_0,IN.texcoord_1.zw) * 0.134610f +
		h4tex2D(s_texture_0,IN.texcoord_2.xy) * 0.113945f + h4tex2D(s_texture_0,IN.texcoord_2.zw) * 0.113945f +
		h4tex2D(s_texture_0,IN.texcoord_3.xy) * 0.086310f + h4tex2D(s_texture_0,IN.texcoord_3.zw) * 0.086310f +
		h4tex2D(s_texture_0,IN.texcoord_4.xy) * 0.058501f + h4tex2D(s_texture_0,IN.texcoord_4.zw) * 0.058501f +
		h4tex2D(s_texture_0,IN.texcoord_5.xy) * 0.035483f + h4tex2D(s_texture_0,IN.texcoord_5.zw) * 0.035483f;
	
	return color;
}

#endif
