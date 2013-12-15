/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_light_world.shader
 * Desc:    Grass base light world shader
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

/* s_texture_0 is diffuse texture
 * s_texture_1 is noise texture
 * 
 * s_texture_14 is light shadow depth texture
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

uniform SAMPLER_SHADOW_DEPTH_WORLD s_texture_14;

uniform half noise_scale;

/*
 */
void main() {
	
	#include <core/shaders/grass/fragment_base_light.h>
	
	#ifdef QUALITY_MEDIUM
		#ifdef SHADOW
			color *= shadowWorld(s_texture_14,gl_TexCoord[2].xyz,gl_TexCoord[3].xyz,gl_TexCoord[4].xyz,gl_TexCoord[5].xyz,s_material_textures[14]);
		#endif
	#endif
	
	gl_FragColor = half4(color,diffuse.w);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
	#ifdef SHADOW
		float3 texcoord_2 : TEXCOORD2;
		float3 texcoord_3 : TEXCOORD3;
		float3 texcoord_4 : TEXCOORD4;
		float3 texcoord_5 : TEXCOORD5;
	#endif
};

half noise_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/grass/fragment_base_light.h>
	
	#ifdef QUALITY_MEDIUM
		#ifdef SHADOW
			color *= shadowWorld(s_texture_14,IN.texcoord_2,IN.texcoord_3,IN.texcoord_4,IN.texcoord_5,s_material_textures[14]);
		#endif
	#endif
	
	return half4(color,diffuse.w);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
Texture2D s_texture_1 : register(t1);

TEXTURE_SHADOW_WORLD s_texture_14 : register(t14);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	#ifdef SHADOW
		float3 texcoord_2 : TEXCOORD2;
		float3 texcoord_3 : TEXCOORD3;
		float3 texcoord_4 : TEXCOORD4;
		float3 texcoord_5 : TEXCOORD5;
	#endif
};

cbuffer shader_parameters {
	float noise_scale;
};

/*
 */
FRAGMENT_ALPHA_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_ALPHA_OUT OUT;
	
	#include <core/shaders/grass/fragment_base_light.h>
	
	#ifdef QUALITY_MEDIUM
		#ifdef SHADOW
			color *= shadowWorld(s_texture_14,s_sampler_14,s_sampler_compare_14,IN.texcoord_2,IN.texcoord_3,IN.texcoord_4,IN.texcoord_5,s_material_textures[14]);
		#endif
	#endif
	
	OUT.color = float4(color,diffuse.w);
	
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

uniform SAMPLER_SHADOW_WORLD s_texture_14 : TEXUNIT14;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
	#ifdef SHADOW
		float3 texcoord_2 : TEXCOORD2;
		float3 texcoord_3 : TEXCOORD3;
		float3 texcoord_4 : TEXCOORD4;
		float3 texcoord_5 : TEXCOORD5;
	#endif
};

uniform half noise_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/grass/fragment_base_light.h>
	
	#ifdef QUALITY_MEDIUM
		#ifdef SHADOW
			color *= shadowWorld(s_texture_14,IN.texcoord_2,IN.texcoord_3,IN.texcoord_4,IN.texcoord_5);
		#endif
	#endif
	
	return half4(color,diffuse.w);
}

#endif
