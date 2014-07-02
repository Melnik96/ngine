/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_shadow.shader
 * Desc:    Mesh base shadow map shader
 * Version: 1.24
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
 * 
 * s_texture_9 is alpha fade texture
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

uniform sampler2D s_texture_9;

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
	
	#ifdef TRANSLUCENT
		
		half4 diffuse = texture2D(s_texture_0,gl_TexCoord[0].xy);
		#ifdef ALPHA
			if(diffuse.w <= 0.5f) discard;
		#endif
		
		half3 normal = texture2DNormal(s_texture_1,gl_TexCoord[0].xy);
		
		#ifdef USE_TESSELLATION && TESSELLATION
			
			half3 vertex_normal = normalize(half3(gl_TexCoord[1].xyz));
			half3 vertex_tangent = normalize(half3(gl_TexCoord[2].xyz));
			half3 vertex_binormal = normalize(cross(vertex_normal,vertex_tangent) * half(gl_TexCoord[2].w));
			half3 world_normal = vertex_tangent * normal.x + vertex_binormal * normal.y + vertex_normal * (normal.z * s_light_front);
			
			half3 light_direction = normalize(half3(s_light_position - gl_TexCoord[3].xyz));
			
			half3 color = diffuse.xyz * saturate(dot(light_direction,world_normal));
			
			half distance = length(-half3(s_light_shadow_offset - gl_TexCoord[3].xyz) * s_light_shadow_iradius.x);
			
		#else
			
			half3 light_direction = normalize(half3(gl_TexCoord[1].xyz));
			
			half3 color = diffuse.xyz * saturate(dot(light_direction,normal));
			
			half distance = length(half3(gl_TexCoord[2].xyz));
			
		#endif
		
		distance += s_light_shadow_depth_bias.z;
		
		gl_FragColor = half4(color * color_scale.xyz,distance);
		
	#else
		
		#ifdef ALPHA
			half4 diffuse = texture2D(s_texture_0,gl_TexCoord[0].xy);
			if(diffuse.w <= 0.5f) discard;
		#endif
		
		gl_FragColor = half4(0.0f);
		
	#endif
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	#ifdef ALPHA || TRANSLUCENT
		float2 texcoord_0 : TEXCOORD0;
	#endif
	#ifdef TRANSLUCENT
		half3 texcoord_1 : TEXCOORD1;
		half3 texcoord_2 : TEXCOORD2;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 texcoord_7 : TEXCOORD7;
	#endif
};

half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_9,IN.texcoord_7,IN.texcoord_7.z);
	#endif
	
	#ifdef TRANSLUCENT
		
		half4 diffuse = tex2D(s_texture_0,IN.texcoord_0);
		#ifdef ALPHA
			if(diffuse.w <= 0.5f) discard;
		#endif
		
		half3 normal = tex2DNormal(s_texture_1,IN.texcoord_0);
		
		half3 light_direction = normalize(IN.texcoord_1);
		
		half3 color = diffuse.xyz * saturate(dot(light_direction,normal));
		
		half distance = length(IN.texcoord_2) + s_light_shadow_depth_bias.z;
		
		return half4(color * color_scale.xyz,distance);
		
	#else
		
		#ifdef ALPHA
			half4 diffuse = tex2D(s_texture_0,IN.texcoord_0);
			if(diffuse.w <= 0.5f) discard;
		#endif
		
		return 0.0f;
		
	#endif
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
Texture2D s_texture_1 : register(t1);

Texture2D s_texture_9 : register(t9);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	#ifdef ALPHA || TRANSLUCENT
		float2 texcoord_0 : TEXCOORD0;
	#endif
	#ifdef USE_TESSELLATION && TESSELLATION
		#ifdef TRANSLUCENT
			float3 texcoord_1 : TEXCOORD1;
			float4 texcoord_2 : TEXCOORD2;
			float3 texcoord_3 : TEXCOORD3;
		#endif
	#else
		#ifdef TRANSLUCENT
			float3 texcoord_1 : TEXCOORD1;
			float3 texcoord_2 : TEXCOORD2;
		#endif
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float1 texcoord_9 : TEXCOORD9;
	#endif
};

cbuffer shader_parameters {
	float4 color_scale;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texture2DAlphaFadeDiscard(s_texture_9,s_sampler_9,IN.position.xy,IN.texcoord_9.x);
	#endif
	
	#ifdef TRANSLUCENT
		
		half4 diffuse = s_texture_0.Sample(s_sampler_0,IN.texcoord_0);
		#ifdef ALPHA
			if(diffuse.w <= 0.5f) discard;
		#endif
		
		half3 normal = texture2DNormal(s_texture_1,s_sampler_1,IN.texcoord_0);
		
		#ifdef USE_TESSELLATION && TESSELLATION
			
			half3 vertex_normal = normalize(IN.texcoord_1);
			half3 vertex_tangent = normalize(IN.texcoord_2.xyz);
			half3 vertex_binormal = normalize(cross(vertex_normal,vertex_tangent) * IN.texcoord_2.w);
			half3 world_normal = vertex_tangent * normal.x + vertex_binormal * normal.y + vertex_normal * normal.z;
			
			half3 light_direction = normalize(s_light_position - IN.texcoord_3);
			
			half3 color = diffuse.xyz * saturate(dot(light_direction,world_normal));
			
			half distance = length(-(s_light_shadow_offset - IN.texcoord_3) * s_light_shadow_iradius.x);
			
		#else
			
			half3 light_direction = normalize(IN.texcoord_1);
			
			half3 color = diffuse.xyz * saturate(dot(light_direction,normal));
			
			half distance = length(IN.texcoord_2);
			
		#endif
		
		distance += s_light_shadow_depth_bias.z;
		
		return float4(color * color_scale.xyz,distance);
		
	#else
		
		#ifdef ALPHA
			half4 diffuse = s_texture_0.Sample(s_sampler_0,IN.texcoord_0);
			if(diffuse.w <= 0.5f) discard;
		#endif
		
		return 0.0f;
		
	#endif
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform sampler2D s_texture_0 : TEXUNIT0;
uniform sampler2D s_texture_1 : TEXUNIT1;

uniform sampler2D s_texture_9 : TEXUNIT9;

struct FRAGMENT_IN {
	float2 position : WPOS;
	#ifdef ALPHA || TRANSLUCENT
		float2 texcoord_0 : TEXCOORD0;
	#endif
	#ifdef TRANSLUCENT
		half3 texcoord_1 : TEXCOORD1;
		half3 texcoord_2 : TEXCOORD2;
	#endif
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		float4 texcoord_9 : TEXCOORD9;
	#endif
};

uniform half4 color_scale;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_9,IN.texcoord_9,IN.texcoord_9.z);
	#endif
	
	#ifdef TRANSLUCENT
		
		half4 diffuse = h4tex2D(s_texture_0,IN.texcoord_0);
		#ifdef ALPHA
			if(diffuse.w <= 0.5f) discard;
		#endif
		
		half3 normal = tex2DNormal(s_texture_1,IN.texcoord_0);
		
		half3 light_direction = normalize(IN.texcoord_1);
		
		half3 color = diffuse.xyz * saturate(dot(light_direction,normal));
		
		half distance = length(IN.texcoord_2) + s_light_shadow_depth_bias.z;
		
		return half4(color * color_scale.xyz,distance);
		
	#else
		
		#ifdef ALPHA
			half4 diffuse = h4tex2D(s_texture_0,IN.texcoord_0);
			if(diffuse.w <= 0.5f) discard;
		#endif
		
		return 0.0f;
		
	#endif
}

#endif
