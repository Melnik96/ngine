/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_leaf.shader
 * Desc:    Mesh leaf vertex shader
 * Version: 1.23
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
#include <core/shaders/meshes/vertex_base.h>

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
attribute float s_attribute_4;

attribute float4 s_attribute_13;
attribute float4 s_attribute_14;
attribute float4 s_attribute_15;

uniform float4 s_instances[96];

uniform float4 base_transform;

uniform float4 noise_transform;
uniform float shadow_offset;

/*
 */
void main() {
	
	float4 row_0,row_1,row_2;
	
	#ifdef USE_INSTANCING
		#ifdef HAS_ARB_DRAW_INSTANCED
			int3 instance = int3(gl_InstanceID * 3) + int3(0,1,2);
		#elif USE_PSEUDO_INSTANCING
			int3 instance = int3(s_attribute_4 * 3.0f) + int3(0,1,2);
		#endif
		row_0 = s_instances[instance.x];
		row_1 = s_instances[instance.y];
		row_2 = s_instances[instance.z];
	#elif USE_PSEUDO_TRANSFORM
		row_0 = s_attribute_13;
		row_1 = s_attribute_14;
		row_2 = s_attribute_15;
	#else
		row_0 = s_transform[0];
		row_1 = s_transform[1];
		row_2 = s_transform[2];
	#endif
	
	float4 position = float4(s_attribute_0.x,s_attribute_0.y,s_attribute_2.w,1.0f);
	float4 vertex = float4(dot(row_0,position),dot(row_1,position),dot(row_2,position),1.0f);
	
	float3 normal = normalize(float3(dot(row_0.xyz,s_attribute_2.xyz),dot(row_1.xyz,s_attribute_2.xyz),dot(row_2.xyz,s_attribute_2.xyz)));
	float3 tangent = normalize(float3(dot(row_0.xyz,s_attribute_3.xyz),dot(row_1.xyz,s_attribute_3.xyz),dot(row_2.xyz,s_attribute_3.xyz)));
	float3 binormal = normalize(cross(normal,tangent) * s_attribute_3.w);
	
	#ifdef LEAFS_BILLBOARD
		#ifdef NOISE
			float3 noise = vertex.xyz;
			noise -= tangent * s_attribute_1.z;
			noise += binormal * s_attribute_1.w;
			gl_TexCoord[6].xyz = noise * noise_transform.xyz;
		#endif
		normal = normalize(float3(s_modelview[0][2],s_modelview[1][2],s_modelview[2][2]));
		tangent = -normalize(float3(s_modelview[0][0],s_modelview[1][0],s_modelview[2][0]));
		binormal = -normalize(float3(s_modelview[0][1],s_modelview[1][1],s_modelview[2][1]));
		#ifdef ANIMATION
			float leaf_time = dot(position.xyz,float3(s_material_animation_leaf.x)) + s_material_animation_leaf.z;
			float leaf_angle = sin(leaf_time) * s_material_animation_leaf.y;
			float leaf_sin = sin(leaf_angle);
			float leaf_cos = cos(leaf_angle);
			float3 leaf_tangent = tangent;
			float3 leaf_binormal = binormal;
			tangent = leaf_tangent * leaf_cos - leaf_binormal * leaf_sin;
			binormal = leaf_tangent * leaf_sin + leaf_binormal * leaf_cos;
		#endif
		vertex.xyz -= tangent * s_attribute_1.z * abs(row_2.z);
		vertex.xyz += binormal * s_attribute_1.w * abs(row_2.z);
		#ifdef LEAF_SHADOW
			vertex.xyz += normal * shadow_offset;
		#endif
	#else
		#ifdef NOISE
			gl_TexCoord[6].xyz = vertex.xyz * noise_transform.xyz;
		#endif
	#endif
	
	float4 texcoord = s_attribute_1;
	texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
	
	#ifdef ANIMATION
		float2 stem_center = float2(row_0.w,row_1.w);
		float stem_scale = max(position.z * s_material_animation_stem.y,0.0f);
		float stem_angle = dot(stem_center,float2(s_material_animation_stem.x)) + s_material_animation_stem.w;
		float2 stem_offset = getAnimationOffset(stem_angle) * (stem_scale * stem_scale);
		vertex.z += dot(stem_offset,stem_center - vertex.xy) * s_material_animation_stem.z;
		vertex.xy += stem_offset;
		#ifdef LEAFS_GEOMETRY
			float leaf_scale = dot(texcoord.zw,float2(1.0f));
			float leaf_time = dot(position.xyz,float3(s_material_animation_leaf.x)) + s_material_animation_leaf.z;
			vertex.z += sin(leaf_time) * leaf_scale * s_material_animation_leaf.y;
		#endif
	#endif
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
		bound_sphere.xyz = float3(dot(row_0,bound_sphere),dot(row_1,bound_sphere),dot(row_2,bound_sphere));
		bound_sphere.w = s_surface_bound_sphere.w * length(float3(row_0.x,row_1.x,row_2.x));
	#endif
	
	#include <core/shaders/meshes/vertex_base.h>
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
	float1 texcoord_3 : TEXCOORD3;
};

