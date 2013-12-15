/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_hdr_scale.shader
 * Desc:    Render hdr scale shader
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
attribute float4 s_attribute_1;

/*
 */
void main() {
	
	gl_Position = getPosition(s_attribute_0);
	
	float4 texcoord = s_attribute_1.xyxy;
	float4 offset = s_viewport.zwzw / 4.0f;
	
	gl_TexCoord[0] = texcoord + offset * float4(-1.5f,-1.5f,-0.5f,-1.5f);
	gl_TexCoord[1] = texcoord + offset * float4( 0.5f,-1.5f, 1.5f,-1.5f);
	gl_TexCoord[2] = texcoord + offset * float4(-1.5f,-0.5f,-0.5f,-0.5f);
	gl_TexCoord[3] = texcoord + offset * float4( 0.5f,-0.5f, 1.5f,-0.5f);
	gl_TexCoord[4] = texcoord + offset * float4(-1.5f, 0.5f,-0.5f, 0.5f);
	gl_TexCoord[5] = texcoord + offset * float4( 0.5f, 0.5f, 1.5f, 0.5f);
	gl_TexCoord[6] = texcoord + offset * float4(-1.5f, 1.5f,-0.5f, 1.5f);
	gl_TexCoord[7] = texcoord + offset * float4( 0.5f, 1.5f, 1.5f, 1.5f);
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
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	float4 texcoord_4 : TEXCOORD4;
	float4 texcoord_5 : TEXCOORD5;
	float4 texcoord_6 : TEXCOORD6;
	float4 texcoord_7 : TEXCOORD7;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = getPosition(IN.position);
	
	float4 texcoord = IN.texcoord.xyxy;
	float4 offset = s_viewport.zwzw / 4.0f;
	
	OUT.texcoord_0 = texcoord + offset * float4(-1.5f,-1.5f,-0.5f,-1.5f);
	OUT.texcoord_1 = texcoord + offset * float4( 0.5f,-1.5f, 1.5f,-1.5f);
	OUT.texcoord_2 = texcoord + offset * float4(-1.5f,-0.5f,-0.5f,-0.5f);
	OUT.texcoord_3 = texcoord + offset * float4( 0.5f,-0.5f, 1.5f,-0.5f);
	OUT.texcoord_4 = texcoord + offset * float4(-1.5f, 0.5f,-0.5f, 0.5f);
	OUT.texcoord_5 = texcoord + offset * float4( 0.5f, 0.5f, 1.5f, 0.5f);
	OUT.texcoord_6 = texcoord + offset * float4(-1.5f, 1.5f,-0.5f, 1.5f);
	OUT.texcoord_7 = texcoord + offset * float4( 0.5f, 1.5f, 1.5f, 1.5f);
	
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
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	float4 texcoord_4 : TEXCOORD4;
	float4 texcoord_5 : TEXCOORD5;
	float4 texcoord_6 : TEXCOORD6;
	float4 texcoord_7 : TEXCOORD7;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = getPosition(IN.position);
	
	float4 texcoord = IN.texcoord.xyxy;
	float4 offset = s_viewport.zwzw / 4.0f;
	
	OUT.texcoord_0 = texcoord + offset * float4(-1.5f,-1.5f,-0.5f,-1.5f);
	OUT.texcoord_1 = texcoord + offset * float4( 0.5f,-1.5f, 1.5f,-1.5f);
	OUT.texcoord_2 = texcoord + offset * float4(-1.5f,-0.5f,-0.5f,-0.5f);
	OUT.texcoord_3 = texcoord + offset * float4( 0.5f,-0.5f, 1.5f,-0.5f);
	OUT.texcoord_4 = texcoord + offset * float4(-1.5f, 0.5f,-0.5f, 0.5f);
	OUT.texcoord_5 = texcoord + offset * float4( 0.5f, 0.5f, 1.5f, 0.5f);
	OUT.texcoord_6 = texcoord + offset * float4(-1.5f, 1.5f,-0.5f, 1.5f);
	OUT.texcoord_7 = texcoord + offset * float4( 0.5f, 1.5f, 1.5f, 1.5f);
	
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
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	float4 texcoord_4 : TEXCOORD4;
	float4 texcoord_5 : TEXCOORD5;
	float4 texcoord_6 : TEXCOORD6;
	float4 texcoord_7 : TEXCOORD7;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = getPosition(IN.position);
	
	float4 texcoord = IN.texcoord.xyxy;
	float4 offset = s_viewport.zwzw / 4.0f;
	
	OUT.texcoord_0 = texcoord + offset * float4(-1.5f,-1.5f,-0.5f,-1.5f);
	OUT.texcoord_1 = texcoord + offset * float4( 0.5f,-1.5f, 1.5f,-1.5f);
	OUT.texcoord_2 = texcoord + offset * float4(-1.5f,-0.5f,-0.5f,-0.5f);
	OUT.texcoord_3 = texcoord + offset * float4( 0.5f,-0.5f, 1.5f,-0.5f);
	OUT.texcoord_4 = texcoord + offset * float4(-1.5f, 0.5f,-0.5f, 0.5f);
	OUT.texcoord_5 = texcoord + offset * float4( 0.5f, 0.5f, 1.5f, 0.5f);
	OUT.texcoord_6 = texcoord + offset * float4(-1.5f, 1.5f,-0.5f, 1.5f);
	OUT.texcoord_7 = texcoord + offset * float4( 0.5f, 1.5f, 1.5f, 1.5f);
	
	return OUT;
}

#endif
