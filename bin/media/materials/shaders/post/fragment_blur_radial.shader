/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_blur_radial.shader
 * Desc:    Post blur radial shader
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

uniform half length;

/*
 */
void main() {
	
	float2 texcoord = gl_TexCoord[0].xy;
	half2 step = (0.5f - texcoord) * length * 0.01f;
	
	half weight = 0.95f;
	half3 color = texture2D(s_texture_0,texcoord).xyz;
	
	for(int i = 1; i < 16; i++) {
		texcoord += step;
		color += texture2D(s_texture_0,texcoord).xyz * weight;
		weight *= 0.95f;
	}
	
	// 11.1975f = (1.0f - pow(0.95f,16.0f)) / (1.0f - 0.95f)
	gl_FragColor = half4(color * (1.0f / 11.1975f),1.0f);
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

half length;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	float2 texcoord = IN.texcoord_0;
	half2 step = (0.5f - texcoord) * length * 0.01f;
	
	half weight = 0.95f;
	half3 color = tex2D(s_texture_0,texcoord).xyz;
	
	[unroll] for(int i = 1; i < 16; i++) {
		texcoord += step;
		color += tex2D(s_texture_0,texcoord).xyz * weight;
		weight *= 0.95f;
	}
	
	return half4(color * (1.0f / 11.1975f),1.0f);
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

float length;

/*
 */
float3 main(FRAGMENT_IN IN) : SV_TARGET {
	
	float2 texcoord = IN.texcoord_0;
	float2 step = (0.5f - texcoord) * length * 0.01f;
	
	float weight = 0.95f;
	float3 color = s_texture_0.Sample(s_sampler_0,texcoord.xy).xyz;
	
	[unroll] for(int i = 1; i < 16; i++) {
		texcoord += step;
		color += s_texture_0.Sample(s_sampler_0,texcoord.xy).xyz * weight;
		weight *= 0.95f;
	}
	
	return color * (1.0f / 11.1975f);
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

uniform half length;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	float2 texcoord = IN.texcoord_0;
	half2 step = (0.5f - texcoord) * length * 0.01f;
	
	half weight = 0.95f;
	half3 color = h3tex2D(s_texture_0,texcoord);
	
	for(int i = 1; i < 16; i++) {
		texcoord += step;
		color += h3tex2D(s_texture_0,texcoord) * weight;
		weight *= 0.95f;
	}
	
	return half4(color * (1.0f / 11.1975f),1.0f);
}

#endif
