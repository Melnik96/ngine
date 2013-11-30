/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_shadow_light_world.shader
 * Desc:    Sky shadow light world shader
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

#include <core/shaders/common/vertex_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

attribute float4 s_attribute_0;

uniform float4x4 s_sky_modelviewprojection;

/*
 */
void main() {
	
	gl_Position = s_sky_modelviewprojection * s_attribute_0;
	
	gl_TexCoord[0].xyz = s_attribute_0.xyz;
	
	gl_TexCoord[7] = getProjection(gl_Position);
	
	gl_Position.z = 0.0f;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct VERTEX_IN {
	float4 position : POSITION;
};

struct VERTEX_OUT {
	float4 position : POSITION;
	float3 texcoord_0 : TEXCOORD0;
	float4 texcoord_7 : TEXCOORD7;
};

float4x4 s_sky_modelviewprojection;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = mul(s_sky_modelviewprojection,IN.position);
	
	OUT.texcoord_0 = IN.position.xyz;
	
	OUT.texcoord_7 = getProjection(OUT.position);
	
	OUT.position.z = 0.0f;
	
	return OUT;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

struct VERTEX_IN {
	float4 position : POSITION;
};

struct VERTEX_OUT {
	float4 position : SV_POSITION;
	float3 texcoord_0 : TEXCOORD0;
};

cbuffer shader_sky_parameters {
	float4x4 s_sky_modelviewprojection;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = mul(s_sky_modelviewprojection,IN.position);
	
	OUT.texcoord_0 = IN.position.xyz;
	
	OUT.position.z = 0.0f;
	
	return OUT;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

struct VERTEX_IN {
	float4 position : ATTR0;
};

struct VERTEX_OUT {
	float4 position : POSITION;
	float3 texcoord_0 : TEXCOORD0;
	float4 texcoord_9 : TEXCOORD9;
};

uniform float4x4 s_sky_modelviewprojection;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = mul(s_sky_modelviewprojection,IN.position);
	
	OUT.texcoord_0 = IN.position.xyz;
	
	OUT.texcoord_9 = getProjection(OUT.position);
	OUT.texcoord_9.z *= s_depth_range.w;
	
	OUT.position.z = 0.0f;
	
	return OUT;
}

#endif
