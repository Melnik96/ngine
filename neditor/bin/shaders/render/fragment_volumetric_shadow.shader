/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_volumetric_shadow.shader
 * Desc:    Render volumetric shadow shader
 * Version: 1.05
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
 * s_texture_1 is noise texture
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

uniform half exposure;

/*
 */
void main() {
	
	float2 texcoord = gl_TexCoord[0].xy;
	float2 direction = gl_TexCoord[1].xy;
	
	half weight = 0.95f;
	half2 sample = texture2D(s_texture_0,texcoord).xy;
	half depth = sample.x + 0.01f;
	half shadow = sample.y;
	
	texcoord += direction * texture2D(s_texture_1,gl_TexCoord[2].xy).x;
	
	for(int i = 1; i < 32; i++) {
		sample = texture2D(s_texture_0,texcoord).xy;
		shadow += saturate(half(sample.x > depth) + sample.y) * weight;
		texcoord += direction;
		weight *= 0.95f;
	}
	
	// 16.1258f = (1.0f - pow(0.95f,32.0f)) / (1.0f - 0.95f)
	gl_FragColor = half4(1.0f - exposure + shadow * exposure * (1.0f / 16.1258f));
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
	float2 texcoord_2 : TEXCOORD2;
};

half exposure;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	float2 texcoord = IN.texcoord_0;
	float2 direction = IN.texcoord_1;
	
	half weight = 0.95f;
	half2 sample = tex2D(s_texture_0,texcoord).xy;
	half depth = sample.x + 0.01f;
	half shadow = sample.y;
	
	texcoord += direction * tex2D(s_texture_1,IN.texcoord_2).x;
	
	[unroll] for(int i = 1; i < 32; i++) {
		sample = tex2D(s_texture_0,texcoord).xy;
		shadow += saturate((sample.x > depth) + sample.y) * weight;
		texcoord += direction;
		weight *= 0.95f;
	}
	
	return 1.0f - exposure + shadow * exposure * (1.0f / 16.1258f);
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
	float2 texcoord_1 : TEXCOORD1;
	float2 texcoord_2 : TEXCOORD2;
};

float exposure;

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	float2 texcoord = IN.texcoord_0;
	float2 direction = IN.texcoord_1;
	
	half weight = 0.95f;
	half2 sample = s_texture_0.Sample(s_sampler_0,texcoord).xy;
	half depth = sample.x + 0.01f;
	half shadow = sample.y;
	
	texcoord += direction * s_texture_1.Sample(s_sampler_1,IN.texcoord_2).x;
	
	[unroll] for(int i = 1; i < 32; i++) {
		sample = s_texture_0.Sample(s_sampler_0,texcoord).xy;
		shadow += saturate((sample.x > depth) + sample.y) * weight;
		texcoord += direction;
		weight *= 0.95f;
	}
	
	return 1.0f - exposure + shadow * exposure * (1.0f / 16.1258f);
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

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
	float2 texcoord_2 : TEXCOORD2;
};

uniform half exposure;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	float2 texcoord = IN.texcoord_0;
	float2 direction = IN.texcoord_1;
	
	half weight = 0.95f;
	half2 sample = h2tex2D(s_texture_0,texcoord);
	half depth = sample.x + 0.01f;
	half shadow = sample.y;
	
	texcoord += direction * h1tex2D(s_texture_1,IN.texcoord_2);
	
	for(int i = 1; i < 32; i++) {
		sample = h2tex2D(s_texture_0,texcoord);
		shadow += saturate((sample.x > depth) + sample.y) * weight;
		texcoord += direction;
		weight *= 0.95f;
	}
	
	return 1.0f - exposure + shadow * exposure * (1.0f / 16.1258f);
}

#endif
