/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_scattering_sample.shader
 * Desc:    Render scattering sample shader
 * Version: 1.23
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

/* s_texture_0 is deferred depth texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform SAMPLER_2DMS s_texture_0;

uniform half power;
uniform half4 sun_color;
uniform half4 sun_angle;
uniform half4 up_direction;
uniform half4 light_direction;
uniform half4 height_falloff;
uniform half4 greenstein;
uniform float4 ray_beta;
uniform float4 mie_beta;
uniform float4 ray_dash;
uniform float4 mie_dash;

#ifdef USE_ARB_BLEND_FUNC_EXTENDED

/*
 */
struct SCATTERING_OUT {
	half3 color_0;
	half3 color_1;
};

/*
 */
SCATTERING_OUT get_scattering(float3 direction,half depth) {
	
	SCATTERING_OUT OUT;
	
	float height = dot(direction,up_direction.xyz) * depth - height_falloff.x;
	
	float ray_density = ray_beta.w;
	float mie_density = mie_beta.w;
	float2 falloff = height_falloff.yz * height;
	if(abs(falloff.x) > 0.0f) ray_density *= (1.0f - exp2(-falloff.x)) / falloff.x;
	if(abs(falloff.y) > 0.0f) mie_density *= (1.0f - exp2(-falloff.y)) / falloff.y;
	
	half distance = pow(depth,power);
	half3 scattering = exp2(-(ray_beta.xyz * ray_density + mie_beta.xyz * mie_density) * distance);
	
	float angle = dot(direction,light_direction.xyz);
	float ray_phase = 1.0f + angle * angle;
	float mie_greenstein = greenstein.y - greenstein.z * angle;
	float mie_phase = min(greenstein.x * rsqrt(mie_greenstein),greenstein.w * distance);
	half3 inscattering = ray_dash.xyz * ray_phase + mie_dash.xyz * mie_phase;
	
	half3 sun = sun_color.xyz * saturate(pow(max(angle,0.0f),sun_angle.x) * sun_angle.y);
	
	OUT.color_0 = inscattering * (1.0f - scattering) + sun * half(depth > 0.99f);
	OUT.color_1 = scattering;
	
	return OUT;
}

/*
 */
void main() {
	
	SCATTERING_OUT OUT;
	
	float3 direction = normalize(gl_TexCoord[1].xyz);
	
	#ifdef MULTISAMPLE_0 || !USE_ARB_TEXTURE_MULTISAMPLE
		half depth = getDeferredDepth(texture2D(s_texture_0,gl_TexCoord[0].xy));
		OUT = get_scattering(direction,depth);
	#elif USE_ARB_SAMPLE_SHADING
		int2 texcoord = int2(gl_TexCoord[0].xy * s_viewport.xy);
		#ifdef MULTISAMPLE
			half depth = getDeferredDepth(texelFetch(s_texture_0,texcoord,gl_SampleID));
			OUT = get_scattering(direction,depth);
		#else
			half depth = getDeferredDepth(texelFetch(s_texture_0,texcoord,0));
			half min_depth = depth;
			half max_depth = depth;
			for(int i = 1; i < MULTISAMPLE_SAMPLES; i++) {
				depth = getDeferredDepth(texelFetch(s_texture_0,texcoord,i));
				min_depth = min(min_depth,depth);
				max_depth = max(max_depth,depth);
			}
			if(max_depth - min_depth > 1e-6f) discard;
			OUT = get_scattering(direction,depth);
		#endif
	#else
		half depth[MULTISAMPLE_SAMPLES];
		int2 texcoord = int2(gl_TexCoord[0].xy * s_viewport.xy);
		depth[0] = getDeferredDepth(texelFetch(s_texture_0,texcoord,0));
		half min_depth = depth[0];
		half max_depth = depth[0];
		for(int i = 1; i < MULTISAMPLE_SAMPLES; i++) {
			depth[i] = getDeferredDepth(texelFetch(s_texture_0,texcoord,i));
			min_depth = min(min_depth,depth[i]);
			max_depth = max(max_depth,depth[i]);
		}
		OUT = get_scattering(direction,depth[0]);
		if(max_depth - min_depth > 1e-6f) {
			for(int i = 1; i < MULTISAMPLE_SAMPLES; i++) {
				SCATTERING_OUT SAMPLE = get_scattering(direction,depth[i]);
				OUT.color_0 += SAMPLE.color_0;
				OUT.color_1 += SAMPLE.color_1;
			}
			OUT.color_0 *= MULTISAMPLE_ISAMPLES;
			OUT.color_1 *= MULTISAMPLE_ISAMPLES;
		}
	#endif
	
	gl_FragData[0] = half4(OUT.color_0,1.0f);
	gl_FragData[1] = half4(OUT.color_1,1.0f);
}

