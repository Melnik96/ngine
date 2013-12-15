/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_leaf_light_omni.shader
 * Desc:    Mesh leaf light omni shader
 * Version: 1.14
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
 * s_texture_1 is thickness texture
 * s_texture_2 is normal texture
 * s_texture_3 is specular texture
 * s_texture_4 is noise texture
 * s_texture_5 is color texture
 * 
 * s_texture_11 is light modulation texture
 * s_texture_12 is light shadow color texture
 * s_texture_13 is light shadow depth texture
 * s_texture_14 is light shadow noise texture
 * s_texture_15 is light virtual cube texture
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
uniform sampler2D s_texture_2;
uniform sampler2D s_texture_3;
uniform sampler3D s_texture_4;
uniform sampler2D s_texture_5;

uniform samplerCube s_texture_11;
SAMPLER_SHADOW_OMNI_PCF

uniform half translucent_scale;
uniform half thickness_scale;
uniform half noise_scale;
uniform half4 color_scale;

/*
 */
void main() {
	
	#include <core/shaders/meshes/fragment_leaf_light.h>
	
	SHADOW_OMNI_PCF
	
	color *= textureCube(s_texture_11,gl_TexCoord[3].xyz).xyz;
	gl_FragColor = half4(color * s_light_color.xyz,diffuse.w) * color_scale;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float2 position : VPOS;
	float4 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
	#ifdef PHONG
		half3 texcoord_2 : TEXCOORD2;
	#endif
	half3 texcoord_3 : TEXCOORD3;
	#ifdef SHADOW
		float4 texcoord_4 : TEXCOORD4;
		#ifdef USE_TRANSLUCENT
			float3 texcoord_5 : TEXCOORD5;
		#endif
	#endif
	#ifdef NOISE
		float3 texcoord_6 : TEXCOORD6;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		half1 texcoord_7 : TEXCOORD7;
	#endif
};

half translucent_scale;
half thickness_scale;
half noise_scale;
half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_leaf_light.h>
	
	SHADOW_OMNI_PCF
	
	color *= texCUBE(s_texture_11,IN.texcoord_3).xyz;
	return half4(color * s_light_color.xyz,diffuse.w) * color_scale;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
Texture2D s_texture_1 : register(t1);
Texture2D s_texture_2 : register(t2);
Texture2D s_texture_3 : register(t3);
Texture3D s_texture_4 : register(t4);
Texture2D s_texture_5 : register(t5);

TextureCube s_texture_11 : register(t11);
TEXTURE_SHADOW_OMNI_PCF

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	#ifdef PHONG
		float3 texcoord_2 : TEXCOORD2;
	#endif
	float3 texcoord_3 : TEXCOORD3;
	#ifdef SHADOW
		float4 texcoord_4 : TEXCOORD4;
		#ifdef USE_TRANSLUCENT
			float3 texcoord_5 : TEXCOORD5;
		#endif
	#endif
	#ifdef NOISE
		float3 texcoord_6 : TEXCOORD6;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

cbuffer shader_parameters {
	float translucent_scale;
	float thickness_scale;
	#ifdef NOISE
		float noise_scale;
	#endif
	float4 color_scale;
};

/*
 */
FRAGMENT_ALPHA_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_ALPHA_OUT OUT;
	
	#include <core/shaders/meshes/fragment_leaf_light.h>
	
	SHADOW_OMNI_PCF
	
	color *= s_texture_11.Sample(s_sampler_11,IN.texcoord_3).xyz;
	OUT.color = float4(color * s_light_color.xyz,diffuse.w) * color_scale;
	
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
uniform sampler2D s_texture_2 : TEXUNIT2;
uniform sampler2D s_texture_3 : TEXUNIT3;
uniform sampler3D s_texture_4 : TEXUNIT4;
uniform sampler2D s_texture_5 : TEXUNIT5;

uniform samplerCUBE s_texture_11 : TEXUNIT11;
SAMPLER_SHADOW_OMNI_PCF

struct FRAGMENT_IN {
	float2 position : WPOS;
	float4 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
	#ifdef PHONG
		half3 texcoord_2 : TEXCOORD2;
	#endif
	half3 texcoord_3 : TEXCOORD3;
	#ifdef SHADOW
		float4 texcoord_4 : TEXCOORD4;
		#ifdef USE_TRANSLUCENT
			float3 texcoord_5 : TEXCOORD5;
		#endif
	#endif
	#ifdef NOISE
		float3 texcoord_8 : TEXCOORD8;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half translucent_scale;
uniform half thickness_scale;
uniform half noise_scale;
uniform half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_leaf_light.h>
	
	SHADOW_OMNI_PCF
	
	color *= h3texCUBE(s_texture_11,IN.texcoord_3);
	return half4(color * s_light_color.xyz,diffuse.w) * color_scale;
}

#endif
