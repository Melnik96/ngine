/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base_light_world.shader
 * Desc:    Particles base light world shader
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
	
	#ifndef VERTEX_BASE_LIGHT_WORLD
		#define VERTEX_BASE_LIGHT_WORLD
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0] = texcoord;
		
		gl_TexCoord[1] = color * s_light_color;
		
		#ifdef VOLUME
			gl_TexCoord[2] = volume;
			gl_TexCoord[7] = getProjection(gl_Position);
		#endif
		
		#ifdef SHADOW
			gl_TexCoord[5] = vertex;
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_BASE_LIGHT_WORLD
		#define VERTEX_BASE_LIGHT_WORLD
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef VOLUME
				float4 texcoord_2 : TEXCOORD2;
				float4 texcoord_7 : TEXCOORD7;
			#endif
			#ifdef SHADOW
				float4 texcoord_5 : TEXCOORD5;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = color * s_light_color;
		
		#ifdef VOLUME
			OUT.texcoord_2 = volume;
			OUT.texcoord_7 = getProjection(OUT.position);
		#endif
		
		#ifdef SHADOW
			OUT.texcoord_5 = vertex;
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_BASE_LIGHT_WORLD
		#define VERTEX_BASE_LIGHT_WORLD
		
		struct VERTEX_OUT {
			float4 position : SV_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef VOLUME
				float4 texcoord_2 : TEXCOORD2;
			#endif
			#ifdef SHADOW
				float4 texcoord_5 : TEXCOORD5;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = color * s_light_color;
		
		#ifdef VOLUME
			OUT.texcoord_2 = volume;
		#endif
		
		#ifdef SHADOW
			OUT.texcoord_5 = vertex;
		#endif
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_BASE_LIGHT_WORLD
		#define VERTEX_BASE_LIGHT_WORLD
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef VOLUME
				float4 texcoord_2 : TEXCOORD2;
				float4 texcoord_9 : TEXCOORD9;
			#endif
			#ifdef SHADOW
				float4 texcoord_5 : TEXCOORD5;
				float4 texcoord_6 : TEXCOORD6;
				float4 texcoord_7 : TEXCOORD7;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = color * s_light_color;
		
		#ifdef VOLUME
			OUT.texcoord_2 = volume;
			OUT.texcoord_9 = getProjection(OUT.position);
		#endif
		
		#ifdef SHADOW
			OUT.texcoord_5 = vertex;
			OUT.texcoord_6.x = dot(s_light_shadow_projections[0][0],vertex);
			OUT.texcoord_6.y = dot(s_light_shadow_projections[0][1],vertex);
			OUT.texcoord_6.z = dot(s_light_shadow_projections[1][0],vertex);
			OUT.texcoord_6.w = dot(s_light_shadow_projections[1][1],vertex);
			OUT.texcoord_7.x = dot(s_light_shadow_projections[2][0],vertex);
			OUT.texcoord_7.y = dot(s_light_shadow_projections[2][1],vertex);
			OUT.texcoord_7.z = dot(s_light_shadow_projections[3][0],vertex);
			OUT.texcoord_7.w = dot(s_light_shadow_projections[3][1],vertex);
		#endif
		
	#endif
	
#endif
