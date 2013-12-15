/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_deferred.shader
 * Desc:    Mesh base deferred shader
 * Version: 1.29
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

/* s_texture_0 is diffuse texture
 * s_texture_1 is normal texture
 * s_texture_3 is detail diffuse texture
 * s_texture_4 is detail normal texture
 * 
 * s_texture_9 is alpha fade texture
 * s_texture_10 is parallax texture
 * s_texture_11 is emission texture
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
uniform sampler2D s_texture_3;
uniform sampler2D s_texture_4;

uniform sampler2D s_texture_9;
uniform sampler2D s_texture_10;
uniform sampler2D s_texture_11;

uniform half4 detail_transform;
uniform half emission_scale;
uniform half glow_scale;
uniform half specular_power;
uniform half4 color_scale;

/*
 */
void main() {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		#ifdef USE_TESSELLATION && TESSELLATION
			texture2DAlphaFadeDiscard(s_texture_9,gl_TexCoord[7].x);
		#else
			texture2DAlphaFadeDiscard(s_texture_9,gl_TexCoord[7].z);
		#endif
	#endif
	
	#ifdef USE_TESSELLATION && TESSELLATION
		float distance = length(gl_TexCoord[1].xyz - s_camera_position) / s_depth_range.y;
	#else
		float distance = length(gl_TexCoord[1].xyz);
	#endif
	
	#ifdef VOLUMETRIC
		gl_FragData[0] = setDeferredDepth(distance,1.0f);
	#else
		gl_FragData[0] = setDeferredDepth(distance,0.0f);
	#endif
	
	float2 texcoord = gl_TexCoord[0].xy;
	
	#ifdef USE_PARALLAX
		
		#ifdef PARALLAX
			
			half3 camera_direction = normalize(half3(gl_TexCoord[5].xyz));
			half2 parallax = camera_direction.xy * half2(gl_TexCoord[6].xy) / abs(camera_direction.z);
			
			#ifdef QUALITY_MEDIUM
				
				half istep = 1.0f / 32.0f;
				half2 step = parallax * istep;
				
				half x,y,xh,yh;
				half threshold = 1.0f;
				for(half i = 0.0f; i <= 32.0f; i += 1.0f) {
					texcoord -= step;
					half h = texture2D(s_texture_10,texcoord).x;
					threshold -= istep;
					if(h > threshold) {
						x = threshold;
						xh = h;
						i = 1024.0f;
					} else {
						yh = h;
					}
				}
				y = x + istep;
				
			#else
				
				float4 texcoord_0 = float4(texcoord.xyxy) - parallax.xyxy * half4(1.000f,1.000f,0.875f,0.875f);
				float4 texcoord_1 = float4(texcoord.xyxy) - parallax.xyxy * half4(0.750f,0.750f,0.625f,0.625f);
				float4 texcoord_2 = float4(texcoord.xyxy) - parallax.xyxy * half4(0.500f,0.500f,0.375f,0.375f);
				float4 texcoord_3 = float4(texcoord.xyxy) - parallax.xyxy * half4(0.250f,0.250f,0.125f,0.125f);
				
				half h0 = texture2D(s_texture_10,texcoord_0.xy).x;
				half h1 = texture2D(s_texture_10,texcoord_0.zw).x;
				half h2 = texture2D(s_texture_10,texcoord_1.xy).x;
				half h3 = texture2D(s_texture_10,texcoord_1.zw).x;
				half h4 = texture2D(s_texture_10,texcoord_2.xy).x;
				half h5 = texture2D(s_texture_10,texcoord_2.zw).x;
				half h6 = texture2D(s_texture_10,texcoord_3.xy).x;
				half h7 = texture2D(s_texture_10,texcoord_3.zw).x;
				
				half x,y,xh,yh;
				if(h7 > 0.875f) { x = 0.875f; xh = h7; yh = h7; }
				else if(h6 > 0.750f) { x = 0.750f; xh = h6; yh = h7; }
				else if(h5 > 0.625f) { x = 0.625f; xh = h5; yh = h6; }
				else if(h4 > 0.500f) { x = 0.500f; xh = h4; yh = h5; }
				else if(h3 > 0.375f) { x = 0.375f; xh = h3; yh = h4; }
				else if(h2 > 0.250f) { x = 0.250f; xh = h2; yh = h3; }
				else if(h1 > 0.125f) { x = 0.125f; xh = h1; yh = h2; }
				else { x = 0.000f; xh = h0; yh = h1; }
				y = x + 0.125f;
				
			#endif
			
			half a = y - yh;
			half b = x - xh;
			
			half2 offset = -parallax * (1.0f - (x * a - y * b) / (a - b));
			
			texcoord = gl_TexCoord[0].xy + offset;
			
			gl_FragData[3] = setDeferredParallax(offset);
			
		#else
			
			gl_FragData[3] = half4(0.0f);
			
		#endif
		
	#endif
	
	half4 diffuse = texture2DAlphaDiscard(s_texture_0,texcoord,1.0f);
	half3 normal = texture2D(s_texture_1,texcoord).xyz;
	
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		
		#ifdef OVERLAY_0 || MULTIPLY_0
			float2 detail_texcoord = texcoord * detail_transform.xy + detail_transform.zw;
		#elif OVERLAY_1 || MULTIPLY_1
			float2 detail_texcoord = gl_TexCoord[0].zw * detail_transform.xy + detail_transform.zw;
		#endif
		
		half4 detail_diffuse = texture2D(s_texture_3,detail_texcoord);
		half2 detail_normal = texture2D(s_texture_4,detail_texcoord).xy;
		
		#ifdef ALPHA
			half3 k = s_material_detail * detail_diffuse.w;
		#else
			half3 k = s_material_detail * (diffuse.w * detail_diffuse.w);
		#endif
		
		#ifdef OVERLAY_0 || OVERLAY_1
			diffuse.xyz = saturate(diffuse.xyz + (detail_diffuse.xyz * 2.0f - 1.0f) * k.x);
		#else
			diffuse.xyz = diffuse.xyz * saturate(detail_diffuse.xyz + 1.0f - k.x);
		#endif
		normal.xy = normal.xy + detail_normal * k.y;
		
		#ifndef USE_ARB_TEXTURE_SNORM
			normal.xy = normal.xy * 2.0f - 1.0f - k.y;
		#endif
		
	#else
		
		#ifndef USE_ARB_TEXTURE_SNORM
			normal.xy = normal.xy * 2.0f - 1.0f;
		#endif
		
	#endif
	
	normal.z = sqrt(saturate(1.0f - dot(normal.xy,normal.xy)));
	
	#ifdef EMISSION
		half4 emission = texture2D(s_texture_11,texcoord);
		diffuse.xyz += emission.xyz * emission_scale;
		gl_FragData[1] = setDeferredColor(diffuse.xyz * color_scale.xyz,emission.w * glow_scale);
	#else
		gl_FragData[1] = setDeferredColor(diffuse.xyz * color_scale.xyz,0.0f);
	#endif
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 screen_normal;
		screen_normal.x = dot(half3(gl_TexCoord[2].xyz),normal);
		screen_normal.y = dot(half3(gl_TexCoord[3].xyz),normal);
		screen_normal.z = dot(half3(gl_TexCoord[4].xyz),normal);
		screen_normal = normalize(screen_normal);
		gl_FragData[2] = setDeferredNormal(screen_normal,specular_power);
	#elif USE_PARALLAX
		gl_FragData[2] = half4(0.0f);
	#endif
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 texcoord_2 : TEXCOORD2;
		half3 texcoord_3 : TEXCOORD3;
		half3 texcoord_4 : TEXCOORD4;
	#endif
	#ifdef USE_PARALLAX && PARALLAX
		half3 texcoord_5 : TEXCOORD5;
		half2 texcoord_6 : TEXCOORD6;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half4 detail_transform;
half emission_scale;
half glow_scale;
half specular_power;
half4 color_scale;

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_9,IN.texcoord_7,IN.texcoord_7.z);
	#endif
	
	float distance = length(IN.texcoord_1);
	
	#ifdef VOLUMETRIC
		OUT.color_0 = setDeferredDepth(distance,1.0f);
	#else
		OUT.color_0 = setDeferredDepth(distance,0.0f);
	#endif
	
	float2 texcoord = IN.texcoord_0.xy;
	
	#ifdef USE_PARALLAX
		
		#ifdef PARALLAX
			
			half3 camera_direction = normalize(IN.texcoord_5);
			half2 parallax = camera_direction.xy * IN.texcoord_6 / abs(camera_direction.z);
			
			#ifdef QUALITY_HIGH
				
				half istep = 1.0f / 32.0f;
				half2 step = parallax * istep;
				
				half x,y,xh,yh;
				half threshold = 1.0f;
				[loop] for(float i = 0.0f; i <= 32.0f; i += 1.0f) {
					texcoord -= step;
					half h = tex2Dlod(s_texture_10,float4(texcoord,0.0f,0.0f)).x;
					threshold -= istep;
					if(h > threshold) {
						x = threshold;
						xh = h;
						i = 1024.0f;
					} else {
						yh = h;
					}
				}
				y = x + istep;
				
			#else
				
				half4 texcoord_0 = texcoord.xyxy - parallax.xyxy * half4(1.000f,1.000f,0.875f,0.875f);
				half4 texcoord_1 = texcoord.xyxy - parallax.xyxy * half4(0.750f,0.750f,0.625f,0.625f);
				half4 texcoord_2 = texcoord.xyxy - parallax.xyxy * half4(0.500f,0.500f,0.375f,0.375f);
				half4 texcoord_3 = texcoord.xyxy - parallax.xyxy * half4(0.250f,0.250f,0.125f,0.125f);
				
				half h0 = tex2D(s_texture_10,texcoord_0.xy).x;
				half h1 = tex2D(s_texture_10,texcoord_0.zw).x;
				half h2 = tex2D(s_texture_10,texcoord_1.xy).x;
				half h3 = tex2D(s_texture_10,texcoord_1.zw).x;
				half h4 = tex2D(s_texture_10,texcoord_2.xy).x;
				half h5 = tex2D(s_texture_10,texcoord_2.zw).x;
				half h6 = tex2D(s_texture_10,texcoord_3.xy).x;
				half h7 = tex2D(s_texture_10,texcoord_3.zw).x;
				
				float x,y,xh,yh;
				[flatten] if(h7 > 0.875f) { x = 0.875f; xh = h7; yh = h7; }
				else [flatten] if(h6 > 0.750f) { x = 0.750f; xh = h6; yh = h7; }
				else [flatten] if(h5 > 0.625f) { x = 0.625f; xh = h5; yh = h6; }
				else [flatten] if(h4 > 0.500f) { x = 0.500f; xh = h4; yh = h5; }
				else [flatten] if(h3 > 0.375f) { x = 0.375f; xh = h3; yh = h4; }
				else [flatten] if(h2 > 0.250f) { x = 0.250f; xh = h2; yh = h3; }
				else [flatten] if(h1 > 0.125f) { x = 0.125f; xh = h1; yh = h2; }
				else { x = 0.000f; xh = h0; yh = h1; }
				y = x + 0.125f;
				
			#endif
			
			half a = y - yh;
			half b = x - xh;
			
			half2 offset = -parallax * (1.0f - (x * a - y * b) / (a - b));
			
			texcoord = IN.texcoord_0.xy + offset;
			
			OUT.color_3 = setDeferredParallax(offset);
			
		#else
			
			OUT.color_3 = 0.0f;
			
		#endif
		
	#endif
	
	half4 diffuse = tex2DAlphaDiscard(s_texture_0,texcoord,1.0f);
	half3 normal = tex2D(s_texture_1,texcoord).xyz;
	
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		
		#ifdef OVERLAY_0 || MULTIPLY_0
			float2 detail_texcoord = texcoord * detail_transform.xy + detail_transform.zw;
		#else
			float2 detail_texcoord = IN.texcoord_0.zw * detail_transform.xy + detail_transform.zw;
		#endif
		
		half4 detail_diffuse = tex2D(s_texture_3,detail_texcoord);
		half2 detail_normal = tex2D(s_texture_4,detail_texcoord).xy;
		
		#ifdef ALPHA
			half k = s_material_detail.y * detail_diffuse.w;
		#else
			half k = s_material_detail.y * diffuse.w * detail_diffuse.w;
		#endif
		
		#ifdef OVERLAY_0 || OVERLAY_1
			diffuse.xyz = saturate(diffuse.xyz + (detail_diffuse.xyz * 2.0f - 1.0f) * k.x);
		#else
			diffuse.xyz = diffuse.xyz * saturate(detail_diffuse.xyz + 1.0f - k.x);
		#endif
		normal.xy = normal.xy + detail_normal * k;
		normal.xy = normal.xy * 2.0f - 1.0f - k;
		
	#else
		
		normal.xy = normal.xy * 2.0f - 1.0f;
		
	#endif
	
	normal.z = sqrt(saturate(1.0f - dot(normal.xy,normal.xy)));
	
	#ifdef EMISSION
		half4 emission = tex2D(s_texture_11,texcoord);
		diffuse.xyz += emission.xyz * emission_scale;
		OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,emission.w * glow_scale);
	#else
		OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,0.0f);
	#endif
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 screen_normal;
		screen_normal.x = dot(IN.texcoord_2,normal);
		screen_normal.y = dot(IN.texcoord_3,normal);
		screen_normal.z = dot(IN.texcoord_4,normal);
		screen_normal = normalize(screen_normal);
		OUT.color_2 = setDeferredNormal(screen_normal,specular_power);
	#elif USE_PARALLAX
		OUT.color_2 = 0.0f;
	#endif
	
	return OUT;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
