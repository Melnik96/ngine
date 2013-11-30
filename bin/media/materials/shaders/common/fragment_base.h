/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base.h
 * Desc:    Base fragment shader
 * Version: 1.22
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

#ifndef __FRAGMENT_BASE_H__
#define __FRAGMENT_BASE_H__

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

/*
 */
#include <core/shaders/common/common_base.h>

/* multisample
 */
#ifdef MULTISAMPLE_0 || !USE_ARB_TEXTURE_MULTISAMPLE
	#define MULTISAMPLE_SAMPLES		1
	#define MULTISAMPLE_ISAMPLES	1.0f
	#define SAMPLER_2DMS			sampler2D
#elif MULTISAMPLE_2
	#define MULTISAMPLE_SAMPLES		2
	#define MULTISAMPLE_ISAMPLES	0.5f
	#define SAMPLER_2DMS			sampler2DMS
#elif MULTISAMPLE_4
	#define MULTISAMPLE_SAMPLES		4
	#define MULTISAMPLE_ISAMPLES	0.25f
	#define SAMPLER_2DMS			sampler2DMS
#elif MULTISAMPLE_8
	#define MULTISAMPLE_SAMPLES		8
	#define MULTISAMPLE_ISAMPLES	0.125f
	#define SAMPLER_2DMS			sampler2DMS
#endif

/* vertex transormation
 */
float4 getPosition(float4 vertex) {
	vertex.xyz -= s_camera_offset;
	return s_modelviewprojection * vertex;
}

/* fragment coordinates
 */
float2 getFragCoord() {
	#ifdef ATI_R300 || ATI_R400 || ATI_R500
		return gl_TexCoord[7].xy * s_viewport.xy / gl_TexCoord[7].w;
	#else
		return gl_FragCoord.xy;
	#endif
}

/* deferred texture sampling
 */
half4 texture2DDeferredProj(SAMPLER_2DMS s_texture,float4 texcoord,float2 texsize) {
	#ifdef MULTISAMPLE_0 || !USE_ARB_TEXTURE_MULTISAMPLE
		half4 deferred = texture2DProj(s_texture,texcoord);
	#else
		half4 deferred = texelFetch(s_texture,int2(texcoord.xy * texsize / texcoord.w),0);
	#endif
	return deferred;
}

half4 texture2DDeferredNorm(SAMPLER_2DMS s_texture,float2 texcoord) {
	#ifdef MULTISAMPLE_0 || !USE_ARB_TEXTURE_MULTISAMPLE
		half4 deferred = texture2D(s_texture,texcoord);
	#else
		half4 deferred = texelFetch(s_texture,int2(texcoord * s_viewport.xy),0);
	#endif
	return deferred;
}

half4 texture2DDeferredNorm2(SAMPLER_2DMS s_texture,float2 texcoord) {
	#ifdef MULTISAMPLE_0 || !USE_ARB_TEXTURE_MULTISAMPLE
		half4 deferred = texture2D(s_texture,texcoord);
	#else
		half4 deferred = texelFetch(s_texture,int2(texcoord * s_viewport.xy * 2.0f),0);
	#endif
	return deferred;
}

/* deferred depth texture sampling
 */
half4 setDeferredDepth(float distance,half volumetric) {
	half3 deferred;
	distance *= 16777215.0f;
	deferred.x = floor(distance / 65536.0f);
	distance -= deferred.x * 65536.0f;
	deferred.y = floor(distance / 256.0f);
	distance -= deferred.y * 256.0f;
	deferred.z = floor(distance);
	return half4(1.0f - deferred / 255.0f,volumetric);
}

float getDeferredDepth(half4 deferred) {
	float3 factor = float3(16711680.0f / 16777215.0f,65280.0f / 16777215.0f,255.0f / 16777215.0f);
	return 1.0f - dot(deferred.xyz,factor);
}

half getDeferredVolumetric(half4 deferred) {
	return 1.0f - deferred.w;
}

/* deferred color texture sampling
 */
half4 setDeferredColor(half3 color,half glow) {
	return half4(color,glow * (1.0f / 16.0f));
}

half3 getDeferredColor(half4 deferred) {
	return deferred.xyz;
}

half getDeferredGlow(half4 deferred) {
	return deferred.w * 16.0f;
}

/* deferred normal texture sampling
 */
half4 setDeferredNormal(half3 normal,half power) {
	return half4(normal * 0.5f + 0.5f,power * (1.0f / 64.0f));
}

half3 getDeferredNormal(half4 deferred) {
	return deferred.xyz * 2.0f - 1.0f;
}

half getDeferredSpecular(half4 deferred) {
	return deferred.w * 64.0f;
}

/* deferred parallax texture sampling
 */
half4 setDeferredParallax(half2 offset) {
	half4 deferred;
	offset = saturate(offset * 0.25f + 0.5f) * 65535.0f;
	deferred.xz = floor(offset / 256.0f);
	offset -= deferred.xz * 256.0f;
	deferred.yw = floor(offset);
	return deferred / 255.0f;
}

half2 getDeferredParallax(half4 deferred) {
	half2 factor = half2(65280.0f / 65535.0f,255.0f / 65535.0f);
	return half2(dot(deferred.xy,factor),dot(deferred.zw,factor)) * 4.0f - 1.0f;
}

/* alpha test texture sampling
 */
