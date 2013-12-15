/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_occlusion_blur.shader
 * Desc:    Render occlusion blur shader
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

/* s_texture_0 is screen texture
 * s_texture_1 is sample texture
 * s_texture_2 is light texture
 * s_texture_3 is deferred depth texture
 * s_texture_4 is deferred color texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;
uniform sampler2D s_texture_1;
uniform sampler2D s_texture_2;
uniform SAMPLER_2DMS s_texture_3;
uniform SAMPLER_2DMS s_texture_4;

uniform half distance_threshold;
uniform half4 ambient;
uniform half4 indirect;

/*
 */
half4 get_occlusion(float2 texcoord,half depth) {
	
	texcoord = floor(texcoord * s_viewport.xy * 0.5f) * s_viewport.zw * 2.0f;
	
	#define SAMPLE(X,Y) { \
		half2 sample_texcoord = texcoord + s_viewport.zw * half2(X,Y); \
		half sample_depth = texture2D(s_texture_1,sample_texcoord).w; \
		half4 sample_occlusion = texture2D(s_texture_2,sample_texcoord); \
		if(abs(sample_depth - depth) < distance_threshold) { \
			occlusion += sample_occlusion; \
			weight += 1.0f; \
		} \
	}
	
	half weight = 0.0f;
	half4 occlusion = half4(0.0f);
	
	SAMPLE(-3.0f,-3.0f);
	SAMPLE(-3.0f,-1.0f);
	SAMPLE(-3.0f, 1.0f);
	SAMPLE(-3.0f, 3.0f);
	SAMPLE(-1.0f,-3.0f);
	SAMPLE(-1.0f,-1.0f);
	SAMPLE(-1.0f, 1.0f);
	SAMPLE(-1.0f, 3.0f);
	SAMPLE( 1.0f,-3.0f);
	SAMPLE( 1.0f,-1.0f);
	SAMPLE( 1.0f, 1.0f);
	SAMPLE( 1.0f, 3.0f);
	SAMPLE( 3.0f,-3.0f);
	SAMPLE( 3.0f,-1.0f);
	SAMPLE( 3.0f, 1.0f);
	SAMPLE( 3.0f, 3.0f);
	
	#undef SAMPLE
	
	if(weight > 0.0f) return occlusion / weight;
	
	return texture2D(s_texture_2,texcoord);
}

/*
 */
#ifdef !MULTISAMPLE_0 && USE_ARB_TEXTURE_MULTISAMPLE

/*
 */