#else

/*
 */
float3 get_scattering(float3 direction,half depth) {
	
	float height = dot(direction,up_direction.xyz) * depth - height_falloff.x;
	
	float ray_density = ray_beta.w;
	float mie_density = mie_beta.w;
	float2 falloff = height_falloff.yz * height;
	if(abs(falloff.x) > 0.0f) ray_density *= (1.0f - exp2(-falloff.x)) / falloff.x;
	if(abs(falloff.y) > 0.0f) mie_density *= (1.0f - exp2(-falloff.y)) / falloff.y;
	
	half distance = pow(depth,power);
	half3 scattering = exp2(-(ray_beta.xyz * ray_density + mie_beta.xyz * mie_density) * distance);
	
	#ifdef INSCATTERING
		float angle = dot(direction,light_direction.xyz);
		float ray_phase = 1.0f + angle * angle;
		float mie_greenstein = greenstein.y - greenstein.z * angle;
		float mie_phase = min(greenstein.x * rsqrt(mie_greenstein),greenstein.w * distance);
		half3 inscattering = ray_dash.xyz * ray_phase + mie_dash.xyz * mie_phase;
		
		half3 sun = sun_color.xyz * saturate(pow(max(angle,0.0f),sun_angle.x) * sun_angle.y);
		half3 color = inscattering * (1.0f - scattering) + sun * half(depth > 0.99f);
	#else
		half3 color = scattering;
	#endif
	
	return color;
}

/*
 */
void main() {
	
	half3 color;
	
	float3 direction = normalize(gl_TexCoord[1].xyz);
	
	#ifdef MULTISAMPLE_0 || !USE_ARB_TEXTURE_MULTISAMPLE
		half depth = getDeferredDepth(texture2D(s_texture_0,gl_TexCoord[0].xy));
		color = get_scattering(direction,depth);
	#else
		half depth[MULTISAMPLE_SAMPLES];
		int2 texcoord = int2(gl_TexCoord[0].xy * s_viewport.xy);
		depth[0] = getDeferredDepth(texelFetch(s_texture_0,texcoord,0));
		half min_depth = depth[0];
		half max_depth = depth[0];
		for(int i = 1; i < MULTISAMPLE_SAMPLES; i++) {
			depth[i] = getDeferredDepth(texelFetch(s_texture_0,texcoord,i));
			min_depth = min(min_depth,depth[i]);
			max_depth = max(max_depth,depth[i]);
		}
		color = get_scattering(direction,depth[0]);
		if(max_depth - min_depth > 1e-6f) {
			for(int i = 1; i < MULTISAMPLE_SAMPLES; i++) {
				color += get_scattering(direction,depth[i]);
			}
			color *= MULTISAMPLE_ISAMPLES;
		}
	#endif
	
	gl_FragColor = half4(color,1.0f);
}

#endif

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
};

