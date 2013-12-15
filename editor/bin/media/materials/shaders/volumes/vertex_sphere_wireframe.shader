/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_sphere_wireframe.shader
 * Desc:    VolumeSphere wireframe shader
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

#include <core/shaders/common/vertex_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

attribute float4 s_attribute_0;

uniform float3 s_volume_radius;

/*
 */
void main() {
	
	float4 vertex = float4(s_attribute_0.xyz * s_volume_radius,1.0f);
	
	gl_Position = getPosition(float4(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]),1.0f));
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
};

float3 s_volume_radius;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = float4(IN.position.xyz * s_volume_radius,1.0f);
	
	OUT.position = getPosition(float4(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]),1.0f));
	
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
};

cbuffer shader_volume_parameters {
	float3 s_volume_radius;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = float4(IN.position.xyz * s_volume_radius,1.0f);
	
	OUT.position = getPosition(float4(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]),1.0f));
	
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
};

uniform float3 s_volume_radius;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = float4(IN.position.xyz * s_volume_radius,1.0f);
	
	OUT.position = getPosition(float4(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]),1.0f));
	
	return OUT;
}

#endif
