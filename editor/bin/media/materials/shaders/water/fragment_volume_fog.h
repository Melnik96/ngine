/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_volume_fog.h
 * Desc:    Water volume fog shader
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
	
	half4 deferred_depth = texture2DDeferredProj(s_texture_12,gl_TexCoord[7],s_material_textures[12].xy);
	
	half distance = length(gl_TexCoord[1].xyz);
	half depth = max(getDeferredDepth(deferred_depth) - distance,0.0f);
	
	half fog = exp2(-pow(half(gl_TexCoord[1].w) * depth,volume_power));
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	half4 deferred_depth = tex2Dproj(s_texture_12,IN.texcoord_7);
	
	half distance = length(IN.texcoord_1.xyz);
	half depth = max(getDeferredDepth(deferred_depth) - distance,0.0f);
	
	half fog = exp2(-pow(half(IN.texcoord_1.w) * depth,volume_power));
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	half4 deferred_depth = texture2DDeferredRect(s_texture_12,s_sampler_12,IN.position.xy,s_material_textures[12].xy);
	
	half distance = length(IN.texcoord_1.xyz);
	half depth = max(getDeferredDepth(deferred_depth) - distance,0.0f);
	
	half fog = exp2(-pow(IN.texcoord_1.w * depth,volume_power));
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	half4 deferred_depth = h4tex2Dproj(s_texture_12,IN.texcoord_9.xyw);
	
	half distance = length(IN.texcoord_1.xyz);
	half depth = max(getDeferredDepth(deferred_depth) - distance,0.0f);
	
	half fog = exp2(-pow(half(IN.texcoord_1.w) * depth,volume_power));
	
#endif