half power;
half4 sun_color;
half4 sun_angle;
half4 up_direction;
half4 light_direction;
half4 height_falloff;
half4 greenstein;
float4 ray_beta;
float4 mie_beta;
float4 ray_dash;
float4 mie_dash;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	float3 direction = normalize(IN.texcoord_1);
	
	half depth = getDeferredDepth(tex2D(s_texture_0,IN.texcoord_0));
	
	float height = dot(direction,up_direction.xyz) * depth - height_falloff.x;
	
	float ray_density = ray_beta.w;
	float mie_density = mie_beta.w;
	float2 falloff = height_falloff.yz * height;
	[flatten] if(abs(falloff.x) > 0.0f) ray_density *= (1.0f - exp2(-falloff.x)) / falloff.x;
	[flatten] if(abs(falloff.y) > 0.0f) mie_density *= (1.0f - exp2(-falloff.y)) / falloff.y;
	
	half distance = pow(depth,power);
	half3 scattering = exp2(-(ray_beta.xyz * ray_density + mie_beta.xyz * mie_density) * distance);
	
	#ifdef INSCATTERING
		float angle = dot(direction,light_direction.xyz);
		float ray_phase = 1.0f + angle * angle;
		float mie_greenstein = greenstein.y - greenstein.z * angle;
		float mie_phase = min(greenstein.x * rsqrt(mie_greenstein),greenstein.w * distance);
		half3 inscattering = ray_dash.xyz * ray_phase + mie_dash.xyz * mie_phase;
		
		half3 sun = sun_color.xyz * saturate(pow(max(angle,0.0f),sun_angle.x) * sun_angle.y);
		half3 color = inscattering * (1.0f - scattering) + sun * (depth > 0.99f);
	#else
		half3 color = scattering;
	#endif
	
	return half4(color,1.0f);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

TEXTURE_2DMS s_texture_0 : register(t0);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	#ifndef MULTISAMPLE_0
		#ifdef MULTISAMPLE && USE_FEATURE_LEVEL_10_1
			uint sample : SV_SAMPLEINDEX;
		#endif
	#endif
};

struct FRAGMENT_SCATTERING_OUT {
	float3 color_0 : SV_TARGET0;
	float3 color_1 : SV_TARGET1;
};

float power;
float4 sun_color;
float4 sun_angle;
float4 up_direction;
float4 light_direction;
float4 height_falloff;
float4 greenstein;
float4 ray_beta;
float4 mie_beta;
float4 ray_dash;
float4 mie_dash;

/*
 */
FRAGMENT_SCATTERING_OUT get_scattering(float3 direction,half depth) {
	
	FRAGMENT_SCATTERING_OUT OUT;
	
	float height = dot(direction,up_direction.xyz) * depth - height_falloff.x;
	
	float ray_density = ray_beta.w;
	float mie_density = mie_beta.w;
	float2 falloff = height_falloff.yz * height;
	[flatten] if(abs(falloff.x) > 0.0f) ray_density *= (1.0f - exp2(-falloff.x)) / falloff.x;
	[flatten] if(abs(falloff.y) > 0.0f) mie_density *= (1.0f - exp2(-falloff.y)) / falloff.y;
	
	half distance = pow(depth,power);
	half3 scattering = exp2(-(ray_beta.xyz * ray_density + mie_beta.xyz * mie_density) * distance);
	
	float angle = dot(direction,light_direction.xyz);
	float ray_phase = 1.0f + angle * angle;
	float mie_greenstein = greenstein.y - greenstein.z * angle;
	float mie_phase = min(greenstein.x * rsqrt(mie_greenstein),greenstein.w * distance);
	half3 inscattering = ray_dash.xyz * ray_phase + mie_dash.xyz * mie_phase;
	
	half3 sun = sun_color.xyz * saturate(pow(max(angle,0.0f),sun_angle.x) * sun_angle.y);
	
	OUT.color_0 = inscattering * (1.0f - scattering) + sun * (depth > 0.99f);
	OUT.color_1 = scattering;
	
	return OUT;
}

/*
 */
