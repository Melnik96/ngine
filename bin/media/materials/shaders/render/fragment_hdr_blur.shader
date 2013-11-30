/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_hdr_blur.shader
 * Desc:    Render hdr blur shader
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

/* s_texture_0 is bright texture
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
	
	half4 color = texture2D(s_texture_0,gl_TexCoord[0].xy) * 0.228297f +
		texture2D(s_texture_0,gl_TexCoord[1].xy) * 0.193907f + texture2D(s_texture_0,gl_TexCoord[1].zw) * 0.193907f +
		texture2D(s_texture_0,gl_TexCoord[2].xy) * 0.118817f + texture2D(s_texture_0,gl_TexCoord[2].zw) * 0.118817f +
		texture2D(s_texture_0,gl_TexCoord[3].xy) * 0.052523f + texture2D(s_texture_0,gl_TexCoord[3].zw) * 0.052523f +
		texture2D(s_texture_0,gl_TexCoord[4].xy) * 0.016750f + texture2D(s_texture_0,gl_TexCoord[4].zw) * 0.016750f +
		texture2D(s_texture_0,gl_TexCoord[5].xy) * 0.003854f + texture2D(s_texture_0,gl_TexCoord[5].zw) * 0.003854f;
	
	gl_FragColor = color;
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
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 color = tex2D(s_texture_0,IN.texcoord_0.xy) * 0.228297f +
		tex2D(s_texture_0,IN.texcoord_1.xy) * 0.193907f + tex2D(s_texture_0,IN.texcoord_1.zw) * 0.193907f +
		tex2D(s_texture_0,IN.texcoord_2.xy) * 0.118817f + tex2D(s_texture_0,IN.texcoord_2.zw) * 0.118817f +
		tex2D(s_texture_0,IN.texcoord_3.xy) * 0.052523f + tex2D(s_texture_0,IN.texcoord_3.zw) * 0.052523f +
		tex2D(s_texture_0,IN.texcoord_4.xy) * 0.016750f + tex2D(s_texture_0,IN.texcoord_4.zw) * 0.016750f +
		tex2D(s_texture_0,IN.texcoord_5.xy) * 0.003854f + tex2D(s_texture_0,IN.texcoord_5.zw) * 0.003854f;
	
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
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	float4 color = s_texture_0.Sample(s_sampler_0,IN.texcoord_0.xy) * 0.228297f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_1.xy) * 0.193907f + s_texture_0.Sample(s_sampler_0,IN.texcoord_1.zw) * 0.193907f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_2.xy) * 0.118817f + s_texture_0.Sample(s_sampler_0,IN.texcoord_2.zw) * 0.118817f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_3.xy) * 0.052523f + s_texture_0.Sample(s_sampler_0,IN.texcoord_3.zw) * 0.052523f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_4.xy) * 0.016750f + s_texture_0.Sample(s_sampler_0,IN.texcoord_4.zw) * 0.016750f +
		s_texture_0.Sample(s_sampler_0,IN.texcoord_5.xy) * 0.003854f + s_texture_0.Sample(s_sampler_0,IN.texcoord_5.zw) * 0.003854f;
	
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
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 color = h4tex2D(s_texture_0,IN.texcoord_0.xy) * 0.230070f +
		h4tex2D(s_texture_0,IN.texcoord_1.xy) * 0.195414f + h4tex2D(s_texture_0,IN.texcoord_1.zw) * 0.195414f +
		h4tex2D(s_texture_0,IN.texcoord_2.xy) * 0.119740f + h4tex2D(s_texture_0,IN.texcoord_2.zw) * 0.119740f +
		h4tex2D(s_texture_0,IN.texcoord_3.xy) * 0.052931f + h4tex2D(s_texture_0,IN.texcoord_3.zw) * 0.052931f +
		h4tex2D(s_texture_0,IN.texcoord_4.xy) * 0.016880f + h4tex2D(s_texture_0,IN.texcoord_4.zw) * 0.016880f;
	
	return color;
}

#endif