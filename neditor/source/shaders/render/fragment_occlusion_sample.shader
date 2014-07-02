/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_occlusion_sample.shader
 * Desc:    Render occlusion sample shader
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

/* s_texture_0 is deferred depth texture
 * s_texture_1 is deferred normal texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform SAMPLER_2DMS s_texture_0;
uniform SAMPLER_2DMS s_texture_1;

/*
 */
void main() {
	
	half depth = getDeferredDepth(texture2DDeferredNorm2(s_texture_0,gl_TexCoord[0].xy));
	half3 normal = getDeferredNormal(texture2DDeferredNorm2(s_texture_1,gl_TexCoord[0].xy));
	
	gl_FragColor = half4(normal,depth);
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

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half depth = getDeferredDepth(tex2D(s_texture_0,IN.texcoord_0));
	half3 normal = getDeferredNormal(tex2D(s_texture_1,IN.texcoord_0));
	
	return half4(normal,depth);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

TEXTURE_2DMS s_texture_0 : register(t0);
TEXTURE_2DMS s_texture_1 : register(t1);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half depth = getDeferredDepth(texture2DDeferredNorm2(s_texture_0,s_sampler_0,IN.texcoord_0));
	half3 normal = getDeferredNormal(texture2DDeferredNorm2(s_texture_1,s_sampler_1,IN.texcoord_0));
	
	return half4(normal,depth);
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

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half depth = getDeferredDepth(h4tex2D(s_texture_0,IN.texcoord_0));
	half3 normal = getDeferredNormal(h4tex2D(s_texture_1,IN.texcoord_0));
	
	return half4(normal,depth);
}

#endif
