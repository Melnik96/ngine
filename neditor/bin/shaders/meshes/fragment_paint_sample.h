/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_paint_sample.h
 * Desc:    Mesh paint sample shader
 * Version: 1.10
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
	
	#ifdef USE_TESSELLATION && TESSELLATION
		texture2DAlphaFadeDiscard(s_texture_9,gl_TexCoord[7].x);
	#else
		texture2DAlphaFadeDiscard(s_texture_9,gl_TexCoord[7].z);
	#endif
	
	float4 texcoord = gl_TexCoord[0];
	
	half4 diffuse = texture2DAlpha(s_texture_0,texcoord.xy,1.0f);
	half3 normal = texture2D(s_texture_1,texcoord.xy).xyz;
	half4 specular = texture2D(s_texture_2,texcoord.xy);
	
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		
		#ifdef OVERLAY_0 || MULTIPLY_0
			float2 detail_texcoord = texcoord.xy * detail_transform.xy + detail_transform.zw;
		#elif OVERLAY_1 || MULTIPLY_1
			float2 detail_texcoord = texcoord.zw * detail_transform.xy + detail_transform.zw;
		#endif
		
		half4 detail_diffuse = texture2D(s_texture_3,detail_texcoord);
		half2 detail_normal = texture2D(s_texture_4,detail_texcoord).xy;
		half3 detail_specular = texture2D(s_texture_5,detail_texcoord).xyz;
		
		#ifdef ALPHA
			half3 k = s_material_detail * detail_diffuse.w;
		#else
			half3 k = s_material_detail * (diffuse.w * detail_diffuse.w);
		#endif
		
		#ifdef OVERLAY_0 || OVERLAY_1
			diffuse.xyz = saturate(diffuse.xyz + (detail_diffuse.xyz * 2.0f - 1.0f) * k.x);
			specular.xyz = saturate(specular.xyz + (detail_specular.xyz * 2.0f - 1.0f) * k.z);
		#else
			diffuse.xyz = diffuse.xyz * saturate(detail_diffuse.xyz + 1.0f - k.x);
			specular.xyz = specular.xyz * saturate(detail_specular.xyz + 1.0f - k.z);
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
	
	#ifdef USE_TESSELLATION && TESSELLATION
		
		half3 vertex_normal = normalize(half3(gl_TexCoord[1].xyz));
		half3 vertex_tangent = normalize(half3(gl_TexCoord[2].xyz));
		half3 vertex_binormal = normalize(cross(vertex_normal,vertex_tangent) * half(gl_TexCoord[2].w));
		
		#ifdef AMBIENT
			half3 world_normal = normalize(vertex_tangent * normal.x + vertex_binormal * normal.y + vertex_normal * normal.z);
		#else
			half3 world_normal = normalize(vertex_tangent * normal.x + vertex_binormal * normal.y + vertex_normal * (normal.z * s_light_front));
		#endif
		
		half3 camera_direction = normalize(s_camera_position - gl_TexCoord[3].xyz);
		half camera_angle = saturate(dot(world_normal,camera_direction));
		#ifdef AMBIENT || PROB || SPOT
			half3 light_direction = camera_direction;
			half light_angle = camera_angle;
		#elif OMNI
			half4 light_direction = half4(getOmniRadius(s_light_position - gl_TexCoord[3].xyz) * s_light_iradius.w,s_light_iradius.w * s_light_iradius.w);
			half light_direction_ilength = rsqrt(dot(light_direction.xyz,light_direction.xyz));
			half light_angle = saturate(dot(reflect(-light_direction.xyz,world_normal),camera_direction) * light_direction_ilength);
		#elif PROJ
			half4 light_direction = half4((s_light_position - gl_TexCoord[3].xyz) * (s_light_iradius.x * s_light_iradius.w),s_light_iradius.w * s_light_iradius.w);
			half light_direction_ilength = rsqrt(dot(light_direction.xyz,light_direction.xyz));
			half light_angle = saturate(dot(reflect(-light_direction.xyz,world_normal),camera_direction) * light_direction_ilength);
		#elif WORLD
			half3 light_direction = s_light_direction;
			half light_angle = saturate(dot(reflect(-light_direction,world_normal),camera_direction));
		#endif
		
		half camera_angle_log2 = log2(camera_angle);
		diffuse.xyz *= diffuse_0_color.xyz * exp2(camera_angle_log2 * diffuse_0_power) +
			diffuse_1_color.xyz * exp2(camera_angle_log2 * diffuse_1_power) +
			diffuse_2_color.xyz * exp2(camera_angle_log2 * diffuse_2_power);
		
		#ifdef QUALITY_MEDIUM
			#ifdef FLECK
				float3 position = s_transform[0].xyz * (gl_TexCoord[3].x - s_transform[0].w);
				position += s_transform[1].xyz * (gl_TexCoord[3].y - s_transform[1].w);
				position += s_transform[2].xyz * (gl_TexCoord[3].z - s_transform[2].w);
				half3 fleck_texcoord = position * fleck_size;
				half fleck_noise_0 = pow(texture3D(s_texture_10,fleck_texcoord * 1.000f).x,fleck_power);
				half fleck_noise_1 = pow(texture3D(s_texture_10,fleck_texcoord * 2.100f).x,fleck_power);
				half fleck_noise_2 = pow(texture3D(s_texture_10,fleck_texcoord * 4.410f).x,fleck_power);
				half fleck_noise_3 = pow(texture3D(s_texture_10,fleck_texcoord * 9.261f).x,fleck_power);
				half fleck = fleck_noise_0 + fleck_noise_1 + fleck_noise_2 + fleck_noise_3;
				diffuse.xyz += specular.xyz * fleck_color.xyz * (pow(light_angle,fleck_radius) * fleck);
			#endif
		#endif
		
	#else
		
		#ifdef AMBIENT
			half3 world_normal;
			world_normal.x = dot(half3(gl_TexCoord[1].xyz),normal);
			world_normal.y = dot(half3(gl_TexCoord[2].xyz),normal);
			world_normal.z = dot(half3(gl_TexCoord[3].xyz),normal);
			world_normal = normalize(world_normal);
			half3 camera_direction = normalize(gl_TexCoord[4].xyz);
			half camera_angle = saturate(dot(world_normal,camera_direction));
			half light_angle = camera_angle;
		#elif PROB
			half3 world_normal;
			world_normal.x = dot(half3(gl_TexCoord[2].xyz),normal);
			world_normal.y = dot(half3(gl_TexCoord[3].xyz),normal);
			world_normal.z = dot(half3(gl_TexCoord[4].xyz),normal);
			world_normal = normalize(world_normal);
			half3 camera_direction = normalize(gl_TexCoord[1].xyz);
			half camera_angle = saturate(dot(world_normal,camera_direction));
			half3 light_direction = camera_direction;
			half light_angle = camera_angle;
		#elif SPOT
			half3 world_normal;
			world_normal.x = dot(half3(gl_TexCoord[3].xyz),normal);
			world_normal.y = dot(half3(gl_TexCoord[4].xyz),normal);
			world_normal.z = dot(half3(gl_TexCoord[5].xyz),normal);
			world_normal = normalize(world_normal);
			half3 camera_direction = normalize(gl_TexCoord[2].xyz);
			half camera_angle = saturate(dot(world_normal,camera_direction));
			half3 light_direction = camera_direction;
			half light_angle = camera_angle;
		#elif OMNI || PROJ
			half3 camera_direction = normalize(gl_TexCoord[2].xyz);
			half camera_angle = saturate(dot(normal,camera_direction));
			half3 light_direction = normalize(gl_TexCoord[1].xyz);
			half light_angle = saturate(dot(reflect(-light_direction,normal),camera_direction));
		#elif WORLD
			half3 camera_direction = normalize(gl_TexCoord[2].xyz);
			half camera_angle = saturate(dot(normal,camera_direction));
			half3 light_direction = gl_TexCoord[1].xyz;
			half light_angle = saturate(dot(reflect(-light_direction,normal),camera_direction));
		#endif
		
		half camera_angle_log2 = log2(camera_angle);
		diffuse.xyz *= diffuse_0_color.xyz * exp2(camera_angle_log2 * diffuse_0_power) +
			diffuse_1_color.xyz * exp2(camera_angle_log2 * diffuse_1_power) +
			diffuse_2_color.xyz * exp2(camera_angle_log2 * diffuse_2_power);
		
		#ifdef QUALITY_MEDIUM
			#ifdef FLECK
				half3 fleck_texcoord = gl_TexCoord[6].xyz * fleck_size;
				half fleck_noise_0 = pow(texture3D(s_texture_10,fleck_texcoord * 1.000f).x,fleck_power);
				half fleck_noise_1 = pow(texture3D(s_texture_10,fleck_texcoord * 2.100f).x,fleck_power);
				half fleck_noise_2 = pow(texture3D(s_texture_10,fleck_texcoord * 4.410f).x,fleck_power);
				half fleck_noise_3 = pow(texture3D(s_texture_10,fleck_texcoord * 9.261f).x,fleck_power);
				half fleck = fleck_noise_0 + fleck_noise_1 + fleck_noise_2 + fleck_noise_3;
				diffuse.xyz += specular.xyz * fleck_color.xyz * (pow(light_angle,fleck_radius) * fleck);
			#endif
		#endif
		
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
		specular.xyz *= specular.xyz;
	#endif
	
