/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base.h
 * Desc:    Base vertex shader
 * Version: 1.11
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

#ifndef __VERTEX_BASE_H__
#define __VERTEX_BASE_H__

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

/*
 */
#include <core/shaders/common/common_base.h>

/* vertex transormation
 */
float4 getPosition(float4 vertex) {
	#ifdef USE_TESSELLATION && TESSELLATION
		return vertex;
	#else
		vertex.xyz -= s_camera_offset;
		return s_modelviewprojection * vertex;
	#endif
}

/* perspective projection
 */
float4 getProjection(float4 position) {
	return (position + position.w) * 0.5f;
}

/* animation offset vector
 */
float2 getAnimationOffset(float angle) {
	float angle_0 = angle * 0.3f;
	float angle_1 = angle * 0.9f;
	float sin_0 = sin(angle_0);
	float cos_0 = cos(angle_0);
	float sin_1 = sin(angle_1);
	float cos_1 = cos(angle_1);
	return float2(sin_1 * cos_0,cos_1 * sin_0);
}

/* alpha fade
 */
float getAlphaFade(float4 bound_sphere) {
	float distance = length(bound_sphere.xyz - s_camera_position) - bound_sphere.w;
	float fade_in = saturate((distance - s_surface_distances.x) / s_surface_distances.z);
	float fade_out = saturate((distance - s_surface_distances.y) / s_surface_distances.w);
	if(distance > s_surface_distances.y) return -saturate(fade_in - fade_out);
	return saturate(fade_in - fade_out);
}

float getAlphaFadeScale(float4 bound_sphere) {
	float distance = length(bound_sphere.xyz - s_camera_position) - bound_sphere.w;
	float fade_in = saturate((distance - s_surface_distances.x) / s_surface_distances.z);
	float fade_out = saturate((distance - s_surface_distances.y) / s_surface_distances.w);
	return saturate(fade_in - fade_out) * 0.5f + 0.5f;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

/*
 */
#include <core/shaders/common/common_base.h>

/* vertex transormation
 */
float4 getPosition(float4 vertex) {
	vertex.xyz -= s_camera_offset;
	return mul(s_modelviewprojection,vertex);
}

/* animation offset vector
 */
float2 getAnimationOffset(float angle) {
	float sin_0,cos_0;
	float sin_1,cos_1;
	sincos(angle * 0.3f,sin_0,cos_0);
	sincos(angle * 0.9f,sin_1,cos_1);
	return float2(sin_1 * cos_0,cos_1 * sin_0);
}

/* perspective projection
 */
float4 getProjection(float4 position) {
	return (position * float4(1.0f,-1.0f,1.0f,1.0f) + position.w * float4(s_viewport.zw + 1.0f,1.0f,1.0f)) * 0.5f;
}

/* alpha fade
 */
float getAlphaFade(float4 bound_sphere) {
	float distance = length(bound_sphere.xyz - s_camera_position) - bound_sphere.w;
	float fade_in = saturate((distance - s_surface_distances.x) / s_surface_distances.z);
	float fade_out = saturate((distance - s_surface_distances.y) / s_surface_distances.w);
	if(distance > s_surface_distances.y) return -saturate(fade_in - fade_out);
	return saturate(fade_in - fade_out);
}

float getAlphaFadeScale(float4 bound_sphere) {
	float distance = length(bound_sphere.xyz - s_camera_position) - bound_sphere.w;
	float fade_in = saturate((distance - s_surface_distances.x) / s_surface_distances.z);
	float fade_out = saturate((distance - s_surface_distances.y) / s_surface_distances.w);
	return saturate(fade_in - fade_out) * 0.5f + 0.5f;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

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

/* tessellation
 */
#ifdef USE_TESSELLATION && TESSELLATION
	#define OUT_POSITION POSITION
#else
	#define OUT_POSITION SV_POSITION
#endif

/* vertex transormation
 */
float4 getPosition(float4 vertex) {
	#ifdef USE_TESSELLATION && TESSELLATION
		return vertex;
	#else
		vertex.xyz -= s_camera_offset;
		return mul(s_modelviewprojection,vertex);
	#endif
}

/* animation offset vector
 */
float2 getAnimationOffset(float angle) {
	float sin_0,cos_0;
	float sin_1,cos_1;
	sincos(angle * 0.3f,sin_0,cos_0);
	sincos(angle * 0.9f,sin_1,cos_1);
	return float2(sin_1 * cos_0,cos_1 * sin_0);
}

/* alpha fade
 */
float getAlphaFade(float4 bound_sphere) {
	float distance = length(bound_sphere.xyz - s_camera_position) - bound_sphere.w;
	float fade_in = saturate((distance - s_surface_distances.x) / s_surface_distances.z);
	float fade_out = saturate((distance - s_surface_distances.y) / s_surface_distances.w);
	if(distance > s_surface_distances.y) return -saturate(fade_in - fade_out);
	return saturate(fade_in - fade_out);
}

float getAlphaFadeScale(float4 bound_sphere) {
	float distance = length(bound_sphere.xyz - s_camera_position) - bound_sphere.w;
	float fade_in = saturate((distance - s_surface_distances.x) / s_surface_distances.z);
	float fade_out = saturate((distance - s_surface_distances.y) / s_surface_distances.w);
	return saturate(fade_in - fade_out) * 0.5f + 0.5f;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

/*
 */
#include <core/shaders/common/common_base.h>

/* vertex transormation
 */
float4 getPosition(float4 vertex) {
	vertex.xyz -= s_camera_offset;
	return mul(s_modelviewprojection,vertex);
}

/* animation offset vector
 */
float2 getAnimationOffset(float angle) {
	float sin_0,cos_0;
	float sin_1,cos_1;
	sincos(angle * 0.3f,sin_0,cos_0);
	sincos(angle * 0.9f,sin_1,cos_1);
	return float2(sin_1 * cos_0,cos_1 * sin_0);
}

/* perspective projection
 */
float4 getProjection(float4 position) {
	return (position * float4(1.0f,-1.0f,1.0f,1.0f) + position.w) * 0.5f;
}

/* alpha fade
 */
float getAlphaFade(float4 bound_sphere) {
	float distance = length(bound_sphere.xyz - s_camera_position) - bound_sphere.w;
	float fade_in = saturate((distance - s_surface_distances.x) / s_surface_distances.z);
	float fade_out = saturate((distance - s_surface_distances.y) / s_surface_distances.w);
	if(distance > s_surface_distances.y) return -saturate(fade_in - fade_out);
	return saturate(fade_in - fade_out);
}

float getAlphaFadeScale(float4 bound_sphere) {
	float distance = length(bound_sphere.xyz - s_camera_position) - bound_sphere.w;
	float fade_in = saturate((distance - s_surface_distances.x) / s_surface_distances.z);
	float fade_out = saturate((distance - s_surface_distances.y) / s_surface_distances.w);
	return saturate(fade_in - fade_out) * 0.5f + 0.5f;
}

#endif

#endif /* __VERTEX_BASE_H__ */
