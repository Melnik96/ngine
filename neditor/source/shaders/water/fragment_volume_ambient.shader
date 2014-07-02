/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_volume_ambient.shader
 * Desc:    Water volume ambient shader
 * Version: 1.11
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

/* s_texture_12 is deferred depth texture
 * s_texture_13 is environment texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform SAMPLER_2DMS s_texture_12;
uniform samplerCube s_texture_13;

uniform half4 volume_color;
uniform half volume_power;
uniform half4 subsurface_color;
uniform	half subsurface_power;
uniform half environment_scale;

/*
 */
void main() {
	
	#include <core/shaders/water/fragment_volume_fog.h>
	
	half3 color = volume_color.xyz;
	
	#ifdef SUBSURFACE
		half density = exp2(half(gl_TexCoord[2].w)) * gl_TexCoord[3].x;
		half camera_density = 1.0f - exp2(-density);
		
		float falloff = dot(gl_TexCoord[1].xyz,gl_TexCoord[2].xyz) * depth / distance;
		if(abs(falloff) > 1e-5f) density *= (1.0f - exp2(-falloff)) / falloff;
		density = 1.0f - exp2(-pow(density * depth,subsurface_power));
		
		color += subsurface_color.xyz * (camera_density * density);
	#endif
	
	half3 environment = textureCube(s_texture_13,gl_TexCoord[0].xyz).xyz;
	color *= (s_ambient_color.xyz + environment * environment_scale);
	
	gl_FragColor = half4(color,1.0f - fog);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float3 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	#ifdef SUBSURFACE
		float4 texcoord_2 : TEXCOORD2;
		float1 texcoord_3 : TEXCOORD3;
	#endif
	float4 texcoord_7 : TEXCOORD7;
};

half4 volume_color;
half volume_power;
half4 subsurface_color;
half subsurface_power;
half environment_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/water/fragment_volume_fog.h>
	
	half3 color = volume_color.xyz;
	
	#ifdef SUBSURFACE
		half density = exp2(half(IN.texcoord_2.w)) * IN.texcoord_3.x;
		half camera_density = 1.0f - exp2(-density);
		
		float falloff = dot(IN.texcoord_1.xyz,IN.texcoord_2.xyz) * depth / distance;
		if(abs(falloff) > 1e-5f) density *= (1.0f - exp2(-falloff)) / falloff;
		density = 1.0f - exp2(-pow(density * depth,subsurface_power));
		
		color += subsurface_color.xyz * (camera_density * density);
	#endif
	
	half3 environment = texCUBE(s_texture_13,IN.texcoord_0).xyz;
	color *= (s_ambient_color.xyz + environment * environment_scale);
	
	return half4(color,1.0f - fog);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

TEXTURE_2DMS s_texture_12 : register(t12);
TextureCube s_texture_13 : register(t13);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float3 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	#ifdef SUBSURFACE
		float4 texcoord_2 : TEXCOORD2;
		float1 texcoord_3 : TEXCOORD3;
	#endif
};

cbuffer shader_parameters {
	float4 volume_color;
	float volume_power;
	float4 subsurface_color;
	float subsurface_power;
	float environment_scale;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#include <core/shaders/water/fragment_volume_fog.h>
	
	half3 color = volume_color.xyz;
	
	#ifdef SUBSURFACE
		half density = exp2(half(IN.texcoord_2.w)) * IN.texcoord_3.x;
		half camera_density = 1.0f - exp2(-density);
		
		float falloff = dot(IN.texcoord_1.xyz,IN.texcoord_2.xyz) * depth / distance;
		if(abs(falloff) > 1e-5f) density *= (1.0f - exp2(-falloff)) / falloff;
		density = 1.0f - exp2(-pow(density * depth,subsurface_power));
		
		color += subsurface_color.xyz * (camera_density * density);
	#endif
	
	half3 environment = s_texture_13.Sample(s_sampler_13,IN.texcoord_0).xyz;
	color *= (s_ambient_color.xyz + environment * environment_scale);
	
	return float4(color,1.0f - fog);
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_12 : TEXUNIT12;
uniform samplerCUBE s_texture_13 : TEXUNIT13;

struct FRAGMENT_IN {
	float3 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	#ifdef SUBSURFACE
		float4 texcoord_2 : TEXCOORD2;
		float1 texcoord_3 : TEXCOORD3;
	#endif
	float4 texcoord_9 : TEXCOORD9;
};

uniform half4 volume_color;
uniform half volume_power;
uniform half4 subsurface_color;
uniform	half subsurface_power;
uniform half environment_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/water/fragment_volume_fog.h>
	
	half3 color = volume_color.xyz;
	
	#ifdef SUBSURFACE
		half density = exp2(half(IN.texcoord_2.w)) * IN.texcoord_3.x;
		half camera_density = 1.0f - exp2(-density);
		
		float falloff = dot(IN.texcoord_1.xyz,IN.texcoord_2.xyz) * depth / distance;
		if(abs(falloff) > 1e-5f) density *= (1.0f - exp2(-falloff)) / falloff;
		density = 1.0f - exp2(-pow(density * depth,subsurface_power));
		
		color += subsurface_color.xyz * (camera_density * density);
	#endif
	
	half3 environment = h3texCUBE(s_texture_13,IN.texcoord_0);
	color *= (s_ambient_color.xyz + environment * environment_scale);
	
	return half4(color,1.0f - fog);
}

#endif
