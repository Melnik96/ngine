/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_deferred.shader
 * Desc:    Render deferred shading shader
 * Version: 1.01
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
 * s_texture_2 is deferred light texture
 * s_texture_3 is environment texture
 */

#include <core/shaders/common/fragment_base.h>
#include <core/shaders/common/fragment_base_shadow_proj.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform SAMPLER_2DMS s_texture_0;
uniform SAMPLER_2DMS s_texture_1;
uniform sampler2D s_texture_2;
uniform samplerCube s_texture_3;

uniform half4 modelview_x;
uniform half4 modelview_y;
uniform half4 modelview_z;

/*
 */
void main() {
	
	half4 deferred_color = texture2DDeferredNorm(s_texture_0,gl_TexCoord[0].xy);
	half4 deferred_normal = texture2DDeferredNorm(s_texture_1,gl_TexCoord[0].xy);
	half4 deferred_light = texture2D(s_texture_2,gl_TexCoord[0].xy);
	
	half3 diffuse = getDeferredColor(deferred_color);
	half3 normal = normalize(getDeferredNormal(deferred_normal));
	
	#ifdef USE_SRGB
		diffuse *= diffuse;
	#endif
	
	half3 world_normal;
	world_normal.x = dot(modelview_x.xyz,normal);
	world_normal.y = dot(modelview_y.xyz,normal);
	world_normal.z = dot(modelview_z.xyz,normal);
	
	half3 environment = textureCube(s_texture_3,world_normal).xyz;
	
	half3 color = diffuse * (s_ambient_color.xyz + environment + deferred_light.xyz * (2.0f + deferred_light.w * 2.0f));
	
	gl_FragColor = half4(color,1.0f);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
};

half4 modelview_x;
half4 modelview_y;
half4 modelview_z;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_color = tex2D(s_texture_0,IN.texcoord_0);
	half4 deferred_normal = tex2D(s_texture_1,IN.texcoord_0);
	half4 deferred_light = tex2D(s_texture_2,IN.texcoord_0);
	
	half3 diffuse = getDeferredColor(deferred_color);
	half3 normal = normalize(getDeferredNormal(deferred_normal));
	
	#ifdef USE_SRGB
		diffuse *= diffuse;
	#endif
	
	half3 world_normal;
	world_normal.x = dot(modelview_x.xyz,normal);
	world_normal.y = dot(modelview_y.xyz,normal);
	world_normal.z = dot(modelview_z.xyz,normal);
	
	half3 environment = texCUBE(s_texture_3,world_normal).xyz;
	
	half3 color = diffuse * (s_ambient_color.xyz + environment + deferred_light.xyz * (2.0f + deferred_light.w * 2.0f));
	
	return half4(color,1.0f);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

TEXTURE_2DMS s_texture_0 : register(t0);
TEXTURE_2DMS s_texture_1 : register(t1);
Texture2D s_texture_2 : register(t2);
TextureCube s_texture_3 : register(t3);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
};

float4 modelview_x;
float4 modelview_y;
float4 modelview_z;

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 deferred_color = texture2DDeferredNorm(s_texture_0,s_sampler_0,IN.texcoord_0);
	half4 deferred_normal = texture2DDeferredNorm(s_texture_1,s_sampler_0,IN.texcoord_0);
	half4 deferred_light = s_texture_2.Sample(s_sampler_2,IN.texcoord_0);
	
	half3 diffuse = getDeferredColor(deferred_color);
	half3 normal = normalize(getDeferredNormal(deferred_normal));
	
	#ifdef USE_SRGB
		diffuse *= diffuse;
	#endif
	
	half3 world_normal;
	world_normal.x = dot(modelview_x.xyz,normal);
	world_normal.y = dot(modelview_y.xyz,normal);
	world_normal.z = dot(modelview_z.xyz,normal);
	
	half3 environment = s_texture_3.Sample(s_sampler_3,world_normal).xyz;
	
	half3 color = diffuse * (s_ambient_color.xyz + environment + deferred_light.xyz * (2.0f + deferred_light.w * 2.0f));
	
	return half4(color,1.0f);
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
uniform sampler2D s_texture_2 : TEXUNIT2;
uniform samplerCUBE s_texture_3 : TEXUNIT3;

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
};

uniform half4 modelview_x;
uniform half4 modelview_y;
uniform half4 modelview_z;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_color = h4tex2D(s_texture_0,IN.texcoord_0);
	half4 deferred_normal = h4tex2D(s_texture_1,IN.texcoord_0);
	half4 deferred_light = h4tex2D(s_texture_2,IN.texcoord_0);
	
	half3 diffuse = getDeferredColor(deferred_color);
	half3 normal = normalize(getDeferredNormal(deferred_normal));
	
	#ifdef USE_SRGB
		diffuse *= diffuse;
	#endif
	
	half3 world_normal;
	world_normal.x = dot(modelview_x.xyz,normal);
	world_normal.y = dot(modelview_y.xyz,normal);
	world_normal.z = dot(modelview_z.xyz,normal);
	
	half3 environment = h3texCUBE(s_texture_3,world_normal);
	
	half3 color = diffuse * (s_ambient_color.xyz + environment + deferred_light.xyz * (2.0f + deferred_light.w * 2.0f));
	
	return half4(color,1.0f);
}

#endif