float4 s_instances[96];

float4 base_transform;

float4 noise_transform;
float shadow_offset;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 row_0,row_1,row_2;
	
	#ifdef USE_INSTANCING
		int3 instance = int(IN.texcoord_3 * 3.0f) + int3(0,1,2);
		row_0 = s_instances[instance.x];
		row_1 = s_instances[instance.y];
		row_2 = s_instances[instance.z];
	#else
		row_0 = s_transform[0];
		row_1 = s_transform[1];
		row_2 = s_transform[2];
	#endif
	
	float4 position = float4(IN.position.x,IN.position.y,IN.texcoord_1.w,1.0f);
	float4 vertex = float4(dot(row_0,position),dot(row_1,position),dot(row_2,position),1.0f);
	
	float3 normal = normalize(float3(dot(row_0.xyz,IN.texcoord_1.xyz),dot(row_1.xyz,IN.texcoord_1.xyz),dot(row_2.xyz,IN.texcoord_1.xyz)));
	float3 tangent = normalize(float3(dot(row_0.xyz,IN.texcoord_2.xyz),dot(row_1.xyz,IN.texcoord_2.xyz),dot(row_2.xyz,IN.texcoord_2.xyz)));
	float3 binormal = normalize(cross(normal,tangent) * IN.texcoord_2.w);
	
	#ifdef LEAFS_BILLBOARD
		#ifdef NOISE
			float3 noise = vertex.xyz;
			noise -= tangent * IN.texcoord_0.z;
			noise += binormal * IN.texcoord_0.w;
			OUT.texcoord_6 = noise * noise_transform.xyz;
		#endif
		normal = normalize(s_modelview[2].xyz);
		tangent = -normalize(s_modelview[0].xyz);
		binormal = -normalize(s_modelview[1].xyz);
		#ifdef LEAF_SHADOW
			binormal = -binormal;
		#endif
		#ifdef ANIMATION
			float leaf_sin,leaf_cos;
			float leaf_time = dot(position.xyz,s_material_animation_leaf.x) + s_material_animation_leaf.z;
			float leaf_angle = sin(leaf_time) * s_material_animation_leaf.y;
			sincos(leaf_angle,leaf_sin,leaf_cos);
			float3 leaf_tangent = tangent;
			float3 leaf_binormal = binormal;
			tangent = leaf_tangent * leaf_cos - leaf_binormal * leaf_sin;
			binormal = leaf_tangent * leaf_sin + leaf_binormal * leaf_cos;
		#endif
		vertex.xyz -= tangent * IN.texcoord_0.z * abs(row_2.z);
		vertex.xyz += binormal * IN.texcoord_0.w * abs(row_2.z);
		#ifdef LEAF_SHADOW
			vertex.xyz += normal * shadow_offset;
		#endif
	#else
		#ifdef NOISE
			OUT.texcoord_6 = vertex.xyz * noise_transform.xyz;
		#endif
	#endif
	
	float4 texcoord = IN.texcoord_0;
	texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
	
	#ifdef ANIMATION
		float2 stem_center = float2(row_0.w,row_1.w);
		float stem_scale = max(position.z * s_material_animation_stem.y,0.0f);
		float stem_angle = dot(stem_center,s_material_animation_stem.x) + s_material_animation_stem.w;
		float2 stem_offset = getAnimationOffset(stem_angle) * (stem_scale * stem_scale);
		vertex.z += dot(stem_offset,stem_center - vertex.xy) * s_material_animation_stem.z;
		vertex.xy += stem_offset;
		#ifdef LEAFS_GEOMETRY
			float leaf_scale = dot(texcoord.zw,1.0f);
			float leaf_time = dot(position.xyz,s_material_animation_leaf.x) + s_material_animation_leaf.z;
			vertex.z += sin(leaf_time) * leaf_scale * s_material_animation_leaf.y;
		#endif
	#endif
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
		bound_sphere.xyz = float3(dot(row_0,bound_sphere),dot(row_1,bound_sphere),dot(row_2,bound_sphere));
		bound_sphere.w = s_surface_bound_sphere.w * length(float3(row_0.x,row_1.x,row_2.x));
	#endif
	
	#include <core/shaders/meshes/vertex_base.h>
	
	return OUT;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);