Texture2D s_texture_1 : register(t1);
Texture2D s_texture_3 : register(t3);
Texture2D s_texture_4 : register(t4);

Texture2D s_texture_9 : register(t9);
Texture2D s_texture_10 : register(t10);
Texture2D s_texture_11 : register(t11);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	#ifdef USE_DEFERRED || USE_OCCLUSION
		float3 texcoord_2 : TEXCOORD2;
		float3 texcoord_3 : TEXCOORD3;
		float3 texcoord_4 : TEXCOORD4;
	#endif
	#ifdef USE_PARALLAX && PARALLAX
		float3 texcoord_5 : TEXCOORD5;
		float2 texcoord_6 : TEXCOORD6;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

cbuffer shader_parameters {
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		float4 detail_transform;
	#endif
	#ifdef EMISSION
		float emission_scale;
		float glow_scale;
	#endif
	#ifdef USE_DEFERRED || USE_OCCLUSION
		float specular_power;
	#endif
	float4 color_scale;
};

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texture2DAlphaFadeDiscard(s_texture_9,s_sampler_9,IN.position.xy,IN.texcoord_9.x);
	#endif
	
	#ifdef USE_TESSELLATION && TESSELLATION
		float distance = length(IN.texcoord_1.xyz - s_camera_position) / s_depth_range.y;
	#else
		float distance = length(IN.texcoord_1);
	#endif
	
	#ifdef VOLUMETRIC
		OUT.color_0 = setDeferredDepth(distance,1.0f);
	#else
		OUT.color_0 = setDeferredDepth(distance,0.0f);
	#endif
	
	float2 texcoord = IN.texcoord_0.xy;
	
	#ifdef USE_PARALLAX
		
		#ifdef PARALLAX
			
			half3 camera_direction = normalize(IN.texcoord_5);
			half2 parallax = camera_direction.xy * IN.texcoord_6 / abs(camera_direction.z);
			
			#ifdef QUALITY_HIGH
				
				half istep = 1.0f / 32.0f;
				half2 step = parallax * istep;
				
				half x,y,xh,yh;
				half threshold = 1.0f;
				[loop] for(float i = 0.0f; i <= 32.0f; i += 1.0f) {
					texcoord -= step;
					half h = s_texture_10.SampleLevel(s_sampler_10,texcoord,0.0f).x;
					threshold -= istep;
					if(h > threshold) {
						x = threshold;
						xh = h;
						i = 1024.0f;
					} else {
						yh = h;
					}
				}
				y = x + istep;
				
			#else
				
				half4 texcoord_0 = texcoord.xyxy - parallax.xyxy * half4(1.000f,1.000f,0.875f,0.875f);
				half4 texcoord_1 = texcoord.xyxy - parallax.xyxy * half4(0.750f,0.750f,0.625f,0.625f);
				half4 texcoord_2 = texcoord.xyxy - parallax.xyxy * half4(0.500f,0.500f,0.375f,0.375f);
				half4 texcoord_3 = texcoord.xyxy - parallax.xyxy * half4(0.250f,0.250f,0.125f,0.125f);
				
				half h0 = s_texture_10.Sample(s_sampler_10,texcoord_0.xy).x;
				half h1 = s_texture_10.Sample(s_sampler_10,texcoord_0.zw).x;
				half h2 = s_texture_10.Sample(s_sampler_10,texcoord_1.xy).x;
				half h3 = s_texture_10.Sample(s_sampler_10,texcoord_1.zw).x;
				half h4 = s_texture_10.Sample(s_sampler_10,texcoord_2.xy).x;
				half h5 = s_texture_10.Sample(s_sampler_10,texcoord_2.zw).x;
				half h6 = s_texture_10.Sample(s_sampler_10,texcoord_3.xy).x;
				half h7 = s_texture_10.Sample(s_sampler_10,texcoord_3.zw).x;
				
				float x,y,xh,yh;
				[flatten] if(h7 > 0.875f) { x = 0.875f; xh = h7; yh = h7; }
				else [flatten] if(h6 > 0.750f) { x = 0.750f; xh = h6; yh = h7; }
				else [flatten] if(h5 > 0.625f) { x = 0.625f; xh = h5; yh = h6; }
				else [flatten] if(h4 > 0.500f) { x = 0.500f; xh = h4; yh = h5; }
				else [flatten] if(h3 > 0.375f) { x = 0.375f; xh = h3; yh = h4; }
				else [flatten] if(h2 > 0.250f) { x = 0.250f; xh = h2; yh = h3; }
				else [flatten] if(h1 > 0.125f) { x = 0.125f; xh = h1; yh = h2; }
				else { x = 0.000f; xh = h0; yh = h1; }
				y = x + 0.125f;
				
			#endif
			
			half a = y - yh;
			half b = x - xh;
			
			half2 offset = -parallax * (1.0f - (x * a - y * b) / (a - b));
			
			texcoord = IN.texcoord_0.xy + offset;
			
			OUT.color_3 = setDeferredParallax(offset);
			
		#else
			
			OUT.color_3 = 0.0f;
			
		#endif
		
	#endif
	
	FRAGMENT_ALPHA_OUT ALPHA_OUT;
	ALPHA_OUT = texture2DAlphaDiscard(s_texture_0,s_sampler_0,texcoord,1.0f);
	#ifdef ALPHA && !MULTISAMPLE_0 && USE_ALPHA_TEST_LEVEL_10_1
		OUT.coverage = ALPHA_OUT.coverage;
	#endif
	
	half4 diffuse = ALPHA_OUT.color;
	half3 normal = s_texture_1.Sample(s_sampler_1,texcoord).xyz;
	
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		
		#ifdef OVERLAY_0 || MULTIPLY_0
			float2 detail_texcoord = texcoord * detail_transform.xy + detail_transform.zw;
		#else
			float2 detail_texcoord = IN.texcoord_0.zw * detail_transform.xy + detail_transform.zw;
		#endif
		
		half4 detail_diffuse = s_texture_3.Sample(s_sampler_3,detail_texcoord);
		half2 detail_normal = s_texture_4.Sample(s_sampler_4,detail_texcoord).xy;
		
		#ifdef ALPHA
			half k = s_material_detail.y * detail_diffuse.w;
		#else
			half k = s_material_detail.y * diffuse.w * detail_diffuse.w;
		#endif
		
		#ifdef OVERLAY_0 || OVERLAY_1
			diffuse.xyz = saturate(diffuse.xyz + (detail_diffuse.xyz * 2.0f - 1.0f) * k.x);
		#else
			diffuse.xyz = diffuse.xyz * saturate(detail_diffuse.xyz + 1.0f - k.x);
		#endif
		normal.xy = normal.xy + detail_normal * k;
		
	#endif
	
	normal.z = sqrt(saturate(1.0f - dot(normal.xy,normal.xy)));
	
	#ifdef EMISSION
		half4 emission = s_texture_11.Sample(s_sampler_11,texcoord);
		diffuse.xyz += emission.xyz * emission_scale;
		OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,emission.w * glow_scale);
	#else
		OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,0.0f);
	#endif
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 screen_normal;
		screen_normal.x = dot(IN.texcoord_2,normal);
		screen_normal.y = dot(IN.texcoord_3,normal);
		screen_normal.z = dot(IN.texcoord_4,normal);
		screen_normal = normalize(screen_normal);
		OUT.color_2 = setDeferredNormal(screen_normal,specular_power);
	#elif USE_PARALLAX
		OUT.color_2 = 0.0f;
	#endif
	
	return OUT;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_0 : TEXUNIT0;
