/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_sphere_light_ambient.shader
 * Desc:    VolumeSphere light ambient shader
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

#include <core/shaders/common/vertex_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

attribute float4 s_attribute_0;

uniform float3 s_volume_radius;
uniform float4 s_volume_icamera_position;

uniform float volume_density;

/*
 */
void main() {
	
	float4 vertex = float4(s_attribute_0.xyz * s_volume_radius,1.0f);
	
	gl_Position = getPosition(float4(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]),1.0f));
	
	gl_TexCoord[0].xyz = vertex.xyz - s_volume_icamera_position.xyz;
	
	gl_TexCoord[1].x = ((1.0f + volume_density) / volume_density - 1.0f) / (s_volume_radius.x * s_volume_radius.x);
	gl_TexCoord[1].y = 1.0f + volume_density;
	gl_TexCoord[1].z = volume_density;
	
	gl_TexCoord[7] = getProjection(gl_Position);
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
	float3 texcoord_1 : TEXCOORD1;
	float4 texcoord_7 : TEXCOORD7;
};

float3 s_volume_radius;
float4 s_volume_icamera_position;

float volume_density;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = float4(IN.position.xyz * s_volume_radius,1.0f);
	
	OUT.position = getPosition(float4(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]),1.0f));
	
	OUT.texcoord_0 = vertex.xyz - s_volume_icamera_position.xyz;
	
	OUT.texcoord_1.x = ((1.0f + volume_density) / volume_density - 1.0f) / (s_volume_radius.x * s_volume_radius.x);
	OUT.texcoord_1.y = 1.0f + volume_density;
	OUT.texcoord_1.z = volume_density;
	
	OUT.texcoord_7 = getProjection(OUT.position);
	
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
	float3 texcoord_1 : TEXCOORD1;
};

cbuffer shader_volume_parameters {
	float3 s_volume_radius;
	float4 s_volume_icamera_position;
};

cbuffer shader_parameters {
	float volume_density;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = float4(IN.position.xyz * s_volume_radius,1.0f);
	
	OUT.position = getPosition(float4(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]),1.0f));
	
	OUT.texcoord_0 = vertex.xyz - s_volume_icamera_position.xyz;
	
	OUT.texcoord_1.x = ((1.0f + volume_density) / volume_density - 1.0f) / (s_volume_radius.x * s_volume_radius.x);
	OUT.texcoord_1.y = 1.0f + volume_density;
	OUT.texcoord_1.z = volume_density;
	
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
	float3 texcoord_1 : TEXCOORD1;
	float4 texcoord_9 : TEXCOORD9;
};

uniform float3 s_volume_radius;
uniform float4 s_volume_icamera_position;

uniform float volume_density;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = float4(IN.position.xyz * s_volume_radius,1.0f);
	
	OUT.position = getPosition(float4(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]),1.0f));
	
	OUT.texcoord_0 = vertex.xyz - s_volume_icamera_position.xyz;
	
	OUT.texcoord_1.x = ((1.0f + volume_density) / volume_density - 1.0f) / (s_volume_radius.x * s_volume_radius.x);
	OUT.texcoord_1.y = 1.0f + volume_density;
	OUT.texcoord_1.z = volume_density;
	
	OUT.texcoord_9 = getProjection(OUT.position);
	
	return OUT;
}

#endif
