/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_reflection_2d_ambient.shader
 * Desc:    Mesh base reflection 2d ambient shader
 * Version: 1.28
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
 * s_texture_2 is specular texture
 * s_texture_3 is detail diffuse texture
 * s_texture_4 is detail normal texture
 * s_texture_5 is detail specular texture
 * s_texture_6 is reflection 2d texture
 * 
 * s_texture_9 is alpha fade texture
 * s_texture_10 is deferred parallax texture
 * s_texture_11 is emission texture
 * s_texture_12 is environment texture
 * s_texture_13 is ambient texture
 * s_texture_14 is lightmap texture
 * s_texture_15 is deferred light texture
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
uniform sampler2D s_texture_3;
uniform sampler2D s_texture_4;
uniform sampler2D s_texture_5;
uniform sampler2D s_texture_6;

uniform sampler2D s_texture_9;
uniform SAMPLER_2DMS s_texture_10;
uniform sampler2D s_texture_11;
uniform samplerCube s_texture_12;
uniform sampler2D s_texture_13;
uniform sampler2D s_texture_14;
uniform sampler2D s_texture_15;

uniform half4 detail_transform;
uniform half emission_scale;
uniform half environment_scale;
uniform half lightmap_scale;
uniform half4 color_scale;

uniform half reflection_normal;

/*
 */
void main() {
	
	#include <core/shaders/meshes/fragment_base_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif LIGHTMAP
		half3 lightmap = texture2DCubic(s_texture_14,texcoord.zw,s_material_textures[14]).xyz;
		half3 color = diffuse.xyz * (s_ambient_color.xyz + lightmap * lightmap_scale);
	#endif
	
	#ifdef EMISSION
		half3 emission = texture2D(s_texture_11,texcoord.xy).xyz;
		color += emission * emission_scale;
	#endif
	
	half3 world_normal;
	#ifdef USE_TESSELLATION && TESSELLATION
		half3 vertex_normal = normalize(half3(gl_TexCoord[1].xyz));
		half3 vertex_tangent = normalize(half3(gl_TexCoord[2].xyz));
		half3 vertex_binormal = normalize(cross(vertex_normal,vertex_tangent) * half(gl_TexCoord[2].w));
		world_normal = vertex_tangent * normal.x + vertex_binormal * normal.y + vertex_normal * normal.z;
	#else
		world_normal.x = dot(half3(gl_TexCoord[1].xyz),normal);
		world_normal.y = dot(half3(gl_TexCoord[2].xyz),normal);
		world_normal.z = dot(half3(gl_TexCoord[3].xyz),normal);
	#endif
	half3 environment = textureCube(s_texture_12,world_normal).xyz;
	half ambient = texture2DCubic(s_texture_13,texcoord.zw,s_material_textures[13]).x;
	color += diffuse.xyz * environment * (ambient * environment_scale);
	
	#ifdef USE_DEFERRED
		#ifdef USE_TESSELLATION && TESSELLATION
			half4 light = texture2D(s_texture_15,gl_FragCoord.xy * s_viewport.zw);
		#else
			half4 light = texture2DProj(s_texture_15,gl_TexCoord[7]);
		#endif
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,specular.xyz,light);
	#endif
	
	color *= color_scale.xyz;
	diffuse.w *= color_scale.w;
	
	#ifdef USE_REFLECTION
		#ifdef USE_TESSELLATION && TESSELLATION
			float4 reflection_texcoord;
			float4 position = getPosition(float4(gl_TexCoord[3].xyz,1.0f));
			#ifdef REFLECTION_DYNAMIC
				reflection_texcoord = s_material_reflection_transform * float4(gl_TexCoord[3].xyz,1.0f);
			#else
				reflection_texcoord = (position * float4(1.0f,-1.0f,1.0f,1.0f) + position.w) * 0.5f;
			#endif
			half fresnel = getFresnelNormalize(world_normal,half3(s_camera_position - gl_TexCoord[3].xyz));
			half2 offset = normal.xy * (reflection_normal * saturate(s_projection[1].y / position.w));
			half3 reflection = texture2D(s_texture_6,reflection_texcoord.xy / reflection_texcoord.w + offset).xyz;
		#else
			half fresnel = getFresnelNormalize(normal,half3(gl_TexCoord[4].xyz));
			half2 offset = normal.xy * (reflection_normal * saturate(gl_TexCoord[6].x / gl_TexCoord[6].y));
			half3 reflection = texture2D(s_texture_6,gl_TexCoord[5].xy / gl_TexCoord[5].w + offset).xyz;
		#endif
		color += s_material_reflection_color * reflection * specular.xyz * fresnel;
	#endif
	
	gl_FragColor = half4(color,diffuse.w);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	float4 texcoord_5 : TEXCOORD5;
	float2 texcoord_6 : TEXCOORD6;
	#ifdef USE_DEFERRED || (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half4 detail_transform;