half4 texture2DAlpha(sampler2D s_texture,half2 texcoord,half scale) {
	half4 sample = texture2D(s_texture,texcoord);
	#ifdef ALPHA
		sample.w = sample.w * scale;
		#ifdef MULTISAMPLE_0
			if(sample.w <= 0.5f) discard;
		#elif USE_ARB_SAMPLE_SHADING
			#ifdef QUALITY_HIGH
				gl_SampleMask[0] = 0x00;
				half2 dx = dFdx(texcoord);
				half2 dy = dFdy(texcoord);
				#define SAMPLE(X,Y,MASK) if(texture2D(s_texture,texcoord + dx * (X) + dy * (Y)).w * scale > 0.5f) gl_SampleMask[0] |= MASK;
				#ifdef MULTISAMPLE_2
					SAMPLE( 0.25f, 0.25f,0x01)
					SAMPLE(-0.25f,-0.25f,0x02)
				#elif MULTISAMPLE_4
					SAMPLE(-0.125f,-0.375f,0x01)
					SAMPLE( 0.375f,-0.125f,0x02)
					SAMPLE(-0.375f, 0.125f,0x04)
					SAMPLE( 0.125f, 0.375f,0x08)
				#elif MULTISAMPLE_8
					SAMPLE(-0.125f,-0.375f,0x03)
					SAMPLE( 0.375f,-0.125f,0x0c)
					SAMPLE(-0.375f, 0.125f,0x30)
					SAMPLE( 0.125f, 0.375f,0xc0)
				#endif
				#undef SAMPLE
			#else
				#ifdef MULTISAMPLE_2
					if(sample.w < 0.49f) gl_SampleMask[0] = 0x00;
					else if(sample.w < 0.50f) gl_SampleMask[0] = 0x01;
					else gl_SampleMask[0] = 0x03;
				#elif MULTISAMPLE_4
					if(sample.w < 0.48f) gl_SampleMask[0] = 0x00;
					else if(sample.w < 0.49f) gl_SampleMask[0] = 0x01;
					else if(sample.w < 0.50f) gl_SampleMask[0] = 0x06;
					else if(sample.w < 0.51f) gl_SampleMask[0] = 0x0e;
					else gl_SampleMask[0] = 0x0f;
				#elif MULTISAMPLE_8
					if(sample.w < 0.48f) gl_SampleMask[0] = 0x00;
					else if(sample.w < 0.49f) gl_SampleMask[0] = 0x11;
					else if(sample.w < 0.50f) gl_SampleMask[0] = 0x66;
					else if(sample.w < 0.51f) gl_SampleMask[0] = 0xee;
					else gl_SampleMask[0] = 0xff;
				#endif
			#endif
		#else
			sample.w = sample.w * 4.0f - 1.5f;
		#endif
	#endif
	return sample;
}

half4 texture2DAlphaDiscard(sampler2D s_texture,half2 texcoord,half scale) {
	half4 sample = texture2D(s_texture,texcoord);
	#ifdef ALPHA
		sample.w = sample.w * scale;
		#ifdef MULTISAMPLE_0
			if(sample.w <= 0.5f) discard;
		#elif USE_ARB_SAMPLE_SHADING
			#ifdef QUALITY_HIGH
				gl_SampleMask[0] = 0x00;
				half2 dx = dFdx(texcoord);
				half2 dy = dFdy(texcoord);
				#define SAMPLE(X,Y,MASK) if(texture2D(s_texture,texcoord + dx * (X) + dy * (Y)).w * scale > 0.5f) gl_SampleMask[0] |= MASK;
				#ifdef MULTISAMPLE_2
					SAMPLE( 0.25f, 0.25f,0x01)
					SAMPLE(-0.25f,-0.25f,0x02)
				#elif MULTISAMPLE_4
					SAMPLE(-0.125f,-0.375f,0x01)
					SAMPLE( 0.375f,-0.125f,0x02)
					SAMPLE(-0.375f, 0.125f,0x04)
					SAMPLE( 0.125f, 0.375f,0x08)
				#elif MULTISAMPLE_8
					SAMPLE(-0.125f,-0.375f,0x03)
					SAMPLE( 0.375f,-0.125f,0x0c)
					SAMPLE(-0.375f, 0.125f,0x30)
					SAMPLE( 0.125f, 0.375f,0xc0)
				#endif
				#undef SAMPLE
			#else
				#ifdef MULTISAMPLE_2
					if(sample.w < 0.49f) gl_SampleMask[0] = 0x00;
					else if(sample.w < 0.50f) gl_SampleMask[0] = 0x01;
					else gl_SampleMask[0] = 0x03;
				#elif MULTISAMPLE_4
					if(sample.w < 0.48f) gl_SampleMask[0] = 0x00;
					else if(sample.w < 0.49f) gl_SampleMask[0] = 0x01;
					else if(sample.w < 0.50f) gl_SampleMask[0] = 0x06;
					else if(sample.w < 0.51f) gl_SampleMask[0] = 0x0e;
					else gl_SampleMask[0] = 0x0f;
				#elif MULTISAMPLE_8
					if(sample.w < 0.48f) gl_SampleMask[0] = 0x00;
					else if(sample.w < 0.49f) gl_SampleMask[0] = 0x11;
					else if(sample.w < 0.50f) gl_SampleMask[0] = 0x66;
					else if(sample.w < 0.51f) gl_SampleMask[0] = 0xee;
					else gl_SampleMask[0] = 0xff;
				#endif
			#endif
		#else
			if(sample.w <= 0.5f) discard;
		#endif
	#endif
	return sample;
}

/* alpha fade texture sampling
 */
void texture2DAlphaFadeDiscard(sampler2D s_texture,half threshold) {
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		half4 sample = texture2D(s_texture,getFragCoord() * (1.0f / 64.0f));
		if(threshold >= 0.0f) {
			if(sample.x >= threshold) discard;
		} else {
			if(sample.x < 1.0f + threshold) discard;
		}
	#endif
}

/* normal texture sampling
 */
half3 texture2DNormal(sampler2D s_texture,half2 texcoord) {
	half3 sample = texture2D(s_texture,texcoord).xyz;
	#ifndef USE_ARB_TEXTURE_SNORM
		sample.xy = sample.xy * 2.0f - 1.0f;
	#endif
	sample.z = sqrt(saturate(1.0f - dot(sample.xy,sample.xy)));
	return sample;
}

/* linear texture sampling
 */
half4 texture2DLinear(sampler2D s_texture,half2 texcoord,float4 texsize) {
	#ifdef ATI_R300 || ATI_R400 || ATI_R500
		half offset = 0.5f - 0.01f;
		half2 weights = fract(texcoord * texsize.xy - offset);
		half4 texcoords = texcoord.xyxy + half4(-offset,-offset,offset,offset) * texsize.zwzw;
		half4 sample_00 = texture2D(s_texture,texcoords.xy);
		half4 sample_10 = texture2D(s_texture,texcoords.zy);
		half4 sample_01 = texture2D(s_texture,texcoords.xw);
		half4 sample_11 = texture2D(s_texture,texcoords.zw);
		return lerp(lerp(sample_00,sample_10,weights.x),lerp(sample_01,sample_11,weights.x),weights.y);
	#else
		return texture2D(s_texture,texcoord);
	#endif
}

