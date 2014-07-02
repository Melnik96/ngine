/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_box_cloud_ambient.shader
 * Desc:    VolumeBox cloud ambient shader
 * Version: 1.09
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

/* s_texture_0 is density texture
 * s_texture_1 is attenuation texture
 * 
 * s_texture_15 is deferred depth texture
 */

#include <core/shaders/common/fragment_base.h>

#ifdef SAMPLES_16
	#define SAMPLES	16.0f
#elif SAMPLES_32
	#define SAMPLES	32.0f
#elif SAMPLES_64
	#define SAMPLES	64.0f
#elif SAMPLES_128
	#define SAMPLES	128.0f
#elif SAMPLES_256
	#define SAMPLES	256.0f
#endif

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

#ifdef VOLUME
	uniform sampler3D s_texture_0;
#else
	uniform sampler2D s_texture_0;
#endif
uniform sampler2D s_texture_1;

uniform SAMPLER_2DMS s_texture_15;

uniform half s_volume_fade;

uniform half4 attenuation_transform;
uniform half4 diffuse_color;
uniform half volume_density;

/*
 */
void main() {
	
	half4 deferred_depth = texture2DDeferredProj(s_texture_15,gl_TexCoord[7],s_material_textures[15].xy);
	
	float front = length(gl_TexCoord[0].xyz);
	float back = length(gl_TexCoord[1].xyz / gl_TexCoord[1].w);
	float near = min(back,getDeferredDepth(deferred_depth));
	
	float3 begin = gl_TexCoord[2].xyz;
	float3 end = gl_TexCoord[3].xyz / gl_TexCoord[3].w;
	float3 direction = end - begin;
	
	float ilength = 1.0f / (length(direction) * SAMPLES);
	float step = max((back - front) * ilength,1e-6f);
	float istep = 1.0f / step;
	
	half density = 0.0f;
	half weight = volume_density * (16.0f / SAMPLES);
	
	front *= istep;
	near *= istep;
	direction *= ilength;
	begin += direction * (near - front);
	
	#ifdef ATTENUATION
		half3 color = half3(0.0f);
	#else
		half color = 0.0f;
	#endif
	
	for(half k = near; k > front; k -= 1.0f) {
		#ifdef VOLUME
			half4 sample = texture3D(s_texture_0,begin);
		#else
			half4 sample = texture2D(s_texture_0,begin.xy);
		#endif
		#ifdef ATTENUATION
			sample = texture2D(s_texture_1,half2(sample.x,attenuation_transform.x));
			sample.w *= saturate(k - front) * weight;
			density = saturate(density + (1.0f - density) * sample.w);
			color = lerp(color,sample.xyz,saturate(sample.w));
		#else
			sample.y *= saturate(k - front) * weight;
			density = saturate(density + (1.0f - density) * sample.y);
			color = lerp(color,sample.x,saturate(sample.y));
		#endif
		begin -= direction;
	}
	
	gl_FragColor = half4(diffuse_color.xyz * color,density * s_volume_fade);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	float4 texcoord_7 : TEXCOORD7;
};

half s_volume_fade;

half4 attenuation_transform;
half4 diffuse_color;
half volume_density;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_depth = tex2Dproj(s_texture_15,IN.texcoord_7);
	
	float front = length(IN.texcoord_0.xyz);
	float back = length(IN.texcoord_1.xyz / IN.texcoord_1.w);
	float near = min(back,getDeferredDepth(deferred_depth));
	
	float3 begin = IN.texcoord_2.xyz;
	float3 end = IN.texcoord_3.xyz / IN.texcoord_3.w;
	float3 direction = end - begin;
	
	float ilength = 1.0f / (length(direction) * SAMPLES);
	float step = max((back - front) * ilength,1e-6f);
	float istep = 1.0f / step;
	
	half density = 0.0f;
	half weight = volume_density * (16.0f / SAMPLES);
	
	front *= istep;
	near *= istep;
	direction *= ilength;
	begin += direction * (near - front);
	
	#ifdef ATTENUATION
		half3 color = 0.0f;
	#else
		half color = 0.0f;
	#endif
	
	[loop] for(half k = near; k > front; k -= 1.0f) {
		#ifdef VOLUME
			half4 sample = tex3Dlod(s_texture_0,half4(begin,0.0f));
		#else
			half4 sample = tex2Dlod(s_texture_0,half4(begin.xy,0.0f,0.0f));
		#endif
		#ifdef ATTENUATION
			sample = tex2Dlod(s_texture_1,half4(sample.x,attenuation_transform.x,0.0f,0.0f));
			sample.w *= saturate(k - front) * weight;
			density = saturate(density + (1.0f - density) * sample.w);
			color = lerp(color,sample.xyz,saturate(sample.w));
		#else
			sample.y *= saturate(k - front) * weight;
			density = saturate(density + (1.0f - density) * sample.y);
			color = lerp(color,sample.x,saturate(sample.y));
		#endif
		begin -= direction;
	}
	
	return half4(diffuse_color.xyz * color,density * s_volume_fade);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

