/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_hdr_sample.shader
 * Desc:    Render hdr sample shader
 * Version: 1.05
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

/* s_texture_0 is screen texture
 * s_texture_1 is glow texture
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
	
	half3 color = texture2D(s_texture_0,gl_TexCoord[0].xy).xyz;
	
	#ifdef GLOW
		half3 glow = texture2D(s_texture_1,gl_TexCoord[0].xy).xyz;
		color += glow;
	#endif
	
	gl_FragColor = half4(max(color,half3(0.0f)),1.0f);
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

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 color = tex2D(s_texture_0,IN.texcoord_0).xyz;
	
	#ifdef GLOW
		half3 glow = tex2D(s_texture_1,IN.texcoord_0).xyz;
		color += glow;
	#endif
	
	return half4(max(color,0.0f),1.0f);
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
	float2 texcoord_0 : TEXCOORD0;
};

/*
 */
float3 main(FRAGMENT_IN IN) : SV_TARGET {
	
	float3 color = s_texture_0.Sample(s_sampler_0,IN.texcoord_0).xyz;
	
	#ifdef GLOW
		float3 glow = s_texture_1.Sample(s_sampler_1,IN.texcoord_0).xyz;
		color += glow;
	#endif
	
	return max(color,0.0f);
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

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 color = h3tex2D(s_texture_0,IN.texcoord_0);
	
	#ifdef GLOW
		half3 glow = h3tex2D(s_texture_1,IN.texcoord_0);
		color += glow;
	#endif
	
	return half4(max(color,0.0f),1.0f);
}

#endif
