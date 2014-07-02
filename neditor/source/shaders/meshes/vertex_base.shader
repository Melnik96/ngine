/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base.shader
 * Desc:    Mesh base shader
 * Version: 1.27
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

#ifdef MESH_SKINNED && !USE_TRANSFORMING
	
	attribute float4 s_attribute_0;
	attribute float4 s_attribute_1;
	attribute float4 s_attribute_2;
	attribute float4 s_attribute_3;
	attribute float4 s_attribute_4;
	attribute float4 s_attribute_5;
	attribute float s_attribute_6;
	
	attribute float4 s_attribute_13;
	attribute float4 s_attribute_14;
	attribute float4 s_attribute_15;
	
	uniform sampler2D s_texture_16;
	
	uniform float s_mesh_num_bones;
	
	UNIFORM_BUFFER_BEGIN(shader_mesh_bones_parameters)
		uniform float4 s_mesh_bones[192];
	UNIFORM_BUFFER_END
	
	UNIFORM_BUFFER_BEGIN(shader_instances_parameters)
		uniform float4 s_instances[24];
	UNIFORM_BUFFER_END
	
	uniform float4 base_transform;
	
	/*
	 */
	void main() {
		
		float4 weights = s_attribute_2;
		
		#ifdef USE_INSTANCING
			#ifdef HAS_ARB_DRAW_INSTANCED
				int4 bones = int4(s_attribute_1) + gl_InstanceID * int(s_mesh_num_bones);
			#else
				int4 bones = int4(s_attribute_1 + s_attribute_6 * s_mesh_num_bones);
			#endif
		#else
			int4 bones = int4(s_attribute_1);
		#endif
		
		#ifdef USE_DUAL_QUATERNIONS
			
			float4 q0 = s_mesh_bones[bones.x];
			float4 q1 = s_mesh_bones[bones.x + 1] * weights.x;
			float len = length(q0);
			float scale = len * weights.x;
			q0 *= (weights.x / len);
			
			#define SKINNING(SWIZZLE) { \
				float4 q2 = s_mesh_bones[bones.SWIZZLE]; \
				float4 q3 = s_mesh_bones[bones.SWIZZLE + 1]; \
				float weight = sign(dot(q0,q2)) * weights.SWIZZLE; \
				float len = length(q2); \
				scale += len * weights.SWIZZLE; \
				q0 += q2 * (weight / len); \
				q1 += q3 * weight; \
			}
			
			SKINNING(y)
			
			#ifdef QUALITY_MEDIUM
				SKINNING(z)
				SKINNING(w)
			#else
				scale = scale / (weights.x + weights.y);
			#endif
			
			float4 q2 = q0 * (2.0f / dot(q0,q0));
			q0 *= scale;
			
			float4 qq0 = q0 * q2 * 0.5f;
			float3 q0x = q0.xxx * q2.yzw;
			float3 q0y = q0.yyz * q2.zww;
			float3 q1x = q1.xxx * q2.wzy;
			float3 q1y = q1.yyy * q2.zwx;
			float3 q1z = q1.zzz * q2.yxw;
			float3 q1w = q1.www * q2.xyz;
			
			float4 row_0 = float4(qq0.w + qq0.x - qq0.y - qq0.z,q0x.x - q0y.z,q0x.y + q0y.y,q1w.x + q1x.x - q1y.x + q1z.x);
			float4 row_1 = float4(q0x.x + q0y.z,qq0.w + qq0.y - qq0.x - qq0.z,q0y.x - q0x.z,q1w.y + q1x.y + q1y.y - q1z.y);
			float4 row_2 = float4(q0x.y - q0y.y,q0x.z + q0y.x,qq0.w + qq0.z - qq0.x - qq0.y,q1w.z - q1x.z + q1y.z + q1z.z);
			
		#else
			
			float4 row_0,row_1,row_2;
			
			#define SKINNING(SWIZZLE,OP) { \
				float4 xyz = s_mesh_bones[bones.SWIZZLE] * weights.SWIZZLE; \
				float4 rot = s_mesh_bones[bones.SWIZZLE + 1]; \
				float3 q0 = rot.xyz * (xyz.w * 2.0f); \
				float2 qx = rot.xw * q0.x; \
				float3 qy = rot.xyw * q0.y; \
				float4 qz = rot.xyzw * q0.z; \
				row_0 OP float4(xyz.w - (qy.y + qz.z),qy.x - qz.w,qz.x + qy.z,xyz.x); \
				row_1 OP float4(qy.x + qz.w,xyz.w - (qx.x + qz.z),qz.y - qx.y,xyz.y); \
				row_2 OP float4(qz.x - qy.z,qz.y + qx.y,xyz.w - (qx.x + qy.y),xyz.z); \
			}
			
			SKINNING(x,=)
			SKINNING(y,+=)
			
			#ifdef QUALITY_MEDIUM
				SKINNING(z,+=)
				SKINNING(w,+=)
			#else
				float iscale = 1.0f / (weights.x + weights.y);
				row_0 *= iscale;
				row_1 *= iscale;
				row_2 *= iscale;
			#endif
			
		#endif
		
		float4 position = float4(s_attribute_0.x,s_attribute_0.y,s_attribute_4.w,1.0f);
		float4 vertex = float4(dot(row_0,position),dot(row_1,position),dot(row_2,position),1.0f);
		
		float3 normal = float3(dot(row_0.xyz,s_attribute_4.xyz),dot(row_1.xyz,s_attribute_4.xyz),dot(row_2.xyz,s_attribute_4.xyz));
		float3 tangent = float3(dot(row_0.xyz,s_attribute_5.xyz),dot(row_1.xyz,s_attribute_5.xyz),dot(row_2.xyz,s_attribute_5.xyz));
		
		#ifdef USE_INSTANCING
			#ifdef HAS_ARB_DRAW_INSTANCED
				int3 instance = int3(gl_InstanceID * 3) + int3(0,1,2);
			#elif USE_PSEUDO_INSTANCING
				int3 instance = int3(s_attribute_6 * 3.0f) + int3(0,1,2);
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
		
		vertex.xyz = float3(dot(vertex,row_0),dot(vertex,row_1),dot(vertex,row_2));
		
		normal = normalize(float3(dot(row_0.xyz,normal),dot(row_1.xyz,normal),dot(row_2.xyz,normal)));
		tangent = normalize(float3(dot(row_0.xyz,tangent),dot(row_1.xyz,tangent),dot(row_2.xyz,tangent)));
		float3 binormal = cross(normal,tangent) * s_attribute_5.w;
		float orientation = s_attribute_5.w;
		
		float4 texcoord = s_attribute_3;
		texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
		
		#ifdef USE_TESSELLATION && TESSELLATION
			float factor = pow(saturate(1.0f - (length(vertex.xyz - s_camera_position) - s_material_tessellation_distance.x) * s_material_tessellation_distance.y),s_material_tessellation_factor.w);
			factor *= texture2D(s_texture_16,texcoord.xy).x * s_material_tessellation_factor.z;
			gl_TexCoord[7] = float4(normal,clamp(factor,1.0f,15.0f) * 0.5f);
		#endif
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
			bound_sphere.xyz = float3(dot(row_0,bound_sphere),dot(row_1,bound_sphere),dot(row_2,bound_sphere));
			bound_sphere.w = s_surface_bound_sphere.w * length(float3(row_0.x,row_1.x,row_2.x));
		#endif
		
		#include <core/shaders/meshes/vertex_base.h>
	}
	
