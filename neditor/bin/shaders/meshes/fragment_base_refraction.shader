/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_refraction.shader
 * Desc:    Mesh base reraction shader
 * Version: 1.13
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
 * s_texture_3 is detail diffuse texture
 * s_texture_4 is detail normal texture
 * s_texture_5 is detail specular texture
 * 
 * s_texture_9 is alpha fade texture
 * s_texture_10 is deferred parallax texture
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

uniform sampler2D s_texture_9;
uniform SAMPLER_2DMS s_texture_10;

uniform half4 detail_transform;
uniform half refraction_scale;

/*
 */
void main() {
	
	#include <core/shaders/meshes/fragment_base_sample.h>
	
	half2 screen_normal;
	screen_normal.x = dot(normalize(half3(gl_TexCoord[1].xyz)).xy,normal.xy);
	screen_normal.y = dot(normalize(half3(gl_TexCoord[2].xyz)).xy,normal.xy);
	
	half4 color = saturate(half4(screen_normal,-screen_normal));
	
	gl_FragColor = color * (refraction_scale * saturate(gl_TexCoord[3].x / gl_TexCoord[3].y)) + 1.0f / 255.0f;
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
	float2 texcoord_3 : TEXCOORD3;
	#ifdef (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half4 detail_transform;
half refraction_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_base_sample.h>
	
	half2 screen_normal;
	screen_normal.x = dot(normalize(IN.texcoord_1).xy,normal.xy);
	screen_normal.y = dot(normalize(IN.texcoord_2).xy,normal.xy);
	
	half4 color = saturate(half4(screen_normal,-screen_normal));
	
	return color * (refraction_scale * saturate(IN.texcoord_3.x / IN.texcoord_3.y)) + 1.0f / 255.0f;
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

Texture2D s_texture_9 : register(t9);
TEXTURE_2DMS s_texture_10 : register(t10);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	float2 texcoord_3 : TEXCOORD3;
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

cbuffer shader_parameters {
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		float4 detail_transform;
	#endif
	float refraction_scale;
};

/*
 */
FRAGMENT_ALPHA_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_ALPHA_OUT OUT;
	
	#include <core/shaders/meshes/fragment_base_sample.h>
	
	half2 screen_normal;
	screen_normal.x = dot(normalize(IN.texcoord_1).xy,normal.xy);
	screen_normal.y = dot(normalize(IN.texcoord_2).xy,normal.xy);
	
	half4 color = saturate(half4(screen_normal,-screen_normal));
	
	OUT.color = color * (refraction_scale * saturate(IN.texcoord_3.x / IN.texcoord_3.y)) + 1.0f / 255.0f;
	
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
uniform sampler2D s_texture_3 : TEXUNIT3;
uniform sampler2D s_texture_4 : TEXUNIT4;
uniform sampler2D s_texture_5 : TEXUNIT5;

uniform sampler2D s_texture_9 : TEXUNIT9;
uniform sampler2D s_texture_10 : TEXUNIT10;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	float2 texcoord_3 : TEXCOORD3;
	#ifdef (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half4 detail_transform;
uniform half refraction_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_base_sample.h>
	
	half2 screen_normal;
	screen_normal.x = dot(normalize(IN.texcoord_1).xy,normal.xy);
	screen_normal.y = dot(normalize(IN.texcoord_2).xy,normal.xy);
	
	half4 color = saturate(half4(screen_normal,-screen_normal));
	
	return color * (refraction_scale * saturate(IN.texcoord_3.x / IN.texcoord_3.y)) + 1.0f / 255.0f;
}

#endif
