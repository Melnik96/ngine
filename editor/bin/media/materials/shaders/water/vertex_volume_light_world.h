/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_volume_light_world.h
 * Desc:    Water volume light world shader
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
	
	#ifndef VERTEX_VOLUME_LIGHT_WORLD
		#define VERTEX_VOLUME_LIGHT_WORLD
		
		uniform float4x4 s_water_projection;
		
	#else
		
		gl_Position = s_water_projection * vertex;
		
		gl_TexCoord[1] = direction;
		
		gl_TexCoord[7] = getProjection(gl_Position);
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_VOLUME_LIGHT_WORLD
		#define VERTEX_VOLUME_LIGHT_WORLD
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_1 : TEXCOORD1;
			float4 texcoord_7 : TEXCOORD7;
		};
		
		float4x4 s_water_projection;
		
	#else
		
		OUT.position = mul(s_water_projection,vertex);
		
		OUT.texcoord_1 = direction;
		
		OUT.texcoord_7 = getProjection(OUT.position);
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_VOLUME_LIGHT_WORLD
		#define VERTEX_VOLUME_LIGHT_WORLD
		
		struct VERTEX_OUT {
			float4 position : SV_POSITION;
			float4 texcoord_1 : TEXCOORD1;
		};
		
		cbuffer shader_water_parameters {
			float4x4 s_water_projection;
		};
		
	#else
		
		OUT.position = mul(s_water_projection,vertex);
		
		OUT.texcoord_1 = direction;
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_VOLUME_LIGHT_WORLD
		#define VERTEX_VOLUME_LIGHT_WORLD
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_1 : TEXCOORD1;
			float4 texcoord_9 : TEXCOORD9;
		};
		
		uniform float4x4 s_water_projection;
		
	#else
		
		OUT.position = mul(s_water_projection,vertex);
		
		OUT.texcoord_1 = direction;
		
		OUT.texcoord_9 = getProjection(OUT.position);
		
	#endif
	
#endif
