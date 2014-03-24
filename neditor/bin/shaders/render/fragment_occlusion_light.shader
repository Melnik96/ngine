/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_occlusion_light.shader
 * Desc:    Render occlusion light shader
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

/* s_texture_0 is screen texture
 * s_texture_1 is sample texture
 * s_texture_2 is noise texture
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

uniform half screen_radius;
uniform half sample_radius;
uniform half distance_power;
uniform half4 normals;
uniform half4 projection;

/*
 */
void main() {
	
	half ambient = 0.0f;
	half3 indirect = half3(0.0f);
	
	float4 sample = texture2D(s_texture_1,gl_TexCoord[0].xy);
	half scale = pow(1.0f - sample.w,distance_power);
	half radius = screen_radius * scale;
	
	if(radius > s_viewport.w) {
		
		half2 noise = (texture2D(s_texture_2,gl_TexCoord[1].xy).xy * 2.0f - 1.0f) * radius;
		half2 tangent = half2(noise.x,noise.y) * (s_viewport.x * s_viewport.w);
		half2 binormal = half2(noise.y,-noise.x);
		
		half3 position = normalize(gl_TexCoord[2].xyz) * sample.w;
		half3 normal = sample.xyz;
		
		#ifdef INDIRECT
			#define KERNEL(OFFSET) { \
				half2 sample_texcoord = saturate(gl_TexCoord[0].xy + OFFSET); \
				float4 sample = texture2D(s_texture_1,sample_texcoord); \
				half3 direction = normalize(half3((sample_texcoord * 2.0f - 1.0f) * projection.xy,-1.0f)) * sample.w - position; \
				half occlusion = saturate(1.0f - dot(direction,direction) * sample_radius); \
				direction = normalize(direction); \
				occlusion *= saturate(-dot(direction,sample.xyz) + normals.x) * saturate(dot(direction,normal) + normals.y); \
				indirect += texture2D(s_texture_0,sample_texcoord).xyz * occlusion; \
				ambient += occlusion; \
			}
		#else
			#define KERNEL(OFFSET) { \
				half2 sample_texcoord = saturate(gl_TexCoord[0].xy + OFFSET); \
				float4 sample = texture2D(s_texture_1,sample_texcoord); \
				half3 direction = normalize(half3((sample_texcoord * 2.0f - 1.0f) * projection.xy,-1.0f)) * sample.w - position; \
				half occlusion = saturate(1.0f - dot(direction,direction) * sample_radius); \
				direction = normalize(direction); \
				occlusion *= saturate(-dot(direction,sample.xyz) + normals.x) * saturate(dot(direction,normal) + normals.y); \
				ambient += occlusion; \
			}
		#endif
		
		#define SAMPLE(X,Y,Z0,Z1) { \
			half2 offset = tangent * X + binormal * Y; \
			KERNEL(offset * Z0); \
			KERNEL(offset * Z1); \
		}
		
		#ifdef QUALITY_HIGH
			
			SAMPLE( 0.001f, 1.000f,0.427f,0.565f)
			SAMPLE( 0.646f, 0.763f,0.256f,0.659f)
			SAMPLE( 0.798f, 0.602f,0.212f,0.869f)
			SAMPLE( 0.993f, 0.115f,0.458f,0.707f)
			SAMPLE( 0.996f,-0.085f,0.216f,0.885f)
			SAMPLE( 0.899f,-0.437f,0.497f,0.976f)
			SAMPLE( 0.436f,-0.900f,0.543f,0.607f)
			SAMPLE( 0.001f,-1.000f,0.196f,0.716f)
			SAMPLE(-0.293f,-0.956f,0.211f,0.567f)
			SAMPLE(-0.506f,-0.863f,0.292f,0.654f)
			SAMPLE(-0.713f,-0.701f,0.260f,0.797f)
			SAMPLE(-1.000f,-0.022f,0.505f,0.754f)
			SAMPLE(-0.939f, 0.345f,0.439f,0.887f)
			SAMPLE(-0.860f, 0.511f,0.302f,0.579f)
			SAMPLE(-0.489f, 0.872f,0.392f,0.939f)
			SAMPLE(-0.215f, 0.977f,0.168f,0.815f)
			
			ambient *= 1.0f / 32.0f;
			indirect *= 1.0f / 32.0f;
			
		#elif QUALITY_MEDIUM
			
			SAMPLE( 0.001f, 1.000f,0.427f,0.565f)
			SAMPLE( 0.806f, 0.592f,0.256f,0.659f)
			SAMPLE( 0.943f, 0.332f,0.212f,0.869f)
			SAMPLE( 0.932f,-0.362f,0.458f,0.707f)
			SAMPLE( 0.804f,-0.595f,0.216f,0.885f)
			SAMPLE( 0.430f,-0.903f,0.497f,0.976f)
			SAMPLE(-0.430f,-0.903f,0.543f,0.607f)
			SAMPLE(-0.865f,-0.501f,0.196f,0.716f)
			SAMPLE(-0.992f,-0.127f,0.211f,0.567f)
			SAMPLE(-0.983f, 0.183f,0.292f,0.654f)
			SAMPLE(-0.861f, 0.509f,0.260f,0.797f)
			SAMPLE(-0.030f, 1.000f,0.505f,0.754f)
			
			ambient *= 1.0f / 24.0f;
			indirect *= 1.0f / 24.0f;
			
		#else
			
			SAMPLE( 0.001f, 1.000f,0.427f,0.565f)
			SAMPLE( 0.986f, 0.164f,0.256f,0.659f)
			SAMPLE( 0.961f,-0.275f,0.212f,0.869f)
			SAMPLE( 0.228f,-0.974f,0.458f,0.707f)
			SAMPLE(-0.169f,-0.986f,0.216f,0.885f)
			SAMPLE(-0.786f,-0.618f,0.497f,0.976f)
			SAMPLE(-0.785f, 0.619f,0.543f,0.607f)
			SAMPLE(-0.002f, 1.000f,0.196f,0.716f)
			
			ambient *= 1.0f / 16.0f;
			indirect *= 1.0f / 16.0f;
			
		#endif
		
		#undef SAMPLE
		#undef KERNEL
	}
	
	gl_FragColor = half4(indirect,ambient) * scale;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
};

