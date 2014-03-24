/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_clouds_ambient.shader
 * Desc:    Sky clouds ambient shader
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

#include <core/shaders/common/vertex_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

attribute float4 s_attribute_0;

uniform float4x4 s_sky_modelview;
uniform float4x4 s_sky_imodelview;
uniform float4x4 s_sky_texcoord;
uniform float3 s_sky_light_direction;
uniform float3 s_sky_height_falloff;
uniform float4 s_sky_greenstein;
uniform float4 s_sky_ray_beta;
uniform float4 s_sky_mie_beta;
uniform float3 s_sky_ray_dash;
uniform float3 s_sky_mie_dash;
uniform float s_sky_power;

uniform float4 clouds_transform;
uniform float4 clouds_color_0;
uniform float4 clouds_color_1;
uniform float clouds_scale;
uniform float clouds_scattering;

/*
 */
void main() {
	
	float4 vertex = s_sky_modelview * float4(s_attribute_0.xyz,1.0f);
	
	gl_Position = s_projection * vertex;
	
	vertex = s_sky_imodelview * vertex;
	float3 direction = (vertex.xyz - s_camera_position) / s_depth_range.y;
	float distance = length(direction);
	
	gl_TexCoord[0].xyz = (s_sky_texcoord * vertex).xyz;
	gl_TexCoord[0].xy = gl_TexCoord[0].xy * clouds_transform.xy + clouds_transform.zw;
	gl_TexCoord[1].xyz = gl_TexCoord[0].xyz * float3(4.0f,4.0f,0.5f);
	
	gl_TexCoord[2].xyz = direction;
	
	gl_TexCoord[3].xyz = clouds_color_0.xyz * clouds_scale;
	gl_TexCoord[4].xyz = clouds_color_1.xyz * clouds_scale;
	
	#ifdef INSCATTERING
		float height = vertex.z / s_depth_range.y - s_sky_height_falloff.x;
		
		float ray_density = s_sky_ray_beta.w;
		float mie_density = s_sky_mie_beta.w;
		float ray_falloff = s_sky_height_falloff.y * height;
		float mie_falloff = s_sky_height_falloff.z * height;
		if(abs(ray_falloff) > 0.01f) ray_density *= (1.0f - exp2(-ray_falloff)) / ray_falloff;
		if(abs(mie_falloff) > 0.01f) mie_density *= (1.0f - exp2(-mie_falloff)) / mie_falloff;
		
		float scattering_distance = pow(distance,s_sky_power);
		float3 scattering = exp2(-(s_sky_ray_beta.xyz * ray_density + s_sky_mie_beta.xyz * mie_density) * scattering_distance);
		
		float angle = dot(direction,s_sky_light_direction) / distance;
		float ray_phase = 1.0f + angle * angle;
		float mie_greenstein = s_sky_greenstein.y - s_sky_greenstein.z * angle;
		float mie_phase = min(s_sky_greenstein.x * rsqrt(mie_greenstein),s_sky_greenstein.w * scattering_distance);
		float3 inscattering = s_sky_ray_dash * ray_phase + s_sky_mie_dash * mie_phase;
		
		gl_TexCoord[5].xyz = scattering;
		gl_TexCoord[5].w = saturate(dot(scattering,float3(clouds_scattering)));
		gl_TexCoord[6].xyz = inscattering * (1.0f - scattering);
		gl_TexCoord[6].w = 0.0f;
	#endif
	
	gl_TexCoord[7] = getProjection(gl_Position);
	
	if(distance > 0.9f) {
		gl_TexCoord[2].xyz = direction * 0.9f / distance;
		gl_Position.z = gl_Position.w;
	}
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
	float3 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	float4 texcoord_7 : TEXCOORD7;
	#ifdef INSCATTERING
		float4 texcoord_5 : TEXCOORD5;
		float4 texcoord_6 : TEXCOORD6;
	#endif
};

float4x4 s_sky_modelview;
float4x4 s_sky_imodelview;
float4x4 s_sky_texcoord;
float3 s_sky_light_direction;
float3 s_sky_height_falloff;
float4 s_sky_greenstein;
float4 s_sky_ray_beta;
float4 s_sky_mie_beta;
float3 s_sky_ray_dash;
float3 s_sky_mie_dash;
float s_sky_power;

