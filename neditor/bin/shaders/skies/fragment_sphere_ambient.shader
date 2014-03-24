/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_sphere_ambient.shader
 * Desc:    Sky sphere ambient shader
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

/* s_texture_0 is mask_0 texture
 * s_texture_1 is mask_1 texture
 * s_texture_2 is clouds_01 texture
 * s_texture_3 is clouds_23 texture
 * s_texture_4 is background texture
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
uniform samplerCube s_texture_4;

uniform half clouds_01_scale;
uniform half clouds_23_scale;
uniform half clouds_01_threshold;
uniform half clouds_23_threshold;
uniform half background_scale;

/*
 */
void main() {
	
	half4 mask_0 = texture2D(s_texture_0,gl_TexCoord[0].xy);
	half4 mask_1 = texture2D(s_texture_1,gl_TexCoord[0].zw);
	
	half4 clouds_0 = texture2D(s_texture_2,gl_TexCoord[1].xy);
	half4 clouds_1 = texture2D(s_texture_2,gl_TexCoord[1].zw);
	half4 clouds_2 = texture2D(s_texture_3,gl_TexCoord[2].xy);
	half4 clouds_3 = texture2D(s_texture_3,gl_TexCoord[2].zw);
	
	half4 clouds_01 = max((clouds_0 + clouds_1 - mask_0 * clouds_01_threshold) * clouds_01_scale,0.0f);
	half4 clouds_23 = max((clouds_2 + clouds_3 - mask_1 * clouds_23_threshold) * clouds_23_scale,0.0f);
	
	half3 color = clouds_01.xyz * min(clouds_01.w,1.0f);
	color = lerp(color,clouds_23.xyz,min(clouds_23.w,1.0f));
	
	#ifdef INSCATTERING
		half alpha = saturate((clouds_01.w + clouds_23.w) * gl_TexCoord[3].w);
		color = color * gl_TexCoord[3].xyz + gl_TexCoord[4].xyz;
	#else
		half alpha = saturate(clouds_01.w + clouds_23.w);
	#endif
	
	#ifdef BACKGROUND
		half3 background = textureCube(s_texture_4,gl_TexCoord[5].xyz).xyz;
		color = lerp(background * background_scale,color,alpha);
		alpha = 1.0f;
	#endif
	
	gl_FragColor = half4(color,alpha);
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
	float4 texcoord_2 : TEXCOORD2;
	#ifdef INSCATTERING
		half4 texcoord_3 : TEXCOORD3;
		half3 texcoord_4 : TEXCOORD4;
	#endif
	#ifdef BACKGROUND
		float3 texcoord_5 : TEXCOORD5;
	#endif
};

half clouds_01_scale;
half clouds_23_scale;
half clouds_01_threshold;
half clouds_23_threshold;
half background_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 mask_0 = tex2D(s_texture_0,IN.texcoord_0.xy);
	half4 mask_1 = tex2D(s_texture_1,IN.texcoord_0.zw);
	
	half4 clouds_0 = tex2D(s_texture_2,IN.texcoord_1.xy);
	half4 clouds_1 = tex2D(s_texture_2,IN.texcoord_1.zw);
	half4 clouds_2 = tex2D(s_texture_3,IN.texcoord_2.xy);
	half4 clouds_3 = tex2D(s_texture_3,IN.texcoord_2.zw);
	
	half4 clouds_01 = max((clouds_0 + clouds_1 - mask_0 * clouds_01_threshold) * clouds_01_scale,0.0f);
	half4 clouds_23 = max((clouds_2 + clouds_3 - mask_1 * clouds_23_threshold) * clouds_23_scale,0.0f);
	
	half3 color = clouds_01.xyz * min(clouds_01.w,1.0f);
	color = lerp(color,clouds_23.xyz,min(clouds_23.w,1.0f));
	
	#ifdef INSCATTERING
		half alpha = saturate((clouds_01.w + clouds_23.w) * IN.texcoord_3.w);
		color = color * IN.texcoord_3.xyz + IN.texcoord_4;
	#else
		half alpha = saturate(clouds_01.w + clouds_23.w);
	#endif
	
	#ifdef BACKGROUND
		half3 background = texCUBE(s_texture_4,IN.texcoord_5).xyz;
		color = lerp(background * background_scale,color,alpha);
		alpha = 1.0f;
	#endif
	
	return half4(color,alpha);
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
TextureCube s_texture_4 : register(t4);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	#ifdef INSCATTERING
		float4 texcoord_3 : TEXCOORD3;
		float3 texcoord_4 : TEXCOORD4;
	#endif
	#ifdef BACKGROUND
		float3 texcoord_5 : TEXCOORD5;
	#endif
};

