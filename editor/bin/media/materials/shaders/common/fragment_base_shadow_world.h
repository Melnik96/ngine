/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_shadow_world.h
 * Desc:    Base fragment shadow world shader
 * Version: 1.05
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

#ifndef __FRAGMENT_BASE_SHADOW_WORLD_H__
#define __FRAGMENT_BASE_SHADOW_WORLD_H__

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

/*
 */
#define SAMPLER_SHADOW_COLOR_WORLD sampler2D
#define SAMPLER_SHADOW_DEPTH_WORLD sampler2DShadow

/*
 */
#define SAMPLER_SHADOW_WORLD_PCF \
uniform sampler2D s_texture_12; \
uniform sampler2DShadow s_texture_13; \
uniform sampler3D s_texture_14;

/*
 */
half shadowWorld(sampler2DShadow s_depth,float4 texcoord,float4 texsize) {
	half shadow = 0.0f;
	float4 sample_texcoord = s_light_shadow_projections[0] * texcoord;
	half2 sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.25f));
	if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
		sample_texcoord = s_light_shadow_projections[1] * texcoord;
		sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.25f));
		if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
			sample_texcoord = s_light_shadow_projections[2] * texcoord;
			sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.75f));
			if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
				sample_texcoord = s_light_shadow_projections[3] * texcoord;
				sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.75f));
				if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
					shadow = 1.0f;
				}
			}
		}
	}
	if(shadow == 0.0f) {
		shadow = shadow2DLinear(s_depth,sample_texcoord.xyz,texsize);
		return saturate(shadow + s_light_shadow_iradius.y);
	}
	return 1.0f;
}

/*
 */
half shadowWorld(sampler2DShadow s_depth,float3 texcoord_0,float3 texcoord_1,float3 texcoord_2,float3 texcoord_3,float4 texsize) {
	half shadow = 0.0f;
	float3 sample_texcoord = texcoord_0;
	half2 sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.25f));
	if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
		sample_texcoord = texcoord_1;
		sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.25f));
		if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
			sample_texcoord = texcoord_2;
			sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.75f));
			if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
				sample_texcoord = texcoord_3;
				sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.75f));
				if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
					shadow = 1.0f;
				}
			}
		}
	}
	if(shadow == 0.0f) {
		shadow = shadow2DLinear(s_depth,sample_texcoord.xyz,texsize);
		return saturate(shadow + s_light_shadow_iradius.y);
	}
	return 1.0f;
}

/*
 */
half3 shadowWorld(half3 color,sampler2DShadow s_depth,sampler2D s_color,float4 texcoord,float4 texsize) {
	half shadow = 0.0f;
	half3 sample_direction = s_light_shadow_offsets[0].xyz - texcoord.xyz;
	float4 sample_texcoord = s_light_shadow_projections[0] * texcoord;
	half2 sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.25f));
	if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
		sample_direction = s_light_shadow_offsets[1].xyz - texcoord.xyz;
		sample_texcoord = s_light_shadow_projections[1] * texcoord;
		sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.25f));
		if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
			sample_direction = s_light_shadow_offsets[2].xyz - texcoord.xyz;
			sample_texcoord = s_light_shadow_projections[2] * texcoord;
			sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.75f));
			if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
				sample_direction = s_light_shadow_offsets[3].xyz - texcoord.xyz;
				sample_texcoord = s_light_shadow_projections[3] * texcoord;
				sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.75f));
				if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
					shadow = 1.0f;
				}
			}
		}
	}
	if(shadow == 0.0f) {
		shadow = shadow2DLinear(s_depth,sample_texcoord.xyz,texsize);
		color *= saturate(shadow + s_light_shadow_iradius.y);
		#ifdef USE_TRANSLUCENT
			half4 translucent = texture2D(s_color,sample_texcoord.xy);
			half sample_distance = dot(sample_direction,s_light_direction) * s_light_shadow_iradius.x;
			if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
		#endif
	}
	return color;
}

/*
 */
