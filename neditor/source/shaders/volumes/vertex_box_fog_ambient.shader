/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_box_fog_ambient.shader
 * Desc:    VolumeBox fog ambient shader
 * Version: 1.13
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
attribute float4 s_attribute_2;

uniform float4 s_volume_plane;

uniform float volume_density;
uniform float height_falloff;

/*
 */
void main() {
	
	gl_Position = s_modelviewprojection * s_attribute_0;
	
	float perspective = gl_Position.w / (s_modelviewprojection * s_attribute_2).w;
	
	gl_TexCoord[0] = float4(s_attribute_1.xyz / s_depth_range.y,1.0f);
	gl_TexCoord[1] = float4(s_attribute_2.xyz / s_depth_range.y,1.0f) * perspective;
	
	gl_TexCoord[2].x = s_depth_range.y * volume_density;
	
	#ifdef HEIGHT
		gl_TexCoord[3] = s_volume_plane * height_falloff;
		gl_TexCoord[4].x = dot(gl_TexCoord[3],s_attribute_1);
		gl_TexCoord[5] = s_attribute_2 * perspective;
	#endif
	
	#ifdef NOISE
		gl_TexCoord[6].xy = s_viewport.xy / s_material_textures[0].xy;
	#endif
	
	gl_TexCoord[7] = getProjection(gl_Position);
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

struct VERTEX_OUT {
	float4 position : POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float1 texcoord_2 : TEXCOORD2;
	#ifdef HEIGHT
		float4 texcoord_3 : TEXCOORD3;
		float1 texcoord_4 : TEXCOORD4;
		float4 texcoord_5 : TEXCOORD5;
	#endif
	#ifdef NOISE
		float2 texcoord_6 : TEXCOORD6;
	#endif
	float4 texcoord_7 : TEXCOORD7;
};

float4 s_volume_plane;

float volume_density;
float height_falloff;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = mul(s_modelviewprojection,IN.position);
	
	float perspective = OUT.position.w / mul(s_modelviewprojection,IN.texcoord_1).w;
	
	OUT.texcoord_0 = float4(IN.texcoord_0.xyz / s_depth_range.y,1.0f);
	OUT.texcoord_1 = float4(IN.texcoord_1.xyz / s_depth_range.y,1.0f) * perspective;
	
	OUT.texcoord_2.x = s_depth_range.y * volume_density;
	
	#ifdef HEIGHT
		OUT.texcoord_3 = s_volume_plane * height_falloff;
		OUT.texcoord_4.x = dot(OUT.texcoord_3,IN.texcoord_0);
		OUT.texcoord_5 = IN.texcoord_1 * perspective;
	#endif
	
	#ifdef NOISE
		OUT.texcoord_6 = s_viewport.xy / s_material_textures[0].xy;
	#endif
	
	OUT.texcoord_7 = getProjection(OUT.position);
	
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

struct VERTEX_OUT {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float1 texcoord_2 : TEXCOORD2;
	#ifdef HEIGHT
		float4 texcoord_3 : TEXCOORD3;
		float1 texcoord_4 : TEXCOORD4;
		float4 texcoord_5 : TEXCOORD5;
	#endif
	#ifdef NOISE
		float2 texcoord_6 : TEXCOORD6;
	#endif
};

cbuffer shader_volume_parameters {
	float4 s_volume_plane;
};

cbuffer shader_parameters {
	float volume_density;
	float height_falloff;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = mul(s_modelviewprojection,IN.position);
	
	float perspective = OUT.position.w / mul(s_modelviewprojection,IN.texcoord_1).w;
	
	OUT.texcoord_0 = float4(IN.texcoord_0.xyz / s_depth_range.y,1.0f);
	OUT.texcoord_1 = float4(IN.texcoord_1.xyz / s_depth_range.y,1.0f) * perspective;
	
	OUT.texcoord_2.x = s_depth_range.y * volume_density;
	
	#ifdef HEIGHT
		OUT.texcoord_3 = s_volume_plane * height_falloff;
		OUT.texcoord_4.x = dot(OUT.texcoord_3,IN.texcoord_0);
		OUT.texcoord_5 = IN.texcoord_1 * perspective;
	#endif
	
	#ifdef NOISE
		OUT.texcoord_6 = 1.0f / s_material_textures[0].xy;
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
	float4 texcoord_0 : ATTR1;
	float4 texcoord_1 : ATTR2;
};

struct VERTEX_OUT {
	float4 position : POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float1 texcoord_2 : TEXCOORD2;
	#ifdef HEIGHT
		float4 texcoord_3 : TEXCOORD3;
		float1 texcoord_4 : TEXCOORD4;
		float4 texcoord_5 : TEXCOORD5;
	#endif
	#ifdef NOISE
		float2 texcoord_6 : TEXCOORD6;
	#endif
	float4 texcoord_9 : TEXCOORD9;
};

uniform float4 s_volume_plane;

uniform float volume_density;
uniform float height_falloff;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = mul(s_modelviewprojection,IN.position);
	
	float perspective = OUT.position.w / mul(s_modelviewprojection,IN.texcoord_1).w;
	
	OUT.texcoord_0 = float4(IN.texcoord_0.xyz / s_depth_range.y,1.0f);
	OUT.texcoord_1 = float4(IN.texcoord_1.xyz / s_depth_range.y,1.0f) * perspective;
	
	OUT.texcoord_2.x = s_depth_range.y * volume_density;
	
	#ifdef HEIGHT
		OUT.texcoord_3 = s_volume_plane * height_falloff;
		OUT.texcoord_4.x = dot(OUT.texcoord_3,IN.texcoord_0);
		OUT.texcoord_5 = IN.texcoord_1 * perspective;
	#endif
	
	#ifdef NOISE
		OUT.texcoord_6 = s_viewport.xy / s_material_textures[0].xy;
	#endif
	
	OUT.texcoord_9 = getProjection(OUT.position);
	
	return OUT;
}

#endif
