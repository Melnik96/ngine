/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base.shader
 * Desc:    Particles base shader
 * Version: 1.14
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
#include <core/shaders/particles/vertex_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

attribute float4 s_attribute_0;
attribute float4 s_attribute_1;

uniform float s_particles_radius;

uniform float4 attenuation_transform;
uniform float4 diffuse_color;
uniform float diffuse_scale;
uniform float volume_scale;

/*
 */
void main() {
	
	float4 vertex = s_attribute_0;
	
	float4 texcoord = float4(s_attribute_1.xyw,attenuation_transform.x);
	texcoord.z += s_attribute_1.z * (1.0f / 256.0f);
	
	float4 color = float4(diffuse_color.xyz * diffuse_scale,diffuse_color.w);
	
	float4 volume;
	volume.xyz = (vertex.xyz - s_camera_position) / s_depth_range.y;
	volume.w = s_depth_range.y / s_particles_radius * volume_scale;
	
	#include <core/shaders/particles/vertex_base.h>
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct VERTEX_IN {
	float4 position : POSITION;
	float4 texcoord : TEXCOORD0;
};

float s_particles_radius;

float4 attenuation_transform;
float4 diffuse_color;
float diffuse_scale;
float volume_scale;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = IN.position;
	
	float4 texcoord = float4(IN.texcoord.xyw,attenuation_transform.x);
	texcoord.z += IN.texcoord.z * (1.0f / 256.0f);
	
	float4 color = float4(diffuse_color.xyz * diffuse_scale,diffuse_color.w);
	
	float4 volume;
	volume.xyz = (vertex.xyz - s_camera_position) / s_depth_range.y;
	volume.w = s_depth_range.y / s_particles_radius * volume_scale;
	
	#include <core/shaders/particles/vertex_base.h>
	
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
	float4 texcoord : TEXCOORD0;
};

cbuffer shader_particles_parameters {
	float s_particles_radius;
};

cbuffer shader_parameters {
	float4 attenuation_transform;
	float4 diffuse_color;
	float diffuse_scale;
	float volume_scale;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = IN.position;
	
	float4 texcoord = float4(IN.texcoord.xyw,attenuation_transform.x);
	texcoord.z += IN.texcoord.z * (1.0f / 256.0f);
	
	float4 color = float4(diffuse_color.xyz * diffuse_scale,diffuse_color.w);
	
	float4 volume;
	volume.xyz = (vertex.xyz - s_camera_position) / s_depth_range.y;
	volume.w = s_depth_range.y / s_particles_radius * volume_scale;
	
	#include <core/shaders/particles/vertex_base.h>
	
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
	float4 texcoord : ATTR1;
};

uniform float s_particles_radius;

uniform float4 attenuation_transform;
uniform float4 diffuse_color;
uniform float diffuse_scale;
uniform float volume_scale;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = IN.position;
	
	float4 texcoord = float4(IN.texcoord.zwx,attenuation_transform.x);
	texcoord.z += IN.texcoord.y * (1.0f / 256.0f);
	
	float4 color = float4(diffuse_color.xyz * diffuse_scale,diffuse_color.w);
	
	float4 volume;
	volume.xyz = (vertex.xyz - s_camera_position) / s_depth_range.y;
	volume.w = s_depth_range.y / s_particles_radius * volume_scale;
	
	#include <core/shaders/particles/vertex_base.h>
	
	return OUT;
}

#endif
