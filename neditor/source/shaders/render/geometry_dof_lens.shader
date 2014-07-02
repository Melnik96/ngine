/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    geometry_dof_lens.shader
 * Desc:    Render dof lens shader
 * Version: 1.01
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

#include <core/shaders/common/geometry_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

#ifdef USE_GEOMETRY_SHADER

layout(points) in;
layout(triangle_strip,max_vertices = 4) out;

/*
 */
void main() {
	
	float2 size = gl_TexCoordIn[0][0].xy;
	
	gl_Position = gl_PositionIn[0] + float4(-size.x,-size.y,0.0f,0.0f);
	gl_TexCoord[0] = float4(gl_PositionIn[0].xy,0.0f,0.0f);
	EmitVertex();
	
	gl_Position = gl_PositionIn[0] + float4(size.x,-size.y,0.0f,0.0f);
	gl_TexCoord[0] = float4(gl_PositionIn[0].xy,1.0f,0.0f);
	EmitVertex();
	
	gl_Position = gl_PositionIn[0] + float4(-size.x,size.y,0.0f,0.0f);
	gl_TexCoord[0] = float4(gl_PositionIn[0].xy,0.0f,1.0f);
	EmitVertex();
	
	gl_Position = gl_PositionIn[0] + float4(size.x,size.y,0.0f,0.0f);
	gl_TexCoord[0] = float4(gl_PositionIn[0].xy,1.0f,1.0f);
	EmitVertex();
	
	EndPrimitive();
}

#endif

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

struct GEOMETRY_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
};

struct GEOMETRY_OUT {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
};

/*
 */
[maxvertexcount(4)]
void main(point GEOMETRY_IN IN[1],inout TriangleStream<GEOMETRY_OUT> stream) {
	
	GEOMETRY_OUT OUT;
	
	float2 size = IN[0].texcoord_0;
	
	OUT.position = IN[0].position + float4(-size.x,-size.y,0.0f,0.0f);
	OUT.texcoord_0 = float4(IN[0].position.xy,0.0f,0.0f);
	stream.Append(OUT);
	
	OUT.position = IN[0].position + float4(size.x,-size.y,0.0f,0.0f);
	OUT.texcoord_0 = float4(IN[0].position.xy,1.0f,0.0f);
	stream.Append(OUT);
	
	OUT.position = IN[0].position + float4(-size.x,size.y,0.0f,0.0f);
	OUT.texcoord_0 = float4(IN[0].position.xy,0.0f,1.0f);
	stream.Append(OUT);
	
	OUT.position = IN[0].position + float4(size.x,size.y,0.0f,0.0f);
	OUT.texcoord_0 = float4(IN[0].position.xy,1.0f,1.0f);
	stream.Append(OUT);
	
	stream.RestartStrip();
}

#endif