half4 get_occlusion(float2 texcoord,half depth[MULTISAMPLE_SAMPLES]) {
	
	half sample_depth[16];
	half4 sample_occlusion[16];
	
	int2 itexcoord = int2(floor(texcoord * s_viewport.xy * 0.5f));
	
	sample_depth[0]  = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(0,0)).w;
	sample_depth[1]  = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(0,1)).w;
	sample_depth[2]  = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(0,2)).w;
	sample_depth[3]  = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(0,3)).w;
	sample_depth[4]  = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(1,0)).w;
	sample_depth[5]  = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(1,1)).w;
	sample_depth[6]  = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(1,2)).w;
	sample_depth[7]  = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(1,3)).w;
	sample_depth[8]  = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(2,0)).w;
	sample_depth[9]  = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(2,1)).w;
	sample_depth[10] = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(2,2)).w;
	sample_depth[11] = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(2,3)).w;
	sample_depth[12] = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(3,0)).w;
	sample_depth[13] = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(3,1)).w;
	sample_depth[14] = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(3,2)).w;
	sample_depth[15] = texelFetch2DOffset(s_texture_1,itexcoord,0,int2(3,3)).w;
	
	sample_occlusion[0]  = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(0,0));
	sample_occlusion[1]  = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(0,1));
	sample_occlusion[2]  = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(0,2));
	sample_occlusion[3]  = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(0,3));
	sample_occlusion[4]  = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(1,0));
	sample_occlusion[5]  = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(1,1));
	sample_occlusion[6]  = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(1,2));
	sample_occlusion[7]  = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(1,3));
	sample_occlusion[8]  = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(2,0));
	sample_occlusion[9]  = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(2,1));
	sample_occlusion[10] = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(2,2));
	sample_occlusion[11] = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(2,3));
	sample_occlusion[12] = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(3,0));
	sample_occlusion[13] = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(3,1));
	sample_occlusion[14] = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(3,2));
	sample_occlusion[15] = texelFetch2DOffset(s_texture_2,itexcoord,0,int2(3,3));
	
	#define SAMPLE(SAMPLE,NUM) { \
		if(abs(sample_depth[NUM] - depth[SAMPLE]) < distance_threshold) { \
			occlusions[SAMPLE] += sample_occlusion[NUM]; \
			weights[SAMPLE] += 1.0f; \
		} \
	}
	
	half weights[MULTISAMPLE_SAMPLES];
	half4 occlusions[MULTISAMPLE_SAMPLES];
	
	for(int i = 0; i < MULTISAMPLE_SAMPLES; i++) {
		weights[i] = 0.0f;
		occlusions[i] = half4(0.0f);
		SAMPLE(i,0);
		SAMPLE(i,1);
		SAMPLE(i,2);
		SAMPLE(i,3);
		SAMPLE(i,4);
		SAMPLE(i,5);
		SAMPLE(i,6);
		SAMPLE(i,7);
		SAMPLE(i,8);
		SAMPLE(i,9);
		SAMPLE(i,10);
		SAMPLE(i,11);
		SAMPLE(i,12);
		SAMPLE(i,13);
		SAMPLE(i,14);
		SAMPLE(i,15);
	}
	
	#undef SAMPLE
	
	half weight = 0.0f;
	half4 occlusion = half4(0.0f);
	
	for(int i = 0; i < MULTISAMPLE_SAMPLES; i++) {
		if(weights[i] > 0.0f) {
			occlusion += occlusions[i] / weights[i];
			weight += 1.0f;
		}
	}
	
	if(weight > 0.0f) return occlusion / weight;
	
	return sample_occlusion[0];
}

#endif

/*
 */
void main() {
	
	half4 occlusion;
	
	#ifdef MULTISAMPLE_0 || !USE_ARB_TEXTURE_MULTISAMPLE
		half depth = getDeferredDepth(texture2D(s_texture_3,gl_TexCoord[0].xy));
		occlusion = get_occlusion(gl_TexCoord[0].xy,depth);
	#else
		half depth[MULTISAMPLE_SAMPLES];
		int2 texcoord = int2(gl_TexCoord[0].xy * s_viewport.xy);
		depth[0] = getDeferredDepth(texelFetch(s_texture_3,texcoord,0));
		half min_depth = depth[0];
		half max_depth = depth[0];
		for(int i = 1; i < MULTISAMPLE_SAMPLES; i++) {
			depth[i] = getDeferredDepth(texelFetch(s_texture_3,texcoord,i));
			min_depth = min(min_depth,depth[i]);
			max_depth = max(max_depth,depth[i]);
		}
		if(max_depth - min_depth > 1e-6f) occlusion = get_occlusion(gl_TexCoord[0].xy,depth);
		else occlusion = get_occlusion(gl_TexCoord[0].xy,depth[0]);
	#endif
	
	#ifdef SHOW_OCCLUSION
		half4 screen = half4(1.0f);
	#else
		half4 screen = texture2D(s_texture_0,gl_TexCoord[0].xy);
	#endif
	half3 color = getDeferredColor(texture2DDeferredNorm(s_texture_4,gl_TexCoord[0].xy));
	
	gl_FragColor = half4(screen.xyz * pow(ambient.x + (1.0f - occlusion.w) * ambient.y,ambient.z) + color * pow(occlusion.xyz,half3(indirect.y)) * indirect.x,screen.w);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
};

