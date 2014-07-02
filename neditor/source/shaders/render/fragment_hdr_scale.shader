/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_hdr_scale.shader
 * Desc:    Render hdr scale shader
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

/* s_texture_0 is average texture
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
	
	half color = (texture2D(s_texture_0,gl_TexCoord[0].xy).x + texture2D(s_texture_0,gl_TexCoord[0].zw).x +
		texture2D(s_texture_0,gl_TexCoord[1].xy).x + texture2D(s_texture_0,gl_TexCoord[1].zw).x +
		texture2D(s_texture_0,gl_TexCoord[2].xy).x + texture2D(s_texture_0,gl_TexCoord[2].zw).x +
		texture2D(s_texture_0,gl_TexCoord[3].xy).x + texture2D(s_texture_0,gl_TexCoord[3].zw).x +
		texture2D(s_texture_0,gl_TexCoord[4].xy).x + texture2D(s_texture_0,gl_TexCoord[4].zw).x +
		texture2D(s_texture_0,gl_TexCoord[5].xy).x + texture2D(s_texture_0,gl_TexCoord[5].zw).x +
		texture2D(s_texture_0,gl_TexCoord[6].xy).x + texture2D(s_texture_0,gl_TexCoord[6].zw).x +
		texture2D(s_texture_0,gl_TexCoord[7].xy).x + texture2D(s_texture_0,gl_TexCoord[7].zw).x) * (1.0f / 16.0f);
	
	gl_FragColor = half4(color);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	float4 texcoord_4 : TEXCOORD4;
	float4 texcoord_5 : TEXCOORD5;
	float4 texcoord_6 : TEXCOORD6;
	float4 texcoord_7 : TEXCOORD7;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half color = (tex2D(s_texture_0,IN.texcoord_0.xy).x + tex2D(s_texture_0,IN.texcoord_0.zw).x +
		tex2D(s_texture_0,IN.texcoord_1.xy).x + tex2D(s_texture_0,IN.texcoord_1.zw).x + 
		tex2D(s_texture_0,IN.texcoord_2.xy).x + tex2D(s_texture_0,IN.texcoord_2.zw).x + 
		tex2D(s_texture_0,IN.texcoord_3.xy).x + tex2D(s_texture_0,IN.texcoord_3.zw).x + 
		tex2D(s_texture_0,IN.texcoord_4.xy).x + tex2D(s_texture_0,IN.texcoord_4.zw).x + 
		tex2D(s_texture_0,IN.texcoord_5.xy).x + tex2D(s_texture_0,IN.texcoord_5.zw).x + 
		tex2D(s_texture_0,IN.texcoord_6.xy).x + tex2D(s_texture_0,IN.texcoord_6.zw).x + 
		tex2D(s_texture_0,IN.texcoord_7.xy).x + tex2D(s_texture_0,IN.texcoord_7.zw).x) * (1.0f / 16.0f);
	
	return color;
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
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	float4 texcoord_4 : TEXCOORD4;
	float4 texcoord_5 : TEXCOORD5;
	float4 texcoord_6 : TEXCOORD6;
	float4 texcoord_7 : TEXCOORD7;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	float color = (s_texture_0.Sample(s_sampler_0,IN.texcoord_0.xy).x + s_texture_0.Sample(s_sampler_0,IN.texcoord_0.zw).x +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_1.xy).x + s_texture_0.Sample(s_sampler_0,IN.texcoord_1.zw).x + 
		s_texture_0.Sample(s_sampler_0,IN.texcoord_2.xy).x + s_texture_0.Sample(s_sampler_0,IN.texcoord_2.zw).x + 
		s_texture_0.Sample(s_sampler_0,IN.texcoord_3.xy).x + s_texture_0.Sample(s_sampler_0,IN.texcoord_3.zw).x + 
		s_texture_0.Sample(s_sampler_0,IN.texcoord_4.xy).x + s_texture_0.Sample(s_sampler_0,IN.texcoord_4.zw).x + 
		s_texture_0.Sample(s_sampler_0,IN.texcoord_5.xy).x + s_texture_0.Sample(s_sampler_0,IN.texcoord_5.zw).x + 
		s_texture_0.Sample(s_sampler_0,IN.texcoord_6.xy).x + s_texture_0.Sample(s_sampler_0,IN.texcoord_6.zw).x + 
		s_texture_0.Sample(s_sampler_0,IN.texcoord_7.xy).x + s_texture_0.Sample(s_sampler_0,IN.texcoord_7.zw).x) * (1.0f / 16.0f);
	
	return color;
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
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	float4 texcoord_4 : TEXCOORD4;
	float4 texcoord_5 : TEXCOORD5;
	float4 texcoord_6 : TEXCOORD6;
	float4 texcoord_7 : TEXCOORD7;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half color = (h1tex2D(s_texture_0,IN.texcoord_0.xy) + h1tex2D(s_texture_0,IN.texcoord_0.zw) +
		h1tex2D(s_texture_0,IN.texcoord_1.xy) + h1tex2D(s_texture_0,IN.texcoord_1.zw) + 
		h1tex2D(s_texture_0,IN.texcoord_2.xy) + h1tex2D(s_texture_0,IN.texcoord_2.zw) + 
		h1tex2D(s_texture_0,IN.texcoord_3.xy) + h1tex2D(s_texture_0,IN.texcoord_3.zw) + 
		h1tex2D(s_texture_0,IN.texcoord_4.xy) + h1tex2D(s_texture_0,IN.texcoord_4.zw) + 
		h1tex2D(s_texture_0,IN.texcoord_5.xy) + h1tex2D(s_texture_0,IN.texcoord_5.zw) + 
		h1tex2D(s_texture_0,IN.texcoord_6.xy) + h1tex2D(s_texture_0,IN.texcoord_6.zw) + 
		h1tex2D(s_texture_0,IN.texcoord_7.xy) + h1tex2D(s_texture_0,IN.texcoord_7.zw)) * (1.0f / 16.0f);
	
	return color;
}

#endif
