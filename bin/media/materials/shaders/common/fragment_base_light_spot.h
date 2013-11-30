/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_light_spot.h
 * Desc:    Base light spot shader
 * Version: 1.07
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
	
	half3 camera_direction = normalize(gl_TexCoord[2].xyz);
	
	half3 world_normal;
	world_normal.x = dot(half3(gl_TexCoord[3].xyz),normal);
	world_normal.y = dot(half3(gl_TexCoord[4].xyz),normal);
	world_normal.z = dot(half3(gl_TexCoord[5].xyz),normal);
	
	half3 color = half3(0.0f);
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - gl_TexCoord[1].xyz) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half3 light = diffuse.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength) * s_material_shadings[NUMBER].x); \
		light += specular.xyz * (getSpecularPower(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength,specular.w * s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
		color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	half3 camera_direction = normalize(IN.texcoord_2);
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_3,normal);
	world_normal.y = dot(IN.texcoord_4,normal);
	world_normal.z = dot(IN.texcoord_5,normal);
	
	half3 color = 0.0f;
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - IN.texcoord_1) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half3 light = diffuse.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength) * s_material_shadings[NUMBER].x); \
		light += specular.xyz * (getSpecularPower(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength,specular.w * s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
		color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	half3 camera_direction = normalize(IN.texcoord_2);
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_3,normal);
	world_normal.y = dot(IN.texcoord_4,normal);
	world_normal.z = dot(IN.texcoord_5,normal);
	
	half3 color = 0.0f;
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - IN.texcoord_1) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half3 light = diffuse.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength) * s_material_shadings[NUMBER].x); \
		light += specular.xyz * (getSpecularPower(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength,specular.w * s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
		color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	half3 camera_direction = normalize(IN.texcoord_2);
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_3,normal);
	world_normal.y = dot(IN.texcoord_4,normal);
	world_normal.z = dot(IN.texcoord_5,normal);
	
	half3 color = 0.0f;
	
	#define LIGHT(NUMBER,SWIZZLE) { \
		half3 light_direction = (s_light_positions[NUMBER].xyz - IN.texcoord_1) * s_light_iradiuses. ## SWIZZLE; \
		half light_direction_length2 = dot(light_direction,light_direction); \
		half light_direction_ilength = rsqrt(light_direction_length2); \
		half light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - light_direction_length2); \
		half3 light = diffuse.xyz * (saturate(dot(light_direction,world_normal) * light_direction_ilength) * s_material_shadings[NUMBER].x); \
		light += specular.xyz * (getSpecularPower(dot(reflect(-light_direction,world_normal),camera_direction) * light_direction_ilength,specular.w * s_material_shadings[NUMBER].z) * s_material_shadings[NUMBER].y); \
		color += light * s_light_colors[NUMBER].xyz * light_attenuation; \
	}
	
	LIGHT(0,x)
	LIGHT(1,y)
	LIGHT(2,z)
	LIGHT(3,w)
	
#endif