/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_9,IN.texcoord_7,IN.texcoord_7.z);
	#endif
	
	float4 texcoord = IN.texcoord_0;
	
	half4 diffuse = tex2DAlpha(s_texture_0,texcoord.xy,1.0f);
	half3 normal = tex2D(s_texture_1,texcoord.xy).xyz;
	half4 specular = tex2D(s_texture_2,texcoord.xy);
	
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		
		#ifdef OVERLAY_0 || MULTIPLY_0
			float2 detail_texcoord = texcoord.xy * detail_transform.xy + detail_transform.zw;
		#elif OVERLAY_1 || MULTIPLY_1
			float2 detail_texcoord = texcoord.zw * detail_transform.xy + detail_transform.zw;
		#endif
		
		half4 detail_diffuse = tex2D(s_texture_3,detail_texcoord);
		half2 detail_normal = tex2D(s_texture_4,detail_texcoord).xy;
		half3 detail_specular = tex2D(s_texture_5,detail_texcoord).xyz;
		
		#ifdef ALPHA
			half3 k = s_material_detail * detail_diffuse.w;
		#else
			half3 k = s_material_detail * (diffuse.w * detail_diffuse.w);
		#endif
		
		#ifdef OVERLAY_0 || OVERLAY_1
			diffuse.xyz = saturate(diffuse.xyz + (detail_diffuse.xyz * 2.0f - 1.0f) * k.x);
			specular.xyz = saturate(specular.xyz + (detail_specular.xyz * 2.0f - 1.0f) * k.z);
		#else
			diffuse.xyz = diffuse.xyz * saturate(detail_diffuse.xyz + 1.0f - k.x);
			specular.xyz = specular.xyz * saturate(detail_specular.xyz + 1.0f - k.z);
		#endif
		normal.xy = normal.xy + detail_normal * k.y;
		
		normal.xy = normal.xy * 2.0f - 1.0f - k.y;
		
	#else
		
		normal.xy = normal.xy * 2.0f - 1.0f;
		
	#endif
	
	normal.z = sqrt(saturate(1.0f - dot(normal.xy,normal.xy)));
	
	#ifdef AMBIENT
		half3 world_normal;
		world_normal.x = dot(IN.texcoord_1,normal);
		world_normal.y = dot(IN.texcoord_2,normal);
		world_normal.z = dot(IN.texcoord_3,normal);
		world_normal = normalize(world_normal);
		half3 camera_direction = normalize(IN.texcoord_4);
		half camera_angle = saturate(dot(world_normal,camera_direction));
		half light_angle = camera_angle;
	#elif PROB
		half3 world_normal;
		world_normal.x = dot(IN.texcoord_2,normal);
		world_normal.y = dot(IN.texcoord_3,normal);
		world_normal.z = dot(IN.texcoord_4,normal);
		world_normal = normalize(world_normal);
		half3 camera_direction = normalize(IN.texcoord_1);
		half camera_angle = saturate(dot(world_normal,camera_direction));
		half3 light_direction = camera_direction;
		half light_angle = camera_angle;
	#elif SPOT
		half3 world_normal;
		world_normal.x = dot(IN.texcoord_3,normal);
		world_normal.y = dot(IN.texcoord_4,normal);
		world_normal.z = dot(IN.texcoord_5,normal);
		world_normal = normalize(world_normal);
		half3 camera_direction = normalize(IN.texcoord_2);
		half camera_angle = saturate(dot(world_normal,camera_direction));
		half3 light_direction = camera_direction;
		half light_angle = camera_angle;
	#elif OMNI || PROJ
		half3 camera_direction = normalize(IN.texcoord_2);
		half camera_angle = saturate(dot(normal,camera_direction));
		half3 light_direction = normalize(IN.texcoord_1.xyz);
		half light_angle = saturate(dot(reflect(-light_direction,normal),camera_direction));
	#elif WORLD
		half3 camera_direction = normalize(IN.texcoord_2);
		half camera_angle = saturate(dot(normal,camera_direction));
		half3 light_direction = IN.texcoord_1;
		half light_angle = saturate(dot(reflect(-light_direction,normal),camera_direction));
	#endif
	
	half camera_angle_log2 = log2(camera_angle);
	diffuse.xyz *= diffuse_0_color.xyz * exp2(camera_angle_log2 * diffuse_0_power) +
		diffuse_1_color.xyz * exp2(camera_angle_log2 * diffuse_1_power) +
		diffuse_2_color.xyz * exp2(camera_angle_log2 * diffuse_2_power);
	
	#ifdef QUALITY_MEDIUM
		#ifdef FLECK
			half3 fleck_texcoord = IN.texcoord_6 * fleck_size;
			half fleck_noise_0 = pow(tex3D(s_texture_10,fleck_texcoord * 1.000f).x,fleck_power);
			half fleck_noise_1 = pow(tex3D(s_texture_10,fleck_texcoord * 2.100f).x,fleck_power);
			half fleck_noise_2 = pow(tex3D(s_texture_10,fleck_texcoord * 4.410f).x,fleck_power);
			half fleck_noise_3 = pow(tex3D(s_texture_10,fleck_texcoord * 9.261f).x,fleck_power);
			half fleck = fleck_noise_0 + fleck_noise_1 + fleck_noise_2 + fleck_noise_3;
			diffuse.xyz += specular.xyz * fleck_color.xyz * (pow(light_angle,fleck_radius) * fleck);
		#endif
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
		specular.xyz *= specular.xyz;
	#endif
	
