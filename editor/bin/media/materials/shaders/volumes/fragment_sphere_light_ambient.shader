/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_sphere_light_ambient.shader
 * Desc:    VolumeSphere light ambient shader
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

/* s_texture_15 is deferred depth texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform SAMPLER_2DMS s_texture_15;

uniform float4 s_volume_icamera_position;
uniform half s_volume_fade;

uniform half4 diffuse_color;
uniform half volume_power;

/*
 */
void main() {
	
	half4 deferred_depth = texture2DDeferredProj(s_texture_15,gl_TexCoord[7],s_material_textures[15].xy);
	
	float3 dir = normalize(gl_TexCoord[0].xyz) * getDeferredDepth(deferred_depth) * s_depth_range.y;
	float k = saturate(-dot(s_volume_icamera_position.xyz,dir) / dot(dir,dir));
	float3 p = s_volume_icamera_position.xyz + dir * k;
	
	half attenuation = half(gl_TexCoord[1].y) / (1.0f + dot(p,p) * half(gl_TexCoord[1].x)) - half(gl_TexCoord[1].z);
	attenuation = pow(saturate(attenuation),volume_power);
	
	gl_FragColor = half4(diffuse_color.xyz * (attenuation * s_volume_fade),1.0f);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float3 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	float4 texcoord_7 : TEXCOORD7;
};

float4 s_volume_icamera_position;
half s_volume_fade;

half4 diffuse_color;
half volume_power;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_depth = tex2Dproj(s_texture_15,IN.texcoord_7);
	
	float3 dir = normalize(IN.texcoord_0) * getDeferredDepth(deferred_depth) * s_depth_range.y;
	float k = saturate(-dot(s_volume_icamera_position.xyz,dir) / dot(dir,dir));
	float3 p = s_volume_icamera_position.xyz + dir * k;
	
	half attenuation = IN.texcoord_1.y / (1.0f + dot(p,p) * IN.texcoord_1.x) - IN.texcoord_1.z;
	attenuation = pow(saturate(attenuation),volume_power);
	
	return half4(diffuse_color.xyz * (attenuation * s_volume_fade),1.0f);
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

TEXTURE_2DMS s_texture_15 : register(t15);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float3 texcoord_0 : TEXCOORD0;
	float3 texcoord_1 : TEXCOORD1;
};

cbuffer shader_volume_parameters {
	float4 s_volume_icamera_position;
	float s_volume_fade;
};

cbuffer shader_parameters {
	float4 diffuse_color;
	float volume_power;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 deferred_depth = texture2DDeferredRect(s_texture_15,s_sampler_15,IN.position.xy,s_material_textures[15].xy);
	
	float3 dir = normalize(IN.texcoord_0) * getDeferredDepth(deferred_depth) * s_depth_range.y;
	float k = saturate(-dot(s_volume_icamera_position.xyz,dir) / dot(dir,dir));
	float3 p = s_volume_icamera_position.xyz + dir * k;
	
	half attenuation = IN.texcoord_1.y / (1.0f + dot(p,p) * IN.texcoord_1.x) - IN.texcoord_1.z;
	attenuation = pow(saturate(attenuation),volume_power);
	
	return float4(diffuse_color.xyz * (attenuation * s_volume_fade),1.0f);
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_15 : TEXUNIT15;

struct FRAGMENT_IN {
	float3 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	float4 texcoord_9 : TEXCOORD9;
};

uniform float4 s_volume_icamera_position;
uniform half s_volume_fade;

uniform half4 diffuse_color;
uniform half volume_power;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 deferred_depth = h4tex2Dproj(s_texture_15,IN.texcoord_9.xyw);
	
	float3 dir = normalize(IN.texcoord_0) * getDeferredDepth(deferred_depth) * s_depth_range.y;
	float k = saturate(-dot(s_volume_icamera_position.xyz,dir) / dot(dir,dir));
	float3 p = s_volume_icamera_position.xyz + dir * k;
	
	half attenuation = IN.texcoord_1.y / (1.0f + dot(p,p) * IN.texcoord_1.x) - IN.texcoord_1.z;
	attenuation = pow(saturate(attenuation),volume_power);
	
	return half4(diffuse_color.xyz * (attenuation * s_volume_fade),1.0f);
}

#endif
