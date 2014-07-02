/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_light_spot.shader
 * Desc:    Terrain base light spot shader
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

uniform half s_terrain_diffuse_texcoord;
uniform half s_terrain_normal_texcoord;
uniform half4 s_terrain_diffuse_scale;
uniform half4 s_terrain_normal_scale;
uniform half4 s_terrain_transform_1;
uniform half4 s_terrain_transform_2;
uniform half4 s_terrain_transform_3;
uniform half4 s_terrain_transform_4;

/*
 */
void main() {
	
	#include <core/shaders/terrains/fragment_base_sample.h>
	
	half3 color = half3(0.0f);
	
	half3 world_normal;
	world_normal.x = dot(half3(gl_TexCoord[3].xyz),normal);
	world_normal.y = dot(half3(gl_TexCoord[4].xyz),normal);
	world_normal.z = dot(half3(gl_TexCoord[5].xyz),normal);
	
	half3 camera_direction = normalize(half3(gl_TexCoord[2].xyz));
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - gl_TexCoord[1].xyz) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half3 light = diffuse.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength) * s_material_shadings[NUMBER].x); \
		light += specular * (pow(saturate(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength),s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
		color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
	gl_FragColor = half4(color,1.0f);
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
	float3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	half3 texcoord_5 : TEXCOORD5;
	#ifdef PATCH
		half2 texcoord_6 : TEXCOORD6;
	#endif
};

half s_terrain_diffuse_texcoord;
half s_terrain_normal_texcoord;
half4 s_terrain_diffuse_scale;
half4 s_terrain_normal_scale;
half4 s_terrain_transform_1;
half4 s_terrain_transform_2;
half4 s_terrain_transform_3;
half4 s_terrain_transform_4;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/terrains/fragment_base_sample.h>
	
	half3 color = 0.0f;
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_3,normal);
	world_normal.y = dot(IN.texcoord_4,normal);
	world_normal.z = dot(IN.texcoord_5,normal);
	
	half3 camera_direction = normalize(IN.texcoord_2);
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - IN.texcoord_1) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half3 light = diffuse.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength) * s_material_shadings[NUMBER].x); \
		light += specular * (pow(saturate(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength),s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
		color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
	return half4(color,1.0f);
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

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	float3 texcoord_5 : TEXCOORD5;
	#ifdef PATCH
		float2 texcoord_6 : TEXCOORD6;
	#endif
};

cbuffer shader_terrain_parameters {
	float s_terrain_diffuse_texcoord;
	float s_terrain_normal_texcoord;
	float4 s_terrain_diffuse_scale;
	float4 s_terrain_normal_scale;
	float4 s_terrain_transform_1;
	float4 s_terrain_transform_2;
	float4 s_terrain_transform_3;
	float4 s_terrain_transform_4;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#include <core/shaders/terrains/fragment_base_sample.h>
	
	half3 color = 0.0f;
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_3,normal);
	world_normal.y = dot(IN.texcoord_4,normal);
	world_normal.z = dot(IN.texcoord_5,normal);
	
	half3 camera_direction = normalize(IN.texcoord_2);
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - IN.texcoord_1) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half3 light = diffuse.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength) * s_material_shadings[NUMBER].x); \
		light += specular * (pow(saturate(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength),s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
		color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
	return float4(color,1.0f);
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

struct FRAGMENT_IN {
	float2 position : WPOS;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	half3 texcoord_5 : TEXCOORD5;
	#ifdef PATCH
		half2 texcoord_8 : TEXCOORD8;
	#endif
};

uniform half s_terrain_diffuse_texcoord;
uniform half s_terrain_normal_texcoord;
uniform half4 s_terrain_diffuse_scale;
uniform half4 s_terrain_normal_scale;
uniform half4 s_terrain_transform_1;
uniform half4 s_terrain_transform_2;
uniform half4 s_terrain_transform_3;
uniform half4 s_terrain_transform_4;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/terrains/fragment_base_sample.h>
	
	half3 color = 0.0f;
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_3,normal);
	world_normal.y = dot(IN.texcoord_4,normal);
	world_normal.z = dot(IN.texcoord_5,normal);
	
	half3 camera_direction = normalize(IN.texcoord_2);
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - IN.texcoord_1) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half3 light = diffuse.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength) * s_material_shadings[NUMBER].x); \
		light += specular * (pow(saturate(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength),s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
		color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
	return half4(color,1.0f);
}

#endif
