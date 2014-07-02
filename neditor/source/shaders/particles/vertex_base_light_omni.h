/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base_light_omni.shader
 * Desc:    Particles base light omni shader
 * Version: 1.15
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
	
	#ifndef VERTEX_BASE_LIGHT_OMNI
		#define VERTEX_BASE_LIGHT_OMNI
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0] = texcoord;
		
		gl_TexCoord[1] = color * s_light_color;
		
		#ifdef VOLUME
			gl_TexCoord[2] = volume;
			gl_TexCoord[7] = getProjection(gl_Position);
		#endif
		
		gl_TexCoord[3].xyz = getOmniRadius(s_light_position - vertex.xyz) * s_light_iradius.w;
		gl_TexCoord[3].w = s_light_iradius.w * s_light_iradius.w;
		
		gl_TexCoord[4] = float4(vertex.xyz - s_light_position,0.0f) * s_light_transform;
		
		#ifdef SHADOW
			gl_TexCoord[5].xyz = (vertex.xyz - s_light_shadow_offset) * s_light_shadow_depth_range.x;
			gl_TexCoord[5].w = s_light_shadow_depth_range.y;
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_BASE_LIGHT_OMNI
		#define VERTEX_BASE_LIGHT_OMNI
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef VOLUME
				float4 texcoord_2 : TEXCOORD2;
				float4 texcoord_7 : TEXCOORD7;
			#endif
			float4 texcoord_3 : TEXCOORD3;
			float3 texcoord_4 : TEXCOORD4;
			#ifdef SHADOW
				float4 texcoord_5 : TEXCOORD5;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = color * s_light_color;
		
		#ifdef VOLUME
			OUT.texcoord_2 = volume;
			OUT.texcoord_7 = getProjection(OUT.position);
		#endif
		
		OUT.texcoord_3.xyz = getOmniRadius(s_light_position - vertex.xyz) * s_light_iradius.w;
		OUT.texcoord_3.w = s_light_iradius.w * s_light_iradius.w;
		
		OUT.texcoord_4 = mul(vertex.xyz - s_light_position,(float3x3)s_light_transform);
		
		#ifdef SHADOW
			OUT.texcoord_5.xyz = (vertex.xyz - s_light_shadow_offset) * s_light_shadow_depth_range.x;
			OUT.texcoord_5.w = s_light_shadow_depth_range.y;
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_BASE_LIGHT_OMNI
		#define VERTEX_BASE_LIGHT_OMNI
		
		struct VERTEX_OUT {
			float4 position : SV_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef VOLUME
				float4 texcoord_2 : TEXCOORD2;
			#endif
			float4 texcoord_3 : TEXCOORD3;
			float3 texcoord_4 : TEXCOORD4;
			#ifdef SHADOW
				float4 texcoord_5 : TEXCOORD5;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = color * s_light_color;
		
		#ifdef VOLUME
			OUT.texcoord_2 = volume;
		#endif
		
		OUT.texcoord_3.xyz = getOmniRadius(s_light_position - vertex.xyz) * s_light_iradius.w;
		OUT.texcoord_3.w = s_light_iradius.w * s_light_iradius.w;
		
		OUT.texcoord_4 = mul(vertex.xyz - s_light_position,(float3x3)s_light_transform);
		
		#ifdef SHADOW
			OUT.texcoord_5.xyz = (vertex.xyz - s_light_shadow_offset) * s_light_shadow_depth_range.x;
			OUT.texcoord_5.w = s_light_shadow_depth_range.y;
		#endif
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_BASE_LIGHT_OMNI
		#define VERTEX_BASE_LIGHT_OMNI
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef VOLUME
				float4 texcoord_2 : TEXCOORD2;
				float4 texcoord_9 : TEXCOORD9;
			#endif
			float4 texcoord_3 : TEXCOORD3;
			float3 texcoord_4 : TEXCOORD4;
			#ifdef SHADOW
				float4 texcoord_5 : TEXCOORD5;
			#endif
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = texcoord;
		
		OUT.texcoord_1 = color * s_light_color;
		
		#ifdef VOLUME
			OUT.texcoord_2 = volume;
			OUT.texcoord_9 = getProjection(OUT.position);
		#endif
		
		OUT.texcoord_3.xyz = getOmniRadius(s_light_position - vertex.xyz) * s_light_iradius.w;
		OUT.texcoord_3.w = s_light_iradius.w * s_light_iradius.w;
		
		OUT.texcoord_4 = mul(vertex.xyz - s_light_position,(float3x3)s_light_transform);
		
		#ifdef SHADOW
			OUT.texcoord_5.xyz = (vertex.xyz - s_light_shadow_offset) * s_light_shadow_depth_range.x;
			OUT.texcoord_5.w = s_light_shadow_depth_range.y;
		#endif
		
	#endif
	
#endif
