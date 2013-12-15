/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_light.h
 * Desc:    Grass base light shader
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
	
	#include <core/shaders/grass/fragment_base_sample.h>
	
	half3 color = diffuse.xyz * half3(gl_TexCoord[1].xyz);
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#include <core/shaders/grass/fragment_base_sample.h>
	
	half3 color = diffuse.xyz * IN.texcoord_1.xyz;
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#include <core/shaders/grass/fragment_base_sample.h>
	
	half3 color = diffuse.xyz * IN.texcoord_1.xyz;
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#include <core/shaders/grass/fragment_base_sample.h>
	
	half3 color = diffuse.xyz * IN.texcoord_1.xyz;
	
#endif