#else
	
	attribute float4 s_attribute_0;
	attribute float4 s_attribute_1;
	attribute float4 s_attribute_2;
	attribute float4 s_attribute_3;
	attribute float s_attribute_4;
	
	attribute float4 s_attribute_13;
	attribute float4 s_attribute_14;
	attribute float4 s_attribute_15;
	
	uniform sampler2D s_texture_16;
	
	UNIFORM_BUFFER_BEGIN(shader_instances_parameters)
		uniform float4 s_instances[96];
	UNIFORM_BUFFER_END
	
	uniform float4 base_transform;
	
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
		float3 binormal = cross(normal,tangent) * s_attribute_3.w;
		float orientation = s_attribute_3.w;
		
		float4 texcoord = s_attribute_1;
		texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
		
		#ifdef USE_TESSELLATION && TESSELLATION
			float factor = pow(saturate(1.0f - (length(vertex.xyz - s_camera_position) - s_material_tessellation_distance.x) * s_material_tessellation_distance.y),s_material_tessellation_factor.w);
			factor *= texture2D(s_texture_16,texcoord.xy).x * s_material_tessellation_factor.z;
			gl_TexCoord[7] = float4(normal,clamp(factor,1.0f,15.0f) * 0.5f);
		#endif
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
			bound_sphere.xyz = float3(dot(row_0,bound_sphere),dot(row_1,bound_sphere),dot(row_2,bound_sphere));
			bound_sphere.w = s_surface_bound_sphere.w * length(float3(row_0.x,row_1.x,row_2.x));
		#endif
		
		#include <core/shaders/meshes/vertex_base.h>
	}
	
