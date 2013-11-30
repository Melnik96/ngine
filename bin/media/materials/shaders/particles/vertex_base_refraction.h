/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base_refraction.shader
 * Desc:    Particles base refraction shader
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
	
	#ifndef VERTEX_BASE_REFRACTION
		#define VERTEX_BASE_REFRACTION
		
		uniform float refraction_scale;
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0] = texcoord;
		
		gl_TexCoord[1].x = refraction_scale * saturate(s_projection[1].y / gl_Position.w);
		
		#ifdef VOLUME
			gl_TexCoord[2] = volume;
			gl_TexCoord[7] = getProjection(gl_Position);
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
			float1 texcoord_1 : TEXCOORD1;
			#ifdef VOLUME
				float4 texcoord_2 : TEXCOORD2;
				float4 texcoord_7 : TEXCOORD7;
			#endif
		};
		
		float refraction_scale;
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = refraction_scale * saturate(s_projection[1].y / OUT.position.w);
		
		#ifdef VOLUME
			OUT.texcoord_2 = volume;
			OUT.texcoord_7 = getProjection(OUT.position);
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
			float4 position : SV_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float1 texcoord_1 : TEXCOORD1;
			#ifdef VOLUME
				float4 texcoord_2 : TEXCOORD2;
			#endif
		};
		
		cbuffer shader_refraction_parameters {
			float refraction_scale;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = refraction_scale * saturate(s_projection[1].y / OUT.position.w);
		
		#ifdef VOLUME
			OUT.texcoord_2 = volume;
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
			float1 texcoord_1 : TEXCOORD1;
			#ifdef VOLUME
				float4 texcoord_2 : TEXCOORD2;
				float4 texcoord_9 : TEXCOORD9;
			#endif
		};
		
		uniform float refraction_scale;
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = refraction_scale * saturate(s_projection[1].y / OUT.position.w);
		
		#ifdef VOLUME
			OUT.texcoord_2 = volume;
			OUT.texcoord_9 = getProjection(OUT.position);
		#endif
		
	#endif
	
#endif
