/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_auxiliary.shader
 * Desc:    Decal base auxiliary shader
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
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;

half4 auxiliary_color;

/*
 */
void main() {
	
	half2 texcoord = gl_TexCoord[0].xy / gl_TexCoord[0].w;
	
	texture2DAlphaDiscard(s_texture_0,texcoord,gl_TexCoord[0].z);
	
	return auxiliary_color;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
};

half4 auxiliary_color;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half2 texcoord = IN.texcoord_0.xy / IN.texcoord_0.w;
	
	tex2DAlphaDiscard(s_texture_0,texcoord,IN.texcoord_0.z);
	
	return auxiliary_color;
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
	float4 texcoord_0 : TEXCOORD0;
};

cbuffer shader_parameters {
	float4 auxiliary_color;
};

/*
 */
FRAGMENT_ALPHA_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_ALPHA_OUT OUT;
	
	half2 texcoord = IN.texcoord_0.xy / IN.texcoord_0.w;
	
	OUT = texture2DAlphaDiscard(s_texture_0,s_sampler_0,texcoord,IN.texcoord_0.z);
	
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

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
};

uniform half4 auxiliary_color;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half2 texcoord = IN.texcoord_0.xy / IN.texcoord_0.w;
	
	tex2DAlphaDiscard(s_texture_0,texcoord,IN.texcoord_0.z);
	
	return auxiliary_color;
}

#endif
