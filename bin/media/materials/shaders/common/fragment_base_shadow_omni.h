/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_shadow_omni.h
 * Desc:    Base fragment shadow omni shader
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

#ifndef __FRAGMENT_BASE_SHADOW_OMNI_H__
#define __FRAGMENT_BASE_SHADOW_OMNI_H__

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

/*
 */
#ifdef USE_TEXTURE_ARRAY

/*
 */
#define SAMPLER_SHADOW_COLOR_OMNI sampler2DArray
#define SAMPLER_SHADOW_DEPTH_OMNI sampler2DArrayShadow

/*
 */
#define SAMPLER_SHADOW_OMNI_PCF \
uniform samplerCube s_texture_12; \
uniform sampler2DArrayShadow s_texture_13; \
uniform sampler3D s_texture_14; \
uniform samplerCube s_texture_15; \

/*
 */
half shadowOmni(sampler2DArrayShadow s_depth,samplerCube s_cube,float4 texcoord,float4 texsize) {
	float3 sample_direction = abs(texcoord.xyz);
	float sample_maximum = max(max(sample_direction.x,sample_direction.y),sample_direction.z);
	float4 sample_texcoord = textureCube(s_cube,texcoord.xyz);
	sample_texcoord.w = -1.0f / sample_maximum + texcoord.w;
	sample_texcoord.z *= 65535.0f;
	half shadow = shadow2DArray(s_depth,sample_texcoord).x;
	return saturate(shadow + s_light_shadow_iradius.y);
}

/*
 */
half3 shadowOmniPCF(half3 color,sampler2DArrayShadow s_depth,samplerCube s_color,sampler3D s_noise,samplerCube s_cube,float4 texcoord,float3 direction,float4 texsize) {
	half shadow = 0.0f;
	#ifdef USE_TESSELLATION && TESSELLATION
		float4 sample_texcoord = float4((texcoord.xyz - s_light_shadow_offset) * s_light_shadow_depth_range.x,0.0f);
		float sample_range = s_light_shadow_depth_range.y;
	#else
		float4 sample_texcoord = texcoord;
		float sample_range = texcoord.w;
	#endif
	float3 sample_direction = abs(sample_texcoord.xyz);
	float sample_maximum = max(max(sample_direction.x,sample_direction.y),sample_direction.z);
	sample_texcoord = textureCube(s_cube,sample_texcoord.xyz);
	sample_texcoord.w = -1.0f / sample_maximum + sample_range;
	sample_texcoord.z *= 65535.0f;
	#ifdef QUALITY_HIGH
		half3 jitter_texcoord = half3(getFragCoord() * (1.0f / 16.0f),0.0f);
		sample_texcoord.xy -= s_light_shadow_iradius.z;
		#define SAMPLE { \
			half4 jitter = texture3D(s_noise,jitter_texcoord) * s_light_shadow_iradius.w; \
			shadow += shadow2DArray(s_depth,float4(sample_texcoord.xy + jitter.xy,sample_texcoord.zw)).x; \
			shadow += shadow2DArray(s_depth,float4(sample_texcoord.xy + jitter.zw,sample_texcoord.zw)).x; \
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
		shadow = shadow2DArray(s_depth,sample_texcoord).x;
	#endif
	color *= saturate(shadow + s_light_shadow_iradius.y);
	#ifdef USE_TRANSLUCENT
		#ifdef USE_TESSELLATION && TESSELLATION
			sample_texcoord.xyz = (texcoord.xyz - s_light_shadow_offset) * s_light_shadow_iradius.x;
		#else
			sample_texcoord.xyz = direction;
		#endif
		half sample_distance = saturate(length(half3(sample_texcoord.xyz)));
		half4 translucent = textureCube(s_color,sample_texcoord.xyz);
		if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
	#endif
	return color;
}

#else

/*
 */
#define SAMPLER_SHADOW_COLOR_OMNI sampler2D
#define SAMPLER_SHADOW_DEPTH_OMNI sampler2DShadow

/*
 */
#define SAMPLER_SHADOW_OMNI_PCF \
uniform samplerCube s_texture_12; \
uniform sampler2DShadow s_texture_13; \
uniform sampler3D s_texture_14; \
uniform samplerCube s_texture_15; \

/*
 */
half shadowOmni(sampler2DShadow s_depth,samplerCube s_cube,float4 texcoord,float4 texsize) {
	float3 sample_direction = abs(texcoord.xyz);
	float sample_maximum = max(max(sample_direction.x,sample_direction.y),sample_direction.z);
	float3 sample_texcoord = textureCube(s_cube,texcoord.xyz).xyz;
	sample_texcoord.z = -1.0f / sample_maximum + texcoord.w;
	half shadow = shadow2DLinear(s_depth,sample_texcoord,texsize);
	return saturate(shadow + s_light_shadow_iradius.y);
}

