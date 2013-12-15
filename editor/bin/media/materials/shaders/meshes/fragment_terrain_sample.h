/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_terrain_sample.h
 * Desc:    Mesh terrain sample shader
 * Version: 1.02
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

#ifdef DETAIL_2
	#define DETAIL_1
#endif
#ifdef DETAIL_3
	#define DETAIL_1
	#define DETAIL_2
#endif
#ifdef DETAIL_4
	#define DETAIL_1
	#define DETAIL_2
	#define DETAIL_3
#endif

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL
	
	half4 diffuse = texture2D(s_texture_0,gl_TexCoord[0].xy);
	half3 normal = texture2DNormal(s_texture_1,gl_TexCoord[0].xy);
	
	#ifdef DETAIL_1
		
		half4 mask = texture2D(s_texture_2,gl_TexCoord[0].xy);
		
		#define DETAIL(DIFFUSE,NORMAL,NUM,SWIZZLE) { \
			float2 texcoord = gl_TexCoord[0].xy * NUM ## _transform.xy + NUM ## _transform.zw; \
			half4 detail_diffuse = texture2D(s_texture_ ## DIFFUSE,texcoord); \
			half3 detail_normal = texture2DNormal(s_texture_ ## NORMAL,texcoord); \
			diffuse = saturate(diffuse + (detail_diffuse * 2.0f - 1.0f) * (NUM ## _diffuse * mask. SWIZZLE)); \
			normal = normal + detail_normal * (NUM ## _normal * mask. SWIZZLE); \
		}
		
		DETAIL(3,4,detail_1,x);
		#ifdef DETAIL_2
			DETAIL(5,6,detail_2,y);
		#endif
		#ifdef DETAIL_3
			DETAIL(7,8,detail_3,z);
		#endif
		#ifdef DETAIL_4
			DETAIL(9,10,detail_4,w);
		#endif
		
		#undef DETAIL
		
		normal = normalize(normal);
		
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
	#endif
	
	half3 specular = diffuse.xyz * diffuse.w;
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	half4 diffuse = tex2D(s_texture_0,IN.texcoord_0.xy);
	half3 normal = tex2DNormal(s_texture_1,IN.texcoord_0.xy);
	
	#ifdef DETAIL_1
		
		half4 mask = tex2D(s_texture_2,IN.texcoord_0.xy);
		
		#define DETAIL(DIFFUSE,NORMAL,NUM,SWIZZLE) { \
			float2 texcoord = IN.texcoord_0.xy * NUM ## _transform.xy + NUM ## _transform.zw; \
			half4 detail_diffuse = tex2D(s_texture_ ## DIFFUSE,texcoord); \
			half3 detail_normal = tex2DNormal(s_texture_ ## NORMAL,texcoord); \
			diffuse = saturate(diffuse + (detail_diffuse * 2.0f - 1.0f) * (NUM ## _diffuse * mask. SWIZZLE)); \
			normal = normal + detail_normal * (NUM ## _normal * mask. SWIZZLE); \
		}
		
		DETAIL(3,4,detail_1,x);
		#ifdef DETAIL_2
			DETAIL(5,6,detail_2,y);
		#endif
		#ifdef DETAIL_3
			DETAIL(7,8,detail_3,z);
		#endif
		#ifdef DETAIL_4
			DETAIL(9,10,detail_4,w);
		#endif
		
		#undef DETAIL
		
		normal = normalize(normal);
		
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
	#endif
	
	half3 specular = diffuse.xyz * diffuse.w;
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	half4 diffuse = s_texture_0.Sample(s_sampler_0,IN.texcoord_0.xy);
	half3 normal = texture2DNormal(s_texture_1,s_sampler_1,IN.texcoord_0.xy);
	
	#ifdef DETAIL_1
		
		half4 mask = s_texture_2.Sample(s_sampler_2,IN.texcoord_0.xy);
		
		#define DETAIL(DIFFUSE,NORMAL,NUM,SWIZZLE) { \
			float2 texcoord = IN.texcoord_0.xy * NUM ## _transform.xy + NUM ## _transform.zw; \
			half4 detail_diffuse = s_texture_ ## DIFFUSE .Sample(s_sampler_ ## DIFFUSE,texcoord); \
			half3 detail_normal = texture2DNormal(s_texture_ ## NORMAL,s_sampler_ ## NORMAL,texcoord); \
			diffuse = saturate(diffuse + (detail_diffuse * 2.0f - 1.0f) * (NUM ## _diffuse * mask. SWIZZLE)); \
			normal = normal + detail_normal * (NUM ## _normal * mask. SWIZZLE); \
		}
		
		DETAIL(3,4,detail_1,x);
		#ifdef DETAIL_2
			DETAIL(5,6,detail_2,y);
		#endif
		#ifdef DETAIL_3
			DETAIL(7,8,detail_3,z);
		#endif
		#ifdef DETAIL_4
			DETAIL(9,10,detail_4,w);
		#endif
		
		#undef DETAIL
		
		normal = normalize(normal);
		
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
	#endif
	
	half3 specular = diffuse.xyz * diffuse.w;
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	half4 diffuse = h4tex2D(s_texture_0,IN.texcoord_0.xy);
	half3 normal = tex2DNormal(s_texture_1,IN.texcoord_0.xy);
	
	#ifdef DETAIL_1
		
		half4 mask = h4tex2D(s_texture_2,IN.texcoord_0.xy);
		
		#define DETAIL(DIFFUSE,NORMAL,NUM,SWIZZLE) { \
			float2 texcoord = IN.texcoord_0.xy * NUM ## _transform.xy + NUM ## _transform.zw; \
			half4 detail_diffuse = h4tex2D(s_texture_ ## DIFFUSE,texcoord); \
			half3 detail_normal = tex2DNormal(s_texture_ ## NORMAL,texcoord); \
			diffuse = saturate(diffuse + (detail_diffuse * 2.0f - 1.0f) * (NUM ## _diffuse * mask. SWIZZLE)); \
			normal = normal + detail_normal * (NUM ## _normal * mask. SWIZZLE); \
		}
		
		DETAIL(3,4,detail_1,x);
		#ifdef DETAIL_2
			DETAIL(5,6,detail_2,y);
		#endif
		#ifdef DETAIL_3
			DETAIL(7,8,detail_3,z);
		#endif
		#ifdef DETAIL_4
			DETAIL(9,10,detail_4,w);
		#endif
		
		#undef DETAIL
		
		normal = normalize(normal);
		
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
	#endif
	
	half3 specular = diffuse.xyz * diffuse.w;
	
#endif