float4 clouds_transform;
float4 clouds_color_0;
float4 clouds_color_1;
float clouds_scale;
float clouds_scattering;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = mul(s_sky_modelview,float4(IN.position.xyz,1.0f));
	
	OUT.position = mul(s_projection,vertex);
	
	vertex = mul(s_sky_imodelview,vertex);
	float3 direction = (vertex.xyz - s_camera_position) / s_depth_range.y;
	float distance = length(direction);
	
	OUT.texcoord_0 = mul(s_sky_texcoord,vertex).xyz;
	OUT.texcoord_0.xy = OUT.texcoord_0.xy * clouds_transform.xy + clouds_transform.zw;
	OUT.texcoord_1 = OUT.texcoord_0 * float3(4.0f,4.0f,0.5f);
	
	OUT.texcoord_2 = direction;
	
	OUT.texcoord_3 = clouds_color_0.xyz * clouds_scale;
	OUT.texcoord_4 = clouds_color_1.xyz * clouds_scale;
	
	#ifdef INSCATTERING
		float height = vertex.z / s_depth_range.y - s_sky_height_falloff.x;
		
		float ray_density = s_sky_ray_beta.w;
		float mie_density = s_sky_mie_beta.w;
		float ray_falloff = s_sky_height_falloff.y * height;
		float mie_falloff = s_sky_height_falloff.z * height;
		if(abs(ray_falloff) > 0.01f) ray_density *= (1.0f - exp2(-ray_falloff)) / ray_falloff;
		if(abs(mie_falloff) > 0.01f) mie_density *= (1.0f - exp2(-mie_falloff)) / mie_falloff;
		
		float scattering_distance = pow(distance,s_sky_power);
		float3 scattering = exp2(-(s_sky_ray_beta.xyz * ray_density + s_sky_mie_beta.xyz * mie_density) * scattering_distance);
		
		float angle = dot(direction,s_sky_light_direction) / distance;
		float ray_phase = 1.0f + angle * angle;
		float mie_greenstein = s_sky_greenstein.y - s_sky_greenstein.z * angle;
		float mie_phase = min(s_sky_greenstein.x * rsqrt(mie_greenstein),s_sky_greenstein.w * scattering_distance);
		float3 inscattering = s_sky_ray_dash * ray_phase + s_sky_mie_dash * mie_phase;
		
		OUT.texcoord_5.xyz = scattering;
		OUT.texcoord_5.w = saturate(dot(scattering,clouds_scattering));
		OUT.texcoord_6.xyz = inscattering * (1.0f - scattering);
		OUT.texcoord_6.w = 0.0f;
	#endif
	
	OUT.texcoord_7 = getProjection(OUT.position);
	
	if(distance > 0.9f) {
		OUT.texcoord_2 = direction * 0.9f / distance;
		OUT.position.z = OUT.position.w;
	}
	
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
	float3 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	#ifdef INSCATTERING
		float4 texcoord_5 : TEXCOORD5;
		float4 texcoord_6 : TEXCOORD6;
	#endif
};

cbuffer shader_sky_parameters {
	float4x4 s_sky_modelview;
	float4x4 s_sky_imodelview;
	float4x4 s_sky_texcoord;
	float3 s_sky_light_direction;
	float3 s_sky_height_falloff;
	float4 s_sky_greenstein;
	float4 s_sky_ray_beta;
	float4 s_sky_mie_beta;
	float3 s_sky_ray_dash;
	float3 s_sky_mie_dash;
	float s_sky_power;
};

cbuffer shader_parameters {
	float4 clouds_transform;
	float4 clouds_color_0;
	float4 clouds_color_1;
	float clouds_scale;
	float clouds_scattering;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = mul(s_sky_modelview,float4(IN.position.xyz,1.0f));
	
	OUT.position = mul(s_projection,vertex);
	
	vertex = mul(s_sky_imodelview,vertex);
	float3 direction = (vertex.xyz - s_camera_position) / s_depth_range.y;
	float distance = length(direction);
	
	OUT.texcoord_0 = mul(s_sky_texcoord,vertex).xyz;
	OUT.texcoord_0.xy = OUT.texcoord_0.xy * clouds_transform.xy + clouds_transform.zw;
	OUT.texcoord_1 = OUT.texcoord_0 * float3(4.0f,4.0f,0.5f);
	
	OUT.texcoord_2 = direction;
	
	OUT.texcoord_3 = clouds_color_0.xyz * clouds_scale;
	OUT.texcoord_4 = clouds_color_1.xyz * clouds_scale;
	
	#ifdef INSCATTERING
		float height = vertex.z / s_depth_range.y - s_sky_height_falloff.x;
		
		float ray_density = s_sky_ray_beta.w;
		float mie_density = s_sky_mie_beta.w;
		float ray_falloff = s_sky_height_falloff.y * height;
		float mie_falloff = s_sky_height_falloff.z * height;
		if(abs(ray_falloff) > 0.01f) ray_density *= (1.0f - exp2(-ray_falloff)) / ray_falloff;
		if(abs(mie_falloff) > 0.01f) mie_density *= (1.0f - exp2(-mie_falloff)) / mie_falloff;
		
		float scattering_distance = pow(distance,s_sky_power);
		float3 scattering = exp2(-(s_sky_ray_beta.xyz * ray_density + s_sky_mie_beta.xyz * mie_density) * scattering_distance);
		
		float angle = dot(direction,s_sky_light_direction) / distance;
		float ray_phase = 1.0f + angle * angle;
		float mie_greenstein = s_sky_greenstein.y - s_sky_greenstein.z * angle;
		float mie_phase = min(s_sky_greenstein.x * rsqrt(mie_greenstein),s_sky_greenstein.w * scattering_distance);
		float3 inscattering = s_sky_ray_dash * ray_phase + s_sky_mie_dash * mie_phase;
		
		OUT.texcoord_5.xyz = scattering;
		OUT.texcoord_5.w = saturate(dot(scattering,clouds_scattering));
		OUT.texcoord_6.xyz = inscattering * (1.0f - scattering);
		OUT.texcoord_6.w = 0.0f;
	#endif
	
	if(distance > 0.9f) {
		OUT.texcoord_2 = direction * 0.9f / distance;
		OUT.position.z = OUT.position.w;
	}
	
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
	float3 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	float4 texcoord_9 : TEXCOORD9;
	#ifdef INSCATTERING
		float4 texcoord_5 : TEXCOORD5;
		float4 texcoord_6 : TEXCOORD6;
	#endif
};

