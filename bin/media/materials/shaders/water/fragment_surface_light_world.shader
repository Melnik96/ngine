/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_surface_light_world.shader
 * Desc:    Water surface light world shader
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

/* s_texture_0 is normal_01 texture
 * s_texture_1 is normal_23 texture
 * s_texture_2 is foam texture
 * 
 * s_texture_12 is deferred depth texture
 * s_texture_14 is light shadow depth texture
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

uniform SAMPLER_2DMS s_texture_12;
uniform SAMPLER_SHADOW_DEPTH_WORLD s_texture_14;

uniform float3 s_water_direction;

uniform half4 normal_0_transform;
uniform half4 normal_1_transform;
uniform half4 normal_2_transform;
uniform half4 normal_3_transform;
uniform half4 foam_0_transform;
uniform half4 foam_1_transform;
uniform half reflection_normal;
uniform half4 reflection_color;
uniform half4 surface_color;
uniform half foam_scale;
uniform half foam_threshold;
uniform half foam_falloff;

/*
 */
void main() {
	
	#include <core/shaders/water/fragment_surface_light.h>
	
	#include <core/shaders/water/fragment_surface_foam.h>
	
	#ifdef QUALITY_MEDIUM
		#ifdef SHADOW
			color *= shadowWorld(s_texture_14,gl_TexCoord[6],s_material_textures[14]);
		#endif
	#endif
	
	gl_FragColor = half4(color * s_light_color.xyz * fog,1.0f);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	#ifdef SHADOW
		float4 texcoord_6 : TEXCOORD6;
	#endif
	float4 texcoord_7 : TEXCOORD7;
};

float3 s_water_direction;

half4 normal_0_transform;
half4 normal_1_transform;
half4 normal_2_transform;
half4 normal_3_transform;
half4 foam_0_transform;
half4 foam_1_transform;
half reflection_normal;
half4 reflection_color;
half4 surface_color;
half foam_scale;
half foam_threshold;
half foam_falloff;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/water/fragment_surface_light.h>
	
	#include <core/shaders/water/fragment_surface_foam.h>
	
	#ifdef QUALITY_MEDIUM
		#ifdef SHADOW
			color *= shadowWorld(s_texture_14,IN.texcoord_6,s_material_textures[14]);
		#endif
	#endif
	
	return half4(color * s_light_color.xyz * fog,1.0f);
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

TEXTURE_2DMS s_texture_12 : register(t12);
TEXTURE_SHADOW_WORLD s_texture_14 : register(t14);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	#ifdef SHADOW
		float4 texcoord_6 : TEXCOORD6;
	#endif
	float4 texcoord_7 : TEXCOORD7;
	float4 texcoord_8 : TEXCOORD8;
	float4 texcoord_9 : TEXCOORD9;
};

cbuffer shader_water_parameters {
	float3 s_water_direction;
};

cbuffer shader_parameters {
	float reflection_normal;
	float4 reflection_color;
	float4 surface_color;
	float foam_scale;
	float foam_threshold;
	float foam_falloff;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#include <core/shaders/water/fragment_surface_light.h>
	
	#include <core/shaders/water/fragment_surface_foam.h>
	
	#ifdef QUALITY_MEDIUM
		#ifdef SHADOW
			color *= shadowWorld(s_texture_14,s_sampler_14,s_sampler_compare_14,IN.texcoord_6,s_material_textures[14]);
		#endif
	#endif
	
	return float4(color * s_light_color.xyz * fog,1.0f);
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

uniform sampler2D s_texture_12 : TEXUNIT12;
uniform SAMPLER_SHADOW_WORLD s_texture_14 : TEXUNIT14;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	#ifdef SHADOW
		float4 texcoord_6 : TEXCOORD6;
	#endif
	float4 texcoord_7 : TEXCOORD7;
	float4 texcoord_8 : TEXCOORD8;
	float4 texcoord_9 : TEXCOORD9;
};

uniform float3 s_water_direction;

uniform half4 foam_0_transform;
uniform half4 foam_1_transform;
uniform half reflection_normal;
uniform half4 reflection_color;
uniform half4 surface_color;
uniform half foam_scale;
uniform half foam_threshold;
uniform half foam_falloff;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/water/fragment_surface_light.h>
	
	#include <core/shaders/water/fragment_surface_foam.h>
	
	#ifdef QUALITY_MEDIUM
		#ifdef SHADOW
			color *= shadowWorld(s_texture_14,IN.texcoord_6);
		#endif
	#endif
	
	return half4(color * s_light_color.xyz * fog,1.0f);
}

#endif