uniform sampler2D s_texture_1 : TEXUNIT1;
uniform sampler2D s_texture_3 : TEXUNIT3;
uniform sampler2D s_texture_4 : TEXUNIT4;

uniform sampler2D s_texture_9 : TEXUNIT9;
uniform sampler2D s_texture_10 : TEXUNIT10;
uniform sampler2D s_texture_11 : TEXUNIT11;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 texcoord_2 : TEXCOORD2;
		half3 texcoord_3 : TEXCOORD3;
		half3 texcoord_4 : TEXCOORD4;
	#endif
	#ifdef USE_PARALLAX && PARALLAX
		half3 texcoord_5 : TEXCOORD5;
		half2 texcoord_6 : TEXCOORD6;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half4 detail_transform;
uniform half emission_scale;
uniform half glow_scale;
uniform half specular_power;
uniform half4 color_scale;

/*
 */
FRAGMENT_DEFERRED_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_DEFERRED_OUT OUT;
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_9,IN.texcoord_9,IN.texcoord_9.z);
	#endif
	
	float distance = length(IN.texcoord_1);
	
	#ifdef VOLUMETRIC
		OUT.color_0 = setDeferredDepth(distance,1.0f);
	#else
		OUT.color_0 = setDeferredDepth(distance,0.0f);
	#endif
	
	float2 texcoord = IN.texcoord_0.xy;
	
	#ifdef USE_PARALLAX
		
		#ifdef PARALLAX
			
			half3 camera_direction = normalize(IN.texcoord_5);
			half2 parallax = camera_direction.xy * IN.texcoord_6 / abs(camera_direction.z);
			
			half4 texcoord_0 = texcoord.xyxy - parallax.xyxy * half4(1.000f,1.000f,0.875f,0.875f);
			half4 texcoord_1 = texcoord.xyxy - parallax.xyxy * half4(0.750f,0.750f,0.625f,0.625f);
			half4 texcoord_2 = texcoord.xyxy - parallax.xyxy * half4(0.500f,0.500f,0.375f,0.375f);
			half4 texcoord_3 = texcoord.xyxy - parallax.xyxy * half4(0.250f,0.250f,0.125f,0.125f);
			
			half h0 = h1tex2D(s_texture_10,texcoord_0.xy);
			half h1 = h1tex2D(s_texture_10,texcoord_0.zw);
			half h2 = h1tex2D(s_texture_10,texcoord_1.xy);
			half h3 = h1tex2D(s_texture_10,texcoord_1.zw);
			half h4 = h1tex2D(s_texture_10,texcoord_2.xy);
			half h5 = h1tex2D(s_texture_10,texcoord_2.zw);
			half h6 = h1tex2D(s_texture_10,texcoord_3.xy);
			half h7 = h1tex2D(s_texture_10,texcoord_3.zw);
			
			float x,y,xh,yh;
			[flatten] if(h7 > 0.875f) { x = 0.875f; xh = h7; yh = h7; }
			else [flatten] if(h6 > 0.750f) { x = 0.750f; xh = h6; yh = h7; }
			else [flatten] if(h5 > 0.625f) { x = 0.625f; xh = h5; yh = h6; }
			else [flatten] if(h4 > 0.500f) { x = 0.500f; xh = h4; yh = h5; }
			else [flatten] if(h3 > 0.375f) { x = 0.375f; xh = h3; yh = h4; }
			else [flatten] if(h2 > 0.250f) { x = 0.250f; xh = h2; yh = h3; }
			else [flatten] if(h1 > 0.125f) { x = 0.125f; xh = h1; yh = h2; }
			else { x = 0.000f; xh = h0; yh = h1; }
			y = x + 0.125f;
			
			half a = y - yh;
			half b = x - xh;
			
			half2 offset = -parallax * (1.0f - (x * a - y * b) / (a - b));
			
			texcoord = IN.texcoord_0.xy + offset;
			
			OUT.color_3 = setDeferredParallax(offset);
			
		#else
			
			OUT.color_3 = 0.0f;
			
		#endif
		
	#endif
	
	half4 diffuse = tex2DAlphaDiscard(s_texture_0,texcoord,1.0f);
	half3 normal = h3tex2D(s_texture_1,texcoord);
	
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		
		#ifdef OVERLAY_0 || MULTIPLY_0
			float2 detail_texcoord = texcoord * detail_transform.xy + detail_transform.zw;
		#else
			float2 detail_texcoord = IN.texcoord_0.zw * detail_transform.xy + detail_transform.zw;
		#endif
		
		half4 detail_diffuse = h4tex2D(s_texture_3,detail_texcoord);
		half2 detail_normal = h2tex2D(s_texture_4,detail_texcoord);
		
		#ifdef ALPHA
			half k = s_material_detail.y * detail_diffuse.w;
		#else
			half k = s_material_detail.y * diffuse.w * detail_diffuse.w;
		#endif
		
		#ifdef OVERLAY_0 || OVERLAY_1
			diffuse.xyz = saturate(diffuse.xyz + (detail_diffuse.xyz * 2.0f - 1.0f) * k.x);
		#else
			diffuse.xyz = diffuse.xyz * saturate(detail_diffuse.xyz + 1.0f - k.x);
		#endif
		normal.xy = normal.xy + detail_normal * k;
		
	#endif
	
	normal.z = sqrt(saturate(1.0f - dot(normal.xy,normal.xy)));
	
	#ifdef EMISSION
		half4 emission = h4tex2D(s_texture_11,texcoord);
		diffuse.xyz += emission.xyz * emission_scale;
		OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,emission.w * glow_scale);
	#else
		OUT.color_1 = setDeferredColor(diffuse.xyz * color_scale.xyz,0.0f);
	#endif
	
	#ifdef USE_DEFERRED || USE_OCCLUSION
		half3 screen_normal;
		screen_normal.x = dot(IN.texcoord_2,normal);
		screen_normal.y = dot(IN.texcoord_3,normal);
		screen_normal.z = dot(IN.texcoord_4,normal);
		screen_normal = normalize(screen_normal);
		OUT.color_2 = setDeferredNormal(screen_normal,specular_power);
	#elif USE_PARALLAX
		OUT.color_2 = 0.0f;
	#endif
	
	return OUT;
}

#endif
