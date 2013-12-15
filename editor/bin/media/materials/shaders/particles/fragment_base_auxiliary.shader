/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_auxiliary.shader
 * Desc:    Particles base auxiliary shader
 * Version: 1.01
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

/* s_texture_0 is diffuse texture
 * s_texture_1 is attenuation texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

#ifdef ANIMATION
	uniform sampler3D s_texture_0;
#else
	uniform sampler2D s_texture_0;
#endif
uniform sampler2D s_texture_1;

uniform half animation_scale;
uniform half auxiliary_threshold;
uniform half4 auxiliary_color;

/*
 */
void main() {
	
	#include <core/shaders/particles/fragment_base_sample.h>
	
	half threshold = dot(color.xyz,half3(gl_TexCoord[1].xyz)) - auxiliary_threshold;
	if(threshold <= 0.0f) discard;
	
	gl_FragColor = auxiliary_color;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	half4 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
};

half animation_scale;
half auxiliary_threshold;
half4 auxiliary_color;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/particles/fragment_base_sample.h>
	
	half threshold = dot(color.xyz,IN.texcoord_1.xyz) - auxiliary_threshold;
	if(threshold <= 0.0f) discard;
	
	return auxiliary_color;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

#ifdef ANIMATION
	Texture3D s_texture_0 : register(t0);
#else
	Texture2D s_texture_0 : register(t0);
#endif
Texture2D s_texture_1 : register(t1);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

cbuffer shader_parameters {
	float animation_scale;
	float auxiliary_threshold;
	float4 auxiliary_color;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#include <core/shaders/particles/fragment_base_sample.h>
	
	half threshold = dot(color.xyz,IN.texcoord_1.xyz) - auxiliary_threshold;
	if(threshold <= 0.0f) discard;
	
	return auxiliary_color;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

#ifdef ANIMATION
	uniform sampler3D s_texture_0 : TEXUNIT0;
#else
	uniform sampler2D s_texture_0 : TEXUNIT0;
#endif
uniform sampler2D s_texture_1 : TEXUNIT1;

struct FRAGMENT_IN {
	half4 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
};

uniform half animation_scale;
uniform half auxiliary_threshold;
uniform half4 auxiliary_color;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/particles/fragment_base_sample.h>
	
	half threshold = dot(color.xyz,IN.texcoord_1.xyz) - auxiliary_threshold;
	if(threshold <= 0.0f) discard;
	
	return auxiliary_color;
}

#endif
