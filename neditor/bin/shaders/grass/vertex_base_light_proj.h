/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base_light_proj.h
 * Desc:    Grass base light proj shader
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
	
	#ifndef VERTEX_BASE_LIGHT_PROJ
		#define VERTEX_BASE_LIGHT_PROJ
		
		uniform float translucent_scale;
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0].xy = texcoord;
		gl_TexCoord[0].zw = noise;
		
		float3 light_direction = (s_light_position - vertex.xyz) * s_light_iradius.x * s_light_iradius.w;
		float attenuation = getAttenuation(s_light_iradius.w * s_light_iradius.w - dot(light_direction,light_direction));
		gl_TexCoord[1].xyz = s_light_color.xyz * (saturate(dot(light_direction,direction) * (1.0f - translucent_scale) + translucent_scale) * s_material_shading.x * attenuation);
		gl_TexCoord[1].w = alpha;
		
		gl_TexCoord[2] = s_light_projection * vertex;
		
		#ifdef SHADOW
			gl_TexCoord[3] = s_light_shadow_projection * vertex;
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_BASE_LIGHT_PROJ
		#define VERTEX_BASE_LIGHT_PROJ
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			float4 texcoord_2 : TEXCOORD2;
			#ifdef SHADOW
				float4 texcoord_3 : TEXCOORD3;
			#endif
		};
		
		float translucent_scale;
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		float3 light_direction = (s_light_position - vertex.xyz) * s_light_iradius.x * s_light_iradius.w;
		float attenuation = getAttenuation(s_light_iradius.w * s_light_iradius.w - dot(light_direction,light_direction));
		OUT.texcoord_1.xyz = s_light_color.xyz * (saturate(dot(light_direction,direction) * (1.0f - translucent_scale) + translucent_scale) * s_material_shading.x * attenuation);
		OUT.texcoord_1.w = alpha;
		
		OUT.texcoord_2 = mul(s_light_projection,vertex);
		
		#ifdef SHADOW
			OUT.texcoord_3 = mul(s_light_shadow_projection,vertex);
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_BASE_LIGHT_PROJ
		#define VERTEX_BASE_LIGHT_PROJ
		
		struct VERTEX_OUT {
			float4 position : SV_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			float4 texcoord_2 : TEXCOORD2;
			#ifdef SHADOW
				float4 texcoord_3 : TEXCOORD3;
			#endif
		};
		
		cbuffer shader_light_proj_parameters {
			float translucent_scale;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		float3 light_direction = (s_light_position - vertex.xyz) * s_light_iradius.x * s_light_iradius.w;
		float attenuation = getAttenuation(s_light_iradius.w * s_light_iradius.w - dot(light_direction,light_direction));
		OUT.texcoord_1.xyz = s_light_color.xyz * (saturate(dot(light_direction,direction) * (1.0f - translucent_scale) + translucent_scale) * s_material_shading.x * attenuation);
		OUT.texcoord_1.w = alpha;
		
		OUT.texcoord_2 = mul(s_light_projection,vertex);
		
		#ifdef SHADOW
			OUT.texcoord_3 = mul(s_light_shadow_projection,vertex);
		#endif
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_BASE_LIGHT_PROJ
		#define VERTEX_BASE_LIGHT_PROJ
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			float4 texcoord_2 : TEXCOORD2;
			#ifdef SHADOW
				float4 texcoord_3 : TEXCOORD3;
			#endif
		};
		
		uniform float translucent_scale;
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = noise;
		
		float3 light_direction = (s_light_position - vertex.xyz) * s_light_iradius.x * s_light_iradius.w;
		float attenuation = getAttenuation(s_light_iradius.w * s_light_iradius.w - dot(light_direction,light_direction));
		OUT.texcoord_1.xyz = s_light_color.xyz * (saturate(dot(light_direction,direction) * (1.0f - translucent_scale) + translucent_scale) * s_material_shading.x * attenuation);
		OUT.texcoord_1.w = alpha;
		
		OUT.texcoord_2 = mul(s_light_projection,vertex);
		
		#ifdef SHADOW
			OUT.texcoord_3 = mul(s_light_shadow_projection,vertex);
		#endif
		
	#endif
	
#endif