half3 shadowWorldPCF(half3 color,sampler2DShadow s_depth,sampler2D s_color,sampler3D s_noise,float4 texcoord,half4 distances,float4 texsize) {
	half shadow = 0.0f;
	half sample_distance = distances.x;
	float4 sample_texcoord = s_light_shadow_projections[0] * texcoord;
	half2 sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.25f));
	if(max(sample_bounds.x,sample_bounds.y) < 0.245f) {
		#ifdef USE_TRANSLUCENT
			#ifdef USE_TESSELLATION && TESSELLATION
				sample_distance = dot(s_light_shadow_offsets[0].xyz - texcoord.xyz,s_light_direction);
			#endif
		#endif
		#ifdef SHOW_SPLITS
			color = half3(1.0f,0.0f,0.0f);
		#endif
	} else {
		sample_texcoord = s_light_shadow_projections[1] * texcoord;
		sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.25f));
		if(max(sample_bounds.x,sample_bounds.y) < 0.245f) {
			#ifdef USE_TRANSLUCENT
				#ifdef USE_TESSELLATION && TESSELLATION
					sample_distance = dot(s_light_shadow_offsets[1].xyz - texcoord.xyz,s_light_direction);
				#else
					sample_distance = distances.y;
				#endif
			#endif
			#ifdef SHOW_SPLITS
				color = half3(0.0f,1.0f,0.0f);
			#endif
		} else {
			sample_texcoord = s_light_shadow_projections[2] * texcoord;
			sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.75f));
			if(max(sample_bounds.x,sample_bounds.y) < 0.245f) {
				#ifdef USE_TRANSLUCENT
					#ifdef USE_TESSELLATION && TESSELLATION
						sample_distance = dot(s_light_shadow_offsets[2].xyz - texcoord.xyz,s_light_direction);
					#else
						sample_distance = distances.z;
					#endif
				#endif
				#ifdef SHOW_SPLITS
					color = half3(0.0f,0.0f,1.0f);
				#endif
			} else {
				sample_texcoord = s_light_shadow_projections[3] * texcoord;
				sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.75f));
				if(max(sample_bounds.x,sample_bounds.y) < 0.245f) {
					#ifdef USE_TRANSLUCENT
						#ifdef USE_TESSELLATION && TESSELLATION
							sample_distance = dot(s_light_shadow_offsets[3].xyz - texcoord.xyz,s_light_direction);
						#else
							sample_distance = distances.w;
						#endif
					#endif
					#ifdef SHOW_SPLITS
						color = half3(1.0f,1.0f,1.0f);
					#endif
				} else {
					shadow = 1.0f;
				}
			}
		}
	}
	if(shadow == 0.0f) {
		#ifdef USE_TRANSLUCENT
			half4 translucent = texture2D(s_color,sample_texcoord.xy);
		#endif
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
			shadow = shadow2DLinear(s_depth,sample_texcoord.xyz,texsize);
		#endif
		color *= saturate(shadow + s_light_shadow_iradius.y);
		#ifdef USE_TRANSLUCENT
			#ifdef USE_TESSELLATION && TESSELLATION
				sample_distance *= s_light_shadow_iradius.x;			
			#endif
			if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
		#endif
	}
	return color;
}

/*
 */
#ifdef SHADOW
	#ifdef USE_TESSELLATION && TESSELLATION
		#define SHADOW_WORLD_PCF color = shadowWorldPCF(color,s_texture_13,s_texture_12,s_texture_14,float4(gl_TexCoord[3].xyz,1.0f),float4(0.0f),s_material_textures[13]);
	#else
		#define SHADOW_WORLD_PCF color = shadowWorldPCF(color,s_texture_13,s_texture_12,s_texture_14,gl_TexCoord[4],gl_TexCoord[5],s_material_textures[13]);
	#endif
#else
	#define SHADOW_WORLD_PCF { }
#endif

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

/*
 */
half shadowWorld(sampler s_depth,float4 texcoord,float4 texsize) {
	half shadow = 0.0f;
	float4 sample_texcoord = mul(s_light_shadow_projections[0],texcoord);
	half2 sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.25f));
	[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
		sample_texcoord = mul(s_light_shadow_projections[1],texcoord);
		sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.25f));
		[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
			sample_texcoord = mul(s_light_shadow_projections[2],texcoord);
			sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.75f));
			[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
				sample_texcoord = mul(s_light_shadow_projections[3],texcoord);
				sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.75f));
				[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
					shadow = 1.0f;
				}
			}
		}
	}
	[flatten] if(shadow == 0.0f) {
		#ifdef HAS_NVIDIA_HARDWARE_SHADOW
			shadow = tex2Dlod(s_depth,float4(sample_texcoord.xyz,0.0f)).x;
		#elif HAS_ATI_HARDWARE_SHADOW
			shadow = shadow2DLodLinear(s_depth,sample_texcoord.xy,texsize,sample_texcoord.z);
		#endif
		return saturate(shadow + s_light_shadow_iradius.y);
	}
	return 1.0f;
}

/*
 */
