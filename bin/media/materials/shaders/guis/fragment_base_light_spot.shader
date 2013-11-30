/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_light_spot.shader
 * Desc:    Gui base light spot shader
 * Version: 1.04
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

/* s_texture_1 is normal texture
 * 
 * s_texture_10 is alpha fade texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_1;

uniform sampler2D s_texture_10;

uniform half4 diffuse_color;
uniform half4 specular_color;
uniform half4 color_scale;

/*
 */
void main() {
	
	#include <core/shaders/guis/fragment_base_sample.h>
	
	#include <core/shaders/common/fragment_base_light_spot.h>
	
	gl_FragColor = half4(color * color_scale.xyz,color_scale.w);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float2 position : VPOS;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	half3 texcoord_5 : TEXCOORD5;
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half4 diffuse_color;
half4 specular_color;
half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/guis/fragment_base_sample.h>
	
	#include <core/shaders/common/fragment_base_light_spot.h>
	
	return half4(color * color_scale.xyz,color_scale.w);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_1 : register(t1);

Texture2D s_texture_10 : register(t10);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	float3 texcoord_5 : TEXCOORD5;
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

cbuffer shader_parameters {
	float4 diffuse_color;
	float4 specular_color;
	float4 color_scale;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#include <core/shaders/guis/fragment_base_sample.h>
	
	#include <core/shaders/common/fragment_base_light_spot.h>
	
	return float4(color * color_scale.xyz,color_scale.w);
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_1 : TEXUNIT1;

uniform sampler2D s_texture_10 : TEXUNIT10;

struct FRAGMENT_IN {
	float2 position : WPOS;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	half3 texcoord_5 : TEXCOORD5;
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half4 diffuse_color;
uniform half4 specular_color;
uniform half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/guis/fragment_base_sample.h>
	
	#include <core/shaders/common/fragment_base_light_spot.h>
	
	return half4(color * color_scale.xyz,color_scale.w);
}

#endif