/* cubic texture sampling
 */
half3 texture_2d_cubic_filter(half x) {
	half x1 = fract(x);
	half x2 = x1 * x1;
	half x3 = x2 * x1;
	half x13 = x1 * 3.0f;
	half x23 = x2 * 3.0f;
	half x33 = x3 * 3.0f;
	half w0 = -x3 + x23 - x13 + 1.0f;
	half w1 = x33 - x23 * 2.0f + 4.0f;
	half w2 = -x33 + x23 + x13 + 1.0f;
	return half3(1.0f + x3 / (w2 + x3) - x1,1.0f - w1 / (w0 + w1) + x1,(w2 + x3) * (1.0f / 6.0f));
}

half4 texture2DCubic(sampler2D s_texture,half2 texcoord,float4 texsize) {
	#ifdef QUALITY_HIGH
		half2 texcoord_hg = texcoord * texsize.xy - 0.5f;
		half3 hg_x = texture_2d_cubic_filter(texcoord_hg.x);
		half3 hg_y = texture_2d_cubic_filter(texcoord_hg.y);
		half4 texcoords = texcoord.xyxy + half4(-hg_x.y,-hg_y.y,hg_x.x,hg_y.x) * texsize.zwzw;
		half4 sample_00 = texture2D(s_texture,texcoords.xy);
		half4 sample_10 = texture2D(s_texture,texcoords.xw);
		half4 sample_01 = texture2D(s_texture,texcoords.zy);
		half4 sample_11 = texture2D(s_texture,texcoords.zw);
		return lerp(lerp(sample_00,sample_10,hg_y.z),lerp(sample_01,sample_11,hg_y.z),hg_x.z);
	#else
		return texture2D(s_texture,texcoord);
	#endif
}

/* linear shadow sampling
 */
half shadow2DLinear(sampler2DShadow s_texture,half3 texcoord,float4 texsize) {
	#ifdef QUALITY_MEDIUM && (ATI_R300 || ATI_R400 || ATI_R500)
		half offset = 0.5f - 0.01f;
		half2 weights = fract(texcoord.xy * texsize.xy - offset);
		half4 texcoords = half4(-offset,-offset,offset,offset) * texsize.zwzw;
		half sample_00 = shadow2D(s_texture,texcoord + half3(texcoords.xy,0.0f)).x;
		half sample_10 = shadow2D(s_texture,texcoord + half3(texcoords.zy,0.0f)).x;
		half sample_01 = shadow2D(s_texture,texcoord + half3(texcoords.xw,0.0f)).x;
		half sample_11 = shadow2D(s_texture,texcoord + half3(texcoords.zw,0.0f)).x;
		return lerp(lerp(sample_00,sample_10,weights.x),lerp(sample_01,sample_11,weights.x),weights.y);
	#else
		return shadow2D(s_texture,texcoord).x;
	#endif
}

half shadow2DProjLinear(sampler2DShadow s_texture,half4 texcoord,float4 texsize) {
	#ifdef QUALITY_MEDIUM && (ATI_R300 || ATI_R400 || ATI_R500)
		half offset = 0.5f - 0.01f;
		half2 weights = fract(texcoord.xy * texsize.xy / texcoord.w - offset);
		half4 texcoords = half4(-offset,-offset,offset,offset) * texsize.zwzw * texcoord.w;
		half sample_00 = shadow2DProj(s_texture,texcoord + half4(texcoords.xy,0.0f,0.0f)).x;
		half sample_10 = shadow2DProj(s_texture,texcoord + half4(texcoords.zy,0.0f,0.0f)).x;
		half sample_01 = shadow2DProj(s_texture,texcoord + half4(texcoords.xw,0.0f,0.0f)).x;
		half sample_11 = shadow2DProj(s_texture,texcoord + half4(texcoords.zw,0.0f,0.0f)).x;
		return lerp(lerp(sample_00,sample_10,weights.x),lerp(sample_01,sample_11,weights.x),weights.y);
	#else
		return shadow2DProj(s_texture,texcoord).x;
	#endif
}

/*
 */
#include <core/shaders/common/fragment_base_shading.h>
#ifdef OMNI
	#include <core/shaders/common/fragment_base_shadow_omni.h>
#elif PROJ
	#include <core/shaders/common/fragment_base_shadow_proj.h>
#elif WORLD
	#include <core/shaders/common/fragment_base_shadow_world.h>
#endif

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

/*
 */
#include <core/shaders/common/common_base.h>

/* texture samplers
 */
sampler s_texture_0 : register(s0);
sampler s_texture_1 : register(s1);
sampler s_texture_2 : register(s2);
sampler s_texture_3 : register(s3);
sampler s_texture_4 : register(s4);
sampler s_texture_5 : register(s5);
sampler s_texture_6 : register(s6);
sampler s_texture_7 : register(s7);
sampler s_texture_8 : register(s8);
sampler s_texture_9 : register(s9);
sampler s_texture_10 : register(s10);
sampler s_texture_11 : register(s11);
sampler s_texture_12 : register(s12);
sampler s_texture_13 : register(s13);
sampler s_texture_14 : register(s14);
sampler s_texture_15 : register(s15);

/* vertex transformation
 */
float4 getPosition(float4 vertex) {
	vertex.xyz -= s_camera_offset;
	return mul(s_modelviewprojection,vertex);
}

/* fragment deferred out
 */
struct FRAGMENT_DEFERRED_OUT {
	half4 color_0 : COLOR0;
	half4 color_1 : COLOR1;
	#ifdef USE_PARALLAX || USE_DEFERRED || USE_OCCLUSION
		half4 color_2 : COLOR2;
	#endif
	#ifdef USE_PARALLAX
		half4 color_3 : COLOR3;
	#endif
};

/* deferred depth texture sampling
 */
half4 setDeferredDepth(float distance,half volumetric) {
	half3 deferred;
	distance *= 16777215.0f;
	deferred.x = floor(distance / 65536.0f);
	distance -= deferred.x * 65536.0f;
	deferred.y = floor(distance / 256.0f);
	distance -= deferred.y * 256.0f;
	deferred.z = floor(distance);
	return half4(1.0f - deferred / 255.0f,volumetric);
}