half shadowWorld(sampler s_depth,float3 texcoord_0,float3 texcoord_1,float3 texcoord_2,float3 texcoord_3,float4 texsize) {
	half shadow = 0.0f;
	float3 sample_texcoord = texcoord_0;
	half2 sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.25f));
	[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
		sample_texcoord = texcoord_1;
		sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.25f));
		[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
			sample_texcoord = texcoord_2;
			sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.75f));
			[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
				sample_texcoord = texcoord_3;
				sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.75f));
				[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
					shadow = 1.0f;
				}
			}
		}
	}
	[flatten] if(shadow == 0.0f) {
		#ifdef HAS_NVIDIA_HARDWARE_SHADOW
			shadow = tex2Dlod(s_depth,float4(sample_texcoord,0.0f)).x;
		#elif HAS_ATI_HARDWARE_SHADOW
			shadow = shadow2DLodLinear(s_depth,sample_texcoord.xy,texsize,sample_texcoord.z);
		#endif
		return saturate(shadow + s_light_shadow_iradius.y);
	}
	return 1.0f;
}

/*
 */
half3 shadowWorld(half3 color,sampler s_depth,sampler s_color,float4 texcoord,float4 texsize) {
	half shadow = 0.0f;
	half3 sample_direction = s_light_shadow_offsets[0].xyz - texcoord.xyz;
	float4 sample_texcoord = mul(s_light_shadow_projections[0],texcoord);
	half2 sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.25f));
	[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
		sample_direction = s_light_shadow_offsets[1].xyz - texcoord.xyz;
		sample_texcoord = mul(s_light_shadow_projections[1],texcoord);
		sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.25f));
		[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
			sample_direction = s_light_shadow_offsets[2].xyz - texcoord.xyz;
			sample_texcoord = mul(s_light_shadow_projections[2],texcoord);
			sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.75f));
			[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
				sample_direction = s_light_shadow_offsets[3].xyz - texcoord.xyz;
				sample_texcoord = mul(s_light_shadow_projections[3],texcoord);
				sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.75f));
				[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
					shadow = 1.0f;
				}
			}
		}
	}
	[flatten] if(shadow == 0.0f) {
		#ifdef HAS_NVIDIA_HARDWARE_SHADOW
			shadow = tex2Dlod(s_depth,float4(sample_texcoord.xyz,0.0f)).x;
		#elif HAS_ATI_HARDWARE_SHADOW
			shadow = shadow2DLodLinear(s_depth,sample_texcoord.xy,texsize,sample_texcoord.z);
		#endif
		color *= saturate(shadow + s_light_shadow_iradius.y);
		#ifdef USE_TRANSLUCENT
			half4 translucent = tex2Dlod(s_color,float4(sample_texcoord.xyz,0.0f));
			half sample_distance = dot(sample_direction,s_light_direction) * s_light_shadow_iradius.x;
			[flatten] if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
		#endif
	}
	return color;
}

/*
 */
half3 shadowWorldPCF(half3 color,sampler s_depth,sampler s_color,sampler s_noise,float2 position,float4 texcoord,half4 distances,float4 texsize) {
	half shadow = 0.0f;
	half sample_distance = distances.x;
	float4 sample_texcoord = mul(s_light_shadow_projections[0],texcoord);
	half2 sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.25f));
	[flatten] if(max(sample_bounds.x,sample_bounds.y) < 0.245f) {
		#ifdef SHOW_SPLITS
			color = half3(1.0f,0.0f,0.0f);
		#endif
	} else {
		sample_texcoord = mul(s_light_shadow_projections[1],texcoord);
		sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.25f));
		[flatten] if(max(sample_bounds.x,sample_bounds.y) < 0.245f) {
			#ifdef USE_TRANSLUCENT
				sample_distance = distances.y;
			#endif
			#ifdef SHOW_SPLITS
				color = half3(0.0f,1.0f,0.0f);
			#endif
		} else {
			sample_texcoord = mul(s_light_shadow_projections[2],texcoord);
			sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.75f));
			[flatten] if(max(sample_bounds.x,sample_bounds.y) < 0.245f) {
				#ifdef USE_TRANSLUCENT
					sample_distance = distances.z;
				#endif
				#ifdef SHOW_SPLITS
					color = half3(0.0f,0.0f,1.0f);
				#endif
			} else {
				sample_texcoord = mul(s_light_shadow_projections[3],texcoord);
				sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.75f));
				[flatten] if(max(sample_bounds.x,sample_bounds.y) < 0.245f) {
					#ifdef USE_TRANSLUCENT
						sample_distance = distances.w;
					#endif
					#ifdef SHOW_SPLITS
						color = half3(1.0f,1.0f,1.0f);
					#endif
				} else {
					shadow = 1.0f;
				}
			}
		}
	}
	#ifdef QUALITY_HIGH
		[branch] if(shadow == 0.0f) {
	#else
		[flatten] if(shadow == 0.0f) {
	#endif
		#ifdef USE_TRANSLUCENT
			half4 translucent = tex2Dlod(s_color,float4(sample_texcoord.xyz,0.0f));
		#endif
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
				shadow = tex2Dlod(s_depth,float4(sample_texcoord.xyz,0.0f)).x;
			#elif HAS_ATI_HARDWARE_SHADOW
				shadow = shadow2DLodLinear(s_depth,sample_texcoord.xy,texsize,sample_texcoord.z);
			#endif
		#endif
		color *= saturate(shadow + s_light_shadow_iradius.y);
		#ifdef USE_TRANSLUCENT
			[flatten] if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
		#endif
	}
	return color;
}

