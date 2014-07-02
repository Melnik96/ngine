/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_leaf_deferred.h
 * Desc:    Mesh leaf deferred shader
 * Version: 1.04
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
	
	#ifndef VERTEX_LEAF_DEFERRED
		#define VERTEX_LEAF_DEFERRED
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0].xy = texcoord.xy;
		
		float distance = length((vertex.xyz - s_camera_position) / s_depth_range.y);
		
		#ifdef LEAFS_BILLBOARD
			float3 screen_normal = float3(0.0f,0.0f,1.0f);
		#else
			float3 screen_normal = (s_modelview * float4(normal,0.0f)).xyz;
		#endif
		
		gl_TexCoord[1] = float4(screen_normal,distance);
		
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
	
	#ifndef VERTEX_LEAF_DEFERRED
		#define VERTEX_LEAF_DEFERRED
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float2 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				float1 texcoord_7 : TEXCOORD7;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord.xy;
		
		float distance = length((vertex.xyz - s_camera_position) / s_depth_range.y);
		
		#ifdef LEAFS_BILLBOARD
			float3 screen_normal = float3(0.0f,0.0f,1.0f);
		#else
			float3 screen_normal = mul((float3x3)s_modelview,normal);
		#endif
		
		OUT.texcoord_1 = float4(screen_normal,distance);
		
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
	
	#ifndef VERTEX_LEAF_DEFERRED
		#define VERTEX_LEAF_DEFERRED
		
		struct VERTEX_OUT {
			float4 position : OUT_POSITION;
			float2 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				float1 texcoord_9 : TEXCOORD9;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord.xy;
		
		float distance = length((vertex.xyz - s_camera_position) / s_depth_range.y);
		
		#ifdef LEAFS_BILLBOARD
			float3 screen_normal = float3(0.0f,0.0f,1.0f);
		#else
			float3 screen_normal = mul((float3x3)s_modelview,normal);
		#endif
		
		OUT.texcoord_1 = float4(screen_normal,distance);
		
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
	
	#ifndef VERTEX_LEAF_DEFERRED
		#define VERTEX_LEAF_DEFERRED
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float2 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				float1 texcoord_9 : TEXCOORD9;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord.xy;
		
		float distance = length((vertex.xyz - s_camera_position) / s_depth_range.y);
		
		#ifdef LEAFS_BILLBOARD
			float3 screen_normal = float3(0.0f,0.0f,1.0f);
		#else
			float3 screen_normal = mul((float3x3)s_modelview,normal);
		#endif
		
		OUT.texcoord_1 = float4(screen_normal,distance);
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			OUT.texcoord_9.x = getAlphaFadeScale(bound_sphere);
		#endif
		
	#endif
	
#endif
