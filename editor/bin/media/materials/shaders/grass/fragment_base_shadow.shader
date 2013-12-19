/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_shadow.shader
 * Desc:    Grass base shadow map shader
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

/*
 */
void main() {
	
	half4 diffuse = texture2D(s_texture_0,gl_TexCoord[0].xy);
	if(diffuse.w * gl_TexCoord[0].z <= 0.5f) discard;
	
	gl_FragColor = half4(0.0f);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	half3 texcoord_0 : TEXCOORD0;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 diffuse = tex2D(s_texture_0,IN.texcoord_0.xy);
	if(diffuse.w * IN.texcoord_0.z <= 0.5f) discard;
	
	return 0.0f;
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
	float3 texcoord_0 : TEXCOORD0;
};

/*
 */
float main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 diffuse = s_texture_0.Sample(s_sampler_0,IN.texcoord_0.xy);
	if(diffuse.w * IN.texcoord_0.z <= 0.5f) discard;
	
	return 0.0f;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_0 : TEXUNIT0;

struct FRAGMENT_IN {
	float3 texcoord_0 : TEXCOORD0;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 diffuse = h4tex2D(s_texture_0,IN.texcoord_0.xy);
	if(diffuse.w * IN.texcoord_0.z <= 0.5f) discard;
	
	return 0.0f;
}

#endif