/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_surface_deferred.shader
 * Desc:    Water surface deferred shader
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

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform half4 surface_color;
uniform half specular_power;

/*
 */
void main() {
	
	gl_FragData[0] = setDeferredDepth(length(gl_TexCoord[0].xyz),0.0f);
	
	gl_FragData[1] = setDeferredColor(surface_color.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		gl_FragData[2] = setDeferredNormal(gl_TexCoord[1].xyz,specular_power);
	#elif USE_PARALLAX
		gl_FragData[2] = half4(0.0f);
	#endif
	
	#ifdef USE_PARALLAX
		gl_FragData[3] = half4(0.0f);
	#endif
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
};

half4 surface_color;
half specular_power;

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_0),0.0f);
	
	OUT.color_1 = setDeferredColor(surface_color.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		OUT.color_2 = setDeferredNormal(IN.texcoord_1.xyz,specular_power);
	#elif USE_PARALLAX
		OUT.color_2 = 0.0f;
	#endif
	
	#ifdef USE_PARALLAX
		OUT.color_3 = 0.0f;
	#endif
	
	return OUT;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float3 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
};

cbuffer shader_parameters {
	float4 surface_color;
	float specular_power;
};

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_0),0.0f);
	
	OUT.color_1 = setDeferredColor(surface_color.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		OUT.color_2 = setDeferredNormal(IN.texcoord_1.xyz,specular_power);
	#elif USE_PARALLAX
		OUT.color_2 = 0.0f;
	#endif
	
	#ifdef USE_PARALLAX
		OUT.color_3 = 0.0f;
	#endif
	
	return OUT;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

struct FRAGMENT_IN {
	float3 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
};

uniform half4 surface_color;
uniform half specular_power;

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	OUT.color_0 = setDeferredDepth(length(IN.texcoord_0),0.0f);
	
	OUT.color_1 = setDeferredColor(surface_color.xyz,0.0f);
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		OUT.color_2 = setDeferredNormal(IN.texcoord_1.xyz,specular_power);
	#elif USE_PARALLAX
		OUT.color_2 = 0.0f;
	#endif
	
	#ifdef USE_PARALLAX
		OUT.color_3 = 0.0f;
	#endif
	
	return OUT;
}

#endif
