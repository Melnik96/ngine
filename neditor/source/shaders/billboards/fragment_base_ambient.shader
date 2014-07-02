/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_ambient.shader
 * Desc:    Billboard base ambient shader
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

/* s_texture_0 is diffuse texture
 * s_texture_1 is normal texture
 * s_texture_2 is specular texture
 * 
 * s_texture_10 is alpha fade texture
 * s_texture_11 is emission texture
 * s_texture_12 is environment texture
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

uniform sampler2D s_texture_10;
uniform sampler2D s_texture_11;
uniform samplerCube s_texture_12;
uniform sampler2D s_texture_13;

uniform half emission_scale;
uniform half environment_scale;
uniform half4 color_scale;

/*
 */
void main() {
	
	#include <core/shaders/billboards/fragment_base_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif TRANSPARENT
		half3 color = diffuse.xyz;
	#endif
	
	#ifdef EMISSION
		half3 emission = texture2D(s_texture_11,gl_TexCoord[0].xy).xyz;
		color += emission * emission_scale;
	#endif
	
	half3 world_normal;
	world_normal.x = dot(half3(gl_TexCoord[1].xyz),normal);
	world_normal.y = dot(half3(gl_TexCoord[2].xyz),normal);
	world_normal.z = dot(half3(gl_TexCoord[3].xyz),normal);
	half3 environment = textureCube(s_texture_12,world_normal).xyz;
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = texture2DProj(s_texture_13,gl_TexCoord[7]);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,specular.xyz,light);
	#endif
	
	gl_FragColor = half4(color,diffuse.w) * color_scale;
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
	#ifdef USE_DEFERRED || (USE_ALPHA_FADE && ALPHA_FADE)
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half emission_scale;
half environment_scale;
half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/billboards/fragment_base_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif TRANSPARENT
		half3 color = diffuse.xyz;
	#endif
	
	#ifdef EMISSION
		half3 emission = tex2D(s_texture_11,IN.texcoord_0.xy).xyz;
		color += emission * emission_scale;
	#endif
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_1,normal);
	world_normal.y = dot(IN.texcoord_2,normal);
	world_normal.z = dot(IN.texcoord_3,normal);
	half3 environment = texCUBE(s_texture_12,world_normal).xyz;
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = tex2Dproj(s_texture_13,IN.texcoord_7);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,specular.xyz,light);
	#endif
	
	return half4(color,diffuse.w) * color_scale;
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

Texture2D s_texture_10 : register(t10);
Texture2D s_texture_11 : register(t11);
TextureCube s_texture_12 : register(t12);
Texture2D s_texture_13 : register(t13);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

cbuffer shader_parameters {
	#ifdef EMISSION
		float emission_scale;
	#endif
	float environment_scale;
	float4 color_scale;
};

/*
 */
FRAGMENT_ALPHA_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_ALPHA_OUT OUT;
	
	#include <core/shaders/billboards/fragment_base_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif TRANSPARENT
		half3 color = diffuse.xyz;
	#endif
	
	#ifdef EMISSION
		half4 emission = s_texture_11.Sample(s_sampler_11,IN.texcoord_0.xy);
		color += emission.xyz * emission_scale;
	#endif
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_1,normal);
	world_normal.y = dot(IN.texcoord_2,normal);
	world_normal.z = dot(IN.texcoord_3,normal);
	half3 environment = s_texture_12.Sample(s_sampler_12,world_normal).xyz;
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = s_texture_13.Sample(s_sampler_13,IN.position.xy * s_viewport.zw);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,specular.xyz,light);
	#endif
	
	OUT.color = half4(color,diffuse.w) * color_scale;
	
	return OUT;
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

uniform sampler2D s_texture_10 : TEXUNIT10;
uniform sampler2D s_texture_11 : TEXUNIT11;
uniform samplerCUBE s_texture_12 : TEXUNIT12;
uniform sampler2D s_texture_13 : TEXUNIT13;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	#ifdef USE_DEFERRED || (USE_ALPHA_FADE && ALPHA_FADE)
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half emission_scale;
uniform half environment_scale;
uniform half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/billboards/fragment_base_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif TRANSPARENT
		half3 color = diffuse.xyz;
	#endif
	
	#ifdef EMISSION
		half3 emission = h3tex2D(s_texture_11,IN.texcoord_0.xy);
		color += emission * emission_scale;
	#endif
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_1,normal);
	world_normal.y = dot(IN.texcoord_2,normal);
	world_normal.z = dot(IN.texcoord_3,normal);
	half3 environment = h3texCUBE(s_texture_12,world_normal);
	color += diffuse.xyz * environment * environment_scale;
	
	#ifdef USE_DEFERRED
		half4 light = h4tex2Dproj(s_texture_13,IN.texcoord_9.xyw);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,specular.xyz,light);
	#endif
	
	return half4(color,diffuse.w) * color_scale;
}

#endif
