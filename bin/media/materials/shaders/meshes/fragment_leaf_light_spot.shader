/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_leaf_light_spot.shader
 * Desc:    Mesh leaf light spot shader
 * Version: 1.04
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

uniform half translucent_scale;
uniform half thickness_scale;
uniform half noise_scale;
uniform half4 color_scale;

/*
 */
void main() {
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	half3 color = half3(0.0f);
	
	half thickness = texture2D(s_texture_1,gl_TexCoord[0].xy).x;
	half offset = saturate(translucent_scale - thickness * thickness_scale);
	
	#ifdef QUALITY_MEDIUM && PHONG
		half3 normal = texture2DNormal(s_texture_2,gl_TexCoord[0].xy);
		half4 specular = texture2D(s_texture_3,gl_TexCoord[0].xy);
		
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
			half3 light = diffuse.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength * (1.0f - offset) + offset) * s_material_shadings[NUMBER].x); \
			light += specular.xyz * (getSpecularPower(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength,specular.w * s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
			color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
		}
	#else
		#define LIGHT(NUMBER,SWIZZLE) { \
			half3 light_direction = (s_light_positions[NUMBER].xyz - gl_TexCoord[1].xyz) * s_light_iradiuses. ## SWIZZLE; \
			half light_direction_length2 = dot(light_direction,light_direction); \
			half light_direction_ilength = rsqrt(light_direction_length2); \
			half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
			half3 light = diffuse.xyz * (saturate(dot(light_direction,half3(gl_TexCoord[2].xyz)) * light_direction_ilength * (1.0f - offset) + offset) * s_material_shadings[NUMBER].x); \
			color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
		}
	#endif
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
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
	half3 texcoord_2 : TEXCOORD2;
	#ifdef QUALITY_MEDIUM && PHONG
		half3 texcoord_3 : TEXCOORD3;
		half3 texcoord_4 : TEXCOORD4;
		half3 texcoord_5 : TEXCOORD5;
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
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	half3 color = 0.0f;
	
	half thickness = tex2D(s_texture_1,IN.texcoord_0.xy).x;
	half offset = saturate(translucent_scale - thickness * thickness_scale);
	
	#ifdef QUALITY_MEDIUM && PHONG
		half3 normal = tex2DNormal(s_texture_2,IN.texcoord_0.xy);
		half4 specular = tex2D(s_texture_3,IN.texcoord_0.xy);
		
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
			half3 light = diffuse.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength * (1.0f - offset) + offset) * s_material_shadings[NUMBER].x); \
			light += specular.xyz * (getSpecularPower(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength,specular.w * s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
			color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
		}
	#else
		#define LIGHT(NUMBER,SWIZZLE) { \
			half3 light_direction = (s_light_positions[NUMBER].xyz - IN.texcoord_1) * s_light_iradiuses. ## SWIZZLE; \
			half light_direction_length2 = dot(light_direction,light_direction); \
			half light_direction_ilength = rsqrt(light_direction_length2); \
			half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
			half3 light = diffuse.xyz * (saturate(dot(light_direction,IN.texcoord_2) * light_direction_ilength * (1.0f - offset) + offset) * s_material_shadings[NUMBER].x); \
			color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
		}
	#endif
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
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
Texture3D s_texture_4 : register(t4);
Texture2D s_texture_5 : register(t5);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	#ifdef QUALITY_MEDIUM && PHONG
		float3 texcoord_3 : TEXCOORD3;
		float3 texcoord_4 : TEXCOORD4;
		float3 texcoord_5 : TEXCOORD5;
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
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	float3 color = 0.0f;
	
	float thickness = s_texture_1.Sample(s_sampler_1,IN.texcoord_0.xy).x;
	float offset = saturate(translucent_scale - thickness * thickness_scale);
	
	#ifdef QUALITY_MEDIUM && PHONG
		float3 normal = texture2DNormal(s_texture_2,s_sampler_2,IN.texcoord_0.xy);
		float4 specular = s_texture_3.Sample(s_sampler_3,IN.texcoord_0.xy);
		
		float3 world_normal;
		world_normal.x = dot(IN.texcoord_3,normal);
		world_normal.y = dot(IN.texcoord_4,normal);
		world_normal.z = dot(IN.texcoord_5,normal);
		
		float3 camera_direction = normalize(IN.texcoord_2);
		
		#define LIGHT(NUMBER,SWIZZLE) { \
			float3 light_direction = (s_light_positions[NUMBER].xyz - IN.texcoord_1) * s_light_iradiuses. ## SWIZZLE; \
			float light_direction_length2 = dot(light_direction,light_direction); \
			float light_direction_ilength = rsqrt(light_direction_length2); \
			float light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
			float3 light = diffuse.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength * (1.0f - offset) + offset) * s_material_shadings[NUMBER].x); \
			light += specular.xyz * (getSpecularPower(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength,specular.w * s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
			color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
		}
	#else
		#define LIGHT(NUMBER,SWIZZLE) { \
			float3 light_direction = (s_light_positions[NUMBER].xyz - IN.texcoord_1) * s_light_iradiuses. ## SWIZZLE; \
			float light_direction_length2 = dot(light_direction,light_direction); \
			float light_direction_ilength = rsqrt(light_direction_length2); \
			float light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
			float3 light = diffuse.xyz * (saturate(dot(light_direction,IN.texcoord_2) * light_direction_ilength * (1.0f - offset) + offset) * s_material_shadings[NUMBER].x); \
			color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
		}
	#endif
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
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
uniform sampler3D s_texture_4 : TEXUNIT4;
uniform sampler2D s_texture_5 : TEXUNIT5;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	#ifdef QUALITY_MEDIUM && PHONG
		half3 texcoord_3 : TEXCOORD3;
		half3 texcoord_4 : TEXCOORD4;
		half3 texcoord_5 : TEXCOORD5;
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
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	half3 color = 0.0f;
	
	half thickness = h1tex2D(s_texture_1,IN.texcoord_0.xy);
	half offset = saturate(translucent_scale - thickness * thickness_scale);
	
	#ifdef QUALITY_MEDIUM && PHONG
		half3 normal = tex2DNormal(s_texture_2,IN.texcoord_0.xy);
		half4 specular = h4tex2D(s_texture_3,IN.texcoord_0.xy);
		
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
			half3 light = diffuse.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength * (1.0f - offset) + offset) * s_material_shadings[NUMBER].x); \
			light += specular.xyz * (getSpecularPower(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength,specular.w * s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
			color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
		}
	#else
		#define LIGHT(NUMBER,SWIZZLE) { \
			half3 light_direction = (s_light_positions[NUMBER].xyz - IN.texcoord_1) * s_light_iradiuses. ## SWIZZLE; \
			half light_direction_length2 = dot(light_direction,light_direction); \
			half light_direction_ilength = rsqrt(light_direction_length2); \
			half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
			half3 light = diffuse.xyz * (saturate(dot(light_direction,IN.texcoord_2) * light_direction_ilength * (1.0f - offset) + offset) * s_material_shadings[NUMBER].x); \
			color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
		}
	#endif
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
	return half4(color,diffuse.w) * color_scale;
}

#endif
