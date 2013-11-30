/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_composite.shader
 * Desc:    Render composite shader
 * Version: 1.21
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
 * s_texture_1 is deferred depth texture
 * s_texture_2 is auxiliary texture
 * s_texture_3 is refraction texture
 * s_texture_4 is velocity texture
 * s_texture_5 is glow texture
 * s_texture_6 is dof texture
 * s_texture_7 is luminance texture
 * s_texture_8 is bright texture
 * s_texture_9 is color texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;
uniform SAMPLER_2DMS s_texture_1;
uniform SAMPLER_2DMS s_texture_2;
uniform SAMPLER_2DMS s_texture_3;
uniform SAMPLER_2DMS s_texture_4;
uniform sampler2D s_texture_5;
uniform sampler2D s_texture_6;
uniform sampler2D s_texture_7;
uniform sampler2D s_texture_8;
uniform sampler3D s_texture_9;

uniform half4 modelview_x;
uniform half4 modelview_y;
uniform half4 modelview_z;
uniform half4 old_modelview_x;
uniform half4 old_modelview_y;
uniform half4 old_modelview_z;
uniform half4 modelviewprojection_x;
uniform half4 modelviewprojection_y;
uniform half4 modelviewprojection_w;
uniform half4 motion_blur_scale;
uniform half focal_distance;
uniform half focal_range;
uniform half focal_power;
uniform half blur_irange;

/*
 */
