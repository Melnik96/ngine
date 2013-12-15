/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    evaluate_base_velocity.h
 * Desc:    Mesh base velocity shader
 * Version: 1.01
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
	
	#ifndef EVALUATE_BASE_VELOCITY
		#define EVALUATE_BASE_VELOCITY
		
		uniform float3 s_mesh_center_of_mass;
		
	#else
		
		gl_Position = getPosition(vertex);
		
		gl_TexCoord[0].xy = texcoord;
		gl_TexCoord[0].zw = gl_in[0].gl_TexCoord[0].zw * gl_TessCoord.x + gl_in[1].gl_TexCoord[0].zw * gl_TessCoord.y + gl_in[2].gl_TexCoord[0].zw * gl_TessCoord.z;
		
		gl_TexCoord[1].xyz = vertex.xyz - s_mesh_center_of_mass;
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			gl_TexCoord[7].x = alpha_fade;
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D11
*
\******************************************************************************/

#elif DIRECT3D11
	
	#ifndef EVALUATE_BASE_VELOCITY
		#define EVALUATE_BASE_VELOCITY
		
		struct EVALUATE_IN {
			float4 position : POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float4 texcoord_9 : TEXCOORD9;
		};
		
		struct EVALUATE_OUT {
			float4 position : SV_POSITION;
			float4 texcoord_0 : TEXCOORD0;
			float3 texcoord_1 : TEXCOORD1;
			#ifdef USE_ALPHA_FADE && ALPHA_FADE
				float1 texcoord_9 : TEXCOORD9;
			#endif
		};
		
		cbuffer shader_velocity_parameters {
			float3 s_mesh_center_of_mass;
		};
		
	#else
		
		OUT.position = getPosition(vertex);
		
		OUT.texcoord_0.xy = texcoord;
		OUT.texcoord_0.zw = patch[0].texcoord_0.zw * IN.coords.x + patch[1].texcoord_0.zw * IN.coords.y + patch[2].texcoord_0.zw * IN.coords.z;
		
		OUT.texcoord_1 = vertex.xyz - s_mesh_center_of_mass;
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			OUT.texcoord_9.x = alpha_fade;
		#endif
		
	#endif
	
#endif