#endif

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

#ifdef MESH_SKINNED && !USE_TRANSFORMING
	
	struct VERTEX_IN {
		float4 position : POSITION;
		float4 texcoord_0 : TEXCOORD0;
		float4 texcoord_1 : TEXCOORD1;
		float4 texcoord_2 : TEXCOORD2;
		float4 texcoord_3 : TEXCOORD3;
		float4 texcoord_4 : TEXCOORD4;
		float1 texcoord_5 : TEXCOORD5;
	};
	
	float s_mesh_num_bones;
	float4 s_mesh_bones[192];
	
	float4 s_instances[24];
	
	float4 base_transform;
	
	/*
	 */
	VERTEX_OUT main(VERTEX_IN IN) {
		
		VERTEX_OUT OUT;
		
		float4 weights = IN.texcoord_1;
		
		#ifdef USE_INSTANCING
			int4 bones = int4(IN.texcoord_0 + IN.texcoord_5 * s_mesh_num_bones);
		#else
			int4 bones = int4(IN.texcoord_0);
		#endif
		
		#ifdef USE_DUAL_QUATERNIONS
			
			float4 q0 = s_mesh_bones[bones.x];
			float4 q1 = s_mesh_bones[bones.x + 1] * weights.x;
			float len = length(q0);
			float scale = len * weights.x;
			q0 *= (weights.x / len);
			
			#define SKINNING(SWIZZLE) { \
				float4 q2 = s_mesh_bones[bones.SWIZZLE]; \
				float4 q3 = s_mesh_bones[bones.SWIZZLE + 1]; \
				float weight = sign(dot(q0,q2)) * weights.SWIZZLE; \
				float len = length(q2); \
				scale += len * weights.SWIZZLE; \
				q0 += q2 * (weight / len); \
				q1 += q3 * weight; \
			}
			
			SKINNING(y)
			
			#ifdef QUALITY_MEDIUM
				SKINNING(z)
				SKINNING(w)
			#else
				scale = scale / (weights.x + weights.y);
			#endif
			
			float4 q2 = q0 * (2.0f / dot(q0,q0));
			q0 *= scale;
			
			float4 qq0 = q0 * q2 * 0.5f;
			float3 q0x = q0.xxx * q2.yzw;
			float3 q0y = q0.yyz * q2.zww;
			float3 q1x = q1.xxx * q2.wzy;
			float3 q1y = q1.yyy * q2.zwx;
			float3 q1z = q1.zzz * q2.yxw;
			float3 q1w = q1.www * q2.xyz;
			
			float4 row_0 = float4(qq0.w + qq0.x - qq0.y - qq0.z,q0x.x - q0y.z,q0x.y + q0y.y,q1w.x + q1x.x - q1y.x + q1z.x);
			float4 row_1 = float4(q0x.x + q0y.z,qq0.w + qq0.y - qq0.x - qq0.z,q0y.x - q0x.z,q1w.y + q1x.y + q1y.y - q1z.y);
			float4 row_2 = float4(q0x.y - q0y.y,q0x.z + q0y.x,qq0.w + qq0.z - qq0.x - qq0.y,q1w.z - q1x.z + q1y.z + q1z.z);
			
		#else
			
			float4 row_0,row_1,row_2;
			
			#define SKINNING(SWIZZLE,OP) { \
				float4 xyz = s_mesh_bones[bones.SWIZZLE] * weights.SWIZZLE; \
				float4 rot = s_mesh_bones[bones.SWIZZLE + 1]; \
				float3 q0 = rot.xyz * (xyz.w * 2.0f); \
				float2 qx = rot.xw * q0.x; \
				float3 qy = rot.xyw * q0.y; \
				float4 qz = rot.xyzw * q0.z; \
				row_0 OP float4(xyz.w - (qy.y + qz.z),qy.x - qz.w,qz.x + qy.z,xyz.x); \
				row_1 OP float4(qy.x + qz.w,xyz.w - (qx.x + qz.z),qz.y - qx.y,xyz.y); \
				row_2 OP float4(qz.x - qy.z,qz.y + qx.y,xyz.w - (qx.x + qy.y),xyz.z); \
			}
			
			SKINNING(x,=)
			SKINNING(y,+=)
			
			#ifdef QUALITY_MEDIUM
				SKINNING(z,+=)
				SKINNING(w,+=)
			#else
				float iscale = 1.0f / (weights.x + weights.y);
				row_0 *= iscale;
				row_1 *= iscale;
				row_2 *= iscale;
			#endif
			
		#endif
		
		float4 position = float4(IN.position.x,IN.position.y,IN.texcoord_3.w,1.0f);
		float4 vertex = float4(dot(row_0,position),dot(row_1,position),dot(row_2,position),1.0f);
		
		float3 normal = float3(dot(IN.texcoord_3.xyz,row_0.xyz),dot(IN.texcoord_3.xyz,row_1.xyz),dot(IN.texcoord_3.xyz,row_2.xyz));
		float3 tangent = float3(dot(IN.texcoord_4.xyz,row_0.xyz),dot(IN.texcoord_4.xyz,row_1.xyz),dot(IN.texcoord_4.xyz,row_2.xyz));
		
		#ifdef USE_INSTANCING
			int3 instance = int(IN.texcoord_5 * 3.0f) + int3(0,1,2);
			row_0 = s_instances[instance.x];
			row_1 = s_instances[instance.y];
			row_2 = s_instances[instance.z];
		#else
			row_0 = s_transform[0];
			row_1 = s_transform[1];
			row_2 = s_transform[2];
		#endif
		
		vertex.xyz = float3(dot(vertex,row_0),dot(vertex,row_1),dot(vertex,row_2));
		
		normal = normalize(float3(dot(row_0.xyz,normal),dot(row_1.xyz,normal),dot(row_2.xyz,normal)));
		tangent = normalize(float3(dot(row_0.xyz,tangent),dot(row_1.xyz,tangent),dot(row_2.xyz,tangent)));
		float3 binormal = cross(normal,tangent) * IN.texcoord_4.w;
		
		float4 texcoord = IN.texcoord_2;
		texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
			bound_sphere.xyz = float3(dot(row_0,bound_sphere),dot(row_1,bound_sphere),dot(row_2,bound_sphere));
			bound_sphere.w = s_surface_bound_sphere.w * length(float3(row_0.x,row_1.x,row_2.x));
		#endif
		
		#include <core/shaders/meshes/vertex_base.h>
		
		return OUT;
	}
	
