/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_light_prob.h
 * Desc:    Base light prob shader
 * Version: 1.01
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
	
	half3 world_normal;
	world_normal.x = dot(half3(gl_TexCoord[2].xyz),normal);
	world_normal.y = dot(half3(gl_TexCoord[3].xyz),normal);
	world_normal.z = dot(half3(gl_TexCoord[4].xyz),normal);
	
	half3 color = diffuse.xyz * getEnvironment(world_normal) * s_material_shading.x;
	
	#ifdef QUALITY_MEDIUM
		half3 camera_direction = normalize(gl_TexCoord[1].xyz);
		color += specular.xyz * getEnvironment(reflect(-camera_direction,world_normal)) * s_material_shading.y;
		color *= 0.5f;
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_2,normal);
	world_normal.y = dot(IN.texcoord_3,normal);
	world_normal.z = dot(IN.texcoord_4,normal);
	
	half3 color = diffuse.xyz * getEnvironment(world_normal) * s_material_shading.x;
	
	#ifdef QUALITY_MEDIUM
		half3 camera_direction = normalize(IN.texcoord_1);
		color += specular.xyz * getEnvironment(reflect(-camera_direction,world_normal)) * s_material_shading.y;
		color *= 0.5f;
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_2,normal);
	world_normal.y = dot(IN.texcoord_3,normal);
	world_normal.z = dot(IN.texcoord_4,normal);
	
	half3 color = diffuse.xyz * getEnvironment(world_normal) * s_material_shading.x;
	
	#ifdef QUALITY_MEDIUM
		half3 camera_direction = normalize(IN.texcoord_1);
		color += specular.xyz * getEnvironment(reflect(-camera_direction,world_normal)) * s_material_shading.y;
		color *= 0.5f;
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_2,normal);
	world_normal.y = dot(IN.texcoord_3,normal);
	world_normal.z = dot(IN.texcoord_4,normal);
	
	half3 color = diffuse.xyz * getEnvironment(world_normal) * s_material_shading.x;
	
	#ifdef QUALITY_MEDIUM
		half3 camera_direction = normalize(IN.texcoord_1);
		color += specular.xyz * getEnvironment(reflect(-camera_direction,world_normal)) * s_material_shading.y;
		color *= 0.5f;
	#endif
	
#endif
