/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_dof_lens.shader
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

#include <core/shaders/common/vertex_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

#ifdef USE_GEOMETRY_SHADER

uniform sampler2D s_texture_0;

uniform float blur_radius;

/*
 */
void main() {
	
	int width = int(s_viewport.x);
	int x = (gl_VertexID % width) * 2;
	int y = (gl_VertexID / width) * 2;
	
	gl_Position.x = float(x) * s_viewport.z - 1.0f;
	gl_Position.y = float(y) * s_viewport.w - 1.0f;
	gl_Position.z = 0.0f;
	gl_Position.w = 1.0f;
	
	int2 texcoord = int2(x,y);
	float weight = texelFetch(s_texture_0,texcoord,0).w;
	weight += texelFetchOffset(s_texture_0,texcoord,0,int2(1,0)).w;
	weight += texelFetchOffset(s_texture_0,texcoord,0,int2(0,1)).w;
	weight += texelFetchOffset(s_texture_0,texcoord,0,int2(1,1)).w;
	
	gl_TexCoord[0].xy = s_viewport.zw * (2.0f + blur_radius * weight * 0.25f);
}

#else

/*
 */
void main() {
	
	gl_Position = float4(0.0f,0.0f,0.0f,1.0f);
}

#endif

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

/*
 */
float4 main() : POSITION {
	
	return float4(0.0f,0.0f,0.0f,1.0f);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);

struct VERTEX_IN {
	uint vertex : SV_VERTEXID;
	uint instance : SV_INSTANCEID;
};

struct VERTEX_OUT {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
};

float blur_radius;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	int x = IN.vertex * 2;
	int y = IN.instance * 2;
	
	OUT.position.x = (float)x * s_viewport.z - 1.0f;
	OUT.position.y = (float)y * s_viewport.w - 1.0f;
	OUT.position.z = 0.0f;
	OUT.position.w = 1.0f;
	
	#ifdef USE_FEATURE_LEVEL_11_0
		
		float2 texcoord = OUT.position.xy * 0.5f + 0.5f;
		float4 sample = s_texture_0.GatherAlpha(s_sampler_0,texcoord);
		float weight = dot(sample,1.0f);
		
	#else
		
		int3 texcoord = int3(x,y,0);
		float weight = s_texture_0.Load(texcoord).w;
		weight += s_texture_0.Load(texcoord,int2(1,0)).w;
		weight += s_texture_0.Load(texcoord,int2(0,1)).w;
		weight += s_texture_0.Load(texcoord,int2(1,1)).w;
		
	#endif
	
	OUT.texcoord_0 = s_viewport.zw * (2.0f + blur_radius * weight * 0.25f);
	
	return OUT;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

/*
 */
float4 main() : POSITION {
	
	return float4(0.0f,0.0f,0.0f,1.0f);
}

#endif