/*
 */
#ifdef SHADOW
	#ifdef USE_TRANSLUCENT
		#define SHADOW_WORLD_PCF color = shadowWorldPCF(color,s_texture_13,s_texture_12,s_texture_14,IN.position,IN.texcoord_4,IN.texcoord_5,s_material_textures[13]);
	#else
		#define SHADOW_WORLD_PCF color = shadowWorldPCF(color,s_texture_13,s_texture_12,s_texture_14,IN.position,IN.texcoord_4,0.0f,s_material_textures[13]);
	#endif
#else
	#define SHADOW_WORLD_PCF { }
#endif

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

/*
 */
#define TEXTURE_SHADOW_WORLD	Texture2D

/*
 */
#define TEXTURE_SHADOW_WORLD_PCF \
Texture2D s_texture_12 : register(t12); \
Texture2D s_texture_13 : register(t13); \
Texture3D s_texture_14 : register(t14);

/*
 */
half shadowWorld(Texture2D s_depth,SamplerState s_depth_sampler,SamplerComparisonState s_depth_sampler_compare,float4 texcoord,float4 texsize) {
	half shadow = 0.0f;
	float4 sample_texcoord = mul(s_light_shadow_projections[0],texcoord);
	half2 sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.25f));
	[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
		sample_texcoord = mul(s_light_shadow_projections[1],texcoord);
		sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.25f));
		[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
			sample_texcoord = mul(s_light_shadow_projections[2],texcoord);
			sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.75f));
			[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
				sample_texcoord = mul(s_light_shadow_projections[3],texcoord);
				sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.75f));
				[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
					shadow = 1.0f;
				}
			}
		}
	}
	[flatten] if(shadow == 0.0f) {
		shadow = s_depth.SampleCmpLevelZero(s_depth_sampler_compare,sample_texcoord.xy,sample_texcoord.z);
		return saturate(shadow + s_light_shadow_iradius.y);
	}
	return 1.0f;
}

/*
 */
half shadowWorld(Texture2D s_depth,SamplerState s_depth_sampler,SamplerComparisonState s_depth_sampler_compare,float3 texcoord_0,float3 texcoord_1,float3 texcoord_2,float3 texcoord_3,float4 texsize) {
	half shadow = 0.0f;
	float3 sample_texcoord = texcoord_0;
	half2 sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.25f));
	[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
		sample_texcoord = texcoord_1;
		sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.25f));
		[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
			sample_texcoord = texcoord_2;
			sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.75f));
			[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
				sample_texcoord = texcoord_3;
				sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.75f));
				[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
					shadow = 1.0f;
				}
			}
		}
	}
	[flatten] if(shadow == 0.0f) {
		shadow = s_depth.SampleCmpLevelZero(s_depth_sampler_compare,sample_texcoord.xy,sample_texcoord.z);
		return saturate(shadow + s_light_shadow_iradius.y);
	}
	return shadow;
}

/*
 */
