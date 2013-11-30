/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_paint_light.h
 * Desc:    Mesh paint light shader
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
	
	#include <core/shaders/meshes/fragment_paint_sample.h>
	
	#ifdef USE_TESSELLATION && TESSELLATION
		
		half fresnel = getFresnel(world_normal,camera_direction);
		
		#ifdef OMNI || PROJ
			half attenuation = getAttenuate(light_direction);
			half3 color = diffuse.xyz * (saturate(dot(light_direction.xyz,world_normal) * light_direction_ilength) * s_material_shading.x * attenuation);
			color += specular.xyz * (getSpecularPower(light_angle,specular.w * s_material_shading.z) * s_material_shading.y * fresnel * attenuation);
		#elif WORLD
			half3 color = diffuse.xyz * (saturate(dot(light_direction,world_normal)) * s_material_shading.x);
			color += specular.xyz * (getSpecularPower(light_angle,specular.w * s_material_shading.z) * s_material_shading.y * fresnel);
		#endif
	
	#else
		
		half fresnel = getFresnel(normal,camera_direction);
		
		#ifdef OMNI || PROJ
			half attenuation = getAttenuate(gl_TexCoord[1]);
			half3 color = diffuse.xyz * (saturate(dot(light_direction,normal)) * s_material_shading.x * attenuation);
			color += specular.xyz * (getSpecularPower(light_angle,specular.w * s_material_shading.z) * s_material_shading.y * fresnel * attenuation);
		#elif WORLD
			half3 color = diffuse.xyz * (saturate(dot(light_direction,normal)) * s_material_shading.x);
			color += specular.xyz * (getSpecularPower(light_angle,specular.w * s_material_shading.z) * s_material_shading.y * fresnel);
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#include <core/shaders/meshes/fragment_paint_sample.h>
	
	half fresnel = getFresnel(normal,camera_direction);
	
	#ifdef OMNI || PROJ
		half attenuation = getAttenuate(IN.texcoord_1);
		half3 color = diffuse.xyz * (saturate(dot(light_direction,normal)) * s_material_shading.x * attenuation);
		color += specular.xyz * (getSpecularPower(light_angle,specular.w * s_material_shading.z) * s_material_shading.y * fresnel * attenuation);
	#elif WORLD
		half3 color = diffuse.xyz * (saturate(dot(light_direction,normal)) * s_material_shading.x);
		color += specular.xyz * (getSpecularPower(light_angle,specular.w * s_material_shading.z) * s_material_shading.y * fresnel);
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#include <core/shaders/meshes/fragment_paint_sample.h>
	
	#ifdef USE_TESSELLATION && TESSELLATION
		
		half fresnel = getFresnel(world_normal,camera_direction);
		
		#ifdef OMNI || PROJ
			half attenuation = getAttenuate(light_direction);
			half3 color = diffuse.xyz * (saturate(dot(light_direction.xyz,world_normal) * light_direction_ilength) * s_material_shading.x * attenuation);
			color += specular.xyz * (getSpecularPower(light_angle,specular.w * s_material_shading.z) * s_material_shading.y * fresnel * attenuation);
		#elif WORLD
			half3 color = diffuse.xyz * (saturate(dot(light_direction,world_normal)) * s_material_shading.x);
			color += specular.xyz * (getSpecularPower(light_angle,specular.w * s_material_shading.z) * s_material_shading.y * fresnel);
		#endif
	
	#else
		
		half fresnel = getFresnel(normal,camera_direction);
		
		#ifdef OMNI || PROJ
			half attenuation = getAttenuate(IN.texcoord_1);
			half3 color = diffuse.xyz * (saturate(dot(light_direction,normal)) * s_material_shading.x * attenuation);
			color += specular.xyz * (getSpecularPower(light_angle,specular.w * s_material_shading.z) * s_material_shading.y * fresnel * attenuation);
		#elif WORLD
			half3 color = diffuse.xyz * (saturate(dot(light_direction,normal)) * s_material_shading.x);
			color += specular.xyz * (getSpecularPower(light_angle,specular.w * s_material_shading.z) * s_material_shading.y * fresnel);
		#endif
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#include <core/shaders/meshes/fragment_paint_sample.h>
	
	half fresnel = getFresnel(normal,camera_direction);
	
	#ifdef OMNI || PROJ
		half attenuation = getAttenuate(IN.texcoord_1);
		half3 color = diffuse.xyz * (saturate(dot(light_direction,normal)) * s_material_shading.x * attenuation);
		color += specular.xyz * (getSpecularPower(light_angle,specular.w * s_material_shading.z) * s_material_shading.y * fresnel * attenuation);
	#elif WORLD
		half3 color = diffuse.xyz * (saturate(dot(light_direction,normal)) * s_material_shading.x);
		color += specular.xyz * (getSpecularPower(light_angle,specular.w * s_material_shading.z) * s_material_shading.y * fresnel);
	#endif
	
#endif