half emission_scale;
half environment_scale;
half lightmap_scale;
half4 color_scale;

half reflection_normal;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_base_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif LIGHTMAP
		half3 lightmap = tex2DCubic(s_texture_14,texcoord.zw,s_material_textures[14]).xyz;
		half3 color = diffuse.xyz * (s_ambient_color.xyz + lightmap * lightmap_scale);
	#endif
	
	#ifdef EMISSION
		half3 emission = tex2D(s_texture_11,texcoord.xy).xyz;
		color += emission * emission_scale;
	#endif
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_1,normal);
	world_normal.y = dot(IN.texcoord_2,normal);
	world_normal.z = dot(IN.texcoord_3,normal);
	half3 environment = texCUBE(s_texture_12,world_normal).xyz;
	half ambient = tex2DCubic(s_texture_13,texcoord.zw,s_material_textures[13]).x;
	color += diffuse.xyz * environment * (ambient * environment_scale);
	
	#ifdef USE_DEFERRED
		half4 light = tex2Dproj(s_texture_15,IN.texcoord_7);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,specular.xyz,light);
	#endif
	
	color *= color_scale.xyz;
	diffuse.w *= color_scale.w;
	
	#ifdef USE_REFLECTION
		half fresnel = getFresnelNormalize(normal,IN.texcoord_4);
		half2 offset = normal.xy * (reflection_normal * saturate(IN.texcoord_6.x / IN.texcoord_6.y));
		half3 reflection = tex2D(s_texture_6,IN.texcoord_5.xy / IN.texcoord_5.w + offset).xyz;
		color += s_material_reflection_color * reflection * specular.xyz * fresnel;
	#endif
	
	return half4(color,diffuse.w);
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
Texture2D s_texture_3 : register(t3);
Texture2D s_texture_4 : register(t4);
Texture2D s_texture_5 : register(t5);
Texture2D s_texture_6 : register(t6);

Texture2D s_texture_9 : register(t9);
TEXTURE_2DMS s_texture_10 : register(t10);
Texture2D s_texture_11 : register(t11);
TextureCube s_texture_12 : register(t12);
Texture2D s_texture_13 : register(t13);
Texture2D s_texture_14 : register(t14);
Texture2D s_texture_15 : register(t15);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
	#ifdef USE_TESSELLATION && TESSELLATION
		float3 texcoord_1 : TEXCOORD1;
		float4 texcoord_2 : TEXCOORD2;
		float3 texcoord_3 : TEXCOORD3;
	#else
		float3 texcoord_1 : TEXCOORD1;
		float3 texcoord_2 : TEXCOORD2;
		float3 texcoord_3 : TEXCOORD3;
		float3 texcoord_4 : TEXCOORD4;
		float4 texcoord_5 : TEXCOORD5;
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
	#endif
	float environment_scale;
	#ifdef LIGHTMAP
		float lightmap_scale;
	#endif
	float4 color_scale;
	float reflection_normal;
};

/*
 */