cbuffer shader_parameters {
	float clouds_01_scale;
	float clouds_23_scale;
	float clouds_01_threshold;
	float clouds_23_threshold;
	#ifdef BACKGROUND
		float background_scale;
	#endif
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 mask_0 = s_texture_0.Sample(s_sampler_0,IN.texcoord_0.xy);
	half4 mask_1 = s_texture_1.Sample(s_sampler_1,IN.texcoord_0.zw);
	
	half4 clouds_0 = s_texture_2.Sample(s_sampler_2,IN.texcoord_1.xy);
	half4 clouds_1 = s_texture_2.Sample(s_sampler_2,IN.texcoord_1.zw);
	half4 clouds_2 = s_texture_3.Sample(s_sampler_3,IN.texcoord_2.xy);
	half4 clouds_3 = s_texture_3.Sample(s_sampler_3,IN.texcoord_2.zw);
	
	half4 clouds_01 = max((clouds_0 + clouds_1 - mask_0 * clouds_01_threshold) * clouds_01_scale,0.0f);
	half4 clouds_23 = max((clouds_2 + clouds_3 - mask_1 * clouds_23_threshold) * clouds_23_scale,0.0f);
	
	half3 color = clouds_01.xyz * min(clouds_01.w,1.0f);
	color = lerp(color,clouds_23.xyz,min(clouds_23.w,1.0f));
	
	#ifdef INSCATTERING
		half alpha = saturate((clouds_01.w + clouds_23.w) * IN.texcoord_3.w);
		color = color * IN.texcoord_3.xyz + IN.texcoord_4;
	#else
		half alpha = saturate(clouds_01.w + clouds_23.w);
	#endif
	
	#ifdef BACKGROUND
		half3 background = s_texture_4.Sample(s_sampler_4,IN.texcoord_5).xyz;
		color = lerp(background * background_scale,color,alpha);
		alpha = 1.0f;
	#endif
	
	return float4(color,alpha);
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
uniform samplerCUBE s_texture_4 : TEXUNIT4;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	#ifdef INSCATTERING
		half4 texcoord_3 : TEXCOORD3;
		half3 texcoord_4 : TEXCOORD4;
	#endif
	#ifdef BACKGROUND
		float3 texcoord_5 : TEXCOORD5;
	#endif
};

uniform half clouds_01_scale;
uniform half clouds_23_scale;
uniform half clouds_01_threshold;
uniform half clouds_23_threshold;
uniform half background_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 mask_0 = h4tex2D(s_texture_0,IN.texcoord_0.xy);
	half4 mask_1 = h4tex2D(s_texture_1,IN.texcoord_0.zw);
	
	half4 clouds_0 = h4tex2D(s_texture_2,IN.texcoord_1.xy);
	half4 clouds_1 = h4tex2D(s_texture_2,IN.texcoord_1.zw);
	half4 clouds_2 = h4tex2D(s_texture_3,IN.texcoord_2.xy);
	half4 clouds_3 = h4tex2D(s_texture_3,IN.texcoord_2.zw);
	
	half4 clouds_01 = max((clouds_0 + clouds_1 - mask_0 * clouds_01_threshold) * clouds_01_scale,0.0f);
	half4 clouds_23 = max((clouds_2 + clouds_3 - mask_1 * clouds_23_threshold) * clouds_23_scale,0.0f);
	
	half3 color = clouds_01.xyz * min(clouds_01.w,1.0f);
	color = lerp(color,clouds_23.xyz,min(clouds_23.w,1.0f));
	
	#ifdef INSCATTERING
		half alpha = saturate((clouds_01.w + clouds_23.w) * IN.texcoord_3.w);
		color = color * IN.texcoord_3.xyz + IN.texcoord_4;
	#else
		half alpha = saturate(clouds_01.w + clouds_23.w);
	#endif
	
	#ifdef BACKGROUND
		half3 background = h3texCUBE(s_texture_4,IN.texcoord_5);
		color = lerp(background * background_scale,color,alpha);
		alpha = 1.0f;
	#endif
	
	return half4(color,alpha);
}

#endif
