/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_ambient.shader
 * Desc:    Grass base ambient shader
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

/* s_texture_0 is diffuse texture
 * s_texture_1 is noise texture
 * 
 * s_texture_13 is environment texture
 * s_texture_14 is lightmap texture
 * s_texture_15 is deferred light texture
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

uniform samplerCube s_texture_13;
uniform sampler2D s_texture_14;
uniform sampler2D s_texture_15;

uniform half environment_scale;
uniform half lightmap_scale;
uniform half noise_scale;

/*
 */
void main() {
	
	#include <core/shaders/grass/fragment_base_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif LIGHTMAP
		half3 lightmap = texture2D(s_texture_14,gl_TexCoord[1].xy).xyz;
		half3 color = diffuse.xyz * (s_ambient_color.xyz + lightmap * lightmap_scale);
	#endif
	
	half3 environment = textureCube(s_texture_13,gl_TexCoord[2].xyz).xyz;
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = texture2DProj(s_texture_15,gl_TexCoord[7]);
		color += getDiffuseDeferredAmbient(diffuse.xyz,light);
	#endif
	
	gl_FragColor = half4(color,diffuse.w);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	#ifdef LIGHTMAP
		float2 texcoord_1 : TEXCOORD1;
	#endif
	float4 texcoord_2 : TEXCOORD2;
	#ifdef USE_DEFERRED
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half environment_scale;
half lightmap_scale;
half noise_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/grass/fragment_base_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif LIGHTMAP
		half3 lightmap = tex2D(s_texture_14,IN.texcoord_1).xyz;
		half3 color = diffuse.xyz * (s_ambient_color.xyz + lightmap * lightmap_scale);
	#endif
	
	half3 environment = texCUBE(s_texture_13,IN.texcoord_2.xyz).xyz;
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = tex2Dproj(s_texture_15,IN.texcoord_7);
		color += getDiffuseDeferredAmbient(diffuse.xyz,light);
	#endif
	
	return half4(color,diffuse.w);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
Texture2D s_texture_1 : register(t1);

TextureCube s_texture_13 : register(t13);
Texture2D s_texture_14 : register(t14);
Texture2D s_texture_15 : register(t15);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	#ifdef LIGHTMAP
		float2 texcoord_1 : TEXCOORD1;
	#endif
	float4 texcoord_2 : TEXCOORD2;
};

cbuffer shader_parameters {
	float environment_scale;
	#ifdef LIGHTMAP
		float lightmap_scale;
	#endif
	#ifdef NOISE
		float noise_scale;
	#endif
};

/*
 */
FRAGMENT_ALPHA_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_ALPHA_OUT OUT;
	
	#include <core/shaders/grass/fragment_base_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif LIGHTMAP
		half3 lightmap = s_texture_14.Sample(s_sampler_14,IN.texcoord_1).xyz;
		half3 color = diffuse.xyz * (s_ambient_color.xyz + lightmap * lightmap_scale);
	#endif
	
	half3 environment = s_texture_13.Sample(s_sampler_13,IN.texcoord_2.xyz).xyz;
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = s_texture_15.Sample(s_sampler_15,IN.position.xy * s_viewport.zw);
		color += getDiffuseDeferredAmbient(diffuse.xyz,light);
	#endif
	
	OUT.color = float4(color,diffuse.w);
	
	return OUT;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_0 : TEXUNIT0;
uniform sampler2D s_texture_1 : TEXUNIT1;

uniform samplerCUBE s_texture_13 : TEXUNIT13;
uniform sampler2D s_texture_14 : TEXUNIT14;
uniform sampler2D s_texture_15 : TEXUNIT15;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	#ifdef LIGHTMAP
		float2 texcoord_1 : TEXCOORD1;
	#endif
	float4 texcoord_2 : TEXCOORD2;
	#ifdef USE_DEFERRED
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half environment_scale;
uniform half lightmap_scale;
uniform half noise_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/grass/fragment_base_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif LIGHTMAP
		half3 lightmap = h3tex2D(s_texture_14,IN.texcoord_1);
		half3 color = diffuse.xyz * (s_ambient_color.xyz + lightmap * lightmap_scale);
	#endif
	
	half3 environment = h3texCUBE(s_texture_13,IN.texcoord_2.xyz);
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = h4tex2Dproj(s_texture_15,IN.texcoord_9.xyw);
		color += getDiffuseDeferredAmbient(diffuse.xyz,light);
	#endif
	
	return half4(color,diffuse.w);
}

#endif
