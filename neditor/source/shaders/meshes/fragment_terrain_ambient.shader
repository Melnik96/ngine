/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_terrain_ambient.shader
 * Desc:    Mesh terrain ambient shader
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

/* s_texture_0 is diffuse texture
 * s_texture_1 is normal texture
 * s_texture_2 is mask texture
 * s_texture_3 is detail_1 diffuse texture
 * s_texture_4 is detail_1 normal texture
 * s_texture_5 is detail_2 diffuse texture
 * s_texture_6 is detail_2 normal texture
 * s_texture_7 is detail_3 diffuse texture
 * s_texture_8 is detail_3 normal texture
 * s_texture_9 is detail_4 diffuse texture
 * s_texture_10 is detail_4 normal texture
 *
 * s_texture_11 is environment texture
 * s_texture_12 is lightmap texture
 * s_texture_13 is deferred light texture
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
uniform sampler2D s_texture_4;
uniform sampler2D s_texture_5;
uniform sampler2D s_texture_6;
uniform sampler2D s_texture_7;
uniform sampler2D s_texture_8;
uniform sampler2D s_texture_9;
uniform sampler2D s_texture_10;

uniform samplerCube s_texture_11;
uniform sampler2D s_texture_12;
uniform sampler2D s_texture_13;

uniform half4 detail_1_transform;
uniform half4 detail_2_transform;
uniform half4 detail_3_transform;
uniform half4 detail_4_transform;
uniform half detail_1_diffuse;
uniform half detail_1_normal;
uniform half detail_2_diffuse;
uniform half detail_2_normal;
uniform half detail_3_diffuse;
uniform half detail_3_normal;
uniform half detail_4_diffuse;
uniform half detail_4_normal;

uniform half environment_scale;
uniform half lightmap_scale;

/*
 */
void main() {
	
	#include <core/shaders/meshes/fragment_terrain_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif LIGHTMAP
		half3 lightmap = texture2DCubic(s_texture_12,gl_TexCoord[0].xy,s_material_textures[12]).xyz;
		half3 color = diffuse.xyz * (s_ambient_color.xyz + lightmap * lightmap_scale);
	#endif
	
	half3 world_normal;
	world_normal.x = dot(half3(gl_TexCoord[1].xyz),normal);
	world_normal.y = dot(half3(gl_TexCoord[2].xyz),normal);
	world_normal.z = dot(half3(gl_TexCoord[3].xyz),normal);
	half3 environment = textureCube(s_texture_11,world_normal).xyz;
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = texture2DProj(s_texture_13,gl_TexCoord[7]);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,specular,light);
	#endif
	
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
	half3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	#ifdef USE_DEFERRED
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half4 detail_1_transform;
half4 detail_2_transform;
half4 detail_3_transform;
half4 detail_4_transform;
half detail_1_diffuse;
half detail_1_normal;
half detail_2_diffuse;
half detail_2_normal;
half detail_3_diffuse;
half detail_3_normal;
half detail_4_diffuse;
half detail_4_normal;

half environment_scale;
half lightmap_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_terrain_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif LIGHTMAP
		half3 lightmap = tex2DCubic(s_texture_12,IN.texcoord_0.xy,s_material_textures[12]).xyz;
		half3 color = diffuse.xyz * (s_ambient_color.xyz + lightmap * lightmap_scale);
	#endif
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_1,normal);
	world_normal.y = dot(IN.texcoord_2,normal);
	world_normal.z = dot(IN.texcoord_3,normal);
	half3 environment = texCUBE(s_texture_11,world_normal).xyz;
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = tex2Dproj(s_texture_13,IN.texcoord_7);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,specular,light);
	#endif
	
	return half4(color,1.0f);
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
Texture2D s_texture_4 : register(t4);
Texture2D s_texture_5 : register(t5);
Texture2D s_texture_6 : register(t6);
Texture2D s_texture_7 : register(t7);
Texture2D s_texture_8 : register(t8);
Texture2D s_texture_9 : register(t9);
Texture2D s_texture_10 : register(t10);

TextureCube s_texture_11 : register(t11);
Texture2D s_texture_12 : register(t12);
Texture2D s_texture_13 : register(t13);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
};

cbuffer shader_parameters {
	#ifdef DETAIL_1 || DETAIL_2 || DETAIL_3 || DETAIL_4
		float4 detail_1_transform;
		float detail_1_diffuse;
		float detail_1_normal;
	#endif
	#ifdef DETAIL_2 || DETAIL_3 || DETAIL_4
		float4 detail_2_transform;
		float detail_2_diffuse;
		float detail_2_normal;
	#endif
	#ifdef DETAIL_3 || DETAIL_4
		float4 detail_3_transform;
		float detail_3_diffuse;
		float detail_3_normal;
	#endif
	#ifdef DETAIL_4
		float4 detail_4_transform;
		float detail_4_diffuse;
		float detail_4_normal;
	#endif
	float environment_scale;
	#ifdef LIGHTMAP
		float lightmap_scale;
	#endif
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#include <core/shaders/meshes/fragment_terrain_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif LIGHTMAP
		half3 lightmap = texture2DCubic(s_texture_12,s_sampler_12,IN.texcoord_0.xy,s_material_textures[12]).xyz;
		half3 color = diffuse.xyz * (s_ambient_color.xyz + lightmap * lightmap_scale);
	#endif
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_1,normal);
	world_normal.y = dot(IN.texcoord_2,normal);
	world_normal.z = dot(IN.texcoord_3,normal);
	half3 environment = s_texture_11.Sample(s_sampler_11,world_normal).xyz;
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = s_texture_13.Sample(s_sampler_13,IN.position.xy * s_viewport.zw);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,specular,light);
	#endif
	
	return float4(color,1.0f);
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
uniform sampler2D s_texture_4 : TEXUNIT4;
uniform sampler2D s_texture_5 : TEXUNIT5;
uniform sampler2D s_texture_6 : TEXUNIT6;
uniform sampler2D s_texture_7 : TEXUNIT7;
uniform sampler2D s_texture_8 : TEXUNIT8;
uniform sampler2D s_texture_9 : TEXUNIT9;
uniform sampler2D s_texture_10 : TEXUNIT10;

uniform samplerCUBE s_texture_11 : TEXUNIT11;
uniform sampler2D s_texture_12 : TEXUNIT12;
uniform sampler2D s_texture_13 : TEXUNIT13;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	#ifdef USE_DEFERRED
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half4 detail_1_transform;
uniform half4 detail_2_transform;
uniform half4 detail_3_transform;
uniform half4 detail_4_transform;
uniform half detail_1_diffuse;
uniform half detail_1_normal;
uniform half detail_2_diffuse;
uniform half detail_2_normal;
uniform half detail_3_diffuse;
uniform half detail_3_normal;
uniform half detail_4_diffuse;
uniform half detail_4_normal;

uniform half environment_scale;
uniform half lightmap_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/terrains/fragment_base_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif LIGHTMAP
		half3 lightmap = h3tex2D(s_texture_12,IN.texcoord_0.xy);
		half3 color = diffuse.xyz * (s_ambient_color.xyz + lightmap * lightmap_scale);
	#endif
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_1,normal);
	world_normal.y = dot(IN.texcoord_2,normal);
	world_normal.z = dot(IN.texcoord_3,normal);
	half3 environment = h3texCUBE(s_texture_11,world_normal);
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = h4tex2Dproj(s_texture_13,IN.texcoord_9.xyw);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,specular,light);
	#endif
	
	return half4(color,1.0f);
}

#endif
