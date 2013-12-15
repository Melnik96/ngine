/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_shading.h
 * Desc:    Base fragment shading shader
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

#ifndef __FRAGMENT_BASE_SHADING_H__
#define __FRAGMENT_BASE_SHADING_H__

/******************************************************************************\
*
* Environment light
*
\******************************************************************************/

/*
 */
half3 getEnvironment(half3 direction) {
	return s_light_coefficients[0].xyz -
		s_light_coefficients[1].xyz * direction.y +
		s_light_coefficients[2].xyz * direction.z +
		s_light_coefficients[3].xyz * direction.x -
		s_light_coefficients[4].xyz * (direction.x * direction.y) -
		s_light_coefficients[5].xyz * (direction.y * direction.z) +
		s_light_coefficients[7].xyz * (direction.z * direction.x) +
		s_light_coefficients[6].xyz * (direction.z * direction.z * 3.0f - 1.0f) +
		s_light_coefficients[8].xyz * (direction.x * direction.x - direction.y * direction.y);
}

/******************************************************************************\
*
* Fresnel term
*
\******************************************************************************/

/*
 */
half getFresnel(half3 normal,half3 camera_direction) {
	return saturate(s_material_fresnel.x + pow(saturate(1.0f - abs(dot(camera_direction,normal))),s_material_fresnel.z) * s_material_fresnel.y);
}

half getFresnelNormalize(half3 normal,float3 camera_direction) {
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	return saturate(s_material_fresnel.x + pow(saturate(1.0f - abs(dot(camera_direction,normal) * camera_direction_ilength)),s_material_fresnel.z) * s_material_fresnel.y);
}

/******************************************************************************\
*
* Attenuation
*
\******************************************************************************/

/*
 */
half getAttenuate(float4 light_direction) {
	half light_direction_length2 = dot(light_direction.xyz,light_direction.xyz);
	return getAttenuation(light_direction.w - light_direction_length2);
}

/******************************************************************************\
*
* Diffuse term
*
\******************************************************************************/

/*
 */
half3 getDiffuse(half3 diffuse,half3 normal,half3 light_direction) {
	return diffuse * (saturate(dot(light_direction,normal)) * s_material_shading.x);
}

half3 getDiffuseNormalize(half3 diffuse,half3 normal,float3 light_direction) {
	half light_direction_ilength = rsqrt(dot(light_direction,light_direction));
	return diffuse * (saturate(dot(light_direction,normal) * light_direction_ilength) * s_material_shading.x);
}

half3 getDiffuseNormalizeAttenuate(half3 diffuse,half3 normal,float4 light_direction) {
	half light_direction_length2 = dot(light_direction.xyz,light_direction.xyz);
	half light_direction_ilength = rsqrt(light_direction_length2);
	half attenuation = getAttenuation(light_direction.w - light_direction_length2);
	return diffuse * (saturate(dot(light_direction.xyz,normal) * light_direction_ilength) * attenuation * s_material_shading.x);
}

/*
 */
half3 getDiffuseRim(half3 diffuse,half3 normal,half3 light_direction) {
	half dot_light_normal = dot(light_direction,normal);
	return diffuse * (saturate(saturate(dot_light_normal) + smoothstep(s_material_phong_rim.x,1.0f,1.0f - abs(dot_light_normal)) * s_material_phong_rim.y) * s_material_shading.x);
}

half3 getDiffuseRimNormalize(half3 diffuse,half3 normal,float3 light_direction) {
	half light_direction_ilength = rsqrt(dot(light_direction,light_direction));
	half dot_light_normal = dot(light_direction,normal) * light_direction_ilength;
	return diffuse * (saturate(saturate(dot_light_normal) + smoothstep(s_material_phong_rim.x,1.0f,1.0f - abs(dot_light_normal)) * s_material_phong_rim.y) * s_material_shading.x);
}

/*
 */
half3 getDiffuseDeferred(half3 normal,half3 light_direction) {
	return s_light_color.xyz * (saturate(dot(light_direction.xyz,normal)) * s_material_shading.x);
}

/*
 */
half3 getDiffuseDeferredAmbient(half3 diffuse,half4 light) {
	return diffuse.xyz * light.xyz * s_material_shading.x;
}

/******************************************************************************\
*
* Specular term
*
\******************************************************************************/

/*
 */
half getSpecularPower(half x,half y) {
	return pow(saturate(x),max(y,1e-6f));
}

/*
 */
half3 getSpecular(half3 specular,half3 normal,half3 light_direction,half3 camera_direction) {
	return specular * (pow(saturate(dot(reflect(-light_direction,normal),camera_direction)),s_material_shading.z) * s_material_shading.y);
}