half3 shadowWorld(half3 color,Texture2D s_depth,SamplerState s_depth_sampler,SamplerComparisonState s_depth_sampler_compare,Texture2D s_color,SamplerState s_color_sampler,float4 texcoord,float4 texsize) {
	half shadow = 0.0f;
	half3 sample_direction = s_light_shadow_offsets[0].xyz - texcoord.xyz;
	float4 sample_texcoord = mul(s_light_shadow_projections[0],texcoord);
	half2 sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.25f));
	[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
		sample_direction = s_light_shadow_offsets[1].xyz - texcoord.xyz;
		sample_texcoord = mul(s_light_shadow_projections[1],texcoord);
		sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.25f));
		[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
			sample_direction = s_light_shadow_offsets[2].xyz - texcoord.xyz;
			sample_texcoord = mul(s_light_shadow_projections[2],texcoord);
			sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.75f));
			[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
				sample_direction = s_light_shadow_offsets[3].xyz - texcoord.xyz;
				sample_texcoord = mul(s_light_shadow_projections[3],texcoord);
				sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.75f));
				[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
					shadow = 1.0f;
				}
			}
		}
	}
	[flatten] if(shadow == 0.0f) {
		shadow = s_depth.SampleCmpLevelZero(s_depth_sampler_compare,sample_texcoord.xy,sample_texcoord.z);
		color *= saturate(shadow + s_light_shadow_iradius.y);
		#ifdef USE_TRANSLUCENT
			half4 translucent = s_color.SampleLevel(s_color_sampler,sample_texcoord.xy,0.0f);
			half sample_distance = dot(sample_direction,s_light_direction) * s_light_shadow_iradius.x;
			[flatten] if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
		#endif
	}
	return color;
}

/*
 */
half3 shadowWorldPCF(half3 color,Texture2D s_depth,SamplerState s_depth_sampler,SamplerComparisonState s_depth_sampler_compare,Texture2D s_color,SamplerState s_color_sampler,Texture3D s_noise,SamplerState s_noise_sampler,float4 position,float4 texcoord,half4 distances,float4 texsize) {
	half shadow = 0.0f;
	half sample_distance = distances.x;
	float4 sample_texcoord = mul(s_light_shadow_projections[0],texcoord);
	half2 sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.25f));
	[flatten] if(max(sample_bounds.x,sample_bounds.y) < 0.245f) {
		#ifdef USE_TRANSLUCENT
			#ifdef USE_TESSELLATION && TESSELLATION
				sample_distance = dot(s_light_shadow_offsets[0].xyz - texcoord.xyz,s_light_direction);
			#endif
		#endif
		#ifdef SHOW_SPLITS
			color = half3(1.0f,0.0f,0.0f);
		#endif
	} else {
		sample_texcoord = mul(s_light_shadow_projections[1],texcoord);
		sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.25f));
		[flatten] if(max(sample_bounds.x,sample_bounds.y) < 0.245f) {
			#ifdef USE_TRANSLUCENT
				#ifdef USE_TESSELLATION && TESSELLATION
					sample_distance = dot(s_light_shadow_offsets[1].xyz - texcoord.xyz,s_light_direction);
				#else
					sample_distance = distances.y;
				#endif
			#endif
			#ifdef SHOW_SPLITS
				color = half3(0.0f,1.0f,0.0f);
			#endif
		} else {
			sample_texcoord = mul(s_light_shadow_projections[2],texcoord);
			sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.75f));
			[flatten] if(max(sample_bounds.x,sample_bounds.y) < 0.245f) {
				#ifdef USE_TRANSLUCENT
					#ifdef USE_TESSELLATION && TESSELLATION
						sample_distance = dot(s_light_shadow_offsets[2].xyz - texcoord.xyz,s_light_direction);
					#else
						sample_distance = distances.z;
					#endif
				#endif
				#ifdef SHOW_SPLITS
					color = half3(0.0f,0.0f,1.0f);
				#endif
			} else {
				sample_texcoord = mul(s_light_shadow_projections[3],texcoord);
				sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.75f));
				[flatten] if(max(sample_bounds.x,sample_bounds.y) < 0.245f) {
					#ifdef USE_TRANSLUCENT
						#ifdef USE_TESSELLATION && TESSELLATION
							sample_distance = dot(s_light_shadow_offsets[3].xyz - texcoord.xyz,s_light_direction);
						#else
							sample_distance = distances.w;
						#endif
					#endif
					#ifdef SHOW_SPLITS
						color = half3(1.0f,1.0f,1.0f);
					#endif
				} else {
					shadow = 1.0f;
				}
			}
		}
	}
	#ifdef QUALITY_HIGH
		[branch] if(shadow == 0.0f) {
	#else
		[flatten] if(shadow == 0.0f) {
	#endif
		#ifdef USE_TRANSLUCENT
			half4 translucent = s_color.SampleLevel(s_color_sampler,sample_texcoord.xy,0.0f);
		#endif
		#ifdef QUALITY_HIGH
			half3 jitter_texcoord = half3(position.xy,0.0f) / 16.0f;
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
				sample_distance *= s_light_shadow_iradius.x;			
			#endif
			[flatten] if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
		#endif
	}
	return color;
}

/*
 */