half distance_threshold;
half4 ambient;
half4 indirect;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half depth = getDeferredDepth(tex2D(s_texture_3,IN.texcoord_0));
	
	half2 texcoord = floor(IN.texcoord_0 * s_viewport.xy * 0.5f) * (s_viewport.zw * 2.0f);
	
	#define SAMPLE(X,Y) { \
		half2 sample_texcoord = texcoord + s_viewport.zw * half2(X,Y); \
		half sample_depth = tex2D(s_texture_1,sample_texcoord).w; \
		half4 sample_occlusion = tex2D(s_texture_2,sample_texcoord); \
		[flatten] if(abs(sample_depth - depth) < distance_threshold) { \
			occlusion += sample_occlusion; \
			weight += 1.0f; \
		} \
	}
	
	half weight = 0.0f;
	half4 occlusion = 0.0f;
	
	SAMPLE(-3.0f,-3.0f);
	SAMPLE(-3.0f,-1.0f);
	SAMPLE(-3.0f, 1.0f);
	SAMPLE(-3.0f, 3.0f);
	SAMPLE(-1.0f,-3.0f);
	SAMPLE(-1.0f,-1.0f);
	SAMPLE(-1.0f, 1.0f);
	SAMPLE(-1.0f, 3.0f);
	SAMPLE( 1.0f,-3.0f);
	SAMPLE( 1.0f,-1.0f);
	SAMPLE( 1.0f, 1.0f);
	SAMPLE( 1.0f, 3.0f);
	SAMPLE( 3.0f,-3.0f);
	SAMPLE( 3.0f,-1.0f);
	SAMPLE( 3.0f, 1.0f);
	SAMPLE( 3.0f, 3.0f);
	
	#undef SAMPLE
	
	[flatten] if(weight > 0.0f) occlusion /= weight;
	else occlusion = tex2D(s_texture_2,texcoord);
	
	#ifdef SHOW_OCCLUSION
		half4 screen = 1.0f;
	#else
		half4 screen = tex2D(s_texture_0,IN.texcoord_0);
	#endif
	half3 color = getDeferredColor(tex2D(s_texture_4,IN.texcoord_0));
	
	return half4(screen.xyz * pow(ambient.x + (1.0f - occlusion.w) * ambient.y,ambient.z) + color * pow(occlusion.xyz,indirect.y) * indirect.x,screen.w);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
Texture2D s_texture_1 : register(t1);
Texture2D s_texture_2 : register(t2);
TEXTURE_2DMS s_texture_3 : register(t3);
TEXTURE_2DMS s_texture_4 : register(t4);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
};

float distance_threshold;
float4 ambient;
float4 indirect;

/*
 */
half4 get_occlusion(float2 texcoord,half depth) {
	
	int3 itexcoord = int3(floor(texcoord * s_viewport.xy * 0.5f - 0.25f),0);
	
	#define SAMPLE(X,Y) { \
		half sample_depth = s_texture_1.Load(itexcoord,int2(X,Y)).w; \
		half4 sample_occlusion = s_texture_2.Load(itexcoord,int2(X,Y)); \
		[flatten] if(abs(sample_depth - depth) < distance_threshold) { \
			occlusion += sample_occlusion; \
			weight += 1.0f; \
		} \
	}
	
	half weight = 0.0f;
	half4 occlusion = 0.0f;
	
	SAMPLE(0,0);
	SAMPLE(0,1);
	SAMPLE(0,2);
	SAMPLE(0,3);
	SAMPLE(1,0);
	SAMPLE(1,1);
	SAMPLE(1,2);
	SAMPLE(1,3);
	SAMPLE(2,0);
	SAMPLE(2,1);
	SAMPLE(2,2);
	SAMPLE(2,3);
	SAMPLE(3,0);
	SAMPLE(3,1);
	SAMPLE(3,2);
	SAMPLE(3,3);
	
	#undef SAMPLE
	
	[flatten] if(weight > 0.0f) return occlusion / weight;
	
	return s_texture_2.Load(itexcoord);
}

#ifndef MULTISAMPLE_0

/*
 */
