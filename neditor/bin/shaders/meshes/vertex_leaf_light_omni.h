/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_leaf_light_omni.h
 * Desc:    Mesh leaf light omni shader
 * Version: 1.11
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
	
	#ifndef VERTEX_LEAF_LIGHT_OMNI
		#define VERTEX_LEAF_LIGHT_OMNI
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0] = texcoord;
		
		float3 light_direction = getOmniRadius(s_light_position - vertex.xyz) * s_light_iradius.w;
		gl_TexCoord[1].x = dot(light_direction,tangent);
		gl_TexCoord[1].y = dot(light_direction,binormal);
		gl_TexCoord[1].z = dot(light_direction,normal) * s_light_front;
		gl_TexCoord[1].w = s_light_iradius.w * s_light_iradius.w;
		
		#ifdef PHONG
			float3 camera_direction = s_camera_position - vertex.xyz;
			gl_TexCoord[2].x = dot(camera_direction,tangent);
			gl_TexCoord[2].y = dot(camera_direction,binormal);
			gl_TexCoord[2].z = dot(camera_direction,normal) * s_light_front;
		#endif
		
		gl_TexCoord[3] = float4(vertex.xyz - s_light_position,0.0f) * s_light_transform;
		
		#ifdef SHADOW
			gl_TexCoord[4].xyz = (vertex.xyz - s_light_shadow_offset) * s_light_shadow_depth_range.x;
			gl_TexCoord[4].w = s_light_shadow_depth_range.y;
			#ifdef USE_TRANSLUCENT
				gl_TexCoord[5].xyz = (vertex.xyz - s_light_shadow_offset) * s_light_shadow_iradius.x;
			#endif
		#endif
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			gl_TexCoord[7].x = getAlphaFadeScale(bound_sphere);
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_LEAF_LIGHT_OMNI
		#define VERTEX_LEAF_LIGHT_OMNI
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef PHONG
				float3 texcoord_2 : TEXCOORD2;
			#endif
			float3 texcoord_3 : TEXCOORD3;
			#ifdef SHADOW
				float4 texcoord_4 : TEXCOORD4;
				#ifdef USE_TRANSLUCENT
					float3 texcoord_5 : TEXCOORD5;
				#endif
			#endif
			#ifdef NOISE
				float3 texcoord_6 : TEXCOORD6;
			#endif
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				float1 texcoord_7 : TEXCOORD7;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		float3 light_direction = getOmniRadius(s_light_position - vertex.xyz) * s_light_iradius.w;
		OUT.texcoord_1.x = dot(light_direction,tangent);
		OUT.texcoord_1.y = dot(light_direction,binormal);
		OUT.texcoord_1.z = dot(light_direction,normal) * s_light_front;
		OUT.texcoord_1.w = s_light_iradius.w * s_light_iradius.w;
		
		#ifdef PHONG
			float3 camera_direction = s_camera_position - vertex.xyz;
			OUT.texcoord_2.x = dot(camera_direction,tangent);
			OUT.texcoord_2.y = dot(camera_direction,binormal);
			OUT.texcoord_2.z = dot(camera_direction,normal) * s_light_front;
		#endif
		
		OUT.texcoord_3 = mul(vertex.xyz - s_light_position,(float3x3)s_light_transform);
		
		#ifdef SHADOW
			OUT.texcoord_4.xyz = (vertex.xyz - s_light_shadow_offset) * s_light_shadow_depth_range.x;
			OUT.texcoord_4.w = s_light_shadow_depth_range.y;
			#ifdef USE_TRANSLUCENT
				OUT.texcoord_5 = (vertex.xyz - s_light_shadow_offset) * s_light_shadow_iradius.x;
			#endif
		#endif
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			OUT.texcoord_7.x = getAlphaFadeScale(bound_sphere);
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_LEAF_LIGHT_OMNI
		#define VERTEX_LEAF_LIGHT_OMNI
		
		struct VERTEX_OUT {
			float4 position : OUT_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef PHONG
				float3 texcoord_2 : TEXCOORD2;
			#endif
			float3 texcoord_3 : TEXCOORD3;
			#ifdef SHADOW
				float4 texcoord_4 : TEXCOORD4;
				#ifdef USE_TRANSLUCENT
					float3 texcoord_5 : TEXCOORD5;
				#endif
			#endif
			#ifdef NOISE
				float3 texcoord_6 : TEXCOORD6;
			#endif
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				float1 texcoord_9 : TEXCOORD9;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		float3 light_direction = getOmniRadius(s_light_position - vertex.xyz) * s_light_iradius.w;
		OUT.texcoord_1.x = dot(light_direction,tangent);
		OUT.texcoord_1.y = dot(light_direction,binormal);
		OUT.texcoord_1.z = dot(light_direction,normal) * s_light_front;
		OUT.texcoord_1.w = s_light_iradius.w * s_light_iradius.w;
		
		#ifdef PHONG
			float3 camera_direction = s_camera_position - vertex.xyz;
			OUT.texcoord_2.x = dot(camera_direction,tangent);
			OUT.texcoord_2.y = dot(camera_direction,binormal);
			OUT.texcoord_2.z = dot(camera_direction,normal) * s_light_front;
		#endif
		
		OUT.texcoord_3 = mul(vertex.xyz - s_light_position,(float3x3)s_light_transform);
		
		#ifdef SHADOW
			OUT.texcoord_4.xyz = (vertex.xyz - s_light_shadow_offset) * s_light_shadow_depth_range.x;
			OUT.texcoord_4.w = s_light_shadow_depth_range.y;
			#ifdef USE_TRANSLUCENT
				OUT.texcoord_5 = (vertex.xyz - s_light_shadow_offset) * s_light_shadow_iradius.x;
			#endif
		#endif
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			OUT.texcoord_9.x = getAlphaFadeScale(bound_sphere);
		#endif
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_LEAF_LIGHT_OMNI
		#define VERTEX_LEAF_LIGHT_OMNI
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef PHONG
				float3 texcoord_2 : TEXCOORD2;
			#endif
			float3 texcoord_3 : TEXCOORD3;
			#ifdef SHADOW
				float4 texcoord_4 : TEXCOORD4;
				#ifdef USE_TRANSLUCENT
					float3 texcoord_5 : TEXCOORD5;
				#endif
			#endif
			#ifdef NOISE
				float3 texcoord_8 : TEXCOORD8;
			#endif
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				float1 texcoord_9 : TEXCOORD9;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		float3 light_direction = getOmniRadius(s_light_position - vertex.xyz) * s_light_iradius.w;
		OUT.texcoord_1.x = dot(light_direction,tangent);
		OUT.texcoord_1.y = dot(light_direction,binormal);
		OUT.texcoord_1.z = dot(light_direction,normal) * s_light_front;
		OUT.texcoord_1.w = s_light_iradius.w * s_light_iradius.w;
		
		#ifdef PHONG
			float3 camera_direction = s_camera_position - vertex.xyz;
			OUT.texcoord_2.x = dot(camera_direction,tangent);
			OUT.texcoord_2.y = dot(camera_direction,binormal);
			OUT.texcoord_2.z = dot(camera_direction,normal) * s_light_front;
		#endif
		
		OUT.texcoord_3 = mul(vertex.xyz - s_light_position,(float3x3)s_light_transform);
		
		#ifdef SHADOW
			OUT.texcoord_4.xyz = (vertex.xyz - s_light_shadow_offset) * s_light_shadow_depth_range.x;
			OUT.texcoord_4.w = s_light_shadow_depth_range.y;
			#ifdef USE_TRANSLUCENT
				OUT.texcoord_5 = (vertex.xyz - s_light_shadow_offset) * s_light_shadow_iradius.x;
			#endif
		#endif
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			OUT.texcoord_9.x = getAlphaFadeScale(bound_sphere);
		#endif
		
	#endif
	
#endif
