/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base_light_spot.h
 * Desc:    Grass base light spot shader
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
	
	#ifndef VERTEX_BASE_LIGHT_SPOT
		#define VERTEX_BASE_LIGHT_SPOT
		
		uniform float translucent_scale;
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0].xy = texcoord;
		gl_TexCoord[0].zw = noise;
		
		float3 light_color = float3(0.0f);
		
		#define LIGHT(NUMBER,SWIZZLE) { \
			float3 light_direction = (s_light_positions[NUMBER].xyz - vertex.xyz) * s_light_iradiuses. ## SWIZZLE; \
			float light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - dot(light_direction,light_direction)); \
			light_color += s_light_colors[NUMBER].xyz * (saturate(dot(normalize(light_direction),direction) * (1.0f - translucent_scale) + translucent_scale) * s_material_shadings[NUMBER].x * light_attenuation); \
		}
		
		LIGHT(0,x)
		LIGHT(1,y)
		LIGHT(2,z)
		LIGHT(3,w)
		
		gl_TexCoord[1].xyz = light_color;
		gl_TexCoord[1].w = alpha;
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_BASE_LIGHT_SPOT
		#define VERTEX_BASE_LIGHT_SPOT
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
		};
		
		float translucent_scale;
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		float3 light_color = 0.0f;
		
		#define LIGHT(NUMBER,SWIZZLE) { \
			float3 light_direction = (s_light_positions[NUMBER].xyz - vertex.xyz) * s_light_iradiuses. ## SWIZZLE; \
			float light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - dot(light_direction,light_direction)); \
			light_color += s_light_colors[NUMBER].xyz * (saturate(dot(normalize(light_direction),direction) * (1.0f - translucent_scale) + translucent_scale) * s_material_shadings[NUMBER].x * light_attenuation); \
		}
		
		LIGHT(0,x)
		LIGHT(1,y)
		LIGHT(2,z)
		LIGHT(3,w)
		
		OUT.texcoord_1.xyz = light_color;
		OUT.texcoord_1.w = alpha;
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_BASE_LIGHT_SPOT
		#define VERTEX_BASE_LIGHT_SPOT
		
		struct VERTEX_OUT {
			float4 position : SV_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
		};
		
		cbuffer shader_light_omni_parameters {
			float translucent_scale;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		float3 light_color = 0.0f;
		
		#define LIGHT(NUMBER,SWIZZLE) { \
			float3 light_direction = (s_light_positions[NUMBER].xyz - vertex.xyz) * s_light_iradiuses. ## SWIZZLE; \
			float light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - dot(light_direction,light_direction)); \
			light_color += s_light_colors[NUMBER].xyz * (saturate(dot(normalize(light_direction),direction) * (1.0f - translucent_scale) + translucent_scale) * s_material_shadings[NUMBER].x * light_attenuation); \
		}
		
		LIGHT(0,x)
		LIGHT(1,y)
		LIGHT(2,z)
		LIGHT(3,w)
		
		OUT.texcoord_1.xyz = light_color;
		OUT.texcoord_1.w = alpha;
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_BASE_LIGHT_SPOT
		#define VERTEX_BASE_LIGHT_SPOT
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
		};
		
		uniform float translucent_scale;
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		float3 light_color = 0.0f;
		
		#define LIGHT(NUMBER,SWIZZLE) { \
			float3 light_direction = (s_light_positions[NUMBER].xyz - vertex.xyz) * s_light_iradiuses. ## SWIZZLE; \
			float light_attenuation = getAttenuation(s_light_attenuations. ## SWIZZLE - dot(light_direction,light_direction)); \
			light_color += s_light_colors[NUMBER].xyz * (saturate(dot(normalize(light_direction),direction) * (1.0f - translucent_scale) + translucent_scale) * s_material_shadings[NUMBER].x * light_attenuation); \
		}
		
		LIGHT(0,x)
		LIGHT(1,y)
		LIGHT(2,z)
		LIGHT(3,w)
		
		OUT.texcoord_1.xyz = light_color;
		OUT.texcoord_1.w = alpha;
		
	#endif
	
#endif
