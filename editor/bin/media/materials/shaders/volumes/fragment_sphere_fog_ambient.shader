/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_sphere_fog_ambient.shader
 * Desc:    VolumeSphere fog ambient shader
 * Version: 1.18
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
 * s_texture_15 is deferred depth texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler3D s_texture_0;

uniform SAMPLER_2DMS s_texture_15;

uniform float4 s_volume_icamera_position;
uniform float4 s_volume_intersection;
uniform half s_volume_fade;

uniform half4 diffuse_color;
uniform half volume_power;
uniform half noise_scale;
uniform float4 noise_transform;

/*
 */
void main() {
	
	half4 deferred_depth = texture2DDeferredProj(s_texture_15,gl_TexCoord[7],s_material_textures[15].xy);
	
	float a = dot(s_volume_intersection.xyz,gl_TexCoord[0].xyz * gl_TexCoord[0].xyz);
	float b = dot(s_volume_intersection.xyz,gl_TexCoord[0].xyz * gl_TexCoord[1].xyz);
	float c = dot(s_volume_intersection,gl_TexCoord[1] * gl_TexCoord[1]);
	float d = sqrt(b * b - a * c);
	float e = -b - a;
	float x0 = (e + d) / a;
	float x1 = (e - d) / a;
	
	float front = length(gl_TexCoord[0].xyz * max(x0,x1)) / s_depth_range.y;
	float back = length(gl_TexCoord[0].xyz * min(x0,x1)) / s_depth_range.y;
	
	float near = min(back,getDeferredDepth(deferred_depth));
	float depth = max(near - front * s_volume_icamera_position.w,0.0f);
	
	#ifdef HEIGHT
		float3 dir = normalize(gl_TexCoord[3].xyz) * s_depth_range.y;
		float4 vertex_front = float4(s_volume_icamera_position.xyz + dir * front,1.0f);
		float4 vertex_near = float4(s_volume_icamera_position.xyz + dir * near,1.0f);
		float height_front = dot(gl_TexCoord[4],vertex_front);
		float height_near = dot(gl_TexCoord[4],vertex_near);
		float falloff = height_near - height_front;
		if(abs(falloff) > 0.0f) depth *= (1.0f - exp2(-falloff)) / falloff;
		depth *= exp2(-height_front);
	#endif
	
	half fog = exp2(-pow(gl_TexCoord[2].x * depth,volume_power));
	
	#ifdef NOISE
		float3 noise_texcoord = float3(gl_TexCoord[7].xy * gl_TexCoord[5].xy / gl_TexCoord[7].w,noise_transform.x + fog);
		half noise_1 = texture3D(s_texture_0,noise_texcoord * float3(1.0f,1.0f,0.7f)).x;
		half noise_2 = texture3D(s_texture_0,noise_texcoord * float3(0.7f,0.7f,0.3f)).x;
		fog += (noise_1 - noise_2) * noise_scale * (1.0f - fog);
	#endif
	
	gl_FragColor = half4(diffuse_color.xyz,(1.0f - fog) * s_volume_fade);
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
	float1 texcoord_2 : TEXCOORD2;
	#ifdef HEIGHT
		float3 texcoord_3 : TEXCOORD3;
		float4 texcoord_4 : TEXCOORD4;
	#endif
	#ifdef NOISE
		float2 texcoord_5 : TEXCOORD5;
	#endif
	float4 texcoord_7 : TEXCOORD7;
};

float4 s_volume_icamera_position;
float4 s_volume_intersection;
half s_volume_fade;

