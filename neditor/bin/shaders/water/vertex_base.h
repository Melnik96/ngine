/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base.h
 * Desc:    Water base vertex shader
 * Version: 1.06
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

#ifdef BASE_WIREFRAME
	#include <core/shaders/common/vertex_base_wireframe.h>
#elif SURFACE_DEFERRED
	#include <core/shaders/water/vertex_surface_deferred.h>
#elif SURFACE_AUXILIARY
	#include <core/shaders/water/vertex_surface_auxiliary.h>
#elif SURFACE_REFRACTION
	#include <core/shaders/water/vertex_surface_refraction.h>
#elif SURFACE_AMBIENT
	#include <core/shaders/water/vertex_surface_ambient.h>
#elif SURFACE_LIGHT_SPOT
	#include <core/shaders/water/vertex_surface_light_spot.h>
#elif SURFACE_LIGHT_OMNI
	#include <core/shaders/water/vertex_surface_light_omni.h>
#elif SURFACE_LIGHT_PROJ
	#include <core/shaders/water/vertex_surface_light_proj.h>
#elif SURFACE_LIGHT_WORLD
	#include <core/shaders/water/vertex_surface_light_world.h>
#elif VOLUME_WIREFRAME
	#include <core/shaders/water/vertex_volume_wireframe.h>
#elif VOLUME_AMBIENT
	#include <core/shaders/water/vertex_volume_ambient.h>
#elif VOLUME_LIGHT_WORLD
	#include <core/shaders/water/vertex_volume_light_world.h>
#else
	#error unknown vertex shader
#endif