float getDeferredDepth(half4 deferred) {
	float3 factor = float3(16711680.0f / 16777215.0f,65280.0f / 16777215.0f,255.0f / 16777215.0f);
	return 1.0f - dot(deferred.xyz,factor);
}

half getDeferredVolumetric(half4 deferred) {
	return 1.0f - deferred.w;
}

/* deferred color texture sampling
 */
half4 setDeferredColor(half3 color,half glow) {
	return half4(color,glow * (1.0f / 16.0f));
}

half3 getDeferredColor(half4 deferred) {
	return deferred.xyz;
}

half getDeferredGlow(half4 deferred) {
	return deferred.w * 16.0f;
}

/* deferred normal texture sampling
 */
half4 setDeferredNormal(half3 normal,half power) {
	return half4(normal * 0.5f + 0.5f,power * (1.0f / 64.0f));
}

half3 getDeferredNormal(half4 deferred) {
	return deferred.xyz * 2.0f - 1.0f;
}

half getDeferredSpecular(half4 deferred) {
	return deferred.w * 64.0f;
}

/* deferred parallax texture sampling
 */
half4 setDeferredParallax(half2 offset) {
	half4 deferred;
	offset = saturate(offset * 0.25f + 0.5f) * 65535.0f;
	deferred.xz = floor(offset / 256.0f);
	offset -= deferred.xz * 256.0f;
	deferred.yw = floor(offset);
	return deferred / 255.0f;
}

half2 getDeferredParallax(half4 deferred) {
	half2 factor = half2(65280.0f / 65535.0f,255.0f / 65535.0f);
	return half2(dot(deferred.xy,factor),dot(deferred.zw,factor)) * 4.0f - 1.0f;
}

/* alpha test texture sampling
 */
half4 tex2DAlpha(sampler s_texture,half2 texcoord,half scale) {
	half4 sample = tex2D(s_texture,texcoord);
	#ifdef ALPHA
		sample.w = sample.w * scale;
		#ifdef MULTISAMPLE_0
			if(sample.w <= 0.5f) discard;
		#else
			sample.w = sample.w * 4.0f - 1.5f;
		#endif
	#endif
	return sample;
}

half4 tex2DAlphaDiscard(sampler s_texture,half2 texcoord,half scale) {
	half4 sample = tex2D(s_texture,texcoord);
	#ifdef ALPHA
		sample.w = sample.w * scale;
		if(sample.w <= 0.5f) discard;
	#endif
	return sample;
}

/* alpha fade texture sampling
 */
void tex2DAlphaFadeDiscard(sampler s_texture,half4 texcoord,half threshold) {
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texcoord.xy *= 64.0f;
		half4 sample = tex2Dproj(s_texture,texcoord);
		if(threshold >= 0.0f) {
			if(sample.x >= threshold) discard;
		} else {
			if(sample.x < 1.0f + threshold) discard;
		}
	#endif
}

/* normal texture sampling
 */
half3 tex2DNormal(sampler s_texture,half2 texcoord) {
	half3 sample = tex2D(s_texture,texcoord).xyz;
	sample.xy = sample.xy * 2.0f - 1.0f;
	sample.z = sqrt(saturate(1.0f - dot(sample.xy,sample.xy)));
	return sample;
}

/* linear texture sampling
 */
half4 tex2DLinear(sampler s_texture,half2 texcoord,float4 texsize) {
	#ifdef ATI_R500
		half offset = 0.5f - 0.01f;
		half2 weights = frac(texcoord * texsize.xy - offset);
		half4 texcoords = texcoord.xyxy + half4(-offset,-offset,offset,offset) * texsize.zwzw;
		half4 sample_00 = tex2D(s_texture,texcoords.xy);
		half4 sample_10 = tex2D(s_texture,texcoords.zy);
		half4 sample_01 = tex2D(s_texture,texcoords.xw);
		half4 sample_11 = tex2D(s_texture,texcoords.zw);
		return lerp(lerp(sample_00,sample_10,weights.x),lerp(sample_01,sample_11,weights.x),weights.y);
	#else
		return tex2D(s_texture,texcoord);
	#endif
}

/* cubic texture sampling
 */
half3 tex_2d_cubic_filter(half x) {
	half x1 = frac(x);
	half x2 = x1 * x1;
	half x3 = x2 * x1;
	half x13 = x1 * 3.0f;
	half x23 = x2 * 3.0f;
	half x33 = x3 * 3.0f;
	half w0 = -x3 + x23 - x13 + 1.0f;
	half w1 = x33 - x23 * 2.0f + 4.0f;
	half w2 = -x33 + x23 + x13 + 1.0f;
	return half3(1.0f + x3 / (w2 + x3) - x1,1.0f - w1 / (w0 + w1) + x1,(w2 + x3) * (1.0f / 6.0f));
}

half4 tex2DCubic(sampler s_texture,half2 texcoord,float4 texsize) {
	#ifdef QUALITY_HIGH
		half2 texcoord_hg = texcoord * texsize.xy - 0.5f;
		half3 hg_x = tex_2d_cubic_filter(texcoord_hg.x);
		half3 hg_y = tex_2d_cubic_filter(texcoord_hg.y);
		half4 texcoords = texcoord.xyxy + half4(-hg_x.y,-hg_y.y,hg_x.x,hg_y.x) * texsize.zwzw;
		half4 sample_00 = tex2D(s_texture,texcoords.xy);
		half4 sample_10 = tex2D(s_texture,texcoords.xw);
		half4 sample_01 = tex2D(s_texture,texcoords.zy);
		half4 sample_11 = tex2D(s_texture,texcoords.zw);
		return lerp(lerp(sample_00,sample_10,hg_y.z),lerp(sample_01,sample_11,hg_y.z),hg_x.z);
	#else
		return tex2D(s_texture,texcoord);
	#endif
}

/* linear shadow sampling
 */
