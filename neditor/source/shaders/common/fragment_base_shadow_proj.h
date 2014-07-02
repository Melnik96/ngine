/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_shadow_proj.h
 * Desc:    Base fragment shadow proj shader
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

#ifndef __FRAGMENT_BASE_SHADOW_PROJ_H__
#define __FRAGMENT_BASE_SHADOW_PROJ_H__

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

/*
 */
#define SAMPLER_SHADOW_COLOR_PROJ sampler2D
#define SAMPLER_SHADOW_DEPTH_PROJ sampler2DShadow

/*
 */
#define SAMPLER_SHADOW_PROJ_PCF \
uniform sampler2D s_texture_12; \
uniform sampler2DShadow s_texture_13; \
uniform sampler3D s_texture_14;

/*
 */
half shadowProj(sampler2DShadow s_depth,float4 texcoord,float4 texsize) {
	half shadow = shadow2DProjLinear(s_depth,texcoord,texsize);
	return saturate(shadow + s_light_shadow_iradius.y);
}

/*
 */
half3 shadowProjPCF(half3 color,sampler2DShadow s_depth,sampler2D s_color,sampler3D s_noise,float4 texcoord,float distance,float4 texsize) {
	half shadow = 0.0f;
	#ifdef USE_TESSELLATION && TESSELLATION
		texcoord = s_light_shadow_projection * texcoord;
	#endif
	#ifdef QUALITY_HIGH
		float3 sample_texcoord = texcoord.xyz / texcoord.w;
		half3 jitter_texcoord = half3(getFragCoord() * (1.0f / 16.0f),0.0f);
		sample_texcoord.xy -= s_light_shadow_iradius.z;
		#define SAMPLE { \
			half4 jitter = texture3D(s_noise,jitter_texcoord) * s_light_shadow_iradius.w; \
			shadow += shadow2D(s_depth,float3(sample_texcoord.xy + jitter.xy,sample_texcoord.z)).x; \
			shadow += shadow2D(s_depth,float3(sample_texcoord.xy + jitter.zw,sample_texcoord.z)).x; \
			jitter_texcoord.z += 1.0f / 16.0f; \
		}
		SAMPLE
		SAMPLE
		SAMPLE
		SAMPLE
		shadow *= 1.0f / 8.0f;
		if(shadow * (1.0f - shadow) != 0.0f) {
			shadow *= 8.0f;
			for(int i = 4; i < 16; i++) {
				SAMPLE
			}
			shadow *= 1.0f / 32.0f;
			#ifdef SHOW_PENUMBRA
				color = half3(1.0f,0.0f,0.0f);
			#endif
		}
		#undef SAMPLE
	#else
		shadow = shadow2DProjLinear(s_depth,texcoord,texsize);
	#endif
	color *= saturate(shadow + s_light_shadow_iradius.y);
	#ifdef USE_TRANSLUCENT
		#ifdef USE_TESSELLATION && TESSELLATION
			half sample_distance = dot(s_light_shadow_offset - texcoord.xyz,s_light_direction) * s_light_shadow_iradius.x;
		#else
			half sample_distance = distance;
		#endif
		half4 translucent = texture2DProj(s_color,texcoord);
		if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
	#endif
	return color;
}

/*
 */
#ifdef SHADOW
	#ifdef USE_TESSELLATION && TESSELLATION
		#define SHADOW_PROJ_PCF color = shadowProjPCF(color,s_texture_13,s_texture_12,s_texture_14,float4(gl_TexCoord[3].xyz,1.0f),0.0f,s_material_textures[13]);
	#else
		#define SHADOW_PROJ_PCF color = shadowProjPCF(color,s_texture_13,s_texture_12,s_texture_14,gl_TexCoord[4],gl_TexCoord[5].x,s_material_textures[13]);
	#endif
#else
	#define SHADOW_PROJ_PCF { }
#endif

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

/*
 */
half shadowProj(sampler s_depth,float4 texcoord,float4 texsize) {
	#ifdef HAS_NVIDIA_HARDWARE_SHADOW
		half shadow = tex2Dproj(s_depth,texcoord).x;
	#elif HAS_ATI_HARDWARE_SHADOW
		float3 sample_texcoord = texcoord.xyz / texcoord.w;
		half shadow = shadow2DLinear(s_depth,sample_texcoord.xy,texsize,sample_texcoord.z);
	#endif
	return saturate(shadow + s_light_shadow_iradius.y);
}

/*
 */
