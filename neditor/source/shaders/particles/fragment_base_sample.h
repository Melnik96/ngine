/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_sample.h
 * Desc:    Particles base sample shader
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
	
	#ifdef ANIMATION
		half3 texcoord = half3(gl_TexCoord[0].xy,half(gl_TexCoord[0].z) * animation_scale);
		half4 diffuse = texture3D(s_texture_0,texcoord);
	#else
		half4 diffuse = texture2D(s_texture_0,gl_TexCoord[0].xy);
	#endif
	
	diffuse *= texture2D(s_texture_1,gl_TexCoord[0].zw);
	
	half4 color = diffuse * half4(gl_TexCoord[1]);
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifdef ANIMATION
		half3 texcoord = half3(IN.texcoord_0.xy,IN.texcoord_0.z * animation_scale);
		half4 diffuse = tex3D(s_texture_0,texcoord);
	#else
		half4 diffuse = tex2D(s_texture_0,IN.texcoord_0.xy);
	#endif
	
	diffuse *= tex2D(s_texture_1,IN.texcoord_0.zw);
	
	half4 color = diffuse * IN.texcoord_1;
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifdef ANIMATION
		half3 texcoord = half3(IN.texcoord_0.xy,IN.texcoord_0.z * animation_scale);
		half4 diffuse = s_texture_0.Sample(s_sampler_0,texcoord);
	#else
		half4 diffuse = s_texture_0.Sample(s_sampler_0,IN.texcoord_0.xy);
	#endif
	
	diffuse *= s_texture_1.Sample(s_sampler_1,IN.texcoord_0.zw);
	
	half4 color = diffuse * IN.texcoord_1;
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifdef ANIMATION
		half3 texcoord = half3(IN.texcoord_0.yx,IN.texcoord_0.z * animation_scale);
		half4 diffuse = h4tex3D(s_texture_0,texcoord);
	#else
		half4 diffuse = h4tex2D(s_texture_0,IN.texcoord_0.yx);
	#endif
	
	diffuse *= h4tex2D(s_texture_1,IN.texcoord_0.zw);
	
	half4 color = diffuse * IN.texcoord_1;
	
#endif