/*
 */
half3 shadowOmniPCF(half3 color,sampler2DShadow s_depth,samplerCube s_color,sampler3D s_noise,samplerCube s_cube,float4 texcoord,float3 direction,float4 texsize) {
	half shadow = 0.0f;
	#ifdef USE_TESSELLATION && TESSELLATION
		float3 sample_texcoord = (texcoord.xyz - s_light_shadow_offset) * s_light_shadow_depth_range.x;
		float sample_range = s_light_shadow_depth_range.y;
	#else
		float3 sample_texcoord = texcoord.xyz;
		float sample_range = texcoord.w;
	#endif
	float3 sample_direction = abs(sample_texcoord);
	float sample_maximum = max(max(sample_direction.x,sample_direction.y),sample_direction.z);
	sample_texcoord = textureCube(s_cube,sample_texcoord).xyz;
	sample_texcoord.z = -1.0f / sample_maximum + sample_range;
	#ifdef QUALITY_HIGH
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
		shadow = shadow2DLinear(s_depth,sample_texcoord,texsize);
	#endif
	color *= saturate(shadow + s_light_shadow_iradius.y);
	#ifdef USE_TRANSLUCENT
		#ifdef USE_TESSELLATION && TESSELLATION
			sample_texcoord = (texcoord.xyz - s_light_shadow_offset) * s_light_shadow_iradius.x;
		#else
			sample_texcoord = direction;
		#endif
		half sample_distance = saturate(length(half3(sample_texcoord)));
		half4 translucent = textureCube(s_color,sample_texcoord);
		if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
	#endif
	return color;
}

#endif

/*
 */
#ifdef SHADOW
	#ifdef USE_TESSELLATION && TESSELLATION
		#define SHADOW_OMNI_PCF color = shadowOmniPCF(color,s_texture_13,s_texture_12,s_texture_14,s_texture_15,float4(gl_TexCoord[3].xyz,1.0f),half3(0.0f),s_material_textures[13]);
	#else
		#define SHADOW_OMNI_PCF color = shadowOmniPCF(color,s_texture_13,s_texture_12,s_texture_14,s_texture_15,gl_TexCoord[4],gl_TexCoord[5].xyz,s_material_textures[13]);
	#endif
#else
	#define SHADOW_OMNI_PCF { }
#endif

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

/*
 */
half shadowOmni(sampler s_depth,sampler s_cube,float4 texcoord,float4 texsize) {
	float3 sample_direction = abs(texcoord.xyz);
	float sample_maximum = max(max(sample_direction.x,sample_direction.y),sample_direction.z);
	#ifdef ATI_R700 || ATI_R800
		float3 sample_clamp = 127.0f / 128.0f + (sample_direction == sample_maximum) * (1.0f / 128.0f);
		sample_direction = clamp(texcoord.xyz / sample_maximum,-sample_clamp,sample_clamp);
	#else
		sample_direction = texcoord.xyz;
	#endif
	float4 sample_texcoord = float4(texCUBE(s_cube,sample_direction).xy,0.0f,1.0f);
	sample_texcoord.z = -1.0f / sample_maximum + texcoord.w;
	#ifdef HAS_NVIDIA_HARDWARE_SHADOW
		half shadow = tex2Dproj(s_depth,sample_texcoord).x;
	#elif HAS_ATI_HARDWARE_SHADOW
		half shadow = shadow2DLinear(s_depth,sample_texcoord.xy,texsize,sample_texcoord.z);
	#endif
	return saturate(shadow + s_light_shadow_iradius.y);
}

/*
 */
