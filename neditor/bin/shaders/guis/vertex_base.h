/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base.h
 * Desc:    Gui base vertex shader
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

#ifdef BASE_WIREFRAME
	#include <core/shaders/common/vertex_base_wireframe.h>
#elif BASE_DEFERRED
	#include <core/shaders/common/vertex_base_deferred.h>
#elif BASE_AUXILIARY
	#include <core/shaders/common/vertex_base_auxiliary.h>
#elif BASE_AMBIENT
	#include <core/shaders/guis/vertex_base_ambient.h>
#elif BASE_LIGHT_SPOT
	#include <core/shaders/common/vertex_base_light_spot.h>
#elif BASE_LIGHT_OMNI
	#include <core/shaders/common/vertex_base_light_omni.h>
#elif BASE_LIGHT_PROJ
	#include <core/shaders/common/vertex_base_light_proj.h>
#elif BASE_LIGHT_WORLD
	#include <core/shaders/common/vertex_base_light_world.h>
#else
	#error unknown vertex shader
#endif
