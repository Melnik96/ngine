/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base_deferred.shader
 * Desc:    Grass base deferred shader
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
	
	#ifndef VERTEX_BASE_DEFERRED
		#define VERTEX_BASE_DEFERRED
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0].xy = texcoord;
		gl_TexCoord[1].zw = noise;
		
		gl_TexCoord[1].xyz = (s_modelview * float4(direction,0.0f)).xyz;
		
		gl_TexCoord[1].w = length(vertex.xyz - s_camera_position) / s_depth_range.y;
		
		gl_TexCoord[2].x = alpha;
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_BASE_DEFERRED
		#define VERTEX_BASE_DEFERRED
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			float1 texcoord_2 : TEXCOORD2;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		OUT.texcoord_1.xyz = mul((float3x3)s_modelview,direction);
		
		OUT.texcoord_1.w = length(vertex.xyz - s_camera_position) / s_depth_range.y;
		
		OUT.texcoord_2.x = alpha;
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_BASE_DEFERRED
		#define VERTEX_BASE_DEFERRED
		
		struct VERTEX_OUT {
			float4 position : SV_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			float1 texcoord_2 : TEXCOORD2;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		OUT.texcoord_1.xyz = mul((float3x3)s_modelview,direction);
		
		OUT.texcoord_1.w = length(vertex.xyz - s_camera_position) / s_depth_range.y;
		
		OUT.texcoord_2.x = alpha;
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_BASE_DEFERRED
		#define VERTEX_BASE_DEFERRED
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			float1 texcoord_2 : TEXCOORD2;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		OUT.texcoord_1.xyz = mul((float3x3)s_modelview,direction);
		
		OUT.texcoord_1.w = length(vertex.xyz - s_camera_position) / s_depth_range.y;
		
		OUT.texcoord_2.x = alpha;
		
	#endif
	
#endif
