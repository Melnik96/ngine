/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_sample.h
 * Desc:    Grass base sample shader
 * Version: 1.04
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
	
	#ifdef OPACITY || LIGHTMAP
		half alpha = gl_TexCoord[2].w;
	#else
		half alpha = gl_TexCoord[1].w;
	#endif
	
	half4 diffuse = texture2DAlpha(s_texture_0,gl_TexCoord[0].xy,alpha);
	
	#ifdef NOISE
		half3 noise = texture2D(s_texture_1,gl_TexCoord[0].zw).xyz;
		diffuse.xyz = saturate(diffuse.xyz + (noise * 2.0f - 1.0f) * noise_scale);
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifdef OPACITY || LIGHTMAP
		half alpha = IN.texcoord_2.w;
	#else
		half alpha = IN.texcoord_1.w;
	#endif
	
	half4 diffuse = tex2DAlpha(s_texture_0,IN.texcoord_0.xy,alpha);
	
	#ifdef NOISE
		half3 noise = tex2D(s_texture_1,IN.texcoord_0.zw).xyz;
		diffuse.xyz = saturate(diffuse.xyz + (noise * 2.0f - 1.0f) * noise_scale);
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifdef OPACITY || LIGHTMAP
		half alpha = IN.texcoord_2.w;
	#else
		half alpha = IN.texcoord_1.w;
	#endif
	
	OUT = texture2DAlpha(s_texture_0,s_sampler_0,IN.texcoord_0.xy,alpha);
	half4 diffuse = OUT.color;
	
	#ifdef NOISE
		half3 noise = s_texture_1.Sample(s_sampler_1,IN.texcoord_0.zw).xyz;
		diffuse.xyz = saturate(diffuse.xyz + (noise * 2.0f - 1.0f) * noise_scale);
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifdef OPACITY || LIGHTMAP
		half alpha = IN.texcoord_2.w;
	#else
		half alpha = IN.texcoord_1.w;
	#endif
	
	half4 diffuse = tex2DAlpha(s_texture_0,IN.texcoord_0.xy,alpha);
	
	#ifdef NOISE
		half3 noise = h3tex2D(s_texture_1,IN.texcoord_0.zw);
		diffuse.xyz = saturate(diffuse.xyz + (noise * 2.0f - 1.0f) * noise_scale);
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
	#endif
	
#endif
