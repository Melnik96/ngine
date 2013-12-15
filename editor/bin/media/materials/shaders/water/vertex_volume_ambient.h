/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_volume_ambient.h
 * Desc:    Water volume ambient shader
 * Version: 1.11
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
	
	#ifndef VERTEX_VOLUME_AMBIENT
		#define VERTEX_VOLUME_AMBIENT
		
		uniform float4x4 s_water_projection;
		uniform float4 s_water_plane;
		
		uniform float subsurface_density;
		uniform float subsurface_falloff;
		
	#else
		
		gl_Position = s_water_projection * vertex;
		
		gl_TexCoord[0].xyz = normal;
		
		gl_TexCoord[1] = direction;
		
		#ifdef SUBSURFACE
			gl_TexCoord[2].xyz = -s_water_plane.xyz * s_depth_range.y * subsurface_falloff;
			gl_TexCoord[2].w = -max(-s_water_plane.w,0.0f) * subsurface_falloff;
			gl_TexCoord[3].x = s_depth_range.y * subsurface_density;
		#endif
		
		gl_TexCoord[7] = getProjection(gl_Position);
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_VOLUME_AMBIENT
		#define VERTEX_VOLUME_AMBIENT
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float3 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef SUBSURFACE
				float4 texcoord_2 : TEXCOORD2;
				float1 texcoord_3 : TEXCOORD3;
			#endif
			float4 texcoord_7 : TEXCOORD7;
		};
		
		float4x4 s_water_projection;
		float4 s_water_plane;
		
		float subsurface_density;
		float subsurface_falloff;
		
	#else
		
		OUT.position = mul(s_water_projection,vertex);
		
		OUT.texcoord_0 = normal;
		
		OUT.texcoord_1 = direction;
		
		#ifdef SUBSURFACE
			OUT.texcoord_2.xyz = -s_water_plane.xyz * s_depth_range.y * subsurface_falloff;
			OUT.texcoord_2.w = -max(-s_water_plane.w,0.0f) * subsurface_falloff;
			OUT.texcoord_3.x = s_depth_range.y * subsurface_density;
		#endif
		
		OUT.texcoord_7 = getProjection(OUT.position);
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_VOLUME_AMBIENT
		#define VERTEX_VOLUME_AMBIENT
		
		struct VERTEX_OUT {
			float4 position : SV_POSITION;
			float3 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef SUBSURFACE
				float4 texcoord_2 : TEXCOORD2;
				float1 texcoord_3 : TEXCOORD3;
			#endif
		};
		
		cbuffer shader_water_parameters {
			float4x4 s_water_projection;
			#ifdef SUBSURFACE
				float4 s_water_plane;
			#endif
		};
		
		cbuffer shader_ambient_parameters {
			#ifdef SUBSURFACE
				float subsurface_density;
				float subsurface_falloff;
			#endif
		};
		
	#else
		
		OUT.position = mul(s_water_projection,vertex);
		
		OUT.texcoord_0 = normal;
		
		OUT.texcoord_1 = direction;
		
		#ifdef SUBSURFACE
			OUT.texcoord_2.xyz = -s_water_plane.xyz * s_depth_range.y * subsurface_falloff;
			OUT.texcoord_2.w = -max(-s_water_plane.w,0.0f) * subsurface_falloff;
			OUT.texcoord_3.x = s_depth_range.y * subsurface_density;
		#endif
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_VOLUME_AMBIENT
		#define VERTEX_VOLUME_AMBIENT
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float3 texcoord_0 : TEXCOORD0;
			float4 texcoord_1 : TEXCOORD1;
			#ifdef SUBSURFACE
				float4 texcoord_2 : TEXCOORD2;
				float1 texcoord_3 : TEXCOORD3;
			#endif
			float4 texcoord_9 : TEXCOORD9;
		};
		
		uniform float4x4 s_water_projection;
		uniform float4 s_water_plane;
		
		uniform float subsurface_density;
		uniform float subsurface_falloff;
		
	#else
		
		OUT.position = mul(s_water_projection,vertex);
		
		OUT.texcoord_0 = normal;
		
		OUT.texcoord_1 = direction;
		
		#ifdef SUBSURFACE
			OUT.texcoord_2.xyz = -s_water_plane.xyz * s_depth_range.y * subsurface_falloff;
			OUT.texcoord_2.w = -max(-s_water_plane.w,0.0f) * subsurface_falloff;
			OUT.texcoord_3.x = s_depth_range.y * subsurface_density;
		#endif
		
		OUT.texcoord_9 = getProjection(OUT.position);
		
	#endif
	
#endif