half screen_radius;
half sample_radius;
half distance_power;
half4 normals;
half4 projection;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half ambient = 0.0f;
	half3 indirect = 0.0f;
	
	float4 sample = tex2D(s_texture_1,IN.texcoord_0);
	half scale = pow(1.0f - sample.w,distance_power);
	half radius = screen_radius * scale;
	
	[branch] if(radius > s_viewport.w) {
		
		half2 noise = (tex2Dlod(s_texture_2,half4(IN.texcoord_1,0.0f,0.0f)).xy * 2.0f - 1.0f) * radius;
		half2 tangent = half2(noise.x,noise.y) * (s_viewport.x * s_viewport.w);
		half2 binormal = half2(noise.y,-noise.x);
		
		half3 position = normalize(IN.texcoord_2) * sample.w;
		half3 normal = sample.xyz;
		
		#ifdef INDIRECT
			#define KERNEL(OFFSET) { \
				half4 sample_texcoord = half4(saturate(IN.texcoord_0 + OFFSET),0.0f,0.0f); \
				float4 sample = tex2Dlod(s_texture_1,sample_texcoord); \
				half3 direction = normalize(half3((sample_texcoord.xy * 2.0f - 1.0f) * projection.xy,-1.0f)) * sample.w - position; \
				half occlusion = saturate(1.0f - dot(direction,direction) * sample_radius); \
				direction = normalize(direction); \
				occlusion *= saturate(-dot(direction,sample.xyz) + normals.x) * saturate(dot(direction,normal) + normals.y); \
				indirect += tex2Dlod(s_texture_0,sample_texcoord).xyz * occlusion; \
				ambient += occlusion; \
			}
		#else
			#define KERNEL(OFFSET) { \
				half4 sample_texcoord = half4(saturate(IN.texcoord_0 + OFFSET),0.0f,0.0f); \
				float4 sample = tex2Dlod(s_texture_1,sample_texcoord); \
				half3 direction = normalize(half3((sample_texcoord.xy * 2.0f - 1.0f) * projection.xy,-1.0f)) * sample.w - position; \
				half occlusion = saturate(1.0f - dot(direction,direction) * sample_radius); \
				direction = normalize(direction); \
				occlusion *= saturate(-dot(direction,sample.xyz) + normals.x) * saturate(dot(direction,normal) + normals.y); \
				ambient += occlusion; \
			}
		#endif
		
		#define SAMPLE(X,Y,Z0,Z1) { \
			half2 offset = tangent * X + binormal * Y; \
			KERNEL(offset * Z0); \
			KERNEL(offset * Z1); \
		}
		
		#ifdef QUALITY_HIGH
			
			SAMPLE( 0.001f, 1.000f,0.427f,0.565f)
			SAMPLE( 0.646f, 0.763f,0.256f,0.659f)
			SAMPLE( 0.798f, 0.602f,0.212f,0.869f)
			SAMPLE( 0.993f, 0.115f,0.458f,0.707f)
			SAMPLE( 0.996f,-0.085f,0.216f,0.885f)
			SAMPLE( 0.899f,-0.437f,0.497f,0.976f)
			SAMPLE( 0.436f,-0.900f,0.543f,0.607f)
			SAMPLE( 0.001f,-1.000f,0.196f,0.716f)
			SAMPLE(-0.293f,-0.956f,0.211f,0.567f)
			SAMPLE(-0.506f,-0.863f,0.292f,0.654f)
			SAMPLE(-0.713f,-0.701f,0.260f,0.797f)
			SAMPLE(-1.000f,-0.022f,0.505f,0.754f)
			SAMPLE(-0.939f, 0.345f,0.439f,0.887f)
			SAMPLE(-0.860f, 0.511f,0.302f,0.579f)
			SAMPLE(-0.489f, 0.872f,0.392f,0.939f)
			SAMPLE(-0.215f, 0.977f,0.168f,0.815f)
			
			ambient *= 1.0f / 32.0f;
			indirect *= 1.0f / 32.0f;
			
		#elif QUALITY_MEDIUM
			
			SAMPLE( 0.001f, 1.000f,0.427f,0.565f)
			SAMPLE( 0.806f, 0.592f,0.256f,0.659f)
			SAMPLE( 0.943f, 0.332f,0.212f,0.869f)
			SAMPLE( 0.932f,-0.362f,0.458f,0.707f)
			SAMPLE( 0.804f,-0.595f,0.216f,0.885f)
			SAMPLE( 0.430f,-0.903f,0.497f,0.976f)
			SAMPLE(-0.430f,-0.903f,0.543f,0.607f)
			SAMPLE(-0.865f,-0.501f,0.196f,0.716f)
			SAMPLE(-0.992f,-0.127f,0.211f,0.567f)
			SAMPLE(-0.983f, 0.183f,0.292f,0.654f)
			SAMPLE(-0.861f, 0.509f,0.260f,0.797f)
			SAMPLE(-0.030f, 1.000f,0.505f,0.754f)
			
			ambient *= 1.0f / 24.0f;
			indirect *= 1.0f / 24.0f;
			
		#else
			
			SAMPLE( 0.001f, 1.000f,0.427f,0.565f)
			SAMPLE( 0.986f, 0.164f,0.256f,0.659f)
			SAMPLE( 0.961f,-0.275f,0.212f,0.869f)
			SAMPLE( 0.228f,-0.974f,0.458f,0.707f)
			SAMPLE(-0.169f,-0.986f,0.216f,0.885f)
			SAMPLE(-0.786f,-0.618f,0.497f,0.976f)
			SAMPLE(-0.785f, 0.619f,0.543f,0.607f)
			SAMPLE(-0.002f, 1.000f,0.196f,0.716f)
			
			ambient *= 1.0f / 16.0f;
			indirect *= 1.0f / 16.0f;
			
		#endif
		
		#undef SAMPLE
		#undef KERNEL
	}
	
	return half4(indirect,ambient) * scale;
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

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
};