/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		texture2DAlphaFadeDiscard(s_texture_9,s_sampler_9,IN.position.xy,IN.texcoord_9.x);
	#endif
	
	float4 texcoord = IN.texcoord_0;
	
	OUT = texture2DAlpha(s_texture_0,s_sampler_0,texcoord.xy,1.0f);
	half4 diffuse = OUT.color;
	
	half3 normal = s_texture_1.Sample(s_sampler_1,texcoord.xy).xyz;
	half4 specular = s_texture_2.Sample(s_sampler_2,texcoord.xy);
	
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		
		#ifdef OVERLAY_0 || MULTIPLY_0
			float2 detail_texcoord = texcoord.xy * detail_transform.xy + detail_transform.zw;
		#elif OVERLAY_1 || MULTIPLY_1
			float2 detail_texcoord = texcoord.zw * detail_transform.xy + detail_transform.zw;
		#endif
		
		half4 detail_diffuse = s_texture_3.Sample(s_sampler_3,detail_texcoord);
		half2 detail_normal = s_texture_4.Sample(s_sampler_4,detail_texcoord).xy;
		half3 detail_specular = s_texture_5.Sample(s_sampler_5,detail_texcoord).xyz;
		
		#ifdef ALPHA
			half3 k = s_material_detail * detail_diffuse.w;
		#else
			half3 k = s_material_detail * (diffuse.w * detail_diffuse.w);
		#endif
		
		#ifdef OVERLAY_0 || OVERLAY_1
			diffuse.xyz = saturate(diffuse.xyz + (detail_diffuse.xyz * 2.0f - 1.0f) * k.x);
			specular.xyz = saturate(specular.xyz + (detail_specular.xyz * 2.0f - 1.0f) * k.z);
		#else
			diffuse.xyz = diffuse.xyz * saturate(detail_diffuse.xyz + 1.0f - k.x);
			specular.xyz = specular.xyz * saturate(detail_specular.xyz + 1.0f - k.z);
		#endif
		normal.xy = normal.xy + detail_normal * k.y;
		
	#endif
	
	normal.z = sqrt(saturate(1.0f - dot(normal.xy,normal.xy)));
	
	#ifdef USE_TESSELLATION && TESSELLATION
		
		half3 vertex_normal = normalize(IN.texcoord_1);
		half3 vertex_tangent = normalize(IN.texcoord_2.xyz);
		half3 vertex_binormal = normalize(cross(vertex_normal,vertex_tangent) * IN.texcoord_2.w);
		
		#ifdef AMBIENT
			half3 world_normal = normalize(vertex_tangent * normal.x + vertex_binormal * normal.y + vertex_normal * normal.z);
		#else
			half3 world_normal = normalize(vertex_tangent * normal.x + vertex_binormal * normal.y + vertex_normal * (normal.z * s_light_front));
		#endif
		
		half3 camera_direction = normalize(s_camera_position - IN.texcoord_3);
		half camera_angle = saturate(dot(world_normal,camera_direction));
		#ifdef AMBIENT || PROB || SPOT
			half3 light_direction = camera_direction;
			half light_angle = camera_angle;
		#elif OMNI
			half4 light_direction = half4(getOmniRadius(s_light_position - IN.texcoord_3) * s_light_iradius.w,s_light_iradius.w * s_light_iradius.w);
			half light_direction_ilength = rsqrt(dot(light_direction.xyz,light_direction.xyz));
			half light_angle = saturate(dot(reflect(-light_direction.xyz,world_normal),camera_direction) * light_direction_ilength);
		#elif PROJ
			half4 light_direction = half4((s_light_position - IN.texcoord_3) * (s_light_iradius.x * s_light_iradius.w),s_light_iradius.w * s_light_iradius.w);
			half light_direction_ilength = rsqrt(dot(light_direction.xyz,light_direction.xyz));
			half light_angle = saturate(dot(reflect(-light_direction.xyz,world_normal),camera_direction) * light_direction_ilength);
		#elif WORLD
			half3 light_direction = s_light_direction;
			half light_angle = saturate(dot(reflect(-light_direction,world_normal),camera_direction));
		#endif
		
		half camera_angle_log2 = log2(camera_angle);
		diffuse.xyz *= diffuse_0_color.xyz * exp2(camera_angle_log2 * diffuse_0_power) +
			diffuse_1_color.xyz * exp2(camera_angle_log2 * diffuse_1_power) +
			diffuse_2_color.xyz * exp2(camera_angle_log2 * diffuse_2_power);
		
		#ifdef QUALITY_MEDIUM
			#ifdef FLECK
				float3 position = s_transform[0].xyz * (IN.texcoord_3.x - s_transform[0].w);
				position += s_transform[1].xyz * (IN.texcoord_3.y - s_transform[1].w);
				position += s_transform[2].xyz * (IN.texcoord_3.z - s_transform[2].w);
				half3 fleck_texcoord = position * fleck_size;
				half fleck_noise_0 = pow(s_texture_10.Sample(s_sampler_10,fleck_texcoord * 1.000f).x,fleck_power);
				half fleck_noise_1 = pow(s_texture_10.Sample(s_sampler_10,fleck_texcoord * 2.100f).x,fleck_power);
				half fleck_noise_2 = pow(s_texture_10.Sample(s_sampler_10,fleck_texcoord * 4.410f).x,fleck_power);
				half fleck_noise_3 = pow(s_texture_10.Sample(s_sampler_10,fleck_texcoord * 9.261f).x,fleck_power);
				half fleck = fleck_noise_0 + fleck_noise_1 + fleck_noise_2 + fleck_noise_3;
				diffuse.xyz += specular.xyz * fleck_color.xyz * (pow(light_angle,fleck_radius) * fleck);
			#endif
		#endif
		
	#else
		
		#ifdef AMBIENT
			half3 world_normal;
			world_normal.x = dot(IN.texcoord_1,normal);
			world_normal.y = dot(IN.texcoord_2,normal);
			world_normal.z = dot(IN.texcoord_3,normal);
			world_normal = normalize(world_normal);
			half3 camera_direction = normalize(IN.texcoord_4);
			half camera_angle = saturate(dot(world_normal,camera_direction));
			half light_angle = camera_angle;
		#elif PROB
			half3 world_normal;
			world_normal.x = dot(IN.texcoord_2,normal);
			world_normal.y = dot(IN.texcoord_3,normal);
			world_normal.z = dot(IN.texcoord_4,normal);
			world_normal = normalize(world_normal);
			half3 camera_direction = normalize(IN.texcoord_1);
			half camera_angle = saturate(dot(world_normal,camera_direction));
			half3 light_direction = camera_direction;
			half light_angle = camera_angle;
		#elif SPOT
			half3 world_normal;
			world_normal.x = dot(IN.texcoord_3,normal);
			world_normal.y = dot(IN.texcoord_4,normal);
			world_normal.z = dot(IN.texcoord_5,normal);
			world_normal = normalize(world_normal);
			half3 camera_direction = normalize(IN.texcoord_2);
			half camera_angle = saturate(dot(world_normal,camera_direction));
			half3 light_direction = camera_direction;
			half light_angle = camera_angle;
		#elif OMNI || PROJ
			half3 camera_direction = normalize(IN.texcoord_2);
			half camera_angle = saturate(dot(normal,camera_direction));
			half3 light_direction = normalize(IN.texcoord_1.xyz);
			half light_angle = saturate(dot(reflect(-light_direction,normal),camera_direction));
		#elif WORLD
			half3 camera_direction = normalize(IN.texcoord_2);
			half camera_angle = saturate(dot(normal,camera_direction));
			half3 light_direction = IN.texcoord_1;
			half light_angle = saturate(dot(reflect(-light_direction,normal),camera_direction));
		#endif
		
		half camera_angle_log2 = log2(camera_angle);
		diffuse.xyz *= diffuse_0_color.xyz * exp2(camera_angle_log2 * diffuse_0_power) +
			diffuse_1_color.xyz * exp2(camera_angle_log2 * diffuse_1_power) +
			diffuse_2_color.xyz * exp2(camera_angle_log2 * diffuse_2_power);
		
		#ifdef QUALITY_MEDIUM
			#ifdef FLECK
				half3 fleck_texcoord = IN.texcoord_6 * fleck_size;
				half fleck_noise_0 = pow(s_texture_10.Sample(s_sampler_10,fleck_texcoord * 1.000f).x,fleck_power);
				half fleck_noise_1 = pow(s_texture_10.Sample(s_sampler_10,fleck_texcoord * 2.100f).x,fleck_power);
				half fleck_noise_2 = pow(s_texture_10.Sample(s_sampler_10,fleck_texcoord * 4.410f).x,fleck_power);
				half fleck_noise_3 = pow(s_texture_10.Sample(s_sampler_10,fleck_texcoord * 9.261f).x,fleck_power);
				half fleck = fleck_noise_0 + fleck_noise_1 + fleck_noise_2 + fleck_noise_3;
				diffuse.xyz += specular.xyz * fleck_color.xyz * (pow(light_angle,fleck_radius) * fleck);
			#endif
		#endif
		
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
		specular.xyz *= specular.xyz;
	#endif
	