struct VERTEX_IN {
	float4 position : POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	uint instance : SV_INSTANCEID;
};

cbuffer shader_instances_parameters {
	float4 s_instances[96];
};

cbuffer shader_parameters {
	float4 base_transform;
	float4 noise_transform;
	float shadow_offset;
};

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 row_0,row_1,row_2;
	
	#ifdef USE_INSTANCING
		[flatten] if(IN.instance == 0) {
			row_0 = s_transform[0];
			row_1 = s_transform[1];
			row_2 = s_transform[2];
		} else {
			int3 instance = IN.instance * 3 + int3(0,1,2);
			row_0 = s_instances[instance.x];
			row_1 = s_instances[instance.y];
			row_2 = s_instances[instance.z];
		}
	#else
		row_0 = s_transform[0];
		row_1 = s_transform[1];
		row_2 = s_transform[2];
	#endif
	
	float4 position = float4(IN.position.x,IN.position.y,IN.texcoord_1.w,1.0f);
	float4 vertex = float4(dot(row_0,position),dot(row_1,position),dot(row_2,position),1.0f);
	
	float3 normal = normalize(float3(dot(row_0.xyz,IN.texcoord_1.xyz),dot(row_1.xyz,IN.texcoord_1.xyz),dot(row_2.xyz,IN.texcoord_1.xyz)));
	float3 tangent = normalize(float3(dot(row_0.xyz,IN.texcoord_2.xyz),dot(row_1.xyz,IN.texcoord_2.xyz),dot(row_2.xyz,IN.texcoord_2.xyz)));
	float3 binormal = normalize(cross(normal,tangent) * IN.texcoord_2.w);
	
	#ifdef LEAFS_BILLBOARD
		#ifdef NOISE
			float3 noise = vertex.xyz;
			noise -= tangent * IN.texcoord_0.z;
			noise += binormal * IN.texcoord_0.w;
			OUT.texcoord_6 = noise * noise_transform.xyz;
		#endif
		normal = normalize(s_modelview[2].xyz);
		tangent = -normalize(s_modelview[0].xyz);
		binormal = -normalize(s_modelview[1].xyz);
		#ifdef LEAF_SHADOW
			binormal = -binormal;
		#endif
		#ifdef ANIMATION
			float leaf_sin,leaf_cos;
			float leaf_time = dot(position.xyz,s_material_animation_leaf.x) + s_material_animation_leaf.z;
			float leaf_angle = sin(leaf_time) * s_material_animation_leaf.y;
			sincos(leaf_angle,leaf_sin,leaf_cos);
			float3 leaf_tangent = tangent;
			float3 leaf_binormal = binormal;
			tangent = leaf_tangent * leaf_cos - leaf_binormal * leaf_sin;
			binormal = leaf_tangent * leaf_sin + leaf_binormal * leaf_cos;
		#endif
		vertex.xyz -= tangent * IN.texcoord_0.z * abs(row_2.z);
		vertex.xyz += binormal * IN.texcoord_0.w * abs(row_2.z);
		#ifdef LEAF_SHADOW
			vertex.xyz += normal * shadow_offset;
		#endif
	#else
		#ifdef NOISE
			OUT.texcoord_6 = vertex.xyz * noise_transform.xyz;
		#endif
	#endif
	
	float4 texcoord = IN.texcoord_0;
	texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
	
	#ifdef ANIMATION
		float2 stem_center = float2(row_0.w,row_1.w);
		float stem_scale = max(position.z * s_material_animation_stem.y,0.0f);
		float stem_angle = dot(stem_center,s_material_animation_stem.x) + s_material_animation_stem.w;
		float2 stem_offset = getAnimationOffset(stem_angle) * (stem_scale * stem_scale);
		vertex.z += dot(stem_offset,stem_center - vertex.xy) * s_material_animation_stem.z;
		vertex.xy += stem_offset;
		#ifdef LEAFS_GEOMETRY
			float leaf_scale = dot(texcoord.zw,1.0f);
			float leaf_time = dot(position.xyz,s_material_animation_leaf.x) + s_material_animation_leaf.z;
			vertex.z += sin(leaf_time) * leaf_scale * s_material_animation_leaf.y;
		#endif
	#endif
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
		bound_sphere.xyz = float3(dot(row_0,bound_sphere),dot(row_1,bound_sphere),dot(row_2,bound_sphere));
		bound_sphere.w = s_surface_bound_sphere.w * length(float3(row_0.x,row_1.x,row_2.x));
	#endif
	
	#include <core/shaders/meshes/vertex_base.h>
	
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
	float1 texcoord_3 : ATTR4;
};