void main() {
	
	#ifdef REFRACTION
		half4 refraction = texture2DDeferredNorm(s_texture_3,gl_TexCoord[0].xy);
		half2 refraction_offset = (refraction.xy - refraction.zw) * half2(gl_TexCoord[1].xy);
		refraction_offset *= saturate(texture2DDeferredNorm(s_texture_3,gl_TexCoord[0].xy + refraction_offset).w * 255.0f);
		float2 texcoord = gl_TexCoord[0].xy + refraction_offset;
	#else
		float2 texcoord = gl_TexCoord[0].xy;
	#endif
	
	#ifdef MOTION_BLUR || DOF
		half4 deferred_depth = texture2DDeferredNorm(s_texture_1,gl_TexCoord[0].xy);
		float depth = getDeferredDepth(deferred_depth);
	#endif
	
	#ifdef DOF
		half dof_weight = pow(saturate(max(abs(depth - focal_distance) - focal_range,0.0f) * blur_irange),focal_power);
	#endif
	
	#ifdef MOTION_BLUR
		half4 position = half4(normalize(gl_TexCoord[2].xyz) * (gl_TexCoord[2].w * depth),1.0f);
		half4 old_position = half4(dot(old_modelview_x,position),dot(old_modelview_y,position),dot(old_modelview_z,position),1.0f);
		position.xyz = half3(dot(modelview_x.xyz,position.xyz),dot(modelview_y.xyz,position.xyz),dot(modelview_z.xyz,position.xyz));
		half3 offset = (position.xyz - old_position.xyz) * motion_blur_scale.x;
		#ifdef VELOCITY_BLUR
			half3 velocity = texture2DDeferredNorm(s_texture_4,texcoord).xyz;
			offset -= (velocity - 127.0f / 255.0f) * motion_blur_scale.y;
		#endif
		old_position.xyz = position.xyz - offset;
		half3 texcoord_0 = half3(dot(modelviewprojection_x,position),dot(modelviewprojection_y,position),dot(modelviewprojection_w,position));
		half3 texcoord_1 = half3(dot(modelviewprojection_x,old_position),dot(modelviewprojection_y,old_position),dot(modelviewprojection_w,old_position));
		offset.xy = texcoord_0.xy / texcoord_0.z - texcoord_1.xy / texcoord_1.z;
		#ifdef DOF
			#define SAMPLE(OFFSET,WEIGHT) { \
				float2 texcoord_0 = texcoord - offset.xy * (OFFSET); \
				float2 texcoord_1 = texcoord + offset.xy * (OFFSET); \
				color += texture2D(s_texture_0,texcoord_0).xyz * (WEIGHT); \
				color += texture2D(s_texture_0,texcoord_1).xyz * (WEIGHT); \
				dof_color += texture2DLinear(s_texture_6,texcoord_0,s_material_textures[6]).xyz * (WEIGHT); \
				dof_color += texture2DLinear(s_texture_6,texcoord_1,s_material_textures[6]).xyz * (WEIGHT); \
			}
		#else
			#define SAMPLE(OFFSET,WEIGHT) { \
				float2 texcoord_0 = texcoord - offset.xy * (OFFSET); \
				float2 texcoord_1 = texcoord + offset.xy * (OFFSET); \
				color += texture2D(s_texture_0,texcoord_0).xyz * (WEIGHT); \
				color += texture2D(s_texture_0,texcoord_1).xyz * (WEIGHT); \
			}
		#endif
		half3 color = half3(0.0f);
		half3 dof_color = half3(0.0f);
		#ifdef QUALITY_HIGH
			SAMPLE(0.058824f,0.064806f)
			SAMPLE(0.176471f,0.064011f)
			SAMPLE(0.294118f,0.062450f)
			SAMPLE(0.411765f,0.060179f)
			SAMPLE(0.529412f,0.057279f)
			SAMPLE(0.647059f,0.053851f)
			SAMPLE(0.764706f,0.050006f)
			SAMPLE(0.882353f,0.045866f)
			SAMPLE(1.000000f,0.041552f)
		#else
			SAMPLE(0.111111f,0.116153f)
			SAMPLE(0.333333f,0.111599f)
			SAMPLE(0.555556f,0.103019f)
			SAMPLE(0.777778f,0.091369f)
			SAMPLE(1.000000f,0.077860f)
		#endif
		#undef SAMPLE
		#ifdef DOF
			color = lerp(color,dof_color,dof_weight);
		#endif
	#else
		half3 color = texture2D(s_texture_0,texcoord).xyz;
		#ifdef DOF
			half3 dof_color = texture2DLinear(s_texture_6,texcoord,s_material_textures[6]).xyz;
			color = lerp(color,dof_color,dof_weight);
		#endif
	#endif
	
	#ifdef AUXILIARY
		#ifdef MULTISAMPLE_0 || !USE_ARB_TEXTURE_MULTISAMPLE
			half4 auxiliary = texture2DDeferredNorm(s_texture_2,texcoord);
		#else
			int2 itexcoord = int2(texcoord * s_viewport.xy);
			half4 auxiliary = texelFetch(s_texture_2,itexcoord,0);
			for(int i = 1; i < MULTISAMPLE_SAMPLES; i++) {
				auxiliary += texelFetch(s_texture_2,itexcoord,i);
			}
			auxiliary *= MULTISAMPLE_ISAMPLES;
		#endif
		color = lerp(color,auxiliary.xyz,auxiliary.w);
	#endif
	
	#ifdef GLOW
		half4 glow = texture2DLinear(s_texture_5,texcoord,s_material_textures[5]);
		color += glow.xyz;
	#endif
	
	#ifdef HDR
		half luminance = texture2D(s_texture_7,float2(0.5f,0.5f)).x;
		half3 bright = texture2D(s_texture_8,texcoord).xyz;
		color = color * luminance + bright;
	#endif
	
	#ifdef USE_SRGB
		color = pow(color,half3(1.0f / 2.2f));
	#endif
	
	color = texture3D(s_texture_9,color * (31.0f / 32.0f) + 1.0f / 64.0f).xyz;
	
	gl_FragColor = half4(color,1.0f);
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
	float4 texcoord_2 : TEXCOORD2;
};