half shadow2DLinear(sampler s_texture,half2 texcoord,float4 texsize,half compare) {
	#ifdef QUALITY_MEDIUM
		#ifdef USE_ATI_TEXTURE_FETCH4
			half2 weights = frac(texcoord * texsize.xy);
			half4 samples = (compare < tex2D(s_texture,texcoord - weights * texsize.zw));
			return lerp(lerp(samples.w,samples.x,weights.x),lerp(samples.y,samples.z,weights.x),weights.y);
		#else
			half offset = 0.5f - 0.01f;
			half2 weights = frac(texcoord * texsize.xy - offset);
			half4 texcoords = texcoord.xyxy + half4(-offset,-offset,offset,offset) * texsize.zwzw;
			half sample_00 = (compare < tex2D(s_texture,texcoords.xy).x);
			half sample_10 = (compare < tex2D(s_texture,texcoords.zy).x);
			half sample_01 = (compare < tex2D(s_texture,texcoords.xw).x);
			half sample_11 = (compare < tex2D(s_texture,texcoords.zw).x);
			return lerp(lerp(sample_00,sample_10,weights.x),lerp(sample_01,sample_11,weights.x),weights.y);
		#endif
	#else
		return (compare < tex2D(s_texture,texcoord).x);
	#endif
}

half shadow2DLodLinear(sampler s_texture,half2 texcoord,float4 texsize,half compare) {
	#ifdef QUALITY_MEDIUM
		#ifdef USE_ATI_TEXTURE_FETCH4
			half2 weights = frac(texcoord * texsize.xy);
			half4 samples = (compare < tex2Dlod(s_texture,half4(texcoord - weights * texsize.zw,0.0f,0.0f)));
			return lerp(lerp(samples.w,samples.x,weights.x),lerp(samples.y,samples.z,weights.x),weights.y);
		#else
			half offset = 0.5f - 0.01f;
			half2 weights = frac(texcoord * texsize.xy - offset);
			half4 texcoords = texcoord.xyxy + half4(-offset,-offset,offset,offset) * texsize.zwzw;
			half sample_00 = (compare < tex2Dlod(s_texture,half4(texcoords.xy,0.0f,0.0f)).x);
			half sample_10 = (compare < tex2Dlod(s_texture,half4(texcoords.zy,0.0f,0.0f)).x);
			half sample_01 = (compare < tex2Dlod(s_texture,half4(texcoords.xw,0.0f,0.0f)).x);
			half sample_11 = (compare < tex2Dlod(s_texture,half4(texcoords.zw,0.0f,0.0f)).x);
			return lerp(lerp(sample_00,sample_10,weights.x),lerp(sample_01,sample_11,weights.x),weights.y);
		#endif
	#else
		return (compare < tex2Dlod(s_texture,half4(texcoord,0.0f,0.0f)).x);
	#endif
}

/*
 */
#include <core/shaders/common/fragment_base_shading.h>
#ifdef OMNI
	#include <core/shaders/common/fragment_base_shadow_omni.h>
#elif PROJ
	#include <core/shaders/common/fragment_base_shadow_proj.h>
#elif WORLD
	#include <core/shaders/common/fragment_base_shadow_world.h>
#endif

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

SamplerComparisonState s_sampler_compare_0 : register(s0);
SamplerComparisonState s_sampler_compare_1 : register(s1);
SamplerComparisonState s_sampler_compare_2 : register(s2);
SamplerComparisonState s_sampler_compare_3 : register(s3);
SamplerComparisonState s_sampler_compare_4 : register(s4);
SamplerComparisonState s_sampler_compare_5 : register(s5);
SamplerComparisonState s_sampler_compare_6 : register(s6);
SamplerComparisonState s_sampler_compare_7 : register(s7);
SamplerComparisonState s_sampler_compare_8 : register(s8);
SamplerComparisonState s_sampler_compare_9 : register(s9);
SamplerComparisonState s_sampler_compare_10 : register(s10);
SamplerComparisonState s_sampler_compare_11 : register(s11);
SamplerComparisonState s_sampler_compare_12 : register(s12);
SamplerComparisonState s_sampler_compare_13 : register(s13);
SamplerComparisonState s_sampler_compare_14 : register(s14);
SamplerComparisonState s_sampler_compare_15 : register(s15);

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

/* vertex transformation
 */
float4 getPosition(float4 vertex) {
	vertex.xyz -= s_camera_offset;
	return mul(s_modelviewprojection,vertex);
}

/* deferred texture sampling
 */
half4 texture2DDeferredRect(TEXTURE_2DMS s_texture,SamplerState s_sampler,float2 position,float2 texsize) {
	#ifdef MULTISAMPLE_0
		half4 deferred = s_texture.SampleLevel(s_sampler_0,position * s_viewport.zw,0.0f);
	#else
		half4 deferred = s_texture.Load(int2(position * texsize * s_viewport.zw),0);
	#endif
	return deferred;
}

half4 texture2DDeferredNorm(TEXTURE_2DMS s_texture,SamplerState s_sampler,float2 texcoord) {
	#ifdef MULTISAMPLE_0
		half4 deferred = s_texture.SampleLevel(s_sampler_0,texcoord,0.0f);
	#else
		half4 deferred = s_texture.Load(int2(texcoord * s_viewport.xy),0);
	#endif
	return deferred;
}

half4 texture2DDeferredNorm2(TEXTURE_2DMS s_texture,SamplerState s_sampler,float2 texcoord) {
	#ifdef MULTISAMPLE_0
		half4 deferred = s_texture.SampleLevel(s_sampler_0,texcoord,0.0f);
	#else
		half4 deferred = s_texture.Load(int2(texcoord * s_viewport.xy * 2.0f),0);
	#endif
	return deferred;
}

/* fragment deferred out
 */
struct FRAGMENT_DEFERRED_OUT {
	float4 color_0 : SV_TARGET0;
	float4 color_1 : SV_TARGET1;
	#ifdef USE_PARALLAX || USE_DEFERRED || USE_OCCLUSION
		float4 color_2 : SV_TARGET2;
	#endif
	#ifdef USE_PARALLAX
		float4 color_3 : SV_TARGET3;
	#endif
	#ifdef ALPHA && !MULTISAMPLE_0 && USE_ALPHA_TEST_LEVEL_10_1
		uint coverage : SV_COVERAGE;
	#endif
};

/* deferred depth texture sampling
 */
