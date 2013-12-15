/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_box_shaft_light_world.shader
 * Desc:    VolumeBox shaft light world shader
 * Version: 1.02
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

/* s_texture_0 is noise texture
 * 
 * s_texture_13 is deferred depth texture
 * s_texture_14 is light shadow color texture
 * s_texture_15 is light shadow depth texture
 */

#include <core/shaders/common/fragment_base.h>

#ifdef SAMPLES_16
	#define SAMPLES	16.0f
#elif SAMPLES_32
	#define SAMPLES	32.0f
#elif SAMPLES_64
	#define SAMPLES	64.0f
#elif SAMPLES_128
	#define SAMPLES	128.0f
#elif SAMPLES_256
	#define	SAMPLES	256.0f
#endif

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;

uniform SAMPLER_2DMS s_texture_13;
uniform SAMPLER_SHADOW_COLOR_WORLD s_texture_14;
uniform SAMPLER_SHADOW_DEPTH_WORLD s_texture_15;

uniform half s_volume_fade;

uniform half4 diffuse_color;
uniform half volume_density;

/*
 */
void main() {
	
	half4 deferred_depth = texture2DDeferredProj(s_texture_13,gl_TexCoord[7],s_material_textures[13].xy);
	
	float4 begin = gl_TexCoord[0];
	float3 end = gl_TexCoord[1].xyz / gl_TexCoord[1].w;
	float3 direction = (end - begin.xyz) * (1.0f / SAMPLES);
	
	float front = length(begin.xyz);
	float back = length(end);
	float near = min(back,getDeferredDepth(deferred_depth) * s_depth_range.y);
	float step = max((back - front) * (1.0f / SAMPLES),1e-3f);
	
	float2 noise_texcoord = gl_TexCoord[7].xy * gl_TexCoord[2].xy / gl_TexCoord[7].w;
	begin.xyz += s_camera_position + direction * texture2D(s_texture_0,noise_texcoord).x;
	
	half3 color = half3(0.0f);
	
	for(float k = front; k < near; k += step) {
		color += shadowWorld(diffuse_color.xyz,s_texture_15,s_texture_14,begin,s_material_textures[15]);
		begin.xyz += direction;
	}
	
	color *= s_light_color.xyz;
	color *= s_volume_fade * volume_density * (1.0f / SAMPLES);
	
	gl_FragColor = half4(color,1.0f);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float2 texcoord_2 : TEXCOORD2;
	float4 texcoord_7 : TEXCOORD7;
};

half s_volume_fade;

half4 diffuse_color;
half volume_density;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_depth = tex2Dproj(s_texture_13,IN.texcoord_7);
	
	float4 begin = IN.texcoord_0;
	float3 end = IN.texcoord_1.xyz / IN.texcoord_1.w;
	float3 direction = (end - begin.xyz) * (1.0f / SAMPLES);
	
	float front = length(begin.xyz);
	float back = length(end);
	float near = min(back,getDeferredDepth(deferred_depth) * s_depth_range.y);
	float step = max((back - front) * (1.0f / SAMPLES),1e-3f);
	
	float2 noise_texcoord = IN.texcoord_7.xy * IN.texcoord_2 / IN.texcoord_7.w;
	begin.xyz += s_camera_position + direction * tex2D(s_texture_0,noise_texcoord).x;
	
	half3 color = 0.0f;
	
	[loop] for(float k = front; k < near; k += step) {
		color += shadowWorld(diffuse_color.xyz,s_texture_15,s_texture_14,begin,s_material_textures[15]);
		begin.xyz += direction;
	}
	
	color *= s_light_color.xyz;
	color *= s_volume_fade * volume_density * (1.0f / SAMPLES);
	
	return half4(color,1.0f);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);

TEXTURE_2DMS s_texture_13 : register(t13);
TEXTURE_SHADOW_WORLD s_texture_14 : register(t14);
TEXTURE_SHADOW_WORLD s_texture_15 : register(t15);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float2 texcoord_2 : TEXCOORD2;
};

cbuffer shader_volume_parameters {
	float s_volume_fade;
};

cbuffer shader_parameters {
	float4 diffuse_color;
	float volume_density;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 deferred_depth = texture2DDeferredRect(s_texture_13,s_sampler_13,IN.position.xy,s_material_textures[13].xy);
	
	float4 begin = IN.texcoord_0;
	float3 end = IN.texcoord_1.xyz / IN.texcoord_1.w;
	float3 direction = (end - begin.xyz) * (1.0f / SAMPLES);
	
	float front = length(begin.xyz);
	float back = length(end);
	float near = min(back,getDeferredDepth(deferred_depth) * s_depth_range.y);
	float step = max((back - front) * (1.0f / SAMPLES),1e-3f);
	
	float2 noise_texcoord = IN.position.xy * IN.texcoord_2;
	begin.xyz += s_camera_position + direction * s_texture_0.Sample(s_sampler_0,noise_texcoord).x;
	
	half3 color = 0.0f;
	
	[loop] for(float k = front; k < near; k += step) {
		color += shadowWorld(diffuse_color.xyz,s_texture_15,s_sampler_15,s_sampler_compare_15,s_texture_14,s_sampler_14,begin,s_material_textures[15]);
		begin.xyz += direction;
	}
	
	color *= s_light_color.xyz;
	color *= s_volume_fade * volume_density * (1.0f / SAMPLES);
	
	return float4(color,1.0f);
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_0 : TEXUNIT0;

uniform sampler2D s_texture_13 : TEXUNIT13;
uniform SAMPLER_SHADOW_WORLD s_texture_14 : TEXUNIT14;
uniform SAMPLER_SHADOW_WORLD s_texture_15 : TEXUNIT15;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float2 texcoord_2 : TEXCOORD2;
	float4 texcoord_9 : TEXCOORD9;
};

uniform half s_volume_fade;

uniform half4 diffuse_color;
uniform half volume_density;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_depth = h4tex2Dproj(s_texture_13,IN.texcoord_9.xyw);
	
	float4 begin = IN.texcoord_0;
	float3 end = IN.texcoord_1.xyz / IN.texcoord_1.w;
	float3 direction = (end - begin.xyz) * (1.0f / SAMPLES);
	
	float front = length(begin.xyz);
	float back = length(end);
	float near = min(back,getDeferredDepth(deferred_depth) * s_depth_range.y);
	float step = max((back - front) * (1.0f / SAMPLES),1e-3f);
	
	float2 noise_texcoord = IN.texcoord_9.xy * IN.texcoord_2 / IN.texcoord_9.w;
	begin.xyz += s_camera_position + direction * h1tex2D(s_texture_0,noise_texcoord);
	
	half3 color = 0.0f;
	
	for(float k = front; k < near; k += step) {
		color += shadowWorld(diffuse_color.xyz,s_texture_15,s_texture_14,begin);
		begin.xyz += direction;
	}
	
	color *= s_light_color.xyz;
	color *= s_volume_fade * volume_density * (1.0f / SAMPLES);
	
	return half4(color,1.0f);
}

#endif