half4 modelview_x;
half4 modelview_y;
half4 modelview_z;
half4 old_modelview_x;
half4 old_modelview_y;
half4 old_modelview_z;
half4 modelviewprojection_x;
half4 modelviewprojection_y;
half4 modelviewprojection_w;
half4 motion_blur_scale;
half focal_distance;
half focal_range;
half focal_power;
half blur_irange;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#ifdef REFRACTION
		half4 refraction = tex2D(s_texture_3,IN.texcoord_0);
		half2 refraction_offset = (refraction.xy - refraction.zw) * IN.texcoord_1;
		refraction_offset *= saturate(tex2D(s_texture_3,IN.texcoord_0 + refraction_offset).w * 255.0f);
		float2 texcoord = IN.texcoord_0.xy + refraction_offset;
	#else
		float2 texcoord = IN.texcoord_0.xy;
	#endif
	
	#ifdef MOTION_BLUR || DOF
		half4 deferred_depth = tex2D(s_texture_1,IN.texcoord_0);
		float depth = getDeferredDepth(deferred_depth);
	#endif
	
	#ifdef DOF
		half dof_weight = pow(saturate(max(abs(depth - focal_distance) - focal_range,0.0f) * blur_irange),focal_power);
	#endif
	
	#ifdef MOTION_BLUR
		half4 position = half4(normalize(IN.texcoord_2.xyz) * (IN.texcoord_2.w * depth),1.0f);
		half4 old_position = half4(dot(old_modelview_x,position),dot(old_modelview_y,position),dot(old_modelview_z,position),1.0f);
		position.xyz = half3(dot(modelview_x.xyz,position.xyz),dot(modelview_y.xyz,position.xyz),dot(modelview_z.xyz,position.xyz));
		half3 offset = (position.xyz - old_position.xyz) * motion_blur_scale.x;
		#ifdef VELOCITY_BLUR
			half3 velocity = tex2D(s_texture_4,texcoord).xyz;
			offset -= (velocity - 127.0f / 255.0f) * motion_blur_scale.y;
		#endif
		old_position.xyz = position.xyz - offset;
		half3 texcoord_0 = half3(dot(modelviewprojection_x,position),dot(modelviewprojection_y,position),dot(modelviewprojection_w,position));
		half3 texcoord_1 = half3(dot(modelviewprojection_x,old_position),dot(modelviewprojection_y,old_position),dot(modelviewprojection_w,old_position));
		offset.xy = texcoord_0.xy / texcoord_0.z - texcoord_1.xy / texcoord_1.z;
		#ifdef DOF
			#define SAMPLE(OFFSET,WEIGHT) { \
				float2 texcoord_0 = texcoord - offset.xy * (OFFSET); \
				float2 texcoord_1 = texcoord + offset.xy * (OFFSET); \
				color += tex2D(s_texture_0,texcoord_0).xyz * (WEIGHT); \
				color += tex2D(s_texture_0,texcoord_1).xyz * (WEIGHT); \
				dof_color += tex2DLinear(s_texture_6,texcoord_0,s_material_textures[6]).xyz * (WEIGHT); \
				dof_color += tex2DLinear(s_texture_6,texcoord_1,s_material_textures[6]).xyz * (WEIGHT); \
			}
		#else
			#define SAMPLE(OFFSET,WEIGHT) { \
				float2 texcoord_0 = texcoord - offset.xy * (OFFSET); \
				float2 texcoord_1 = texcoord + offset.xy * (OFFSET); \
				color += tex2D(s_texture_0,texcoord_0).xyz * (WEIGHT); \
				color += tex2D(s_texture_0,texcoord_1).xyz * (WEIGHT); \
			}
		#endif
		half3 color = 0.0f;
		half3 dof_color = 0.0f;
		#ifdef QUALITY_HIGH
			SAMPLE(0.058824f,0.064806f)
			SAMPLE(0.176471f,0.064011f)
			SAMPLE(0.294118f,0.062450f)
			SAMPLE(0.411765f,0.060179f)
			SAMPLE(0.529412f,0.057279f)
			SAMPLE(0.647059f,0.053851f)
			SAMPLE(0.764706f,0.050006f)
			SAMPLE(0.882353f,0.045866f)
			SAMPLE(1.000000f,0.041552f)
		#else
			SAMPLE(0.111111f,0.116153f)
			SAMPLE(0.333333f,0.111599f)
			SAMPLE(0.555556f,0.103019f)
			SAMPLE(0.777778f,0.091369f)
			SAMPLE(1.000000f,0.077860f)
		#endif
		#undef SAMPLE
		#ifdef DOF
			color = lerp(color,dof_color,dof_weight);
		#endif
	#else
		half3 color = tex2D(s_texture_0,texcoord).xyz;
		#ifdef DOF
			half3 dof_color = tex2DLinear(s_texture_6,texcoord,s_material_textures[6]).xyz;
			color = lerp(color,dof_color,dof_weight);
		#endif
	#endif
	
	#ifdef AUXILIARY
		half4 auxiliary = tex2D(s_texture_2,texcoord);
		color = lerp(color,auxiliary.xyz,auxiliary.w);
	#endif
	
	#ifdef GLOW
		half4 glow = tex2DLinear(s_texture_5,texcoord,s_material_textures[4]);
		color += glow.xyz;
	#endif
	
	#ifdef HDR
		half luminance = tex2D(s_texture_7,half2(0.5f,0.5f)).x;
		half3 bright = tex2D(s_texture_8,texcoord).xyz;
		color = color * luminance + bright;
	#endif
	
	#ifdef USE_SRGB
		color = pow(color,1.0f / 2.2f);
	#endif
	
	color = tex3D(s_texture_9,color * (31.0f / 32.0f) + 1.0f / 64.0f).xyz;
	
	return half4(color,1.0f);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