half4 setDeferredDepth(float distance,half volumetric) {
	half3 deferred;
	distance *= 16777215.0f;
	deferred.x = floor(distance / 65536.0f);
	distance -= deferred.x * 65536.0f;
	deferred.y = floor(distance / 256.0f);
	distance -= deferred.y * 256.0f;
	deferred.z = floor(distance);
	return half4(1.0f - deferred / 255.0f,volumetric);
}

float getDeferredDepth(half4 deferred) {
	float3 factor = float3(16711680.0f / 16777215.0f,65280.0f / 16777215.0f,255.0f / 16777215.0f);
	return 1.0f - dot(deferred.xyz,factor);
}

half getDeferredVolumetric(half4 deferred) {
	return 1.0f - deferred.w;
}

/* deferred color texture sampling
 */
half4 setDeferredColor(half3 color,half glow) {
	return half4(color,glow * (1.0f / 16.0f));
}

half3 getDeferredColor(half4 deferred) {
	return deferred.xyz;
}

half getDeferredGlow(half4 deferred) {
	return deferred.w * 16.0f;
}

/* deferred normal texture sampling
 */
half4 setDeferredNormal(half3 normal,half power) {
	return half4(normal * 0.5f + 0.5f,power * (1.0f / 64.0f));
}

half3 getDeferredNormal(half4 deferred) {
	return deferred.xyz * 2.0f - 1.0f;
}

half getDeferredSpecular(half4 deferred) {
	return deferred.w * 64.0f;
}

/* deferred parallax texture sampling
 */
half4 setDeferredParallax(half2 offset) {
	half4 deferred;
	offset = saturate(offset * 0.25f + 0.5f) * 65535.0f;
	deferred.xz = floor(offset / 256.0f);
	offset -= deferred.xz * 256.0f;
	deferred.yw = floor(offset);
	return deferred / 255.0f;
}

half2 getDeferredParallax(half4 deferred) {
	half2 factor = half2(65280.0f / 65535.0f,255.0f / 65535.0f);
	return half2(dot(deferred.xy,factor),dot(deferred.zw,factor)) * 4.0f - 1.0f;
}

/* fragment alpha out
 */
struct FRAGMENT_ALPHA_OUT {
	float4 color : SV_TARGET;
	#ifdef ALPHA && !MULTISAMPLE_0 && USE_ALPHA_TEST_LEVEL_10_1
		uint coverage : SV_COVERAGE;
	#endif
};

/* alpha test texture sampling
 */
FRAGMENT_ALPHA_OUT texture2DAlpha(Texture2D s_texture,SamplerState s_sampler,half2 texcoord,half scale) {
	FRAGMENT_ALPHA_OUT OUT;
	OUT.color = s_texture.Sample(s_sampler,texcoord);
	#ifdef ALPHA
		OUT.color.w = OUT.color.w * scale;
		#ifdef MULTISAMPLE_0
			if(OUT.color.w <= 0.5f) discard;
		#elif USE_ALPHA_TEST_LEVEL_10_1
			#ifdef QUALITY_HIGH
				OUT.coverage = 0x00;
				half2 dx = ddx(texcoord);
				half2 dy = ddy(texcoord);
				#define SAMPLE(X,Y,MASK) if(s_texture.Sample(s_sampler,texcoord + dx * (X) + dy * (Y)).w * scale > 0.5f) OUT.coverage |= MASK;
				#ifdef MULTISAMPLE_2
					SAMPLE( 0.25f, 0.25f,0x01)
					SAMPLE(-0.25f,-0.25f,0x02)
				#elif MULTISAMPLE_4
					SAMPLE(-0.125f,-0.375f,0x01)
					SAMPLE( 0.375f,-0.125f,0x02)
					SAMPLE(-0.375f, 0.125f,0x04)
					SAMPLE( 0.125f, 0.375f,0x08)
				#elif MULTISAMPLE_8
					SAMPLE(-0.125f,-0.375f,0x03)
					SAMPLE( 0.375f,-0.125f,0x0c)
					SAMPLE(-0.375f, 0.125f,0x30)
					SAMPLE( 0.125f, 0.375f,0xc0)
				#endif
				#undef SAMPLE
			#else
				#ifdef MULTISAMPLE_2
					if(OUT.color.w < 0.49f) OUT.coverage = 0x00;
					else if(OUT.color.w < 0.50f) OUT.coverage = 0x01;
					else OUT.coverage = 0x03;
				#elif MULTISAMPLE_4
					if(OUT.color.w < 0.48f) OUT.coverage = 0x00;
					else if(OUT.color.w < 0.49f) OUT.coverage = 0x01;
					else if(OUT.color.w < 0.50f) OUT.coverage = 0x06;
					else if(OUT.color.w < 0.51f) OUT.coverage = 0x0e;
					else OUT.coverage = 0x0f;
				#elif MULTISAMPLE_8
					if(OUT.color.w < 0.48f) OUT.coverage = 0x00;
					else if(OUT.color.w < 0.49f) OUT.coverage = 0x11;
					else if(OUT.color.w < 0.50f) OUT.coverage = 0x66;
					else if(OUT.color.w < 0.51f) OUT.coverage = 0xee;
					else OUT.coverage = 0xff;
				#endif
			#endif
		#else
			OUT.color.w = OUT.color.w * 4.0f - 1.5f;
		#endif
	#endif
	return OUT;
}

