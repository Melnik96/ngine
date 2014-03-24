/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_hdr_luminance.shader
 * Desc:    Render hdr luminance shader
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

/* s_texture_0 is average texture
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

uniform float exposure;
uniform float interpolation;
uniform float min_luminance;
uniform float max_luminance;

/*
 */
void main() {
	
	float new_luminance = texture2D(s_texture_0,float2(0.5f,0.5f)).x;
	float old_luminance = texture2D(s_texture_1,float2(0.5f,0.5f)).y;
	
	float luminance = lerp(old_luminance,new_luminance,interpolation);
	luminance = clamp(luminance,min_luminance,max_luminance);
	
	#ifdef QUADRATIC
		gl_FragColor = float4(exposure / (luminance * luminance),luminance,0.0f,0.0f);
	#else
		gl_FragColor = float4(exposure / exp2(luminance),luminance,0.0f,0.0f);
	#endif
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

float exposure;
float interpolation;
float min_luminance;
float max_luminance;

/*
 */
float4 main() : COLOR {
	
	float new_luminance = tex2D(s_texture_0,float2(0.5f,0.5f)).x;
	float old_luminance = tex2D(s_texture_1,float2(0.5f,0.5f)).y;
	
	float luminance = lerp(old_luminance,new_luminance,interpolation);
	luminance = clamp(luminance,min_luminance,max_luminance);
	
	#ifdef QUADRATIC
		return float4(exposure / (luminance * luminance),luminance,0.0f,0.0f);
	#else
		return float4(exposure / exp2(luminance),luminance,0.0f,0.0f);
	#endif
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
};

float exposure;
float interpolation;
float min_luminance;
float max_luminance;

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	float new_luminance = s_texture_0.Sample(s_sampler_0,float2(0.5f,0.5f)).x;
	float old_luminance = s_texture_1.Sample(s_sampler_1,float2(0.5f,0.5f)).y;
	
	float luminance = lerp(old_luminance,new_luminance,interpolation);
	luminance = clamp(luminance,min_luminance,max_luminance);
	
	#ifdef QUADRATIC
		return float4(exposure / (luminance * luminance),luminance,0.0f,0.0f);
	#else
		return float4(exposure / exp2(luminance),luminance,0.0f,0.0f);
	#endif
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

uniform float exposure;
uniform float interpolation;
uniform float min_luminance;
uniform float max_luminance;

/*
 */
float4 main() : COLOR {
	
	float new_luminance = f4tex2D(s_texture_0,float2(0.5f,0.5f)).x;
	float old_luminance = f4tex2D(s_texture_1,float2(0.5f,0.5f)).y;
	
	float range = max_luminance - min_luminance + 1e-4f;
	float luminance = lerp(old_luminance,new_luminance,interpolation);
	luminance = min_luminance + saturate((luminance - min_luminance) / range) * range;
	
	#ifdef QUADRATIC
		return float4(exposure / (luminance * luminance),luminance,0.0f,0.0f);
	#else
		return float4(exposure / exp2(luminance),luminance,0.0f,0.0f);
	#endif
}

#endif