half3 getSpecularNormalize(half3 specular,half3 normal,half3 light_direction,float3 camera_direction) {
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	return specular * (pow(saturate(dot(reflect(-light_direction,normal),camera_direction) * camera_direction_ilength),s_material_shading.z) * s_material_shading.y);
}

half3 getSpecularFresnelNormalize(half3 specular,half3 normal,half3 light_direction,float3 camera_direction) {
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	half fresnel = saturate(s_material_fresnel.x + pow(saturate(1.0f - abs(dot(camera_direction,normal) * camera_direction_ilength)),s_material_fresnel.z) * s_material_fresnel.y);
	return specular * (pow(saturate(dot(reflect(-light_direction,normal),camera_direction) * camera_direction_ilength),s_material_shading.z) * s_material_shading.y * fresnel);
}

/*
 */
half3 getSpecular(half4 specular,half3 normal,half3 light_direction,half3 camera_direction) {
	return specular.xyz * (getSpecularPower(dot(reflect(-light_direction,normal),camera_direction),specular.w * s_material_shading.z) * s_material_shading.y);
}

half3 getSpecularNormalize(half4 specular,half3 normal,half3 light_direction,float3 camera_direction) {
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	return specular.xyz * (getSpecularPower(dot(reflect(-light_direction,normal),camera_direction) * camera_direction_ilength,specular.w * s_material_shading.z) * s_material_shading.y);
}

half3 getSpecularFresnelNormalize(half4 specular,half3 normal,half3 light_direction,float3 camera_direction) {
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	half fresnel = saturate(s_material_fresnel.x + pow(saturate(1.0f - abs(dot(camera_direction,normal) * camera_direction_ilength)),s_material_fresnel.z) * s_material_fresnel.y);
	return specular.xyz * (getSpecularPower(dot(reflect(-light_direction,normal),camera_direction) * camera_direction_ilength,specular.w * s_material_shading.z) * s_material_shading.y * fresnel);
}

/*
 */
half getSpecularDeferredNormalize(half specular,half3 normal,half3 light_direction,float3 camera_direction) {
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	return getSpecularPower(dot(reflect(-light_direction.xyz,normal),camera_direction) * camera_direction_ilength,specular * s_material_shading.z) * s_material_shading.y;
}

/******************************************************************************\
*
* Diffuse specular term
*
\******************************************************************************/

/*
 */
half3 getDiffuseSpecularNormalize(half3 diffuse,half3 specular,half3 normal,float3 light_direction,float3 camera_direction) {
	half light_direction_ilength = rsqrt(dot(light_direction,light_direction));
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	return diffuse * (saturate(dot(light_direction,normal) * light_direction_ilength) * s_material_shading.x) +
		specular * (pow(saturate(dot(reflect(-light_direction,normal),camera_direction) * light_direction_ilength * camera_direction_ilength),s_material_shading.z) * s_material_shading.y);
}

half3 getDiffuseSpecularFresnelNormalize(half3 diffuse,half3 specular,half3 normal,float3 light_direction,float3 camera_direction) {
	half light_direction_ilength = rsqrt(dot(light_direction,light_direction));
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	half fresnel = saturate(s_material_fresnel.x + pow(saturate(1.0f - abs(dot(camera_direction,normal) * camera_direction_ilength)),s_material_fresnel.z) * s_material_fresnel.y);
	return diffuse * (saturate(dot(light_direction,normal) * light_direction_ilength) * s_material_shading.x) +
		specular * (pow(saturate(dot(reflect(-light_direction,normal),camera_direction) * light_direction_ilength * camera_direction_ilength),s_material_shading.z) * s_material_shading.y * fresnel);
}

half3 getDiffuseSpecularNormalize(half3 diffuse,half4 specular,half3 normal,float3 light_direction,float3 camera_direction) {
	half light_direction_ilength = rsqrt(dot(light_direction,light_direction));
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	return diffuse * (saturate(dot(light_direction,normal) * light_direction_ilength) * s_material_shading.x) +
		specular.xyz * (getSpecularPower(dot(reflect(-light_direction,normal),camera_direction) * light_direction_ilength * camera_direction_ilength,specular.w * s_material_shading.z) * s_material_shading.y);
}

