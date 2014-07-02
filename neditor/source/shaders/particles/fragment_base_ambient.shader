/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_ambient.shader
 * Desc:    Particles base ambient shader
 * Version: 1.11
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
 * 
 * s_texture_12 is deferred depth texture
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

uniform SAMPLER_2DMS s_texture_12;

uniform half animation_scale;

/*
 */
void main() {
	
	#include <core/shaders/particles/fragment_base_sample.h>
	
	#ifdef OPACITY
		color *= s_ambient_color;
	#endif
	
	#include <core/shaders/particles/fragment_base_volume.h>
	
	gl_FragColor = color * half4(gl_TexCoord[1]);
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
	#ifdef VOLUME
		float4 texcoord_2 : TEXCOORD2;
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half animation_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/particles/fragment_base_sample.h>
	
	#ifdef OPACITY
		color *= s_ambient_color;
	#endif
	
	#include <core/shaders/particles/fragment_base_volume.h>
	
	return color * IN.texcoord_1;
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

TEXTURE_2DMS s_texture_12 : register(t12);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	#ifdef VOLUME
		float4 texcoord_2 : TEXCOORD2;
	#endif
};

cbuffer shader_parameters {
	float animation_scale;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#include <core/shaders/particles/fragment_base_sample.h>
	
	#ifdef OPACITY
		color *= s_ambient_color;
	#endif
	
	#include <core/shaders/particles/fragment_base_volume.h>
	
	return color * IN.texcoord_1;
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

uniform sampler2D s_texture_12 : TEXUNIT12;

struct FRAGMENT_IN {
	half4 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
	#ifdef VOLUME
		float4 texcoord_2 : TEXCOORD2;
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half animation_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/particles/fragment_base_sample.h>
	
	#ifdef OPACITY
		color *= s_ambient_color;
	#endif
	
	#include <core/shaders/particles/fragment_base_volume.h>
	
	return color * IN.texcoord_1;
}

#endif
