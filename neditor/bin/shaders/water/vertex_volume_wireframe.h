/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_volume_wireframe.h
 * Desc:    Water volume wireframe shader
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
	
	#ifndef VERTEX_VOLUME_WIREFRAME
		#define VERTEX_VOLUME_WIREFRAME
		
		uniform float4x4 s_water_projection;
		
	#else
		
		gl_Position = s_water_projection * vertex;
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_VOLUME_WIREFRAME
		#define VERTEX_VOLUME_WIREFRAME
		
		struct VERTEX_OUT {
			float4 position : POSITION;
		};
		
		float4x4 s_water_projection;
		
	#else
		
		OUT.position = mul(s_water_projection,vertex);
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_VOLUME_WIREFRAME
		#define VERTEX_VOLUME_WIREFRAME
		
		struct VERTEX_OUT {
			float4 position : SV_POSITION;
		};
		
		cbuffer shader_water_parameters {
			float4x4 s_water_projection;
		};
		
	#else
		
		OUT.position = mul(s_water_projection,vertex);
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_VOLUME_WIREFRAME
		#define VERTEX_VOLUME_WIREFRAME
		
		struct VERTEX_OUT {
			float4 position : POSITION;
		};
		
		uniform float4x4 s_water_projection;
		
	#else
		
		OUT.position = mul(s_water_projection,vertex);
		
	#endif
	
#endif
