/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base_deferred.h
 * Desc:    Base deferred shader
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

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL
	
	#ifndef VERTEX_BASE_DEFERRED
		#define VERTEX_BASE_DEFERRED
		
		#ifdef USE_PARALLAX && PARALLAX
			uniform float parallax_scale;
		#endif
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0] = texcoord;
		
		#ifdef USE_TESSELLATION && TESSELLATION
			
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				gl_Position.w = getAlphaFade(bound_sphere);
			#endif
			
			#ifdef USE_DEFERRED || USE_OCCLUSION
				float3x3 transform = float3x3(s_modelview[0].xyz,s_modelview[1].xyz,s_modelview[2].xyz) * float3x3(tangent,binormal,normal);
				gl_TexCoord[1].xyz = float3(transform[0].x,transform[1].x,transform[2].x);
				gl_TexCoord[2].xyz = float3(transform[0].y,transform[1].y,transform[2].y);
				gl_TexCoord[3].xyz = float3(transform[0].z,transform[1].z,transform[2].z);
			#endif
			
		#else
			
			gl_TexCoord[1].xyz = (vertex.xyz - s_camera_position) / s_depth_range.y;
			
			#ifdef USE_DEFERRED || USE_OCCLUSION
				float3x3 transform = float3x3(s_modelview[0].xyz,s_modelview[1].xyz,s_modelview[2].xyz) * float3x3(tangent,binormal,normal);
				gl_TexCoord[2].xyz = float3(transform[0].x,transform[1].x,transform[2].x);
				gl_TexCoord[3].xyz = float3(transform[0].y,transform[1].y,transform[2].y);
				gl_TexCoord[4].xyz = float3(transform[0].z,transform[1].z,transform[2].z);
			#endif
			
			#ifdef USE_PARALLAX && PARALLAX
				float3 camera_direction = s_camera_position - vertex.xyz;
				gl_TexCoord[5].x = dot(camera_direction,tangent);
				gl_TexCoord[5].y = dot(camera_direction,binormal);
				gl_TexCoord[5].z = dot(camera_direction,normal);
				
				float aspect = s_material_textures[10].x * s_material_textures[10].w;
				if(aspect > 1.0f) gl_TexCoord[6].xy = float2(parallax_scale / aspect,parallax_scale);
				else gl_TexCoord[6].xy = float2(parallax_scale,parallax_scale * aspect);
			#endif
			
			#ifdef PATCH
				gl_TexCoord[6].xy = patch_parameters;
			#endif
			
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				gl_TexCoord[7] = getProjection(gl_Position);
				gl_TexCoord[7].z = getAlphaFade(bound_sphere);
			#endif
			
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_BASE_DEFERRED
		#define VERTEX_BASE_DEFERRED
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			#ifdef USE_DEFERRED || USE_OCCLUSION
				float3 texcoord_2 : TEXCOORD2;
				float3 texcoord_3 : TEXCOORD3;
				float3 texcoord_4 : TEXCOORD4;
			#endif
			#ifdef USE_PARALLAX && PARALLAX
				float3 texcoord_5 : TEXCOORD5;
				float2 texcoord_6 : TEXCOORD6;
			#endif
			#ifdef PATCH
				float2 texcoord_6 : TEXCOORD6;
			#endif
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				float4 texcoord_7 : TEXCOORD7;
			#endif
		};
		
		#ifdef USE_PARALLAX && PARALLAX
			float parallax_scale;
		#endif
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = (vertex.xyz - s_camera_position) / s_depth_range.y;
		
		#ifdef USE_DEFERRED || USE_OCCLUSION
			float3x3 transform = mul((float3x3)s_modelview,transpose(float3x3(tangent,binormal,normal)));
			OUT.texcoord_2 = transform[0].xyz;
			OUT.texcoord_3 = transform[1].xyz;
			OUT.texcoord_4 = transform[2].xyz;
		#endif
		
		#ifdef USE_PARALLAX && PARALLAX
			float3 camera_direction = s_camera_position - vertex.xyz;
			OUT.texcoord_5.x = dot(camera_direction,tangent);
			OUT.texcoord_5.y = dot(camera_direction,binormal);
			OUT.texcoord_5.z = dot(camera_direction,normal);
			
			float aspect = s_material_textures[10].x * s_material_textures[10].w;
			if(aspect > 1.0f) OUT.texcoord_6 = float2(parallax_scale / aspect,parallax_scale);
			else OUT.texcoord_6 = float2(parallax_scale,parallax_scale * aspect);
		#endif
		
		#ifdef PATCH
			OUT.texcoord_6 = patch_parameters;
		#endif
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			OUT.texcoord_7 = getProjection(OUT.position);
			OUT.texcoord_7.z = getAlphaFade(bound_sphere);
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_BASE_DEFERRED
		#define VERTEX_BASE_DEFERRED
		
		struct VERTEX_OUT {
			float4 position : OUT_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			#ifdef USE_TESSELLATION && TESSELLATION
				#ifdef USE_DEFERRED || USE_OCCLUSION
					float3 texcoord_1 : TEXCOORD1;
					float3 texcoord_2 : TEXCOORD2;
					float3 texcoord_3 : TEXCOORD3;
				#endif
				float4 texcoord_9 : TEXCOORD9;
			#else
				float3 texcoord_1 : TEXCOORD1;
				#ifdef USE_DEFERRED || USE_OCCLUSION
					float3 texcoord_2 : TEXCOORD2;
					float3 texcoord_3 : TEXCOORD3;
					float3 texcoord_4 : TEXCOORD4;
				#endif
				#ifdef USE_PARALLAX && PARALLAX
					float3 texcoord_5 : TEXCOORD5;
					float2 texcoord_6 : TEXCOORD6;
				#endif
				#ifdef PATCH
					float2 texcoord_6 : TEXCOORD6;
				#endif
				#ifdef USE_ALPHA_FADE && ALPHA_FADE
					float1 texcoord_9 : TEXCOORD9;
				#endif
			#endif
		};
		
		#ifdef USE_PARALLAX && PARALLAX
			cbuffer shader_deferred_parameters {
				float parallax_scale;
			};
		#endif
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		#ifdef USE_TESSELLATION && TESSELLATION
			
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				OUT.position.w = getAlphaFade(bound_sphere);
			#endif
			
			#ifdef USE_DEFERRED || USE_OCCLUSION
				float3x3 transform = mul((float3x3)s_modelview,transpose(float3x3(tangent,binormal,normal)));
				OUT.texcoord_1 = transform[0].xyz;
				OUT.texcoord_2 = transform[1].xyz;
				OUT.texcoord_3 = transform[2].xyz;
			#endif
			
		#else
			
			OUT.texcoord_1 = (vertex.xyz - s_camera_position) / s_depth_range.y;
			
			#ifdef USE_DEFERRED || USE_OCCLUSION
				float3x3 transform = mul((float3x3)s_modelview,transpose(float3x3(tangent,binormal,normal)));
				OUT.texcoord_2 = transform[0].xyz;
				OUT.texcoord_3 = transform[1].xyz;
				OUT.texcoord_4 = transform[2].xyz;
			#endif
			
			#ifdef USE_PARALLAX && PARALLAX
				float3 camera_direction = s_camera_position - vertex.xyz;
				OUT.texcoord_5.x = dot(camera_direction,tangent);
				OUT.texcoord_5.y = dot(camera_direction,binormal);
				OUT.texcoord_5.z = dot(camera_direction,normal);
				
				float aspect = s_material_textures[10].x * s_material_textures[10].w;
				if(aspect > 1.0f) OUT.texcoord_6 = float2(parallax_scale / aspect,parallax_scale);
				else OUT.texcoord_6 = float2(parallax_scale,parallax_scale * aspect);
			#endif
			
			#ifdef PATCH
				OUT.texcoord_6 = patch_parameters;
			#endif
			
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				OUT.texcoord_9.x = getAlphaFade(bound_sphere);
			#endif
			
		#endif
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_BASE_DEFERRED
		#define VERTEX_BASE_DEFERRED
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			#ifdef USE_DEFERRED || USE_OCCLUSION
				float3 texcoord_2 : TEXCOORD2;
				float3 texcoord_3 : TEXCOORD3;
				float3 texcoord_4 : TEXCOORD4;
			#endif
			#ifdef USE_PARALLAX && PARALLAX
				float3 texcoord_5 : TEXCOORD5;
				float2 texcoord_6 : TEXCOORD6;
			#endif
			#ifdef PATCH
				float2 texcoord_8 : TEXCOORD8;
			#endif
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				float4 texcoord_9 : TEXCOORD9;
			#endif
		};
		
		#ifdef USE_PARALLAX && PARALLAX
			uniform float parallax_scale;
		#endif
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = (vertex.xyz - s_camera_position) / s_depth_range.y;
		
		#ifdef USE_DEFERRED || USE_OCCLUSION
			float3x3 transform = mul((float3x3)s_modelview,transpose(float3x3(tangent,binormal,normal)));
			OUT.texcoord_2 = transform[0].xyz;
			OUT.texcoord_3 = transform[1].xyz;
			OUT.texcoord_4 = transform[2].xyz;
		#endif
		
		#ifdef USE_PARALLAX && PARALLAX
			float3 camera_direction = s_camera_position - vertex.xyz;
			OUT.texcoord_5.x = dot(camera_direction,tangent);
			OUT.texcoord_5.y = dot(camera_direction,binormal);
			OUT.texcoord_5.z = dot(camera_direction,normal);
			
			float aspect = s_material_textures[10].x * s_material_textures[10].w;
			if(aspect > 1.0f) OUT.texcoord_6 = float2(parallax_scale / aspect,parallax_scale);
			else OUT.texcoord_6 = float2(parallax_scale,parallax_scale * aspect);
		#endif
		
		#ifdef PATCH
			OUT.texcoord_8 = patch_parameters;
		#endif
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			OUT.texcoord_9 = getProjection(OUT.position);
			OUT.texcoord_9.z = getAlphaFade(bound_sphere);
		#endif
		
	#endif
	
#endif
