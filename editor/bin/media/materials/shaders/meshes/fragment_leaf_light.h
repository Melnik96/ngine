/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_leaf_light.h
 * Desc:    Mesh leaf light shader
 * Version: 1.14
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
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	#ifdef WORLD
		half3 light_direction = gl_TexCoord[1].xyz;
	#else
		half4 light_direction = gl_TexCoord[1];
		half light_direction_length2 = dot(light_direction.xyz,light_direction.xyz);
		half light_direction_ilength = rsqrt(light_direction_length2);
		#ifdef QUALITY_MEDIUM && PHONG
			light_direction.xyz *= light_direction_ilength;
		#else
			light_direction.z *= light_direction_ilength;
		#endif
	#endif
	
	half thickness = texture2D(s_texture_1,gl_TexCoord[0].xy).x;
	half offset = saturate(translucent_scale - thickness * thickness_scale);
	
	#ifdef QUALITY_MEDIUM && PHONG
		half3 normal = texture2DNormal(s_texture_2,gl_TexCoord[0].xy);
		half4 specular = texture2D(s_texture_3,gl_TexCoord[0].xy);
		
		half3 camera_direction = gl_TexCoord[2].xyz;
		half3 color = diffuse.xyz * (saturate(dot(light_direction.xyz,normal) * (1.0f - offset) + offset) * s_material_shading.x);
		color += getSpecularNormalize(specular.xyz,normal,light_direction.xyz,camera_direction);
	#else
		half3 color = diffuse.xyz * (saturate(light_direction.z * (1.0f - offset) + offset) * s_material_shading.x);
	#endif
	
	#ifndef WORLD
		half attenuation = getAttenuation(light_direction.w - light_direction_length2);
		color *= attenuation;
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	#ifdef WORLD
		half3 light_direction = IN.texcoord_1.xyz;
	#else
		half4 light_direction = IN.texcoord_1;
		half light_direction_length2 = dot(light_direction.xyz,light_direction.xyz);
		half light_direction_ilength = rsqrt(light_direction_length2);
		#ifdef QUALITY_MEDIUM && PHONG
			light_direction.xyz *= light_direction_ilength;
		#else
			light_direction.z *= light_direction_ilength;
		#endif
	#endif
	
	half thickness = tex2D(s_texture_1,IN.texcoord_0.xy).x;
	half offset = saturate(translucent_scale - thickness * thickness_scale);
	
	#ifdef QUALITY_MEDIUM && PHONG
		half3 normal = tex2DNormal(s_texture_2,IN.texcoord_0.xy);
		half4 specular = tex2D(s_texture_3,IN.texcoord_0.xy);
		
		half3 camera_direction = IN.texcoord_2.xyz;
		half3 color = diffuse.xyz * (saturate(dot(light_direction.xyz,normal) * (1.0f - offset) + offset) * s_material_shading.x);
		color += getSpecularNormalize(specular.xyz,normal,light_direction.xyz,camera_direction);
	#else
		half3 color = diffuse.xyz * (saturate(light_direction.z * (1.0f - offset) + offset) * s_material_shading.x);
	#endif
	
	#ifndef WORLD
		half attenuation = getAttenuation(light_direction.w - light_direction_length2);
		color *= attenuation;
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	#ifdef WORLD
		half3 light_direction = IN.texcoord_1.xyz;
	#else
		half4 light_direction = IN.texcoord_1;
		half light_direction_length2 = dot(light_direction.xyz,light_direction.xyz);
		half light_direction_ilength = rsqrt(light_direction_length2);
		#ifdef QUALITY_MEDIUM && PHONG
			light_direction.xyz *= light_direction_ilength;
		#else
			light_direction.z *= light_direction_ilength;
		#endif
	#endif
	
	half thickness = s_texture_1.Sample(s_sampler_1,IN.texcoord_0.xy).x;
	half offset = saturate(translucent_scale - thickness * thickness_scale);
	
	#ifdef QUALITY_MEDIUM && PHONG
		half3 normal = texture2DNormal(s_texture_2,s_sampler_2,IN.texcoord_0.xy);
		half4 specular = s_texture_3.Sample(s_sampler_3,IN.texcoord_0.xy);
		
		half3 camera_direction = IN.texcoord_2.xyz;
		half3 color = diffuse.xyz * (saturate(dot(light_direction.xyz,normal) * (1.0f - offset) + offset) * s_material_shading.x);
		color += getSpecularNormalize(specular.xyz,normal,light_direction.xyz,camera_direction);
	#else
		half3 color = diffuse.xyz * (saturate(light_direction.z * (1.0f - offset) + offset) * s_material_shading.x);
	#endif
	
	#ifndef WORLD
		half attenuation = getAttenuation(light_direction.w - light_direction_length2);
		color *= attenuation;
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#include <core/shaders/meshes/fragment_leaf_sample.h>
	
	#ifdef WORLD
		half3 light_direction = IN.texcoord_1.xyz;
	#else
		half4 light_direction = IN.texcoord_1;
		half light_direction_length2 = dot(light_direction.xyz,light_direction.xyz);
		half light_direction_ilength = rsqrt(light_direction_length2);
		#ifdef QUALITY_MEDIUM && PHONG
			light_direction.xyz *= light_direction_ilength;
		#else
			light_direction.z *= light_direction_ilength;
		#endif
	#endif
	
	half thickness = h1tex2D(s_texture_1,IN.texcoord_0.xy);
	half offset = saturate(translucent_scale - thickness * thickness_scale);
	
	#ifdef QUALITY_MEDIUM && PHONG
		half3 normal = tex2DNormal(s_texture_2,IN.texcoord_0.xy);
		half4 specular = h4tex2D(s_texture_3,IN.texcoord_0.xy);
		
		half3 camera_direction = IN.texcoord_2.xyz;
		half3 color = diffuse.xyz * (saturate(dot(light_direction.xyz,normal) * (1.0f - offset) + offset) * s_material_shading.x);
		color += getSpecularNormalize(specular.xyz,normal,light_direction.xyz,camera_direction);
	#else
		half3 color = diffuse.xyz * (saturate(light_direction.z * (1.0f - offset) + offset) * s_material_shading.x);
	#endif
	
	#ifndef WORLD
		half attenuation = getAttenuation(light_direction.w - light_direction_length2);
		color *= attenuation;
	#endif
	
#endif
