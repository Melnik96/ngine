/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_dof_blur.shader
 * Desc:    Render dof blur shader
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

/* s_texture_0 is dof texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;

uniform half blur_radius;

/*
 */
void main() {
	
	half4 color = texture2D(s_texture_0,gl_TexCoord[0].xy);
	
	#ifdef HBLUR
		half4 offset = half4(color.w * blur_radius,0.0f,-color.w * blur_radius,0.0f);
	#elif VBLUR
		half4 offset = half4(0.0f,color.w * blur_radius,0.0f,-color.w * blur_radius);
	#endif
	
	#define SAMPLE(OFFSET,WEIGHT) { \
		float4 texcoord = gl_TexCoord[0].xyxy + offset; \
		half4 sample_0 = texture2D(s_texture_0,texcoord.xy); \
		half4 sample_1 = texture2D(s_texture_0,texcoord.zw); \
		half weight_0 = sample_0.w * WEIGHT; \
		half weight_1 = sample_1.w * WEIGHT; \
		color.xyz += sample_0.xyz * weight_0; \
		color.xyz += sample_1.xyz * weight_1; \
		weight += weight_0; \
		weight += weight_1; \
	}
	
	half weight = 1.0f;
	
	SAMPLE(offset * 1.0f,0.960005f)
	SAMPLE(offset * 2.0f,0.849366f)
	SAMPLE(offset * 3.0f,0.692569f)
	SAMPLE(offset * 4.0f,0.520450f)
	SAMPLE(offset * 5.0f,0.360448f)
	
	color.xyz /= weight;
	
	gl_FragColor = color;
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

half blur_radius;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 color = tex2D(s_texture_0,IN.texcoord_0);
	
	#ifdef HBLUR
		half4 offset = half4(color.w * blur_radius,0.0f,-color.w * blur_radius,0.0f);
	#elif VBLUR
		half4 offset = half4(0.0f,color.w * blur_radius,0.0f,-color.w * blur_radius);
	#endif
	
	#define SAMPLE(OFFSET,WEIGHT) { \
		float4 texcoord = IN.texcoord_0.xyxy + offset; \
		half4 sample_0 = tex2D(s_texture_0,texcoord.xy); \
		half4 sample_1 = tex2D(s_texture_0,texcoord.zw); \
		half weight_0 = sample_0.w * WEIGHT; \
		half weight_1 = sample_1.w * WEIGHT; \
		color.xyz += sample_0.xyz * weight_0; \
		color.xyz += sample_1.xyz * weight_1; \
		weight += weight_0; \
		weight += weight_1; \
	}
	
	half weight = 1.0f;
	
	SAMPLE(offset * 1.0f,0.960005f)
	SAMPLE(offset * 2.0f,0.849366f)
	SAMPLE(offset * 3.0f,0.692569f)
	SAMPLE(offset * 4.0f,0.520450f)
	SAMPLE(offset * 5.0f,0.360448f)
	
	color.xyz /= weight;
	
	return color;
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

float blur_radius;

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 color = s_texture_0.Sample(s_sampler_0,IN.texcoord_0);
	
	#ifdef HBLUR
		half4 offset = half4(color.w * blur_radius,0.0f,-color.w * blur_radius,0.0f);
	#elif VBLUR
		half4 offset = half4(0.0f,color.w * blur_radius,0.0f,-color.w * blur_radius);
	#endif
	
	#define SAMPLE(OFFSET,WEIGHT) { \
		float4 texcoord = IN.texcoord_0.xyxy + offset; \
		half4 sample_0 = s_texture_0.Sample(s_sampler_0,texcoord.xy); \
		half4 sample_1 = s_texture_0.Sample(s_sampler_0,texcoord.zw); \
		half weight_0 = sample_0.w * WEIGHT; \
		half weight_1 = sample_1.w * WEIGHT; \
		color.xyz += sample_0.xyz * weight_0; \
		color.xyz += sample_1.xyz * weight_1; \
		weight += weight_0; \
		weight += weight_1; \
	}
	
	half weight = 1.0f;
	
	SAMPLE(offset * 1.0f,0.960005f)
	SAMPLE(offset * 2.0f,0.849366f)
	SAMPLE(offset * 3.0f,0.692569f)
	SAMPLE(offset * 4.0f,0.520450f)
	SAMPLE(offset * 5.0f,0.360448f)
	
	color.xyz /= weight;
	
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

uniform half blur_radius;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 color = h4tex2D(s_texture_0,IN.texcoord_0);
	
	#ifdef HBLUR
		half4 offset = half4(color.w * blur_radius,0.0f,-color.w * blur_radius,0.0f);
	#elif VBLUR
		half4 offset = half4(0.0f,color.w * blur_radius,0.0f,-color.w * blur_radius);
	#endif
	
	#define SAMPLE(OFFSET,WEIGHT) { \
		float4 texcoord = IN.texcoord_0.xyxy + offset; \
		half4 sample_0 = h4tex2D(s_texture_0,texcoord.xy); \
		half4 sample_1 = h4tex2D(s_texture_0,texcoord.zw); \
		half weight_0 = sample_0.w * WEIGHT; \
		half weight_1 = sample_1.w * WEIGHT; \
		color.xyz += sample_0.xyz * weight_0; \
		color.xyz += sample_1.xyz * weight_1; \
		weight += weight_0; \
		weight += weight_1; \
	}
	
	half weight = 1.0f;
	
	SAMPLE(offset * 1.0f,0.960005f)
	SAMPLE(offset * 2.0f,0.849366f)
	SAMPLE(offset * 3.0f,0.692569f)
	SAMPLE(offset * 4.0f,0.520450f)
	
	color.xyz /= weight;
	
	return color;
}

#endif