float screen_radius;
float sample_radius;
float distance_power;
float4 normals;
float4 projection;

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half ambient = 0.0f;
	half3 indirect = 0.0f;
	
	float4 sample = s_texture_1.Sample(s_sampler_1,IN.texcoord_0);
	half scale = pow(1.0f - sample.w,distance_power);
	half radius = screen_radius * scale;
	
	[branch] if(radius > s_viewport.w) {
		
		half2 noise = (s_texture_2.SampleLevel(s_sampler_2,IN.texcoord_1,0.0f).xy * 2.0f - 1.0f) * radius;
		half2 tangent = half2(noise.x,noise.y) * (s_viewport.x * s_viewport.w);
		half2 binormal = half2(noise.y,-noise.x);
		
		half3 position = normalize(IN.texcoord_2) * sample.w;
		half3 normal = sample.xyz;
		
		#ifdef INDIRECT
			#define KERNEL(OFFSET) { \
				half2 sample_texcoord = saturate(IN.texcoord_0 + OFFSET); \
				float4 sample = s_texture_1.SampleLevel(s_sampler_1,sample_texcoord,0.0f); \
				half3 direction = normalize(half3((sample_texcoord * 2.0f - 1.0f) * projection.xy,-1.0f)) * sample.w - position; \
				half occlusion = saturate(1.0f - dot(direction,direction) * sample_radius); \
				direction = normalize(direction); \
				occlusion *= saturate(-dot(direction,sample.xyz) + normals.x) * saturate(dot(direction,normal) + normals.y); \
				indirect += s_texture_0.SampleLevel(s_sampler_0,sample_texcoord,0.0f).xyz * occlusion; \
				ambient += occlusion; \
			}
		#else
			#define KERNEL(OFFSET) { \
				half2 sample_texcoord = saturate(IN.texcoord_0 + OFFSET); \
				float4 sample = s_texture_1.SampleLevel(s_sampler_1,sample_texcoord,0.0f); \
				half3 direction = normalize(half3((sample_texcoord * 2.0f - 1.0f) * projection.xy,-1.0f)) * sample.w - position; \
				half occlusion = saturate(1.0f - dot(direction,direction) * sample_radius); \
				direction = normalize(direction); \
				occlusion *= saturate(-dot(direction,sample.xyz) + normals.x) * saturate(dot(direction,normal) + normals.y); \
				ambient += occlusion; \
			}
		#endif
		
		#define SAMPLE(X,Y,Z0,Z1) { \
			half2 offset = tangent * X + binormal * Y; \
			KERNEL(offset * Z0); \
			KERNEL(offset * Z1); \
		}
		
		#ifdef QUALITY_HIGH
			
			SAMPLE( 0.001f, 1.000f,0.427f,0.565f)
			SAMPLE( 0.646f, 0.763f,0.256f,0.659f)
			SAMPLE( 0.798f, 0.602f,0.212f,0.869f)
			SAMPLE( 0.993f, 0.115f,0.458f,0.707f)
			SAMPLE( 0.996f,-0.085f,0.216f,0.885f)
			SAMPLE( 0.899f,-0.437f,0.497f,0.976f)
			SAMPLE( 0.436f,-0.900f,0.543f,0.607f)
			SAMPLE( 0.001f,-1.000f,0.196f,0.716f)
			SAMPLE(-0.293f,-0.956f,0.211f,0.567f)
			SAMPLE(-0.506f,-0.863f,0.292f,0.654f)
			SAMPLE(-0.713f,-0.701f,0.260f,0.797f)
			SAMPLE(-1.000f,-0.022f,0.505f,0.754f)
			SAMPLE(-0.939f, 0.345f,0.439f,0.887f)
			SAMPLE(-0.860f, 0.511f,0.302f,0.579f)
			SAMPLE(-0.489f, 0.872f,0.392f,0.939f)
			SAMPLE(-0.215f, 0.977f,0.168f,0.815f)
			
			ambient *= 1.0f / 32.0f;
			indirect *= 1.0f / 32.0f;
			
		#elif QUALITY_MEDIUM
			
			SAMPLE( 0.001f, 1.000f,0.427f,0.565f)
			SAMPLE( 0.806f, 0.592f,0.256f,0.659f)
			SAMPLE( 0.943f, 0.332f,0.212f,0.869f)
			SAMPLE( 0.932f,-0.362f,0.458f,0.707f)
			SAMPLE( 0.804f,-0.595f,0.216f,0.885f)
			SAMPLE( 0.430f,-0.903f,0.497f,0.976f)
			SAMPLE(-0.430f,-0.903f,0.543f,0.607f)
			SAMPLE(-0.865f,-0.501f,0.196f,0.716f)
			SAMPLE(-0.992f,-0.127f,0.211f,0.567f)
			SAMPLE(-0.983f, 0.183f,0.292f,0.654f)
			SAMPLE(-0.861f, 0.509f,0.260f,0.797f)
			SAMPLE(-0.030f, 1.000f,0.505f,0.754f)
			
			ambient *= 1.0f / 24.0f;
			indirect *= 1.0f / 24.0f;
			
		#else
			
			SAMPLE( 0.001f, 1.000f,0.427f,0.565f)
			SAMPLE( 0.986f, 0.164f,0.256f,0.659f)
			SAMPLE( 0.961f,-0.275f,0.212f,0.869f)
			SAMPLE( 0.228f,-0.974f,0.458f,0.707f)
			SAMPLE(-0.169f,-0.986f,0.216f,0.885f)
			SAMPLE(-0.786f,-0.618f,0.497f,0.976f)
			SAMPLE(-0.785f, 0.619f,0.543f,0.607f)
			SAMPLE(-0.002f, 1.000f,0.196f,0.716f)
			
			ambient *= 1.0f / 16.0f;
			indirect *= 1.0f / 16.0f;
			
		#endif
		
		#undef SAMPLE
		#undef KERNEL
	}
	
	return half4(indirect,ambient) * scale;
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

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
	float3 texcoord_2 : TEXCOORD2;
};