half4 diffuse_color;
half volume_power;
half noise_scale;
float4 noise_transform;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_depth = tex2Dproj(s_texture_15,IN.texcoord_7);
	
	float a = dot(s_volume_intersection.xyz,IN.texcoord_0.xyz * IN.texcoord_0.xyz);
	float b = dot(s_volume_intersection.xyz,IN.texcoord_0.xyz * IN.texcoord_1.xyz);
	float c = dot(s_volume_intersection,IN.texcoord_1 * IN.texcoord_1);
	float d = sqrt(b * b - a * c);
	float e = -b - a;
	float x0 = (e + d) / a;
	float x1 = (e - d) / a;
	
	float front = length(IN.texcoord_0.xyz * max(x0,x1)) / s_depth_range.y;
	float back = length(IN.texcoord_0.xyz * min(x0,x1)) / s_depth_range.y;
	
	float near = min(back,getDeferredDepth(deferred_depth));
	float depth = max(near - front * s_volume_icamera_position.w,0.0f);
	
	#ifdef HEIGHT
		float3 dir = normalize(IN.texcoord_3) * s_depth_range.y;
		float4 vertex_front = float4(s_volume_icamera_position.xyz + dir * front,1.0f);
		float4 vertex_near = float4(s_volume_icamera_position.xyz + dir * near,1.0f);
		float height_front = dot(IN.texcoord_4,vertex_front);
		float height_near = dot(IN.texcoord_4,vertex_near);
		float falloff = height_near - height_front;
		if(abs(falloff) > 0.0f) depth *= (1.0f - exp2(-falloff)) / falloff;
		depth *= exp2(-height_front);
	#endif
	
	half fog = exp2(-pow(IN.texcoord_2.x * depth,volume_power));
	
	#ifdef NOISE
		float3 noise_texcoord = float3(IN.texcoord_7.xy * IN.texcoord_5 / IN.texcoord_7.w,noise_transform.x + fog);
		half noise_1 = tex3D(s_texture_0,noise_texcoord * float3(1.0f,1.0f,0.7f)).x;
		half noise_2 = tex3D(s_texture_0,noise_texcoord * float3(0.7f,0.7f,0.3f)).x;
		fog += (noise_1 - noise_2) * noise_scale * (1.0f - fog);
	#endif
	
	return half4(diffuse_color.xyz,(1.0f - fog) * s_volume_fade);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture3D s_texture_0 : register(t0);

TEXTURE_2DMS s_texture_15 : register(t15);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0_centroid;
	float4 texcoord_1 : TEXCOORD1_centroid;
	float1 texcoord_2 : TEXCOORD2;
	#ifdef HEIGHT
		float3 texcoord_3 : TEXCOORD3;
		float4 texcoord_4 : TEXCOORD4;
	#endif
	#ifdef NOISE
		float2 texcoord_5 : TEXCOORD5;
	#endif
};

cbuffer shader_volume_parameters {
	float4 s_volume_icamera_position;
	float4 s_volume_intersection;
	float s_volume_fade;
};

cbuffer shader_parameters {
	float4 diffuse_color;
	float volume_power;
	float noise_scale;
	float4 noise_transform;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 deferred_depth = texture2DDeferredRect(s_texture_15,s_sampler_15,IN.position.xy,s_material_textures[15].xy);
	
	float a = dot(s_volume_intersection.xyz,IN.texcoord_0.xyz * IN.texcoord_0.xyz);
	float b = dot(s_volume_intersection.xyz,IN.texcoord_0.xyz * IN.texcoord_1.xyz);
	float c = dot(s_volume_intersection,IN.texcoord_1 * IN.texcoord_1);
	float d = sqrt(b * b - a * c);
	float e = -b - a;
	float x0 = (e + d) / a;
	float x1 = (e - d) / a;
	
	float front = length(IN.texcoord_0.xyz * max(x0,x1)) / s_depth_range.y;
	float back = length(IN.texcoord_0.xyz * min(x0,x1)) / s_depth_range.y;
	
	float near = min(back,getDeferredDepth(deferred_depth));
	float depth = max(near - front * s_volume_icamera_position.w,0.0f);
	
	#ifdef HEIGHT
		float3 dir = normalize(IN.texcoord_3) * s_depth_range.y;
		float4 vertex_front = float4(s_volume_icamera_position.xyz + dir * front,1.0f);
		float4 vertex_near = float4(s_volume_icamera_position.xyz + dir * near,1.0f);
		float height_front = dot(IN.texcoord_4,vertex_front);
		float height_near = dot(IN.texcoord_4,vertex_near);
		float falloff = height_near - height_front;
		if(abs(falloff) > 0.0f) depth *= (1.0f - exp2(-falloff)) / falloff;
		depth *= exp2(-height_front);
	#endif
	
	half fog = exp2(-pow(IN.texcoord_2.x * depth,volume_power));
	
	#ifdef NOISE
		float3 noise_texcoord = float3(IN.position.xy * IN.texcoord_5,noise_transform.x + fog);
		half noise_1 = s_texture_0.Sample(s_sampler_0,noise_texcoord * float3(1.0f,1.0f,0.7f)).x;
		half noise_2 = s_texture_0.Sample(s_sampler_0,noise_texcoord * float3(0.7f,0.7f,0.3f)).x;
		fog += (noise_1 - noise_2) * noise_scale * (1.0f - fog);
	#endif
	
	return float4(diffuse_color.xyz,(1.0f - fog) * s_volume_fade);
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler3D s_texture_0 : TEXUNIT0;

uniform sampler2D s_texture_15 : TEXUNIT15;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float1 texcoord_2 : TEXCOORD2;
	#ifdef HEIGHT
		float3 texcoord_3 : TEXCOORD3;
		float4 texcoord_4 : TEXCOORD4;
	#endif
	#ifdef NOISE
		float2 texcoord_5 : TEXCOORD5;
	#endif
	float4 texcoord_9 : TEXCOORD9;
};

