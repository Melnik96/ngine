/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_surface_refraction.shader
 * Desc:    Water surface refraction shader
 * Version: 1.09
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

uniform sampler2D s_texture_0;
uniform sampler2D s_texture_1;

uniform SAMPLER_2DMS s_texture_12;

uniform float3 s_water_direction;

uniform half reflection_normal;
uniform half refraction_scale;
uniform half surface_power;

/*
 */
void main() {
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	half2 screen_normal;
	screen_normal.x = dot(normalize(half3(gl_TexCoord[3].xyz)).xy,normal.xy);
	screen_normal.y = dot(normalize(half3(gl_TexCoord[4].xyz)).xy,normal.xy);
	
	half4 color = saturate(half4(screen_normal,-screen_normal));
	
	gl_FragColor = color * (refraction_scale * saturate(gl_TexCoord[0].z / gl_TexCoord[0].w) * saturate(fog * 4.0f)) + 1.0f / 255.0f;
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
	half3 texcoord_4 : TEXCOORD4;
	float4 texcoord_5 : TEXCOORD5;
	float4 texcoord_6 : TEXCOORD6;
	float4 texcoord_7 : TEXCOORD7;
};

float3 s_water_direction;

half reflection_normal;
half refraction_scale;
half surface_power;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	half2 screen_normal;
	screen_normal.x = dot(normalize(IN.texcoord_3).xy,normal.xy);
	screen_normal.y = dot(normalize(IN.texcoord_4).xy,normal.xy);
	
	half4 color = saturate(half4(screen_normal,-screen_normal));
	
	return color * (refraction_scale * saturate(IN.texcoord_0.z / IN.texcoord_0.w) * saturate(fog * 4.0f)) + 1.0f / 255.0f;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
Texture2D s_texture_1 : register(t1);

TEXTURE_2DMS s_texture_12 : register(t12);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	float4 texcoord_7 : TEXCOORD7;
	float4 texcoord_8 : TEXCOORD8;
};

cbuffer shader_water_parameters {
	float3 s_water_direction;
};

cbuffer shader_parameters {
	float reflection_normal;
	float refraction_scale;
	float surface_power;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	half2 screen_normal;
	screen_normal.x = dot(normalize(IN.texcoord_3).xy,normal.xy);
	screen_normal.y = dot(normalize(IN.texcoord_4).xy,normal.xy);
	
	half4 color = saturate(half4(screen_normal,-screen_normal));
	
	return color * (refraction_scale * saturate(IN.texcoord_0.z / IN.texcoord_0.w) * saturate(fog * 4.0f)) + 1.0f / 255.0f;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_0 : TEXUNIT0;
uniform sampler2D s_texture_1 : TEXUNIT1;

uniform sampler2D s_texture_12 : TEXUNIT12;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	float4 texcoord_7 : TEXCOORD7;
	float4 texcoord_8 : TEXCOORD8;
	float4 texcoord_9 : TEXCOORD9;
};

uniform float3 s_water_direction;

uniform half reflection_normal;
uniform half refraction_scale;
uniform half surface_power;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	half2 screen_normal;
	screen_normal.x = dot(normalize(IN.texcoord_3).xy,normal.xy);
	screen_normal.y = dot(normalize(IN.texcoord_4).xy,normal.xy);
	
	half4 color = saturate(half4(screen_normal,-screen_normal));
	
	return color * (refraction_scale * saturate(IN.texcoord_0.z / IN.texcoord_0.w) * saturate(fog * 4.0f)) + 1.0f / 255.0f;
}

#endif