#ifdef SHADOW
	#ifdef USE_TESSELLATION && TESSELLATION
		#define SHADOW_WORLD_PCF color = shadowWorldPCF(color,s_texture_13,s_sampler_13,s_sampler_compare_13,s_texture_12,s_sampler_12,s_texture_14,s_sampler_14,IN.position,float4(IN.texcoord_3,1.0f),0.0f,s_material_textures[13]);
	#elif USE_TRANSLUCENT
		#define SHADOW_WORLD_PCF color = shadowWorldPCF(color,s_texture_13,s_sampler_13,s_sampler_compare_13,s_texture_12,s_sampler_12,s_texture_14,s_sampler_14,IN.position,IN.texcoord_4,IN.texcoord_5,s_material_textures[13]);
	#else
		#define SHADOW_WORLD_PCF color = shadowWorldPCF(color,s_texture_13,s_sampler_13,s_sampler_compare_13,s_texture_12,s_sampler_12,s_texture_14,s_sampler_14,IN.position,IN.texcoord_4,0.0f,s_material_textures[13]);
	#endif
#else
	#define SHADOW_WORLD_PCF { }
#endif

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

/*
 */
#define SAMPLER_SHADOW_WORLD sampler2D

/*
 */
#define SAMPLER_SHADOW_WORLD_PCF \
uniform sampler2D s_texture_12 : TEXUNIT12; \
uniform sampler2D s_texture_13 : TEXUNIT13; \
uniform sampler3D s_texture_14 : TEXUNIT14;

/*
 */
half shadowWorld(sampler2D s_depth,float4 texcoord) {
	half shadow = 0.0f;
	float3 sample_texcoord;
	float4 sample_texcoord_01,sample_texcoord_23;
	sample_texcoord_01.x = dot(s_light_shadow_projections[0][0],texcoord);
	sample_texcoord_01.y = dot(s_light_shadow_projections[0][1],texcoord);
	sample_texcoord_01.z = dot(s_light_shadow_projections[1][0],texcoord);
	sample_texcoord_01.w = dot(s_light_shadow_projections[1][1],texcoord);
	sample_texcoord_23.x = dot(s_light_shadow_projections[2][0],texcoord);
	sample_texcoord_23.y = dot(s_light_shadow_projections[2][1],texcoord);
	sample_texcoord_23.z = dot(s_light_shadow_projections[3][0],texcoord);
	sample_texcoord_23.w = dot(s_light_shadow_projections[3][1],texcoord);
	half4 sample_bounds_01 = abs(sample_texcoord_01 - half4(0.25f,0.25f,0.75f,0.25f));
	half4 sample_bounds_23 = abs(sample_texcoord_23 - half4(0.25f,0.75f,0.75f,0.75f));
	sample_texcoord.xy = sample_texcoord_01.xy;
	sample_texcoord.z = dot(s_light_shadow_projections[0][2],texcoord);
	[flatten] if(max(sample_bounds_01.x,sample_bounds_01.y) > 0.245f) {
		sample_texcoord.xy = sample_texcoord_01.zw;
		sample_texcoord.z = dot(s_light_shadow_projections[1][2],texcoord);
		[flatten] if(max(sample_bounds_01.z,sample_bounds_01.w) > 0.245f) {
			sample_texcoord.xy = sample_texcoord_23.xy;
			sample_texcoord.z = dot(s_light_shadow_projections[2][2],texcoord);
			[flatten] if(max(sample_bounds_23.x,sample_bounds_23.y) > 0.245f) {
				sample_texcoord.xy = sample_texcoord_23.zw;
				sample_texcoord.z = dot(s_light_shadow_projections[3][2],texcoord);
				[flatten] if(max(sample_bounds_23.z,sample_bounds_23.w) > 0.245f) {
					shadow = 1.0f;
				}
			}
		}
	}
	[flatten] if(shadow == 0.0f) {
		shadow = 1.0f - h1texcompare2D(s_depth,sample_texcoord);
		return saturate(shadow + s_light_shadow_iradius.y);
	}
	return 1.0f;
}

/*
 */
