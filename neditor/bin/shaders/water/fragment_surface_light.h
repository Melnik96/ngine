/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_surface_light.h
 * Desc:    Water surface light shader
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
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	#ifdef WORLD
		half3 light_direction = gl_TexCoord[3].xyz;
	#else
		half3 light_direction = normalize(half3(gl_TexCoord[3].xyz));
	#endif
	half3 camera_direction = normalize(gl_TexCoord[4].xyz);
	
	half fresnel = getFresnel(normal,camera_direction);
	
	half3 color = getDiffuse(surface_color.xyz,normal,light_direction) * (1.0f - fresnel);
	
	color += getSpecular(reflection_color.xyz,normal,light_direction,camera_direction);
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	#ifdef WORLD
		half3 light_direction = IN.texcoord_3;
	#else
		half3 light_direction = normalize(IN.texcoord_3.xyz);
	#endif
	half3 camera_direction = normalize(IN.texcoord_4);
	
	half fresnel = getFresnel(normal,camera_direction);
	
	half3 color = getDiffuse(surface_color.xyz,normal,light_direction) * (1.0f - fresnel);
	
	color += getSpecular(reflection_color.xyz,normal,light_direction,camera_direction);
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	#ifdef WORLD
		half3 light_direction = IN.texcoord_3;
	#else
		half3 light_direction = normalize(IN.texcoord_3.xyz);
	#endif
	half3 camera_direction = normalize(IN.texcoord_4.xyz);
	
	half fresnel = getFresnel(normal,camera_direction);
	
	half3 color = getDiffuse(surface_color.xyz,normal,light_direction) * (1.0f - fresnel);
	
	color += getSpecular(reflection_color.xyz,normal,light_direction,camera_direction);
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#include <core/shaders/water/fragment_surface_normal.h>
	
	#ifdef WORLD
		half3 light_direction = IN.texcoord_3;
	#else
		half3 light_direction = normalize(IN.texcoord_3.xyz);
	#endif
	half3 camera_direction = normalize(IN.texcoord_4);
	
	half fresnel = getFresnel(normal,camera_direction);
	
	half3 color = getDiffuse(surface_color.xyz,normal,light_direction) * (1.0f - fresnel);
	
	color += getSpecular(reflection_color.xyz,normal,light_direction,camera_direction);
	
#endif
