/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_refraction_sample.shader
 * Desc:    Render refraction sample shader
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

/* s_texture_0 is screen texture
 * s_texture_1 is refraction texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;
uniform SAMPLER_2DMS s_texture_1;

/*
 */
void main() {
	
	half4 refraction = texture2DDeferredNorm(s_texture_1,gl_TexCoord[0].xy);
	half2 refraction_offset = (refraction.xy - refraction.zw) * half2(gl_TexCoord[1].xy);
	refraction_offset *= saturate(texture2DDeferredNorm(s_texture_1,gl_TexCoord[0].xy + refraction_offset).w * 255.0f);
	float2 texcoord = gl_TexCoord[0].xy + refraction_offset;
	
	half4 color = texture2D(s_texture_0,texcoord);
	
	gl_FragColor = color;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 refraction = tex2D(s_texture_1,IN.texcoord_0);
	half2 refraction_offset = (refraction.xy - refraction.zw) * IN.texcoord_1;
	refraction_offset *= saturate(tex2D(s_texture_1,IN.texcoord_0 + refraction_offset).w * 255.0f);
	float2 texcoord = IN.texcoord_0.xy + refraction_offset;
	
	half4 color = tex2D(s_texture_0,texcoord);
	
	return color;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
TEXTURE_2DMS s_texture_1 : register(t1);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 refraction = texture2DDeferredNorm(s_texture_1,s_sampler_1,IN.texcoord_0);
	half2 refraction_offset = (refraction.xy - refraction.zw) * IN.texcoord_1;
	refraction_offset *= saturate(texture2DDeferredNorm(s_texture_1,s_sampler_1,IN.texcoord_0 + refraction_offset).w * 255.0f);
	float2 texcoord = IN.texcoord_0.xy + refraction_offset;
	
	float4 color = s_texture_0.Sample(s_sampler_0,texcoord);
	
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
uniform sampler2D s_texture_1 : TEXUNIT1;

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 refraction = h4tex2D(s_texture_1,IN.texcoord_0);
	half2 refraction_offset = (refraction.xy - refraction.zw) * IN.texcoord_1;
	refraction_offset *= saturate(h4tex2D(s_texture_1,IN.texcoord_0 + refraction_offset).w * 255.0f);
	float2 texcoord = IN.texcoord_0.xy + refraction_offset;
	
	half4 color = h4tex2D(s_texture_0,texcoord);
	
	return color;
}

#endif
