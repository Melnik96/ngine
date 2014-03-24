/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base_light_world.h
 * Desc:    Grass base light world shader
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
	
	#ifndef VERTEX_BASE_LIGHT_WORLD
		#define VERTEX_BASE_LIGHT_WORLD
		
		uniform float translucent_scale;
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0].xy = texcoord;
		gl_TexCoord[0].zw = noise;
		
		gl_TexCoord[1].xyz = s_light_color.xyz * (saturate(dot(s_light_direction,direction) * (1.0f - translucent_scale) + translucent_scale) *s_material_shading.x);
		gl_TexCoord[1].w = alpha;
		
		#ifdef SHADOW
			gl_TexCoord[2].xyz = (s_light_shadow_projections[0] * vertex).xyz;
			gl_TexCoord[3].xyz = (s_light_shadow_projections[1] * vertex).xyz;
			gl_TexCoord[4].xyz = (s_light_shadow_projections[2] * vertex).xyz;
			gl_TexCoord[5].xyz = (s_light_shadow_projections[3] * vertex).xyz;
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_BASE_LIGHT_WORLD
		#define VERTEX_BASE_LIGHT_WORLD
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef SHADOW
				float3 texcoord_2 : TEXCOORD2;
				float3 texcoord_3 : TEXCOORD3;
				float3 texcoord_4 : TEXCOORD4;
				float3 texcoord_5 : TEXCOORD5;
			#endif
		};
		
		float translucent_scale;
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		OUT.texcoord_1.xyz = s_light_color.xyz * (saturate(dot(s_light_direction,direction) * (1.0f - translucent_scale) + translucent_scale) * s_material_shading.x);
		OUT.texcoord_1.w = alpha;
		
		#ifdef SHADOW
			OUT.texcoord_2 = mul(s_light_shadow_projections[0],vertex).xyz;
			OUT.texcoord_3 = mul(s_light_shadow_projections[1],vertex).xyz;
			OUT.texcoord_4 = mul(s_light_shadow_projections[2],vertex).xyz;
			OUT.texcoord_5 = mul(s_light_shadow_projections[3],vertex).xyz;
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_BASE_LIGHT_WORLD
		#define VERTEX_BASE_LIGHT_WORLD
		
		struct VERTEX_OUT {
			float4 position : SV_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef SHADOW
				float3 texcoord_2 : TEXCOORD2;
				float3 texcoord_3 : TEXCOORD3;
				float3 texcoord_4 : TEXCOORD4;
				float3 texcoord_5 : TEXCOORD5;
			#endif
		};
		
		cbuffer shader_light_omni_parameters {
			float translucent_scale;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		OUT.texcoord_1.xyz = s_light_color.xyz * (saturate(dot(s_light_direction,direction) * (1.0f - translucent_scale) + translucent_scale) * s_material_shading.x);
		OUT.texcoord_1.w = alpha;
		
		#ifdef SHADOW
			OUT.texcoord_2 = mul(s_light_shadow_projections[0],vertex).xyz;
			OUT.texcoord_3 = mul(s_light_shadow_projections[1],vertex).xyz;
			OUT.texcoord_4 = mul(s_light_shadow_projections[2],vertex).xyz;
			OUT.texcoord_5 = mul(s_light_shadow_projections[3],vertex).xyz;
		#endif
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_BASE_LIGHT_WORLD
		#define VERTEX_BASE_LIGHT_WORLD
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef SHADOW
				float3 texcoord_2 : TEXCOORD2;
				float3 texcoord_3 : TEXCOORD3;
				float3 texcoord_4 : TEXCOORD4;
				float3 texcoord_5 : TEXCOORD5;
			#endif
		};
		
		float translucent_scale;
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		OUT.texcoord_1.xyz = s_light_color.xyz * (saturate(dot(s_light_direction,direction) * (1.0f - translucent_scale) + translucent_scale) * s_material_shading.x);
		OUT.texcoord_1.w = alpha;
		
		#ifdef SHADOW
			OUT.texcoord_2 = mul(s_light_shadow_projections[0],vertex).xyz;
			OUT.texcoord_3 = mul(s_light_shadow_projections[1],vertex).xyz;
			OUT.texcoord_4 = mul(s_light_shadow_projections[2],vertex).xyz;
			OUT.texcoord_5 = mul(s_light_shadow_projections[3],vertex).xyz;
		#endif
		
	#endif
	
#endif
