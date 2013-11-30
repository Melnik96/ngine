/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_clouds_ambient.shader
 * Desc:    Sky clouds ambient
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

/* s_texture_0 is noise texture
 * s_texture_1 is volume texture
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
uniform sampler3D s_texture_1;

uniform SAMPLER_2DMS s_texture_15;

uniform half clouds_turbulence;
uniform half volume_scale;

/*
 */
void main() {
	
	#ifdef QUALITY_MEDIUM && TURBULENCE
		half3 noise = texture3D(s_texture_0,gl_TexCoord[1].xyz).xyz - 0.5f;
		half2 volume = texture3D(s_texture_1,gl_TexCoord[0].xyz + noise * clouds_turbulence).xy;
	#else
		half2 volume = texture3D(s_texture_1,gl_TexCoord[0].xyz).xy;
	#endif
	
	#ifdef VOLUME
		half4 deferred_depth = texture2DDeferredProj(s_texture_15,gl_TexCoord[7],s_material_textures[15].xy);
		half depth = getDeferredDepth(deferred_depth) - length(gl_TexCoord[2].xyz);
		volume.y *= saturate(depth * volume_scale);
	#endif
	
	half4 color = half4(lerp(half3(gl_TexCoord[4]).xyz,half3(gl_TexCoord[3]).xyz,volume.x),volume.y);
	
	#ifdef INSCATTERING
		color = color * half4(gl_TexCoord[5]) + half4(gl_TexCoord[6]);
	#endif
	
	gl_FragColor = color;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float3 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	#ifdef INSCATTERING
		half4 texcoord_5 : TEXCOORD5;
		half4 texcoord_6 : TEXCOORD6;
	#endif
	float4 texcoord_7 : TEXCOORD7;
};

half clouds_turbulence;
half volume_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#ifdef QUALITY_MEDIUM && TURBULENCE
		half3 noise = tex3D(s_texture_0,IN.texcoord_1).xyz - 0.5f;
		half2 volume = tex3D(s_texture_1,IN.texcoord_0 + noise * clouds_turbulence).xy;
	#else
		half2 volume = tex3D(s_texture_1,IN.texcoord_0).xy;
	#endif
	
	#ifdef VOLUME
		half4 deferred_depth = tex2Dproj(s_texture_15,IN.texcoord_7);
		half depth = getDeferredDepth(deferred_depth) - length(IN.texcoord_2);
		volume.y *= saturate(depth * volume_scale);
	#endif
	
	half4 color = half4(lerp(IN.texcoord_4,IN.texcoord_3,volume.x),volume.y);
	
	#ifdef INSCATTERING
		color = color * IN.texcoord_5 + IN.texcoord_6;
	#endif
	
	return color;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture3D s_texture_0 : register(t0);
Texture3D s_texture_1 : register(t1);

TEXTURE_2DMS s_texture_15 : register(t15);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float3 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	#ifdef INSCATTERING
		float4 texcoord_5 : TEXCOORD5;
		float4 texcoord_6 : TEXCOORD6;
	#endif
};

cbuffer shader_parameters {
	float clouds_turbulence;
	float volume_scale;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#ifdef QUALITY_MEDIUM && TURBULENCE
		half3 noise = s_texture_0.Sample(s_sampler_0,IN.texcoord_1).xyz - 0.5f;
		half2 volume = s_texture_1.Sample(s_sampler_1,IN.texcoord_0 + noise * clouds_turbulence).xy;
	#else
		half2 volume = s_texture_1.Sample(s_sampler_1,IN.texcoord_0).xy;
	#endif
	
	#ifdef VOLUME
		half4 deferred_depth = texture2DDeferredRect(s_texture_15,s_sampler_15,IN.position.xy,s_material_textures[15].xy);
		half depth = getDeferredDepth(deferred_depth) - length(IN.texcoord_2);
		volume.y *= saturate(depth * volume_scale);
	#endif
	
	half4 color = half4(lerp(IN.texcoord_4,IN.texcoord_3,volume.x),volume.y);
	
	#ifdef INSCATTERING
		color = color * IN.texcoord_5 + IN.texcoord_6;
	#endif
	
	return color;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler3D s_texture_0 : TEXUNIT0;
uniform sampler3D s_texture_1 : TEXUNIT1;

uniform sampler2D s_texture_15 : TEXUNIT15;

struct FRAGMENT_IN {
	float3 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	#ifdef INSCATTERING
		half4 texcoord_5 : TEXCOORD5;
		half4 texcoord_6 : TEXCOORD6;
	#endif
	float4 texcoord_9 : TEXCOORD9;
};

uniform half clouds_turbulence;
uniform half volume_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#ifdef QUALITY_MEDIUM && TURBULENCE
		half3 noise = h3tex3D(s_texture_0,IN.texcoord_1) - 0.5f;
		half2 volume = h2tex3D(s_texture_1,IN.texcoord_0 + noise * clouds_turbulence);
	#else
		half2 volume = h2tex3D(s_texture_1,IN.texcoord_0);
	#endif
	
	#ifdef VOLUME
		half4 deferred_depth = tex2DDepthProj(s_texture_15,IN.texcoord_9.xyw);
		half depth = getDeferredDepth(deferred_depth) - length(IN.texcoord_2);
		volume.y *= saturate(depth * volume_scale);
	#endif
	
	half4 color = half4(lerp(IN.texcoord_4,IN.texcoord_3,volume.x),volume.y);
	
	#ifdef INSCATTERING
		color = color * IN.texcoord_5 + IN.texcoord_6;
	#endif
	
	return color;
}

#endif
