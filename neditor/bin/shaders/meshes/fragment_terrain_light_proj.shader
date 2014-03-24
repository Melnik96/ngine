/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_terrain_light_proj.shader
 * Desc:    Mesh terrain light proj shader
 * Version: 1.02
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
 * s_texture_2 is mask texture
 * s_texture_3 is detail_1 diffuse texture
 * s_texture_4 is detail_1 normal texture
 * s_texture_5 is detail_2 diffuse texture
 * s_texture_6 is detail_2 normal texture
 * s_texture_7 is detail_3 diffuse texture
 * s_texture_8 is detail_3 normal texture
 * s_texture_9 is detail_4 diffuse texture
 * s_texture_10 is detail_4 normal texture
 * 
 * s_texture_11 is light modulation texture
 * s_texture_12 is light shadow color texture
 * s_texture_13 is light shadow depth texture
 * s_texture_14 is light shadow noise texture
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
uniform sampler2D s_texture_6;
uniform sampler2D s_texture_7;
uniform sampler2D s_texture_8;
uniform sampler2D s_texture_9;
uniform sampler2D s_texture_10;

uniform sampler2D s_texture_11;
SAMPLER_SHADOW_PROJ_PCF

uniform half4 detail_1_transform;
uniform half4 detail_2_transform;
uniform half4 detail_3_transform;
uniform half4 detail_4_transform;
uniform half detail_1_diffuse;
uniform half detail_1_normal;
uniform half detail_2_diffuse;
uniform half detail_2_normal;
uniform half detail_3_diffuse;
uniform half detail_3_normal;
uniform half detail_4_diffuse;
uniform half detail_4_normal;

/*
 */
void main() {
	
	#include <core/shaders/meshes/fragment_terrain_light.h>
	
	SHADOW_PROJ_PCF
	
	color *= half(half(gl_TexCoord[3].z) > 0.0f);
	color *= texture2DProj(s_texture_11,gl_TexCoord[3]).xyz;
	gl_FragColor = half4(color * s_light_color.xyz,1.0f);
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
	float4 texcoord_3 : TEXCOORD3;
	#ifdef SHADOW
		float4 texcoord_4 : TEXCOORD4;
		#ifdef USE_TRANSLUCENT
			float1 texcoord_5 : TEXCOORD5;
		#endif
	#endif
};

half4 detail_1_transform;
half4 detail_2_transform;
half4 detail_3_transform;
half4 detail_4_transform;
half detail_1_diffuse;
half detail_1_normal;
half detail_2_diffuse;
half detail_2_normal;
half detail_3_diffuse;
half detail_3_normal;
half detail_4_diffuse;
half detail_4_normal;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_terrain_light.h>
	
	SHADOW_PROJ_PCF
	
	color *= (IN.texcoord_3.z > 0.0f);
	color *= tex2Dproj(s_texture_11,IN.texcoord_3).xyz;
	return half4(color * s_light_color.xyz,1.0f);
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
Texture2D s_texture_6 : register(t6);
Texture2D s_texture_7 : register(t7);
Texture2D s_texture_8 : register(t8);
Texture2D s_texture_9 : register(t9);
Texture2D s_texture_10 : register(t10);

Texture2D s_texture_11 : register(t11);
TEXTURE_SHADOW_PROJ_PCF

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	#ifdef SHADOW
		float4 texcoord_4 : TEXCOORD4;
		#ifdef USE_TRANSLUCENT
			float1 texcoord_5 : TEXCOORD5;
		#endif
	#endif
};

cbuffer shader_parameters {
	#ifdef DETAIL_1 || DETAIL_2 || DETAIL_3 || DETAIL_4
		float4 detail_1_transform;
		float detail_1_diffuse;
		float detail_1_normal;
	#endif
	#ifdef DETAIL_2 || DETAIL_3 || DETAIL_4
		float4 detail_2_transform;
		float detail_2_diffuse;
		float detail_2_normal;
	#endif
	#ifdef DETAIL_3 || DETAIL_4
		float4 detail_3_transform;
		float detail_3_diffuse;
		float detail_3_normal;
	#endif
	#ifdef DETAIL_4
		float4 detail_4_transform;
		float detail_4_diffuse;
		float detail_4_normal;
	#endif
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#include <core/shaders/meshes/fragment_terrain_light.h>
	
	SHADOW_PROJ_PCF
	
	color *= (IN.texcoord_3.z > 0.0f);
	color *= s_texture_11.Sample(s_sampler_11,IN.texcoord_3.xy / IN.texcoord_3.w).xyz;
	return float4(color * s_light_color.xyz,1.0f);
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
uniform sampler2D s_texture_6 : TEXUNIT6;
uniform sampler2D s_texture_7 : TEXUNIT7;
uniform sampler2D s_texture_8 : TEXUNIT8;
uniform sampler2D s_texture_9 : TEXUNIT9;
uniform sampler2D s_texture_10 : TEXUNIT10;

uniform sampler2D s_texture_11 : TEXUNIT11;
SAMPLER_SHADOW_PROJ_PCF

struct FRAGMENT_IN {
	float2 position : WPOS;
	float4 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	#ifdef SHADOW
		float4 texcoord_4 : TEXCOORD4;
		#ifdef USE_TRANSLUCENT
			float1 texcoord_5 : TEXCOORD5;
		#endif
	#endif
};

uniform half4 detail_1_transform;
uniform half4 detail_2_transform;
uniform half4 detail_3_transform;
uniform half4 detail_4_transform;
uniform half detail_1_diffuse;
uniform half detail_1_normal;
uniform half detail_2_diffuse;
uniform half detail_2_normal;
uniform half detail_3_diffuse;
uniform half detail_3_normal;
uniform half detail_4_diffuse;
uniform half detail_4_normal;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_terrain_light.h>
	
	SHADOW_PROJ_PCF
	
	color *= (IN.texcoord_3.z > 0.0f);
	color *= h3tex2Dproj(s_texture_11,IN.texcoord_3.xyw);
	return half4(color * s_light_color.xyz,1.0f);
}

#endif
