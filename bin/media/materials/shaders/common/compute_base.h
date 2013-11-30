/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    compute_base.h
 * Desc:    Base compute shader
 * Version: 1.01
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

#ifndef __COMPUTE_BASE_H__
#define __COMPUTE_BASE_H__

/******************************************************************************\
*
* Direct3D11
*
\******************************************************************************/

#ifdef DIRECT3D11 && USE_COMPUTE_SHADER_11_0

/*
 */
#include <core/shaders/common/common_base.h>

/* multisample
 */
#ifdef MULTISAMPLE_0
	#define MULTISAMPLE_SAMPLES		1
	#define MULTISAMPLE_ISAMPLES	1.0f
	#define TEXTURE_2DMS			Texture2D
#elif MULTISAMPLE_2
	#define MULTISAMPLE_SAMPLES		2
	#define MULTISAMPLE_ISAMPLES	0.5f
	#define TEXTURE_2DMS			Texture2DMS<float4,2>
#elif MULTISAMPLE_4
	#define MULTISAMPLE_SAMPLES		4
	#define MULTISAMPLE_ISAMPLES	0.25f
	#define TEXTURE_2DMS			Texture2DMS<float4,4>
#elif MULTISAMPLE_8
	#define MULTISAMPLE_SAMPLES		8
	#define MULTISAMPLE_ISAMPLES	0.125f
	#define TEXTURE_2DMS			Texture2DMS<float4,8>
#endif

/* shader dimension parameters
 */
cbuffer shader_dispatch_parameters {
	float4 s_dimension;
};

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

#endif

#endif /* __COMPUTE_BASE_H__ */
