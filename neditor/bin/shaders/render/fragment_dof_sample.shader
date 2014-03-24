/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_dof_sample.shader
 * Desc:    Render dof sample shader
 * Version: 1.03
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

/* s_texture_0 is screen texture
 * s_texture_1 is deferred depth texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;
uniform SAMPLER_2DMS s_texture_1;

uniform half focal_distance;
uniform half focal_range;
uniform half blur_irange;
uniform half blur_power;

/*
 */
void main() {
	
	half4 screen = texture2D(s_texture_0,gl_TexCoord[0].xy);
	half4 deferred_depth = texture2DDeferredNorm2(s_texture_1,gl_TexCoord[0].xy);
	
	half weight = pow(saturate(max(abs(getDeferredDepth(deferred_depth) - focal_distance) - focal_range,0.0f) * blur_irange),blur_power);
	
	gl_FragColor = half4(screen.xyz,weight);
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

half focal_distance;
half focal_range;
half blur_irange;
half blur_power;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 screen = tex2D(s_texture_0,IN.texcoord_0.xy);
	half4 deferred_depth = tex2D(s_texture_1,IN.texcoord_0.xy);
	
	half weight = pow(saturate(max(abs(getDeferredDepth(deferred_depth) - focal_distance) - focal_range,0.0f) * blur_irange),blur_power);
	
	return half4(screen.xyz,weight);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
TEXTURE_2DMS s_texture_1 : register(t1);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
};

float focal_distance;
float focal_range;
float blur_irange;
float blur_power;

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 screen = s_texture_0.Sample(s_sampler_0,IN.texcoord_0.xy);
	half4 deferred_depth = texture2DDeferredNorm2(s_texture_1,s_sampler_1,IN.texcoord_0.xy);
	
	half weight = pow(saturate(max(abs(getDeferredDepth(deferred_depth) - focal_distance) - focal_range,0.0f) * blur_irange),blur_power);
	
	return half4(screen.xyz,weight);
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

uniform half focal_distance;
uniform half focal_range;
uniform half blur_irange;
uniform half blur_power;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 screen = h4tex2D(s_texture_0,IN.texcoord_0.xy);
	half4 deferred_depth = h4tex2D(s_texture_1,IN.texcoord_0.xy);
	
	half weight = pow(saturate(max(abs(getDeferredDepth(deferred_depth) - focal_distance) - focal_range,0.0f) * blur_irange),blur_power);
	
	return half4(screen.xyz,weight);
}

#endif