FRAGMENT_ALPHA_OUT texture2DAlphaDiscard(Texture2D s_texture,SamplerState s_sampler,half2 texcoord,half scale) {
	FRAGMENT_ALPHA_OUT OUT;
	OUT.color = s_texture.Sample(s_sampler,texcoord);
	#ifdef ALPHA
		OUT.color.w = OUT.color.w * scale;
		#ifdef MULTISAMPLE_0
			if(OUT.color.w <= 0.5f) discard;
		#elif USE_ALPHA_TEST_LEVEL_10_1
			#ifdef QUALITY_HIGH
				OUT.coverage = 0x00;
				half2 dx = ddx(texcoord);
				half2 dy = ddy(texcoord);
				#define SAMPLE(X,Y,MASK) if(s_texture.Sample(s_sampler,texcoord + dx * (X) + dy * (Y)).w * scale > 0.5f) OUT.coverage |= MASK;
				#ifdef MULTISAMPLE_2
					SAMPLE( 0.25f, 0.25f,0x01)
					SAMPLE(-0.25f,-0.25f,0x02)
				#elif MULTISAMPLE_4
					SAMPLE(-0.125f,-0.375f,0x01)
					SAMPLE( 0.375f,-0.125f,0x02)
					SAMPLE(-0.375f, 0.125f,0x04)
					SAMPLE( 0.125f, 0.375f,0x08)
				#elif MULTISAMPLE_8
					SAMPLE(-0.125f,-0.375f,0x03)
					SAMPLE( 0.375f,-0.125f,0x0c)
					SAMPLE(-0.375f, 0.125f,0x30)
					SAMPLE( 0.125f, 0.375f,0xc0)
				#endif
				#undef SAMPLE
			#else
				#ifdef MULTISAMPLE_2
					if(OUT.color.w < 0.49f) OUT.coverage = 0x00;
					else if(OUT.color.w < 0.50f) OUT.coverage = 0x01;
					else OUT.coverage = 0x03;
				#elif MULTISAMPLE_4
					if(OUT.color.w < 0.48f) OUT.coverage = 0x00;
					else if(OUT.color.w < 0.49f) OUT.coverage = 0x01;
					else if(OUT.color.w < 0.50f) OUT.coverage = 0x06;
					else if(OUT.color.w < 0.51f) OUT.coverage = 0x0e;
					else OUT.coverage = 0x0f;
				#elif MULTISAMPLE_8
					if(OUT.color.w < 0.48f) OUT.coverage = 0x00;
					else if(OUT.color.w < 0.49f) OUT.coverage = 0x11;
					else if(OUT.color.w < 0.50f) OUT.coverage = 0x66;
					else if(OUT.color.w < 0.51f) OUT.coverage = 0xee;
					else OUT.coverage = 0xff;
				#endif
			#endif
		#else
			if(OUT.color.w <= 0.5f) discard;
		#endif
	#endif
	return OUT;
}

/* alpha fade texture sampling
 */
void texture2DAlphaFadeDiscard(Texture2D s_texture,SamplerState s_sampler,half2 position,half threshold) {
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		half4 sample = s_texture.Sample(s_sampler,position * (1.0f / 64.0f));
		if(threshold >= 0.0f) {
			if(sample.x >= threshold) discard;
		} else {
			if(sample.x < 1.0f + threshold) discard;
		}
	#endif
}

/* normal texture sampling
 */
half3 texture2DNormal(Texture2D s_texture,SamplerState s_sampler,half2 texcoord) {
	half3 sample = s_texture.Sample(s_sampler,texcoord).xyz;
	sample.z = sqrt(saturate(1.0f - dot(sample.xy,sample.xy)));
	return sample;
}

/* cubic texture sampling
 */
half3 texture_2d_cubic_filter(half x) {
	half x1 = frac(x);
	half x2 = x1 * x1;
	half x3 = x2 * x1;
	half x13 = x1 * 3.0f;
	half x23 = x2 * 3.0f;
	half x33 = x3 * 3.0f;
	half w0 = -x3 + x23 - x13 + 1.0f;
	half w1 = x33 - x23 * 2.0f + 4.0f;
	half w2 = -x33 + x23 + x13 + 1.0f;
	return half3(1.0f + x3 / (w2 + x3) - x1,1.0f - w1 / (w0 + w1) + x1,(w2 + x3) * (1.0f / 6.0f));
}

half4 texture2DCubic(Texture2D s_texture,SamplerState s_sampler,half2 texcoord,float4 texsize) {
	#ifdef QUALITY_HIGH
		half2 texcoord_hg = texcoord * texsize.xy - 0.5f;
		half3 hg_x = texture_2d_cubic_filter(texcoord_hg.x);
		half3 hg_y = texture_2d_cubic_filter(texcoord_hg.y);
		half4 texcoords = texcoord.xyxy + half4(-hg_x.y,-hg_y.y,hg_x.x,hg_y.x) * texsize.zwzw;
		half4 sample_00 = s_texture.Sample(s_sampler,texcoords.xy);
		half4 sample_10 = s_texture.Sample(s_sampler,texcoords.xw);
		half4 sample_01 = s_texture.Sample(s_sampler,texcoords.zy);
		half4 sample_11 = s_texture.Sample(s_sampler,texcoords.zw);
		return lerp(lerp(sample_00,sample_10,hg_y.z),lerp(sample_01,sample_11,hg_y.z),hg_x.z);
	#else
		return s_texture.Sample(s_sampler,texcoord);
	#endif
}

/* linear shadow sampling
 */
float shadow2DArrayLinear(Texture2DArray s_texture,SamplerState s_sampler,float3 texcoord,float4 texsize,float compare) {
	#ifdef QUALITY_MEDIUM
		float offset = 0.5f - 0.01f;
		float2 weights = frac(texcoord.xy * texsize.xy - offset);
		float4 texcoords = float4(-offset,-offset,offset,offset) * texsize.zwzw;
		float sample_00 = (compare < s_texture.Sample(s_sampler,texcoord + float3(texcoords.xy,0.0f)).x);
		float sample_10 = (compare < s_texture.Sample(s_sampler,texcoord + float3(texcoords.zy,0.0f)).x);
		float sample_01 = (compare < s_texture.Sample(s_sampler,texcoord + float3(texcoords.xw,0.0f)).x);
		float sample_11 = (compare < s_texture.Sample(s_sampler,texcoord + float3(texcoords.zw,0.0f)).x);
		return lerp(lerp(sample_00,sample_10,weights.x),lerp(sample_01,sample_11,weights.x),weights.y);
	#else
		return (compare < s_texture.Sample(s_sampler,texcoord).x);
	#endif
}

