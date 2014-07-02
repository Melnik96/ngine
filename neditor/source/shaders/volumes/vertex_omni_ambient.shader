/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_omni_light_ambient.shader
 * Desc:    VolumeOmni light ambient shader
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

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

attribute float4 s_attribute_0;
attribute float3 s_attribute_1;
attribute float2 s_attribute_2;

uniform float4 diffuse_color;
uniform float diffuse_scale;
uniform float volume_scale;

/*
 */
void main() {
	
	gl_Position = getPosition(s_attribute_0);
	
	gl_TexCoord[0].xyz = (s_attribute_0.xyz - s_attribute_1) / s_attribute_2.y;
	
	gl_TexCoord[1] = float4(diffuse_color.xyz * diffuse_scale,diffuse_color.w) * s_attribute_2.x;
	
	#ifdef VOLUME
		gl_TexCoord[2].xyz = (s_attribute_0.xyz - s_camera_position) / s_depth_range.y;
		gl_TexCoord[2].w = s_depth_range.y / s_attribute_2.y * volume_scale;
		gl_TexCoord[7] = getProjection(gl_Position);
	#endif
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct VERTEX_IN {
	float4 position : POSITION;
	float3 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
};

struct VERTEX_OUT {
	float4 position : POSITION;
	float3 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	#ifdef VOLUME
		float4 texcoord_2 : TEXCOORD2;
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

float4 diffuse_color;
float diffuse_scale;
float volume_scale;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = getPosition(IN.position);
	
	OUT.texcoord_0 = (IN.position.xyz - IN.texcoord_0) / IN.texcoord_1.y;
	
	OUT.texcoord_1 = float4(diffuse_color.xyz * diffuse_scale,diffuse_color.w) * IN.texcoord_1.x;
	
	#ifdef VOLUME
		OUT.texcoord_2.xyz = (IN.position.xyz - s_camera_position) / s_depth_range.y;
		OUT.texcoord_2.w = s_depth_range.y / IN.texcoord_1.y * volume_scale;
		OUT.texcoord_7 = getProjection(OUT.position);
	#endif
	
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
	float3 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
};

struct VERTEX_OUT {
	float4 position : SV_POSITION;
	float3 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	#ifdef VOLUME
		float4 texcoord_2 : TEXCOORD2;
	#endif
};

cbuffer shader_parameters {
	float4 diffuse_color;
	float diffuse_scale;
	float volume_scale;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = getPosition(IN.position);
	
	OUT.texcoord_0 = (IN.position.xyz - IN.texcoord_0) / IN.texcoord_1.y;
	
	OUT.texcoord_1 = float4(diffuse_color.xyz * diffuse_scale,diffuse_color.w) * IN.texcoord_1.x;
	
	#ifdef VOLUME
		OUT.texcoord_2.xyz = (IN.position.xyz - s_camera_position) / s_depth_range.y;
		OUT.texcoord_2.w = s_depth_range.y / IN.texcoord_1.y * volume_scale;
	#endif
	
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
	float3 texcoord_0 : ATTR1;
	float2 texcoord_1 : ATTR2;
};

struct VERTEX_OUT {
	float4 position : POSITION;
	float3 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	#ifdef VOLUME
		float4 texcoord_2 : TEXCOORD2;
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform float4 diffuse_color;
uniform float diffuse_scale;
uniform float volume_scale;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = getPosition(IN.position);
	
	OUT.texcoord_0 = (IN.position.xyz - IN.texcoord_0) / IN.texcoord_1.y;
	
	OUT.texcoord_1 = float4(diffuse_color.xyz * diffuse_scale,diffuse_color.w) * IN.texcoord_1.x;
	
	#ifdef VOLUME
		OUT.texcoord_2.xyz = (IN.position.xyz - s_camera_position) / s_depth_range.y;
		OUT.texcoord_2.w = s_depth_range.y / IN.texcoord_1.y * volume_scale;
		OUT.texcoord_9 = getProjection(OUT.position);
	#endif
	
	return OUT;
}

#endif
