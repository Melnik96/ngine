/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_light_spot.shader
 * Desc:    Render light spot shader
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
 * s_texture_1 is deferred depth texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform SAMPLER_2DMS s_texture_0;
uniform SAMPLER_2DMS s_texture_1;

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
	
	half3 camera_direction = normalize(-position);
	
	half4 color = half4(0.0f);
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - position) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half4 light = half4(s_light_colors[NUMBER].xyz * (saturate(dot(light_direction,normal) * light_direction_ilength) * s_material_shadings[NUMBER].x), \
			pow(saturate(dot(reflect(-light_direction,normal),camera_direction) * light_direction_ilength),max(specular * s_material_shadings[NUMBER].z,1e-6f)) * s_material_shadings[NUMBER].y); \
		color += light * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
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
	
	half3 camera_direction = normalize(-position);
	
	half4 color = 0.0f;
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - position) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half4 light = half4(s_light_colors[NUMBER].xyz * (saturate(dot(light_direction,normal) * light_direction_ilength) * s_material_shadings[NUMBER].x), \
			pow(saturate(dot(reflect(-light_direction,normal),camera_direction) * light_direction_ilength),max(specular * s_material_shadings[NUMBER].z,1e-6f)) * s_material_shadings[NUMBER].y); \
		color += light * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
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
	
	half3 camera_direction = normalize(-position);
	
	half4 color = 0.0f;
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - position) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half4 light = half4(s_light_colors[NUMBER].xyz * (saturate(dot(light_direction,normal) * light_direction_ilength) * s_material_shadings[NUMBER].x), \
			pow(saturate(dot(reflect(-light_direction,normal),camera_direction) * light_direction_ilength),max(specular * s_material_shadings[NUMBER].z,1e-6f)) * s_material_shadings[NUMBER].y); \
		color += light * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
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
	
	half3 camera_direction = normalize(-position);
	
	half4 color = 0.0f;
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - position) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half4 light = half4(s_light_colors[NUMBER].xyz * (saturate(dot(light_direction,normal) * light_direction_ilength) * s_material_shadings[NUMBER].x), \
			pow(saturate(dot(reflect(-light_direction,normal),camera_direction) * light_direction_ilength),max(specular * s_material_shadings[NUMBER].z,1e-6f)) * s_material_shadings[NUMBER].y); \
		color += light * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
	return color * 0.5f;
}

#endif