/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3
	
	#ifdef USE_ALPHA_FADE && ALPHA_FADE
		tex2DAlphaFadeDiscard(s_texture_9,IN.texcoord_9,IN.texcoord_9.z);
	#endif
	
	float4 texcoord = IN.texcoord_0;
	
	half4 diffuse = tex2DAlpha(s_texture_0,texcoord.xy,1.0f);
	half3 normal = h3tex2D(s_texture_1,texcoord.xy).xyz;
	half4 specular = h4tex2D(s_texture_2,texcoord.xy);
	
	#ifdef OVERLAY_0 || OVERLAY_1 || MULTIPLY_0 || MULTIPLY_1
		
		#ifdef OVERLAY_0 || MULTIPLY_0
			float2 detail_texcoord = texcoord.xy * detail_transform.xy + detail_transform.zw;
		#elif OVERLAY_1 || MULTIPLY_1
			float2 detail_texcoord = texcoord.zw * detail_transform.xy + detail_transform.zw;
		#endif
		
		half4 detail_diffuse = h4tex2D(s_texture_3,detail_texcoord);
		half2 detail_normal = h2tex2D(s_texture_4,detail_texcoord).xy;
		half3 detail_specular = h3tex2D(s_texture_5,detail_texcoord).xyz;
		
		#ifdef ALPHA
			half3 k = s_material_detail * detail_diffuse.w;
		#else
			half3 k = s_material_detail * (diffuse.w * detail_diffuse.w);
		#endif
		
		#ifdef OVERLAY_0 || OVERLAY_1
			diffuse.xyz = saturate(diffuse.xyz + (detail_diffuse.xyz * 2.0f - 1.0f) * k.x);
			specular.xyz = saturate(specular.xyz + (detail_specular.xyz * 2.0f - 1.0f) * k.z);
		#else
			diffuse.xyz = diffuse.xyz * saturate(detail_diffuse.xyz + 1.0f - k.x);
			specular.xyz = specular.xyz * saturate(detail_specular.xyz + 1.0f - k.z);
		#endif
		normal.xy = normal.xy + detail_normal * k.y;
		
	#endif
	
	normal.z = sqrt(saturate(1.0f - dot(normal.xy,normal.xy)));
	
	#ifdef AMBIENT
		half3 world_normal;
		world_normal.x = dot(IN.texcoord_1,normal);
		world_normal.y = dot(IN.texcoord_2,normal);
		world_normal.z = dot(IN.texcoord_3,normal);
		world_normal = normalize(world_normal);
		half3 camera_direction = normalize(IN.texcoord_4);
		half camera_angle = saturate(dot(world_normal,camera_direction));
		half light_angle = camera_angle;
	#elif PROB
		half3 world_normal;
		world_normal.x = dot(IN.texcoord_2,normal);
		world_normal.y = dot(IN.texcoord_3,normal);
		world_normal.z = dot(IN.texcoord_4,normal);
		world_normal = normalize(world_normal);
		half3 camera_direction = normalize(IN.texcoord_1);
		half camera_angle = saturate(dot(world_normal,camera_direction));
		half3 light_direction = camera_direction;
		half light_angle = camera_angle;
	#elif SPOT
		half3 world_normal;
		world_normal.x = dot(IN.texcoord_3,normal);
		world_normal.y = dot(IN.texcoord_4,normal);
		world_normal.z = dot(IN.texcoord_5,normal);
		world_normal = normalize(world_normal);
		half3 camera_direction = normalize(IN.texcoord_2);
		half camera_angle = saturate(dot(world_normal,camera_direction));
		half3 light_direction = camera_direction;
		half light_angle = camera_angle;
	#elif OMNI || PROJ
		half3 camera_direction = normalize(IN.texcoord_2);
		half camera_angle = saturate(dot(normal,camera_direction));
		half3 light_direction = normalize(IN.texcoord_1.xyz);
		half light_angle = saturate(dot(reflect(-light_direction,normal),camera_direction));
	#elif WORLD
		half3 camera_direction = normalize(IN.texcoord_2);
		half camera_angle = saturate(dot(normal,camera_direction));
		half3 light_direction = IN.texcoord_1;
		half light_angle = saturate(dot(reflect(-light_direction,normal),camera_direction));
	#endif
	
	half camera_angle_log2 = log2(camera_angle);
	diffuse.xyz *= diffuse_0_color.xyz * exp2(camera_angle_log2 * diffuse_0_power) +
		diffuse_1_color.xyz * exp2(camera_angle_log2 * diffuse_1_power) +
		diffuse_2_color.xyz * exp2(camera_angle_log2 * diffuse_2_power);
	
	#ifdef QUALITY_MEDIUM
		#ifdef FLECK
			half3 fleck_texcoord = IN.texcoord_8 * fleck_size;
			half fleck_noise_0 = pow(h1tex3D(s_texture_10,fleck_texcoord * 1.000f),fleck_power);
			half fleck_noise_1 = pow(h1tex3D(s_texture_10,fleck_texcoord * 2.100f),fleck_power);
			half fleck_noise_2 = pow(h1tex3D(s_texture_10,fleck_texcoord * 4.410f),fleck_power);
			half fleck_noise_3 = pow(h1tex3D(s_texture_10,fleck_texcoord * 9.261f),fleck_power);
			half fleck = fleck_noise_0 + fleck_noise_1 + fleck_noise_2 + fleck_noise_3;
			diffuse.xyz += specular.xyz * fleck_color.xyz * (pow(light_angle,fleck_radius) * fleck);
		#endif
	#endif
	
	#ifdef USE_SRGB
		diffuse.xyz *= diffuse.xyz;
		specular.xyz *= specular.xyz;
	#endif
	
#endif
