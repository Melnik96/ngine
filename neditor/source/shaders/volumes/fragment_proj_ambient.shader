/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_proj_ambient.shader
 * Desc:    VolumeProj ambient shader
 * Version: 1.08
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
 * s_texture_1 is attenuation texture
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

uniform sampler2D s_texture_0;
uniform sampler2D s_texture_1;

uniform SAMPLER_2DMS s_texture_15;

/*
 */
void main() {
	
	half4 color = texture2D(s_texture_0,gl_TexCoord[0].xy);
	color *= texture2D(s_texture_1,gl_TexCoord[0].zw);
	
	#ifdef VOLUME
		half4 deferred_depth = texture2DDeferredProj(s_texture_15,gl_TexCoord[7],s_material_textures[15].xy);
		half depth = getDeferredDepth(deferred_depth) - length(gl_TexCoord[2].xyz);
		color *= saturate(depth * gl_TexCoord[2].w);
	#endif
	
	gl_FragColor = color * half4(gl_TexCoord[1]);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	half4 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
	#ifdef VOLUME
		float4 texcoord_2 : TEXCOORD2;
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 color = tex2D(s_texture_0,IN.texcoord_0.xy);
	color *= tex2D(s_texture_1,IN.texcoord_0.zw);
	
	#ifdef VOLUME
		half4 deferred_depth = tex2Dproj(s_texture_15,IN.texcoord_7);
		half depth = getDeferredDepth(deferred_depth) - length(IN.texcoord_2.xyz);
		color *= saturate(depth * IN.texcoord_2.w);
	#endif
	
	return color * IN.texcoord_1;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
Texture2D s_texture_1 : register(t1);

TEXTURE_2DMS s_texture_15 : register(t15);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	#ifdef VOLUME
		float4 texcoord_2 : TEXCOORD2;
	#endif
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 color = s_texture_0.Sample(s_sampler_0,IN.texcoord_0.xy);
	color *= s_texture_1.Sample(s_sampler_1,IN.texcoord_0.zw);
	
	#ifdef VOLUME
		half4 deferred_depth = texture2DDeferredRect(s_texture_15,s_sampler_15,IN.position.xy,s_material_textures[15].xy);
		half depth = getDeferredDepth(deferred_depth) - length(IN.texcoord_2.xyz);
		color *= saturate(depth * IN.texcoord_2.w);
	#endif
	
	return color * IN.texcoord_1;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_0 : TEXUNIT0;
uniform sampler2D s_texture_1 : TEXUNIT1;

uniform sampler2D s_texture_15 : TEXUNIT15;

struct FRAGMENT_IN {
	half4 texcoord_0 : TEXCOORD0;
	half4 texcoord_1 : TEXCOORD1;
	#ifdef VOLUME
		float4 texcoord_2 : TEXCOORD2;
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 color = h4tex2D(s_texture_0,IN.texcoord_0.xy);
	color *= h4tex2D(s_texture_1,IN.texcoord_0.zw);
	
	#ifdef VOLUME
		half4 deferred_depth = tex2DDepthProj(s_texture_15,IN.texcoord_9.xyw);
		half depth = getDeferredDepth(deferred_depth) - length(IN.texcoord_2.xyz);
		color *= saturate(depth * IN.texcoord_2.w);
	#endif
	
	return color * IN.texcoord_1;
}

#endif