half3 shadowOmniPCF(half3 color,sampler s_depth,sampler s_color,sampler s_noise,sampler s_cube,float2 position,float4 texcoord,float3 direction,float4 texsize) {
	half shadow = 0.0f;
	float3 sample_direction = abs(texcoord.xyz);
	float sample_maximum = max(max(sample_direction.x,sample_direction.y),sample_direction.z);
	#ifdef ATI_R700 || ATI_R800
		float3 sample_clamp = 127.0f / 128.0f + (sample_direction == sample_maximum) * (1.0f / 128.0f);
		sample_direction = clamp(texcoord.xyz / sample_maximum,-sample_clamp,sample_clamp);
	#else
		sample_direction = texcoord.xyz;
	#endif
	float4 sample_texcoord = float4(texCUBE(s_cube,sample_direction).xy,0.0f,1.0f);
	sample_texcoord.z = -1.0f / sample_maximum + texcoord.w;
	#ifdef QUALITY_HIGH
		half4 jitter_texcoord = half4(position * (1.0f / 16.0f),0.0f,0.0f);
		sample_texcoord.xy -= s_light_shadow_iradius.z;
		#ifdef HAS_NVIDIA_HARDWARE_SHADOW
			#define SAMPLE { \
				half4 jitter = tex3Dlod(s_noise,jitter_texcoord) * s_light_shadow_iradius.w; \
				shadow += tex2Dlod(s_depth,float4(sample_texcoord.xyz + half3(jitter.xy,0.0f),0.0f)).x; \
				shadow += tex2Dlod(s_depth,float4(sample_texcoord.xyz + half3(jitter.zw,0.0f),0.0f)).x; \
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
			shadow = tex2Dproj(s_depth,sample_texcoord).x;
		#elif HAS_ATI_HARDWARE_SHADOW
			shadow = shadow2DLinear(s_depth,sample_texcoord.xy,texsize,sample_texcoord.z);
		#endif
	#endif
	color *= saturate(shadow + s_light_shadow_iradius.y);
	#ifdef USE_TRANSLUCENT
		half sample_distance = saturate(length(half3(direction)));
		half4 translucent = texCUBE(s_color,direction);
		[flatten] if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
	#endif
	return color;
}

/*
 */
#ifdef SHADOW
	#ifdef USE_TRANSLUCENT
		#define SHADOW_OMNI_PCF color = shadowOmniPCF(color,s_texture_13,s_texture_12,s_texture_14,s_texture_15,IN.position,IN.texcoord_4,IN.texcoord_5,s_material_textures[13]);
	#else
		#define SHADOW_OMNI_PCF color = shadowOmniPCF(color,s_texture_13,s_texture_12,s_texture_14,s_texture_15,IN.position,IN.texcoord_4,0.0f,s_material_textures[13]);
	#endif
#else
	#define SHADOW_OMNI_PCF { }
#endif

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

/*
 */
#ifdef QUALITY_HIGH

/*
 */
#define TEXTURE_SHADOW_OMNI	Texture2DArray

/*
 */
#define TEXTURE_SHADOW_OMNI_PCF \
TextureCube s_texture_12 : register(t12); \
Texture2DArray s_texture_13 : register(t13); \
Texture3D s_texture_14 : register(t14); \
TextureCube s_texture_15 : register(t15);

/*
 */
half shadowOmni(Texture2DArray s_depth,SamplerState s_depth_sampler,SamplerComparisonState s_depth_sampler_compare,TextureCube s_cube,SamplerState s_cube_sampler,float4 texcoord) {
	float3 sample_direction = abs(texcoord.xyz);
	float sample_maximum = max(max(sample_direction.x,sample_direction.y),sample_direction.z);
	float sample_compare = -1.0f / sample_maximum + texcoord.w;
	float3 sample_clamp = 127.0f / 128.0f + (sample_direction == sample_maximum) / 128.0f;
	sample_direction = clamp(texcoord.xyz / sample_maximum,-sample_clamp,sample_clamp);
	float3 sample_texcoord = s_cube.Sample(s_cube_sampler,sample_direction).xyz;
	sample_texcoord.z *= 65535.0f;
	#ifdef USE_FEATURE_LEVEL_10_1
		half shadow = s_depth.SampleCmpLevelZero(s_depth_sampler_compare,sample_texcoord,sample_compare);
	#else
		half shadow = shadow2DArrayLinear(s_depth,s_depth_sampler,sample_texcoord,s_material_textures[4],sample_compare);
	#endif
	return saturate(shadow + s_light_shadow_iradius.y);
}

/*
 */
