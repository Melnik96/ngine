/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_auxiliary.shader
 * Desc:    Billboard base auxiliary shader
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

uniform sampler2D s_texture_0;

uniform sampler2D s_texture_10;

uniform half4 auxiliary_color;

/*
 */
void main() {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texture2DAlphaFadeDiscard(s_texture_10,gl_TexCoord[7].z);
	#endif
	
	texture2DAlphaDiscard(s_texture_0,gl_TexCoord[0].xy,1.0f);
	
	gl_FragColor = auxiliary_color;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half4 auxiliary_color;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_10,IN.texcoord_7,IN.texcoord_7.z);
	#endif
	
	tex2DAlphaDiscard(s_texture_0,IN.texcoord_0.xy,1.0f);
	
	return auxiliary_color;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);

Texture2D s_texture_10 : register(t10);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

cbuffer shader_parameters {
	float4 auxiliary_color;
};

/*
 */
FRAGMENT_ALPHA_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_ALPHA_OUT OUT;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texture2DAlphaFadeDiscard(s_texture_10,s_sampler_10,IN.position.xy,IN.texcoord_9.x);
	#endif
	
	OUT = texture2DAlphaDiscard(s_texture_0,s_sampler_0,IN.texcoord_0.xy,1.0f);
	
	OUT.color = auxiliary_color;
	
	return OUT;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_0 : TEXUNIT0;

uniform sampler2D s_texture_10 : TEXUNIT10;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half4 auxiliary_color;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_10,IN.texcoord_9,IN.texcoord_9.z);
	#endif
	
	tex2DAlphaDiscard(s_texture_0,IN.texcoord_0.xy,1.0f);
	
	return auxiliary_color;
}

#endif
