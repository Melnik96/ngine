/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_leaf_ambient.shader
 * Desc:    Mesh leaf ambient shader
 * Version: 1.18
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
 * s_texture_4 is noise texture
 * s_texture_5 is color texture
 * 
 * s_texture_11 is environment texture
 * s_texture_12 is deferred light texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;
uniform sampler3D s_texture_4;
uniform sampler2D s_texture_5;

uniform samplerCube s_texture_11;
uniform sampler2D s_texture_12;

uniform half environment_scale;
uniform half noise_scale;
uniform half4 color_scale;

/*
 */
void main() {
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	half3 color = diffuse.xyz * s_ambient_color.xyz;
	
	half3 environment = textureCube(s_texture_11,gl_TexCoord[1].xyz).xyz;
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = texture2DProj(s_texture_12,gl_TexCoord[7]);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,diffuse.xyz,light);
	#endif
	
	gl_FragColor = half4(color,diffuse.w) * color_scale;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	#ifdef NOISE
		float3 texcoord_6 : TEXCOORD6;
	#endif
	#ifdef USE_DEFERRED || (USE_ALPHA_FADE && ALPHA_FADE)
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half environment_scale;
half noise_scale;
half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	half3 color = diffuse.xyz * s_ambient_color.xyz;
	
	half3 environment = texCUBE(s_texture_11,IN.texcoord_1).xyz;
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = tex2Dproj(s_texture_12,IN.texcoord_7);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,diffuse.xyz,light);
	#endif
	
	return half4(color,diffuse.w) * color_scale;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
Texture3D s_texture_4 : register(t4);
Texture2D s_texture_5 : register(t5);

TextureCube s_texture_11 : register(t11);
Texture2D s_texture_12 : register(t12);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	#ifdef NOISE
		float3 texcoord_6 : TEXCOORD6;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

cbuffer shader_parameters {
	float environment_scale;
	#ifdef NOISE
		float noise_scale;
	#endif
	float4 color_scale;
};

/*
 */
FRAGMENT_ALPHA_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_ALPHA_OUT OUT;
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	half3 color = diffuse.xyz * s_ambient_color.xyz;
	
	half3 environment = s_texture_11.Sample(s_sampler_11,IN.texcoord_1).xyz;
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = s_texture_12.Sample(s_sampler_12,IN.position.xy * s_viewport.zw);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,diffuse.xyz,light);
	#endif
	
	OUT.color = float4(color,diffuse.w) * color_scale;
	
	return OUT;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_0 : TEXUNIT0;
uniform sampler3D s_texture_4 : TEXUNIT4;
uniform sampler2D s_texture_5 : TEXUNIT5;

uniform samplerCUBE s_texture_11 : TEXUNIT11;
uniform sampler2D s_texture_12 : TEXUNIT12;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	#ifdef NOISE
		float3 texcoord_8 : TEXCOORD8;
	#endif
	#ifdef USE_DEFERRED || (USE_ALPHA_FADE && ALPHA_FADE)
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half environment_scale;
uniform half noise_scale;
uniform half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	half3 color = diffuse.xyz * s_ambient_color.xyz;
	
	half3 environment = h3texCUBE(s_texture_11,IN.texcoord_1);
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = h4tex2Dproj(s_texture_12,IN.texcoord_9.xyw);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,diffuse.xyz,light);
	#endif
	
	return half4(color,diffuse.w) * color_scale;
}

#endif