uniform float4 s_instances[96];

uniform float4 base_transform;

uniform float4 noise_transform;
uniform float shadow_offset;

/*
 */
VERTEX_OUT main(VERTEX_IN IN) {
	
	VERTEX_OUT OUT;
	
	float4 row_0,row_1,row_2;
	
	#ifdef USE_INSTANCING
		int3 instance = int(IN.texcoord_3.x * 3.0f) + int3(0,1,2);
		row_0 = s_instances[instance.x];
		row_1 = s_instances[instance.y];
		row_2 = s_instances[instance.z];
	#else
		row_0 = s_transform[0];
		row_1 = s_transform[1];
		row_2 = s_transform[2];
	#endif
	
	float4 position = float4(IN.position.x,IN.position.y,IN.texcoord_1.w,1.0f);
	float4 vertex = float4(dot(row_0,position),dot(row_1,position),dot(row_2,position),1.0f);
	
	float3 normal = normalize(float3(dot(row_0.xyz,IN.texcoord_1.xyz),dot(row_1.xyz,IN.texcoord_1.xyz),dot(row_2.xyz,IN.texcoord_1.xyz)));
	float3 tangent = normalize(float3(dot(row_0.xyz,IN.texcoord_2.xyz),dot(row_1.xyz,IN.texcoord_2.xyz),dot(row_2.xyz,IN.texcoord_2.xyz)));
	float3 binormal = normalize(cross(normal,tangent) * IN.texcoord_2.w);
	
	#ifdef LEAFS_BILLBOARD
		#ifdef NOISE
			float3 noise = vertex.xyz;
			noise -= tangent * IN.texcoord_0.z;
			noise += binormal * IN.texcoord_0.w;
			OUT.texcoord_8 = noise * noise_transform.xyz;
		#endif
		normal = normalize(s_modelview[2].xyz);
		tangent = -normalize(s_modelview[0].xyz);
		binormal = -normalize(s_modelview[1].xyz);
		#ifdef LEAF_SHADOW
			binormal = -binormal;
		#endif
		#ifdef ANIMATION
			float leaf_sin,leaf_cos;
			float leaf_time = dot(position.xyz,s_material_animation_leaf.x) + s_material_animation_leaf.z;
			float leaf_angle = sin(leaf_time) * s_material_animation_leaf.y;
			sincos(leaf_angle,leaf_sin,leaf_cos);
			float3 leaf_tangent = tangent;
			float3 leaf_binormal = binormal;
			tangent = leaf_tangent * leaf_cos - leaf_binormal * leaf_sin;
			binormal = leaf_tangent * leaf_sin + leaf_binormal * leaf_cos;
		#endif
		vertex.xyz -= tangent * IN.texcoord_0.z * abs(row_2.z);
		vertex.xyz += binormal * IN.texcoord_0.w * abs(row_2.z);
		#ifdef LEAF_SHADOW
			vertex.xyz += normal * shadow_offset;
		#endif
	#else
		#ifdef NOISE
			OUT.texcoord_8 = vertex.xyz * noise_transform.xyz;
		#endif
	#endif
	
	float4 texcoord = IN.texcoord_0;
	texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
	
	#ifdef ANIMATION
		float2 stem_center = float2(row_0.w,row_1.w);
		float stem_scale = max(position.z * s_material_animation_stem.y,0.0f);
		float stem_angle = dot(stem_center,s_material_animation_stem.x) + s_material_animation_stem.w;
		float2 stem_offset = getAnimationOffset(stem_angle) * (stem_scale * stem_scale);
		vertex.z += dot(stem_offset,stem_center - vertex.xy) * s_material_animation_stem.z;
		vertex.xy += stem_offset;
		#ifdef LEAFS_GEOMETRY
			float leaf_scale = dot(texcoord.zw,1.0f);
			float leaf_time = dot(position.xyz,s_material_animation_leaf.x) + s_material_animation_leaf.z;
			vertex.z += sin(leaf_time) * leaf_scale * s_material_animation_leaf.y;
		#endif
	#endif
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
		bound_sphere.xyz = float3(dot(row_0,bound_sphere),dot(row_1,bound_sphere),dot(row_2,bound_sphere));
		bound_sphere.w = s_surface_bound_sphere.w * length(float3(row_0.x,row_1.x,row_2.x));
	#endif
	
	#include <core/shaders/meshes/vertex_base.h>
	
	return OUT;
}

#endif
