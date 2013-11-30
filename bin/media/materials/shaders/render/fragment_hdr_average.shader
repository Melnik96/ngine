/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_hdr_avarage.shader
 * Desc:    Render hdr average shader
 * Version: 1.05
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

/* s_texture_0 is sample texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;

/*
 */
void main() {
	
	half3 color;
	half4 luminance;
	
	color = texture2D(s_texture_0,gl_TexCoord[0].xy).xyz;
	luminance.x = max(max(color.x,color.y),color.z);
	
	color = texture2D(s_texture_0,gl_TexCoord[0].zw).xyz;
	luminance.y = max(max(color.x,color.y),color.z);
	
	color = texture2D(s_texture_0,gl_TexCoord[1].xy).xyz;
	luminance.z = max(max(color.x,color.y),color.z);
	
	color = texture2D(s_texture_0,gl_TexCoord[1].zw).xyz;
	luminance.w = max(max(color.x,color.y),color.z);
	
	luminance = max(luminance,1e-4f);
	
	#ifdef QUADRATIC
		luminance = sqrt(luminance);
	#else
		luminance = log2(luminance);
	#endif
	
	gl_FragColor = half4(dot(luminance,half4(0.25f)));
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
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 color;
	half4 luminance;
	
	color = tex2D(s_texture_0,IN.texcoord_0.xy).xyz;
	luminance.x = max(max(color.x,color.y),color.z);
	
	color = tex2D(s_texture_0,IN.texcoord_0.zw).xyz;
	luminance.y = max(max(color.x,color.y),color.z);
	
	color = tex2D(s_texture_0,IN.texcoord_1.xy).xyz;
	luminance.z = max(max(color.x,color.y),color.z);
	
	color = tex2D(s_texture_0,IN.texcoord_1.zw).xyz;
	luminance.w = max(max(color.x,color.y),color.z);
	
	luminance = max(luminance,1e-4f);
	
	#ifdef QUADRATIC
		luminance = sqrt(luminance);
	#else
		luminance = log2(luminance);
	#endif
	
	return dot(luminance,0.25f);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	float3 color;
	float4 luminance;
	
	color = s_texture_0.Sample(s_sampler_0,IN.texcoord_0.xy).xyz;
	luminance.x = max(max(color.x,color.y),color.z);
	
	color = s_texture_0.Sample(s_sampler_0,IN.texcoord_0.zw).xyz;
	luminance.y = max(max(color.x,color.y),color.z);
	
	color = s_texture_0.Sample(s_sampler_0,IN.texcoord_1.xy).xyz;
	luminance.z = max(max(color.x,color.y),color.z);
	
	color = s_texture_0.Sample(s_sampler_0,IN.texcoord_1.zw).xyz;
	luminance.w = max(max(color.x,color.y),color.z);
	
	luminance = max(luminance,1e-4f);
	
	#ifdef QUADRATIC
		luminance = sqrt(luminance);
	#else
		luminance = log2(luminance);
	#endif
	
	return dot(luminance,0.25f);
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

##pragma disablepc all

uniform sampler2D s_texture_0 : TEXUNIT0;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half3 color;
	half4 luminance;
	
	color = h3tex2D(s_texture_0,IN.texcoord_0.xy);
	luminance.x = max(max(color.x,color.y),color.z);
	
	color = h3tex2D(s_texture_0,IN.texcoord_0.zw);
	luminance.y = max(max(color.x,color.y),color.z);
	
	color = h3tex2D(s_texture_0,IN.texcoord_1.xy);
	luminance.z = max(max(color.x,color.y),color.z);
	
	color = h3tex2D(s_texture_0,IN.texcoord_1.zw);
	luminance.w = max(max(color.x,color.y),color.z);
	
	luminance = max(luminance,1e-4f);
	
	#ifdef QUADRATIC
		luminance = sqrt(luminance);
	#else
		luminance = log2(luminance);
	#endif
	
	return dot(luminance,0.25f);
}

#endif
