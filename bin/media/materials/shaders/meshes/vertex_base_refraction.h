/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base_refraction.h
 * Desc:    Mesh base refraction shader
 * Version: 1.12
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
	
	#ifndef VERTEX_BASE_REFRACTION
		#define VERTEX_BASE_REFRACTION
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0] = texcoord;
		
		float3x3 transform = float3x3(s_modelview[0].xyz,s_modelview[1].xyz,s_modelview[2].xyz) * float3x3(tangent,binormal,normal);
		gl_TexCoord[1].xyz = float3(transform[0].x,transform[1].x,transform[2].x);
		gl_TexCoord[2].xyz = float3(transform[0].y,transform[1].y,transform[2].y);
		
		gl_TexCoord[3].xy = float2(s_projection[1].y,gl_Position.w);
		
		#ifdef (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
			gl_TexCoord[7] = getProjection(gl_Position);
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
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
	
	#ifndef VERTEX_BASE_REFRACTION
		#define VERTEX_BASE_REFRACTION
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float3 texcoord_2 : TEXCOORD2;
			float2 texcoord_3 : TEXCOORD3;
			#ifdef (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
				float4 texcoord_7 : TEXCOORD7;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		float3x3 transform = mul((float3x3)s_modelview,transpose(float3x3(tangent,binormal,normal)));
		OUT.texcoord_1 = transform[0].xyz;
		OUT.texcoord_2 = transform[1].xyz;
		
		OUT.texcoord_3 = float2(s_projection[1].y,OUT.position.w);
		
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
	
	#ifndef VERTEX_BASE_REFRACTION
		#define VERTEX_BASE_REFRACTION
		
		struct VERTEX_OUT {
			float4 position : OUT_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float3 texcoord_2 : TEXCOORD2;
			float2 texcoord_3 : TEXCOORD3;
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				float1 texcoord_9 : TEXCOORD9;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		float3x3 transform = mul((float3x3)s_modelview,transpose(float3x3(tangent,binormal,normal)));
		OUT.texcoord_1 = transform[0].xyz;
		OUT.texcoord_2 = transform[1].xyz;
		
		OUT.texcoord_3 = float2(s_projection[1].y,OUT.position.w);
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			OUT.texcoord_9.x = getAlphaFade(bound_sphere);
		#endif
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_BASE_REFRACTION
		#define VERTEX_BASE_REFRACTION
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float3 texcoord_2 : TEXCOORD2;
			float2 texcoord_3 : TEXCOORD3;
			#ifdef (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
				float4 texcoord_9 : TEXCOORD9;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		float3x3 transform = mul((float3x3)s_modelview,transpose(float3x3(tangent,binormal,normal)));
		OUT.texcoord_1 = transform[0].xyz;
		OUT.texcoord_2 = transform[1].xyz;
		
		OUT.texcoord_3 = float2(s_projection[1].y,OUT.position.w);
		
		#ifdef (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
			OUT.texcoord_9 = getProjection(OUT.position);
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				OUT.texcoord_9.z = getAlphaFade(bound_sphere);
			#endif
		#endif
		
	#endif
	
#endif