half4 get_occlusion(float2 texcoord,half depth[MULTISAMPLE_SAMPLES]) {
	
	half sample_depth[16];
	half4 sample_occlusion[16];
	
	int3 itexcoord = int3(floor(texcoord * s_viewport.xy * 0.5f - 0.25f),0);
	
	sample_depth[0]  = s_texture_1.Load(itexcoord,int2(0,0)).w;
	sample_depth[1]  = s_texture_1.Load(itexcoord,int2(0,1)).w;
	sample_depth[2]  = s_texture_1.Load(itexcoord,int2(0,2)).w;
	sample_depth[3]  = s_texture_1.Load(itexcoord,int2(0,3)).w;
	sample_depth[4]  = s_texture_1.Load(itexcoord,int2(1,0)).w;
	sample_depth[5]  = s_texture_1.Load(itexcoord,int2(1,1)).w;
	sample_depth[6]  = s_texture_1.Load(itexcoord,int2(1,2)).w;
	sample_depth[7]  = s_texture_1.Load(itexcoord,int2(1,3)).w;
	sample_depth[8]  = s_texture_1.Load(itexcoord,int2(2,0)).w;
	sample_depth[9]  = s_texture_1.Load(itexcoord,int2(2,1)).w;
	sample_depth[10] = s_texture_1.Load(itexcoord,int2(2,2)).w;
	sample_depth[11] = s_texture_1.Load(itexcoord,int2(2,3)).w;
	sample_depth[12] = s_texture_1.Load(itexcoord,int2(3,0)).w;
	sample_depth[13] = s_texture_1.Load(itexcoord,int2(3,1)).w;
	sample_depth[14] = s_texture_1.Load(itexcoord,int2(3,2)).w;
	sample_depth[15] = s_texture_1.Load(itexcoord,int2(3,3)).w;
	
	sample_occlusion[0]  = s_texture_2.Load(itexcoord,int2(0,0));
	sample_occlusion[1]  = s_texture_2.Load(itexcoord,int2(0,1));
	sample_occlusion[2]  = s_texture_2.Load(itexcoord,int2(0,2));
	sample_occlusion[3]  = s_texture_2.Load(itexcoord,int2(0,3));
	sample_occlusion[4]  = s_texture_2.Load(itexcoord,int2(1,0));
	sample_occlusion[5]  = s_texture_2.Load(itexcoord,int2(1,1));
	sample_occlusion[6]  = s_texture_2.Load(itexcoord,int2(1,2));
	sample_occlusion[7]  = s_texture_2.Load(itexcoord,int2(1,3));
	sample_occlusion[8]  = s_texture_2.Load(itexcoord,int2(2,0));
	sample_occlusion[9]  = s_texture_2.Load(itexcoord,int2(2,1));
	sample_occlusion[10] = s_texture_2.Load(itexcoord,int2(2,2));
	sample_occlusion[11] = s_texture_2.Load(itexcoord,int2(2,3));
	sample_occlusion[12] = s_texture_2.Load(itexcoord,int2(3,0));
	sample_occlusion[13] = s_texture_2.Load(itexcoord,int2(3,1));
	sample_occlusion[14] = s_texture_2.Load(itexcoord,int2(3,2));
	sample_occlusion[15] = s_texture_2.Load(itexcoord,int2(3,3));
	
	#define SAMPLE(SAMPLE,NUM) { \
		if(abs(sample_depth[NUM] - depth[SAMPLE]) < distance_threshold) { \
			occlusions[SAMPLE] += sample_occlusion[NUM]; \
			weights[SAMPLE] += 1.0f; \
		} \
	}
	
	half weights[MULTISAMPLE_SAMPLES];
	half4 occlusions[MULTISAMPLE_SAMPLES];
	
	[unroll] for(int i = 0; i < MULTISAMPLE_SAMPLES; i++) {
		weights[i] = 0.0f;
		occlusions[i] = 0.0f;
		SAMPLE(i,0);
		SAMPLE(i,1);
		SAMPLE(i,2);
		SAMPLE(i,3);
		SAMPLE(i,4);
		SAMPLE(i,5);
		SAMPLE(i,6);
		SAMPLE(i,7);
		SAMPLE(i,8);
		SAMPLE(i,9);
		SAMPLE(i,10);
		SAMPLE(i,11);
		SAMPLE(i,12);
		SAMPLE(i,13);
		SAMPLE(i,14);
		SAMPLE(i,15);
	}
	
	#undef SAMPLE
	
	half weight = 0.0f;
	half4 occlusion = 0.0f;
	
	[unroll] for(int j = 0; j < MULTISAMPLE_SAMPLES; j++) {
		[flatten] if(weights[j] > 0.0f) {
			occlusion += occlusions[j] / weights[j];
			weight += 1.0f;
		}
	}
	
	[flatten] if(weight > 0.0f) return occlusion / weight;
	
	return sample_occlusion[0];
}

