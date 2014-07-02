/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base.shader
 * Desc:    Decal base shader
 * Version: 1.06
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
#include <core/shaders/decals/vertex_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

attribute float4 s_attribute_0;
attribute float4 s_attribute_1;
attribute float4 s_attribute_2;
attribute float4 s_attribute_3;

uniform float4 base_transform;

/*
 */
void main() {
	
	float4 vertex = s_attribute_0;
	
	float3 normal = normalize(s_attribute_2.xyz);
	float3 tangent = normalize(s_attribute_3.xyz);
	float3 binormal = cross(normal,tangent) * s_attribute_3.w;
	
	float4 texcoord = s_attribute_1;
	texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw * texcoord.w;
	
	#include <core/shaders/decals/vertex_base.h>
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
	float4 texcoord_2 : TEXCOORD2;
};

float4 base_transform;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = IN.position;
	
	float3 normal = normalize(IN.texcoord_1.xyz);
	float3 tangent = normalize(IN.texcoord_2.xyz);
	float3 binormal = cross(normal,tangent) * IN.texcoord_2.w;
	
	float4 texcoord = IN.texcoord_0;
	texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw * texcoord.w;
	
	#include <core/shaders/decals/vertex_base.h>
	
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
	float4 texcoord_2 : TEXCOORD2;
};

cbuffer shader_parameters {
	float4 base_transform;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = IN.position;
	
	float3 normal = normalize(IN.texcoord_1.xyz);
	float3 tangent = normalize(IN.texcoord_2.xyz);
	float3 binormal = cross(normal,tangent) * IN.texcoord_2.w;
	
	float4 texcoord = IN.texcoord_0;
	texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw * texcoord.w;
	
	#include <core/shaders/decals/vertex_base.h>
	
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
	float4 texcoord_2 : ATTR3;
};

uniform float4 base_transform;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 vertex = IN.position;
	
	float3 normal = normalize(IN.texcoord_1.xyz);
	float3 tangent = normalize(IN.texcoord_2.xyz);
	float3 binormal = cross(normal,tangent) * IN.texcoord_2.w;
	
	float4 texcoord = IN.texcoord_0;
	texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw * texcoord.w;
	
	#include <core/shaders/decals/vertex_base.h>
	
	return OUT;
}

#endif
