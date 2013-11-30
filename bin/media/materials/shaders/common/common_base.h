/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    common_base.h
 * Desc:    Base common shader
 * Version: 1.14
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

#ifndef __COMMON_BASE_H__
#define __COMMON_BASE_H__

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

/* ARB Uniform buffer object
 */
#ifdef USE_ARB_UNIFORM_BUFFER_OBJECT
	#define UNIFORM_BUFFER_BEGIN(NAME) uniform NAME {
	#define UNIFORM_BUFFER_END };
#else
	#define UNIFORM_BUFFER_BEGIN(NAME)
	#define UNIFORM_BUFFER_END
#endif

/* EXT Cg shader
 */
#ifndef USE_EXT_CG_SHADER
	#define int2 ivec2
	#define int3 ivec3
	#define int4 ivec4
	#define half float
	#define half2 vec2
	#define half3 vec3
	#define half4 vec4
	#define half3x3 mat3
	#define half4x4 mat4
	#define float2 vec2
	#define float3 vec3
	#define float4 vec4
	#define float3x3 mat3
	#define float4x4 mat4
	#define lerp(X,Y,VALUE) mix(X,Y,VALUE)
	#define saturate(VALUE) clamp(VALUE,0.0f,1.0f)
	#define rsqrt(VALUE) inversesqrt(VALUE)
#endif

/* shader parameters
 */
uniform float4 s_viewport;
uniform float4 s_depth_range;
uniform half4 s_solid_color;
uniform half4 s_ambient_color;
uniform float4x4 s_projection;
uniform float4x4 s_modelview;
uniform float4x4 s_modelviewprojection;
uniform float3 s_camera_position;
uniform float3 s_camera_direction;
uniform float3 s_camera_offset;

/* shader transform parameters
 */
uniform float4 s_transform[3];

/* shader light parameters
 */
uniform float3 s_light_position;
uniform float4 s_light_positions[4];
uniform float3 s_light_direction;
uniform half4 s_light_color;
uniform half4 s_light_colors[4];
uniform float4 s_light_iradius;
uniform float4 s_light_iradiuses;
uniform float4 s_light_attenuations;
uniform float4x4 s_light_transform;
uniform float4x4 s_light_projection;
uniform half4 s_light_coefficients[9];
uniform float3 s_light_shadow_offset;
uniform float4 s_light_shadow_offsets[4];
uniform half4 s_light_shadow_iradius;
uniform half3 s_light_shadow_depth_bias;
uniform half2 s_light_shadow_depth_range;
uniform float4x4 s_light_shadow_projection;
uniform float4x4 s_light_shadow_projections[4];

/* shader light front parameters
 */
uniform half s_light_front;

/* shader material parameters
 */
uniform half3 s_material_detail;
uniform half3 s_material_fresnel;
uniform float4 s_material_textures[16];

/* shader material tessellation parameters
 */
uniform half4 s_material_tessellation_factor;
uniform half3 s_material_tessellation_distance;

/* shader material animation parameters
 */
uniform float4 s_material_animation_stem;
uniform float3 s_material_animation_leaf;

/* shader material ambient parameters
 */
uniform float4x4 s_material_reflection_transform;
uniform float3 s_material_reflection_center;
uniform float s_material_reflection_radius;
uniform half3 s_material_reflection_color;

/* shader material light parameters
 */
uniform half3 s_material_shading;
uniform half4 s_material_shadings[4];
uniform half2 s_material_phong_rim;
uniform half4 s_material_anisotropy;

/* shader surface parameters
 */
uniform float4 s_surface_distances;
uniform float4 s_surface_bound_sphere;

/* light omni radius
 */
float3 getOmniRadius(float3 radius) {
	half3 x = s_light_transform[0].xyz;
	half3 y = s_light_transform[1].xyz;
	half3 z = s_light_transform[2].xyz;
	return float3(x * (dot(x,radius) * s_light_iradius.x) + y * (dot(y,radius) * s_light_iradius.y) + z * (dot(z,radius) * s_light_iradius.z));
}

/* light attenuation
 */
