/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_hdr_lens.shader
 * Desc:    Render hdr lens flare shader
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

/* s_texture_0 is sample texture
 * s_texture_1 is vignette texture
 * s_texture_2 is color gradient texture
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

uniform half4 color;
uniform half threshold;

/*
 */
void main() {
	
	half3 lens = half3(0.0f);
	
	#define SAMPLE(POSITION,STEP,NUMBER,TEXCOORD) { \
		float position = POSITION; \
		for(int i = 0; i < NUMBER; i++) { \
			float2 texcoord = gl_TexCoord[0].xy * (1.0f / position) + 0.5f; \
			half4 sample = texture2D(s_texture_0,texcoord); \
			half4 color = texture2D(s_texture_2,float2(TEXCOORD,0.5f)); \
			lens += sample.xyz * color.xyz * (texture2D(s_texture_1,texcoord).x * saturate(sample.w - threshold)); \
			position += STEP; \
		} \
	}
	
	SAMPLE(-0.2f,-0.006f,3,0.05f);
	SAMPLE( 0.2f, 0.006f,3,0.15f);
	SAMPLE( 0.3f, 0.008f,4,0.19f);
	SAMPLE( 0.7f, 0.020f,4,0.35f);
	SAMPLE( 1.1f, 0.040f,5,0.50f);
	SAMPLE( 1.3f, 0.040f,5,0.57f);
	SAMPLE( 2.0f, 0.040f,5,0.85f);
	SAMPLE( 2.4f, 0.040f,5,1.00f);
	
	gl_FragColor = half4(lens * color.xyz,1.0f);
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

half4 color;
half threshold;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 lens = 0.0f;
	
	#define SAMPLE(POSITION,STEP,NUMBER,TEXCOORD) { \
		float position = POSITION; \
		[unroll] for(int i = 0; i < NUMBER; i++) { \
			float2 texcoord = IN.texcoord_0 * (1.0f / position) + 0.5f; \
			half4 sample = tex2D(s_texture_0,texcoord); \
			half4 color = tex2D(s_texture_2,float2(TEXCOORD,0.5f)); \
			lens += sample.xyz * color.xyz * (tex2D(s_texture_1,texcoord).x * saturate(sample.w - threshold)); \
			position += STEP; \
		} \
	}
	
	SAMPLE(-0.2f,-0.006f,3,0.05f);
	SAMPLE( 0.2f, 0.006f,3,0.15f);
	SAMPLE( 0.3f, 0.008f,4,0.19f);
	SAMPLE( 0.7f, 0.020f,4,0.35f);
	SAMPLE( 1.1f, 0.040f,5,0.50f);
	SAMPLE( 1.3f, 0.040f,5,0.57f);
	SAMPLE( 2.0f, 0.040f,5,0.85f);
	SAMPLE( 2.4f, 0.040f,5,1.00f);
	
	return half4(lens * color.xyz,1.0f);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
Texture2D s_texture_1 : register(t1);
Texture2D s_texture_2 : register(t2);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
};

float4 color;
float threshold;

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half3 lens = 0.0f;
	
	#define SAMPLE(POSITION,STEP,NUMBER,TEXCOORD) { \
		float position = POSITION; \
		[unroll] for(int i = 0; i < NUMBER; i++) { \
			float2 texcoord = IN.texcoord_0 * (1.0f / position) + 0.5f; \
			half4 sample = s_texture_0.Sample(s_sampler_0,texcoord); \
			half4 color = s_texture_2.Sample(s_sampler_2,float2(TEXCOORD,0.5f)); \
			lens += sample.xyz * color.xyz * (s_texture_1.Sample(s_sampler_1,texcoord).x * saturate(sample.w - threshold)); \
			position += STEP; \
		} \
	}
	
	SAMPLE(-0.2f,-0.006f,3,0.05f);
	SAMPLE( 0.2f, 0.006f,3,0.15f);
	SAMPLE( 0.3f, 0.008f,4,0.19f);
	SAMPLE( 0.7f, 0.020f,4,0.35f);
	SAMPLE( 1.1f, 0.040f,5,0.50f);
	SAMPLE( 1.3f, 0.040f,5,0.57f);
	SAMPLE( 2.0f, 0.040f,5,0.85f);
	SAMPLE( 2.4f, 0.040f,5,1.00f);
	
	return float4(lens * color.xyz,1.0f);
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

uniform half4 color;
uniform half threshold;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 lens = 0.0f;
	
	#define SAMPLE(POSITION,STEP,NUMBER,TEXCOORD) { \
		float position = POSITION; \
		for(int i = 0; i < NUMBER; i++) { \
			float2 texcoord = IN.texcoord_0 * (1.0f / position) + 0.5f; \
			half4 sample = h4tex2D(s_texture_0,texcoord); \
			half4 color = h4tex2D(s_texture_2,float2(TEXCOORD,0.5f)); \
			lens += sample.xyz * color.xyz * (h1tex2D(s_texture_1,texcoord) * saturate(sample.w - threshold)); \
			position += STEP; \
		} \
	}
	
	SAMPLE(-0.2f,-0.006f,3,0.05f);
	SAMPLE( 0.2f, 0.006f,3,0.15f);
	SAMPLE( 0.3f, 0.008f,4,0.19f);
	SAMPLE( 0.7f, 0.020f,4,0.35f);
	SAMPLE( 1.1f, 0.040f,5,0.50f);
	SAMPLE( 1.3f, 0.040f,5,0.57f);
	SAMPLE( 2.0f, 0.040f,5,0.85f);
	SAMPLE( 2.4f, 0.040f,5,1.00f);
	
	return half4(lens * color.xyz,1.0f);
}

#endif
