/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    control_base.h
 * Desc:    Base control shader
 * Version: 1.02
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

#ifndef __CONTROL_BASE_H__
#define __CONTROL_BASE_H__

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

#ifdef USE_TESSELLATION && TESSELLATION

##version 150
##extension GL_ARB_tessellation_shader : enable

/*
 */
#ifdef USE_EXT_CG_SHADER
	#undef USE_EXT_CG_SHADER
#endif

/*
 */
#include <core/shaders/common/common_base.h>

/* vertex transormation
 */
float4 getPosition(float4 vertex) {
	vertex.xyz -= s_camera_offset;
	return s_modelviewprojection * vertex;
}

#endif

/******************************************************************************\
*
* Direct3D11
*
\******************************************************************************/

#elif DIRECT3D11

#ifdef USE_TESSELLATION && TESSELLATION

/*
 */
#include <core/shaders/common/common_base.h>

/* texture samplers
 */
SamplerState s_sampler_0 : register(s0);
SamplerState s_sampler_1 : register(s1);
SamplerState s_sampler_2 : register(s2);
SamplerState s_sampler_3 : register(s3);
SamplerState s_sampler_4 : register(s4);
SamplerState s_sampler_5 : register(s5);
SamplerState s_sampler_6 : register(s6);
SamplerState s_sampler_7 : register(s7);
SamplerState s_sampler_8 : register(s8);
SamplerState s_sampler_9 : register(s9);
SamplerState s_sampler_10 : register(s10);
SamplerState s_sampler_11 : register(s11);
SamplerState s_sampler_12 : register(s12);
SamplerState s_sampler_13 : register(s13);
SamplerState s_sampler_14 : register(s14);
SamplerState s_sampler_15 : register(s15);

/* vertex transformation
 */
float4 getPosition(float4 vertex) {
	vertex.xyz -= s_camera_offset;
	return mul(s_modelviewprojection,vertex);
}

#endif

#endif

#endif /* __CONTROL_BASE_H__ */