FRAGMENT_SCATTERING_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_SCATTERING_OUT OUT;
	
	float3 direction = normalize(IN.texcoord_1);
	
	#ifdef MULTISAMPLE_0
		half depth = getDeferredDepth(s_texture_0.Sample(s_sampler_0,IN.texcoord_0));
		OUT = get_scattering(direction,depth);
	#elif USE_FEATURE_LEVEL_10_1
		int2 texcoord = int2(IN.texcoord_0 * s_viewport.xy);
		#ifdef MULTISAMPLE
			half depth = getDeferredDepth(s_texture_0.Load(texcoord,IN.sample));
			OUT = get_scattering(direction,depth);
		#else
			half depth = getDeferredDepth(s_texture_0.Load(texcoord,0));
			half min_depth = depth;
			half max_depth = depth;
			[unroll] for(int i = 1; i < MULTISAMPLE_SAMPLES; i++) {
				depth = getDeferredDepth(s_texture_0.Load(texcoord,i));
				min_depth = min(min_depth,depth);
				max_depth = max(max_depth,depth);
			}
			if(max_depth - min_depth > 1e-6f) discard;
			OUT = get_scattering(direction,depth);
		#endif
	#else
		half depth[MULTISAMPLE_SAMPLES];
		int2 texcoord = int2(IN.texcoord_0 * s_viewport.xy);
		depth[0] = getDeferredDepth(s_texture_0.Load(texcoord,0));
		half min_depth = depth[0];
		half max_depth = depth[0];
		[unroll] for(int i = 1; i < MULTISAMPLE_SAMPLES; i++) {
			depth[i] = getDeferredDepth(s_texture_0.Load(texcoord,i));
			min_depth = min(min_depth,depth[i]);
			max_depth = max(max_depth,depth[i]);
		}
		OUT = get_scattering(direction,depth[0]);
		[branch] if(max_depth - min_depth > 1e-6f) {
			[unroll] for(int i = 1; i < MULTISAMPLE_SAMPLES; i++) {
				FRAGMENT_SCATTERING_OUT SAMPLE = get_scattering(direction,depth[i]);
				OUT.color_0 += SAMPLE.color_0;
				OUT.color_1 += SAMPLE.color_1;
			}
			OUT.color_0 *= MULTISAMPLE_ISAMPLES;
			OUT.color_1 *= MULTISAMPLE_ISAMPLES;
		}
	#endif
	
	return OUT;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

##pragma disablepc all

uniform sampler2D s_texture_0 : TEXUNIT0;

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
};

uniform half power;
uniform half4 sun_color;
uniform half4 sun_angle;
uniform half4 up_direction;
uniform half4 light_direction;
uniform half4 height_falloff;
uniform half4 greenstein;
uniform float4 ray_beta;
uniform float4 mie_beta;
uniform float4 ray_dash;
uniform float4 mie_dash;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	float3 direction = normalize(IN.texcoord_1);
	
	half depth = getDeferredDepth(h4tex2D(s_texture_0,IN.texcoord_0));
	
	float height = dot(direction,up_direction.xyz) * depth - height_falloff.x;
	
	float ray_density = ray_beta.w;
	float mie_density = mie_beta.w;
	float2 falloff = height_falloff.yz * height;
	[flatten] if(abs(falloff.x) > 0.0f) ray_density *= (1.0f - exp2(-falloff.x)) / falloff.x;
	[flatten] if(abs(falloff.y) > 0.0f) mie_density *= (1.0f - exp2(-falloff.y)) / falloff.y;
	
	half distance = pow(depth,power);
	half3 scattering = exp2(-(ray_beta.xyz * ray_density + mie_beta.xyz * mie_density) * distance);
	
	#ifdef INSCATTERING
		float angle = dot(direction,light_direction.xyz);
		float ray_phase = 1.0f + angle * angle;
		float mie_greenstein = greenstein.y - greenstein.z * angle;
		float mie_phase = min(greenstein.x * rsqrt(mie_greenstein),greenstein.w * distance);
		half3 inscattering = ray_dash.xyz * ray_phase + mie_dash.xyz * mie_phase;
		
		half3 sun = sun_color.xyz * saturate(pow(max(angle,0.0f),sun_angle.x) * sun_angle.y);
		half3 color = inscattering * (1.0f - scattering) + sun * (depth > 0.99f);
	#else
		half3 color = scattering;
	#endif
	
	return half4(color,1.0f);
}

#endif
