/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_surface_foam.h
 * Desc:    Water surface foam shader
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
	
	#ifdef QUALITY_MEDIUM
		#ifdef FOAM
			
			half foam_0 = texture2D(s_texture_2,gl_TexCoord[0].xy * foam_0_transform.xy + foam_0_transform.zw).x;
			half foam_1 = texture2D(s_texture_2,gl_TexCoord[0].xy * foam_1_transform.xy + foam_1_transform.zw).x;
			
			half height = abs(dot(half3(gl_TexCoord[1].xyz),half3(gl_TexCoord[2].xyz)) * depth * s_depth_range.y / distance) * foam_falloff;
			half foam = saturate(foam_0 + foam_1 - foam_threshold - height) * foam_scale * exp2(-height);
			
			#ifdef OMNI || PROJ || WORLD
				foam *= s_material_shading.x;
			#endif
			
			color = color * (1.0f - foam) + foam;
			
		#endif
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifdef QUALITY_MEDIUM
		#ifdef FOAM
			
			half foam_0 = tex2D(s_texture_2,IN.texcoord_0.xy * foam_0_transform.xy + foam_0_transform.zw).x;
			half foam_1 = tex2D(s_texture_2,IN.texcoord_0.xy * foam_1_transform.xy + foam_1_transform.zw).x;
			
			half height = abs(dot(IN.texcoord_1,IN.texcoord_2.xyz) * depth * s_depth_range.y / distance) * foam_falloff;
			half foam = saturate(foam_0 + foam_1 - foam_threshold - height) * foam_scale * exp2(-height);
			
			#ifdef OMNI || PROJ || WORLD
				foam *= s_material_shading.x;
			#endif
			
			color = color * (1.0f - foam) + foam;
			
		#endif
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifdef QUALITY_MEDIUM
		#ifdef FOAM
			
			half foam_0 = s_texture_2.Sample(s_sampler_2,IN.texcoord_9.xy).x;
			half foam_1 = s_texture_2.Sample(s_sampler_2,IN.texcoord_9.zw).x;
			
			half height = abs(dot(IN.texcoord_1,IN.texcoord_2.xyz) * depth * s_depth_range.y / distance) * foam_falloff;
			half foam = saturate(foam_0 + foam_1 - foam_threshold - height) * foam_scale * exp2(-height);
			
			#ifdef OMNI || PROJ || WORLD
				foam *= s_material_shading.x;
			#endif
			
			color = color * (1.0f - foam) + foam;
			
		#endif
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifdef QUALITY_MEDIUM
		#ifdef FOAM
			
			half foam_0 = h1tex2D(s_texture_2,IN.texcoord_0.xy * foam_0_transform.xy + foam_0_transform.zw);
			half foam_1 = h1tex2D(s_texture_2,IN.texcoord_0.xy * foam_1_transform.xy + foam_1_transform.zw);
			
			half height = abs(dot(IN.texcoord_1,IN.texcoord_2.xyz) * depth * s_depth_range.y / distance) * foam_falloff;
			half foam = saturate(foam_0 + foam_1 - foam_threshold - height) * foam_scale * exp2(-height);
			
			#ifdef OMNI || PROJ || WORLD
				foam *= s_material_shading.x;
			#endif
			
			color = color * (1.0f - foam) + foam;
			
		#endif
	#endif
	
#endif
