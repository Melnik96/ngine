/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_ambient.shader
 * Desc:    Gui base ambient shader
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

/* s_texture_0 is color texture
 * 
 * s_texture_10 is alpha fade texture
 * s_texture_11 is deferred light texture
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
uniform sampler2D s_texture_11;

uniform half4 diffuse_color;
uniform half4 specular_color;
uniform half4 color_scale;

/*
 */
void main() {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texture2DAlphaFadeDiscard(s_texture_10,gl_TexCoord[7].z);
	#endif
	
	half4 color = texture2D(s_texture_0,gl_TexCoord[0].zw);
	
	#ifdef YUV
		half2 uv = color.yz - 0.5f;
		color.xyz = saturate(half3(1.40200f * uv.y,-0.71414f * uv.y - 0.34414f * uv.x,1.77200f * uv.x) + color.x);
	#endif
	
	#ifdef USE_SRGB
		color.xyz *= color.xyz;
	#endif
	
	color *= half4(gl_TexCoord[1]);
	
	#ifdef USE_DEFERRED
		half4 light = texture2DProj(s_texture_11,gl_TexCoord[7]);
		color.xyz += getDiffuseSpecularDeferredAmbient(diffuse_color.xyz,specular_color.xyz,light);
	#endif
	
	gl_FragColor = color * color_scale;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
	#ifdef USE_DEFERRED || (USE_ALPHA_FADE && ALPHA_FADE)
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half4 diffuse_color;
half4 specular_color;
half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_10,IN.texcoord_7,IN.texcoord_7.z);
	#endif
	
	half4 color = tex2D(s_texture_0,IN.texcoord_0.xy);
	
	#ifdef YUV
		half2 uv = color.yz - 0.5f;
		color.xyz = saturate(half3(1.40200f * uv.y,-0.71414f * uv.y - 0.34414f * uv.x,1.77200f * uv.x) + color.x);
	#endif
	
	#ifdef USE_SRGB
		color.xyz *= color.xyz;
	#endif
	
	color *= IN.texcoord_1;
	
	#ifdef USE_DEFERRED
		half4 light = tex2Dproj(s_texture_11,IN.texcoord_7);
		color.xyz += getDiffuseSpecularDeferredAmbient(diffuse_color.xyz,specular_color.xyz,light);
	#endif
	
	return color * color_scale;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);

Texture2D s_texture_10 : register(t10);
Texture2D s_texture_11 : register(t11);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

cbuffer shader_parameters {
	float4 diffuse_color;
	float4 specular_color;
	float4 color_scale;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texture2DAlphaFadeDiscard(s_texture_10,s_sampler_10,IN.position.xy,IN.texcoord_9.x);
	#endif
	
	half4 color = s_texture_0.Sample(s_sampler_1,IN.texcoord_0.xy);
	
	#ifdef YUV
		half2 uv = color.yz - 0.5f;
		color.xyz = saturate(half3(1.40200f * uv.y,-0.71414f * uv.y - 0.34414f * uv.x,1.77200f * uv.x) + color.x);
	#endif
	
	#ifdef USE_SRGB
		color.xyz *= color.xyz;
	#endif
	
	color *= half4(IN.texcoord_1);
	
	#ifdef USE_DEFERRED
		half4 light = s_texture_11.Sample(s_sampler_11,IN.position.xy * s_viewport.zw);
		color.xyz += getDiffuseSpecularDeferredAmbient(diffuse_color.xyz,specular_color.xyz,light);
	#endif
	
	return color * color_scale;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_0 : TEXUNIT0;

uniform sampler2D s_texture_10 : TEXUNIT10;
uniform sampler2D s_texture_11 : TEXUNIT11;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	#ifdef USE_DEFERRED || (USE_ALPHA_FADE && ALPHA_FADE)
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half4 diffuse_color;
uniform half4 specular_color;
uniform half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_10,IN.texcoord_9,IN.texcoord_9.z);
	#endif
	
	half4 color = h4tex2D(s_texture_0,IN.texcoord_0.xy);
	
	#ifdef YUV
		half2 uv = color.yz - 0.5f;
		color.xyz = saturate(half3(1.40200f * uv.y,-0.71414f * uv.y - 0.34414f * uv.x,1.77200f * uv.x) + color.x);
	#endif
	
	#ifdef USE_SRGB
		color.xyz *= color.xyz;
	#endif
	
	color *= IN.texcoord_1;
	
	#ifdef USE_DEFERRED
		half4 light = h4tex2Dproj(s_texture_11,IN.texcoord_9.xyw);
		color.xyz += getDiffuseSpecularDeferredAmbient(diffuse_color.xyz,specular_color.xyz,light);
	#endif
	
	return color * color_scale;
}

#endif
