/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_sphere_ambient.shader
 * Desc:    Sky sphere ambient shader
 * Version: 1.07
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

#include <core/shaders/common/vertex_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

attribute float4 s_attribute_0;

uniform float3 s_sky_tangent;
uniform float3 s_sky_binormal;
uniform float3 s_sky_light_direction;
uniform float3 s_sky_height_falloff;
uniform float4 s_sky_greenstein;
uniform float4 s_sky_ray_beta;
uniform float4 s_sky_mie_beta;
uniform float3 s_sky_ray_dash;
uniform float3 s_sky_mie_dash;

uniform float4 sphere_transform;
uniform float4 mask_0_transform;
uniform float4 mask_1_transform;
uniform float4 clouds_0_transform;
uniform float4 clouds_1_transform;
uniform float4 clouds_2_transform;
uniform float4 clouds_3_transform;
uniform float sphere_scattering;

/*
 */
void main() {
	
	float3 direction = s_attribute_0.xyz * sphere_transform.xyz - float3(0.0f,0.0f,sphere_transform.w);
	
	float4 vertex = float4(direction * s_depth_range.y + s_camera_position,1.0f);
	
	float2 texcoord = float2(dot(s_sky_tangent,direction),dot(s_sky_binormal,direction));
	
	gl_Position = getPosition(vertex);
	
	gl_TexCoord[0].xy = texcoord * mask_0_transform.xy + mask_0_transform.zw;
	gl_TexCoord[0].zw = texcoord * mask_1_transform.xy + mask_1_transform.zw;
	gl_TexCoord[1].xy = texcoord * clouds_0_transform.xy + clouds_0_transform.zw;
	gl_TexCoord[1].zw = texcoord * clouds_1_transform.xy + clouds_1_transform.zw;
	gl_TexCoord[2].xy = texcoord * clouds_2_transform.xy + clouds_2_transform.zw;
	gl_TexCoord[2].zw = texcoord * clouds_3_transform.xy + clouds_3_transform.zw;
	
	#ifdef INSCATTERING
		float distance = length(direction);
		float height = direction.z - s_sky_height_falloff.x;
		
		float ray_density = s_sky_ray_beta.w;
		float mie_density = s_sky_mie_beta.w;
		float ray_falloff = s_sky_height_falloff.y * height;
		float mie_falloff = s_sky_height_falloff.z * height;
		if(abs(ray_falloff) > 0.01f) ray_density *= (1.0f - exp2(-ray_falloff)) / ray_falloff;
		if(abs(mie_falloff) > 0.01f) mie_density *= (1.0f - exp2(-mie_falloff)) / mie_falloff;
		
		float3 scattering = exp2(-(s_sky_ray_beta.xyz * ray_density + s_sky_mie_beta.xyz * mie_density) * distance);
		
		float angle = dot(direction,s_sky_light_direction) / distance;
		float ray_phase = 1.0f + angle * angle;
		float mie_greenstein = s_sky_greenstein.y - s_sky_greenstein.z * angle;
		float mie_phase = min(s_sky_greenstein.x * rsqrt(mie_greenstein),s_sky_greenstein.w * distance);
		float3 inscattering = s_sky_ray_dash * ray_phase + s_sky_mie_dash * mie_phase;
		
		gl_TexCoord[3].xyz = scattering;
		gl_TexCoord[3].w = dot(scattering,float3(sphere_scattering));
		gl_TexCoord[4].xyz = inscattering * (1.0f - scattering);
	#endif
	
	#ifdef BACKGROUND
		gl_TexCoord[5].xyz = direction;
	#endif
	
	gl_Position.z = gl_Position.w;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct VERTEX_IN {
	float4 position : POSITION;
};

struct VERTEX_OUT {
	float4 position : POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	#ifdef INSCATTERING
		float4 texcoord_3 : TEXCOORD3;
		float3 texcoord_4 : TEXCOORD4;
	#endif
	#ifdef BACKGROUND
		float3 texcoord_5 : TEXCOORD5;
	#endif
};

float3 s_sky_tangent;
float3 s_sky_binormal;
float3 s_sky_light_direction;
float3 s_sky_height_falloff;
float4 s_sky_greenstein;
float4 s_sky_ray_beta;
float4 s_sky_mie_beta;
float3 s_sky_ray_dash;
float3 s_sky_mie_dash;

float4 sphere_transform;
float4 mask_0_transform;
float4 mask_1_transform;
float4 clouds_0_transform;
float4 clouds_1_transform;
float4 clouds_2_transform;
float4 clouds_3_transform;
float sphere_scattering;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float3 direction = IN.position.xyz * sphere_transform.xyz - float3(0.0f,0.0f,sphere_transform.w);
	
	float4 vertex = float4(direction * s_depth_range.y + s_camera_position,1.0f);
	
	float2 texcoord = float2(dot(s_sky_tangent,direction),dot(s_sky_binormal,direction));
	
	OUT.position = getPosition(vertex);
	
	OUT.texcoord_0.xy = texcoord * mask_0_transform.xy + mask_0_transform.zw;
	OUT.texcoord_0.zw = texcoord * mask_1_transform.xy + mask_1_transform.zw;
	OUT.texcoord_1.xy = texcoord * clouds_0_transform.xy + clouds_0_transform.zw;
	OUT.texcoord_1.zw = texcoord * clouds_1_transform.xy + clouds_1_transform.zw;
	OUT.texcoord_2.xy = texcoord * clouds_2_transform.xy + clouds_2_transform.zw;
	OUT.texcoord_2.zw = texcoord * clouds_3_transform.xy + clouds_3_transform.zw;
	
	#ifdef INSCATTERING
		float distance = length(direction);
		float height = direction.z - s_sky_height_falloff.x;
		
		float ray_density = s_sky_ray_beta.w;
		float mie_density = s_sky_mie_beta.w;
		float ray_falloff = s_sky_height_falloff.y * height;
		float mie_falloff = s_sky_height_falloff.z * height;
		if(abs(ray_falloff) > 0.01f) ray_density *= (1.0f - exp2(-ray_falloff)) / ray_falloff;
		if(abs(mie_falloff) > 0.01f) mie_density *= (1.0f - exp2(-mie_falloff)) / mie_falloff;
		
		float3 scattering = exp2(-(s_sky_ray_beta.xyz * ray_density + s_sky_mie_beta.xyz * mie_density) * distance);
		
		float angle = dot(direction,s_sky_light_direction) / distance;
		float ray_phase = 1.0f + angle * angle;
		float mie_greenstein = s_sky_greenstein.y - s_sky_greenstein.z * angle;
		float mie_phase = min(s_sky_greenstein.x * rsqrt(mie_greenstein),s_sky_greenstein.w * distance);
		float3 inscattering = s_sky_ray_dash * ray_phase + s_sky_mie_dash * mie_phase;
		
		OUT.texcoord_3.xyz = scattering;
		OUT.texcoord_3.w = dot(scattering,sphere_scattering);
		OUT.texcoord_4.xyz = inscattering * (1.0f - scattering);
	#endif
	
	#ifdef BACKGROUND
		OUT.texcoord_5 = direction;
	#endif
	
	OUT.position.z = OUT.position.w;
	
	return OUT;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

struct VERTEX_IN {
	float4 position : POSITION;
};

struct VERTEX_OUT {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	#ifdef INSCATTERING
		float4 texcoord_3 : TEXCOORD3;
		float3 texcoord_4 : TEXCOORD4;
	#endif
	#ifdef BACKGROUND
		float3 texcoord_5 : TEXCOORD5;
	#endif
};

cbuffer shader_sky_parameters {
	float3 s_sky_tangent;
	float3 s_sky_binormal;
	float3 s_sky_light_direction;
	float3 s_sky_height_falloff;
	float4 s_sky_greenstein;
	float4 s_sky_ray_beta;
	float4 s_sky_mie_beta;
	float3 s_sky_ray_dash;
	float3 s_sky_mie_dash;
};

cbuffer shader_parameters {
	float4 sphere_transform;
	float4 mask_0_transform;
	float4 mask_1_transform;
	float4 clouds_0_transform;
	float4 clouds_1_transform;
	float4 clouds_2_transform;
	float4 clouds_3_transform;
	float sphere_scattering;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float3 direction = IN.position.xyz * sphere_transform.xyz - float3(0.0f,0.0f,sphere_transform.w);
	
	float4 vertex = float4(direction * s_depth_range.y + s_camera_position,1.0f);
	
	float2 texcoord = float2(dot(s_sky_tangent,direction),dot(s_sky_binormal,direction));
	
	OUT.position = getPosition(vertex);
	
	OUT.texcoord_0.xy = texcoord * mask_0_transform.xy + mask_0_transform.zw;
	OUT.texcoord_0.zw = texcoord * mask_1_transform.xy + mask_1_transform.zw;
	OUT.texcoord_1.xy = texcoord * clouds_0_transform.xy + clouds_0_transform.zw;
	OUT.texcoord_1.zw = texcoord * clouds_1_transform.xy + clouds_1_transform.zw;
	OUT.texcoord_2.xy = texcoord * clouds_2_transform.xy + clouds_2_transform.zw;
	OUT.texcoord_2.zw = texcoord * clouds_3_transform.xy + clouds_3_transform.zw;
	
	#ifdef INSCATTERING
		float distance = length(direction);
		float height = direction.z - s_sky_height_falloff.x;
		
		float ray_density = s_sky_ray_beta.w;
		float mie_density = s_sky_mie_beta.w;
		float ray_falloff = s_sky_height_falloff.y * height;
		float mie_falloff = s_sky_height_falloff.z * height;
		if(abs(ray_falloff) > 0.01f) ray_density *= (1.0f - exp2(-ray_falloff)) / ray_falloff;
		if(abs(mie_falloff) > 0.01f) mie_density *= (1.0f - exp2(-mie_falloff)) / mie_falloff;
		
		float3 scattering = exp2(-(s_sky_ray_beta.xyz * ray_density + s_sky_mie_beta.xyz * mie_density) * distance);
		
		float angle = dot(direction,s_sky_light_direction) / distance;
		float ray_phase = 1.0f + angle * angle;
		float mie_greenstein = s_sky_greenstein.y - s_sky_greenstein.z * angle;
		float mie_phase = min(s_sky_greenstein.x * rsqrt(mie_greenstein),s_sky_greenstein.w * distance);
		float3 inscattering = s_sky_ray_dash * ray_phase + s_sky_mie_dash * mie_phase;
		
		OUT.texcoord_3.xyz = scattering;
		OUT.texcoord_3.w = dot(scattering,sphere_scattering);
		OUT.texcoord_4.xyz = inscattering * (1.0f - scattering);
	#endif
	
	#ifdef BACKGROUND
		OUT.texcoord_5 = direction;
	#endif
	
	OUT.position.z = OUT.position.w;
	
	return OUT;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

struct VERTEX_IN {
	float4 position : ATTR0;
};

struct VERTEX_OUT {
	float4 position : POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	#ifdef INSCATTERING
		float4 texcoord_3 : TEXCOORD3;
		float3 texcoord_4 : TEXCOORD4;
	#endif
	#ifdef BACKGROUND
		float3 texcoord_5 : TEXCOORD5;
	#endif
};

uniform float3 s_sky_tangent;
uniform float3 s_sky_binormal;
uniform float3 s_sky_light_direction;
uniform float3 s_sky_height_falloff;
uniform float4 s_sky_greenstein;
uniform float4 s_sky_ray_beta;
uniform float4 s_sky_mie_beta;
uniform float3 s_sky_ray_dash;
uniform float3 s_sky_mie_dash;

uniform float4 sphere_transform;
uniform float4 mask_0_transform;
uniform float4 mask_1_transform;
uniform float4 clouds_0_transform;
uniform float4 clouds_1_transform;
uniform float4 clouds_2_transform;
uniform float4 clouds_3_transform;
uniform float sphere_scattering;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float3 direction = IN.position.xyz * sphere_transform.xyz - float3(0.0f,0.0f,sphere_transform.w);
	
	float4 vertex = float4(direction * s_depth_range.y + s_camera_position,1.0f);
	
	float2 texcoord = float2(dot(s_sky_tangent,direction),dot(s_sky_binormal,direction));
	
	OUT.position = getPosition(vertex);
	
	OUT.texcoord_0.xy = texcoord * mask_0_transform.xy + mask_0_transform.zw;
	OUT.texcoord_0.zw = texcoord * mask_1_transform.xy + mask_1_transform.zw;
	OUT.texcoord_1.xy = texcoord * clouds_0_transform.xy + clouds_0_transform.zw;
	OUT.texcoord_1.zw = texcoord * clouds_1_transform.xy + clouds_1_transform.zw;
	OUT.texcoord_2.xy = texcoord * clouds_2_transform.xy + clouds_2_transform.zw;
	OUT.texcoord_2.zw = texcoord * clouds_3_transform.xy + clouds_3_transform.zw;
	
	#ifdef INSCATTERING
		float distance = length(direction);
		float height = direction.z - s_sky_height_falloff.x;
		
		float ray_density = s_sky_ray_beta.w;
		float mie_density = s_sky_mie_beta.w;
		float ray_falloff = s_sky_height_falloff.y * height;
		float mie_falloff = s_sky_height_falloff.z * height;
		if(abs(ray_falloff) > 0.01f) ray_density *= (1.0f - exp2(-ray_falloff)) / ray_falloff;
		if(abs(mie_falloff) > 0.01f) mie_density *= (1.0f - exp2(-mie_falloff)) / mie_falloff;
		
		float3 scattering = exp2(-(s_sky_ray_beta.xyz * ray_density + s_sky_mie_beta.xyz * mie_density) * distance);
		
		float angle = dot(direction,s_sky_light_direction) / distance;
		float ray_phase = 1.0f + angle * angle;
		float mie_greenstein = s_sky_greenstein.y - s_sky_greenstein.z * angle;
		float mie_phase = min(s_sky_greenstein.x * rsqrt(mie_greenstein),s_sky_greenstein.w * distance);
		float3 inscattering = s_sky_ray_dash * ray_phase + s_sky_mie_dash * mie_phase;
		
		OUT.texcoord_3.xyz = scattering;
		OUT.texcoord_3.w = dot(scattering,sphere_scattering);
		OUT.texcoord_4.xyz = inscattering * (1.0f - scattering);
	#endif
	
	#ifdef BACKGROUND
		OUT.texcoord_5 = direction;
	#endif
	
	OUT.position.z = OUT.position.w;
	
	return OUT;
}

#endif