#ifdef VOLUME
	Texture3D s_texture_0 : register(t0);
#else
	Texture2D s_texture_0 : register(t0);
#endif
Texture2D s_texture_1 : register(t1);

TEXTURE_2DMS s_texture_15 : register(t15);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
};

cbuffer shader_volume_parameters {
	float s_volume_fade;
};

cbuffer shader_parameters {
	float4 attenuation_transform;
	float4 diffuse_color;
	float volume_density;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 deferred_depth = texture2DDeferredRect(s_texture_15,s_sampler_15,IN.position.xy,s_material_textures[15].xy);
	
	float front = length(IN.texcoord_0.xyz);
	float back = length(IN.texcoord_1.xyz / IN.texcoord_1.w);
	float near = min(back,getDeferredDepth(deferred_depth));
	
	float3 begin = IN.texcoord_2.xyz;
	float3 end = IN.texcoord_3.xyz / IN.texcoord_3.w;
	float3 direction = end - begin;
	
	float ilength = 1.0f / (length(direction) * SAMPLES);
	float step = max((back - front) * ilength,1e-6f);
	float istep = 1.0f / step;
	
	half density = 0.0f;
	half weight = volume_density * (16.0f / SAMPLES);
	
	front *= istep;
	near *= istep;
	direction *= ilength;
	begin += direction * (near - front);
	
	#ifdef ATTENUATION
		half3 color = 0.0f;
	#else
		half color = 0.0f;
	#endif
	
	[loop] for(half k = near; k > front; k -= 1.0f) {
		#ifdef VOLUME
			half4 sample = s_texture_0.SampleLevel(s_sampler_0,begin,0.0f);
		#else
			half4 sample = s_texture_0.SampleLevel(s_sampler_0,begin.xy,0.0f);
		#endif
		#ifdef ATTENUATION
			sample = s_texture_1.SampleLevel(s_sampler_1,half2(sample.x,attenuation_transform.x),0.0f);
			sample.w *= saturate(k - front) * weight;
			density = saturate(density + (1.0f - density) * sample.w);
			color = lerp(color,sample.xyz,saturate(sample.w));
		#else
			sample.y *= saturate(k - front) * weight;
			density = saturate(density + (1.0f - density) * sample.y);
			color = lerp(color,sample.x,saturate(sample.y));
		#endif
		begin -= direction;
	}
	
	return float4(diffuse_color.xyz * color,density * s_volume_fade);
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

#ifdef VOLUME
	uniform sampler3D s_texture_0 : TEXUNIT0;
#else
	uniform sampler2D s_texture_0 : TEXUNIT0;
#endif
uniform sampler2D s_texture_1 : TEXUNIT1;

uniform sampler2D s_texture_15 : TEXUNIT15;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
	float4 texcoord_3 : TEXCOORD3;
	float4 texcoord_9 : TEXCOORD9;
};

uniform half s_volume_fade;

uniform half4 attenuation_transform;
uniform half4 diffuse_color;
uniform half volume_density;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_depth = h4tex2Dproj(s_texture_15,IN.texcoord_9.xyw);
	
	float front = length(IN.texcoord_0.xyz);
	float back = length(IN.texcoord_1.xyz / IN.texcoord_1.w);
	float near = min(back,getDeferredDepth(deferred_depth));
	
	float3 begin = IN.texcoord_2.xyz;
	float3 end = IN.texcoord_3.xyz / IN.texcoord_3.w;
	float3 direction = end - begin;
	
	float ilength = 1.0f / (length(direction) * SAMPLES);
	float step = max((back - front) * ilength,1e-6f);
	float istep = 1.0f / step;
	
	half density = 0.0f;
	half weight = volume_density * (16.0f / SAMPLES);
	
	front *= istep;
	near *= istep;
	direction *= ilength;
	begin += direction * (near - front);
	
	#ifdef ATTENUATION
		half3 color = 0.0f;
	#else
		half color = 0.0f;
	#endif
	
	for(half k = near; k > front; k -= 1.0f) {
		#ifdef VOLUME
			half4 sample = h4tex3D(s_texture_0,begin);
		#else
			half4 sample = h4tex2D(s_texture_0,begin.xy);
		#endif
		#ifdef ATTENUATION
			sample = h4tex2D(s_texture_1,half2(sample.x,attenuation_transform.x));
			sample.w *= saturate(k - front) * weight;
			density = saturate(density + (1.0f - density) * sample.w);
			color = lerp(color,sample.xyz,saturate(sample.w));
		#else
			sample.y *= saturate(k - front) * weight;
			density = saturate(density + (1.0f - density) * sample.y);
			color = lerp(color,sample.x,saturate(sample.y));
		#endif
		begin -= direction;
	}
	
	return half4(diffuse_color.xyz * color,density * s_volume_fade);
}

#endif
