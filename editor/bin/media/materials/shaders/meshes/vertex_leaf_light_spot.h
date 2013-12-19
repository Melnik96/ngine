/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_leaf_light_spot.h
 * Desc:    Mesh leaf light spot shader
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

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL
	
	#ifndef VERTEX_LEAF_LIGHT_SPOT
		#define VERTEX_LEAF_LIGHT_SPOT
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0] = texcoord;
		
		gl_TexCoord[1] = vertex;
		
		normal *= s_light_front;
		
		#ifdef QUALITY_MEDIUM && PHONG
			gl_TexCoord[2].xyz = s_camera_position - vertex.xyz;
			gl_TexCoord[3].xyz = float3(tangent.x,binormal.x,normal.x);
			gl_TexCoord[4].xyz = float3(tangent.y,binormal.y,normal.y);
			gl_TexCoord[5].xyz = float3(tangent.z,binormal.z,normal.z);
		#else
			gl_TexCoord[2].xyz = normal;
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
	
	#ifndef VERTEX_LEAF_LIGHT_SPOT
		#define VERTEX_LEAF_LIGHT_SPOT
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float3 texcoord_2 : TEXCOORD2;
			#ifdef QUALITY_MEDIUM && PHONG
				float3 texcoord_3 : TEXCOORD3;
				float3 texcoord_4 : TEXCOORD4;
				float3 texcoord_5 : TEXCOORD5;
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
		
		OUT.texcoord_1 = vertex.xyz;
		
		normal *= s_light_front;
		
		#ifdef QUALITY_MEDIUM && PHONG
			OUT.texcoord_2 = s_camera_position - vertex.xyz;
			OUT.texcoord_3 = float3(tangent.x,binormal.x,normal.x);
			OUT.texcoord_4 = float3(tangent.y,binormal.y,normal.y);
			OUT.texcoord_5 = float3(tangent.z,binormal.z,normal.z);
		#else
			OUT.texcoord_2 = normal;
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
	
	#ifndef VERTEX_LEAF_LIGHT_SPOT
		#define VERTEX_LEAF_LIGHT_SPOT
		
		struct VERTEX_OUT {
			float4 position : OUT_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float3 texcoord_2 : TEXCOORD2;
			#ifdef QUALITY_MEDIUM && PHONG
				float3 texcoord_3 : TEXCOORD3;
				float3 texcoord_4 : TEXCOORD4;
				float3 texcoord_5 : TEXCOORD5;
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
		
		OUT.texcoord_1 = vertex.xyz;
		
		normal *= s_light_front;
		
		#ifdef QUALITY_MEDIUM && PHONG
			OUT.texcoord_2 = s_camera_position - vertex.xyz;
			OUT.texcoord_3 = float3(tangent.x,binormal.x,normal.x);
			OUT.texcoord_4 = float3(tangent.y,binormal.y,normal.y);
			OUT.texcoord_5 = float3(tangent.z,binormal.z,normal.z);
		#else
			OUT.texcoord_2 = normal;
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
	
	#ifndef VERTEX_LEAF_LIGHT_SPOT
		#define VERTEX_LEAF_LIGHT_SPOT
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float3 texcoord_2 : TEXCOORD2;
			#ifdef QUALITY_MEDIUM && PHONG
				float3 texcoord_3 : TEXCOORD3;
				float3 texcoord_4 : TEXCOORD4;
				float3 texcoord_5 : TEXCOORD5;
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
		
		OUT.texcoord_1 = vertex.xyz;
		
		normal *= s_light_front;
		
		#ifdef QUALITY_MEDIUM && PHONG
			OUT.texcoord_2 = s_camera_position - vertex.xyz;
			OUT.texcoord_3 = float3(tangent.x,binormal.x,normal.x);
			OUT.texcoord_4 = float3(tangent.y,binormal.y,normal.y);
			OUT.texcoord_5 = float3(tangent.z,binormal.z,normal.z);
		#else
			OUT.texcoord_2 = normal;
		#endif
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			OUT.texcoord_9.x = getAlphaFadeScale(bound_sphere);
		#endif
		
	#endif
	
#endif