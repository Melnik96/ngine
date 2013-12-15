/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_sample.h
 * Desc:    Decal base sample shader
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
	
	half fade = gl_TexCoord[0].z;
	
	float2 texcoord = gl_TexCoord[0].xy / gl_TexCoord[0].w;
	
	#ifdef USE_PARALLAX && PARALLAX
		half4 deferred_parallax = texture2DDeferredProj(s_texture_10,gl_TexCoord[7],s_material_textures[10].xy);
		texcoord.xy += getDeferredParallax(deferred_parallax);
	#endif
	
	half4 diffuse = texture2DAlpha(s_texture_0,texcoord.xy,fade);
	half3 normal = texture2DNormal(s_texture_1,texcoord.xy);
	half4 specular = texture2D(s_texture_2,texcoord.xy);
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	half fade = IN.texcoord_0.z;
	
	float2 texcoord = IN.texcoord_0.xy / IN.texcoord_0.w;
	
	#ifdef USE_PARALLAX && PARALLAX
		half4 deferred_parallax = tex2Dproj(s_texture_10,IN.texcoord_7);
		texcoord.xy += getDeferredParallax(deferred_parallax);
	#endif
	
	half4 diffuse = tex2DAlpha(s_texture_0,texcoord.xy,fade);
	half3 normal = tex2DNormal(s_texture_1,texcoord.xy);
	half4 specular = tex2D(s_texture_2,texcoord.xy);
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	half fade = IN.texcoord_0.z;
	
	float2 texcoord = IN.texcoord_0.xy / IN.texcoord_0.w;
	
	#ifdef USE_PARALLAX && PARALLAX
		half4 deferred_parallax = texture2DDeferredRect(s_texture_10,s_sampler_10,IN.position.xy,s_material_textures[10].xy);
		texcoord.xy += getDeferredParallax(deferred_parallax);
	#endif
	
	OUT = texture2DAlpha(s_texture_0,s_sampler_0,texcoord.xy,fade);
	
	half4 diffuse = OUT.color;
	half3 normal = texture2DNormal(s_texture_1,s_sampler_1,texcoord.xy);
	half4 specular = s_texture_2.Sample(s_sampler_2,texcoord.xy);
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	half fade = IN.texcoord_0.z;
	
	float2 texcoord = IN.texcoord_0.xy / IN.texcoord_0.w;
	
	#ifdef USE_PARALLAX && PARALLAX
		half4 deferred_parallax = h4tex2Dproj(s_texture_10,IN.texcoord_9.xyw);
		texcoord.xy += getDeferredParallax(deferred_parallax);
	#endif
	
	half4 diffuse = tex2DAlpha(s_texture_0,texcoord.xy,fade);
	half3 normal = tex2DNormal(s_texture_1,texcoord.xy);
	half4 specular = h4tex2D(s_texture_2,texcoord.xy);
	
#endif
