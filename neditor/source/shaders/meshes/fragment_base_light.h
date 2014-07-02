/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_light.h
 * Desc:    Mesh base light shader
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

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL
	
	#include <core/shaders/meshes/fragment_base_sample.h>
	
	#ifdef USE_TESSELLATION && TESSELLATION
		
		half3 vertex_normal = normalize(half3(gl_TexCoord[1].xyz));
		half3 vertex_tangent = normalize(half3(gl_TexCoord[2].xyz));
		half3 vertex_binormal = normalize(cross(vertex_normal,vertex_tangent) * half(gl_TexCoord[2].w));
		
		half3 camera_direction = half3(s_camera_position - gl_TexCoord[3].xyz);
		
		#ifdef PHONG_RIM || !QUALITY_MEDIUM
			
			half3 world_normal = vertex_tangent * normal.x + vertex_binormal * normal.y + vertex_normal * (normal.z * s_light_front);
			
			#ifdef OMNI
				half4 light_direction = half4(getOmniRadius(s_light_position - gl_TexCoord[3].xyz) * s_light_iradius.w,s_light_iradius.w * s_light_iradius.w);
				#ifdef USE_PHONG_RIM && QUALITY_MEDIUM
					half3 color = getDiffuseRimSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,world_normal,light_direction,camera_direction);
				#else
					half3 color = getDiffuseSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,world_normal,light_direction,camera_direction);
				#endif
			#elif PROJ
				half4 light_direction = half4((s_light_position - gl_TexCoord[3].xyz) * (s_light_iradius.x * s_light_iradius.w),s_light_iradius.w * s_light_iradius.w);
				#ifdef USE_PHONG_RIM && QUALITY_MEDIUM
					half3 color = getDiffuseRimSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,world_normal,light_direction,camera_direction);
				#else
					half3 color = getDiffuseSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,world_normal,light_direction,camera_direction);
				#endif
			#elif WORLD
				half3 light_direction = s_light_direction;
				#ifdef USE_PHONG_RIM && QUALITY_MEDIUM
					half3 color = getDiffuseRim(diffuse.xyz,world_normal,light_direction);
				#else
					half3 color = getDiffuse(diffuse.xyz,world_normal,light_direction);
				#endif
				color += getSpecularFresnelNormalize(specular,world_normal,light_direction,camera_direction);
			#endif
			
		#elif ANISOTROPY
			
			camera_direction = half3(dot(camera_direction,vertex_tangent),dot(camera_direction,vertex_binormal),dot(camera_direction,vertex_normal));
			camera_direction.xy = half2(dot(camera_direction.xy,s_material_anisotropy.xy),dot(camera_direction.xy,s_material_anisotropy.zw));
			
			#ifdef OMNI
				half4 light_direction = half4(getOmniRadius(s_light_position - gl_TexCoord[3].xyz) * s_light_iradius.w,s_light_iradius.w * s_light_iradius.w);
				half attenuation = getAttenuate(light_direction);
				light_direction.xyz = half3(dot(light_direction.xyz,vertex_tangent),dot(light_direction.xyz,vertex_binormal),dot(light_direction.xyz,vertex_normal));
				light_direction.xy = half2(dot(light_direction.xy,s_material_anisotropy.xy),dot(light_direction.xy,s_material_anisotropy.zw));
				half3 color = getDiffuseSpecularFresnelNormalize(diffuse.xyz,specular,normal,light_direction.xyz,camera_direction) * attenuation;
			#elif PROJ
				half4 light_direction = half4((s_light_position - gl_TexCoord[3].xyz) * (s_light_iradius.x * s_light_iradius.w),s_light_iradius.w * s_light_iradius.w);
				half attenuation = getAttenuate(light_direction);
				light_direction.xyz = half3(dot(light_direction.xyz,vertex_tangent),dot(light_direction.xyz,vertex_binormal),dot(light_direction.xyz,vertex_normal));
				light_direction.xy = half2(dot(light_direction.xy,s_material_anisotropy.xy),dot(light_direction.xy,s_material_anisotropy.zw));
				half3 color = getDiffuseSpecularFresnelNormalize(diffuse.xyz,specular,normal,light_direction.xyz,camera_direction) * attenuation;
			#elif WORLD
				half3 light_direction = s_light_direction;
				light_direction.xyz = half3(dot(light_direction.xyz,vertex_tangent),dot(light_direction.xyz,vertex_binormal),dot(light_direction.xyz,vertex_normal));
				light_direction.xy = half2(dot(light_direction.xy,s_material_anisotropy.xy),dot(light_direction.xy,s_material_anisotropy.zw));
				half3 color = getDiffuseSpecularFresnelNormalize(diffuse.xyz,specular,normal,light_direction,camera_direction);
			#endif
			
		#endif
		
	#else
		
		#ifdef PHONG_RIM || !QUALITY_MEDIUM
			
			half3 camera_direction = gl_TexCoord[2].xyz;
			
			#ifdef OMNI || PROJ
				half4 light_direction = gl_TexCoord[1];
				#ifdef USE_PHONG_RIM && QUALITY_MEDIUM
					half3 color = getDiffuseRimSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,normal,light_direction,camera_direction);
				#else
					half3 color = getDiffuseSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,normal,light_direction,camera_direction);
				#endif
			#elif WORLD
				half3 light_direction = gl_TexCoord[1].xyz;
				#ifdef USE_PHONG_RIM && QUALITY_MEDIUM
					half3 color = getDiffuseRim(diffuse.xyz,normal,light_direction);
				#else
					half3 color = getDiffuse(diffuse.xyz,normal,light_direction);
				#endif
				color += getSpecularFresnelNormalize(specular,normal,light_direction,camera_direction);
			#endif
			
		#elif ANISOTROPY
			
			half3 camera_direction = gl_TexCoord[2].xyz;
			camera_direction.xy = half2(dot(camera_direction.xy,s_material_anisotropy.xy),dot(camera_direction.xy,s_material_anisotropy.zw));
			
			#ifdef OMNI || PROJ
				half4 light_direction = gl_TexCoord[1];
				half attenuation = getAttenuate(light_direction);
				light_direction.xy = half2(dot(light_direction.xy,s_material_anisotropy.xy),dot(light_direction.xy,s_material_anisotropy.zw));
				half3 color = getDiffuseSpecularFresnelNormalize(diffuse.xyz,specular,normal,light_direction.xyz,camera_direction) * attenuation;
			#elif WORLD
				half3 light_direction = gl_TexCoord[1].xyz;
				light_direction.xy = half2(dot(light_direction.xy,s_material_anisotropy.xy),dot(light_direction.xy,s_material_anisotropy.zw));
				half3 color = getDiffuseSpecularFresnelNormalize(diffuse.xyz,specular,normal,light_direction,camera_direction);
			#endif
			
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#include <core/shaders/meshes/fragment_base_sample.h>
	
	#ifdef PHONG_RIM || !QUALITY_MEDIUM
		
		half3 camera_direction = IN.texcoord_2.xyz;
		
		#ifdef OMNI || PROJ
			half4 light_direction = IN.texcoord_1;
			#ifdef USE_PHONG_RIM && QUALITY_MEDIUM
				half3 color = getDiffuseRimSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,normal,light_direction,camera_direction);
			#else
				half3 color = getDiffuseSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,normal,light_direction,camera_direction);
			#endif
		#elif WORLD
			half3 light_direction = IN.texcoord_1.xyz;
			#ifdef USE_PHONG_RIM && QUALITY_MEDIUM
				half3 color = getDiffuseRim(diffuse.xyz,normal,light_direction);
			#else
				half3 color = getDiffuse(diffuse.xyz,normal,light_direction);
			#endif
			color += getSpecularFresnelNormalize(specular,normal,light_direction,camera_direction);
		#endif
		
	#elif ANISOTROPY
		
		half3 camera_direction = IN.texcoord_2.xyz;
		camera_direction.xy = half2(dot(camera_direction.xy,s_material_anisotropy.xy),dot(camera_direction.xy,s_material_anisotropy.zw));
		
		#ifdef OMNI || PROJ
			half4 light_direction = IN.texcoord_1;
			half attenuation = getAttenuate(light_direction);
			light_direction.xy = half2(dot(light_direction.xy,s_material_anisotropy.xy),dot(light_direction.xy,s_material_anisotropy.zw));
			half3 color = getDiffuseSpecularFresnelNormalize(diffuse.xyz,specular,normal,light_direction.xyz,camera_direction) * attenuation;
		#elif WORLD
			half3 light_direction = IN.texcoord_1.xyz;
			light_direction.xy = half2(dot(light_direction.xy,s_material_anisotropy.xy),dot(light_direction.xy,s_material_anisotropy.zw));
			half3 color = getDiffuseSpecularFresnelNormalize(diffuse.xyz,specular,normal,light_direction,camera_direction);
		#endif
		
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#include <core/shaders/meshes/fragment_base_sample.h>
	
	#ifdef USE_TESSELLATION && TESSELLATION
		
		half3 vertex_normal = normalize(IN.texcoord_1);
		half3 vertex_tangent = normalize(IN.texcoord_2.xyz);
		half3 vertex_binormal = normalize(cross(vertex_normal,vertex_tangent) * IN.texcoord_2.w);
		
		half3 camera_direction = s_camera_position - IN.texcoord_3;
		
		#ifdef PHONG_RIM || !QUALITY_MEDIUM
			
			half3 world_normal = vertex_tangent * normal.x + vertex_binormal * normal.y + vertex_normal * (normal.z * s_light_front);
			
			#ifdef OMNI
				half4 light_direction = half4(getOmniRadius(s_light_position - IN.texcoord_3) * s_light_iradius.w,s_light_iradius.w * s_light_iradius.w);
				#ifdef USE_PHONG_RIM && QUALITY_MEDIUM
					half3 color = getDiffuseRimSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,world_normal,light_direction,camera_direction);
				#else
					half3 color = getDiffuseSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,world_normal,light_direction,camera_direction);
				#endif
			#elif PROJ
				half4 light_direction = half4((s_light_position - IN.texcoord_3) * (s_light_iradius.x * s_light_iradius.w),s_light_iradius.w * s_light_iradius.w);
				#ifdef USE_PHONG_RIM && QUALITY_MEDIUM
					half3 color = getDiffuseRimSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,world_normal,light_direction,camera_direction);
				#else
					half3 color = getDiffuseSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,world_normal,light_direction,camera_direction);
				#endif
			#elif WORLD
				half3 light_direction = s_light_direction;
				#ifdef USE_PHONG_RIM && QUALITY_MEDIUM
					half3 color = getDiffuseRim(diffuse.xyz,world_normal,light_direction);
				#else
					half3 color = getDiffuse(diffuse.xyz,world_normal,light_direction);
				#endif
				color += getSpecularFresnelNormalize(specular,world_normal,light_direction,camera_direction);
			#endif
			
		#elif ANISOTROPY
			
			camera_direction = half3(dot(camera_direction,vertex_tangent),dot(camera_direction,vertex_binormal),dot(camera_direction,vertex_normal));
			camera_direction.xy = half2(dot(camera_direction.xy,s_material_anisotropy.xy),dot(camera_direction.xy,s_material_anisotropy.zw));
			
			#ifdef OMNI
				half4 light_direction = half4(getOmniRadius(s_light_position - IN.texcoord_3) * s_light_iradius.w,s_light_iradius.w * s_light_iradius.w);
				half attenuation = getAttenuate(light_direction);
				light_direction.xyz = half3(dot(light_direction.xyz,vertex_tangent),dot(light_direction.xyz,vertex_binormal),dot(light_direction.xyz,vertex_normal));
				light_direction.xy = half2(dot(light_direction.xy,s_material_anisotropy.xy),dot(light_direction.xy,s_material_anisotropy.zw));
				half3 color = getDiffuseSpecularFresnelNormalize(diffuse.xyz,specular,normal,light_direction.xyz,camera_direction) * attenuation;
			#elif PROJ
				half4 light_direction = half4((s_light_position - IN.texcoord_3) * (s_light_iradius.x * s_light_iradius.w),s_light_iradius.w * s_light_iradius.w);
				half attenuation = getAttenuate(light_direction);
				light_direction.xyz = half3(dot(light_direction.xyz,vertex_tangent),dot(light_direction.xyz,vertex_binormal),dot(light_direction.xyz,vertex_normal));
				light_direction.xy = half2(dot(light_direction.xy,s_material_anisotropy.xy),dot(light_direction.xy,s_material_anisotropy.zw));
				half3 color = getDiffuseSpecularFresnelNormalize(diffuse.xyz,specular,normal,light_direction.xyz,camera_direction) * attenuation;
			#elif WORLD
				half3 light_direction = s_light_direction;
				light_direction.xyz = half3(dot(light_direction.xyz,vertex_tangent),dot(light_direction.xyz,vertex_binormal),dot(light_direction.xyz,vertex_normal));
				light_direction.xy = half2(dot(light_direction.xy,s_material_anisotropy.xy),dot(light_direction.xy,s_material_anisotropy.zw));
				half3 color = getDiffuseSpecularFresnelNormalize(diffuse.xyz,specular,normal,light_direction,camera_direction);
			#endif
			
		#endif
		
	#else
		
		#ifdef PHONG_RIM || !QUALITY_MEDIUM
			
			half3 camera_direction = IN.texcoord_2.xyz;
			
			#ifdef OMNI || PROJ
				half4 light_direction = IN.texcoord_1;
				#ifdef USE_PHONG_RIM && QUALITY_MEDIUM
					half3 color = getDiffuseRimSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,normal,light_direction,camera_direction);
				#else
					half3 color = getDiffuseSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,normal,light_direction,camera_direction);
				#endif
			#elif WORLD
				half3 light_direction = IN.texcoord_1.xyz;
				#ifdef USE_PHONG_RIM && QUALITY_MEDIUM
					half3 color = getDiffuseRim(diffuse.xyz,normal,light_direction);
				#else
					half3 color = getDiffuse(diffuse.xyz,normal,light_direction);
				#endif
				color += getSpecularFresnelNormalize(specular,normal,light_direction,camera_direction);
			#endif
			
		#elif ANISOTROPY
			
			half3 camera_direction = IN.texcoord_2.xyz;
			camera_direction.xy = half2(dot(camera_direction.xy,s_material_anisotropy.xy),dot(camera_direction.xy,s_material_anisotropy.zw));
			
			#ifdef OMNI || PROJ
				half4 light_direction = IN.texcoord_1;
				half attenuation = getAttenuate(light_direction);
				light_direction.xy = half2(dot(light_direction.xy,s_material_anisotropy.xy),dot(light_direction.xy,s_material_anisotropy.zw));
				half3 color = getDiffuseSpecularFresnelNormalize(diffuse.xyz,specular,normal,light_direction.xyz,camera_direction) * attenuation;
			#elif WORLD
				half3 light_direction = IN.texcoord_1.xyz;
				light_direction.xy = half2(dot(light_direction.xy,s_material_anisotropy.xy),dot(light_direction.xy,s_material_anisotropy.zw));
				half3 color = getDiffuseSpecularFresnelNormalize(diffuse.xyz,specular,normal,light_direction,camera_direction);
			#endif
			
		#endif
		
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#include <core/shaders/meshes/fragment_base_sample.h>
	
	#ifdef PHONG_RIM || !QUALITY_MEDIUM
		
		half3 camera_direction = IN.texcoord_2.xyz;
		
		#ifdef OMNI || PROJ
			half4 light_direction = IN.texcoord_1;
			#ifdef USE_PHONG_RIM && QUALITY_MEDIUM
				half3 color = getDiffuseRimSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,normal,light_direction,camera_direction);
			#else
				half3 color = getDiffuseSpecularFresnelNormalizeAttenuate(diffuse.xyz,specular,normal,light_direction,camera_direction);
			#endif
		#elif WORLD
			half3 light_direction = IN.texcoord_1.xyz;
			#ifdef USE_PHONG_RIM && QUALITY_MEDIUM
				half3 color = getDiffuseRim(diffuse.xyz,normal,light_direction);
			#else
				half3 color = getDiffuse(diffuse.xyz,normal,light_direction);
			#endif
			color += getSpecularFresnelNormalize(specular,normal,light_direction,camera_direction);
		#endif
		
	#elif ANISOTROPY
		
		half3 camera_direction = IN.texcoord_2.xyz;
		camera_direction.xy = half2(dot(camera_direction.xy,s_material_anisotropy.xy),dot(camera_direction.xy,s_material_anisotropy.zw));
		
		#ifdef OMNI || PROJ
			half4 light_direction = IN.texcoord_1;
			half attenuation = getAttenuate(light_direction);
			light_direction.xy = half2(dot(light_direction.xy,s_material_anisotropy.xy),dot(light_direction.xy,s_material_anisotropy.zw));
			half3 color = getDiffuseSpecularFresnelNormalize(diffuse.xyz,specular,normal,light_direction.xyz,camera_direction) * attenuation;
		#elif WORLD
			half3 light_direction = IN.texcoord_1.xyz;
			light_direction.xy = half2(dot(light_direction.xy,s_material_anisotropy.xy),dot(light_direction.xy,s_material_anisotropy.zw));
			half3 color = getDiffuseSpecularFresnelNormalize(diffuse.xyz,specular,normal,light_direction,camera_direction);
		#endif
		
	#endif
	
#endif
