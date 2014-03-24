/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base_ambient_indirect.h
 * Desc:    Mesh base ambient indirect shader
 * Version: 1.08
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
	
	#ifndef VERTEX_BASE_AMBIENT_INDIRECT
		#define VERTEX_BASE_AMBIENT_INDIRECT
		
		uniform float reflection_adjust;
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0] = texcoord;
		
		#ifdef USE_TESSELLATION && TESSELLATION
			
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				gl_Position.w = getAlphaFade(bound_sphere);
			#endif
			
			gl_TexCoord[1] = float4(tangent,orientation);
			
		#else
			
			gl_TexCoord[1].xyz = float3(tangent.x,binormal.x,normal.x);
			gl_TexCoord[2].xyz = float3(tangent.y,binormal.y,normal.y);
			gl_TexCoord[3].xyz = float3(tangent.z,binormal.z,normal.z);
			
			gl_TexCoord[4].xyz = (vertex.xyz - s_material_reflection_center) * reflection_adjust * 10.0f / s_material_reflection_radius;
			
			#ifdef USE_DEFERRED || (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
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
	
	#ifndef VERTEX_BASE_AMBIENT_INDIRECT
		#define VERTEX_BASE_AMBIENT_INDIRECT
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float3 texcoord_2 : TEXCOORD2;
			float3 texcoord_3 : TEXCOORD3;
			float3 texcoord_4 : TEXCOORD4;
			#ifdef USE_DEFERRED || (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
				float4 texcoord_7 : TEXCOORD7;
			#endif
		};
		
		float reflection_adjust;
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = float3(tangent.x,binormal.x,normal.x);
		OUT.texcoord_2 = float3(tangent.y,binormal.y,normal.y);
		OUT.texcoord_3 = float3(tangent.z,binormal.z,normal.z);
		
		OUT.texcoord_4 = (vertex.xyz - s_material_reflection_center) * reflection_adjust * 10.0f / s_material_reflection_radius;
		
		#ifdef USE_DEFERRED || (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
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
	
	#ifndef VERTEX_BASE_AMBIENT_INDIRECT
		#define VERTEX_BASE_AMBIENT_INDIRECT
		
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
				#ifdef USE_ALPHA_FADE && ALPHA_FADE
					float1 texcoord_9 : TEXCOORD9;
				#endif
			#endif
		};
		
		cbuffer shader_indirect_parameters {
			float reflection_adjust;
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
			
			OUT.texcoord_1 = float3(tangent.x,binormal.x,normal.x);
			OUT.texcoord_2 = float3(tangent.y,binormal.y,normal.y);
			OUT.texcoord_3 = float3(tangent.z,binormal.z,normal.z);
			
			OUT.texcoord_4 = (vertex.xyz - s_material_reflection_center) * reflection_adjust * 10.0f / s_material_reflection_radius;
			
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
	
	#ifndef VERTEX_BASE_AMBIENT_INDIRECT
		#define VERTEX_BASE_AMBIENT_INDIRECT
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float3 texcoord_2 : TEXCOORD2;
			float3 texcoord_3 : TEXCOORD3;
			float3 texcoord_4 : TEXCOORD4;
			#ifdef USE_DEFERRED || (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
				float4 texcoord_9 : TEXCOORD9;
			#endif
		};
		
		uniform float reflection_adjust;
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = float3(tangent.x,binormal.x,normal.x);
		OUT.texcoord_2 = float3(tangent.y,binormal.y,normal.y);
		OUT.texcoord_3 = float3(tangent.z,binormal.z,normal.z);
		
		OUT.texcoord_4 = (vertex.xyz - s_material_reflection_center) * reflection_adjust * 10.0f / s_material_reflection_radius;
		
		#ifdef USE_DEFERRED || (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
			OUT.texcoord_9 = getProjection(OUT.position);
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				OUT.texcoord_9.z = getAlphaFade(bound_sphere);
			#endif
		#endif
		
	#endif
	
#endif