half getAttenuation(half radius) {
	#ifdef SHOW_LIGHTS
		half attenuation = 1.0f;
	#else
		half attenuation = saturate(radius);
		attenuation *= attenuation;
		#ifdef USE_SRGB
			attenuation *= attenuation;
		#endif
	#endif
	return attenuation;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

/*
 */
##pragma warning(disable : 3205 3571)

/* shader parameters
 */
float4 s_viewport;
float4 s_depth_range;
half4 s_solid_color;
half4 s_ambient_color;
float4x4 s_projection;
float4x4 s_modelview;
float4x4 s_modelviewprojection;
float3 s_camera_position;
float3 s_camera_direction;
float3 s_camera_offset;

/* shader transform parameters
 */
float4 s_transform[3];

/* shader light parameters
 */
float3 s_light_position;
float4 s_light_positions[4];
float3 s_light_direction;
half4 s_light_color;
half4 s_light_colors[4];
float4 s_light_iradius;
float4 s_light_iradiuses;
float4 s_light_attenuations;
float4x4 s_light_transform;
float4x4 s_light_projection;
half4 s_light_coefficients[9];
float3 s_light_shadow_offset;
float4 s_light_shadow_offsets[4];
half4 s_light_shadow_iradius;
half3 s_light_shadow_depth_bias;
half2 s_light_shadow_depth_range;
float4x4 s_light_shadow_projection;
float4x4 s_light_shadow_projections[4];

/* shader light front parameters
 */
half s_light_front;

/* shader material parameters
 */
half3 s_material_detail;
half3 s_material_fresnel;
float4 s_material_textures[16];

/* shader material tessellation parameters
 */
half4 s_material_tessellation_factor;
half3 s_material_tessellation_distance;

/* shader material animation parameters
 */
float4 s_material_animation_stem;
float3 s_material_animation_leaf;

/* shader material ambient parameters
 */
float4x4 s_material_reflection_transform;
float3 s_material_reflection_center;
float s_material_reflection_radius;
half3 s_material_reflection_color;

/* shader material light parameters
 */
half3 s_material_shading;
half4 s_material_shadings[4];
half2 s_material_phong_rim;
half4 s_material_anisotropy;

/* shader surface parameters
 */
float4 s_surface_distances;
float4 s_surface_bound_sphere;

/* light omni radius
 */
float3 getOmniRadius(float3 radius) {
	half3 x = s_light_transform._m00_m10_m20;
	half3 y = s_light_transform._m01_m11_m21;
	half3 z = s_light_transform._m02_m12_m22;
	return float3(x * (dot(x,radius) * s_light_iradius.x) + y * (dot(y,radius) * s_light_iradius.y) + z * (dot(z,radius) * s_light_iradius.z));
}

/* light attenuation
 */
half getAttenuation(half radius) {
	#ifdef SHOW_LIGHTS
		half attenuation = 1.0f;
	#else
		half attenuation = saturate(radius);
		attenuation *= attenuation;
		#ifdef USE_SRGB
			attenuation *= attenuation;
		#endif
	#endif
	return attenuation;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

/*
 */
##pragma warning(disable : 3205 3571 4000)

/* shader common parameters
 */
cbuffer shader_common_parameters {
	float4 s_viewport;
	float4 s_depth_range;
	float4 s_solid_color;
	float4 s_ambient_color;
	float4x4 s_projection;
	float4x4 s_modelview;
};

/* shader render parameters
 */
cbuffer shader_render_parameters {
	float4x4 s_modelviewprojection;
	float3 s_camera_position;
	float3 s_camera_direction;
	float3 s_camera_offset;
};

/* shader transform parameters
 */
cbuffer shader_transform_parameter {
	float4 s_transform[3];
};

/* shader light parameters
 */
cbuffer shader_light_parameters {
	float3 s_light_position;
	float3 s_light_direction;
	float4 s_light_color;
	float4 s_light_iradius;
	float4x4 s_light_transform;
	float4x4 s_light_projection;
	float3 s_light_shadow_offset;
	float4 s_light_shadow_iradius;
	float3 s_light_shadow_depth_bias;
	float2 s_light_shadow_depth_range;
	float4x4 s_light_shadow_projection;
};

/* shader light prob parameters
 */
cbuffer shader_light_prob_parameters {
	float4 s_light_coefficients[9];
};

/* shader light spot parameters
 */
cbuffer shader_light_spot_parameters {
	float4 s_light_positions[4];
	float4 s_light_colors[4];
	float4 s_light_iradiuses;
	float4 s_light_attenuations;
};

/* shader light world offset parameters
 */
cbuffer shader_light_world_offset_parameters {
	float4 s_light_shadow_offsets[4];
};

/* shader light world projection parameters
 */
cbuffer shader_light_world_projection_parameters {
	float4x4 s_light_shadow_projections[4];
};

/* shader light front parameters
 */
cbuffer shader_light_front_parameters {
	float s_light_front;
};

/* shader material parameters
 */
cbuffer shader_material_parameters {
	float3 s_material_detail;
	float3 s_material_fresnel;
};

/* shader material textures parameters
 */
cbuffer shader_material_textures_parameters {
	float4 s_material_textures[16];
};

/* shader material tessellation parameters
 */
cbuffer shader_material_tessellation_parameters {
	float4 s_material_tessellation_factor;
	float3 s_material_tessellation_distance;
}

/* shader material animation parameters
 */
cbuffer shader_material_animation_parameters {
	float4 s_material_animation_stem;
	float3 s_material_animation_leaf;
}

/* shader material ambient parameters
 */
cbuffer shader_material_ambient_parameters {
	float4x4 s_material_reflection_transform;
	float3 s_material_reflection_center;
	float3 s_material_reflection_color;
	float s_material_reflection_radius;
};

/* shader material light parameters
 */
cbuffer shader_material_light_parameters {
	float3 s_material_shading;
	float2 s_material_phong_rim;
	float4 s_material_anisotropy;
};

/* shader material light spot parameters
 */
cbuffer shader_material_light_spot_parameters {
	float4 s_material_shadings[4];
};

/* shader surface parameters
 */
cbuffer shader_surface_parameters {
	float4 s_surface_distances;
	float4 s_surface_bound_sphere;
}

/* light omni radius
 */
float3 getOmniRadius(float3 radius) {
	half3 x = s_light_transform._m00_m10_m20;
	half3 y = s_light_transform._m01_m11_m21;
	half3 z = s_light_transform._m02_m12_m22;
	return float3(x * (dot(x,radius) * s_light_iradius.x) + y * (dot(y,radius) * s_light_iradius.y) + z * (dot(z,radius) * s_light_iradius.z));
}

/* light attenuation
 */
half getAttenuation(half radius) {
	#ifdef SHOW_LIGHTS
		half attenuation = 1.0f;
	#else
		half attenuation = saturate(radius);
		attenuation *= attenuation;
		#ifdef USE_SRGB
			attenuation *= attenuation;
		#endif
	#endif
	return attenuation;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

/* shader parameters
 */
uniform float4 s_viewport;
uniform float4 s_depth_range;
uniform half4 s_solid_color;
uniform half4 s_ambient_color;
uniform float4x4 s_projection;
uniform float4x4 s_modelview;
uniform float4x4 s_modelviewprojection;
uniform float3 s_camera_position;
uniform float3 s_camera_direction;
uniform float3 s_camera_offset;

/* shader transform parameters
 */
uniform float4 s_transform[3];

/* shader light parameters
 */
uniform float3 s_light_position;
uniform float4 s_light_positions[4];
uniform float3 s_light_direction;
uniform half4 s_light_color;
uniform half4 s_light_colors[4];
uniform float4 s_light_iradius;
uniform float4 s_light_iradiuses;
uniform float4 s_light_attenuations;
uniform float4x4 s_light_transform;
uniform float4x4 s_light_projection;
uniform half4 s_light_coefficients[9];
uniform float3 s_light_shadow_offset;
uniform float4 s_light_shadow_offsets[4];
uniform half4 s_light_shadow_iradius;
uniform half3 s_light_shadow_depth_bias;
uniform half2 s_light_shadow_depth_range;
uniform float4x4 s_light_shadow_projection;
uniform float4x4 s_light_shadow_projections[4];

/* shader light front parameters
 */
uniform half s_light_front;

/* shader material parameters
 */
uniform half3 s_material_detail;
uniform half3 s_material_fresnel;
uniform float4 s_material_textures[16];

/* shader material tessellation parameters
 */
uniform half4 s_material_tessellation_factor;
uniform half3 s_material_tessellation_distance;

/* shader material animation parameters
 */
uniform float4 s_material_animation_stem;
uniform float3 s_material_animation_leaf;

/* shader material ambient parameters
 */
uniform float4x4 s_material_reflection_transform;
uniform float3 s_material_reflection_center;
uniform float s_material_reflection_radius;
uniform half3 s_material_reflection_color;

/* shader material light parameters
 */
uniform half3 s_material_shading;
uniform half4 s_material_shadings[4];
uniform half2 s_material_phong_rim;
uniform half4 s_material_anisotropy;

/* shader surface parameters
 */
uniform float4 s_surface_distances;
uniform float4 s_surface_bound_sphere;

/* light omni radius
 */
float3 getOmniRadius(float3 radius) {
	half3 x = s_light_transform[0].xyz;
	half3 y = s_light_transform[1].xyz;
	half3 z = s_light_transform[2].xyz;
	return float3(x * (dot(x,radius) * s_light_iradius.x) + y * (dot(y,radius) * s_light_iradius.y) + z * (dot(z,radius) * s_light_iradius.z));
}

/* light attenuation
 */
half getAttenuation(half radius) {
	#ifdef SHOW_LIGHTS
		half attenuation = 1.0f;
	#else
		half attenuation = saturate(radius);
		attenuation *= attenuation;
		#ifdef USE_SRGB
			attenuation *= attenuation;
		#endif
	#endif
	return attenuation;
}

#endif

#endif /* __COMMON_BASE_H__ */
