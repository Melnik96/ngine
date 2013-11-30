/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_stereo_wide.shader
 * Desc:    Post stereo wide shader
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

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;
uniform sampler2D s_texture_1;

/*
 */
void main() {
	
	if(gl_TexCoord[0].x < 1.0f) {
		gl_FragColor = texture2D(s_texture_0,gl_TexCoord[0].xy);
	} else {
		gl_FragColor = texture2D(s_texture_1,gl_TexCoord[0].zw);
	}
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

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	if(IN.texcoord_0.x < 1.0f) {
		return tex2D(s_texture_0,IN.texcoord_0.xy);
	} else {
		return tex2D(s_texture_1,IN.texcoord_0.zw);
	}
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
	float4 texcoord_0 : TEXCOORD0;
};

/*
 */
float3 main(FRAGMENT_IN IN) : SV_TARGET {
	
	if(IN.texcoord_0.x < 1.0f) {
		return s_texture_0.Sample(s_sampler_0,IN.texcoord_0.xy).xyz;
	} else {
		return s_texture_1.Sample(s_sampler_1,IN.texcoord_0.zw).xyz;
	}
}

#endif