half shadowWorld(sampler2D s_depth,float4 texcoord,float4 texcoord_01,float4 texcoord_23) {
	half shadow = 0.0f;
	float3 sample_texcoord;
	half4 sample_bounds_01 = abs(texcoord_01 - half4(0.25f,0.25f,0.75f,0.25f));
	half4 sample_bounds_23 = abs(texcoord_23 - half4(0.25f,0.75f,0.75f,0.75f));
	sample_texcoord.xy = texcoord_01.xy;
	sample_texcoord.z = dot(s_light_shadow_projections[0][2],texcoord);
	[flatten] if(max(sample_bounds_01.x,sample_bounds_01.y) > 0.245f) {
		sample_texcoord.xy = texcoord_01.zw;
		sample_texcoord.z = dot(s_light_shadow_projections[1][2],texcoord);
		[flatten] if(max(sample_bounds_01.z,sample_bounds_01.w) > 0.245f) {
			sample_texcoord.xy = texcoord_23.xy;
			sample_texcoord.z = dot(s_light_shadow_projections[2][2],texcoord);
			[flatten] if(max(sample_bounds_23.x,sample_bounds_23.y) > 0.245f) {
				sample_texcoord.xy = texcoord_23.zw;
				sample_texcoord.z = dot(s_light_shadow_projections[3][2],texcoord);
				[flatten] if(max(sample_bounds_23.z,sample_bounds_23.w) > 0.245f) {
					shadow = 1.0f;
				}
			}
		}
	}
	[flatten] if(shadow == 0.0f) {
		shadow = 1.0f - h1texcompare2D(s_depth,sample_texcoord);
		return saturate(shadow + s_light_shadow_iradius.y);
	}
	return 1.0f;
}

/*
 */
half shadowWorld(sampler2D s_depth,float3 texcoord_0,float3 texcoord_1,float3 texcoord_2,float3 texcoord_3) {
	half shadow = 0.0f;
	float3 sample_texcoord = texcoord_0;
	half2 sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.25f));
	[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
		sample_texcoord = texcoord_1;
		sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.25f));
		[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
			sample_texcoord = texcoord_2;
			sample_bounds = abs(sample_texcoord.xy - half2(0.25f,0.75f));
			[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
				sample_texcoord = texcoord_3;
				sample_bounds = abs(sample_texcoord.xy - half2(0.75f,0.75f));
				[flatten] if(max(sample_bounds.x,sample_bounds.y) > 0.245f) {
					shadow = 1.0f;
				}
			}
		}
	}
	[flatten] if(shadow == 0.0f) {
		shadow = 1.0f - h1texcompare2D(s_depth,sample_texcoord);
		return saturate(shadow + s_light_shadow_iradius.y);
	}
	return 1.0f;
}

/*
 */
half3 shadowWorld(half3 color,sampler2D s_depth,sampler2D s_color,float4 texcoord) {
	half shadow = 0.0f;
	float3 sample_texcoord;
	float4 sample_texcoord_01,sample_texcoord_23;
	sample_texcoord_01.x = dot(s_light_shadow_projections[0][0],texcoord);
	sample_texcoord_01.y = dot(s_light_shadow_projections[0][1],texcoord);
	sample_texcoord_01.z = dot(s_light_shadow_projections[1][0],texcoord);
	sample_texcoord_01.w = dot(s_light_shadow_projections[1][1],texcoord);
	sample_texcoord_23.x = dot(s_light_shadow_projections[2][0],texcoord);
	sample_texcoord_23.y = dot(s_light_shadow_projections[2][1],texcoord);
	sample_texcoord_23.z = dot(s_light_shadow_projections[3][0],texcoord);
	sample_texcoord_23.w = dot(s_light_shadow_projections[3][1],texcoord);
	half4 sample_bounds_01 = abs(sample_texcoord_01 - half4(0.25f,0.25f,0.75f,0.25f));
	half4 sample_bounds_23 = abs(sample_texcoord_23 - half4(0.25f,0.75f,0.75f,0.75f));
	half3 sample_direction = s_light_shadow_offsets[0].xyz - texcoord.xyz;
	sample_texcoord.xy = sample_texcoord_01.xy;
	sample_texcoord.z = dot(s_light_shadow_projections[0][2],texcoord);
	[flatten] if(max(sample_bounds_01.x,sample_bounds_01.y) > 0.245f) {
		sample_direction = s_light_shadow_offsets[1].xyz - texcoord.xyz;
		sample_texcoord.xy = sample_texcoord_01.zw;
		sample_texcoord.z = dot(s_light_shadow_projections[1][2],texcoord);
		[flatten] if(max(sample_bounds_01.z,sample_bounds_01.w) > 0.245f) {
			sample_direction = s_light_shadow_offsets[2].xyz - texcoord.xyz;
			sample_texcoord.xy = sample_texcoord_23.xy;
			sample_texcoord.z = dot(s_light_shadow_projections[2][2],texcoord);
			[flatten] if(max(sample_bounds_23.x,sample_bounds_23.y) > 0.245f) {
				sample_direction = s_light_shadow_offsets[3].xyz - texcoord.xyz;
				sample_texcoord.xy = sample_texcoord_23.zw;
				sample_texcoord.z = dot(s_light_shadow_projections[3][2],texcoord);
				[flatten] if(max(sample_bounds_23.z,sample_bounds_23.w) > 0.245f) {
					shadow = 1.0f;
				}
			}
		}
	}
	[flatten] if(shadow == 0.0f) {
		shadow = 1.0f - h1texcompare2D(s_depth,sample_texcoord);
		color *= saturate(shadow + s_light_shadow_iradius.y);
		#ifdef USE_TRANSLUCENT
			half4 translucent = h4tex2D(s_color,sample_texcoord.xy);
			half sample_distance = dot(sample_direction,s_light_direction) * s_light_shadow_iradius.x;
			[flatten] if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
		#endif
	}
	return color;
}