half3 shadowProjPCF(half3 color,sampler s_depth,sampler s_color,sampler s_noise,float2 position,float4 texcoord,float distance,float4 texsize) {
	half shadow = 0.0f;
	#ifdef QUALITY_HIGH
		float3 sample_texcoord = texcoord.xyz / texcoord.w;
		half4 jitter_texcoord = half4(position * (1.0f / 16.0f),0.0f,0.0f);
		sample_texcoord.xy -= s_light_shadow_iradius.z;
		#ifdef HAS_NVIDIA_HARDWARE_SHADOW
			#define SAMPLE { \
				half4 jitter = tex3Dlod(s_noise,jitter_texcoord) * s_light_shadow_iradius.w; \
				shadow += tex2Dlod(s_depth,float4(sample_texcoord + half3(jitter.xy,0.0f),0.0f)).x; \
				shadow += tex2Dlod(s_depth,float4(sample_texcoord + half3(jitter.zw,0.0f),0.0f)).x; \
				jitter_texcoord.z += 1.0f / 16.0f; \
			}
		#elif HAS_ATI_HARDWARE_SHADOW
			#define SAMPLE { \
				half4 jitter = tex3Dlod(s_noise,jitter_texcoord) * s_light_shadow_iradius.w; \
				shadow += (sample_texcoord.z < tex2Dlod(s_depth,float4(sample_texcoord.xy + jitter.xy,0.0f,0.0f)).x); \
				shadow += (sample_texcoord.z < tex2Dlod(s_depth,float4(sample_texcoord.xy + jitter.zw,0.0f,0.0f)).x); \
				jitter_texcoord.z += 1.0f / 16.0f; \
			}
		#endif
		SAMPLE
		SAMPLE
		SAMPLE
		SAMPLE
		shadow *= 1.0f / 8.0f;
		[branch] if(shadow * (1.0f - shadow) != 0.0f) {
			shadow *= 8.0f;
			[unroll] for(int i = 4; i < 16; i++) {
				SAMPLE
			}
			shadow *= 1.0f / 32.0f;
			#ifdef SHOW_PENUMBRA
				color = half3(1.0f,0.0f,0.0f);
			#endif
		}
		#undef SAMPLE
	#else
		#ifdef HAS_NVIDIA_HARDWARE_SHADOW
			shadow = tex2Dproj(s_depth,texcoord).x;
		#elif HAS_ATI_HARDWARE_SHADOW
			float3 sample_texcoord = texcoord.xyz / texcoord.w;
			shadow = shadow2DLinear(s_depth,sample_texcoord.xy,texsize,sample_texcoord.z);
		#endif
	#endif
	color *= saturate(shadow + s_light_shadow_iradius.y);
	#ifdef USE_TRANSLUCENT
		half4 translucent = tex2Dproj(s_color,texcoord);
		[flatten] if(shadow > 0.0f && distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
	#endif
	return color;
}

/*
 */
#ifdef SHADOW
	#ifdef USE_TRANSLUCENT
		#define SHADOW_PROJ_PCF color = shadowProjPCF(color,s_texture_13,s_texture_12,s_texture_14,IN.position,IN.texcoord_4,IN.texcoord_5,s_material_textures[13]);
	#else
		#define SHADOW_PROJ_PCF color = shadowProjPCF(color,s_texture_13,s_texture_12,s_texture_14,IN.position,IN.texcoord_4,0.0f,s_material_textures[13]);
	#endif
#else
	#define SHADOW_PROJ_PCF { }
#endif

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

/*
 */
#define TEXTURE_SHADOW_PROJ	Texture2D

/*
 */
#define TEXTURE_SHADOW_PROJ_PCF \
Texture2D s_texture_12 : register(t12); \
Texture2D s_texture_13 : register(t13); \
Texture3D s_texture_14 : register(t14);

/*
 */
half shadowProj(Texture2D s_depth,SamplerComparisonState s_depth_sampler_compare,float4 texcoord) {
	float3 sample_texcoord = texcoord.xyz / texcoord.w;
	half shadow = s_depth.SampleCmpLevelZero(s_depth_sampler_compare,sample_texcoord.xy,sample_texcoord.z);
	return saturate(shadow + s_light_shadow_iradius.y);
}

/*
 */
half3 shadowProjPCF(half3 color,Texture2D s_depth,SamplerComparisonState s_depth_sampler_compare,Texture2D s_color,SamplerState s_color_sampler,Texture3D s_noise,SamplerState s_noise_sampler,float4 position,float4 texcoord,float distance) {
	half shadow = 0.0f;
	#ifdef USE_TESSELLATION && TESSELLATION
		float4 sample_texcoord = mul(s_light_shadow_projection,texcoord);
		sample_texcoord.xyz /= sample_texcoord.w;
	#else
		float3 sample_texcoord = texcoord.xyz / texcoord.w;
	#endif
	#ifdef USE_TRANSLUCENT
		half4 translucent = s_color.Sample(s_color_sampler,sample_texcoord.xy);
	#endif
	#ifdef QUALITY_HIGH
		half3 jitter_texcoord = half3(position.xy * (1.0f / 16.0f),0.0f);
		sample_texcoord.xy -= s_light_shadow_iradius.z;
		#define SAMPLE { \
			half4 jitter = s_noise.SampleLevel(s_noise_sampler,jitter_texcoord,0.0f) * s_light_shadow_iradius.w; \
			shadow += s_depth.SampleCmpLevelZero(s_depth_sampler_compare,sample_texcoord.xy + jitter.xy,sample_texcoord.z); \
			shadow += s_depth.SampleCmpLevelZero(s_depth_sampler_compare,sample_texcoord.xy + jitter.zw,sample_texcoord.z); \
			jitter_texcoord.z += 1.0f / 16.0f; \
		}
		SAMPLE
		SAMPLE
		SAMPLE
		SAMPLE
		shadow *= 1.0f / 8.0f;
		[branch] if(shadow * (1.0f - shadow) != 0.0f) {
			shadow *= 8.0f;
			[unroll] for(int i = 4; i < 16; i++) {
				SAMPLE
			}
			shadow *= 1.0f / 32.0f;
			#ifdef SHOW_PENUMBRA
				color = half3(1.0f,0.0f,0.0f);
			#endif
		}
		#undef SAMPLE
	#else
		shadow = s_depth.SampleCmpLevelZero(s_depth_sampler_compare,sample_texcoord.xy,sample_texcoord.z);
	#endif
	color *= saturate(shadow + s_light_shadow_iradius.y);
	#ifdef USE_TRANSLUCENT
		#ifdef USE_TESSELLATION && TESSELLATION
			half sample_distance = dot(s_light_shadow_offset - texcoord.xyz,s_light_direction) * s_light_shadow_iradius.x;
		#else
			half sample_distance = distance;
		#endif
		[flatten] if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
	#endif
	return color;
}