#else
	
	struct VERTEX_IN {
		float4 position : POSITION;
		float4 texcoord_0 : TEXCOORD0;
		float4 texcoord_1 : TEXCOORD1;
		float4 texcoord_2 : TEXCOORD2;
		float1 texcoord_3 : TEXCOORD3;
	};
	
	float4 s_instances[96];
	
	float4 base_transform;
	
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
		float3 binormal = cross(normal,tangent) * IN.texcoord_2.w;
		
		float4 texcoord = IN.texcoord_0;
		texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
			bound_sphere.xyz = float3(dot(row_0,bound_sphere),dot(row_1,bound_sphere),dot(row_2,bound_sphere));
			bound_sphere.w = s_surface_bound_sphere.w * length(float3(row_0.x,row_1.x,row_2.x));
		#endif
		
		#include <core/shaders/meshes/vertex_base.h>
		
		return OUT;
	}
	
#endif

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

#ifdef MESH_SKINNED && !USE_TRANSFORMING
	
	Texture2D s_texture_0 : register(t0);
	
	struct VERTEX_IN {
		float4 position : POSITION;
		float4 texcoord_0 : TEXCOORD0;
		float4 texcoord_1 : TEXCOORD1;
		float4 texcoord_2 : TEXCOORD2;
		float4 texcoord_3 : TEXCOORD3;
		float4 texcoord_4 : TEXCOORD4;
		uint instance : SV_INSTANCEID;
	};
	
	cbuffer shader_mesh_bones_parameters {
		float s_mesh_num_bones;
		float4 s_mesh_bones[192];
	};
	
	cbuffer shader_instances_parameters {
		float4 s_instances[96];
	};
	
	cbuffer shader_parameters {
		float4 base_transform;
	};
	
	/*
	 */
	VERTEX_OUT main(VERTEX_IN IN) {
		
		VERTEX_OUT OUT;
		
		float4 weights = IN.texcoord_1;
		
		#ifdef USE_INSTANCING
			int4 bones = int4(IN.texcoord_0) + IN.instance * (int)s_mesh_num_bones;
		#else
			int4 bones = int4(IN.texcoord_0);
		#endif
		
		#ifdef USE_DUAL_QUATERNIONS
			
			float4 q0 = s_mesh_bones[bones.x];
			float4 q1 = s_mesh_bones[bones.x + 1] * weights.x;
			float len = length(q0);
			float scale = len * weights.x;
			q0 *= (weights.x / len);
			
			#define SKINNING(SWIZZLE) { \
				float4 q2 = s_mesh_bones[bones.SWIZZLE]; \
				float4 q3 = s_mesh_bones[bones.SWIZZLE + 1]; \
				float weight = sign(dot(q0,q2)) * weights.SWIZZLE; \
				float len = length(q2); \
				scale += len * weights.SWIZZLE; \
				q0 += q2 * (weight / len); \
				q1 += q3 * weight; \
			}
			
			SKINNING(y)
			
			#ifdef QUALITY_MEDIUM
				SKINNING(z)
				SKINNING(w)
			#else
				scale = scale / (weights.x + weights.y);
			#endif
			
			float4 q2 = q0 * (2.0f / dot(q0,q0));
			q0 *= scale;
			
			float4 qq0 = q0 * q2 * 0.5f;
			float3 q0x = q0.xxx * q2.yzw;
			float3 q0y = q0.yyz * q2.zww;
			float3 q1x = q1.xxx * q2.wzy;
			float3 q1y = q1.yyy * q2.zwx;
			float3 q1z = q1.zzz * q2.yxw;
			float3 q1w = q1.www * q2.xyz;
			
			float4 row_0 = float4(qq0.w + qq0.x - qq0.y - qq0.z,q0x.x - q0y.z,q0x.y + q0y.y,q1w.x + q1x.x - q1y.x + q1z.x);
			float4 row_1 = float4(q0x.x + q0y.z,qq0.w + qq0.y - qq0.x - qq0.z,q0y.x - q0x.z,q1w.y + q1x.y + q1y.y - q1z.y);
			float4 row_2 = float4(q0x.y - q0y.y,q0x.z + q0y.x,qq0.w + qq0.z - qq0.x - qq0.y,q1w.z - q1x.z + q1y.z + q1z.z);
			
		#else
			
			float4 row_0,row_1,row_2;
			
			#define SKINNING(SWIZZLE,OP) { \
				float4 xyz = s_mesh_bones[bones.SWIZZLE] * weights.SWIZZLE; \
				float4 rot = s_mesh_bones[bones.SWIZZLE + 1]; \
				float3 q0 = rot.xyz * (xyz.w * 2.0f); \
				float2 qx = rot.xw * q0.x; \
				float3 qy = rot.xyw * q0.y; \
				float4 qz = rot.xyzw * q0.z; \
				row_0 OP float4(xyz.w - (qy.y + qz.z),qy.x - qz.w,qz.x + qy.z,xyz.x); \
				row_1 OP float4(qy.x + qz.w,xyz.w - (qx.x + qz.z),qz.y - qx.y,xyz.y); \
				row_2 OP float4(qz.x - qy.z,qz.y + qx.y,xyz.w - (qx.x + qy.y),xyz.z); \
			}
			
			SKINNING(x,=)
			SKINNING(y,+=)
			
			#ifdef QUALITY_MEDIUM
				SKINNING(z,+=)
				SKINNING(w,+=)
			#else
				float iscale = 1.0f / (weights.x + weights.y);
				row_0 *= iscale;
				row_1 *= iscale;
				row_2 *= iscale;
			#endif
			
		#endif
		
		float4 position = float4(IN.position.x,IN.position.y,IN.texcoord_3.w,1.0f);
		float4 vertex = float4(dot(row_0,position),dot(row_1,position),dot(row_2,position),1.0f);
		
		float3 normal = float3(dot(IN.texcoord_3.xyz,row_0.xyz),dot(IN.texcoord_3.xyz,row_1.xyz),dot(IN.texcoord_3.xyz,row_2.xyz));
		float3 tangent = float3(dot(IN.texcoord_4.xyz,row_0.xyz),dot(IN.texcoord_4.xyz,row_1.xyz),dot(IN.texcoord_4.xyz,row_2.xyz));
		
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
		
		vertex.xyz = float3(dot(vertex,row_0),dot(vertex,row_1),dot(vertex,row_2));
		
		normal = normalize(float3(dot(row_0.xyz,normal),dot(row_1.xyz,normal),dot(row_2.xyz,normal)));
		tangent = normalize(float3(dot(row_0.xyz,tangent),dot(row_1.xyz,tangent),dot(row_2.xyz,tangent)));
		float3 binormal = cross(normal,tangent) * IN.texcoord_4.w;
		float orientation = IN.texcoord_4.w;
		
		float4 texcoord = IN.texcoord_2;
		texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
		
		#ifdef USE_TESSELLATION && TESSELLATION
			float factor = pow(saturate(1.0f - (length(vertex.xyz - s_camera_position) - s_material_tessellation_distance.x) * s_material_tessellation_distance.y),s_material_tessellation_factor.w);
			factor *= s_texture_0.SampleLevel(s_sampler_0,texcoord.xy,0.0f).x * s_material_tessellation_factor.z;
			OUT.texcoord_9 = float4(normal,clamp(factor,1.0f,15.0f) * 0.5f);
		#endif
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
			bound_sphere.xyz = float3(dot(row_0,bound_sphere),dot(row_1,bound_sphere),dot(row_2,bound_sphere));
			bound_sphere.w = s_surface_bound_sphere.w * length(float3(row_0.x,row_1.x,row_2.x));
		#endif
		
		#include <core/shaders/meshes/vertex_base.h>
		
		return OUT;
	}
	