uniform float4x4 s_sky_modelview;
uniform float4x4 s_sky_imodelview;
uniform float4x4 s_sky_texcoord;
uniform float3 s_sky_light_direction;
uniform float3 s_sky_height_falloff;
uniform float4 s_sky_greenstein;
uniform float4 s_sky_ray_beta;
uniform float4 s_sky_mie_beta;
uniform float3 s_sky_ray_dash;
uniform float3 s_sky_mie_dash;
uniform float s_sky_power;

uniform float4 clouds_transform;
uniform float4 clouds_color_0;
uniform float4 clouds_color_1;
uniform float clouds_scale;
uniform float clouds_scattering;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = mul(s_sky_modelview,float4(IN.position.xyz,1.0f));
	
	OUT.position = mul(s_projection,vertex);
	
	vertex = mul(s_sky_imodelview,vertex);
	float3 direction = (vertex.xyz - s_camera_position) / s_depth_range.y;
	float distance = length(direction);
	
	OUT.texcoord_0 = mul(s_sky_texcoord,vertex).xyz;
	OUT.texcoord_0.xy = OUT.texcoord_0.xy * clouds_transform.xy + clouds_transform.zw;
	OUT.texcoord_1 = OUT.texcoord_0 * float3(4.0f,4.0f,0.5f);
	
	OUT.texcoord_2 = direction;
	
	OUT.texcoord_3 = clouds_color_0.xyz * clouds_scale;
	OUT.texcoord_4 = clouds_color_1.xyz * clouds_scale;
	
	#ifdef INSCATTERING
		float height = vertex.z / s_depth_range.y - s_sky_height_falloff.x;
		
		float ray_density = s_sky_ray_beta.w;
		float mie_density = s_sky_mie_beta.w;
		float ray_falloff = s_sky_height_falloff.y * height;
		float mie_falloff = s_sky_height_falloff.z * height;
		if(abs(ray_falloff) > 0.01f) ray_density *= (1.0f - exp2(-ray_falloff)) / ray_falloff;
		if(abs(mie_falloff) > 0.01f) mie_density *= (1.0f - exp2(-mie_falloff)) / mie_falloff;
		
		float scattering_distance = pow(distance,s_sky_power);
		float3 scattering = exp2(-(s_sky_ray_beta.xyz * ray_density + s_sky_mie_beta.xyz * mie_density) * scattering_distance);
		
		float angle = dot(direction,s_sky_light_direction) / distance;
		float ray_phase = 1.0f + angle * angle;
		float mie_greenstein = s_sky_greenstein.y - s_sky_greenstein.z * angle;
		float mie_phase = min(s_sky_greenstein.x * rsqrt(mie_greenstein),s_sky_greenstein.w * scattering_distance);
		float3 inscattering = s_sky_ray_dash * ray_phase + s_sky_mie_dash * mie_phase;
		
		OUT.texcoord_5.xyz = scattering;
		OUT.texcoord_5.w = saturate(dot(scattering,clouds_scattering));
		OUT.texcoord_6.xyz = inscattering * (1.0f - scattering);
		OUT.texcoord_6.w = 0.0f;
	#endif
	
	OUT.texcoord_9 = getProjection(OUT.position);
	
	if(distance > 0.9f) {
		OUT.texcoord_2 = direction * 0.9f / distance;
		OUT.position.z = OUT.position.w;
	}
	
	return OUT;
}

#endif
