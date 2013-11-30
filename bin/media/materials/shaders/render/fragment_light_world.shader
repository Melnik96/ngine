/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_light_world.shader
 * Desc:    Render light world shader
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

/* s_texture_0 is deferred color texture
 * s_texture_1 is deferred normal texture
 *
 * s_texture_12 is light shadow color texture
 * s_texture_13 is light shadow depth texture
 * s_texture_14 is light shadow noise texture
 */

#include <core/shaders/common/fragment_base.h>
#include <core/shaders/common/fragment_base_shadow_world.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform SAMPLER_2DMS s_texture_0;
uniform SAMPLER_2DMS s_texture_1;

SAMPLER_SHADOW_WORLD_PCF

/*
 */
void main() {
	
	half4 deferred_depth = texture2DDeferredNorm(s_texture_0,gl_TexCoord[0].xy);
	float depth = getDeferredDepth(deferred_depth);
	if(depth > 0.9f) discard;
	
	float3 position = normalize(gl_TexCoord[1].xyz) * (gl_TexCoord[1].w * depth);
	
	half4 deferred_normal = texture2DDeferredNorm(s_texture_1,gl_TexCoord[0].xy);
	half3 normal = normalize(getDeferredNormal(deferred_normal));
	half specular = getDeferredSpecular(deferred_normal);
	
	half3 camera_direction = -position;
	half3 light_direction = s_light_direction;
	
	half4 color = half4(getDiffuseDeferred(normal,light_direction),getSpecularDeferredNormalize(specular,normal,light_direction,camera_direction));
	
	#ifdef SHADOW
		half4 shadow_distances = half4(0.0f);
		float4 shadow_texcoord = float4(position,1.0f);
		#ifdef USE_TRANSLUCENT
			shadow_distances.x = dot(s_light_shadow_offsets[0].xyz - position,s_light_direction);
			shadow_distances.y = dot(s_light_shadow_offsets[1].xyz - position,s_light_direction);
			shadow_distances.z = dot(s_light_shadow_offsets[2].xyz - position,s_light_direction);
			shadow_distances.w = dot(s_light_shadow_offsets[3].xyz - position,s_light_direction);
			shadow_distances *= s_light_shadow_iradius.x;
		#endif
		color.xyz = shadowWorldPCF(color.xyz,s_texture_13,s_texture_12,s_texture_14,shadow_texcoord,shadow_distances,s_material_textures[13]);
	#endif
	
	gl_FragColor = color * 0.5f;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float2 position : VPOS;
	float2 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_depth = tex2D(s_texture_0,IN.texcoord_0);
	float depth = getDeferredDepth(deferred_depth);
	if(depth > 0.9f) discard;
	
	float3 position = normalize(IN.texcoord_1.xyz) * (IN.texcoord_1.w * depth);
	
	half4 deferred_normal = tex2D(s_texture_1,IN.texcoord_0);
	half3 normal = normalize(getDeferredNormal(deferred_normal));
	half specular = getDeferredSpecular(deferred_normal);
	
	half3 camera_direction = -position;
	half3 light_direction = s_light_direction;
	
	half4 color = half4(getDiffuseDeferred(normal,light_direction),getSpecularDeferredNormalize(specular,normal,light_direction,camera_direction));
	
	#ifdef SHADOW
		half4 shadow_distances = 0.0f;
		float4 shadow_texcoord = float4(position,1.0f);
		#ifdef USE_TRANSLUCENT
			shadow_distances.x = dot(s_light_shadow_offsets[0].xyz - position,s_light_direction);
			shadow_distances.y = dot(s_light_shadow_offsets[1].xyz - position,s_light_direction);
			shadow_distances.z = dot(s_light_shadow_offsets[2].xyz - position,s_light_direction);
			shadow_distances.w = dot(s_light_shadow_offsets[3].xyz - position,s_light_direction);
			shadow_distances *= s_light_shadow_iradius.x;
		#endif
		color.xyz = shadowWorldPCF(color.xyz,s_texture_13,s_texture_12,s_texture_14,IN.position,shadow_texcoord,shadow_distances,s_material_textures[13]);
	#endif
	
	return color * 0.5f;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

TEXTURE_2DMS s_texture_0 : register(t0);
TEXTURE_2DMS s_texture_1 : register(t1);

TEXTURE_SHADOW_WORLD_PCF

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 deferred_depth = texture2DDeferredNorm(s_texture_0,s_sampler_0,IN.texcoord_0);
	float depth = getDeferredDepth(deferred_depth);
	if(depth > 0.9f) discard;
	
	float3 position = normalize(IN.texcoord_1.xyz) * (IN.texcoord_1.w * depth);
	
	half4 deferred_normal = texture2DDeferredNorm(s_texture_1,s_sampler_1,IN.texcoord_0);
	half3 normal = normalize(getDeferredNormal(deferred_normal));
	half specular = getDeferredSpecular(deferred_normal);
	
	half3 camera_direction = -position;
	half3 light_direction = s_light_direction;
	
	half4 color = half4(getDiffuseDeferred(normal,light_direction),getSpecularDeferredNormalize(specular,normal,light_direction,camera_direction));
	
	#ifdef SHADOW
		half4 shadow_distances = 0.0f;
		float4 shadow_texcoord = float4(position,1.0f);
		#ifdef USE_TRANSLUCENT
			shadow_distances.x = dot(s_light_shadow_offsets[0].xyz - position,s_light_direction);
			shadow_distances.y = dot(s_light_shadow_offsets[1].xyz - position,s_light_direction);
			shadow_distances.z = dot(s_light_shadow_offsets[2].xyz - position,s_light_direction);
			shadow_distances.w = dot(s_light_shadow_offsets[3].xyz - position,s_light_direction);
			shadow_distances *= s_light_shadow_iradius.x;
		#endif
		color.xyz = shadowWorldPCF(color.xyz,s_texture_13,s_sampler_13,s_sampler_compare_13,s_texture_12,s_sampler_12,s_texture_14,s_sampler_14,IN.position,shadow_texcoord,shadow_distances,s_material_textures[13]);
	#endif
	
	return color * 0.5f;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

##pragma disablepc all

uniform sampler2D s_texture_0 : TEXUNIT0;
uniform sampler2D s_texture_1 : TEXUNIT1;

SAMPLER_SHADOW_WORLD_PCF

struct FRAGMENT_IN {
	float2 position : WPOS;
	float2 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_depth = h4tex2D(s_texture_0,IN.texcoord_0);
	float depth = getDeferredDepth(deferred_depth);
	if(depth > 0.9f) discard;
	
	float3 position = normalize(IN.texcoord_1.xyz) * (IN.texcoord_1.w * depth);
	
	half4 deferred_normal = h4tex2D(s_texture_1,IN.texcoord_0);
	half3 normal = normalize(getDeferredNormal(deferred_normal));
	half specular = getDeferredSpecular(deferred_normal);
	
	half3 camera_direction = -position;
	half3 light_direction = s_light_direction;
	
	half4 color = half4(getDiffuseDeferred(normal,light_direction),getSpecularDeferredNormalize(specular,normal,light_direction,camera_direction));
	
	#ifdef SHADOW
		half4 shadow_distances = 0.0f;
		float4 shadow_texcoord = float4(position,1.0f);
		float4 shadow_texcoord_01,shadow_texcoord_23;
		shadow_texcoord_01.x = dot(s_light_shadow_projections[0][0],shadow_texcoord);
		shadow_texcoord_01.y = dot(s_light_shadow_projections[0][1],shadow_texcoord);
		shadow_texcoord_01.z = dot(s_light_shadow_projections[1][0],shadow_texcoord);
		shadow_texcoord_01.w = dot(s_light_shadow_projections[1][1],shadow_texcoord);
		shadow_texcoord_23.x = dot(s_light_shadow_projections[2][0],shadow_texcoord);
		shadow_texcoord_23.y = dot(s_light_shadow_projections[2][1],shadow_texcoord);
		shadow_texcoord_23.z = dot(s_light_shadow_projections[3][0],shadow_texcoord);
		shadow_texcoord_23.w = dot(s_light_shadow_projections[3][1],shadow_texcoord);
		#ifdef USE_TRANSLUCENT
			shadow_distances.x = dot(s_light_shadow_offsets[0].xyz - position,s_light_direction);
			shadow_distances.y = dot(s_light_shadow_offsets[1].xyz - position,s_light_direction);
			shadow_distances.z = dot(s_light_shadow_offsets[2].xyz - position,s_light_direction);
			shadow_distances.w = dot(s_light_shadow_offsets[3].xyz - position,s_light_direction);
			shadow_distances *= s_light_shadow_iradius.x;
		#endif
		color.xyz = shadowWorldPCF(color.xyz,s_texture_13,s_texture_12,s_texture_14,IN.position,shadow_texcoord,shadow_texcoord_01,shadow_texcoord_23,shadow_distances);
	#endif
	
	return color * 0.5f;
}

#endif
