/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_volume_light_world.shader
 * Desc:    Water volume light world shader
 * Version: 1.16
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

uniform SAMPLER_2DMS s_texture_12;
uniform SAMPLER_SHADOW_DEPTH_WORLD s_texture_14;

uniform float4 s_water_plane;

uniform half volume_power;
uniform half4 caustic_0_transform;
uniform half4 caustic_1_transform;
uniform half4 caustic_color;
uniform half caustic_scale;
uniform half caustic_threshold;
uniform half caustic_density;
uniform half caustic_falloff;

/*
 */
void main() {
	
	#include <core/shaders/water/fragment_volume_fog.h>
	
	float3 direction = normalize(gl_TexCoord[1].xyz) * (getDeferredDepth(deferred_depth) * s_depth_range.y);
	float3 position = s_camera_position + direction;
	
	half2 normal_0 = texture2D(s_texture_0,position.xy * caustic_0_transform.xy + caustic_0_transform.zw).xy;
	half2 normal_1 = texture2D(s_texture_0,position.xy * caustic_1_transform.xy + caustic_1_transform.zw).xy;
	
	#ifdef USE_ARB_TEXTURE_SNORM
		half2 normal = abs((normal_0 + normal_1) * 0.5f);
	#else
		half2 normal = abs((normal_0 + normal_1) - 1.0f);
	#endif
	
	half height = min(dot(s_water_plane,float4(direction,1.0f)),0.0f);
	half caustic = pow(saturate(1.0f - (normal.x + normal.y) * caustic_threshold),16.0f);
	caustic *= caustic_scale * saturate(-height * caustic_density) * exp2(height * caustic_falloff);
	
	#ifdef QUALITY_MEDIUM
		#ifdef SHADOW
			caustic *= shadowWorld(s_texture_14,float4(position,1.0f),s_material_textures[14]);
		#endif
	#endif
	
	half3 color = caustic_color.xyz * (caustic * s_material_shading.x);
	
	gl_FragColor = half4(color * s_light_color.xyz * fog,1.0f);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_7 : TEXCOORD7;
};

float4 s_water_plane;

half volume_power;
half4 caustic_0_transform;
half4 caustic_1_transform;
half4 caustic_color;
half caustic_scale;
half caustic_threshold;
half caustic_density;
half caustic_falloff;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/water/fragment_volume_fog.h>
	
	float3 direction = normalize(IN.texcoord_1.xyz) * (getDeferredDepth(deferred_depth) * s_depth_range.y);
	float3 position = s_camera_position + direction;
	
	half2 normal_0 = tex2D(s_texture_0,position.xy * caustic_0_transform.xy + caustic_0_transform.zw).xy;
	half2 normal_1 = tex2D(s_texture_0,position.xy * caustic_1_transform.xy + caustic_1_transform.zw).xy;
	
	half2 normal = abs((normal_0 + normal_1) - 1.0f);
	
	half height = min(dot(s_water_plane,float4(direction,1.0f)),0.0f);
	half caustic = pow(saturate(1.0f - (normal.x + normal.y) * caustic_threshold),16.0f);
	caustic *= caustic_scale * saturate(-height * caustic_density) * exp2(height * caustic_falloff);
	
	#ifdef QUALITY_MEDIUM
		#ifdef SHADOW
			caustic *= shadowWorld(s_texture_14,float4(position,1.0f),s_material_textures[5]);
		#endif
	#endif
	
	half3 color = caustic_color.xyz * (caustic * s_material_shading.x);
	
	return half4(color * s_light_color.xyz * fog,1.0f);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);

TEXTURE_2DMS s_texture_12 : register(t12);
TEXTURE_SHADOW_WORLD s_texture_14 : register(t14);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_1 : TEXCOORD1;
};

cbuffer shader_water_parameters {
	float4 s_water_plane;
};

cbuffer shader_parameters {
	float volume_power;
	float4 caustic_0_transform;
	float4 caustic_1_transform;
	float4 caustic_color;
	float caustic_scale;
	float caustic_threshold;
	float caustic_density;
	float caustic_falloff;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#include <core/shaders/water/fragment_volume_fog.h>
	
	float3 direction = normalize(IN.texcoord_1.xyz) * (getDeferredDepth(deferred_depth) * s_depth_range.y);
	float3 position = s_camera_position + direction;
	
	half2 normal_0 = s_texture_0.Sample(s_sampler_0,position.xy * caustic_0_transform.xy + caustic_0_transform.zw).xy;
	half2 normal_1 = s_texture_0.Sample(s_sampler_0,position.xy * caustic_1_transform.xy + caustic_1_transform.zw).xy;
	
	half2 normal = abs((normal_0 + normal_1) * 0.5f);
	
	half height = min(dot(s_water_plane,float4(direction,1.0f)),0.0f);
	half caustic = pow(saturate(1.0f - (normal.x + normal.y) * caustic_threshold),16.0f);
	caustic *= caustic_scale * saturate(-height * caustic_density) * exp2(height * caustic_falloff);
	
	#ifdef QUALITY_MEDIUM
		#ifdef SHADOW
			caustic *= shadowWorld(s_texture_14,s_sampler_14,s_sampler_compare_14,float4(position,1.0f),s_material_textures[14]);
		#endif
	#endif
	
	float3 color = caustic_color.xyz * (caustic * s_material_shading.x);
	
	return float4(color * s_light_color.xyz * fog,1.0f);
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_0 : TEXUNIT0;

uniform sampler2D s_texture_12 : TEXUNIT12;
uniform SAMPLER_SHADOW_WORLD s_texture_14 : TEXUNIT14;

struct FRAGMENT_IN {
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_9 : TEXCOORD9;
};

uniform float4 s_water_plane;

uniform half volume_power;
uniform half4 caustic_0_transform;
uniform half4 caustic_1_transform;
uniform half4 caustic_color;
uniform half caustic_scale;
uniform half caustic_threshold;
uniform half caustic_density;
uniform half caustic_falloff;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/water/fragment_volume_fog.h>
	
	float3 direction = IN.texcoord_1.xyz * (getDeferredDepth(deferred_depth) * s_depth_range.y);
	float3 position = s_camera_position + direction;
	
	half2 normal_0 = h2tex2D(s_texture_0,position.xy * caustic_0_transform.xy + caustic_0_transform.zw);
	half2 normal_1 = h2tex2D(s_texture_0,position.xy * caustic_1_transform.xy + caustic_1_transform.zw);
	
	half2 normal = abs((normal_0 + normal_1) * 0.5f);
	
	half height = min(dot(s_water_plane,float4(direction,1.0f)),0.0f);
	half caustic = pow(saturate(1.0f - (normal.x + normal.y) * caustic_threshold),16.0f);
	caustic *= caustic_scale * saturate(-height * caustic_density) * exp2(height * caustic_falloff);
	
	#ifdef QUALITY_MEDIUM
		#ifdef SHADOW
			caustic *= shadowWorld(s_texture_14,float4(position,1.0f));
		#endif
	#endif
	
	half3 color = caustic_color.xyz * (caustic * s_material_shading.x);
	
	return half4(color * s_light_color.xyz * fog,1.0f);
}

#endif
