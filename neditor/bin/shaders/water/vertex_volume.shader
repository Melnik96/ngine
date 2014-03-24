/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_volume.shader
 * Desc:    Water volume shader
 * Version: 1.07
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
#include <core/shaders/water/vertex_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

attribute float4 s_attribute_0;

uniform float volume_density;

/*
 */
void main() {
	
	float4 vertex = s_attribute_0;
	
	float3 normal = float3(s_transform[0].z,s_transform[1].z,s_transform[2].z);
	
	float4 direction;
	direction.xyz = s_attribute_0.xyz / s_depth_range.y;
	direction.w = s_depth_range.y * volume_density;
	
	#include <core/shaders/water/vertex_base.h>
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

float volume_density;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = IN.position;
	
	float3 normal = float3(s_transform[0].z,s_transform[1].z,s_transform[2].z);
	
	float4 direction;
	direction.xyz = IN.position.xyz / s_depth_range.y;
	direction.w = s_depth_range.y * volume_density;
	
	#include <core/shaders/water/vertex_base.h>
	
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

cbuffer shader_parameters {
	float volume_density;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = IN.position;
	
	float3 normal = float3(s_transform[0].z,s_transform[1].z,s_transform[2].z);
	
	float4 direction;
	direction.xyz = IN.position.xyz / s_depth_range.y;
	direction.w = s_depth_range.y * volume_density;
	
	#include <core/shaders/water/vertex_base.h>
	
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

uniform float volume_density;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = IN.position;
	
	float3 normal = float3(s_transform[0].z,s_transform[1].z,s_transform[2].z);
	
	float4 direction;
	direction.xyz = IN.position.xyz / s_depth_range.y;
	direction.w = s_depth_range.y * volume_density;
	
	#include <core/shaders/water/vertex_base.h>
	
	return OUT;
}

#endif
