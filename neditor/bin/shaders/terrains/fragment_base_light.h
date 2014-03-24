/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_light.h
 * Desc:    Terrain base light shader
 * Version: 1.09
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
	
	#include <core/shaders/terrains/fragment_base_sample.h>
	
	half3 camera_direction = gl_TexCoord[2].xyz;
	
	#ifdef WORLD
		half3 light_direction = gl_TexCoord[1].xyz;
		half3 color = getDiffuse(diffuse.xyz,normal,light_direction);
		color += getSpecularFresnelNormalize(specular,normal,light_direction,camera_direction);
	#else
		half4 light_direction = gl_TexCoord[1];
		half3 color = getDiffuseSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,normal,light_direction,camera_direction);
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#include <core/shaders/terrains/fragment_base_sample.h>
	
	half3 camera_direction = IN.texcoord_2.xyz;
	
	#ifdef WORLD
		half3 light_direction = IN.texcoord_1.xyz;
		half3 color = getDiffuse(diffuse.xyz,normal,light_direction);
		color += getSpecularFresnelNormalize(specular,normal,light_direction,camera_direction);
	#else
		half4 light_direction = IN.texcoord_1;
		half3 color = getDiffuseSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,normal,light_direction,camera_direction);
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#include <core/shaders/terrains/fragment_base_sample.h>
	
	half3 camera_direction = IN.texcoord_2.xyz;
	
	#ifdef WORLD
		half3 light_direction = IN.texcoord_1.xyz;
		half3 color = getDiffuse(diffuse.xyz,normal,light_direction);
		color += getSpecularFresnelNormalize(specular,normal,light_direction,camera_direction);
	#else
		half4 light_direction = IN.texcoord_1;
		half3 color = getDiffuseSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,normal,light_direction,camera_direction);
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#include <core/shaders/terrains/fragment_base_sample.h>
	
	half3 camera_direction = IN.texcoord_2.xyz;
	
	#ifdef WORLD
		half3 light_direction = IN.texcoord_1.xyz;
		half3 color = getDiffuse(diffuse.xyz,normal,light_direction);
		color += getSpecularFresnelNormalize(specular,normal,light_direction,camera_direction);
	#else
		half4 light_direction = IN.texcoord_1;
		half3 color = getDiffuseSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,normal,light_direction,camera_direction);
	#endif
	
#endif
