/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_shadow_light_world.shader
 * Desc:    Sky shadow light world shader
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

/* s_texture_0 is mask_0 texture
 * s_texture_1 is mask_1 texture
 * s_texture_2 is clouds_01 texture
 * s_texture_3 is clouds_23 texture
 * 
 * s_texture_15 is deferred depth texture
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

uniform SAMPLER_2DMS s_texture_15;

uniform float3 s_sky_tangent;
uniform float3 s_sky_binormal;

uniform float4 mask_0_transform;
uniform float4 mask_1_transform;
uniform float4 clouds_0_transform;
uniform float4 clouds_1_transform;
uniform float4 clouds_2_transform;
uniform float4 clouds_3_transform;
uniform half clouds_01_scale;
uniform half clouds_23_scale;
uniform half clouds_01_threshold;
uniform half clouds_23_threshold;
uniform half shadow_scale;

/*
 */
void main() {
	
	half4 deferred_depth = texture2DDeferredProj(s_texture_15,gl_TexCoord[7],s_material_textures[15].xy);
	float depth = getDeferredDepth(deferred_depth);
	if(depth > 0.9f) discard;
	
	half3 direction = normalize(gl_TexCoord[0].xyz) * depth;
	half3 position = direction + s_camera_position / s_depth_range.y;
	half2 texcoord = half2(dot(s_sky_tangent,position),dot(s_sky_binormal,position));
	
	half mask_0 = texture2D(s_texture_0,texcoord * mask_0_transform.xy + mask_0_transform.zw).w;
	half mask_1 = texture2D(s_texture_1,texcoord * mask_1_transform.xy + mask_1_transform.zw).w;
	
	half clouds_0 = texture2D(s_texture_2,texcoord * clouds_0_transform.xy + clouds_0_transform.zw).w;
	half clouds_1 = texture2D(s_texture_2,texcoord * clouds_1_transform.xy + clouds_1_transform.zw).w;
	half clouds_2 = texture2D(s_texture_3,texcoord * clouds_2_transform.xy + clouds_2_transform.zw).w;
	half clouds_3 = texture2D(s_texture_3,texcoord * clouds_3_transform.xy + clouds_3_transform.zw).w;
	
	half clouds_01 = saturate((clouds_0 + clouds_1 - mask_0 * clouds_01_threshold) * clouds_01_scale);
	half clouds_23 = saturate((clouds_2 + clouds_3 - mask_1 * clouds_23_threshold) * clouds_23_scale);
	
	gl_FragColor = half4(1.0f - max(clouds_01,clouds_23) * shadow_scale);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float3 texcoord_0 : TEXCOORD0;
	float4 texcoord_7 : TEXCOORD7;
};

float3 s_sky_tangent;
float3 s_sky_binormal;

float4 mask_0_transform;
float4 mask_1_transform;
float4 clouds_0_transform;
float4 clouds_1_transform;
float4 clouds_2_transform;
float4 clouds_3_transform;
half diffuse_0_scale;
half diffuse_1_scale;
half clouds_01_scale;
half clouds_23_scale;
half clouds_01_threshold;
half clouds_23_threshold;
half shadow_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_depth = tex2Dproj(s_texture_15,IN.texcoord_7);
	float depth = getDeferredDepth(deferred_depth);
	if(depth > 0.9f) discard;
	
	half3 direction = normalize(IN.texcoord_0) * depth;
	half3 position = direction + s_camera_position / s_depth_range.y;
	half2 texcoord = half2(dot(s_sky_tangent,position),dot(s_sky_binormal,position));
	
	half mask_0 = tex2D(s_texture_0,texcoord * mask_0_transform.xy + mask_0_transform.zw).w;
	half mask_1 = tex2D(s_texture_1,texcoord * mask_1_transform.xy + mask_1_transform.zw).w;
	
	half clouds_0 = tex2D(s_texture_2,texcoord * clouds_0_transform.xy + clouds_0_transform.zw).w;
	half clouds_1 = tex2D(s_texture_2,texcoord * clouds_1_transform.xy + clouds_1_transform.zw).w;
	half clouds_2 = tex2D(s_texture_3,texcoord * clouds_2_transform.xy + clouds_2_transform.zw).w;
	half clouds_3 = tex2D(s_texture_3,texcoord * clouds_3_transform.xy + clouds_3_transform.zw).w;
	
	half clouds_01 = saturate((clouds_0 + clouds_1 - mask_0 * clouds_01_threshold) * clouds_01_scale);
	half clouds_23 = saturate((clouds_2 + clouds_3 - mask_1 * clouds_23_threshold) * clouds_23_scale);
	
	return 1.0f - max(clouds_01,clouds_23) * shadow_scale;
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

TEXTURE_2DMS s_texture_15 : register(t15);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float3 texcoord_0 : TEXCOORD0;
};