uniform half screen_radius;
uniform half sample_radius;
uniform half distance_power;
uniform half4 normals;
uniform half4 projection;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half ambient = 0.0f;
	half3 indirect = 0.0f;
	
	float4 sample = f4tex2D(s_texture_1,IN.texcoord_0);
	half scale = pow(1.0f - sample.w,distance_power);
	half radius = screen_radius * scale;
	
	[branch] if(radius > s_viewport.w) {
		
		half2 noise = (h2tex2D(s_texture_2,IN.texcoord_1) * 2.0f - 1.0f) * radius;
		half2 tangent = half2(noise.x,noise.y) * (s_viewport.x * s_viewport.w);
		half2 binormal = half2(noise.y,-noise.x);
		
		half3 position = normalize(IN.texcoord_2) * sample.w;
		half3 normal = sample.xyz;
		
		#ifdef INDIRECT
			#define KERNEL(OFFSET) { \
				half2 sample_texcoord = saturate(IN.texcoord_0 + OFFSET); \
				float4 sample = f4tex2D(s_texture_1,sample_texcoord); \
				half3 direction = normalize(half3((sample_texcoord * 2.0f - 1.0f) * projection.xy,-1.0f)) * sample.w - position; \
				half occlusion = saturate(1.0f - dot(direction,direction) * sample_radius); \
				direction = normalize(direction); \
				occlusion *= saturate(-dot(direction,sample.xyz) + normals.x) * saturate(dot(direction,normal) + normals.y); \
				indirect += h3tex2D(s_texture_0,sample_texcoord) * occlusion; \
				ambient += occlusion; \
			}
		#else
			#define KERNEL(OFFSET) { \
				half2 sample_texcoord = saturate(IN.texcoord_0 + OFFSET); \
				float4 sample = f4tex2D(s_texture_1,sample_texcoord); \
				half3 direction = normalize(half3((sample_texcoord * 2.0f - 1.0f) * projection.xy,-1.0f)) * sample.w - position; \
				half occlusion = saturate(1.0f - dot(direction,direction) * sample_radius); \
				direction = normalize(direction); \
				occlusion *= saturate(-dot(direction,sample.xyz) + normals.x) * saturate(dot(direction,normal) + normals.y); \
				ambient += occlusion; \
			}
		#endif
		
		#define SAMPLE(X,Y,Z0,Z1) { \
			half2 offset = tangent * X + binormal * Y; \
			KERNEL(offset * Z0); \
			KERNEL(offset * Z1); \
		}
		
		#ifdef QUALITY_HIGH
			
			SAMPLE( 0.001f, 1.000f,0.427f,0.565f)
			SAMPLE( 0.646f, 0.763f,0.256f,0.659f)
			SAMPLE( 0.798f, 0.602f,0.212f,0.869f)
			SAMPLE( 0.993f, 0.115f,0.458f,0.707f)
			SAMPLE( 0.996f,-0.085f,0.216f,0.885f)
			SAMPLE( 0.899f,-0.437f,0.497f,0.976f)
			SAMPLE( 0.436f,-0.900f,0.543f,0.607f)
			SAMPLE( 0.001f,-1.000f,0.196f,0.716f)
			SAMPLE(-0.293f,-0.956f,0.211f,0.567f)
			SAMPLE(-0.506f,-0.863f,0.292f,0.654f)
			SAMPLE(-0.713f,-0.701f,0.260f,0.797f)
			SAMPLE(-1.000f,-0.022f,0.505f,0.754f)
			SAMPLE(-0.939f, 0.345f,0.439f,0.887f)
			SAMPLE(-0.860f, 0.511f,0.302f,0.579f)
			SAMPLE(-0.489f, 0.872f,0.392f,0.939f)
			SAMPLE(-0.215f, 0.977f,0.168f,0.815f)
			
			ambient *= 1.0f / 32.0f;
			indirect *= 1.0f / 32.0f;
			
		#elif QUALITY_MEDIUM
			
			SAMPLE( 0.001f, 1.000f,0.427f,0.565f)
			SAMPLE( 0.806f, 0.592f,0.256f,0.659f)
			SAMPLE( 0.943f, 0.332f,0.212f,0.869f)
			SAMPLE( 0.932f,-0.362f,0.458f,0.707f)
			SAMPLE( 0.804f,-0.595f,0.216f,0.885f)
			SAMPLE( 0.430f,-0.903f,0.497f,0.976f)
			SAMPLE(-0.430f,-0.903f,0.543f,0.607f)
			SAMPLE(-0.865f,-0.501f,0.196f,0.716f)
			SAMPLE(-0.992f,-0.127f,0.211f,0.567f)
			SAMPLE(-0.983f, 0.183f,0.292f,0.654f)
			SAMPLE(-0.861f, 0.509f,0.260f,0.797f)
			SAMPLE(-0.030f, 1.000f,0.505f,0.754f)
			
			ambient *= 1.0f / 24.0f;
			indirect *= 1.0f / 24.0f;
			
		#else
			
			SAMPLE( 0.001f, 1.000f,0.427f,0.565f)
			SAMPLE( 0.986f, 0.164f,0.256f,0.659f)
			SAMPLE( 0.961f,-0.275f,0.212f,0.869f)
			SAMPLE( 0.228f,-0.974f,0.458f,0.707f)
			SAMPLE(-0.169f,-0.986f,0.216f,0.885f)
			SAMPLE(-0.786f,-0.618f,0.497f,0.976f)
			SAMPLE(-0.785f, 0.619f,0.543f,0.607f)
			SAMPLE(-0.002f, 1.000f,0.196f,0.716f)
			
			ambient *= 1.0f / 16.0f;
			indirect *= 1.0f / 16.0f;
			
		#endif
		
		#undef SAMPLE
		#undef KERNEL
	}
	
	return half4(indirect,ambient) * scale;
}

#endif