TEXTURE_2DMS s_texture_1 : register(t1);
TEXTURE_2DMS s_texture_2 : register(t2);
TEXTURE_2DMS s_texture_3 : register(t3);
TEXTURE_2DMS s_texture_4 : register(t4);
Texture2D s_texture_5 : register(t5);
Texture2D s_texture_6 : register(t6);
Texture2D s_texture_7 : register(t7);
Texture2D s_texture_8 : register(t8);
Texture3D s_texture_9 : register(t9);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
};

float4 modelview_x;
float4 modelview_y;
float4 modelview_z;
float4 old_modelview_x;
float4 old_modelview_y;
float4 old_modelview_z;
float4 modelviewprojection_x;
float4 modelviewprojection_y;
float4 modelviewprojection_w;
float4 motion_blur_scale;
float focal_distance;
float focal_range;
float focal_power;
float blur_irange;

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#ifdef REFRACTION
		half4 refraction = texture2DDeferredNorm(s_texture_3,s_sampler_3,IN.texcoord_0);
		half2 refraction_offset = (refraction.xy - refraction.zw) * IN.texcoord_1;
		refraction_offset *= saturate(texture2DDeferredNorm(s_texture_3,s_sampler_3,IN.texcoord_0 + refraction_offset).w * 255.0f);
		float2 texcoord = IN.texcoord_0.xy + refraction_offset;
	#else
		float2 texcoord = IN.texcoord_0.xy;
	#endif
	
	#ifdef MOTION_BLUR || DOF
		half4 deferred_depth = texture2DDeferredNorm(s_texture_1,s_sampler_1,IN.texcoord_0);
		float depth = getDeferredDepth(deferred_depth);
	#endif
	
	#ifdef DOF
		half dof_weight = pow(saturate(max(abs(depth - focal_distance) - focal_range,0.0f) * blur_irange),focal_power);
	#endif
	
	#ifdef MOTION_BLUR
		half4 position = half4(normalize(IN.texcoord_2.xyz) * (IN.texcoord_2.w * depth),1.0f);
		half4 old_position = half4(dot(old_modelview_x,position),dot(old_modelview_y,position),dot(old_modelview_z,position),1.0f);
		position.xyz = half3(dot(modelview_x.xyz,position.xyz),dot(modelview_y.xyz,position.xyz),dot(modelview_z.xyz,position.xyz));
		half3 offset = (position.xyz - old_position.xyz) * motion_blur_scale.x;
		#ifdef VELOCITY_BLUR
			half3 velocity = texture2DDeferredNorm(s_texture_4,s_sampler_4,texcoord).xyz;
			offset -= (velocity - 127.0f / 255.0f) * motion_blur_scale.y;
		#endif
		old_position.xyz = position.xyz - offset;
		half3 texcoord_0 = half3(dot(modelviewprojection_x,position),dot(modelviewprojection_y,position),dot(modelviewprojection_w,position));
		half3 texcoord_1 = half3(dot(modelviewprojection_x,old_position),dot(modelviewprojection_y,old_position),dot(modelviewprojection_w,old_position));
		offset.xy = texcoord_0.xy / texcoord_0.z - texcoord_1.xy / texcoord_1.z;
		#ifdef DOF
			#define SAMPLE(OFFSET,WEIGHT) { \
				float2 texcoord_0 = texcoord - offset.xy * (OFFSET); \
				float2 texcoord_1 = texcoord + offset.xy * (OFFSET); \
				color += s_texture_0.Sample(s_sampler_0,texcoord_0).xyz * (WEIGHT); \
				color += s_texture_0.Sample(s_sampler_0,texcoord_1).xyz * (WEIGHT); \
				dof_color += s_texture_6.Sample(s_sampler_6,texcoord_0).xyz * (WEIGHT); \
				dof_color += s_texture_6.Sample(s_sampler_6,texcoord_1).xyz * (WEIGHT); \
			}
		#else
			#define SAMPLE(OFFSET,WEIGHT) { \
				float2 texcoord_0 = texcoord - offset.xy * (OFFSET); \
				float2 texcoord_1 = texcoord + offset.xy * (OFFSET); \
				color += s_texture_0.Sample(s_sampler_0,texcoord_0).xyz * (WEIGHT); \
				color += s_texture_0.Sample(s_sampler_0,texcoord_1).xyz * (WEIGHT); \
			}
		#endif
		half3 color = 0.0f;
		half3 dof_color = 0.0f;
		#ifdef QUALITY_HIGH
			SAMPLE(0.058824f,0.064806f)
			SAMPLE(0.176471f,0.064011f)
			SAMPLE(0.294118f,0.062450f)
			SAMPLE(0.411765f,0.060179f)
			SAMPLE(0.529412f,0.057279f)
			SAMPLE(0.647059f,0.053851f)
			SAMPLE(0.764706f,0.050006f)
			SAMPLE(0.882353f,0.045866f)
			SAMPLE(1.000000f,0.041552f)
		#else
			SAMPLE(0.111111f,0.116153f)
			SAMPLE(0.333333f,0.111599f)
			SAMPLE(0.555556f,0.103019f)
			SAMPLE(0.777778f,0.091369f)
			SAMPLE(1.000000f,0.077860f)
		#endif
		#undef SAMPLE
		#ifdef DOF
			color = lerp(color,dof_color,dof_weight);
		#endif
	#else
		half3 color = s_texture_0.Sample(s_sampler_0,texcoord).xyz;
		#ifdef DOF
			half3 dof_color = s_texture_6.Sample(s_sampler_6,texcoord).xyz;
			color = lerp(color,dof_color,dof_weight);
		#endif
	#endif
	
	#ifdef AUXILIARY
		#ifdef MULTISAMPLE_0
			half4 auxiliary = texture2DDeferredNorm(s_texture_2,s_sampler_2,texcoord);
		#else
			int2 itexcoord = int2(texcoord * s_viewport.xy);
			half4 auxiliary = s_texture_2.Load(itexcoord,0);
			[unroll] for(int i = 1; i < MULTISAMPLE_SAMPLES; i++) {
				auxiliary += s_texture_2.Load(itexcoord,i);
			}
			auxiliary *= MULTISAMPLE_ISAMPLES;
		#endif
		color = lerp(color,auxiliary.xyz,auxiliary.w);
	#endif
	
	#ifdef GLOW
		half3 glow = s_texture_5.Sample(s_sampler_5,texcoord).xyz;
		color += glow;
	#endif
	
	#ifdef HDR
		half luminance = s_texture_7.Sample(s_sampler_7,half2(0.5f,0.5f)).x;
		half3 bright = s_texture_8.Sample(s_sampler_8,texcoord).xyz;
		color = color * luminance + bright;
	#endif
	
	#ifdef USE_SRGB
		color = pow(color,1.0f / 2.2f);
	#endif
	
	color = s_texture_9.Sample(s_sampler_9,color * (31.0f / 32.0f) + 1.0f / 64.0f).xyz;
	
	return half4(color,1.0f);
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
uniform sampler2D s_texture_5 : TEXUNIT5;
uniform sampler2D s_texture_6 : TEXUNIT6;
uniform sampler2D s_texture_7 : TEXUNIT7;
uniform sampler2D s_texture_8 : TEXUNIT8;
uniform sampler3D s_texture_9 : TEXUNIT9;

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
	float2 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
};