half3 shadowOmniPCF(half3 color,Texture2DArray s_depth,SamplerState s_depth_sampler,SamplerComparisonState s_depth_sampler_compare,TextureCube s_color,SamplerState s_color_sampler,Texture3D s_noise,SamplerState s_noise_sampler,TextureCube s_cube,SamplerState s_cube_sampler,float4 position,float4 texcoord,float3 direction) {
	half shadow = 0.0f;
	#ifdef USE_TESSELLATION && TESSELLATION
		float3 sample_texcoord = (texcoord.xyz - s_light_shadow_offset) * s_light_shadow_depth_range.x;
		float sample_range = s_light_shadow_depth_range.y;
	#else
		float3 sample_texcoord = texcoord.xyz;
		float sample_range = texcoord.w;
	#endif
	float3 sample_direction = abs(sample_texcoord);
	float sample_maximum = max(max(sample_direction.x,sample_direction.y),sample_direction.z);
	float3 sample_clamp = 127.0f / 128.0f + (sample_direction == sample_maximum) * (1.0f / 128.0f);
	sample_direction = clamp(sample_texcoord / sample_maximum,-sample_clamp,sample_clamp);
	half sample_compare = -1.0f / sample_maximum + sample_range;
	sample_texcoord = s_cube.Sample(s_cube_sampler,sample_direction).xyz;
	sample_texcoord.z *= 65535.0f;
	half3 jitter_texcoord = half3(position.xy,0.0f) / 16.0f;
	sample_texcoord.xy -= s_light_shadow_iradius.z;
	#ifdef USE_FEATURE_LEVEL_10_1
		#define SAMPLE { \
			half4 jitter = s_noise.SampleLevel(s_noise_sampler,jitter_texcoord,0.0f) * s_light_shadow_iradius.w; \
			shadow += s_depth.SampleCmpLevelZero(s_depth_sampler_compare,sample_texcoord + half3(jitter.xy,0.0f),sample_compare); \
			shadow += s_depth.SampleCmpLevelZero(s_depth_sampler_compare,sample_texcoord + half3(jitter.zw,0.0f),sample_compare); \
			jitter_texcoord.z += 1.0f / 16.0f; \
		}
	#else
		#define SAMPLE { \
			half4 jitter = s_noise.SampleLevel(s_noise_sampler,jitter_texcoord,0.0f) * s_light_shadow_iradius.w; \
			shadow += (sample_compare < s_depth.SampleLevel(s_depth_sampler,sample_texcoord + half3(jitter.xy,0.0f),0.0f).x); \
			shadow += (sample_compare < s_depth.SampleLevel(s_depth_sampler,sample_texcoord + half3(jitter.zw,0.0f),0.0f).x); \
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
	color *= saturate(shadow + s_light_shadow_iradius.y);
	#ifdef USE_TRANSLUCENT
		#ifdef USE_TESSELLATION && TESSELLATION
			sample_texcoord = (texcoord.xyz - s_light_shadow_offset) * s_light_shadow_iradius.x;
		#else
			sample_texcoord = direction;
		#endif
		half sample_distance = saturate(length(sample_texcoord));
		half4 translucent = s_color.Sample(s_color_sampler,sample_texcoord);
		[flatten] if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
	#endif
	return color;
}

#else

/*
 */
#define TEXTURE_SHADOW_OMNI	TextureCube

/*
 */
#define TEXTURE_SHADOW_OMNI_PCF \
TextureCube s_texture_12 : register(t12); \
TextureCube s_texture_13 : register(t13); \
Texture3D s_texture_14 : register(t14); \
TextureCube s_texture_15 : register(t15);

/*
 */
half shadowOmni(TextureCube s_depth,SamplerState s_depth_sampler,SamplerComparisonState s_depth_sampler_compare,TextureCube s_cube,SamplerState s_cube_sampler,float4 texcoord) {
	float3 sample_direction = abs(texcoord.xyz);
	float sample_maximum = max(max(sample_direction.x,sample_direction.y),sample_direction.z);
	float sample_compare = -1.0f / sample_maximum + texcoord.w;
	half shadow = s_depth.SampleCmpLevelZero(s_depth_sampler_compare,texcoord.xyz,sample_compare);
	return saturate(shadow + s_light_shadow_iradius.y);
}

/*
 */
half3 shadowOmniPCF(half3 color,TextureCube s_depth,SamplerState s_depth_sampler,SamplerComparisonState s_depth_sampler_compare,TextureCube s_color,SamplerState s_color_sampler,Texture3D s_noise,SamplerState s_noise_sampler,TextureCube s_cube,SamplerState s_cube_sampler,float4 position,float4 texcoord,float3 direction) {
	half shadow = 0.0f;
	#ifdef USE_TESSELLATION && TESSELLATION
		float3 sample_texcoord = (texcoord.xyz - s_light_shadow_offset) * s_light_shadow_depth_range.x;
		float sample_range = s_light_shadow_depth_range.y;
	#else
		float3 sample_texcoord = texcoord.xyz;
		float sample_range = texcoord.w;
	#endif
	float3 sample_direction = abs(sample_texcoord);
	float sample_maximum = max(max(sample_direction.x,sample_direction.y),sample_direction.z);
	half sample_compare = -1.0f / sample_maximum + sample_range;
	shadow = s_depth.SampleCmpLevelZero(s_depth_sampler_compare,sample_texcoord,sample_compare);
	color *= saturate(shadow + s_light_shadow_iradius.y);
	#ifdef USE_TRANSLUCENT
		#ifdef USE_TESSELLATION && TESSELLATION
			sample_texcoord = (texcoord.xyz - s_light_shadow_offset) * s_light_shadow_iradius.x;
		#else
			sample_texcoord = direction;
		#endif
		half sample_distance = saturate(length(sample_texcoord));
		half4 translucent = s_color.Sample(s_color_sampler,sample_texcoord);
		[flatten] if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
	#endif
	return color;
}

