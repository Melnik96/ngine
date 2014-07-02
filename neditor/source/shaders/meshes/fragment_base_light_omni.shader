/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_light_omni.shader
 * Desc:    Mesh base light omni shader
 * Version: 1.23
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
 * s_texture_1 is normal texture
 * s_texture_2 is specular texture
 * s_texture_3 is detail diffuse texture
 * s_texture_4 is detail normal texture
 * s_texture_5 is detail specular texture
 * 
 * s_texture_9 is alpha fade texture
 * s_texture_10 is deferred parallax texture
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
uniform sampler2D s_texture_4;
uniform sampler2D s_texture_5;

uniform sampler2D s_texture_9;
uniform SAMPLER_2DMS s_texture_10;
uniform samplerCube s_texture_11;
SAMPLER_SHADOW_OMNI_PCF

uniform half4 detail_transform;
uniform half4 color_scale;

/*
 */
void main() {
	
	#include <core/shaders/meshes/fragment_base_light.h>
	
	SHADOW_OMNI_PCF
	
	#ifdef USE_TESSELLATION && TESSELLATION
		color *= textureCube(s_texture_11,(half4(gl_TexCoord[3].xyz - s_light_position,0.0f) * s_light_transform).xyz).xyz;
	#else
		color *= textureCube(s_texture_11,gl_TexCoord[3].xyz).xyz;
	#endif
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
	half3 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	#ifdef SHADOW
		float4 texcoord_4 : TEXCOORD4;
		#ifdef USE_TRANSLUCENT
			float3 texcoord_5 : TEXCOORD5;
		#endif
	#endif
	#ifdef (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half4 detail_transform;
half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_base_light.h>
	
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
Texture2D s_texture_4 : register(t4);
Texture2D s_texture_5 : register(t5);

Texture2D s_texture_9 : register(t9);
TEXTURE_2DMS s_texture_10 : register(t10);
TextureCube s_texture_11 : register(t11);
TEXTURE_SHADOW_OMNI_PCF

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	#ifdef USE_TESSELLATION && TESSELLATION
		float3 texcoord_1 : TEXCOORD1;
		float4 texcoord_2 : TEXCOORD2;
		float3 texcoord_3 : TEXCOORD3;
	#else
		float4 texcoord_1 : TEXCOORD1;
		float3 texcoord_2 : TEXCOORD2;
		float3 texcoord_3 : TEXCOORD3;
		#ifdef SHADOW
			float4 texcoord_4 : TEXCOORD4;
			#ifdef USE_TRANSLUCENT
				float3 texcoord_5 : TEXCOORD5;
			#endif
		#endif
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

cbuffer shader_parameters {
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		float4 detail_transform;
	#endif
	float4 color_scale;
};

/*
 */
FRAGMENT_ALPHA_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_ALPHA_OUT OUT;
	
	#include <core/shaders/meshes/fragment_base_light.h>
	
	SHADOW_OMNI_PCF
	
	#ifdef USE_TESSELLATION && TESSELLATION
		color *= s_texture_11.Sample(s_sampler_11,mul(IN.texcoord_3 - s_light_position,(float3x3)s_light_transform)).xyz;
	#else
		color *= s_texture_11.Sample(s_sampler_11,IN.texcoord_3).xyz;
	#endif
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
uniform sampler2D s_texture_4 : TEXUNIT4;
uniform sampler2D s_texture_5 : TEXUNIT5;

uniform sampler2D s_texture_9 : TEXUNIT9;
uniform sampler2D s_texture_10 : TEXUNIT10;
uniform samplerCUBE s_texture_11 : TEXUNIT11;
SAMPLER_SHADOW_OMNI_PCF

struct FRAGMENT_IN {
	float2 position : WPOS;
	float4 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	#ifdef SHADOW
		float4 texcoord_4 : TEXCOORD4;
		#ifdef USE_TRANSLUCENT
			float3 texcoord_5 : TEXCOORD5;
		#endif
	#endif
	#ifdef (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half4 detail_transform;
uniform half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_base_light.h>
	
	SHADOW_OMNI_PCF
	
	color *= h3texCUBE(s_texture_11,IN.texcoord_3);
	return half4(color * s_light_color.xyz,diffuse.w) * color_scale;
}

#endif
