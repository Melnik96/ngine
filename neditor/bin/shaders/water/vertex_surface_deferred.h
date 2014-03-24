/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_surface_deferred.h
 * Desc:    Water surface deferred shader
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
	
	#ifndef VERTEX_SURFACE_DEFERRED
		#define VERTEX_SURFACE_DEFERRED
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0].xyz = (vertex.xyz - s_camera_position) / s_depth_range.y;
		
		gl_TexCoord[1].xyz = (s_modelview * float4(normal,0.0f)).xyz;
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_SURFACE_DEFERRED
		#define VERTEX_SURFACE_DEFERRED
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float3 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = (vertex.xyz - s_camera_position) / s_depth_range.y;
		
		OUT.texcoord_1 = mul((float3x3)s_modelview,normal);
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_SURFACE_DEFERRED
		#define VERTEX_SURFACE_DEFERRED
		
		struct VERTEX_OUT {
			float4 position : SV_POSITION;
			float3 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = (vertex.xyz - s_camera_position) / s_depth_range.y;
		
		OUT.texcoord_1 = mul((float3x3)s_modelview,normal);
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_SURFACE_DEFERRED
		#define VERTEX_SURFACE_DEFERRED
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float3 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = (vertex.xyz - s_camera_position) / s_depth_range.y;
		
		OUT.texcoord_1 = mul((float3x3)s_modelview,normal);
		
	#endif
	
#endif