#endif

/*
 */
#ifdef SHADOW
	#ifdef USE_TESSELLATION && TESSELLATION
		#define SHADOW_OMNI_PCF color = shadowOmniPCF(color,s_texture_13,s_sampler_13,s_sampler_compare_13,s_texture_12,s_sampler_12,s_texture_14,s_sampler_14,s_texture_15,s_sampler_15,IN.position,float4(IN.texcoord_3,1.0f),0.0f);
	#elif USE_TRANSLUCENT
		#define SHADOW_OMNI_PCF color = shadowOmniPCF(color,s_texture_13,s_sampler_13,s_sampler_compare_13,s_texture_12,s_sampler_12,s_texture_14,s_sampler_14,s_texture_15,s_sampler_15,IN.position,IN.texcoord_4,IN.texcoord_5);
	#else
		#define SHADOW_OMNI_PCF color = shadowOmniPCF(color,s_texture_13,s_sampler_13,s_sampler_compare_13,s_texture_12,s_sampler_12,s_texture_14,s_sampler_14,s_texture_15,s_sampler_15,IN.position,IN.texcoord_4,0.0f);
	#endif
#else
	#define SHADOW_OMNI_PCF { }
#endif

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

/*
 */
#define SAMPLER_SHADOW_OMNI sampler2D

/*
 */
#define SAMPLER_SHADOW_OMNI_PCF \
uniform samplerCUBE s_texture_12 : TEXUNIT12; \
uniform sampler2D s_texture_13 : TEXUNIT13; \
uniform sampler3D s_texture_14 : TEXUNIT14; \
uniform samplerCUBE s_texture_15 : TEXUNIT15; \

/*
 */
half shadowOmni(sampler2D s_depth,samplerCUBE s_cube,float4 texcoord) {
	float3 sample_direction = abs(texcoord.xyz);
	float sample_maximum = max(max(sample_direction.x,sample_direction.y),sample_direction.z);
	float4 sample_texcoord = float4(texCUBE(s_cube,texcoord.xyz).xy,0.0f,1.0f);
	sample_texcoord.z = -1.0f / sample_maximum + texcoord.w;
	half shadow = 1.0f - h1texcompare2D(s_depth,sample_texcoord);
	return saturate(shadow + s_light_shadow_iradius.y);
}

/*
 */
half3 shadowOmniPCF(half3 color,sampler2D s_depth,samplerCUBE s_color,sampler3D s_noise,sampler s_cube,float2 position,float4 texcoord,float3 direction) {
	half shadow = 0.0f;
	float3 sample_direction = abs(texcoord.xyz);
	float sample_maximum = max(max(sample_direction.x,sample_direction.y),sample_direction.z);
	float3 sample_texcoord = float3(h2texCUBE(s_cube,texcoord.xyz),0.0f);
	sample_texcoord.z = -1.0f / sample_maximum + texcoord.w;
	#ifdef QUALITY_HIGH
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
		shadow = 1.0f - h1texcompare2D(s_depth,sample_texcoord);
	#endif
	color *= saturate(shadow + s_light_shadow_iradius.y);
	#ifdef USE_TRANSLUCENT
		half sample_distance = saturate(length(half3(direction)));
		half4 translucent = h4texCUBE(s_color,direction);
		[flatten] if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
	#endif
	return color;
}

/*
 */
#ifdef SHADOW
	#ifdef USE_TRANSLUCENT
		#define SHADOW_OMNI_PCF color = shadowOmniPCF(color,s_texture_13,s_texture_12,s_texture_14,s_texture_15,IN.position,IN.texcoord_4,IN.texcoord_5);
	#else
		#define SHADOW_OMNI_PCF color = shadowOmniPCF(color,s_texture_13,s_texture_12,s_texture_14,s_texture_15,IN.position,IN.texcoord_4,0.0f);
	#endif
#else
	#define SHADOW_OMNI_PCF { }
#endif

#endif

#endif /* __FRAGMENT_BASE_SHADOW_OMNI_H__ */
