/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    control_base_light_prob.h
 * Desc:    Mesh base light prob shader
 * Version: 1.06
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
	
	#ifndef CONTROL_BASE_LIGHT_PROB
		#define CONTROL_BASE_LIGHT_PROB
		
	#else
		
		gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
		gl_out[gl_InvocationID].gl_TexCoord[0] = gl_in[gl_InvocationID].gl_TexCoord[0];
		gl_out[gl_InvocationID].gl_TexCoord[1] = gl_in[gl_InvocationID].gl_TexCoord[1];
		gl_out[gl_InvocationID].gl_TexCoord[7] = gl_in[gl_InvocationID].gl_TexCoord[7];
		
	#endif
	
/******************************************************************************\
*
* Direct3D11
*
\******************************************************************************/

#elif DIRECT3D11
	
	#ifndef CONTROL_BASE_LIGHT_PROB
		#define CONTROL_BASE_LIGHT_PROB
		
		struct CONTROL_IO {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			float4 texcoord_9 : TEXCOORD9;
		};
		
	#else
		
	#endif
	
#endif
