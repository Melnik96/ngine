/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base_velocity.h
 * Desc:    Mesh base velocity shader
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
	
	#ifndef VERTEX_BASE_VELOCITY
		#define VERTEX_BASE_VELOCITY
		
		uniform float3 s_mesh_center_of_mass;
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0] = texcoord;
		
		#ifdef USE_TESSELLATION && TESSELLATION
			
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				gl_Position.w = getAlphaFade(bound_sphere);
			#endif
			
		#else
			
			gl_TexCoord[1].xyz = vertex.xyz - s_mesh_center_of_mass;
			
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
	
	#ifndef VERTEX_BASE_VELOCITY
		#define VERTEX_BASE_VELOCITY
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				float4 texcoord_7 : TEXCOORD7;
			#endif
		};
		
		float3 s_mesh_center_of_mass;
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = vertex.xyz - s_mesh_center_of_mass;
		
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
	
	#ifndef VERTEX_BASE_VELOCITY
		#define VERTEX_BASE_VELOCITY
		
		struct VERTEX_OUT {
			float4 position : OUT_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			#ifdef USE_TESSELLATION && TESSELLATION
				float4 texcoord_9 : TEXCOORD9;
			#else
				float3 texcoord_1 : TEXCOORD1;
				#ifdef USE_ALPHA_FADE && ALPHA_FADE
					float1 texcoord_9 : TEXCOORD9;
				#endif
			#endif
		};
		
		cbuffer shader_velocity_parameters {
			float3 s_mesh_center_of_mass;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		#ifdef USE_TESSELLATION && TESSELLATION
			
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				OUT.position.w = getAlphaFade(bound_sphere);
			#endif
			
		#else
			
			OUT.texcoord_1 = vertex.xyz - s_mesh_center_of_mass;
			
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
	
	#ifndef VERTEX_BASE_VELOCITY
		#define VERTEX_BASE_VELOCITY
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				float4 texcoord_9 : TEXCOORD9;
			#endif
		};
		
		uniform float3 s_mesh_center_of_mass;
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = vertex.xyz - s_mesh_center_of_mass;
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			OUT.texcoord_9 = getProjection(OUT.position);
			OUT.texcoord_9.z = getAlphaFade(bound_sphere);
		#endif
		
	#endif
	
#endif