#else
	
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
		float3 binormal = cross(normal,tangent) * IN.texcoord_2.w;
		float orientation = IN.texcoord_2.w;
		
		float4 texcoord = IN.texcoord_0;
		texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
		
		#ifdef USE_TESSELLATION && TESSELLATION
			float factor = pow(saturate(1.0f - (length(vertex.xyz - s_camera_position) - s_material_tessellation_distance.x) * s_material_tessellation_distance.y),s_material_tessellation_factor.w);
			factor *= s_texture_0.SampleLevel(s_sampler_0,texcoord.xy,0.0f).x * s_material_tessellation_factor.z;
			OUT.texcoord_9 = float4(normal,clamp(factor,1.0f,15.0f) * 0.5f);
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
	float3 binormal = cross(normal,tangent) * IN.texcoord_2.w;
	
	float4 texcoord = IN.texcoord_0;
	texcoord.xy = texcoord.xy * base_transform.xy + base_transform.zw;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
		bound_sphere.xyz = float3(dot(row_0,bound_sphere),dot(row_1,bound_sphere),dot(row_2,bound_sphere));
		bound_sphere.w = s_surface_bound_sphere.w * length(float3(row_0.x,row_1.x,row_2.x));
	#endif
	
	#include <core/shaders/meshes/vertex_base.h>
	
	return OUT;
}

#endif