half3 getDiffuseSpecularFresnelNormalize(half3 diffuse,half4 specular,half3 normal,float3 light_direction,float3 camera_direction) {
	half light_direction_ilength = rsqrt(dot(light_direction,light_direction));
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	half fresnel = saturate(s_material_fresnel.x + pow(saturate(1.0f - abs(dot(camera_direction,normal) * camera_direction_ilength)),s_material_fresnel.z) * s_material_fresnel.y);
	return diffuse * (saturate(dot(light_direction,normal) * light_direction_ilength) * s_material_shading.x) +
		specular.xyz * (getSpecularPower(dot(reflect(-light_direction,normal),camera_direction) * light_direction_ilength * camera_direction_ilength,specular.w * s_material_shading.z) * s_material_shading.y * fresnel);
}

/*
 */
half3 getDiffuseRimSpecularNormalize(half3 diffuse,half4 specular,half3 normal,float3 light_direction,float3 camera_direction) {
	half light_direction_ilength = rsqrt(dot(light_direction,light_direction));
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	half dot_light_normal = dot(light_direction,normal) * light_direction_ilength;
	return diffuse * (saturate(saturate(dot_light_normal) + smoothstep(s_material_phong_rim.x,1.0f,1.0f - abs(dot_light_normal)) * s_material_phong_rim.y) * s_material_shading.x) +
		specular.xyz * (getSpecularPower(dot(reflect(-light_direction,normal),camera_direction) * light_direction_ilength * camera_direction_ilength,specular.w * s_material_shading.z) * s_material_shading.y);
}

half3 getDiffuseRimSpecularFresnelNormalize(half3 diffuse,half4 specular,half3 normal,float3 light_direction,float3 camera_direction) {
	half light_direction_ilength = rsqrt(dot(light_direction,light_direction));
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	half dot_light_normal = dot(light_direction,normal) * light_direction_ilength;
	half fresnel = saturate(s_material_fresnel.x + pow(saturate(1.0f - abs(dot(camera_direction,normal) * camera_direction_ilength)),s_material_fresnel.z) * s_material_fresnel.y);
	return diffuse * (saturate(saturate(dot_light_normal) + smoothstep(s_material_phong_rim.x,1.0f,1.0f - abs(dot_light_normal)) * s_material_phong_rim.y) * s_material_shading.x) +
		specular.xyz * (getSpecularPower(dot(reflect(-light_direction,normal),camera_direction) * light_direction_ilength * camera_direction_ilength,specular.w * s_material_shading.z) * s_material_shading.y * fresnel);
}

/*
 */
half3 getDiffuseSpecularDeferredAmbient(half3 diffuse,half3 specular,half4 light) {
	return (diffuse.xyz * s_material_shading.x + specular * (s_material_shading.y * light.w)) * light.xyz;
}

/******************************************************************************\
*
* Diffuse specular attenuation term
*
\******************************************************************************/

/*
 */
half3 getDiffuseSpecularNormalizeAttenuate(half3 diffuse,half3 specular,half3 normal,float4 light_direction,float3 camera_direction) {
	half light_direction_length2 = dot(light_direction.xyz,light_direction.xyz);
	half light_direction_ilength = rsqrt(light_direction_length2);
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	half attenuation = getAttenuation(light_direction.w - light_direction_length2);
	return diffuse * (saturate(dot(light_direction.xyz,normal) * light_direction_ilength) * attenuation * s_material_shading.x) +
		specular * (pow(saturate(dot(reflect(-light_direction.xyz,normal),camera_direction) * light_direction_ilength * camera_direction_ilength),s_material_shading.z) * attenuation * s_material_shading.y);
}

half3 getDiffuseSpecularFresnelNormalizeAttenuate(half3 diffuse,half3 specular,half3 normal,float4 light_direction,float3 camera_direction) {
	half light_direction_length2 = dot(light_direction.xyz,light_direction.xyz);
	half light_direction_ilength = rsqrt(light_direction_length2);
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	half fresnel = saturate(s_material_fresnel.x + pow(saturate(1.0f - abs(dot(camera_direction,normal) * camera_direction_ilength)),s_material_fresnel.z) * s_material_fresnel.y);
	half attenuation = getAttenuation(light_direction.w - light_direction_length2);
	return diffuse * (saturate(dot(light_direction.xyz,normal) * light_direction_ilength) * attenuation * s_material_shading.x) +
		specular * (pow(saturate(dot(reflect(-light_direction.xyz,normal),camera_direction) * light_direction_ilength * camera_direction_ilength),s_material_shading.z) * attenuation * s_material_shading.y * fresnel);
}

