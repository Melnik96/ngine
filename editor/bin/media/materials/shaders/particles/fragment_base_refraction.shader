/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_refraction.shader
 * Desc:    Particles base refraction shader
 * Version: 1.10
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

/* s_texture_1 is attenuation texture
 * s_texture_2 is normal texture
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

uniform sampler2D s_texture_1;
#ifdef ANIMATION
	uniform sampler3D s_texture_2;
#else
	uniform sampler2D s_texture_2;
#endif

uniform SAMPLER_2DMS s_texture_12;

uniform float animation_scale;

/*
 */
void main() {
	
	#ifdef ANIMATION
		half3 texcoord = half3(gl_TexCoord[0].xy,half(gl_TexCoord[0].z) * animation_scale);
		half2 normal = texture3D(s_texture_2,texcoord).xy;
	#else
		half2 normal = texture2D(s_texture_2,gl_TexCoord[0].xy).xy;
	#endif
	
	#ifndef USE_ARB_TEXTURE_SNORM
		normal = normal * 2.0f - 1.0f;
	#endif
	
	normal *= texture2D(s_texture_1,gl_TexCoord[0].zw).w;
	
	half4 color = saturate(half4(normal,-normal));
	
	#include <core/shaders/particles/fragment_base_volume.h>
	
	gl_FragColor = color * half(gl_TexCoord[1].x) + 1.0f / 255.0f;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	half4 texcoord_0 : TEXCOORD0;
	half1 texcoord_1 : TEXCOORD1;
	#ifdef VOLUME
		float4 texcoord_2 : TEXCOORD2;
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half animation_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#ifdef ANIMATION
		half3 texcoord = half3(IN.texcoord_0.xy,IN.texcoord_0.z * animation_scale);
		half2 normal = tex3D(s_texture_2,texcoord).xy * 2.0f - 1.0f;
	#else
		half2 normal = tex2D(s_texture_2,IN.texcoord_0.xy).xy * 2.0f - 1.0f;
	#endif
	
	normal *= tex2D(s_texture_1,IN.texcoord_0.zw).w;
	
	half4 color = saturate(half4(normal,-normal));
	
	#include <core/shaders/particles/fragment_base_volume.h>
	
	return color * IN.texcoord_1.x + 1.0f / 255.0f;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_1 : register(t1);
#ifdef ANIMATION
	Texture3D s_texture_2 : register(t2);
#else
	Texture2D s_texture_2 : register(t2);
#endif

TEXTURE_2DMS s_texture_12 : register(t12);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float1 texcoord_1 : TEXCOORD1;
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
	
	#ifdef ANIMATION
		half3 texcoord = half3(IN.texcoord_0.xy,IN.texcoord_0.z * animation_scale);
		half2 normal = s_texture_2.Sample(s_sampler_2,texcoord).xy;
	#else
		half2 normal = s_texture_2.Sample(s_sampler_2,IN.texcoord_0.xy).xy;
	#endif
	
	normal *= s_texture_1.Sample(s_sampler_1,IN.texcoord_0.zw).w;
	
	half4 color = saturate(half4(normal,-normal));
	
	#include <core/shaders/particles/fragment_base_volume.h>
	
	return color * IN.texcoord_1.x + 1.0f / 255.0f;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_1 : TEXUNIT1;
#ifdef ANIMATION
	uniform sampler3D s_texture_2 : TEXUNIT2;
#else
	uniform sampler2D s_texture_2 : TEXUNIT2;
#endif

uniform sampler2D s_texture_12 : TEXUNIT12;

struct FRAGMENT_IN {
	half4 texcoord_0 : TEXCOORD0;
	half1 texcoord_1 : TEXCOORD1;
	#ifdef VOLUME
		float4 texcoord_2 : TEXCOORD2;
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half animation_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#ifdef ANIMATION
		half3 texcoord = half3(IN.texcoord_0.xy,IN.texcoord_0.z * animation_scale);
		half2 normal = h2tex3D(s_texture_2,texcoord);
	#else
		half2 normal = h2tex2D(s_texture_2,IN.texcoord_0.xy);
	#endif
	
	normal *= h4tex2D(s_texture_1,IN.texcoord_0.zw).w;
	
	half4 color = saturate(half4(normal,-normal));
	
	#include <core/shaders/particles/fragment_base_volume.h>
	
	return color * IN.texcoord_1.x + 1.0f / 255.0f;
}

#endif
