/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    control_base.shader
 * Desc:    Mesh base shader
 * Version: 1.10
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

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

#ifdef USE_TESSELLATION && TESSELLATION

#include <core/shaders/common/control_base.h>
#include <core/shaders/meshes/control_base.h>

layout(vertices = 3) out;

/*
 */
void main() {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 p0 = getPosition(float4(gl_in[0].gl_Position.xyz,1.0f));
		float4 p1 = getPosition(float4(gl_in[1].gl_Position.xyz,1.0f));
		float4 p2 = getPosition(float4(gl_in[2].gl_Position.xyz,1.0f));
	#else
		float4 p0 = getPosition(gl_in[0].gl_Position);
		float4 p1 = getPosition(gl_in[1].gl_Position);
		float4 p2 = getPosition(gl_in[2].gl_Position);
	#endif
	
	p0.xy /= p0.w;
	p1.xy /= p1.w;
	p2.xy /= p2.w;
	
	if(!all(lessThan(float4(min(min(p0.xy,p1.xy),p2.xy),-max(max(p0.xy,p1.xy),p2.xy)),float4(1.2f)))) {
		gl_TessLevelOuter[0] = 0.0f;
		gl_TessLevelOuter[1] = 0.0f;
		gl_TessLevelOuter[2] = 0.0f;
		gl_TessLevelInner[0] = 0.0f;
		return;
	}
	
	float l0 = length(gl_in[1].gl_Position.xyz - gl_in[2].gl_Position.xyz);
	float l1 = length(gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz);
	float l2 = length(gl_in[0].gl_Position.xyz - gl_in[1].gl_Position.xyz);
	
	float f0 = (gl_in[1].gl_TexCoord[7].w + gl_in[2].gl_TexCoord[7].w) * saturate(l0 * s_material_tessellation_distance.z);
	float f1 = (gl_in[2].gl_TexCoord[7].w + gl_in[0].gl_TexCoord[7].w) * saturate(l1 * s_material_tessellation_distance.z);
	float f2 = (gl_in[0].gl_TexCoord[7].w + gl_in[1].gl_TexCoord[7].w) * saturate(l2 * s_material_tessellation_distance.z);
	
	gl_TessLevelOuter[0] = f0;
	gl_TessLevelOuter[1] = f1;
	gl_TessLevelOuter[2] = f2;
	gl_TessLevelInner[0] = (f0 + f1 + f2) * (1.0f / 3.0f);
	
	#include <core/shaders/meshes/control_base.h>
}

#endif

/******************************************************************************\
*
* Direct3D11
*
\******************************************************************************/

#elif DIRECT3D11

#ifdef USE_TESSELLATION && TESSELLATION

#include <core/shaders/common/control_base.h>
#include <core/shaders/meshes/control_base.h>

struct CONTROL_CONSTANT_OUT {
	float edges[3] : SV_TESSFACTOR;
	float inside : SV_INSIDETESSFACTOR;
};

/*
 */
CONTROL_CONSTANT_OUT constant(InputPatch<CONTROL_IO,3> patch) {
	
	CONTROL_CONSTANT_OUT OUT;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 p0 = getPosition(float4(patch[0].position.xyz,1.0f));
		float4 p1 = getPosition(float4(patch[1].position.xyz,1.0f));
		float4 p2 = getPosition(float4(patch[2].position.xyz,1.0f));
	#else
		float4 p0 = getPosition(patch[0].position);
		float4 p1 = getPosition(patch[1].position);
		float4 p2 = getPosition(patch[2].position);
	#endif
	
	p0.xy /= p0.w;
	p1.xy /= p1.w;
	p2.xy /= p2.w;
	
	[branch] if(!all(float4(min(min(p0.xy,p1.xy),p2.xy),-max(max(p0.xy,p1.xy),p2.xy)) < 1.2f)) {
		OUT.edges[0] = 0.0f;
		OUT.edges[1] = 0.0f;
		OUT.edges[2] = 0.0f;
		OUT.inside = 0.0f;
		return OUT;
	}
	
	float l0 = length(patch[1].position.xyz - patch[2].position.xyz);
	float l1 = length(patch[2].position.xyz - patch[0].position.xyz);
	float l2 = length(patch[0].position.xyz - patch[1].position.xyz);
	
	float f0 = (patch[1].texcoord_9.w + patch[2].texcoord_9.w) * saturate(l0 * s_material_tessellation_distance.z);
	float f1 = (patch[2].texcoord_9.w + patch[0].texcoord_9.w) * saturate(l1 * s_material_tessellation_distance.z);
	float f2 = (patch[0].texcoord_9.w + patch[1].texcoord_9.w) * saturate(l2 * s_material_tessellation_distance.z);
	
	OUT.edges[0] = f0;
	OUT.edges[1] = f1;
	OUT.edges[2] = f2;
	OUT.inside = (f0 + f1 + f2) * (1.0f / 3.0f);
	
	return OUT;
}

/*
 */
[domain("tri")]
[maxtessfactor(15.0f)]
[outputcontrolpoints(3)]
[patchconstantfunc("constant")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
CONTROL_IO main(InputPatch<CONTROL_IO,3> patch,uint ID : SV_OUTPUTCONTROLPOINTID) {
	
	#include <core/shaders/meshes/control_base.h>
	
	return patch[ID];
}

#endif

#endif
