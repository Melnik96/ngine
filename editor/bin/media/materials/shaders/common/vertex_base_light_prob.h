/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base_light_prob.h
 * Desc:    Base light prob shader
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
	
	#ifndef VERTEX_BASE_LIGHT_PROB
		#define VERTEX_BASE_LIGHT_PROB
		
	#else
			
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0] = texcoord;
		
		#ifdef USE_TESSELLATION && TESSELLATION
			
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				gl_Position.w = getAlphaFade(bound_sphere);
			#endif
			
			gl_TexCoord[1] = float4(tangent,orientation);
			
		#else
			
			gl_TexCoord[1].xyz = s_camera_position - vertex.xyz;
			
			normal *= s_light_front;
			
			gl_TexCoord[2].xyz = float3(tangent.x,binormal.x,normal.x);
			gl_TexCoord[3].xyz = float3(tangent.y,binormal.y,normal.y);
			gl_TexCoord[4].xyz = float3(tangent.z,binormal.z,normal.z);
			
			#ifdef FLECK
				gl_TexCoord[6].xyz = position.xyz;
			#endif
			
			#ifdef (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
				gl_TexCoord[7] = getProjection(gl_Position);
				#ifdef USE_ALPHA_FADE && ALPHA_FADE
					gl_TexCoord[7].z = getAlphaFade(bound_sphere);
				#endif
			#endif
			
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_BASE_LIGHT_PROB
		#define VERTEX_BASE_LIGHT_PROB
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float3 texcoord_2 : TEXCOORD2;
			float3 texcoord_3 : TEXCOORD3;
			float3 texcoord_4 : TEXCOORD4;
			#ifdef FLECK
				float3 texcoord_6 : TEXCOORD6;
			#endif
			#ifdef (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
				float4 texcoord_7 : TEXCOORD7;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = s_camera_position - vertex.xyz;
		
		normal *= s_light_front;
		
		OUT.texcoord_2 = float3(tangent.x,binormal.x,normal.x);
		OUT.texcoord_3 = float3(tangent.y,binormal.y,normal.y);
		OUT.texcoord_4 = float3(tangent.z,binormal.z,normal.z);
		
		#ifdef FLECK
			OUT.texcoord_6 = position.xyz;
		#endif
		
		#ifdef (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
			OUT.texcoord_7 = getProjection(OUT.position);
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				OUT.texcoord_7.z = getAlphaFade(bound_sphere);
			#endif
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_BASE_LIGHT_PROB
		#define VERTEX_BASE_LIGHT_PROB
		
		struct VERTEX_OUT {
			float4 position : OUT_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			#ifdef USE_TESSELLATION && TESSELLATION
				float4 texcoord_1 : TEXCOORD1;
				float4 texcoord_9 : TEXCOORD9;
			#else
				float3 texcoord_1 : TEXCOORD1;
				float3 texcoord_2 : TEXCOORD2;
				float3 texcoord_3 : TEXCOORD3;
				float3 texcoord_4 : TEXCOORD4;
				#ifdef FLECK
					float3 texcoord_6 : TEXCOORD6;
				#endif
				#ifdef USE_ALPHA_FADE && ALPHA_FADE
					float1 texcoord_9 : TEXCOORD9;
				#endif
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		#ifdef USE_TESSELLATION && TESSELLATION
			
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				OUT.position.w = getAlphaFade(bound_sphere);
			#endif
			
			OUT.texcoord_1 = float4(tangent,orientation);
			
		#else
			
			OUT.texcoord_1 = s_camera_position - vertex.xyz;
			
			normal *= s_light_front;
			
			OUT.texcoord_2 = float3(tangent.x,binormal.x,normal.x);
			OUT.texcoord_3 = float3(tangent.y,binormal.y,normal.y);
			OUT.texcoord_4 = float3(tangent.z,binormal.z,normal.z);
			
			#ifdef FLECK
				OUT.texcoord_6 = position.xyz;
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
	
	#ifndef VERTEX_BASE_LIGHT_PROB
		#define VERTEX_BASE_LIGHT_PROB
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float3 texcoord_2 : TEXCOORD2;
			float3 texcoord_3 : TEXCOORD3;
			float3 texcoord_4 : TEXCOORD4;
			#ifdef FLECK
				float3 texcoord_8 : TEXCOORD8;
			#endif
			#ifdef (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
				float4 texcoord_9 : TEXCOORD9;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = s_camera_position - vertex.xyz;
		
		normal *= s_light_front;
		
		OUT.texcoord_2 = float3(tangent.x,binormal.x,normal.x);
		OUT.texcoord_3 = float3(tangent.y,binormal.y,normal.y);
		OUT.texcoord_4 = float3(tangent.z,binormal.z,normal.z);
		
		#ifdef FLECK
			OUT.texcoord_8 = position.xyz;
		#endif
		
		#ifdef (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
			OUT.texcoord_9 = getProjection(OUT.position);
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				OUT.texcoord_9.z = getAlphaFade(bound_sphere);
			#endif
		#endif
		
	#endif
	
#endif