#endif

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 occlusion;
	
	#ifdef MULTISAMPLE_0
		half depth = getDeferredDepth(s_texture_3.Sample(s_sampler_3,IN.texcoord_0));
		occlusion = get_occlusion(IN.texcoord_0,depth);
	#else
		half depth[MULTISAMPLE_SAMPLES];
		int2 texcoord = int2(IN.texcoord_0 * s_viewport.xy);
		depth[0] = getDeferredDepth(s_texture_3.Load(texcoord,0));
		half min_depth = depth[0];
		half max_depth = depth[0];
		[unroll] for(int i = 1; i < MULTISAMPLE_SAMPLES; i++) {
			depth[i] = getDeferredDepth(s_texture_3.Load(texcoord,i));
			min_depth = min(min_depth,depth[i]);
			max_depth = max(max_depth,depth[i]);
		}
		[branch] if(max_depth - min_depth > 1e-6f) occlusion = get_occlusion(IN.texcoord_0,depth);
		else occlusion = get_occlusion(IN.texcoord_0,depth[0]);
	#endif
	
	#ifdef SHOW_OCCLUSION
		half4 screen = 1.0f;
	#else
		half4 screen = s_texture_0.Sample(s_sampler_0,IN.texcoord_0);
	#endif
	half3 color = getDeferredColor(texture2DDeferredNorm(s_texture_4,s_sampler_4,IN.texcoord_0));
	
	return half4(screen.xyz * pow(ambient.x + (1.0f - occlusion.w) * ambient.y,ambient.z) + color * pow(occlusion.xyz,indirect.y) * indirect.x,screen.w);
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

##pragma disablepc all

uniform sampler2D s_texture_0 : TEXUNIT0;
uniform sampler2D s_texture_1 : TEXUNIT1;
uniform sampler2D s_texture_2 : TEXUNIT2;
uniform sampler2D s_texture_3 : TEXUNIT3;
uniform sampler2D s_texture_4 : TEXUNIT4;

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
};

uniform half distance_threshold;
uniform half4 ambient;
uniform half4 indirect;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half depth = getDeferredDepth(h4tex2D(s_texture_3,IN.texcoord_0));
	
	half2 texcoord = floor(IN.texcoord_0 * s_viewport.xy * 0.5f) * (s_viewport.zw * 2.0f);
	
	#define SAMPLE(X,Y) { \
		half2 sample_texcoord = texcoord + s_viewport.zw * half2(X,Y); \
		half sample_depth = h4tex2D(s_texture_1,sample_texcoord).w; \
		half4 sample_occlusion = h4tex2D(s_texture_2,sample_texcoord); \
		[flatten] if(abs(sample_depth - depth) < distance_threshold) { \
			occlusion += sample_occlusion; \
			weight += 1.0f; \
		} \
	}
	
	half weight = 0.0f;
	half4 occlusion = 0.0f;
	
	SAMPLE(-3.0f,-3.0f);
	SAMPLE(-3.0f,-1.0f);
	SAMPLE(-3.0f, 1.0f);
	SAMPLE(-3.0f, 3.0f);
	SAMPLE(-1.0f,-3.0f);
	SAMPLE(-1.0f,-1.0f);
	SAMPLE(-1.0f, 1.0f);
	SAMPLE(-1.0f, 3.0f);
	SAMPLE( 1.0f,-3.0f);
	SAMPLE( 1.0f,-1.0f);
	SAMPLE( 1.0f, 1.0f);
	SAMPLE( 1.0f, 3.0f);
	SAMPLE( 3.0f,-3.0f);
	SAMPLE( 3.0f,-1.0f);
	SAMPLE( 3.0f, 1.0f);
	SAMPLE( 3.0f, 3.0f);
	
	#undef SAMPLE
	
	[flatten] if(weight > 0.0f) occlusion /= weight;
	else occlusion = h4tex2D(s_texture_2,texcoord);
	
	#ifdef SHOW_OCCLUSION
		half4 screen = 1.0f;
	#else
		half4 screen = h4tex2D(s_texture_0,IN.texcoord_0);
	#endif
	half3 color = getDeferredColor(h4tex2D(s_texture_4,IN.texcoord_0));
	
	return half4(screen.xyz * pow(ambient.x + (1.0f - occlusion.w) * ambient.y,ambient.z) + color * pow(occlusion.xyz,indirect.y) * indirect.x,screen.w);
}

#endif
