/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_filter_sobel.shader
 * Desc:    Post filter sobel shader
 * Version: 1.03
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

uniform half threshold;
uniform half scale;

/*
 */
void main() {
	
	half3 c11 = texture2D(s_texture_0,gl_TexCoord[0].xy).xyz;
	half3 c21 = texture2D(s_texture_0,gl_TexCoord[1].xy).xyz;
	half3 c01 = texture2D(s_texture_0,gl_TexCoord[1].zw).xyz;
	half3 c12 = texture2D(s_texture_0,gl_TexCoord[2].xy).xyz;
	half3 c10 = texture2D(s_texture_0,gl_TexCoord[2].zw).xyz;
	half3 c22 = texture2D(s_texture_0,gl_TexCoord[3].xy).xyz;
	half3 c00 = texture2D(s_texture_0,gl_TexCoord[3].zw).xyz;
	half3 c20 = texture2D(s_texture_0,gl_TexCoord[4].xy).xyz;
	half3 c02 = texture2D(s_texture_0,gl_TexCoord[4].zw).xyz;
	
	half3 sobel_x = c00 + c01 * 2.0f + c02 - c20 - c21 * 2.0f - c22;
	half3 sobel_y = c00 + c10 * 2.0f + c20 - c02 - c12 * 2.0f - c22;
	half3 sobel = sqrt(sobel_x * sobel_x + sobel_y * sobel_y);
	
	half edge = saturate(1.0f - dot(sobel,half3(threshold)));
	
	gl_FragColor = half4(saturate(c11 + scale) * edge,1.0f);
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
};

half threshold;
half scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 c11 = tex2D(s_texture_0,IN.texcoord_0.xy).xyz;
	half3 c21 = tex2D(s_texture_0,IN.texcoord_1.xy).xyz;
	half3 c01 = tex2D(s_texture_0,IN.texcoord_1.zw).xyz;
	half3 c12 = tex2D(s_texture_0,IN.texcoord_2.xy).xyz;
	half3 c10 = tex2D(s_texture_0,IN.texcoord_2.zw).xyz;
	half3 c22 = tex2D(s_texture_0,IN.texcoord_3.xy).xyz;
	half3 c00 = tex2D(s_texture_0,IN.texcoord_3.zw).xyz;
	half3 c20 = tex2D(s_texture_0,IN.texcoord_4.xy).xyz;
	half3 c02 = tex2D(s_texture_0,IN.texcoord_4.zw).xyz;
	
	half3 sobel_x = c00 + c01 * 2.0f + c02 - c20 - c21 * 2.0f - c22;
	half3 sobel_y = c00 + c10 * 2.0f + c20 - c02 - c12 * 2.0f - c22;
	half3 sobel = sqrt(sobel_x * sobel_x + sobel_y * sobel_y);
	
	half edge = saturate(1.0f - dot(sobel,threshold));
	
	return half4(saturate(c11 + scale) * edge,1.0f);
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
};

float threshold;
float scale;

/*
 */
float3 main(FRAGMENT_IN IN) : SV_TARGET {
	
	float3 c11 = s_texture_0.Sample(s_sampler_0,IN.texcoord_0.xy).xyz;
	float3 c21 = s_texture_0.Sample(s_sampler_0,IN.texcoord_1.xy).xyz;
	float3 c01 = s_texture_0.Sample(s_sampler_0,IN.texcoord_1.zw).xyz;
	float3 c12 = s_texture_0.Sample(s_sampler_0,IN.texcoord_2.xy).xyz;
	float3 c10 = s_texture_0.Sample(s_sampler_0,IN.texcoord_2.zw).xyz;
	float3 c22 = s_texture_0.Sample(s_sampler_0,IN.texcoord_3.xy).xyz;
	float3 c00 = s_texture_0.Sample(s_sampler_0,IN.texcoord_3.zw).xyz;
	float3 c20 = s_texture_0.Sample(s_sampler_0,IN.texcoord_4.xy).xyz;
	float3 c02 = s_texture_0.Sample(s_sampler_0,IN.texcoord_4.zw).xyz;
	
	float3 sobel_x = c00 + c01 * 2.0f + c02 - c20 - c21 * 2.0f - c22;
	float3 sobel_y = c00 + c10 * 2.0f + c20 - c02 - c12 * 2.0f - c22;
	float3 sobel = sqrt(sobel_x * sobel_x + sobel_y * sobel_y);
	
	float edge = saturate(1.0f - dot(sobel,threshold));
	
	return saturate(c11 + scale) * edge;
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
};

uniform half threshold;
uniform half scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 c11 = h3tex2D(s_texture_0,IN.texcoord_0.xy);
	half3 c21 = h3tex2D(s_texture_0,IN.texcoord_1.xy);
	half3 c01 = h3tex2D(s_texture_0,IN.texcoord_1.zw);
	half3 c12 = h3tex2D(s_texture_0,IN.texcoord_2.xy);
	half3 c10 = h3tex2D(s_texture_0,IN.texcoord_2.zw);
	half3 c22 = h3tex2D(s_texture_0,IN.texcoord_3.xy);
	half3 c00 = h3tex2D(s_texture_0,IN.texcoord_3.zw);
	half3 c20 = h3tex2D(s_texture_0,IN.texcoord_4.xy);
	half3 c02 = h3tex2D(s_texture_0,IN.texcoord_4.zw);
	
	half3 sobel_x = c00 + c01 * 2.0f + c02 - c20 - c21 * 2.0f - c22;
	half3 sobel_y = c00 + c10 * 2.0f + c20 - c02 - c12 * 2.0f - c22;
	half3 sobel = sqrt(sobel_x * sobel_x + sobel_y * sobel_y);
	
	half edge = saturate(1.0f - dot(sobel,threshold));
	
	return half4(saturate(c11 + scale) * edge,1.0f);
}

#endif
