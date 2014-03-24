/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_sample.h
 * Desc:    Mesh base sample shader
 * Version: 1.12
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
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		#ifdef USE_TESSELLATION && TESSELLATION
			texture2DAlphaFadeDiscard(s_texture_9,gl_TexCoord[7].x);
		#else
			texture2DAlphaFadeDiscard(s_texture_9,gl_TexCoord[7].z);
		#endif
	#endif
	
	float4 texcoord = gl_TexCoord[0];
	
	#ifdef USE_PARALLAX && PARALLAX
		half4 deferred_parallax = texture2DDeferredProj(s_texture_10,gl_TexCoord[7],s_material_textures[10].xy);
		texcoord.xy += getDeferredParallax(deferred_parallax);
	#endif
	
	half4 diffuse = texture2DAlpha(s_texture_0,texcoord.xy,1.0f);
	half3 normal = texture2D(s_texture_1,texcoord.xy).xyz;
	half4 specular = texture2D(s_texture_2,texcoord.xy);
	
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		
		#ifdef OVERLAY_0 || MULTIPLY_0
			float2 detail_texcoord = texcoord.xy * detail_transform.xy + detail_transform.zw;
		#elif OVERLAY_1 || MULTIPLY_1
			float2 detail_texcoord = texcoord.zw * detail_transform.xy + detail_transform.zw;
		#endif
		
		half4 detail_diffuse = texture2D(s_texture_3,detail_texcoord);
		half2 detail_normal = texture2D(s_texture_4,detail_texcoord).xy;
		half3 detail_specular = texture2D(s_texture_5,detail_texcoord).xyz;
		
		#ifdef ALPHA
			half3 k = s_material_detail * detail_diffuse.w;
		#else
			half3 k = s_material_detail * (diffuse.w * detail_diffuse.w);
		#endif
		
		#ifdef OVERLAY_0 || OVERLAY_1
			diffuse.xyz = saturate(diffuse.xyz + (detail_diffuse.xyz * 2.0f - 1.0f) * k.x);
			specular.xyz = saturate(specular.xyz + (detail_specular.xyz * 2.0f - 1.0f) * k.z);
		#else
			diffuse.xyz = diffuse.xyz * saturate(detail_diffuse.xyz + 1.0f - k.x);
			specular.xyz = specular.xyz * saturate(detail_specular.xyz + 1.0f - k.z);
		#endif
		normal.xy = normal.xy + detail_normal * k.y;
		
		#ifndef USE_ARB_TEXTURE_SNORM
			normal.xy = normal.xy * 2.0f - 1.0f - k.y;
		#endif
		
	#else
		
		#ifndef USE_ARB_TEXTURE_SNORM
			normal.xy = normal.xy * 2.0f - 1.0f;
		#endif
		
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
		specular.xyz *= specular.xyz;
	#endif
	
	normal.z = sqrt(saturate(1.0f - dot(normal.xy,normal.xy)));
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_9,IN.texcoord_7,IN.texcoord_7.z);
	#endif
	
	float4 texcoord = IN.texcoord_0;
	
	#ifdef USE_PARALLAX && PARALLAX
		half4 deferred_parallax = tex2Dproj(s_texture_10,IN.texcoord_7);
		texcoord.xy += getDeferredParallax(deferred_parallax);
	#endif
	
	half4 diffuse = tex2DAlpha(s_texture_0,texcoord.xy,1.0f);
	half3 normal = tex2D(s_texture_1,texcoord.xy).xyz;
	half4 specular = tex2D(s_texture_2,texcoord.xy);
	
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		
		#ifdef OVERLAY_0 || MULTIPLY_0
			float2 detail_texcoord = texcoord.xy * detail_transform.xy + detail_transform.zw;
		#elif OVERLAY_1 || MULTIPLY_1
			float2 detail_texcoord = texcoord.zw * detail_transform.xy + detail_transform.zw;
		#endif
		
		half4 detail_diffuse = tex2D(s_texture_3,detail_texcoord);
		half2 detail_normal = tex2D(s_texture_4,detail_texcoord).xy;
		half3 detail_specular = tex2D(s_texture_5,detail_texcoord).xyz;
		
		#ifdef ALPHA
			half3 k = s_material_detail * detail_diffuse.w;
		#else
			half3 k = s_material_detail * (diffuse.w * detail_diffuse.w);
		#endif
		
		#ifdef OVERLAY_0 || OVERLAY_1
			diffuse.xyz = saturate(diffuse.xyz + (detail_diffuse.xyz * 2.0f - 1.0f) * k.x);
			specular.xyz = saturate(specular.xyz + (detail_specular.xyz * 2.0f - 1.0f) * k.z);
		#else
			diffuse.xyz = diffuse.xyz * saturate(detail_diffuse.xyz + 1.0f - k.x);
			specular.xyz = specular.xyz * saturate(detail_specular.xyz + 1.0f - k.z);
		#endif
		normal.xy = normal.xy + detail_normal * k.y;
		
		normal.xy = normal.xy * 2.0f - 1.0f - k.y;
		
	#else
		
		normal.xy = normal.xy * 2.0f - 1.0f;
		
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
		specular.xyz *= specular.xyz;
	#endif
	
	normal.z = sqrt(saturate(1.0f - dot(normal.xy,normal.xy)));
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texture2DAlphaFadeDiscard(s_texture_9,s_sampler_9,IN.position.xy,IN.texcoord_9.x);
	#endif
	
	float4 texcoord = IN.texcoord_0;
	
	#ifdef USE_PARALLAX && PARALLAX
		half4 deferred_parallax = texture2DDeferredRect(s_texture_10,s_sampler_10,IN.position.xy,s_material_textures[10].xy);
		texcoord.xy += getDeferredParallax(deferred_parallax);
	#endif
	
	OUT = texture2DAlpha(s_texture_0,s_sampler_0,texcoord.xy,1.0f);
	
	half4 diffuse = OUT.color;
	half3 normal = s_texture_1.Sample(s_sampler_1,texcoord.xy).xyz;
	half4 specular = s_texture_2.Sample(s_sampler_2,texcoord.xy);
	
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		
		#ifdef OVERLAY_0 || MULTIPLY_0
			float2 detail_texcoord = texcoord.xy * detail_transform.xy + detail_transform.zw;
		#elif OVERLAY_1 || MULTIPLY_1
			float2 detail_texcoord = texcoord.zw * detail_transform.xy + detail_transform.zw;
		#endif
		
		half4 detail_diffuse = s_texture_3.Sample(s_sampler_3,detail_texcoord);
		half2 detail_normal = s_texture_4.Sample(s_sampler_4,detail_texcoord).xy;
		half3 detail_specular = s_texture_5.Sample(s_sampler_5,detail_texcoord).xyz;
		
		#ifdef ALPHA
			half3 k = s_material_detail * detail_diffuse.w;
		#else
			half3 k = s_material_detail * (diffuse.w * detail_diffuse.w);
		#endif
		
		#ifdef OVERLAY_0 || OVERLAY_1
			diffuse.xyz = saturate(diffuse.xyz + (detail_diffuse.xyz * 2.0f - 1.0f) * k.x);
			specular.xyz = saturate(specular.xyz + (detail_specular.xyz * 2.0f - 1.0f) * k.z);
		#else
			diffuse.xyz = diffuse.xyz * saturate(detail_diffuse.xyz + 1.0f - k.x);
			specular.xyz = specular.xyz * saturate(detail_specular.xyz + 1.0f - k.z);
		#endif
		normal.xy = normal.xy + detail_normal * k.y;
		
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
		specular.xyz *= specular.xyz;
	#endif
	
	normal.z = sqrt(saturate(1.0f - dot(normal.xy,normal.xy)));
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_9,IN.texcoord_9,IN.texcoord_9.z);
	#endif
	
	float4 texcoord = IN.texcoord_0;
	
	#ifdef USE_PARALLAX && PARALLAX
		half4 deferred_parallax = h4tex2Dproj(s_texture_10,IN.texcoord_9.xyw);
		texcoord.xy += getDeferredParallax(deferred_parallax);
	#endif
	
	half4 diffuse = tex2DAlpha(s_texture_0,texcoord.xy,1.0f);
	half3 normal = h3tex2D(s_texture_1,texcoord.xy);
	half4 specular = h4tex2D(s_texture_2,texcoord.xy);
	
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		
		#ifdef OVERLAY_0 || MULTIPLY_0
			float2 detail_texcoord = texcoord.xy * detail_transform.xy + detail_transform.zw;
		#elif OVERLAY_1 || MULTIPLY_1
			float2 detail_texcoord = texcoord.zw * detail_transform.xy + detail_transform.zw;
		#endif
		
		half4 detail_diffuse = h4tex2D(s_texture_3,detail_texcoord);
		half2 detail_normal = h2tex2D(s_texture_4,detail_texcoord);
		half3 detail_specular = h3tex2D(s_texture_5,detail_texcoord);
		
		#ifdef ALPHA
			half3 k = s_material_detail * detail_diffuse.w;
		#else
			half3 k = s_material_detail * (diffuse.w * detail_diffuse.w);
		#endif
		
		#ifdef OVERLAY_0 || OVERLAY_1
			diffuse.xyz = saturate(diffuse.xyz + (detail_diffuse.xyz * 2.0f - 1.0f) * k.x);
			specular.xyz = saturate(specular.xyz + (detail_specular.xyz * 2.0f - 1.0f) * k.z);
		#else
			diffuse.xyz = diffuse.xyz * saturate(detail_diffuse.xyz + 1.0f - k.x);
			specular.xyz = specular.xyz * saturate(detail_specular.xyz + 1.0f - k.z);
		#endif
		normal.xy = normal.xy + detail_normal * k.y;
		
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
		specular.xyz *= specular.xyz;
	#endif
	
	normal.z = sqrt(saturate(1.0f - dot(normal.xy,normal.xy)));
	
#endif
