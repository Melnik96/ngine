/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base.shader
 * Desc:    Billboard base shader
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
#include <core/shaders/billboards/vertex_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

attribute float4 s_attribute_0;
attribute float4 s_attribute_1;
attribute float4 s_attribute_2;

uniform float4 base_transform;

/*
 */
void main() {
	
	float3 dx,dy,dz;
	
	bool axis = (s_attribute_0.w == 1.0f || s_attribute_0.w == 3.0f);
	bool screen = (s_attribute_0.w == 2.0f || s_attribute_0.w == 3.0f);
	
	float3 billboard_direction = s_camera_position - s_attribute_0.xyz;
	float3 screen_direction = float3(s_modelview[0][2],s_modelview[1][2],s_modelview[2][2]);
	
	if(screen) {
		dx = normalize(cross(s_attribute_1.xyz,screen_direction));
		if(!axis && dot(dx,float3(s_modelview[0][0],s_modelview[1][0],s_modelview[2][0])) < 0.0f) dx = -dx;
	} else {
		dx = normalize(cross(s_attribute_1.xyz,billboard_direction));
	}
	
	if(axis) dy = s_attribute_1.xyz;
	else if(screen) dy = normalize(cross(screen_direction,dx));
	else dy = normalize(cross(billboard_direction,dx));
	
	dz = normalize(cross(dx,dy));
	if(dot(dz,billboard_direction) < 0.0f) {
		if(screen && axis) dx = -dx;
		else dz = -dz;
	}
	
	float4 vertex = float4(s_attribute_0.xyz,1.0f);
	vertex.xyz += dx * s_attribute_2.x;
	vertex.xyz += dy * s_attribute_2.y;
	vertex.xyz += dz * s_attribute_1.w;
	
	float3 normal = dz;
	float3 tangent = dx;
	float3 binormal = dy;
	
	float4 texcoord = float4(s_attribute_2.zw,0.0f,0.0f);
	texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 bound_sphere = float4(s_attribute_0.xyz,s_surface_bound_sphere.w);
	#endif
	
	#include <core/shaders/billboards/vertex_base.h>
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct VERTEX_IN {
	float4 position : POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

float4 base_transform;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float3 dx,dy,dz;
	
	bool axis = (IN.position.w == 1.0f || IN.position.w == 3.0f);
	bool screen = (IN.position.w == 2.0f || IN.position.w == 3.0f);
	
	float3 billboard_direction = s_camera_position - IN.position.xyz;
	float3 screen_direction = s_modelview[2].xyz;
	
	if(screen) {
		dx = normalize(cross(IN.texcoord_0.xyz,screen_direction));
		if(!axis && dot(dx,s_modelview[0].xyz) < 0.0f) dx = -dx;
	} else {
		dx = normalize(cross(IN.texcoord_0.xyz,billboard_direction));
	}
	
	if(axis) dy = IN.texcoord_0.xyz;
	else if(screen) dy = normalize(cross(screen_direction,dx));
	else dy = normalize(cross(billboard_direction,dx));
	
	dz = normalize(cross(dx,dy));
	if(dot(dz,billboard_direction) < 0.0f) {
		if(screen && axis) dx = -dx;
		else dz = -dz;
	}
	
	float4 vertex = float4(IN.position.xyz,1.0f);
	vertex.xyz += dx * IN.texcoord_1.x;
	vertex.xyz += dy * IN.texcoord_1.y;
	vertex.xyz += dz * IN.texcoord_0.w;
	
	float3 normal = dz;
	float3 tangent = dx;
	float3 binormal = dy;
	
	float4 texcoord = float4(IN.texcoord_1.zw,0.0f,0.0f);
	texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 bound_sphere = float4(IN.position.xyz,s_surface_bound_sphere.w);
	#endif
	
	#include <core/shaders/billboards/vertex_base.h>
	
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
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

cbuffer shader_parameters {
	float4 base_transform;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float3 dx,dy,dz;
	
	bool axis = (IN.position.w == 1.0f || IN.position.w == 3.0f);
	bool screen = (IN.position.w == 2.0f || IN.position.w == 3.0f);
	
	float3 billboard_direction = s_camera_position - IN.position.xyz;
	float3 screen_direction = s_modelview[2].xyz;
	
	if(screen) {
		dx = normalize(cross(IN.texcoord_0.xyz,screen_direction));
		if(!axis && dot(dx,s_modelview[0].xyz) < 0.0f) dx = -dx;
	} else {
		dx = normalize(cross(IN.texcoord_0.xyz,billboard_direction));
	}
	
	if(axis) dy = IN.texcoord_0.xyz;
	else if(screen) dy = normalize(cross(screen_direction,dx));
	else dy = normalize(cross(billboard_direction,dx));
	
	dz = normalize(cross(dx,dy));
	if(dot(dz,billboard_direction) < 0.0f) {
		if(screen && axis) dx = -dx;
		else dz = -dz;
	}
	
	float4 vertex = float4(IN.position.xyz,1.0f);
	vertex.xyz += dx * IN.texcoord_1.x;
	vertex.xyz += dy * IN.texcoord_1.y;
	vertex.xyz += dz * IN.texcoord_0.w;
	
	float3 normal = dz;
	float3 tangent = dx;
	float3 binormal = dy;
	
	float4 texcoord = float4(IN.texcoord_1.zw,0.0f,0.0f);
	texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 bound_sphere = float4(IN.position.xyz,s_surface_bound_sphere.w);
	#endif
	
	#include <core/shaders/billboards/vertex_base.h>
	
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
	float4 texcoord_0 : ATTR1;
	float4 texcoord_1 : ATTR2;
};

uniform float4 base_transform;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float3 dx,dy,dz;
	
	bool axis = (IN.position.w == 1.0f || IN.position.w == 3.0f);
	bool screen = (IN.position.w == 2.0f || IN.position.w == 3.0f);
	
	float3 billboard_direction = s_camera_position - IN.position.xyz;
	float3 screen_direction = s_modelview[2].xyz;
	
	if(screen) {
		dx = normalize(cross(IN.texcoord_0.xyz,screen_direction));
		if(!axis && dot(dx,s_modelview[0].xyz) < 0.0f) dx = -dx;
	} else {
		dx = normalize(cross(IN.texcoord_0.xyz,billboard_direction));
	}
	
	if(axis) dy = IN.texcoord_0.xyz;
	else if(screen) dy = normalize(cross(screen_direction,dx));
	else dy = normalize(cross(billboard_direction,dx));
	
	dz = normalize(cross(dx,dy));
	if(dot(dz,billboard_direction) < 0.0f) {
		if(screen && axis) dx = -dx;
		else dz = -dz;
	}
	
	float4 vertex = float4(IN.position.xyz,1.0f);
	vertex.xyz += dx * IN.texcoord_1.x;
	vertex.xyz += dy * IN.texcoord_1.y;
	vertex.xyz += dz * IN.texcoord_0.w;
	
	float3 normal = dz;
	float3 tangent = dx;
	float3 binormal = dy;
	
	float4 texcoord = float4(IN.texcoord_1.zw,0.0f,0.0f);
	texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 bound_sphere = float4(IN.position.xyz,s_surface_bound_sphere.w);
	#endif
	
	#include <core/shaders/billboards/vertex_base.h>
	
	return OUT;
}

#endif
