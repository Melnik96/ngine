/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_paint_light_prob.shader
 * Desc:    Mesh paint light prob shader
 * Version: 1.06
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
 * s_texture_10 is fleck noise texture
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
uniform sampler3D s_texture_10;

uniform half4 detail_transform;
uniform half diffuse_0_power;
uniform half diffuse_1_power;
uniform half diffuse_2_power;
uniform half4 diffuse_0_color;
uniform half4 diffuse_1_color;
uniform half4 diffuse_2_color;
uniform half4 color_scale;

uniform half fleck_size;
uniform half fleck_power;
uniform half fleck_radius;
uniform half4 fleck_color;

/*
 */
void main() {
	
	#include <core/shaders/meshes/fragment_paint_sample.h>
	
	half3 color = diffuse.xyz * getEnvironment(world_normal) * s_material_shading.x;
	
	#ifdef QUALITY_MEDIUM
		half fresnel = getFresnel(world_normal,camera_direction);
		color += specular.xyz * getEnvironment(reflect(-camera_direction,world_normal)) * (s_material_shading.y * fresnel);
		color *= 0.5f;
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
	half3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	#ifdef FLECK
		float3 texcoord_6 : TEXCOORD6;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half4 detail_transform;
half diffuse_0_power;
half diffuse_1_power;
half diffuse_2_power;
half4 diffuse_0_color;
half4 diffuse_1_color;
half4 diffuse_2_color;
half4 color_scale;

half fleck_size;
half fleck_power;
half fleck_radius;
half4 fleck_color;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_paint_sample.h>
	
	half3 color = diffuse.xyz * getEnvironment(world_normal) * s_material_shading.x;
	
	#ifdef QUALITY_MEDIUM
		half fresnel = getFresnel(world_normal,camera_direction);
		color += specular.xyz * getEnvironment(reflect(-camera_direction,world_normal)) * (s_material_shading.y * fresnel);
		color *= 0.5f;
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
Texture2D s_texture_1 : register(t1);
Texture2D s_texture_2 : register(t2);
Texture2D s_texture_3 : register(t3);
Texture2D s_texture_4 : register(t4);
Texture2D s_texture_5 : register(t5);

Texture2D s_texture_9 : register(t9);
Texture3D s_texture_10 : register(t10);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	#ifdef USE_TESSELLATION && TESSELLATION
		float3 texcoord_1 : TEXCOORD1;
		float4 texcoord_2 : TEXCOORD2;
		float3 texcoord_3 : TEXCOORD3;
	#else
		float3 texcoord_1 : TEXCOORD1;
		float3 texcoord_2 : TEXCOORD2;
		float3 texcoord_3 : TEXCOORD3;
		float3 texcoord_4 : TEXCOORD4;
		#ifdef FLECK
			float3 texcoord_6 : TEXCOORD6;
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
	float diffuse_0_power;
	float diffuse_1_power;
	float diffuse_2_power;
	float4 diffuse_0_color;
	float4 diffuse_1_color;
	float4 diffuse_2_color;
	float4 color_scale;
	#ifdef FLECK
		float fleck_size;
		float fleck_power;
		float fleck_radius;
		float4 fleck_color;
	#endif
};

/*
 */
FRAGMENT_ALPHA_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_ALPHA_OUT OUT;
	
	#include <core/shaders/meshes/fragment_paint_sample.h>
	
	half3 color = diffuse.xyz * getEnvironment(world_normal) * s_material_shading.x;
	
	#ifdef QUALITY_MEDIUM
		half fresnel = getFresnel(world_normal,camera_direction);
		color += specular.xyz * getEnvironment(reflect(-camera_direction,world_normal)) * (s_material_shading.y * fresnel);
		color *= 0.5f;
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
uniform sampler2D s_texture_1 : TEXUNIT1;
uniform sampler2D s_texture_2 : TEXUNIT2;
uniform sampler2D s_texture_3 : TEXUNIT3;
uniform sampler2D s_texture_4 : TEXUNIT4;
uniform sampler2D s_texture_5 : TEXUNIT5;

uniform sampler2D s_texture_9 : TEXUNIT9;
uniform sampler3D s_texture_10 : TEXUNIT10;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	#ifdef FLECK
		float3 texcoord_8 : TEXCOORD8;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half4 detail_transform;
uniform half diffuse_0_power;
uniform half diffuse_1_power;
uniform half diffuse_2_power;
uniform half4 diffuse_0_color;
uniform half4 diffuse_1_color;
uniform half4 diffuse_2_color;
uniform half4 color_scale;

uniform half fleck_size;
uniform half fleck_power;
uniform half fleck_radius;
uniform half4 fleck_color;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_paint_sample.h>
	
	half3 color = diffuse.xyz * getEnvironment(world_normal) * s_material_shading.x;
	
	#ifdef QUALITY_MEDIUM
		half fresnel = getFresnel(world_normal,camera_direction);
		color += specular.xyz * getEnvironment(reflect(-camera_direction,world_normal)) * (s_material_shading.y * fresnel);
		color *= 0.5f;
	#endif
	
	return half4(color,diffuse.w) * color_scale;
}

#endif
