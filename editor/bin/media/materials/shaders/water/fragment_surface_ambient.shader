/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_surface_ambient.shader
 * Desc:    Water surface ambient shader
 * Version: 1.10
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
 * s_texture_1 is normal_23 texture
 * s_texture_2 is foam texture
 * s_texture_3 is reflection texture
 * 
 * s_texture_12 is deferred depth texture
 * s_texture_13 is environment texture
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

uniform SAMPLER_2DMS s_texture_12;
uniform samplerCube s_texture_13;

uniform float3 s_water_direction;

uniform half4 foam_0_transform;
uniform half4 foam_1_transform;
uniform half reflection_normal;
uniform half4 reflection_color;
uniform half4 surface_color;
uniform half foam_scale;
uniform half foam_threshold;
uniform half foam_falloff;
uniform half environment_scale;

/*
 */
void main() {
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	half3 color = surface_color.xyz;
	
	#include <core/shaders/water/fragment_surface_foam.h>
	
	half3 environment = textureCube(s_texture_13,gl_TexCoord[1].xyz).xyz;
	color *= (s_ambient_color.xyz + environment * environment_scale);
	
	#ifdef USE_REFLECTION
		half3 camera_direction = gl_TexCoord[3].xyz;
		half fresnel = getFresnelNormalize(normal,camera_direction);
		
		half2 offset = normal.xy * saturate(gl_TexCoord[0].z / gl_TexCoord[0].w);
		half3 reflection = texture2D(s_texture_3,gl_TexCoord[4].xy / gl_TexCoord[4].w + offset).xyz;
		
		#ifdef QUALITY_MEDIUM && FOAM
			color += reflection * reflection_color.xyz * fresnel * (1.0f - foam);
		#else
			color += reflection * reflection_color.xyz * fresnel;
		#endif
	#endif
	
	gl_FragColor = half4(color * fog,1.0f);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	float4 texcoord_4 : TEXCOORD4;
	float4 texcoord_5 : TEXCOORD5;
	float4 texcoord_6 : TEXCOORD6;
	float4 texcoord_7 : TEXCOORD7;
};

float3 s_water_direction;

half4 foam_0_transform;
half4 foam_1_transform;
half reflection_normal;
half4 reflection_color;
half4 surface_color;
half foam_scale;
half foam_threshold;
half foam_falloff;
half environment_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	half3 color = surface_color.xyz;
	
	#include <core/shaders/water/fragment_surface_foam.h>
	
	half3 environment = texCUBE(s_texture_13,IN.texcoord_1).xyz;
	color *= (s_ambient_color.xyz + environment * environment_scale);
	
	#ifdef USE_REFLECTION
		half3 camera_direction = IN.texcoord_3;
		half fresnel = getFresnelNormalize(normal,camera_direction);
		
		half2 offset = normal.xy * saturate(IN.texcoord_0.z / IN.texcoord_0.w);
		half3 reflection = tex2D(s_texture_3,IN.texcoord_4.xy / IN.texcoord_4.w + offset).xyz;
		
		#ifdef QUALITY_MEDIUM && FOAM
			color += reflection * reflection_color.xyz * fresnel * (1.0f - foam);
		#else
			color += reflection * reflection_color.xyz * fresnel;
		#endif
	#endif
	
	return half4(color * fog,1.0f);
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

TEXTURE_2DMS s_texture_12 : register(t12);
TextureCube s_texture_13 : register(t13);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	float4 texcoord_4 : TEXCOORD4;
	float4 texcoord_7 : TEXCOORD7;
	float4 texcoord_8 : TEXCOORD8;
	float4 texcoord_9 : TEXCOORD9;
};

cbuffer shader_water_parameters {
	float3 s_water_direction;
};

cbuffer shader_parameters {
	float reflection_normal;
	float4 reflection_color;
	float4 surface_color;
	float foam_scale;
	float foam_threshold;
	float foam_falloff;
	float environment_scale;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	half3 color = surface_color.xyz;
	
	#include <core/shaders/water/fragment_surface_foam.h>
	
	half3 environment = s_texture_13.Sample(s_sampler_13,IN.texcoord_1).xyz;
	color *= (s_ambient_color.xyz + environment * environment_scale);
	
	#ifdef USE_REFLECTION
		half3 camera_direction = IN.texcoord_3;
		half fresnel = getFresnelNormalize(normal,camera_direction);
		
		half2 offset = normal.xy * saturate(IN.texcoord_0.z / IN.texcoord_0.w);
		half3 reflection = s_texture_3.Sample(s_sampler_3,IN.texcoord_4.xy / IN.texcoord_4.w + offset).xyz;
		
		#ifdef QUALITY_MEDIUM && FOAM
			color += reflection * reflection_color.xyz * fresnel * (1.0f - foam);
		#else
			color += reflection * reflection_color.xyz * fresnel;
		#endif
	#endif
	
	return float4(color * fog,1.0f);
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

uniform sampler2D s_texture_12 : TEXUNIT12;
uniform samplerCUBE s_texture_13 : TEXUNIT13;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	float4 texcoord_4 : TEXCOORD4;
	float4 texcoord_7 : TEXCOORD7;
	float4 texcoord_8 : TEXCOORD8;
	float4 texcoord_9 : TEXCOORD9;
};

uniform float3 s_water_direction;

uniform half4 foam_0_transform;
uniform half4 foam_1_transform;
uniform half reflection_normal;
uniform half4 reflection_color;
uniform half4 surface_color;
uniform half foam_scale;
uniform half foam_threshold;
uniform half foam_falloff;
uniform half environment_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	half3 color = surface_color.xyz;
	
	#include <core/shaders/water/fragment_surface_foam.h>
	
	half3 environment = h3texCUBE(s_texture_13,IN.texcoord_1);
	color *= (s_ambient_color.xyz + environment * environment_scale);
	
	#ifdef USE_REFLECTION
		half3 camera_direction = IN.texcoord_3;
		half fresnel = getFresnelNormalize(normal,camera_direction);
		
		half2 offset = normal.xy * saturate(IN.texcoord_0.z / IN.texcoord_0.w);
		half3 reflection = h3tex2D(s_texture_3,IN.texcoord_4.xy / IN.texcoord_4.w + offset);
		
		#ifdef QUALITY_MEDIUM && FOAM
			color += reflection * reflection_color.xyz * fresnel * (1.0f - foam);
		#else
			color += reflection * reflection_color.xyz * fresnel;
		#endif
	#endif
	
	return half4(color * fog,1.0f);
}

#endif
