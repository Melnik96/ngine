/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_leaf_sample.h
 * Desc:    Mesh leaf sample shader
 * Version: 1.03
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
		#ifdef LEAF_AMBIENT
			half4 diffuse = texture2DAlpha(s_texture_0,gl_TexCoord[0].xy,gl_TexCoord[7].z);
		#else
			half4 diffuse = texture2DAlpha(s_texture_0,gl_TexCoord[0].xy,gl_TexCoord[7].x);
		#endif
	#else
		half4 diffuse = texture2DAlpha(s_texture_0,gl_TexCoord[0].xy,1.0f);
	#endif
	
	#ifdef NOISE
		half noise_texcoord = texture3D(s_texture_4,gl_TexCoord[6].xyz).x;
		half3 noise = texture2D(s_texture_5,half2(noise_texcoord,0.0f)).xyz;
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
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		#ifdef LEAF_AMBIENT
			half4 diffuse = tex2DAlpha(s_texture_0,IN.texcoord_0.xy,IN.texcoord_7.z);
		#else
			half4 diffuse = tex2DAlpha(s_texture_0,IN.texcoord_0.xy,IN.texcoord_7.x);
		#endif
	#else
		half4 diffuse = tex2DAlpha(s_texture_0,IN.texcoord_0.xy,1.0f);
	#endif
	
	#ifdef NOISE
		half noise_texcoord = tex3D(s_texture_4,IN.texcoord_6).x;
		half3 noise = tex2D(s_texture_5,half2(noise_texcoord,0.0f)).xyz;
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
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		OUT = texture2DAlpha(s_texture_0,s_sampler_0,IN.texcoord_0.xy,IN.texcoord_9.x);
	#else
		OUT = texture2DAlpha(s_texture_0,s_sampler_0,IN.texcoord_0.xy,1.0f);
	#endif
	half4 diffuse = OUT.color;
	
	#ifdef NOISE
		half noise_texcoord = s_texture_4.Sample(s_sampler_4,IN.texcoord_6).x;
		half3 noise = s_texture_5.Sample(s_sampler_5,half2(noise_texcoord,0.0f)).xyz;
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
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		#ifdef LEAF_AMBIENT
			half4 diffuse = tex2DAlpha(s_texture_0,IN.texcoord_0.xy,IN.texcoord_9.z);
		#else
			half4 diffuse = tex2DAlpha(s_texture_0,IN.texcoord_0.xy,IN.texcoord_9.x);
		#endif
	#else
		half4 diffuse = tex2DAlpha(s_texture_0,IN.texcoord_0.xy,1.0f);
	#endif
	
	#ifdef NOISE
		half noise_texcoord = h1tex3D(s_texture_4,IN.texcoord_8);
		half3 noise = h3tex2D(s_texture_5,half2(noise_texcoord,0.0f));
		diffuse.xyz = saturate(diffuse.xyz + (noise * 2.0f - 1.0f) * noise_scale);
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
	#endif
	
#endif
