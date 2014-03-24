/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_blur_cube.shader
 * Desc:    Post blur cube shader
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

uniform samplerCube s_texture_0;

/*
 */
void main() {
	
	half3 color = textureCube(s_texture_0,gl_TexCoord[0].xyz).xyz * 0.142300f +
		textureCube(s_texture_0,half3(gl_TexCoord[0].xyz) + half3(gl_TexCoord[1].xyz)).xyz * 0.134610f + textureCube(s_texture_0,half3(gl_TexCoord[0].xyz) - half3(gl_TexCoord[1].xyz)).xyz * 0.134610f +
		textureCube(s_texture_0,half3(gl_TexCoord[0].xyz) + half3(gl_TexCoord[2].xyz)).xyz * 0.113945f + textureCube(s_texture_0,half3(gl_TexCoord[0].xyz) - half3(gl_TexCoord[2].xyz)).xyz * 0.113945f +
		textureCube(s_texture_0,half3(gl_TexCoord[0].xyz) + half3(gl_TexCoord[3].xyz)).xyz * 0.086310f + textureCube(s_texture_0,half3(gl_TexCoord[0].xyz) - half3(gl_TexCoord[3].xyz)).xyz * 0.086310f +
		textureCube(s_texture_0,half3(gl_TexCoord[0].xyz) + half3(gl_TexCoord[4].xyz)).xyz * 0.058501f + textureCube(s_texture_0,half3(gl_TexCoord[0].xyz) - half3(gl_TexCoord[4].xyz)).xyz * 0.058501f +
		textureCube(s_texture_0,half3(gl_TexCoord[0].xyz) + half3(gl_TexCoord[5].xyz)).xyz * 0.035483f + textureCube(s_texture_0,half3(gl_TexCoord[0].xyz) - half3(gl_TexCoord[5].xyz)).xyz * 0.035483f;
	
	gl_FragColor = half4(color,1.0f);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	half3 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	half3 texcoord_5 : TEXCOORD5;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 color = texCUBE(s_texture_0,IN.texcoord_0).xyz * 0.142300f +
		texCUBE(s_texture_0,IN.texcoord_0 + IN.texcoord_1).xyz * 0.134610f + texCUBE(s_texture_0,IN.texcoord_0 - IN.texcoord_1).xyz * 0.134610f +
		texCUBE(s_texture_0,IN.texcoord_0 + IN.texcoord_2).xyz * 0.113945f + texCUBE(s_texture_0,IN.texcoord_0 - IN.texcoord_2).xyz * 0.113945f +
		texCUBE(s_texture_0,IN.texcoord_0 + IN.texcoord_3).xyz * 0.086310f + texCUBE(s_texture_0,IN.texcoord_0 - IN.texcoord_3).xyz * 0.086310f +
		texCUBE(s_texture_0,IN.texcoord_0 + IN.texcoord_4).xyz * 0.058501f + texCUBE(s_texture_0,IN.texcoord_0 - IN.texcoord_4).xyz * 0.058501f +
		texCUBE(s_texture_0,IN.texcoord_0 + IN.texcoord_5).xyz * 0.035483f + texCUBE(s_texture_0,IN.texcoord_0 - IN.texcoord_5).xyz * 0.035483f;
	
	return half4(color,1.0f);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

TextureCube s_texture_0 : register(t0);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float3 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	float3 texcoord_5 : TEXCOORD5;
};

/*
 */
float3 main(FRAGMENT_IN IN) : SV_TARGET {
	
	float3 color = s_texture_0.Sample(s_sampler_0,IN.texcoord_0).xyz * 0.142300f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_0 + IN.texcoord_1).xyz * 0.134610f + s_texture_0.Sample(s_sampler_0,IN.texcoord_0 - IN.texcoord_1).xyz * 0.134610f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_0 + IN.texcoord_2).xyz * 0.113945f + s_texture_0.Sample(s_sampler_0,IN.texcoord_0 - IN.texcoord_2).xyz * 0.113945f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_0 + IN.texcoord_3).xyz * 0.086310f + s_texture_0.Sample(s_sampler_0,IN.texcoord_0 - IN.texcoord_3).xyz * 0.086310f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_0 + IN.texcoord_4).xyz * 0.058501f + s_texture_0.Sample(s_sampler_0,IN.texcoord_0 - IN.texcoord_4).xyz * 0.058501f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_0 + IN.texcoord_5).xyz * 0.035483f + s_texture_0.Sample(s_sampler_0,IN.texcoord_0 - IN.texcoord_5).xyz * 0.035483f;
	
	return color;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

##pragma disablepc all

uniform samplerCUBE s_texture_0 : TEXUNIT0;

struct FRAGMENT_IN {
	half3 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	half3 texcoord_5 : TEXCOORD5;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 color = h4texCUBE(s_texture_0,IN.texcoord_0) * 0.142300f +
		h4texCUBE(s_texture_0,IN.texcoord_0 + IN.texcoord_1) * 0.134610f + h4texCUBE(s_texture_0,IN.texcoord_0 - IN.texcoord_1) * 0.134610f +
		h4texCUBE(s_texture_0,IN.texcoord_0 + IN.texcoord_2) * 0.113945f + h4texCUBE(s_texture_0,IN.texcoord_0 - IN.texcoord_2) * 0.113945f +
		h4texCUBE(s_texture_0,IN.texcoord_0 + IN.texcoord_3) * 0.086310f + h4texCUBE(s_texture_0,IN.texcoord_0 - IN.texcoord_3) * 0.086310f +
		h4texCUBE(s_texture_0,IN.texcoord_0 + IN.texcoord_4) * 0.058501f + h4texCUBE(s_texture_0,IN.texcoord_0 - IN.texcoord_4) * 0.058501f +
		h4texCUBE(s_texture_0,IN.texcoord_0 + IN.texcoord_5) * 0.035483f + h4texCUBE(s_texture_0,IN.texcoord_0 - IN.texcoord_5) * 0.035483f;
	
	return color;
}

#endif
