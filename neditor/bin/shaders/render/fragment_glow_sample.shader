/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_glow_sample.shader
 * Desc:    Render glow sample shader
 * Version: 1.15
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
 * s_texture_1 is deferred texture
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

uniform half threshold;
uniform half multiplier;

/*
 */
void main() {
	
	#ifndef QUALITY_MEDIUM
		half3 color = texture2D(s_texture_0,gl_TexCoord[0].xy).xyz * getDeferredGlow(texture2DDeferredNorm2(s_texture_1,gl_TexCoord[0].xy));
	#else
		half3 color = (texture2D(s_texture_0,gl_TexCoord[0].xy).xyz * getDeferredGlow(texture2DDeferredNorm2(s_texture_1,gl_TexCoord[0].xy)) +
			texture2D(s_texture_0,gl_TexCoord[0].zw).xyz * getDeferredGlow(texture2DDeferredNorm2(s_texture_1,gl_TexCoord[0].zw)) +
			texture2D(s_texture_0,gl_TexCoord[1].xy).xyz * getDeferredGlow(texture2DDeferredNorm2(s_texture_1,gl_TexCoord[1].xy)) +
			texture2D(s_texture_0,gl_TexCoord[1].zw).xyz * getDeferredGlow(texture2DDeferredNorm2(s_texture_1,gl_TexCoord[1].zw))) * (1.0f / 4.0f);
	#endif
	
	half value = max(max(color.x,color.y),color.z);
	color *= max(value - threshold,0.0f) * multiplier;
	
	gl_FragColor = half4(color,1.0f);
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
};

half threshold;
half multiplier;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#ifndef QUALITY_MEDIUM
		half3 color = tex2D(s_texture_0,IN.texcoord_0.xy).xyz * getDeferredGlow(tex2D(s_texture_1,IN.texcoord_0.xy));
	#else
		half3 color = (tex2D(s_texture_0,IN.texcoord_0.xy).xyz * getDeferredGlow(tex2D(s_texture_1,IN.texcoord_0.xy)) +
			tex2D(s_texture_0,IN.texcoord_0.zw).xyz * getDeferredGlow(tex2D(s_texture_1,IN.texcoord_0.zw)) +
			tex2D(s_texture_0,IN.texcoord_1.xy).xyz * getDeferredGlow(tex2D(s_texture_1,IN.texcoord_1.xy)) +
			tex2D(s_texture_0,IN.texcoord_1.zw).xyz * getDeferredGlow(tex2D(s_texture_1,IN.texcoord_1.zw))) * (1.0f / 4.0f);
	#endif
	
	half value = max(max(color.x,color.y),color.z);
	color *= max(value - threshold,0.0f) * multiplier;
	
	return half4(color,1.0f);
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
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

float threshold;
float multiplier;

/*
 */
float3 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#ifndef QUALITY_MEDIUM
		float3 color = s_texture_0.Sample(s_sampler_0,IN.texcoord_0.xy).xyz * getDeferredGlow(texture2DDeferredNorm2(s_texture_1,s_sampler_1,IN.texcoord_0.xy));
	#else
		float3 color = (s_texture_0.Sample(s_sampler_0,IN.texcoord_0.xy).xyz * getDeferredGlow(texture2DDeferredNorm2(s_texture_1,s_sampler_1,IN.texcoord_0.xy)) +
			s_texture_0.Sample(s_sampler_0,IN.texcoord_0.zw).xyz * getDeferredGlow(texture2DDeferredNorm2(s_texture_1,s_sampler_1,IN.texcoord_0.zw)) +
			s_texture_0.Sample(s_sampler_0,IN.texcoord_1.xy).xyz * getDeferredGlow(texture2DDeferredNorm2(s_texture_1,s_sampler_1,IN.texcoord_1.xy)) +
			s_texture_0.Sample(s_sampler_0,IN.texcoord_1.zw).xyz * getDeferredGlow(texture2DDeferredNorm2(s_texture_1,s_sampler_1,IN.texcoord_1.zw))) * (1.0f / 4.0f);
	#endif
	
	float value = max(max(color.x,color.y),color.z);
	color *= max(value - threshold,0.0f) * multiplier;
	
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
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

uniform half threshold;
uniform half multiplier;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 color = h3tex2D(s_texture_0,IN.texcoord_0.xy) * getDeferredGlow(h4tex2D(s_texture_1,IN.texcoord_0.xy));
	
	half value = max(max(color.x,color.y),color.z);
	color *= max(value - threshold,0.0f) * multiplier;
	
	return half4(color,1.0f);
}

#endif
