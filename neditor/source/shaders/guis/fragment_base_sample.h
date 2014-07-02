/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_sample.h
 * Desc:    Gui base sample shader
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
		texture2DAlphaFadeDiscard(s_texture_10,gl_TexCoord[7].z);
	#endif
	
	half4 diffuse = diffuse_color;
	half3 normal = texture2DNormal(s_texture_1,gl_TexCoord[0].xy);
	half4 specular = specular_color;
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_10,IN.texcoord_7,IN.texcoord_7.z);
	#endif
	
	half4 diffuse = diffuse_color;
	half3 normal = tex2DNormal(s_texture_1,IN.texcoord_0.xy);
	half4 specular = specular_color;
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texture2DAlphaFadeDiscard(s_texture_10,s_sampler_10,IN.position.xy,IN.texcoord_9.x);
	#endif
	
	half4 diffuse = diffuse_color;
	half3 normal = texture2DNormal(s_texture_1,s_sampler_1,IN.texcoord_0.xy);
	half4 specular = specular_color;
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_10,IN.texcoord_9,IN.texcoord_9.z);
	#endif
	
	half4 diffuse = diffuse_color;
	half3 normal = tex2DNormal(s_texture_1,IN.texcoord_0.xy);
	half4 specular = specular_color;
	
#endif