/*
 */
#ifdef SHADOW
	#ifdef USE_TESSELLATION && TESSELLATION
		#define SHADOW_PROJ_PCF color = shadowProjPCF(color,s_texture_13,s_sampler_compare_13,s_texture_12,s_sampler_12,s_texture_14,s_sampler_14,IN.position,float4(IN.texcoord_3,1.0f),0.0f);
	#elif USE_TRANSLUCENT
		#define SHADOW_PROJ_PCF color = shadowProjPCF(color,s_texture_13,s_sampler_compare_13,s_texture_12,s_sampler_12,s_texture_14,s_sampler_14,IN.position,IN.texcoord_4,IN.texcoord_5);
	#else
		#define SHADOW_PROJ_PCF color = shadowProjPCF(color,s_texture_13,s_sampler_compare_13,s_texture_12,s_sampler_12,s_texture_14,s_sampler_14,IN.position,IN.texcoord_4,0.0f);
	#endif
#else
	#define SHADOW_PROJ_PCF { }
#endif

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

/*
 */
#define SAMPLER_SHADOW_PROJ sampler2D

/*
 */
#define SAMPLER_SHADOW_PROJ_PCF \
uniform sampler2D s_texture_12 : TEXUNIT12; \
uniform sampler2D s_texture_13 : TEXUNIT13; \
uniform sampler3D s_texture_14 : TEXUNIT14;

/*
 */
half shadowProj(sampler2D s_depth,float4 texcoord) {
	half shadow = 1.0f - h1texcompare2D(s_depth,texcoord);
	return saturate(shadow + s_light_shadow_iradius.y);
}

/*
 */
half3 shadowProjPCF(half3 color,sampler2D s_depth,sampler2D s_color,sampler3D s_noise,float2 position,float4 texcoord,float distance) {
	half shadow = 0.0f;
	#ifdef QUALITY_HIGH
		float3 sample_texcoord = texcoord.xyz / texcoord.w;
		half3 jitter_texcoord = half3(position * (1.0f / 16.0f),0.0f);
		sample_texcoord.xy -= s_light_shadow_iradius.z;
		#define SAMPLE { \
			half4 jitter = tex3D(s_noise,jitter_texcoord) * s_light_shadow_iradius.w; \
			shadow += h1texcompare2D(s_depth,float3(sample_texcoord + half3(jitter.xy,0.0f))); \
			shadow += h1texcompare2D(s_depth,float3(sample_texcoord + half3(jitter.zw,0.0f))); \
			jitter_texcoord.z += 1.0f / 16.0f; \
		}
		SAMPLE
		SAMPLE
		SAMPLE
		SAMPLE
		shadow = (8.0f - shadow) / 8.0f;
		#undef SAMPLE
	#else
		shadow = 1.0f - h1texcompare2D(s_depth,texcoord);
	#endif
	color *= saturate(shadow + s_light_shadow_iradius.y);
	#ifdef USE_TRANSLUCENT
		half4 translucent = h4tex2Dproj(s_color,texcoord);
		[flatten] if(shadow > 0.0f && distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
	#endif
	return color;
}

/*
 */
#ifdef SHADOW
	#ifdef USE_TRANSLUCENT
		#define SHADOW_PROJ_PCF color = shadowProjPCF(color,s_texture_13,s_texture_12,s_texture_14,IN.position,IN.texcoord_4,IN.texcoord_5.x);
	#else
		#define SHADOW_PROJ_PCF color = shadowProjPCF(color,s_texture_13,s_texture_12,s_texture_14,IN.position,IN.texcoord_4,0.0f);
	#endif
#else
	#define SHADOW_PROJ_PCF { }
#endif

#endif

#endif /* __FRAGMENT_BASE_SHADOW_PROJ_H__ */
