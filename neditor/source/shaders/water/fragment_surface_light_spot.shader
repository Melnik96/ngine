/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_surface_light_spot.shader
 * Desc:    Water surface light spot shader
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

uniform half4 normal_0_transform;
uniform half4 normal_1_transform;
uniform half4 normal_2_transform;
uniform half4 normal_3_transform;
uniform half reflection_normal;
uniform half4 reflection_color;
uniform half4 surface_color;

/*
 */
void main() {
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	half3 color = half3(0.0f);
	
	half3 world_normal;
	world_normal.x = dot(half3(gl_TexCoord[4].xyz),normal);
	world_normal.y = dot(half3(gl_TexCoord[5].xyz),normal);
	world_normal.z = dot(half3(gl_TexCoord[6].xyz),normal);
	
	half3 camera_direction = normalize(s_camera_position - gl_TexCoord[3].xyz);
	half fresnel = getFresnel(world_normal,camera_direction);
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - gl_TexCoord[3].xyz) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half3 light = surface_color.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength) * (1.0f - fresnel) * s_material_shadings[NUMBER].x); \
		light += reflection_color.xyz * (pow(saturate(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength),s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
		color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
	gl_FragColor = half4(color * fog,1.0f);
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
	float4 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	half3 texcoord_5 : TEXCOORD5;
	half3 texcoord_6 : TEXCOORD6;
	float4 texcoord_7 : TEXCOORD7;
};

float3 s_water_direction;

half4 normal_0_transform;
half4 normal_1_transform;
half4 normal_2_transform;
half4 normal_3_transform;
half reflection_normal;
half4 reflection_color;
half4 surface_color;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	half3 color = 0.0f;
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_4,normal);
	world_normal.y = dot(IN.texcoord_5,normal);
	world_normal.z = dot(IN.texcoord_6,normal);
	
	half3 camera_direction = normalize(s_camera_position - IN.texcoord_3.xyz);
	half fresnel = getFresnel(world_normal,camera_direction);
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - IN.texcoord_3.xyz) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half3 light = surface_color.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength) * (1.0f - fresnel) * s_material_shadings[NUMBER].x); \
		light += reflection_color.xyz * (pow(saturate(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength),s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
		color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
	return half4(color * fog,1.0f);
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
	float4 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	float3 texcoord_5 : TEXCOORD5;
	float3 texcoord_6 : TEXCOORD6;
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
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	half3 color = 0.0f;
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_4,normal);
	world_normal.y = dot(IN.texcoord_5,normal);
	world_normal.z = dot(IN.texcoord_6,normal);
	
	half3 camera_direction = normalize(s_camera_position - IN.texcoord_3.xyz);
	half fresnel = getFresnel(world_normal,camera_direction);
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - IN.texcoord_3.xyz) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half3 light = surface_color.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength) * (1.0f - fresnel) * s_material_shadings[NUMBER].x); \
		light += reflection_color.xyz * (pow(saturate(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength),s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
		color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
	return float4(color * fog,1.0f);
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
	float4 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	half3 texcoord_5 : TEXCOORD5;
	half3 texcoord_6 : TEXCOORD6;
	float4 texcoord_7 : TEXCOORD7;
	float4 texcoord_8 : TEXCOORD8;
	float4 texcoord_9 : TEXCOORD9;
};

uniform float3 s_water_direction;

uniform half reflection_normal;
uniform half4 reflection_color;
uniform half4 surface_color;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	half3 color = 0.0f;
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_4,normal);
	world_normal.y = dot(IN.texcoord_5,normal);
	world_normal.z = dot(IN.texcoord_6,normal);
	
	half3 camera_direction = normalize(s_camera_position - IN.texcoord_3.xyz);
	half fresnel = getFresnel(world_normal,camera_direction);
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - IN.texcoord_3.xyz) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half3 light = surface_color.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength) * (1.0f - fresnel) * s_material_shadings[NUMBER].x); \
		light += reflection_color.xyz * (pow(saturate(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength),s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
		color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
	return half4(color * fog,1.0f);
}

#endif
