/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_hdr_cross.shader
 * Desc:    Render hdr cross flare shader
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
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;

uniform half4 color;
uniform half threshold;

/*
 */
void main() {
	
	float2 texcoord = gl_TexCoord[0].xy;
	float2 direction = gl_TexCoord[1].xy;
	
	half weight = 0.95f;
	half4 sample = texture2D(s_texture_0,texcoord.xy);
	half3 cross = sample.xyz * saturate(sample.w - threshold);
	
	for(int i = 1; i < 32; i++) {
		texcoord += direction;
		sample = texture2D(s_texture_0,texcoord);
		cross += sample.xyz * (saturate(sample.w - threshold) * weight);
		weight *= 0.95f;
	}
	
	// 16.1258f = (1.0f - pow(0.95f,32.0f)) / (1.0f - 0.95f)
	gl_FragColor = half4(cross * color.xyz * (2.0f / 16.1258f),1.0f);
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
};

half4 color;
half threshold;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	float2 texcoord = IN.texcoord_0;
	float2 direction = IN.texcoord_1;
	
	half weight = 0.95f;
	half4 sample = tex2D(s_texture_0,texcoord.xy);
	half3 cross = sample.xyz * (saturate(sample.w - threshold));
	
	[unroll] for(int i = 1; i < 32; i++) {
		texcoord += direction;
		sample = tex2D(s_texture_0,texcoord);
		cross += sample.xyz * (saturate(sample.w - threshold) * weight);
		weight *= 0.95f;
	}
	
	return half4(cross * color.xyz * (2.0f / 16.1258f),1.0f);
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
	float2 texcoord_1 : TEXCOORD1;
};

float4 color;
float threshold;

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	float2 texcoord = IN.texcoord_0;
	float2 direction = IN.texcoord_1;
	
	half weight = 0.95f;
	half4 sample = s_texture_0.Sample(s_sampler_0,texcoord.xy);
	half3 cross = sample.xyz * (saturate(sample.w - threshold));
	
	[unroll] for(int i = 1; i < 32; i++) {
		texcoord += direction;
		sample = s_texture_0.Sample(s_sampler_0,texcoord.xy);
		cross += sample.xyz * (saturate(sample.w - threshold) * weight);
		weight *= 0.95f;
	}
	
	return float4(cross * color.xyz * (2.0f / 16.1258f),1.0f);
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
	float2 texcoord_1 : TEXCOORD1;
};

uniform half4 color;
uniform half threshold;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	float2 texcoord = IN.texcoord_0;
	float2 direction = IN.texcoord_1;
	
	half weight = 0.95f;
	half4 sample = h4tex2D(s_texture_0,texcoord.xy);
	half3 cross = sample.xyz * (saturate(sample.w - threshold));
	
	for(int i = 1; i < 32; i++) {
		texcoord += direction;
		sample = h4tex2D(s_texture_0,texcoord);
		cross += sample.xyz * (saturate(sample.w - threshold) * weight);
		weight *= 0.95f;
	}
	
	return half4(cross * color.xyz * (2.0f / 16.1258f),1.0f);
}

#endif
