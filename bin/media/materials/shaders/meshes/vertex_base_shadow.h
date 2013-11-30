/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base_shadow.h
 * Desc:    Mesh base shadow map shader
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

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL
	
	#ifndef VERTEX_BASE_SHADOW
		#define VERTEX_BASE_SHADOW
		
	#else
		
		gl_Position = getPosition(vertex);
		
		#ifdef USE_TESSELLATION && TESSELLATION
			
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				gl_Position.w = getAlphaFade(bound_sphere);
			#endif
			
			gl_TexCoord[0].xy = texcoord.xy;
			
			#ifdef TRANSLUCENT
				gl_TexCoord[1] = float4(tangent,orientation);
			#endif
			
		#else
			
			#ifdef ALPHA || TRANSLUCENT
				gl_TexCoord[0].xy = texcoord.xy;
			#endif
			
			#ifdef TRANSLUCENT
				float3 light_direction = normalize(s_light_position - vertex.xyz);
				gl_TexCoord[1].x = dot(light_direction,tangent);
				gl_TexCoord[1].y = dot(light_direction,binormal);
				gl_TexCoord[1].z = dot(light_direction,normal) * s_light_front;
				
				gl_TexCoord[2].xyz = (s_light_shadow_offset - vertex.xyz) * s_light_shadow_iradius.x;
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
	
	#ifndef VERTEX_BASE_SHADOW
		#define VERTEX_BASE_SHADOW
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			#ifdef ALPHA || TRANSLUCENT
				float2 texcoord_0 : TEXCOORD0;
			#endif
			#ifdef TRANSLUCENT
				float3 texcoord_1 : TEXCOORD1;
				float3 texcoord_2 : TEXCOORD2;
			#endif
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				float4 texcoord_7 : TEXCOORD7;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		#ifdef ALPHA || TRANSLUCENT
			OUT.texcoord_0 = texcoord.xy;
		#endif
		
		#ifdef TRANSLUCENT
			float3 light_direction = s_light_position - vertex.xyz;
			OUT.texcoord_1.x = dot(light_direction,tangent);
			OUT.texcoord_1.y = dot(light_direction,binormal);
			OUT.texcoord_1.z = dot(light_direction,normal) * s_light_front;
			
			OUT.texcoord_2.xyz = (s_light_shadow_offset - vertex.xyz) * s_light_shadow_iradius.x;
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
	
	#ifndef VERTEX_BASE_SHADOW
		#define VERTEX_BASE_SHADOW
		
		struct VERTEX_OUT {
			float4 position : OUT_POSITION;
			#ifdef USE_TESSELLATION && TESSELLATION
				float2 texcoord_0 : TEXCOORD0;
				#ifdef TRANSLUCENT
					float4 texcoord_1 : TEXCOORD1;
				#endif
				float4 texcoord_9 : TEXCOORD9;
			#else
				#ifdef ALPHA || TRANSLUCENT
					float2 texcoord_0 : TEXCOORD0;
				#endif
				#ifdef TRANSLUCENT
					float3 texcoord_1 : TEXCOORD1;
					float3 texcoord_2 : TEXCOORD2;
				#endif
				#ifdef USE_ALPHA_FADE && ALPHA_FADE
					float1 texcoord_9 : TEXCOORD9;
				#endif
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		#ifdef USE_TESSELLATION && TESSELLATION
			
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				OUT.position.w = getAlphaFade(bound_sphere);
			#endif
			
			OUT.texcoord_0 = texcoord.xy;
			
			#ifdef TRANSLUCENT
				OUT.texcoord_1 = float4(tangent,orientation);
			#endif
			
		#else
			
			#ifdef ALPHA || TRANSLUCENT
				OUT.texcoord_0 = texcoord.xy;
			#endif
			
			#ifdef TRANSLUCENT
				float3 light_direction = s_light_position - vertex.xyz;
				OUT.texcoord_1.x = dot(light_direction,tangent);
				OUT.texcoord_1.y = dot(light_direction,binormal);
				OUT.texcoord_1.z = dot(light_direction,normal) * s_light_front;
				
				OUT.texcoord_2.xyz = (s_light_shadow_offset - vertex.xyz) * s_light_shadow_iradius.x;
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
	
	#ifndef VERTEX_BASE_SHADOW
		#define VERTEX_BASE_SHADOW
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			#ifdef ALPHA || TRANSLUCENT
				float2 texcoord_0 : TEXCOORD0;
			#endif
			#ifdef TRANSLUCENT
				float3 texcoord_1 : TEXCOORD1;
				float3 texcoord_2 : TEXCOORD2;
			#endif
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				float4 texcoord_9 : TEXCOORD9;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		#ifdef ALPHA || TRANSLUCENT
			OUT.texcoord_0 = texcoord.xy;
		#endif
		
		#ifdef TRANSLUCENT
			float3 light_direction = s_light_position - vertex.xyz;
			OUT.texcoord_1.x = dot(light_direction,tangent);
			OUT.texcoord_1.y = dot(light_direction,binormal);
			OUT.texcoord_1.z = dot(light_direction,normal) * s_light_front;
			
			OUT.texcoord_2.xyz = (s_light_shadow_offset - vertex.xyz) * s_light_shadow_iradius.x;
		#endif
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			OUT.texcoord_9 = getProjection(OUT.position);
			OUT.texcoord_9.z = getAlphaFade(bound_sphere);
		#endif
		
	#endif
	
#endif
