/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_fade.shader
 * Desc:    Render fade shader
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

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform half color;

/*
 */
void main() {
	
	gl_FragData[0] = half4(color);
	gl_FragData[1] = half4(color);
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_OUT {
	float4 color_0 : COLOR0;
	float4 color_1 : COLOR1;
};

half color;

/*
 */
FRAGMENT_OUT main() {
	
	FRAGMENT_OUT OUT;
	
	OUT.color_0 = color;
	OUT.color_1 = color;
	
	return OUT;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
};

struct FRAGMENT_OUT {
	float3 color_0 : SV_TARGET0;
	float3 color_1 : SV_TARGET1;
};

float color;

/*
 */
FRAGMENT_OUT main(FRAGMENT_IN IN) {
	
	FRAGMENT_OUT OUT;
	
	OUT.color_0 = color;
	OUT.color_1 = color;
	
	return OUT;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

uniform half color;

/*
 */
half4 main() : COLOR {
	
	return color;
}

#endif
