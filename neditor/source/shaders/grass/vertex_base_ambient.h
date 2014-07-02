/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base_ambient.shader
 * Desc:    Grass base ambient shader
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
	
	#ifndef VERTEX_BASE_AMBIENT
		#define VERTEX_BASE_AMBIENT
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0].xy = texcoord;
		gl_TexCoord[0].zw = noise;
		
		#ifdef LIGHTMAP
			gl_TexCoord[1].xy = lightmap;
		#endif
		
		gl_TexCoord[2].xyz = direction;
		
		gl_TexCoord[2].w = alpha;
		
		#ifdef USE_DEFERRED
			gl_TexCoord[7] = getProjection(gl_Position);
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_BASE_AMBIENT
		#define VERTEX_BASE_AMBIENT
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			#ifdef LIGHTMAP
				float2 texcoord_1 : TEXCOORD1;
			#endif
			float4 texcoord_2 : TEXCOORD2;
			#ifdef USE_DEFERRED
				float4 texcoord_7 : TEXCOORD7;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		#ifdef LIGHTMAP
			OUT.texcoord_1 = lightmap;
		#endif
		
		OUT.texcoord_2.xyz = direction;
		
		OUT.texcoord_2.w = alpha;
		
		#ifdef USE_DEFERRED
			OUT.texcoord_7 = getProjection(OUT.position);
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_BASE_AMBIENT
		#define VERTEX_BASE_AMBIENT
		
		struct VERTEX_OUT {
			float4 position : SV_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			#ifdef LIGHTMAP
				float2 texcoord_1 : TEXCOORD1;
			#endif
			float4 texcoord_2 : TEXCOORD2;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		#ifdef LIGHTMAP
			OUT.texcoord_1 = lightmap;
		#endif
		
		OUT.texcoord_2.xyz = direction;
		
		OUT.texcoord_2.w = alpha;
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_BASE_AMBIENT
		#define VERTEX_BASE_AMBIENT
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			#ifdef LIGHTMAP
				float2 texcoord_1 : TEXCOORD1;
			#endif
			float4 texcoord_2 : TEXCOORD2;
			#ifdef USE_DEFERRED
				float4 texcoord_9 : TEXCOORD9;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		#ifdef LIGHTMAP
			OUT.texcoord_1 = lightmap;
		#endif
		
		OUT.texcoord_2.xyz = direction;
		
		OUT.texcoord_2.w = alpha;
		
		#ifdef USE_DEFERRED
			OUT.texcoord_9 = getProjection(OUT.position);
		#endif
		
	#endif
	
#endif
