/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_light_omni.shader
 * Desc:    Render light omni shader
 * Version: 1.06
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

/* s_texture_0 is deferred color texture
 * s_texture_1 is deferred depth texture
 *
 * s_texture_11 is light modulation texture
 * s_texture_12 is light shadow color texture
 * s_texture_13 is light shadow depth texture
 * s_texture_14 is light shadow noise texture
 * s_texture_15 is light virtual cube texture
 */

#include <core/shaders/common/fragment_base.h>
#include <core/shaders/common/fragment_base_shadow_omni.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform SAMPLER_2DMS s_texture_0;
uniform SAMPLER_2DMS s_texture_1;

uniform samplerCube s_texture_11;
SAMPLER_SHADOW_OMNI_PCF

uniform half4 modelview_x;
uniform half4 modelview_y;
uniform half4 modelview_z;

/*
 */
void main() {
	
	half4 deferred_depth = texture2DDeferredNorm(s_texture_0,gl_TexCoord[0].xy);
	float depth = getDeferredDepth(deferred_depth);
	if(depth > 0.9f) discard;
	
	float3 position = normalize(gl_TexCoord[1].xyz) * (gl_TexCoord[1].w * depth);
	
	half4 deferred_normal = texture2DDeferredNorm(s_texture_1,gl_TexCoord[0].xy);
	half3 normal = normalize(getDeferredNormal(deferred_normal));
	half specular = getDeferredSpecular(deferred_normal);
	
	half3 camera_direction = -position;
	half4 light_direction = half4(getOmniRadius(s_light_position - position) * s_light_iradius.w,s_light_iradius.w * s_light_iradius.w);
	
	half4 color = getDiffuseSpecularDeferredNormalizeAttenuate(specular,normal,light_direction,camera_direction);
	
	#ifdef SHADOW
		half3 direction = position - s_light_shadow_offset;
		half3 shadow_direction = half3(dot(modelview_x.xyz,direction),dot(modelview_y.xyz,direction),dot(modelview_z.xyz,direction));
		half4 shadow_texcoord = half4(shadow_direction * s_light_shadow_depth_range.x,s_light_shadow_depth_range.y);
		#ifdef USE_TRANSLUCENT
			shadow_direction = shadow_direction * s_light_shadow_iradius.x;
		#endif
		color.xyz = shadowOmniPCF(color.xyz,s_texture_13,s_texture_12,s_texture_14,s_texture_15,shadow_texcoord,shadow_direction,s_material_textures[13]);
	#endif
	
	half3 modulation = textureCube(s_texture_11,(half4(position - s_light_position,0.0f) * s_light_transform).xyz).xyz;
	color *= half4(modulation,dot(modulation,half3(1.0f / 3.0f)));
	
	gl_FragColor = color * 0.5f;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float2 position : VPOS;
	float2 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

half4 modelview_x;
half4 modelview_y;
half4 modelview_z;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_depth = tex2D(s_texture_0,IN.texcoord_0);
	float depth = getDeferredDepth(deferred_depth);
	if(depth > 0.9f) discard;
	
	float3 position = normalize(IN.texcoord_1.xyz) * (IN.texcoord_1.w * depth);
	
	half4 deferred_normal = tex2D(s_texture_1,IN.texcoord_0);
	half3 normal = normalize(getDeferredNormal(deferred_normal));
	half specular = getDeferredSpecular(deferred_normal);
	
	half3 camera_direction = -position;
	half4 light_direction = half4(getOmniRadius(s_light_position - position) * s_light_iradius.w,s_light_iradius.w * s_light_iradius.w);
	
	half4 color = getDiffuseSpecularDeferredNormalizeAttenuate(specular,normal,light_direction,camera_direction);
	
	#ifdef SHADOW
		half3 direction = position - s_light_shadow_offset;
		half3 shadow_direction = half3(dot(modelview_x.xyz,direction),dot(modelview_y.xyz,direction),dot(modelview_z.xyz,direction));
		half4 shadow_texcoord = half4(shadow_direction * s_light_shadow_depth_range.x,s_light_shadow_depth_range.y);
		#ifdef USE_TRANSLUCENT
			shadow_direction = shadow_direction * s_light_shadow_iradius.x;
		#endif
		color.xyz = shadowOmniPCF(color.xyz,s_texture_13,s_texture_12,s_texture_14,s_texture_15,IN.position,shadow_texcoord,shadow_direction,s_material_textures[13]);
	#endif
	
	half3 modulation = texCUBE(s_texture_11,mul(position - s_light_position,(float3x3)s_light_transform)).xyz;
	color *= half4(modulation,dot(modulation,1.0f / 3.0f));
	
	return color * 0.5f;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

TEXTURE_2DMS s_texture_0 : register(t0);
TEXTURE_2DMS s_texture_1 : register(t1);

TextureCube s_texture_11 : register(t11);
TEXTURE_SHADOW_OMNI_PCF

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

float4 modelview_x;
float4 modelview_y;
float4 modelview_z;

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 deferred_depth = texture2DDeferredNorm(s_texture_0,s_sampler_0,IN.texcoord_0);
	float depth = getDeferredDepth(deferred_depth);
	if(depth > 0.9f) discard;
	
	float3 position = normalize(IN.texcoord_1.xyz) * (IN.texcoord_1.w * depth);
	
	half4 deferred_normal = texture2DDeferredNorm(s_texture_1,s_sampler_1,IN.texcoord_0);
	half3 normal = normalize(getDeferredNormal(deferred_normal));
	half specular = getDeferredSpecular(deferred_normal);
	
	half3 camera_direction = -position;
	half4 light_direction = half4(getOmniRadius(s_light_position - position) * s_light_iradius.w,s_light_iradius.w * s_light_iradius.w);
	
	half4 color = getDiffuseSpecularDeferredNormalizeAttenuate(specular,normal,light_direction,camera_direction);
	
	#ifdef SHADOW
		half3 direction = position - s_light_shadow_offset;
		half3 shadow_direction = half3(dot(modelview_x.xyz,direction),dot(modelview_y.xyz,direction),dot(modelview_z.xyz,direction));
		half4 shadow_texcoord = half4(shadow_direction * s_light_shadow_depth_range.x,s_light_shadow_depth_range.y);
		#ifdef USE_TRANSLUCENT
			shadow_direction = shadow_direction * s_light_shadow_iradius.x;
		#endif
		color.xyz = shadowOmniPCF(color.xyz,s_texture_13,s_sampler_13,s_sampler_compare_13,s_texture_12,s_sampler_12,s_texture_14,s_sampler_14,s_texture_15,s_sampler_15,IN.position,shadow_texcoord,shadow_direction);
	#endif
	
	half3 modulation = s_texture_11.Sample(s_sampler_11,mul(position - s_light_position,(float3x3)s_light_transform)).xyz;
	color *= half4(modulation,dot(modulation,1.0f / 3.0f));
	
	return color * 0.5f;
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

uniform samplerCUBE s_texture_11 : TEXUNIT11;
SAMPLER_SHADOW_OMNI_PCF

struct FRAGMENT_IN {
	float2 position : WPOS;
	float2 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

uniform half4 modelview_x;
uniform half4 modelview_y;
uniform half4 modelview_z;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_depth = tex2D(s_texture_0,IN.texcoord_0);
	float depth = getDeferredDepth(deferred_depth);
	if(depth > 0.9f) discard;
	
	float3 position = normalize(IN.texcoord_1.xyz) * (IN.texcoord_1.w * depth);
	
	half4 deferred_normal = h4tex2D(s_texture_1,IN.texcoord_0);
	half3 normal = normalize(getDeferredNormal(deferred_normal));
	half specular = getDeferredSpecular(deferred_normal);
	
	half3 camera_direction = -position;
	half4 light_direction = half4(getOmniRadius(s_light_position - position) * s_light_iradius.w,s_light_iradius.w * s_light_iradius.w);
	
	half4 color = getDiffuseSpecularDeferredNormalizeAttenuate(specular,normal,light_direction,camera_direction);
	
	#ifdef SHADOW
		half3 direction = position - s_light_shadow_offset;
		half3 shadow_direction = half3(dot(modelview_x.xyz,direction),dot(modelview_y.xyz,direction),dot(modelview_z.xyz,direction));
		half4 shadow_texcoord = half4(shadow_direction * s_light_shadow_depth_range.x,s_light_shadow_depth_range.y);
		#ifdef USE_TRANSLUCENT
			shadow_direction = shadow_direction * s_light_shadow_iradius.x;
		#endif
		color.xyz = shadowOmniPCF(color.xyz,s_texture_13,s_texture_12,s_texture_14,s_texture_15,IN.position,shadow_texcoord,shadow_direction);
	#endif
	
	half3 modulation = h3texCUBE(s_texture_11,mul(position - s_light_position,(float3x3)s_light_transform));
	color *= half4(modulation,dot(modulation,1.0f / 3.0f));
	
	return color * 0.5f;
}

#endif
