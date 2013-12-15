/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_surface_light_proj.h
 * Desc:    Water surface light proj shader
 * Version: 1.08
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
	
	#ifndef VERTEX_SURFACE_LIGHT_PROJ
		#define VERTEX_SURFACE_LIGHT_PROJ
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0] = float4(texcoord,s_projection[1].y,gl_Position.w);
		
		gl_TexCoord[1].xyz = normal;
		
		gl_TexCoord[2] = direction;
		
		float3 light_direction = (s_light_position - vertex.xyz) * s_light_iradius.x * s_light_iradius.w;
		gl_TexCoord[3].x = dot(light_direction,tangent);
		gl_TexCoord[3].y = dot(light_direction,binormal);
		gl_TexCoord[3].z = dot(light_direction,normal) * s_light_front;
		gl_TexCoord[3].w = s_light_iradius.w * s_light_iradius.w;
		
		float3 camera_direction = s_camera_position - vertex.xyz;
		gl_TexCoord[4].x = dot(camera_direction,tangent);
		gl_TexCoord[4].y = dot(camera_direction,binormal);
		gl_TexCoord[4].z = dot(camera_direction,normal) * s_light_front;
		
		gl_TexCoord[5] = s_light_projection * vertex;
		
		#ifdef SHADOW
			gl_TexCoord[6] = s_light_shadow_projection * vertex;
		#endif
		
		gl_TexCoord[7] = getProjection(gl_Position);
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_SURFACE_LIGHT_PROJ
		#define VERTEX_SURFACE_LIGHT_PROJ
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float4 texcoord_2 : TEXCOORD2;
			float4 texcoord_3 : TEXCOORD3;
			float3 texcoord_4 : TEXCOORD4;
			float4 texcoord_5 : TEXCOORD5;
			#ifdef SHADOW
				float4 texcoord_6 : TEXCOORD6;
			#endif
			float4 texcoord_7 : TEXCOORD7;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = float4(texcoord,s_projection[1].y,OUT.position.w);
		
		OUT.texcoord_1 = normal;
		
		OUT.texcoord_2 = direction;
		
		float3 light_direction = (s_light_position - vertex.xyz) * s_light_iradius.x * s_light_iradius.w;
		OUT.texcoord_3.x = dot(light_direction,tangent);
		OUT.texcoord_3.y = dot(light_direction,binormal);
		OUT.texcoord_3.z = dot(light_direction,normal) * s_light_front;
		OUT.texcoord_3.w = s_light_iradius.w * s_light_iradius.w;
		
		float3 camera_direction = s_camera_position - vertex.xyz;
		OUT.texcoord_4.x = dot(camera_direction,tangent);
		OUT.texcoord_4.y = dot(camera_direction,binormal);
		OUT.texcoord_4.z = dot(camera_direction,normal) * s_light_front;
		
		OUT.texcoord_5 = mul(s_light_projection,vertex);
		
		#ifdef SHADOW
			OUT.texcoord_6 = mul(s_light_shadow_projection,vertex);
		#endif
		
		OUT.texcoord_7 = getProjection(OUT.position);
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_SURFACE_LIGHT_PROJ
		#define VERTEX_SURFACE_LIGHT_PROJ
		
		struct VERTEX_OUT {
			float4 position : SV_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float4 texcoord_2 : TEXCOORD2;
			float4 texcoord_3 : TEXCOORD3;
			float3 texcoord_4 : TEXCOORD4;
			float4 texcoord_5 : TEXCOORD5;
			#ifdef SHADOW
				float4 texcoord_6 : TEXCOORD6;
			#endif
			float4 texcoord_7 : TEXCOORD7;
			float4 texcoord_8 : TEXCOORD8;
			float4 texcoord_9 : TEXCOORD9;
		};
		
		cbuffer shader_light_proj_parameters {
			float4 normal_0_transform;
			float4 normal_1_transform;
			float4 normal_2_transform;
			float4 normal_3_transform;
			float4 foam_0_transform;
			float4 foam_1_transform;
		};
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = float4(texcoord,s_projection[1].y,OUT.position.w);
		
		OUT.texcoord_1 = normal;
		
		OUT.texcoord_2 = direction;
		
		float3 light_direction = (s_light_position - vertex.xyz) * s_light_iradius.x * s_light_iradius.w;
		OUT.texcoord_3.x = dot(light_direction,tangent);
		OUT.texcoord_3.y = dot(light_direction,binormal);
		OUT.texcoord_3.z = dot(light_direction,normal) * s_light_front;
		OUT.texcoord_3.w = s_light_iradius.w * s_light_iradius.w;
		
		float3 camera_direction = s_camera_position - vertex.xyz;
		OUT.texcoord_4.x = dot(camera_direction,tangent);
		OUT.texcoord_4.y = dot(camera_direction,binormal);
		OUT.texcoord_4.z = dot(camera_direction,normal) * s_light_front;
		
		OUT.texcoord_5 = mul(s_light_projection,vertex);
		
		#ifdef SHADOW
			OUT.texcoord_6 = mul(s_light_shadow_projection,vertex);
		#endif
		
		OUT.texcoord_7.xy = texcoord * normal_0_transform.xy + normal_0_transform.zw;
		OUT.texcoord_7.zw = texcoord * normal_1_transform.xy + normal_1_transform.zw;
		OUT.texcoord_8.xy = texcoord * normal_2_transform.xy + normal_2_transform.zw;
		OUT.texcoord_8.zw = texcoord * normal_3_transform.xy + normal_3_transform.zw;
		
		OUT.texcoord_9.xy = texcoord * foam_0_transform.xy + foam_0_transform.zw;
		OUT.texcoord_9.zw = texcoord * foam_1_transform.xy + foam_1_transform.zw;
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_SURFACE_LIGHT_PROJ
		#define VERTEX_SURFACE_LIGHT_PROJ
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float4 texcoord_2 : TEXCOORD2;
			float4 texcoord_3 : TEXCOORD3;
			float3 texcoord_4 : TEXCOORD4;
			float4 texcoord_5 : TEXCOORD5;
			#ifdef SHADOW
				float4 texcoord_6 : TEXCOORD6;
			#endif
			float4 texcoord_7 : TEXCOORD7;
			float4 texcoord_8 : TEXCOORD8;
			float4 texcoord_9 : TEXCOORD9;
		};
		
		uniform float4 normal_0_transform;
		uniform float4 normal_1_transform;
		uniform float4 normal_2_transform;
		uniform float4 normal_3_transform;
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = float4(texcoord,s_projection[1].y,OUT.position.w);
		
		OUT.texcoord_1 = normal;
		
		OUT.texcoord_2 = direction;
		
		float3 light_direction = (s_light_position - vertex.xyz) * s_light_iradius.x * s_light_iradius.w;
		OUT.texcoord_3.x = dot(light_direction,tangent);
		OUT.texcoord_3.y = dot(light_direction,binormal);
		OUT.texcoord_3.z = dot(light_direction,normal) * s_light_front;
		OUT.texcoord_3.w = s_light_iradius.w * s_light_iradius.w;
		
		float3 camera_direction = s_camera_position - vertex.xyz;
		OUT.texcoord_4.x = dot(camera_direction,tangent);
		OUT.texcoord_4.y = dot(camera_direction,binormal);
		OUT.texcoord_4.z = dot(camera_direction,normal) * s_light_front;
		
		OUT.texcoord_5 = mul(s_light_projection,vertex);
		
		#ifdef SHADOW
			OUT.texcoord_6 = mul(s_light_shadow_projection,vertex);
		#endif
		
		OUT.texcoord_7.xy = texcoord * normal_0_transform.xy + normal_0_transform.zw;
		OUT.texcoord_7.zw = texcoord * normal_1_transform.xy + normal_1_transform.zw;
		OUT.texcoord_8.xy = texcoord * normal_2_transform.xy + normal_2_transform.zw;
		OUT.texcoord_8.zw = texcoord * normal_3_transform.xy + normal_3_transform.zw;
		
		OUT.texcoord_9 = getProjection(OUT.position);
		
	#endif
	
#endif
