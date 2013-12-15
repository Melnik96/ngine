/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_sample.h
 * Desc:    Terrain base sample shader
 * Version: 1.12
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
	
	#ifdef PATCH
		
		half4 diffuse = texture2D(s_texture_0,lerp(gl_TexCoord[0].xy,gl_TexCoord[0].zw,s_terrain_diffuse_texcoord));
		half3 normal = texture2DNormal(s_texture_1,lerp(gl_TexCoord[0].xy,gl_TexCoord[0].zw,s_terrain_normal_texcoord));
		
		#ifdef DETAIL_1
			
			half3 binormal = normalize(cross(half3(-1.0f,0.0f,0.0f),normal));
			half3 tangent = normalize(cross(binormal,normal));
			half3x3 basis = half3x3(tangent,binormal,normal);
			
			half4 mask = texture2D(s_texture_2,gl_TexCoord[0].xy) * gl_TexCoord[6].x;
			half4 diffuse_scale = s_terrain_diffuse_scale * mask;
			half4 normal_scale = s_terrain_normal_scale * mask;
			
			#ifdef TRIPLANAR
				
				half3 scale = normal * normal;
				half4 diffuse_scale_xy = diffuse_scale * scale.z;
				half4 diffuse_scale_xz = diffuse_scale * scale.y;
				half4 diffuse_scale_yz = diffuse_scale * scale.x;
				half4 normal_scale_xy = normal_scale * scale.z;
				half4 normal_scale_xz = normal_scale * scale.y;
				half4 normal_scale_yz = normal_scale * scale.x;
				
				#define DETAIL(DIFFUSE,NORMAL,NUM,SWIZZLE) { \
					float2 texcoord_xy = gl_TexCoord[0].xy * s_terrain_transform_ ## NUM.xy + s_terrain_transform_ ## NUM.zw; \
					float2 texcoord_xz = float2(texcoord_xy.x,gl_TexCoord[6].y * s_terrain_transform_ ## NUM.x); \
					float2 texcoord_yz = float2(texcoord_xy.y,texcoord_xz.y); \
					half4 detail_diffuse_xy = texture2D(s_texture_ ## DIFFUSE,texcoord_xy); \
					half4 detail_diffuse_xz = texture2D(s_texture_ ## DIFFUSE,texcoord_xz); \
					half4 detail_diffuse_yz = texture2D(s_texture_ ## DIFFUSE,texcoord_yz); \
					half3 detail_normal_xy = basis * texture2DNormal(s_texture_ ## NORMAL,texcoord_xy); \
					half3 detail_normal_xz = basis * texture2DNormal(s_texture_ ## NORMAL,texcoord_xz); \
					half3 detail_normal_yz = basis * texture2DNormal(s_texture_ ## NORMAL,texcoord_yz); \
					diffuse = saturate(diffuse + (detail_diffuse_xy * 2.0f - 1.0f) * diffuse_scale_xy. ## SWIZZLE); \
					diffuse = saturate(diffuse + (detail_diffuse_xz * 2.0f - 1.0f) * diffuse_scale_xz. ## SWIZZLE); \
					diffuse = saturate(diffuse + (detail_diffuse_yz * 2.0f - 1.0f) * diffuse_scale_yz. ## SWIZZLE); \
					normal = normal + detail_normal_xy * normal_scale_xy. ## SWIZZLE; \
					normal = normal + detail_normal_xz * normal_scale_xz. ## SWIZZLE; \
					normal = normal + detail_normal_yz * normal_scale_yz. ## SWIZZLE; \
				}
				
			#else
				
				#define DETAIL(DIFFUSE,NORMAL,NUM,SWIZZLE) { \
					float2 texcoord = gl_TexCoord[0].xy * s_terrain_transform_ ## NUM.xy + s_terrain_transform_ ## NUM.zw; \
					half4 detail_diffuse = texture2D(s_texture_ ## DIFFUSE,texcoord); \
					half3 detail_normal = basis * texture2DNormal(s_texture_ ## NORMAL,texcoord); \
					diffuse = saturate(diffuse + (detail_diffuse * 2.0f - 1.0f) * diffuse_scale. ## SWIZZLE); \
					normal = normal + detail_normal * normal_scale. ## SWIZZLE; \
				}
				
			#endif
			
			DETAIL(3,4,1,x);
			#ifdef DETAIL_2
				DETAIL(5,6,2,y);
			#endif
			#ifdef DETAIL_3
				DETAIL(7,8,3,z);
			#endif
			#ifdef DETAIL_4
				DETAIL(9,10,4,w);
			#endif
			
			#undef DETAIL
			
			normal = normalize(normal);
			
		#endif
		
	#else
		
		half4 diffuse = texture2D(s_texture_0,gl_TexCoord[0].zw);
		half3 normal = texture2DNormal(s_texture_1,gl_TexCoord[0].zw);
		
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
	
	#ifdef PATCH
		
		half4 diffuse = tex2D(s_texture_0,lerp(IN.texcoord_0.xy,IN.texcoord_0.zw,s_terrain_diffuse_texcoord));
		half3 normal = tex2DNormal(s_texture_1,lerp(IN.texcoord_0.xy,IN.texcoord_0.zw,s_terrain_normal_texcoord));
		
		#ifdef DETAIL_1
			
			half3 binormal = normalize(cross(half3(-1.0f,0.0f,0.0f),normal));
			half3 tangent = normalize(cross(binormal,normal));
			half3x3 basis = half3x3(tangent,binormal,normal);
			
			half4 mask = tex2D(s_texture_2,IN.texcoord_0.xy) * IN.texcoord_6.x;
			half4 diffuse_scale = s_terrain_diffuse_scale * mask;
			half4 normal_scale = s_terrain_normal_scale * mask;
			
			#ifdef TRIPLANAR
				
				half3 scale = normal * normal;
				half4 diffuse_scale_xy = diffuse_scale * scale.z;
				half4 diffuse_scale_xz = diffuse_scale * scale.y;
				half4 diffuse_scale_yz = diffuse_scale * scale.x;
				half4 normal_scale_xy = normal_scale * scale.z;
				half4 normal_scale_xz = normal_scale * scale.y;
				half4 normal_scale_yz = normal_scale * scale.x;
				
				#define DETAIL(DIFFUSE,NORMAL,NUM,SWIZZLE) { \
					float2 texcoord_xy = IN.texcoord_0.xy * s_terrain_transform_ ## NUM.xy + s_terrain_transform_ ## NUM.zw; \
					float2 texcoord_xz = float2(texcoord_xy.x,IN.texcoord_6.y * s_terrain_transform_ ## NUM.x); \
					float2 texcoord_yz = float2(texcoord_xy.y,texcoord_xz.y); \
					half4 detail_diffuse_xy = tex2D(s_texture_ ## DIFFUSE,texcoord_xy); \
					half4 detail_diffuse_xz = tex2D(s_texture_ ## DIFFUSE,texcoord_xz); \
					half4 detail_diffuse_yz = tex2D(s_texture_ ## DIFFUSE,texcoord_yz); \
					half3 detail_normal_xy = mul(tex2DNormal(s_texture_ ## NORMAL,texcoord_xy),basis); \
					half3 detail_normal_xz = mul(tex2DNormal(s_texture_ ## NORMAL,texcoord_xz),basis); \
					half3 detail_normal_yz = mul(tex2DNormal(s_texture_ ## NORMAL,texcoord_yz),basis); \
					diffuse = saturate(diffuse + (detail_diffuse_xy * 2.0f - 1.0f) * diffuse_scale_xy. ## SWIZZLE); \
					diffuse = saturate(diffuse + (detail_diffuse_xz * 2.0f - 1.0f) * diffuse_scale_xz. ## SWIZZLE); \
					diffuse = saturate(diffuse + (detail_diffuse_yz * 2.0f - 1.0f) * diffuse_scale_yz. ## SWIZZLE); \
					normal = normal + detail_normal_xy * normal_scale_xy. ## SWIZZLE; \
					normal = normal + detail_normal_xz * normal_scale_xz. ## SWIZZLE; \
					normal = normal + detail_normal_yz * normal_scale_yz. ## SWIZZLE; \
				}
				
			#else
				
				#define DETAIL(DIFFUSE,NORMAL,NUM,SWIZZLE) { \
					float2 texcoord = IN.texcoord_0.xy * s_terrain_transform_ ## NUM.xy + s_terrain_transform_ ## NUM.zw; \
					half4 detail_diffuse = tex2D(s_texture_ ## DIFFUSE,texcoord); \
					half3 detail_normal = mul(tex2DNormal(s_texture_ ## NORMAL,texcoord),basis); \
					diffuse = saturate(diffuse + (detail_diffuse * 2.0f - 1.0f) * diffuse_scale. ## SWIZZLE); \
					normal = normal + detail_normal * normal_scale. ## SWIZZLE; \
				}
				
			#endif
			
			DETAIL(3,4,1,x);
			#ifdef DETAIL_2
				DETAIL(5,6,2,y);
			#endif
			#ifdef DETAIL_3
				DETAIL(7,8,3,z);
			#endif
			#ifdef DETAIL_4
				DETAIL(9,10,4,w);
			#endif
			
			#undef DETAIL
			
			normal = normalize(normal);
			
		#endif
		
	#else
		
		half4 diffuse = tex2D(s_texture_0,IN.texcoord_0.zw);
		half3 normal = tex2DNormal(s_texture_1,IN.texcoord_0.zw);
		
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
	
	#ifdef PATCH
		
		half4 diffuse = s_texture_0.Sample(s_sampler_0,lerp(IN.texcoord_0.xy,IN.texcoord_0.zw,s_terrain_diffuse_texcoord));
		half3 normal = texture2DNormal(s_texture_1,s_sampler_1,lerp(IN.texcoord_0.xy,IN.texcoord_0.zw,s_terrain_normal_texcoord));
		
		#ifdef DETAIL_1
			
			half3 binormal = normalize(cross(half3(-1.0f,0.0f,0.0f),normal));
			half3 tangent = normalize(cross(binormal,normal));
			half3x3 basis = half3x3(tangent,binormal,normal);
			
			half4 mask = s_texture_2.Sample(s_sampler_2,IN.texcoord_0.xy) * IN.texcoord_6.x;
			half4 diffuse_scale = s_terrain_diffuse_scale * mask;
			half4 normal_scale = s_terrain_normal_scale * mask;
			
			#ifdef TRIPLANAR
				
				half3 scale = normal * normal;
				half4 diffuse_scale_xy = diffuse_scale * scale.z;
				half4 diffuse_scale_xz = diffuse_scale * scale.y;
				half4 diffuse_scale_yz = diffuse_scale * scale.x;
				half4 normal_scale_xy = normal_scale * scale.z;
				half4 normal_scale_xz = normal_scale * scale.y;
				half4 normal_scale_yz = normal_scale * scale.x;
				
				#define DETAIL(DIFFUSE,NORMAL,NUM,SWIZZLE) { \
					float2 texcoord_xy = IN.texcoord_0.xy * s_terrain_transform_ ## NUM.xy + s_terrain_transform_ ## NUM.zw; \
					float2 texcoord_xz = float2(texcoord_xy.x,IN.texcoord_6.y * s_terrain_transform_ ## NUM.x); \
					float2 texcoord_yz = float2(texcoord_xy.y,texcoord_xz.y); \
					half4 detail_diffuse_xy = s_texture_ ## DIFFUSE .Sample(s_sampler_ ## DIFFUSE,texcoord_xy); \
					half4 detail_diffuse_xz = s_texture_ ## DIFFUSE .Sample(s_sampler_ ## DIFFUSE,texcoord_xz); \
					half4 detail_diffuse_yz = s_texture_ ## DIFFUSE .Sample(s_sampler_ ## DIFFUSE,texcoord_yz); \
					half3 detail_normal_xy = mul(texture2DNormal(s_texture_ ## NORMAL,s_sampler_ ## NORMAL,texcoord_xy),basis); \
					half3 detail_normal_xz = mul(texture2DNormal(s_texture_ ## NORMAL,s_sampler_ ## NORMAL,texcoord_xz),basis); \
					half3 detail_normal_yz = mul(texture2DNormal(s_texture_ ## NORMAL,s_sampler_ ## NORMAL,texcoord_yz),basis); \
					diffuse = saturate(diffuse + (detail_diffuse_xy * 2.0f - 1.0f) * diffuse_scale_xy. ## SWIZZLE); \
					diffuse = saturate(diffuse + (detail_diffuse_xz * 2.0f - 1.0f) * diffuse_scale_xz. ## SWIZZLE); \
					diffuse = saturate(diffuse + (detail_diffuse_yz * 2.0f - 1.0f) * diffuse_scale_yz. ## SWIZZLE); \
					normal = normal + detail_normal_xy * normal_scale_xy. ## SWIZZLE; \
					normal = normal + detail_normal_xz * normal_scale_xz. ## SWIZZLE; \
					normal = normal + detail_normal_yz * normal_scale_yz. ## SWIZZLE; \
				}
				
			#else
				
				#define DETAIL(DIFFUSE,NORMAL,NUM,SWIZZLE) { \
					float2 texcoord = IN.texcoord_0.xy * s_terrain_transform_ ## NUM.xy + s_terrain_transform_ ## NUM.zw; \
					half4 detail_diffuse = s_texture_ ## DIFFUSE .Sample(s_sampler_ ## DIFFUSE,texcoord); \
					half3 detail_normal = mul(texture2DNormal(s_texture_ ## NORMAL,s_sampler_ ## NORMAL,texcoord),basis); \
					diffuse = saturate(diffuse + (detail_diffuse * 2.0f - 1.0f) * diffuse_scale. ## SWIZZLE); \
					normal = normal + detail_normal * normal_scale. ## SWIZZLE; \
				}
				
			#endif
			
			DETAIL(3,4,1,x);
			#ifdef DETAIL_2
				DETAIL(5,6,2,y);
			#endif
			#ifdef DETAIL_3
				DETAIL(7,8,3,z);
			#endif
			#ifdef DETAIL_4
				DETAIL(9,10,4,w);
			#endif
			
			#undef DETAIL
			
			normal = normalize(normal);
			
		#endif
		
	#else
		
		half4 diffuse = s_texture_0.Sample(s_sampler_0,IN.texcoord_0.zw);
		half3 normal = texture2DNormal(s_texture_1,s_sampler_1,IN.texcoord_0.zw);
		
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
	
	#ifdef PATCH
		
		half4 diffuse = h4tex2D(s_texture_0,lerp(IN.texcoord_0.xy,IN.texcoord_0.zw,s_terrain_diffuse_texcoord));
		half3 normal = tex2DNormal(s_texture_1,lerp(IN.texcoord_0.xy,IN.texcoord_0.zw,s_terrain_normal_texcoord));
		
		#ifdef DETAIL_1
			
			half3 binormal = normalize(cross(half3(-1.0f,0.0f,0.0f),normal));
			half3 tangent = normalize(cross(binormal,normal));
			half3x3 basis = half3x3(tangent,binormal,normal);
			
			half4 mask = h4tex2D(s_texture_2,IN.texcoord_0.xy) * IN.texcoord_8.x;
			half4 diffuse_scale = s_terrain_diffuse_scale * mask;
			half4 normal_scale = s_terrain_normal_scale * mask;
			
			#ifdef TRIPLANAR
				
				half3 scale = normal * normal;
				half4 diffuse_scale_xy = diffuse_scale * scale.z;
				half4 diffuse_scale_xz = diffuse_scale * scale.y;
				half4 diffuse_scale_yz = diffuse_scale * scale.x;
				half4 normal_scale_xy = normal_scale * scale.z;
				half4 normal_scale_xz = normal_scale * scale.y;
				half4 normal_scale_yz = normal_scale * scale.x;
				
				#define DETAIL(DIFFUSE,NORMAL,NUM,SWIZZLE) { \
					float2 texcoord_xy = IN.texcoord_0.xy * s_terrain_transform_ ## NUM.xy + s_terrain_transform_ ## NUM.zw; \
					float2 texcoord_xz = float2(texcoord_xy.x,IN.texcoord_8.y * s_terrain_transform_ ## NUM.x); \
					float2 texcoord_yz = float2(texcoord_xy.y,texcoord_xz.y); \
					half4 detail_diffuse_xy = h4tex2D(s_texture_ ## DIFFUSE,texcoord_xy); \
					half4 detail_diffuse_xz = h4tex2D(s_texture_ ## DIFFUSE,texcoord_xz); \
					half4 detail_diffuse_yz = h4tex2D(s_texture_ ## DIFFUSE,texcoord_yz); \
					half3 detail_normal_xy = mul(tex2DNormal(s_texture_ ## NORMAL,texcoord_xy),basis); \
					half3 detail_normal_xz = mul(tex2DNormal(s_texture_ ## NORMAL,texcoord_xz),basis); \
					half3 detail_normal_yz = mul(tex2DNormal(s_texture_ ## NORMAL,texcoord_yz),basis); \
					diffuse = saturate(diffuse + (detail_diffuse_xy * 2.0f - 1.0f) * diffuse_scale_xy. ## SWIZZLE); \
					diffuse = saturate(diffuse + (detail_diffuse_xz * 2.0f - 1.0f) * diffuse_scale_xz. ## SWIZZLE); \
					diffuse = saturate(diffuse + (detail_diffuse_yz * 2.0f - 1.0f) * diffuse_scale_yz. ## SWIZZLE); \
					normal = normal + detail_normal_xy * normal_scale_xy. ## SWIZZLE; \
					normal = normal + detail_normal_xz * normal_scale_xz. ## SWIZZLE; \
					normal = normal + detail_normal_yz * normal_scale_yz. ## SWIZZLE; \
				}
				
			#else
				
				#define DETAIL(DIFFUSE,NORMAL,NUM,SWIZZLE) { \
					float2 texcoord = IN.texcoord_0.xy * s_terrain_transform_ ## NUM.xy + s_terrain_transform_ ## NUM.zw; \
					half4 detail_diffuse = h4tex2D(s_texture_ ## DIFFUSE,texcoord); \
					half3 detail_normal = mul(tex2DNormal(s_texture_ ## NORMAL,texcoord),basis); \
					diffuse = saturate(diffuse + (detail_diffuse * 2.0f - 1.0f) * diffuse_scale. ## SWIZZLE); \
					normal = normal + detail_normal * normal_scale. ## SWIZZLE; \
				}
				
			#endif
			
			DETAIL(3,4,1,x);
			#ifdef DETAIL_2
				DETAIL(5,6,2,y);
			#endif
			#ifdef DETAIL_3
				DETAIL(7,8,3,z);
			#endif
			#ifdef DETAIL_4
				DETAIL(9,10,4,w);
			#endif
			
			#undef DETAIL
			
			normal = normalize(normal);
			
		#endif
		
	#else
		
		half4 diffuse = h4tex2D(s_texture_0,IN.texcoord_0.zw);
		half3 normal = tex2DNormal(s_texture_1,IN.texcoord_0.zw);
		
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
	#endif
	
	half3 specular = diffuse.xyz * diffuse.w;
	
#endif