uniform float4 s_volume_icamera_position;
uniform float4 s_volume_intersection;
uniform half s_volume_fade;

uniform half4 diffuse_color;
uniform half volume_power;
uniform half noise_scale;
uniform float4 noise_transform;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_depth = h4tex2Dproj(s_texture_15,IN.texcoord_9.xyw);
	
	float a = dot(s_volume_intersection.xyz,IN.texcoord_0.xyz * IN.texcoord_0.xyz);
	float b = dot(s_volume_intersection.xyz,IN.texcoord_0.xyz * IN.texcoord_1.xyz);
	float c = dot(s_volume_intersection,IN.texcoord_1 * IN.texcoord_1);
	float d = sqrt(b * b - a * c);
	float e = -b - a;
	float x0 = (e + d) / a;
	float x1 = (e - d) / a;
	
	float front = length(IN.texcoord_0.xyz * max(x0,x1)) / s_depth_range.y;
	float back = length(IN.texcoord_0.xyz * min(x0,x1)) / s_depth_range.y;
	
	float near = min(back,getDeferredDepth(deferred_depth));
	float depth = max(near - front * s_volume_icamera_position.w,0.0f);
	
	#ifdef HEIGHT
		float3 dir = normalize(IN.texcoord_3) * s_depth_range.y;
		float4 vertex_front = float4(s_volume_icamera_position.xyz + dir * front,1.0f);
		float4 vertex_near = float4(s_volume_icamera_position.xyz + dir * near,1.0f);
		float height_front = dot(IN.texcoord_4,vertex_front);
		float height_near = dot(IN.texcoord_4,vertex_near);
		float falloff = height_near - height_front;
		if(abs(falloff) > 0.0f) depth *= (1.0f - exp2(-falloff)) / falloff;
		depth *= exp2(-height_front);
	#endif
	
	half fog = exp2(-pow(IN.texcoord_2.x * depth,volume_power));
	
	#ifdef NOISE
		float3 noise_texcoord = float3(IN.texcoord_9.xy * IN.texcoord_5 / IN.texcoord_9.w,noise_transform.x + fog);
		half noise_1 = h1tex3D(s_texture_0,noise_texcoord * float3(1.0f,1.0f,0.7f));
		half noise_2 = h1tex3D(s_texture_0,noise_texcoord * float3(0.7f,0.7f,0.3f));
		fog += (noise_1 - noise_2) * noise_scale * (1.0f - fog);
	#endif
	
	return half4(diffuse_color.xyz,(1.0f - fog) * s_volume_fade);
}

#endif
