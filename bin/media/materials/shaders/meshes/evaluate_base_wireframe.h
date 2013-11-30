/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    evaluate_base_wireframe.h
 * Desc:    Base wireframe shader
 * Version: 1.05
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
	
	#ifndef EVALUATE_BASE_WIREFRAME
		#define EVALUATE_BASE_WIREFRAME
		
	#else
		
		gl_Position = getPosition(vertex);
		
	#endif
	
/******************************************************************************\
*
* Direct3D11
*
\******************************************************************************/

#elif DIRECT3D11
	
	#ifndef EVALUATE_BASE_WIREFRAME
		#define EVALUATE_BASE_WIREFRAME
		
		struct EVALUATE_IN {
			float4 position : POSITION;
			float2 texcoord_0 : TEXCOORD0;
			float4 texcoord_9 : TEXCOORD9;
		};
		
		struct EVALUATE_OUT {
			float4 position : SV_POSITION;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
	#endif
	
#endif
