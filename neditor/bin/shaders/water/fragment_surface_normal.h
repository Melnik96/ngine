/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_surface_normal.h
 * Desc:    Water surface normal shader
 * Version: 1.13
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
	
	half4 deferred_depth = texture2DDeferredProj(s_texture_12,gl_TexCoord[7],s_material_textures[12].xy);
	
	half distance = length(gl_TexCoord[2].xyz);
	half depth = max(getDeferredDepth(deferred_depth) - distance,0.0f);
	
	half fog = 1.0f - exp2(-gl_TexCoord[2].w * depth);
	fog *= saturate(dot(gl_TexCoord[2].xyz,s_water_direction) - 1.0f);
	
	#ifdef QUALITY_MEDIUM
		
		#ifdef SPOT || OMNI || PROJ || WORLD
			half2 normal_0 = texture2D(s_texture_0,gl_TexCoord[0].xy * normal_0_transform.xy + normal_0_transform.zw).xy;
			half2 normal_1 = texture2D(s_texture_0,gl_TexCoord[0].xy * normal_1_transform.xy + normal_1_transform.zw).xy;
			half2 normal_2 = texture2D(s_texture_1,gl_TexCoord[0].xy * normal_2_transform.xy + normal_2_transform.zw).xy;
			half2 normal_3 = texture2D(s_texture_1,gl_TexCoord[0].xy * normal_3_transform.xy + normal_3_transform.zw).xy;
		#else
			half2 normal_0 = texture2D(s_texture_0,gl_TexCoord[5].xy).xy;
			half2 normal_1 = texture2D(s_texture_0,gl_TexCoord[5].zw).xy;
			half2 normal_2 = texture2D(s_texture_1,gl_TexCoord[6].xy).xy;
			half2 normal_3 = texture2D(s_texture_1,gl_TexCoord[6].zw).xy;
		#endif
		
		#ifdef USE_ARB_TEXTURE_SNORM
			half3 normal = half3((normal_0 + normal_1 + normal_2 + normal_3) * 0.25f,0.0f);
		#else
			half3 normal = half3((normal_0 + normal_1 + normal_2 + normal_3) * 0.5f - 1.0f,0.0f);
		#endif
		
	#else
		
		#ifdef SPOT || OMNI || PROJ || WORLD
			half2 normal_0 = texture2D(s_texture_0,gl_TexCoord[0].xy * normal_0_transform.xy + normal_0_transform.zw).xy;
			half2 normal_1 = texture2D(s_texture_0,gl_TexCoord[0].xy * normal_1_transform.xy + normal_1_transform.zw).xy;
		#else
			half2 normal_0 = texture2D(s_texture_0,gl_TexCoord[5].xy).xy;
			half2 normal_1 = texture2D(s_texture_0,gl_TexCoord[5].zw).xy;
		#endif
		
		#ifdef USE_ARB_TEXTURE_SNORM
			half3 normal = half3((normal_0 + normal_1) * 0.5f,0.0f);
		#else
			half3 normal = half3((normal_0 + normal_1) - 1.0f,0.0f);
		#endif
		
	#endif
	
	normal.xy = gl_TexCoord[1].xy + normal.xy * reflection_normal;
	normal.z = sqrt(saturate(1.0 - dot(normal.xy,normal.xy)));
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	half4 deferred_depth = tex2Dproj(s_texture_12,IN.texcoord_7);
	
	half distance = length(IN.texcoord_2.xyz);
	half depth = max(getDeferredDepth(deferred_depth) - distance,0.0f);
	
	half fog = 1.0f - exp2(-IN.texcoord_2.w * depth);
	fog *= saturate(dot(IN.texcoord_2.xyz,s_water_direction) - 1.0f);
	
	#ifdef QUALITY_MEDIUM
		
		#ifdef SPOT || OMNI || PROJ || WORLD
			half2 normal_0 = tex2D(s_texture_0,IN.texcoord_0.xy * normal_0_transform.xy + normal_0_transform.zw).xy;
			half2 normal_1 = tex2D(s_texture_0,IN.texcoord_0.xy * normal_1_transform.xy + normal_1_transform.zw).xy;
			half2 normal_2 = tex2D(s_texture_1,IN.texcoord_0.xy * normal_2_transform.xy + normal_2_transform.zw).xy;
			half2 normal_3 = tex2D(s_texture_1,IN.texcoord_0.xy * normal_3_transform.xy + normal_3_transform.zw).xy;
		#else
			half2 normal_0 = tex2D(s_texture_0,IN.texcoord_5.xy).xy;
			half2 normal_1 = tex2D(s_texture_0,IN.texcoord_5.zw).xy;
			half2 normal_2 = tex2D(s_texture_1,IN.texcoord_6.xy).xy;
			half2 normal_3 = tex2D(s_texture_1,IN.texcoord_6.zw).xy;
		#endif
		
		half3 normal = half3((normal_0 + normal_1 + normal_2 + normal_3) * 0.5f - 1.0f,0.0f);
		
	#else
		
		#ifdef SPOT || OMNI || PROJ || WORLD
			half2 normal_0 = tex2D(s_texture_0,IN.texcoord_0.xy * normal_0_transform.xy + normal_0_transform.zw).xy;
			half2 normal_1 = tex2D(s_texture_0,IN.texcoord_0.xy * normal_1_transform.xy + normal_1_transform.zw).xy;
		#else
			half2 normal_0 = tex2D(s_texture_0,IN.texcoord_5.xy).xy;
			half2 normal_1 = tex2D(s_texture_0,IN.texcoord_5.zw).xy;
		#endif
		
		half3 normal = half3((normal_0 + normal_1) - 1.0f,0.0f);
		
	#endif
	
	normal.xy = IN.texcoord_1.xy + normal.xy * reflection_normal;
	normal.z = sqrt(saturate(1.0f - dot(normal.xy,normal.xy)));
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	half4 deferred_depth = texture2DDeferredRect(s_texture_12,s_sampler_12,IN.position.xy,s_material_textures[12].xy);
	
	half distance = length(IN.texcoord_2.xyz);
	half depth = max(getDeferredDepth(deferred_depth) - distance,0.0f);
	
	half fog = 1.0f - exp2(-IN.texcoord_2.w * depth);
	fog *= saturate(dot(IN.texcoord_2.xyz,s_water_direction) - 1.0f);
	
	#ifdef QUALITY_MEDIUM
		
		half2 normal_0 = s_texture_0.Sample(s_sampler_1,IN.texcoord_7.xy).xy;
		half2 normal_1 = s_texture_0.Sample(s_sampler_1,IN.texcoord_7.zw).xy;
		half2 normal_2 = s_texture_1.Sample(s_sampler_2,IN.texcoord_8.xy).xy;
		half2 normal_3 = s_texture_1.Sample(s_sampler_2,IN.texcoord_8.zw).xy;
		
		half3 normal = half3((normal_0 + normal_1 + normal_2 + normal_3) * 0.25f,0.0f);
		
	#else
		
		half2 normal_0 = s_texture_0.Sample(s_sampler_1,IN.texcoord_7.xy).xy;
		half2 normal_1 = s_texture_0.Sample(s_sampler_1,IN.texcoord_7.zw).xy;
		
		half3 normal = half3((normal_0 + normal_1) * 0.5f,0.0f);
		
	#endif
	
	normal.xy = IN.texcoord_1.xy + normal.xy * reflection_normal;
	normal.z = sqrt(saturate(1.0 - dot(normal.xy,normal.xy)));
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	half4 deferred_depth = h4tex2Dproj(s_texture_12,IN.texcoord_9.xyw);
	
	half distance = length(IN.texcoord_2.xyz);
	half depth = max(getDeferredDepth(deferred_depth) - distance,0.0f);

	half fog = 1.0f - exp2(-IN.texcoord_2.w * depth);
	fog *= saturate(dot(IN.texcoord_2.xyz,s_water_direction) - 1.0f);
	
	#ifdef QUALITY_MEDIUM
		
		half2 normal_0 = h2tex2D(s_texture_0,IN.texcoord_7.xy);
		half2 normal_1 = h2tex2D(s_texture_0,IN.texcoord_7.zw);
		half2 normal_2 = h2tex2D(s_texture_1,IN.texcoord_8.xy);
		half2 normal_3 = h2tex2D(s_texture_1,IN.texcoord_8.zw);
		
		half3 normal = half3((normal_0 + normal_1 + normal_2 + normal_3) * 0.25f,0.0f);
		
	#else
		
		half2 normal_0 = h2tex2D(s_texture_0,IN.texcoord_7.xy);
		half2 normal_1 = h2tex2D(s_texture_0,IN.texcoord_7.zw);
		
		half3 normal = half3((normal_0 + normal_1) * 0.5f,0.0f);
		
	#endif
	
	normal.xy = IN.texcoord_1.xy + normal.xy * reflection_normal;
	normal.z = sqrt(saturate(1.0f - dot(normal.xy,normal.xy)));
	
#endif
