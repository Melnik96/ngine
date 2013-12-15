/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_surface_refraction.h
 * Desc:    Water surface refraction shader
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
	
	#ifndef VERTEX_SURFACE_REFRACTION
		#define VERTEX_SURFACE_REFRACTION
		
		uniform float4 normal_0_transform;
		uniform float4 normal_1_transform;
		uniform float4 normal_2_transform;
		uniform float4 normal_3_transform;
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0] = float4(texcoord,s_projection[1].y,gl_Position.w);
		
		gl_TexCoord[1].xyz = normal;
		
		gl_TexCoord[2] = direction;
		
		mat3 transform = mat3(s_modelview[0].xyz,s_modelview[1].xyz,s_modelview[2].xyz) * mat3(tangent,binormal,normal);
		gl_TexCoord[3].xyz = float3(transform[0].x,transform[1].x,transform[2].x);
		gl_TexCoord[4].xyz = float3(transform[0].y,transform[1].y,transform[2].y);
		
		gl_TexCoord[5].xy = texcoord * normal_0_transform.xy + normal_0_transform.zw;
		gl_TexCoord[5].zw = texcoord * normal_1_transform.xy + normal_1_transform.zw;
		gl_TexCoord[6].xy = texcoord * normal_2_transform.xy + normal_2_transform.zw;
		gl_TexCoord[6].zw = texcoord * normal_3_transform.xy + normal_3_transform.zw;
		
		gl_TexCoord[7] = getProjection(gl_Position);
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifndef VERTEX_SURFACE_REFRACTION
		#define VERTEX_SURFACE_REFRACTION
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float4 texcoord_2 : TEXCOORD2;
			float3 texcoord_3 : TEXCOORD3;
			float3 texcoord_4 : TEXCOORD4;
			float4 texcoord_5 : TEXCOORD5;
			float4 texcoord_6 : TEXCOORD6;
			float4 texcoord_7 : TEXCOORD7;
		};
		
		float4 normal_0_transform;
		float4 normal_1_transform;
		float4 normal_2_transform;
		float4 normal_3_transform;
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = float4(texcoord,s_projection[1].y,OUT.position.w);
		
		OUT.texcoord_1 = normal;
		
		OUT.texcoord_2 = direction;
		
		float3x3 transform = mul((float3x3)s_modelview,transpose(float3x3(tangent,binormal,normal)));
		OUT.texcoord_3 = transform[0].xyz;
		OUT.texcoord_4 = transform[1].xyz;
		
		OUT.texcoord_5.xy = texcoord * normal_0_transform.xy + normal_0_transform.zw;
		OUT.texcoord_5.zw = texcoord * normal_1_transform.xy + normal_1_transform.zw;
		OUT.texcoord_6.xy = texcoord * normal_2_transform.xy + normal_2_transform.zw;
		OUT.texcoord_6.zw = texcoord * normal_3_transform.xy + normal_3_transform.zw;
		
		OUT.texcoord_7 = getProjection(OUT.position);
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifndef VERTEX_SURFACE_REFRACTION
		#define VERTEX_SURFACE_REFRACTION
		
		struct VERTEX_OUT {
			float4 position : SV_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float4 texcoord_2 : TEXCOORD2;
			float3 texcoord_3 : TEXCOORD3;
			float3 texcoord_4 : TEXCOORD4;
			float4 texcoord_7 : TEXCOORD7;
			float4 texcoord_8 : TEXCOORD8;
		};
		
		cbuffer shader_refraction_parameters {
			float4 normal_0_transform;
			float4 normal_1_transform;
			float4 normal_2_transform;
			float4 normal_3_transform;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0 = float4(texcoord,s_projection[1].y,OUT.position.w);
		
		OUT.texcoord_1 = normal;
		
		OUT.texcoord_2 = direction;
		
		float3x3 transform = mul((float3x3)s_modelview,transpose(float3x3(tangent,binormal,normal)));
		OUT.texcoord_3 = transform[0].xyz;
		OUT.texcoord_4 = transform[1].xyz;
		
		OUT.texcoord_7.xy = texcoord * normal_0_transform.xy + normal_0_transform.zw;
		OUT.texcoord_7.zw = texcoord * normal_1_transform.xy + normal_1_transform.zw;
		OUT.texcoord_8.xy = texcoord * normal_2_transform.xy + normal_2_transform.zw;
		OUT.texcoord_8.zw = texcoord * normal_3_transform.xy + normal_3_transform.zw;
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifndef VERTEX_SURFACE_REFRACTION
		#define VERTEX_SURFACE_REFRACTION
		
		struct VERTEX_OUT {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			float4 texcoord_2 : TEXCOORD2;
			float3 texcoord_3 : TEXCOORD3;
			float3 texcoord_4 : TEXCOORD4;
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
		
		float3x3 transform = mul((float3x3)s_modelview,transpose(float3x3(tangent,binormal,normal)));
		OUT.texcoord_3 = transform[0].xyz;
		OUT.texcoord_4 = transform[1].xyz;
		
		OUT.texcoord_7.xy = texcoord * normal_0_transform.xy + normal_0_transform.zw;
		OUT.texcoord_7.zw = texcoord * normal_1_transform.xy + normal_1_transform.zw;
		OUT.texcoord_8.xy = texcoord * normal_2_transform.xy + normal_2_transform.zw;
		OUT.texcoord_8.zw = texcoord * normal_3_transform.xy + normal_3_transform.zw;
		
		OUT.texcoord_9 = getProjection(OUT.position);
		
	#endif
	
#endif
