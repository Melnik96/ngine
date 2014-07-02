/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_box_cloud_ambient.shader
 * Desc:    VolumeBox cloud ambient shader
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
attribute float4 s_attribute_1;
attribute float4 s_attribute_2;

uniform float4x4 s_volume_texcoord;

uniform float4 base_scale;
uniform float4 base_offset;

/*
 */
void main() {
	
	gl_Position = s_modelviewprojection * s_attribute_0;
	
	float perspective = gl_Position.w / (s_modelviewprojection * s_attribute_2).w;
	
	gl_TexCoord[0] = float4(s_attribute_1.xyz / s_depth_range.y,1.0f);
	gl_TexCoord[1] = float4(s_attribute_2.xyz / s_depth_range.y,1.0f) * perspective;
	
	gl_TexCoord[2] = float4((s_volume_texcoord * s_attribute_1).xyz * base_scale.xyz + base_offset.xyz,1.0f);
	gl_TexCoord[3] = float4((s_volume_texcoord * s_attribute_2).xyz * base_scale.xyz + base_offset.xyz,1.0f) * perspective;
	
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
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	float4 texcoord_7 : TEXCOORD7;
};

float4x4 s_volume_texcoord;

float4 base_scale;
float4 base_offset;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = mul(s_modelviewprojection,IN.position);
	
	float perspective = OUT.position.w / mul(s_modelviewprojection,IN.texcoord_1).w;
	
	OUT.texcoord_0 = float4(IN.texcoord_0.xyz / s_depth_range.y,1.0f);
	OUT.texcoord_1 = float4(IN.texcoord_1.xyz / s_depth_range.y,1.0f) * perspective;
	
	OUT.texcoord_2 = float4(mul(s_volume_texcoord,IN.texcoord_0).xyz * base_scale.xyz + base_offset.xyz,1.0f);
	OUT.texcoord_3 = float4(mul(s_volume_texcoord,IN.texcoord_1).xyz * base_scale.xyz + base_offset.xyz,1.0f) * perspective;
	
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
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
};

cbuffer shader_volume_parameters {
	float4x4 s_volume_texcoord;
};

cbuffer shader_parameters {
	float4 base_scale;
	float4 base_offset;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = mul(s_modelviewprojection,IN.position);
	
	float perspective = OUT.position.w / mul(s_modelviewprojection,IN.texcoord_1).w;
	
	OUT.texcoord_0 = float4(IN.texcoord_0.xyz / s_depth_range.y,1.0f);
	OUT.texcoord_1 = float4(IN.texcoord_1.xyz / s_depth_range.y,1.0f) * perspective;
	
	OUT.texcoord_2 = float4(mul(s_volume_texcoord,IN.texcoord_0).xyz * base_scale.xyz + base_offset.xyz,1.0f);
	OUT.texcoord_3 = float4(mul(s_volume_texcoord,IN.texcoord_1).xyz * base_scale.xyz + base_offset.xyz,1.0f) * perspective;
	
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
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	float4 texcoord_9 : TEXCOORD9;
};

uniform float4x4 s_volume_texcoord;

uniform float4 base_scale;
uniform float4 base_offset;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	OUT.position = mul(s_modelviewprojection,IN.position);
	
	float perspective = OUT.position.w / mul(s_modelviewprojection,IN.texcoord_1).w;
	
	OUT.texcoord_0 = float4(IN.texcoord_0.xyz / s_depth_range.y,1.0f);
	OUT.texcoord_1 = float4(IN.texcoord_1.xyz / s_depth_range.y,1.0f) * perspective;
	
	OUT.texcoord_2 = float4(mul(s_volume_texcoord,IN.texcoord_0).xyz * base_scale.xyz + base_offset.xyz,1.0f);
	OUT.texcoord_3 = float4(mul(s_volume_texcoord,IN.texcoord_1).xyz * base_scale.xyz + base_offset.xyz,1.0f) * perspective;
	
	OUT.texcoord_9 = getProjection(OUT.position);
	
	return OUT;
}

#endif
