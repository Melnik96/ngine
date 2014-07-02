/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_volume.shader
 * Desc:    Particles base volume shader
 * Version: 1.10
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
	
	#ifdef VOLUME
		half4 deferred_depth = texture2DDeferredProj(s_texture_12,gl_TexCoord[7],s_material_textures[12].xy);
		half depth = getDeferredDepth(deferred_depth) - length(gl_TexCoord[2].xyz);
		color *= saturate(depth * half(gl_TexCoord[2].w));
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifdef VOLUME
		half4 deferred_depth = tex2Dproj(s_texture_12,IN.texcoord_7);
		half depth = getDeferredDepth(deferred_depth) - length(IN.texcoord_2.xyz);
		color *= saturate(depth * half(IN.texcoord_2.w));
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifdef VOLUME
		half4 deferred_depth = texture2DDeferredRect(s_texture_12,s_sampler_12,IN.position.xy,s_material_textures[12].xy);
		half depth = getDeferredDepth(deferred_depth) - length(IN.texcoord_2.xyz);
		color *= saturate(depth * IN.texcoord_2.w);
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifdef VOLUME
		half deferred_depth = tex2DDepthProj(s_texture_12,IN.texcoord_9.xyw);
		half depth = getDeferredDepth(deferred_depth) - length(IN.texcoord_2.xyz);
		color *= saturate(depth * half(IN.texcoord_2.w));
	#endif
	
#endif
