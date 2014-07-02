/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    geometry_base.h
 * Desc:    Base geometry shader
 * Version: 1.04
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

#ifndef __GEOMETRY_BASE_H__
#define __GEOMETRY_BASE_H__

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

#ifdef USE_GEOMETRY_SHADER

##version 150
##extension GL_ARB_geometry_shader4 : enable

/*
 */
#ifdef USE_EXT_CG_SHADER
	#undef USE_EXT_CG_SHADER
#endif

/*
 */
#include <core/shaders/common/common_base.h>

/* compatibility
 */
out float4 gl_TexCoord[8];

/* vertex transformation
 */
float4 getPosition(float4 vertex) {
	vertex.xyz -= s_camera_offset;
	return s_modelviewprojection * vertex;
}

#endif

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

#ifdef USE_GEOMETRY_SHADER

/*
 */
#include <core/shaders/common/common_base.h>

/* vertex transformation
 */
float4 getPosition(float4 vertex) {
	vertex.xyz -= s_camera_offset;
	return mul(s_modelviewprojection,vertex);
}

#endif

#endif

#endif /* __GEOMETRY_BASE_H__ */
