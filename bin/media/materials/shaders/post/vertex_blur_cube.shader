/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_blur_cube.shader
 * Desc:    Post blur cube shader
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

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

attribute float4 s_attribute_0;
attribute float4 s_attribute_1;

/*
 */
void main() {
	
	gl_Position = getPosition(s_attribute_0);
	
	float3 dir = float3(0.0f,0.0f,1.0f);
	
	#ifdef HBLUR
		if(s_attribute_1.w == 0.0f || s_attribute_1.w == 1.0f) dir = float3(0.0f,1.0,0.0f);
		if(s_attribute_1.w == 2.0f || s_attribute_1.w == 3.0f) dir = float3(1.0f,0.0,0.0f);
		if(s_attribute_1.w == 4.0f || s_attribute_1.w == 5.0f) dir = float3(1.0f,0.0,0.0f);
	#elif VBLUR
		if(s_attribute_1.w == 0.0f || s_attribute_1.w == 1.0f) dir = float3(0.0f,0.0f,1.0f);
		if(s_attribute_1.w == 2.0f || s_attribute_1.w == 3.0f) dir = float3(0.0f,0.0f,1.0f);
		if(s_attribute_1.w == 4.0f || s_attribute_1.w == 5.0f) dir = float3(0.0f,1.0f,0.0f);
	#endif
	
	float3 texcoord = normalize(s_attribute_1.xyz);
	float3 offset = normalize(cross(texcoord,dir)) * s_viewport.z * 1.5f;
	
	gl_TexCoord[0].xyz = texcoord;
	gl_TexCoord[1].xyz = offset * 1.0f;
	gl_TexCoord[2].xyz = offset * 2.0f;
	gl_TexCoord[3].xyz = offset * 3.0f;
	gl_TexCoord[4].xyz = offset * 4.0f;
	gl_TexCoord[5].xyz = offset * 5.0f;
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
	float3 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	float3 texcoord_5 : TEXCOORD5;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = getPosition(IN.position);
	
	float3 dir = float3(0.0f,0.0f,1.0f);
	
	#ifdef HBLUR
		if(IN.texcoord.w == 0.0f || IN.texcoord.w == 1.0f) dir = float3(0.0f,1.0f,0.0f);
		if(IN.texcoord.w == 2.0f || IN.texcoord.w == 3.0f) dir = float3(1.0f,0.0f,0.0f);
		if(IN.texcoord.w == 4.0f || IN.texcoord.w == 5.0f) dir = float3(1.0f,0.0f,0.0f);
	#elif VBLUR
		if(IN.texcoord.w == 0.0f || IN.texcoord.w == 1.0f) dir = float3(0.0f,0.0f,1.0f);
		if(IN.texcoord.w == 2.0f || IN.texcoord.w == 3.0f) dir = float3(0.0f,0.0f,1.0f);
		if(IN.texcoord.w == 4.0f || IN.texcoord.w == 5.0f) dir = float3(0.0f,1.0f,0.0f);
	#endif
	
	float3 texcoord = normalize(IN.texcoord.xyz);
	float3 offset = normalize(cross(texcoord,dir)) * s_viewport.z * 1.5f;
	
	OUT.texcoord_0 = texcoord;
	OUT.texcoord_1 = offset * 1.0f;
	OUT.texcoord_2 = offset * 2.0f;
	OUT.texcoord_3 = offset * 3.0f;
	OUT.texcoord_4 = offset * 4.0f;
	OUT.texcoord_5 = offset * 5.0f;
	
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
	float3 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	float3 texcoord_5 : TEXCOORD5;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = getPosition(IN.position);
	
	float3 dir = float3(0.0f,0.0f,1.0f);
	
	#ifdef HBLUR
		if(IN.texcoord.w == 0.0f || IN.texcoord.w == 1.0f) dir = float3(0.0f,1.0f,0.0f);
		if(IN.texcoord.w == 2.0f || IN.texcoord.w == 3.0f) dir = float3(1.0f,0.0f,0.0f);
		if(IN.texcoord.w == 4.0f || IN.texcoord.w == 5.0f) dir = float3(1.0f,0.0f,0.0f);
	#elif VBLUR
		if(IN.texcoord.w == 0.0f || IN.texcoord.w == 1.0f) dir = float3(0.0f,0.0f,1.0f);
		if(IN.texcoord.w == 2.0f || IN.texcoord.w == 3.0f) dir = float3(0.0f,0.0f,1.0f);
		if(IN.texcoord.w == 4.0f || IN.texcoord.w == 5.0f) dir = float3(0.0f,1.0f,0.0f);
	#endif
	
	float3 texcoord = normalize(IN.texcoord.xyz);
	float3 offset = normalize(cross(texcoord,dir)) * s_viewport.z * 1.5f;
	
	OUT.texcoord_0 = texcoord;
	OUT.texcoord_1 = offset * 1.0f;
	OUT.texcoord_2 = offset * 2.0f;
	OUT.texcoord_3 = offset * 3.0f;
	OUT.texcoord_4 = offset * 4.0f;
	OUT.texcoord_5 = offset * 5.0f;
	
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
	float3 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
	float3 texcoord_3 : TEXCOORD3;
	float3 texcoord_4 : TEXCOORD4;
	float3 texcoord_5 : TEXCOORD5;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = getPosition(IN.position);
	
	float3 dir = float3(0.0f,0.0f,1.0f);
	
	#ifdef HBLUR
		if(IN.texcoord.w == 0.0f || IN.texcoord.w == 1.0f) dir = float3(0.0f,1.0f,0.0f);
		if(IN.texcoord.w == 2.0f || IN.texcoord.w == 3.0f) dir = float3(1.0f,0.0f,0.0f);
		if(IN.texcoord.w == 4.0f || IN.texcoord.w == 5.0f) dir = float3(1.0f,0.0f,0.0f);
	#elif VBLUR
		if(IN.texcoord.w == 0.0f || IN.texcoord.w == 1.0f) dir = float3(0.0f,0.0f,1.0f);
		if(IN.texcoord.w == 2.0f || IN.texcoord.w == 3.0f) dir = float3(0.0f,0.0f,1.0f);
		if(IN.texcoord.w == 4.0f || IN.texcoord.w == 5.0f) dir = float3(0.0f,1.0f,0.0f);
	#endif
	
	float3 texcoord = normalize(IN.texcoord.xyz);
	float3 offset = normalize(cross(texcoord,dir)) * s_viewport.z * 1.5f;
	
	OUT.texcoord_0 = texcoord;
	OUT.texcoord_1 = offset * 1.0f;
	OUT.texcoord_2 = offset * 2.0f;
	OUT.texcoord_3 = offset * 3.0f;
	OUT.texcoord_4 = offset * 4.0f;
	OUT.texcoord_5 = offset * 5.0f;
	
	return OUT;
}

#endif