FRAGMENT_ALPHA_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_ALPHA_OUT OUT;
	
	#include <core/shaders/meshes/fragment_base_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif LIGHTMAP
		half3 lightmap = texture2DCubic(s_texture_14,s_sampler_14,texcoord.zw,s_material_textures[14]).xyz;
		half3 color = diffuse.xyz * (s_ambient_color.xyz + lightmap * lightmap_scale);
	#endif
	
	#ifdef EMISSION
		half3 emission = s_texture_11.Sample(s_sampler_11,texcoord.xy).xyz;
		color += emission * emission_scale;
	#endif
	
	half3 world_normal;
	#ifdef USE_TESSELLATION && TESSELLATION
		half3 vertex_normal = normalize(IN.texcoord_1);
		half3 vertex_tangent = normalize(IN.texcoord_2.xyz);
		half3 vertex_binormal = normalize(cross(vertex_normal,vertex_tangent) * IN.texcoord_2.w);
		world_normal = vertex_tangent * normal.x + vertex_binormal * normal.y + vertex_normal * normal.z;
	#else
		world_normal.x = dot(IN.texcoord_1,normal);
		world_normal.y = dot(IN.texcoord_2,normal);
		world_normal.z = dot(IN.texcoord_3,normal);
	#endif
	half3 environment = s_texture_12.Sample(s_sampler_12,world_normal).xyz;
	half ambient = texture2DCubic(s_texture_13,s_sampler_13,texcoord.zw,s_material_textures[13]).x;
	color += diffuse.xyz * environment * (ambient * environment_scale);
	
	#ifdef USE_DEFERRED
		half4 light = s_texture_15.Sample(s_sampler_15,IN.position.xy * s_viewport.zw);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,specular.xyz,light);
	#endif
	
	color *= color_scale.xyz;
	diffuse.w *= color_scale.w;
	
	#ifdef USE_REFLECTION
		#ifdef USE_TESSELLATION && TESSELLATION
			float4 reflection_texcoord;
			float4 position = getPosition(float4(IN.texcoord_3,1.0f));
			#ifdef REFLECTION_DYNAMIC
				reflection_texcoord = mul(s_material_reflection_transform,float4(IN.texcoord_3,1.0f));
			#else
				reflection_texcoord = (position * float4(1.0f,-1.0f,1.0f,1.0f) + position.w) * 0.5f;
			#endif
			half fresnel = getFresnelNormalize(world_normal,half3(s_camera_position - IN.texcoord_3));
			half2 offset = normal.xy * (reflection_normal * saturate(s_projection[1].y / position.w));
			half3 reflection = s_texture_6.Sample(s_sampler_12,reflection_texcoord.xy / reflection_texcoord.w + offset).xyz;
		#else
			half fresnel = getFresnelNormalize(normal,IN.texcoord_4);
			half2 offset = normal.xy * (reflection_normal * saturate(IN.texcoord_6.x / IN.texcoord_6.y));
			half3 reflection = s_texture_6.Sample(s_sampler_12,IN.texcoord_5.xy / IN.texcoord_5.w + offset).xyz;
		#endif
		color += s_material_reflection_color * reflection * specular.xyz * fresnel;
	#endif
	
	OUT.color = float4(color,diffuse.w);
	
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
uniform sampler2D s_texture_2 : TEXUNIT2;
uniform sampler2D s_texture_3 : TEXUNIT3;
uniform sampler2D s_texture_4 : TEXUNIT4;
uniform sampler2D s_texture_5 : TEXUNIT5;
uniform sampler2D s_texture_6 : TEXUNIT6;

uniform sampler2D s_texture_9 : TEXUNIT9;
uniform sampler2D s_texture_10 : TEXUNIT10;
uniform sampler2D s_texture_11 : TEXUNIT11;
uniform samplerCUBE s_texture_12 : TEXUNIT12;
uniform sampler2D s_texture_13 : TEXUNIT13;
uniform sampler2D s_texture_14 : TEXUNIT14;
uniform sampler2D s_texture_15 : TEXUNIT15;

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
	half3 texcoord_1 : TEXCOORD1;
	half3 texcoord_2 : TEXCOORD2;
	half3 texcoord_3 : TEXCOORD3;
	half3 texcoord_4 : TEXCOORD4;
	float4 texcoord_5 : TEXCOORD5;
	float2 texcoord_6 : TEXCOORD6;
	#ifdef USE_DEFERRED || (USE_PARALLAX && PARALLAX) || (USE_ALPHA_FADE && ALPHA_FADE)
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half4 detail_transform;
uniform half emission_scale;
uniform half environment_scale;
uniform half lightmap_scale;
uniform half4 color_scale;

uniform half reflection_normal;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#include <core/shaders/meshes/fragment_base_sample.h>
	
	#ifdef OPACITY
		half3 color = diffuse.xyz * s_ambient_color.xyz;
	#elif LIGHTMAP
		half3 lightmap = h3tex2D(s_texture_14,texcoord.zw);
		half3 color = diffuse.xyz * (s_ambient_color.xyz + lightmap * lightmap_scale);
	#endif
	
	#ifdef EMISSION
		half3 emission = h3tex2D(s_texture_11,texcoord.xy);
		color += emission * emission_scale;
	#endif
	
	half3 world_normal;
	world_normal.x = dot(IN.texcoord_1,normal);
	world_normal.y = dot(IN.texcoord_2,normal);
	world_normal.z = dot(IN.texcoord_3,normal);
	half3 environment = h3texCUBE(s_texture_12,world_normal);
	half ambient = h1tex2D(s_texture_13,texcoord.zw);
	color += diffuse.xyz * environment * (ambient * environment_scale);
	
	#ifdef USE_DEFERRED
		half4 light = h4tex2Dproj(s_texture_15,IN.texcoord_9.xyw);
		color += getDiffuseSpecularDeferredAmbient(diffuse.xyz,specular.xyz,light);
	#endif
	
	color *= color_scale.xyz;
	diffuse.w *= color_scale.w;
	
	#ifdef USE_REFLECTION
		half fresnel = getFresnelNormalize(normal,IN.texcoord_4);
		half2 offset = normal.xy * (reflection_normal * saturate(IN.texcoord_6.x / IN.texcoord_6.y));
		half3 reflection = h3tex2D(s_texture_6,IN.texcoord_5.xy / IN.texcoord_5.w + offset);
		color += s_material_reflection_color * reflection * specular.xyz * fresnel;
	#endif
	
	return half4(color,diffuse.w);
}

#endif
