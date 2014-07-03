/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_composite.shader
 * Desc:    Render composite shader
 * Version: 1.18
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
attribute float4 s_attribute_1;

uniform float4 projection;

/*
 */
void main() {
	
	gl_Position = getPosition(s_attribute_0);
	
	gl_TexCoord[0].xy = s_attribute_1.xy;
	
	gl_TexCoord[1].xy = float2(s_viewport.y / s_viewport.x,1.0f) / 8.0f;
	
	gl_TexCoord[2].x = s_attribute_0.x * projection.x + projection.z;
	gl_TexCoord[2].y = s_attribute_0.y * projection.y;
	gl_TexCoord[2].z = -1.0f;
	gl_TexCoord[2].w = projection.w;
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

struct VERTEX_OUT {
	float4 position : POSITION;
	float2 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
};

float4 projection;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = getPosition(IN.position);
	
	OUT.texcoord_0 = IN.texcoord.xy;
	
	OUT.texcoord_1 = float2(s_viewport.y / s_viewport.x,-1.0f) / 8.0f;
	
	OUT.texcoord_2.x = IN.position.x * projection.x + projection.z;
	OUT.texcoord_2.y = IN.position.y * projection.y;
	OUT.texcoord_2.z = -1.0f;
	OUT.texcoord_2.w = projection.w;
	
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
	float4 color : COLOR0;
};

struct VERTEX_OUT {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
};

float4 projection;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = getPosition(IN.position);
	
	OUT.texcoord_0 = IN.texcoord.xy;
	
	OUT.texcoord_1 = float2(s_viewport.y / s_viewport.x,-1.0f) / 8.0f;
	
	OUT.texcoord_2.x = IN.position.x * projection.x + projection.z;
	OUT.texcoord_2.y = IN.position.y * projection.y;
	OUT.texcoord_2.z = -1.0f;
	OUT.texcoord_2.w = projection.w;
	
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

struct VERTEX_OUT {
	float4 position : POSITION;
	float2 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
};

uniform float4 projection;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = getPosition(IN.position);
	
	OUT.texcoord_0 = IN.texcoord.xy;
	
	OUT.texcoord_1 = float2(s_viewport.y / s_viewport.x,-1.0f) / 8.0f;
	
	OUT.texcoord_2.x = IN.position.x * projection.x + projection.z;
	OUT.texcoord_2.y = IN.position.y * projection.y;
	OUT.texcoord_2.z = -1.0f;
	OUT.texcoord_2.w = projection.w;
	
	return OUT;
}

#endif