float shadow2DArrayLevelZeroLinear(Texture2DArray s_texture,SamplerState s_sampler,float3 texcoord,float4 texsize,float compare) {
	#ifdef QUALITY_MEDIUM
		float offset = 0.5f - 0.01f;
		float2 weights = frac(texcoord.xy * texsize.xy - offset);
		float4 texcoords = float4(-offset,-offset,offset,offset) * texsize.zwzw;
		float sample_00 = (compare < s_texture.SampleLevel(s_sampler,texcoord + float3(texcoords.xy,0.0f),0.0f).x);
		float sample_10 = (compare < s_texture.SampleLevel(s_sampler,texcoord + float3(texcoords.zy,0.0f),0.0f).x);
		float sample_01 = (compare < s_texture.SampleLevel(s_sampler,texcoord + float3(texcoords.xw,0.0f),0.0f).x);
		float sample_11 = (compare < s_texture.SampleLevel(s_sampler,texcoord + float3(texcoords.zw,0.0f),0.0f).x);
		return lerp(lerp(sample_00,sample_10,weights.x),lerp(sample_01,sample_11,weights.x),weights.y);
	#else
		return (compare < s_texture.SampleLevel(s_sampler,texcoord,0.0f).x);
	#endif
}

/*
 */
#include <core/shaders/common/fragment_base_shading.h>
#ifdef OMNI
	#include <core/shaders/common/fragment_base_shadow_omni.h>
#elif PROJ
	#include <core/shaders/common/fragment_base_shadow_proj.h>
#elif WORLD
	#include <core/shaders/common/fragment_base_shadow_world.h>
#endif

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

/*
 */
#include <core/shaders/common/common_base.h>

/* vertex transformation
 */
float4 getPosition(float4 vertex) {
	vertex.xyz -= s_camera_offset;
	return mul(s_modelviewprojection,vertex);
}

/* fragment deferred out
 */
struct FRAGMENT_DEFERRED_OUT {
	half4 color_0 : COLOR0;
	half4 color_1 : COLOR1;
	#ifdef USE_PARALLAX || USE_DEFERRED || USE_OCCLUSION
		half4 color_2 : COLOR2;
	#endif
	#ifdef USE_PARALLAX
		half4 color_3 : COLOR3;
	#endif
};

/* deferred depth texture sampling
 */
half4 setDeferredDepth(float distance,half volumetric) {
	half3 deferred;
	distance *= 16777215.0f;
	deferred.x = floor(distance / 65536.0f);
	distance -= deferred.x * 65536.0f;
	deferred.y = floor(distance / 256.0f);
	distance -= deferred.y * 256.0f;
	deferred.z = floor(distance);
	return half4(1.0f - deferred / 255.0f,volumetric);
}

float getDeferredDepth(half4 deferred) {
	float3 factor = float3(16711680.0f / 16777215.0f,65280.0f / 16777215.0f,255.0f / 16777215.0f);
	return 1.0f - dot(deferred.xyz,factor);
}

half getDeferredVolumetric(half4 deferred) {
	return 1.0f - deferred.w;
}

/* deferred color texture sampling
 */
half4 setDeferredColor(half3 color,half glow) {
	return half4(color,glow * (1.0f / 16.0f));
}

half3 getDeferredColor(half4 deferred) {
	return deferred.xyz;
}

half getDeferredGlow(half4 deferred) {
	return deferred.w * 16.0f;
}

/* deferred normal texture sampling
 */
half4 setDeferredNormal(half3 normal,half power) {
	return half4(normal * 0.5f + 0.5f,power * (1.0f / 64.0f));
}

half3 getDeferredNormal(half4 deferred) {
	return deferred.xyz * 2.0f - 1.0f;
}

half getDeferredSpecular(half4 deferred) {
	return deferred.w * 64.0f;
}

/* deferred parallax texture sampling
 */
half4 setDeferredParallax(half2 offset) {
	half4 deferred;
	offset = saturate(offset * 0.25f + 0.5f) * 65535.0f;
	deferred.xz = floor(offset / 256.0f);
	offset -= deferred.xz * 256.0f;
	deferred.yw = floor(offset);
	return deferred / 255.0f;
}

half2 getDeferredParallax(half4 deferred) {
	half2 factor = half2(65280.0f / 65535.0f,255.0f / 65535.0f);
	return half2(dot(deferred.xy,factor),dot(deferred.zw,factor)) * 4.0f - 1.0f;
}

/* alpha test texture sampling
 */
half4 tex2DAlpha(sampler s_texture,half2 texcoord,half scale) {
	half4 sample = h4tex2D(s_texture,texcoord);
	#ifdef ALPHA
		sample.w = sample.w * scale;
		if(sample.w <= 0.5f) discard;
	#endif
	return sample;
}

half4 tex2DAlphaDiscard(sampler s_texture,half2 texcoord,half scale) {
	half4 sample = h4tex2D(s_texture,texcoord);
	#ifdef ALPHA
		sample.w = sample.w * scale;
		if(sample.w <= 0.5f) discard;
	#endif
	return sample;
}

/* alpha fade texture sampling
 */
void tex2DAlphaFadeDiscard(sampler s_texture,half4 texcoord,half threshold) {
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texcoord.xy *= 64.0f;
		half sample = h1tex2Dproj(s_texture,texcoord.xyw);
		if(threshold >= 0.0f) {
			if(sample >= threshold) discard;
		} else {
			if(sample < 1.0f + threshold) discard;
		}
	#endif
}

/* normal texture sampling
 */
half3 tex2DNormal(sampler s_texture,half2 texcoord) {
	half3 sample = h3tex2D(s_texture,texcoord);
	sample.z = sqrt(saturate(1.0f - dot(sample.xy,sample.xy)));
	return sample;
}

/* depth texture sampling
 */
half tex2DDepth(sampler s_texture,half2 texcoord) {
	half sample = texDepth2D_precise(s_texture,texcoord);
	return 1.0f / (s_depth_range.z - s_depth_range.w * sample);
}

half tex2DDepthProj(sampler s_texture,half3 texcoord) {
	half sample = texDepth2Dproj_precise(s_texture,texcoord);
	return 1.0f / (s_depth_range.z - s_depth_range.w * sample);
}

/*
 */
#include <core/shaders/common/fragment_base_shading.h>
#ifdef OMNI
	#include <core/shaders/common/fragment_base_shadow_omni.h>
#elif PROJ
	#include <core/shaders/common/fragment_base_shadow_proj.h>
#elif WORLD
	#include <core/shaders/common/fragment_base_shadow_world.h>
#endif

#endif

#endif /* __FRAGMENT_BASE_H__ */