uniform half4 modelview_x;
uniform half4 modelview_y;
uniform half4 modelview_z;
uniform half4 old_modelview_x;
uniform half4 old_modelview_y;
uniform half4 old_modelview_z;
uniform half4 modelviewprojection_x;
uniform half4 modelviewprojection_y;
uniform half4 modelviewprojection_w;
uniform half4 motion_blur_scale;
uniform half focal_distance;
uniform half focal_range;
uniform half focal_power;
uniform half blur_irange;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#ifdef REFRACTION
		half4 refraction = h4tex2D(s_texture_3,IN.texcoord_0);
		half2 refraction_offset = (refraction.xy - refraction.zw) * IN.texcoord_1;
		refraction_offset *= saturate(h4tex2D(s_texture_3,IN.texcoord_0 + refraction_offset).w * 255.0f);
		half2 texcoord = IN.texcoord_0.xy + refraction_offset;
	#else
		half2 texcoord = IN.texcoord_0.xy;
	#endif
	
	#ifdef MOTION_BLUR || DOF
		half4 deferred_depth = h4tex2D(s_texture_1,IN.texcoord_0);
		half depth = getDeferredDepth(deferred_depth);
	#endif
	
	#ifdef DOF
		half dof_weight = pow(saturate(max(abs(depth - focal_distance) - focal_range,0.0f) * blur_irange),focal_power);
	#endif
	
	#ifdef MOTION_BLUR
		half4 position = half4(normalize(IN.texcoord_2.xyz) * (IN.texcoord_2.w * depth),1.0f);
		half4 old_position = half4(dot(old_modelview_x,position),dot(old_modelview_y,position),dot(old_modelview_z,position),1.0f);
		position.xyz = half3(dot(modelview_x.xyz,position.xyz),dot(modelview_y.xyz,position.xyz),dot(modelview_z.xyz,position.xyz));
		half3 offset = (position.xyz - old_position.xyz) * motion_blur_scale.x;
		#ifdef VELOCITY_BLUR
			half3 velocity = h3tex2D(s_texture_4,texcoord);
			offset -= (velocity - 127.0f / 255.0f) * motion_blur_scale.y;
		#endif
		old_position.xyz = position.xyz - offset;
		half3 texcoord_0 = half3(dot(modelviewprojection_x,position),dot(modelviewprojection_y,position),dot(modelviewprojection_w,position));
		half3 texcoord_1 = half3(dot(modelviewprojection_x,old_position),dot(modelviewprojection_y,old_position),dot(modelviewprojection_w,old_position));
		offset.xy = texcoord_0.xy / texcoord_0.z - texcoord_1.xy / texcoord_1.z;
		#ifdef DOF
			#define SAMPLE(OFFSET,WEIGHT) { \
				half2 texcoord_0 = texcoord - offset.xy * (OFFSET); \
				half2 texcoord_1 = texcoord + offset.xy * (OFFSET); \
				color += h3tex2D(s_texture_0,texcoord_0) * (WEIGHT); \
				color += h3tex2D(s_texture_0,texcoord_1) * (WEIGHT); \
				dof_color += h3tex2D(s_texture_6,texcoord_0) * (WEIGHT); \
				dof_color += h3tex2D(s_texture_6,texcoord_1) * (WEIGHT); \
			}
		#else
			#define SAMPLE(OFFSET,WEIGHT) { \
				half2 texcoord_0 = texcoord - offset.xy * (OFFSET); \
				half2 texcoord_1 = texcoord + offset.xy * (OFFSET); \
				color += h3tex2D(s_texture_0,texcoord_0) * (WEIGHT); \
				color += h3tex2D(s_texture_0,texcoord_1) * (WEIGHT); \
			}
		#endif
		half3 color = 0.0f;
		half3 dof_color = 0.0f;
		#ifdef QUALITY_HIGH
			SAMPLE(0.058824f,0.064806f)
			SAMPLE(0.176471f,0.064011f)
			SAMPLE(0.294118f,0.062450f)
			SAMPLE(0.411765f,0.060179f)
			SAMPLE(0.529412f,0.057279f)
			SAMPLE(0.647059f,0.053851f)
			SAMPLE(0.764706f,0.050006f)
			SAMPLE(0.882353f,0.045866f)
			SAMPLE(1.000000f,0.041552f)
		#else
			SAMPLE(0.111111f,0.116153f)
			SAMPLE(0.333333f,0.111599f)
			SAMPLE(0.555556f,0.103019f)
			SAMPLE(0.777778f,0.091369f)
			SAMPLE(1.000000f,0.077860f)
		#endif
		#undef SAMPLE
		#ifdef DOF
			color = lerp(color,dof_color,dof_weight);
		#endif
	#else
		half3 color = h3tex2D(s_texture_0,texcoord);
		#ifdef DOF
			half3 dof_color = h3tex2D(s_texture_6,texcoord);
			color = lerp(color,dof_color,dof_weight);
		#endif
	#endif
	
	#ifdef AUXILIARY
		half4 auxiliary = h4tex2D(s_texture_2,texcoord);
		color = lerp(color,auxiliary.xyz,auxiliary.w);
	#endif
	
	#ifdef GLOW
		half4 glow = h4tex2D(s_texture_5,texcoord);
		color += glow.xyz;
	#endif
	
	#ifdef HDR
		half luminance = h1tex2D(s_texture_7,half2(0.5f,0.5f));
		half3 bright = h3tex2D(s_texture_8,texcoord);
		color = color * luminance + bright;
	#endif
	
	#ifdef USE_SRGB
		color = pow(color,1.0f / 2.2f);
	#endif
	
	color = h3tex3D(s_texture_9,color * (31.0f / 32.0f) + 1.0f / 64.0f);
	
	return half4(color,1.0f);
}

#endif