/*
 */
half3 shadowWorldPCF(half3 color,sampler2D s_depth,sampler2D s_color,sampler3D s_noise,float2 position,float4 texcoord,float4 texcoord_01,float4 texcoord_23,half4 distances) {
	half shadow = 0.0f;
	float sample_distance;
	float3 sample_texcoord;
	half4 sample_bounds_01 = abs(texcoord_01 - half4(0.25f,0.25f,0.75f,0.25f));
	half4 sample_bounds_23 = abs(texcoord_23 - half4(0.25f,0.75f,0.75f,0.75f));
	[flatten] if(max(sample_bounds_01.x,sample_bounds_01.y) < 0.245f) {
		sample_texcoord.xy = texcoord_01.xy;
		sample_texcoord.z = dot(s_light_shadow_projections[0][2],texcoord);
		#ifdef USE_TRANSLUCENT
			sample_distance = distances.x;
		#endif
		#ifdef SHOW_SPLITS
			color = half3(1.0f,0.0f,0.0f);
		#endif
	} else {
		[flatten] if(max(sample_bounds_01.z,sample_bounds_01.w) < 0.245f) {
			sample_texcoord.xy = texcoord_01.zw;
			sample_texcoord.z = dot(s_light_shadow_projections[1][2],texcoord);
			#ifdef USE_TRANSLUCENT
				sample_distance = distances.y;
			#endif
			#ifdef SHOW_SPLITS
				color = half3(0.0f,1.0f,0.0f);
			#endif
		} else {
			[flatten] if(max(sample_bounds_23.x,sample_bounds_23.y) < 0.245f) {
				sample_texcoord.xy = texcoord_23.xy;
				sample_texcoord.z = dot(s_light_shadow_projections[2][2],texcoord);
				#ifdef USE_TRANSLUCENT
					sample_distance = distances.z;
				#endif
				#ifdef SHOW_SPLITS
					color = half3(0.0f,0.0f,1.0f);
				#endif
			} else {
				[flatten] if(max(sample_bounds_23.z,sample_bounds_23.w) < 0.245f) {
					sample_texcoord.xy = texcoord_23.zw;
					sample_texcoord.z = dot(s_light_shadow_projections[3][2],texcoord);
					#ifdef USE_TRANSLUCENT
						sample_distance = distances.w;
					#endif
					#ifdef SHOW_SPLITS
						color = half3(1.0f,1.0f,1.0f);
					#endif
				} else {
					shadow = 1.0f;
					sample_texcoord = 0.0f;
					#ifdef USE_TRANSLUCENT
						sample_distance = distances.w;
					#endif
				}
			}
		}
	}
	#ifdef QUALITY_HIGH
		[branch] if(shadow == 0.0f) {
	#else
		[flatten] if(shadow == 0.0f) {
	#endif
		#ifdef USE_TRANSLUCENT
			half4 translucent = h4tex2D(s_color,sample_texcoord.xy);
		#endif
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
			[flatten] if(shadow > 0.0f && sample_distance > translucent.w) color *= saturate(translucent.xyz + s_light_shadow_iradius.y);
		#endif
	}
	return color;
}

/*
 */
#ifdef SHADOW
	#ifdef USE_TRANSLUCENT
		#define SHADOW_WORLD_PCF color = shadowWorldPCF(color,s_texture_13,s_texture_12,s_texture_14,IN.position,IN.texcoord_4,IN.texcoord_5,IN.texcoord_6,IN.texcoord_7);
	#else
		#define SHADOW_WORLD_PCF color = shadowWorldPCF(color,s_texture_13,s_texture_12,s_texture_14,IN.position,IN.texcoord_4,IN.texcoord_5,IN.texcoord_6,0.0f);
	#endif
#else
	#define SHADOW_WORLD_PCF { }
#endif

#endif

#endif /* __FRAGMENT_BASE_SHADOW_H__ */
