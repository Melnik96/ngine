/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_base_auxiliary.shader
 * Desc:    Terrain base auxiliary shader
 * Version: 1.01
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

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform half4 auxiliary_color;

/*
 */
void main() {
	
	gl_FragColor = auxiliary_color;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
};

half4 auxiliary_color;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	return auxiliary_color;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float4 texcoord_0 : TEXCOORD0;
};

cbuffer shader_parameters {
	float4 auxiliary_color;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	return auxiliary_color;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

struct FRAGMENT_IN {
	float4 texcoord_0 : TEXCOORD0;
};

uniform half4 auxiliary_color;

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	return auxiliary_color;
}

#endif