cbuffer shader_sky_parameters {
	float3 s_sky_tangent;
	float3 s_sky_binormal;
};

cbuffer shader_parameters {
	float4 mask_0_transform;
	float4 mask_1_transform;
	float4 clouds_0_transform;
	float4 clouds_1_transform;
	float4 clouds_2_transform;
	float4 clouds_3_transform;
	float diffuse_0_scale;
	float diffuse_1_scale;
	float clouds_01_scale;
	float clouds_23_scale;
	float clouds_01_threshold;
	float clouds_23_threshold;
	float shadow_scale;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 deferred_depth = texture2DDeferredRect(s_texture_15,s_sampler_15,IN.position.xy,s_material_textures[15].xy);
	float depth = getDeferredDepth(deferred_depth);
	if(depth > 0.9f) discard;
	
	half3 direction = normalize(IN.texcoord_0) * depth;
	half3 position = direction + s_camera_position / s_depth_range.y;
	half2 texcoord = half2(dot(s_sky_tangent,position),dot(s_sky_binormal,position));
	
	half mask_0 = s_texture_0.Sample(s_sampler_0,texcoord * mask_0_transform.xy + mask_0_transform.zw).w;
	half mask_1 = s_texture_1.Sample(s_sampler_1,texcoord * mask_1_transform.xy + mask_1_transform.zw).w;
	
	half clouds_0 = s_texture_2.Sample(s_sampler_2,texcoord * clouds_0_transform.xy + clouds_0_transform.zw).w;
	half clouds_1 = s_texture_2.Sample(s_sampler_2,texcoord * clouds_1_transform.xy + clouds_1_transform.zw).w;
	half clouds_2 = s_texture_3.Sample(s_sampler_3,texcoord * clouds_2_transform.xy + clouds_2_transform.zw).w;
	half clouds_3 = s_texture_3.Sample(s_sampler_3,texcoord * clouds_3_transform.xy + clouds_3_transform.zw).w;
	
	half clouds_01 = saturate((clouds_0 + clouds_1 - mask_0 * clouds_01_threshold) * clouds_01_scale);
	half clouds_23 = saturate((clouds_2 + clouds_3 - mask_1 * clouds_23_threshold) * clouds_23_scale);
	
	return 1.0f - max(clouds_01,clouds_23) * shadow_scale;
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

uniform sampler2D s_texture_15 : TEXUNIT15;

struct FRAGMENT_IN {
	float3 texcoord_0 : TEXCOORD0;
	float4 texcoord_9 : TEXCOORD9;
};

uniform float3 s_sky_tangent;
uniform float3 s_sky_binormal;

uniform float4 mask_0_transform;
uniform float4 mask_1_transform;
uniform float4 clouds_0_transform;
uniform float4 clouds_1_transform;
uniform float4 clouds_2_transform;
uniform float4 clouds_3_transform;
uniform half diffuse_0_scale;
uniform half diffuse_1_scale;
uniform half clouds_01_scale;
uniform half clouds_23_scale;
uniform half clouds_01_threshold;
uniform half clouds_23_threshold;
uniform half shadow_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_depth = tex2DDepthProj(s_texture_15,IN.texcoord_9.xyw);
	float depth = getDeferredDepth(deferred_depth);
	if(depth > 0.9f) discard;
	
	half3 direction = normalize(IN.texcoord_0) * depth;
	half3 position = direction + s_camera_position / s_depth_range.y;
	half2 texcoord = half2(dot(s_sky_tangent,position),dot(s_sky_binormal,position));
	
	half mask_0 = h4tex2D(s_texture_0,texcoord * mask_0_transform.xy + mask_0_transform.zw).w;
	half mask_1 = h4tex2D(s_texture_1,texcoord * mask_1_transform.xy + mask_1_transform.zw).w;
	
	half clouds_0 = h4tex2D(s_texture_2,texcoord * clouds_0_transform.xy + clouds_0_transform.zw).w;
	half clouds_1 = h4tex2D(s_texture_2,texcoord * clouds_1_transform.xy + clouds_1_transform.zw).w;
	half clouds_2 = h4tex2D(s_texture_3,texcoord * clouds_2_transform.xy + clouds_2_transform.zw).w;
	half clouds_3 = h4tex2D(s_texture_3,texcoord * clouds_3_transform.xy + clouds_3_transform.zw).w;
	
	half clouds_01 = saturate((clouds_0 + clouds_1 - mask_0 * clouds_01_threshold) * clouds_01_scale);
	half clouds_23 = saturate((clouds_2 + clouds_3 - mask_1 * clouds_23_threshold) * clouds_23_scale);
	
	return 1.0f - max(clouds_01,clouds_23) * shadow_scale;
}

#endif