half3 getDiffuseSpecularNormalizeAttenuate(half3 diffuse,half4 specular,half3 normal,float4 light_direction,float3 camera_direction) {
	half light_direction_length2 = dot(light_direction.xyz,light_direction.xyz);
	half light_direction_ilength = rsqrt(light_direction_length2);
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	half attenuation = getAttenuation(light_direction.w - light_direction_length2);
	return diffuse * (saturate(dot(light_direction.xyz,normal) * light_direction_ilength) * attenuation * s_material_shading.x) +
		specular.xyz * (getSpecularPower(dot(reflect(-light_direction.xyz,normal),camera_direction) * light_direction_ilength * camera_direction_ilength,specular.w * s_material_shading.z) * attenuation * s_material_shading.y);
}

half3 getDiffuseSpecularFresnelNormalizeAttenuate(half3 diffuse,half4 specular,half3 normal,float4 light_direction,float3 camera_direction) {
	half light_direction_length2 = dot(light_direction.xyz,light_direction.xyz);
	half light_direction_ilength = rsqrt(light_direction_length2);
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	half fresnel = saturate(s_material_fresnel.x + pow(saturate(1.0f - abs(dot(camera_direction,normal) * camera_direction_ilength)),s_material_fresnel.z) * s_material_fresnel.y);
	half attenuation = getAttenuation(light_direction.w - light_direction_length2);
	return diffuse * (saturate(dot(light_direction.xyz,normal) * light_direction_ilength) * attenuation * s_material_shading.x) +
		specular.xyz * (getSpecularPower(dot(reflect(-light_direction.xyz,normal),camera_direction) * light_direction_ilength * camera_direction_ilength,specular.w * s_material_shading.z) * attenuation * s_material_shading.y * fresnel);
}

/*
 */
half3 getDiffuseRimSpecularNormalizeAttenuate(half3 diffuse,half4 specular,half3 normal,float4 light_direction,float3 camera_direction) {
	half light_direction_length2 = dot(light_direction.xyz,light_direction.xyz);
	half light_direction_ilength = rsqrt(light_direction_length2);
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	half dot_light_normal = dot(light_direction.xyz,normal) * light_direction_ilength;
	half attenuation = getAttenuation(light_direction.w - light_direction_length2);
	return diffuse * (saturate(saturate(dot_light_normal) + smoothstep(s_material_phong_rim.x,1.0f,1.0f - abs(dot_light_normal)) * s_material_phong_rim.y) * attenuation * s_material_shading.x) +
		specular.xyz * (getSpecularPower(dot(reflect(-light_direction.xyz,normal),camera_direction) * light_direction_ilength * camera_direction_ilength,specular.w * s_material_shading.z) * attenuation * s_material_shading.y);
}

half3 getDiffuseRimSpecularFresnelNormalizeAttenuate(half3 diffuse,half4 specular,half3 normal,float4 light_direction,float3 camera_direction) {
	half light_direction_length2 = dot(light_direction.xyz,light_direction.xyz);
	half light_direction_ilength = rsqrt(light_direction_length2);
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	half dot_light_normal = dot(light_direction.xyz,normal) * light_direction_ilength;
	half fresnel = saturate(s_material_fresnel.x + pow(saturate(1.0f - abs(dot(camera_direction,normal) * camera_direction_ilength)),s_material_fresnel.z) * s_material_fresnel.y);
	half attenuation = getAttenuation(light_direction.w - light_direction_length2);
	return diffuse * (saturate(saturate(dot_light_normal) + smoothstep(s_material_phong_rim.x,1.0f,1.0f - abs(dot_light_normal)) * s_material_phong_rim.y) * attenuation * s_material_shading.x) +
		specular.xyz * (getSpecularPower(dot(reflect(-light_direction.xyz,normal),camera_direction) * light_direction_ilength * camera_direction_ilength,specular.w * s_material_shading.z) * attenuation * s_material_shading.y * fresnel);
}

/*
 */
half4 getDiffuseSpecularDeferredNormalizeAttenuate(half specular,half3 normal,float4 light_direction,float3 camera_direction) {
	half light_direction_length2 = dot(light_direction.xyz,light_direction.xyz);
	half light_direction_ilength = rsqrt(light_direction_length2);
	half camera_direction_ilength = rsqrt(dot(camera_direction,camera_direction));
	half attenuation = getAttenuation(light_direction.w - light_direction_length2);
	return half4(s_light_color.xyz * (saturate(dot(light_direction.xyz,normal) * light_direction_ilength) * attenuation * s_material_shading.x),
		getSpecularPower(dot(reflect(-light_direction.xyz,normal),camera_direction) * light_direction_ilength * camera_direction_ilength,specular * s_material_shading.z) * attenuation * s_material_shading.y);
}

#endif /* __FRAGMENT_BASE_SHADING_H__ */
