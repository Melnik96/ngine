/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    geometry_base_wireframe.shader
 * Desc:    Terrain base wireframe shader
 * Version: 1.03
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

layout(triangles) in;
layout(line_strip,max_vertices = 4) out;

/*
 */
void main() {
	
	if(gl_PositionIn[0] != gl_PositionIn[1] && gl_PositionIn[1] != gl_PositionIn[2] && gl_PositionIn[2] != gl_PositionIn[0]) {
		
		gl_Position = gl_PositionIn[0] - float4(0.0f,0.0f,0.0001f,0.0f);
		EmitVertex();
		
		gl_Position = gl_PositionIn[1] - float4(0.0f,0.0f,0.0001f,0.0f);
		EmitVertex();
		
		gl_Position = gl_PositionIn[2] - float4(0.0f,0.0f,0.0001f,0.0f);
		EmitVertex();
		
		gl_Position = gl_PositionIn[0] - float4(0.0f,0.0f,0.0001f,0.0f);
		EmitVertex();
		
		EndPrimitive();
	}
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
};

struct GEOMETRY_OUT {
	float4 position : SV_POSITION;
};

/*
 */
[maxvertexcount(4)]
void main(triangle GEOMETRY_IN IN[3],inout LineStream<GEOMETRY_OUT> stream) {
	
	GEOMETRY_OUT OUT;
	
	[branch] if(any(IN[0].position != IN[1].position) && any(IN[1].position != IN[2].position) && any(IN[2].position != IN[0].position)) {
		
		OUT.position = IN[0].position - float4(0.0f,0.0f,0.0001f,0.0f);
		stream.Append(OUT);
		
		OUT.position = IN[1].position - float4(0.0f,0.0f,0.0001f,0.0f);
		stream.Append(OUT);
		
		OUT.position = IN[2].position - float4(0.0f,0.0f,0.0001f,0.0f);
		stream.Append(OUT);
		
		OUT.position = IN[0].position - float4(0.0f,0.0f,0.0001f,0.0f);
		stream.Append(OUT);
		
		stream.RestartStrip();
	}
}

#endif
