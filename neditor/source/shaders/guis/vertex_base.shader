/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    vertex_base.shader
 * Desc:    Gui base shader
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

#include <core/shaders/common/vertex_base.h>
#include <core/shaders/guis/vertex_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

#ifdef GUI_MESH
	
	attribute float4 s_attribute_0;
	attribute float4 s_attribute_1;
	attribute float4 s_attribute_2;
	attribute float4 s_attribute_3;
	
	/*
	 */
	void main() {
		
		float4 vertex = float4(s_attribute_0.x,s_attribute_0.y,s_attribute_2.w,1.0f);
		vertex.xyz = float3(dot(s_transform[0],vertex),dot(s_transform[1],vertex),dot(s_transform[2],vertex));
		
		float3 normal = normalize(float3(dot(s_transform[0].xyz,s_attribute_2.xyz),dot(s_transform[1].xyz,s_attribute_2.xyz),dot(s_transform[2].xyz,s_attribute_2.xyz)));
		float3 tangent = normalize(float3(dot(s_transform[0].xyz,s_attribute_3.xyz),dot(s_transform[1].xyz,s_attribute_3.xyz),dot(s_transform[2].xyz,s_attribute_3.xyz)));
		float3 binormal = cross(normal,tangent) * s_attribute_3.w;
		
		float4 texcoord = float4(s_attribute_1.xyx,1.0f - s_attribute_1.y);
		
		float4 color = float4(1.0f);
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
			bound_sphere.xyz = float3(dot(s_transform[0],bound_sphere),dot(s_transform[1],bound_sphere),dot(s_transform[2],bound_sphere));
			bound_sphere.w = s_surface_bound_sphere.w * length(float3(s_transform[0].x,s_transform[1].x,s_transform[2].x));
		#endif
		
		#include <core/shaders/guis/vertex_base.h>
	}
	
#else
	
	attribute float4 s_attribute_0;
	attribute float4 s_attribute_1;
	attribute float4 s_attribute_2;
	
	uniform float4 s_gui_transform[3];
	
	/*
	 */
	void main() {
		
		float4 vertex = float4(dot(s_gui_transform[0],s_attribute_0),dot(s_gui_transform[1],s_attribute_0),dot(s_gui_transform[2],s_attribute_0),1.0f);
		
		float3 normal = -normalize(float3(s_gui_transform[0].z,s_gui_transform[1].z,s_gui_transform[2].z));
		float3 tangent = normalize(float3(s_gui_transform[0].x,s_gui_transform[1].x,s_gui_transform[2].x));
		float3 binormal = normalize(float3(s_gui_transform[0].y,s_gui_transform[1].y,s_gui_transform[2].y));
		
		float4 texcoord = s_attribute_1.xyxy;
		
		float4 color = s_attribute_2;
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
			bound_sphere.xyz = float3(dot(s_transform[0],bound_sphere),dot(s_transform[1],bound_sphere),dot(s_transform[2],bound_sphere));
			bound_sphere.w = s_surface_bound_sphere.w * length(float3(s_transform[0].x,s_transform[1].x,s_transform[2].x));
		#endif
		
		#include <core/shaders/guis/vertex_base.h>
	}
	
#endif

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

#ifdef GUI_MESH
	
	struct VERTEX_IN {
		float4 position : POSITION;
		float4 texcoord_0 : TEXCOORD0;
		float4 texcoord_1 : TEXCOORD1;
		float4 texcoord_2 : TEXCOORD2;
	};
	
	/*
	 */
	VERTEX_OUT main(VERTEX_IN IN) {
		
		VERTEX_OUT OUT;
		
		float4 vertex = float4(IN.position.x,IN.position.y,IN.texcoord_1.w,1.0f);
		vertex.xyz = float3(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]));
		
		float3 normal = normalize(float3(dot(s_transform[0].xyz,IN.texcoord_1.xyz),dot(s_transform[1].xyz,IN.texcoord_1.xyz),dot(s_transform[2].xyz,IN.texcoord_1.xyz)));
		float3 tangent = normalize(float3(dot(s_transform[0].xyz,IN.texcoord_2.xyz),dot(s_transform[1].xyz,IN.texcoord_2.xyz),dot(s_transform[2].xyz,IN.texcoord_2.xyz)));
		float3 binormal = cross(normal,tangent) * IN.texcoord_2.w;
		
		float4 texcoord = IN.texcoord_0;
		
		float4 color = 1.0f;
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
			bound_sphere.xyz = float3(dot(s_transform[0],bound_sphere),dot(s_transform[1],bound_sphere),dot(s_transform[2],bound_sphere));
			bound_sphere.w = s_surface_bound_sphere.w * length(float3(s_transform[0].x,s_transform[1].x,s_transform[2].x));
		#endif
		
		#include <core/shaders/guis/vertex_base.h>
		
		return OUT;
	}
	
#else
	
	struct VERTEX_IN {
		float4 position : POSITION;
		float4 texcoord : TEXCOORD0;
		float4 color : COLOR0;
	};
	
	float4 s_gui_transform[3];
	
	/*
	 */
	VERTEX_OUT main(VERTEX_IN IN) {
		
		VERTEX_OUT OUT;
		
		float4 vertex = float4(dot(IN.position,s_gui_transform[0]),dot(IN.position,s_gui_transform[1]),dot(IN.position,s_gui_transform[2]),1.0f);
		
		float3 normal = -normalize(float3(s_gui_transform[0].z,s_gui_transform[1].z,s_gui_transform[2].z));
		float3 tangent = normalize(float3(s_gui_transform[0].x,s_gui_transform[1].x,s_gui_transform[2].x));
		float3 binormal = normalize(float3(s_gui_transform[0].y,s_gui_transform[1].y,s_gui_transform[2].y));
		
		float4 texcoord = IN.texcoord;
		
		float4 color = IN.color;
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
			bound_sphere.xyz = float3(dot(s_transform[0],bound_sphere),dot(s_transform[1],bound_sphere),dot(s_transform[2],bound_sphere));
			bound_sphere.w = s_surface_bound_sphere.w * length(float3(s_transform[0].x,s_transform[1].x,s_transform[2].x));
		#endif
		
		#include <core/shaders/guis/vertex_base.h>
		
		return OUT;
	}
	
#endif

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

#ifdef GUI_MESH
	
	struct VERTEX_IN {
		float4 position : POSITION;
		float4 texcoord_0 : TEXCOORD0;
		float4 texcoord_1 : TEXCOORD1;
		float4 texcoord_2 : TEXCOORD2;
	};
	
	/*
	 */
	VERTEX_OUT main(VERTEX_IN IN) {
		
		VERTEX_OUT OUT;
		
		float4 vertex = float4(IN.position.x,IN.position.y,IN.texcoord_1.w,1.0f);
		vertex.xyz = float3(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]));
		
		float3 normal = normalize(float3(dot(s_transform[0].xyz,IN.texcoord_1.xyz),dot(s_transform[1].xyz,IN.texcoord_1.xyz),dot(s_transform[2].xyz,IN.texcoord_1.xyz)));
		float3 tangent = normalize(float3(dot(s_transform[0].xyz,IN.texcoord_2.xyz),dot(s_transform[1].xyz,IN.texcoord_2.xyz),dot(s_transform[2].xyz,IN.texcoord_2.xyz)));
		float3 binormal = cross(normal,tangent) * IN.texcoord_2.w;
		
		float4 texcoord = IN.texcoord_0;
		
		float4 color = 1.0f;
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
			bound_sphere.xyz = float3(dot(s_transform[0],bound_sphere),dot(s_transform[1],bound_sphere),dot(s_transform[2],bound_sphere));
			bound_sphere.w = s_surface_bound_sphere.w * length(float3(s_transform[0].x,s_transform[1].x,s_transform[2].x));
		#endif
		
		#include <core/shaders/guis/vertex_base.h>
		
		return OUT;
	}
	
#else
	
	struct VERTEX_IN {
		float4 position : POSITION;
		float4 texcoord : TEXCOORD0;
		float4 color : COLOR0;
	};
	
	cbuffer shader_parameters {
		float4 s_gui_transform[3];
	};
	
	/*
	 */
	VERTEX_OUT main(VERTEX_IN IN) {
		
		VERTEX_OUT OUT;
		
		float4 vertex = float4(dot(IN.position,s_gui_transform[0]),dot(IN.position,s_gui_transform[1]),dot(IN.position,s_gui_transform[2]),1.0f);
		
		float3 normal = -normalize(float3(s_gui_transform[0].z,s_gui_transform[1].z,s_gui_transform[2].z));
		float3 tangent = normalize(float3(s_gui_transform[0].x,s_gui_transform[1].x,s_gui_transform[2].x));
		float3 binormal = normalize(float3(s_gui_transform[0].y,s_gui_transform[1].y,s_gui_transform[2].y));
		
		float4 texcoord = IN.texcoord;
		
		float4 color = IN.color;
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
			bound_sphere.xyz = float3(dot(s_transform[0],bound_sphere),dot(s_transform[1],bound_sphere),dot(s_transform[2],bound_sphere));
			bound_sphere.w = s_surface_bound_sphere.w * length(float3(s_transform[0].x,s_transform[1].x,s_transform[2].x));
		#endif
		
		#include <core/shaders/guis/vertex_base.h>
		
		return OUT;
	}
	
#endif

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

#ifdef GUI_MESH
	
	struct VERTEX_IN {
		float4 position : ATTR0;
		float4 texcoord_0 : ATTR1;
		float4 texcoord_1 : ATTR2;
		float4 texcoord_2 : ATTR3;
	};
	
	/*
	 */
	VERTEX_OUT main(VERTEX_IN IN) {
		
		VERTEX_OUT OUT;
		
		float4 vertex = float4(IN.position.x,IN.position.y,IN.texcoord_1.w,1.0f);
		vertex.xyz = float3(dot(vertex,s_transform[0]),dot(vertex,s_transform[1]),dot(vertex,s_transform[2]));
		
		float3 normal = normalize(float3(dot(s_transform[0].xyz,IN.texcoord_1.xyz),dot(s_transform[1].xyz,IN.texcoord_1.xyz),dot(s_transform[2].xyz,IN.texcoord_1.xyz)));
		float3 tangent = normalize(float3(dot(s_transform[0].xyz,IN.texcoord_2.xyz),dot(s_transform[1].xyz,IN.texcoord_2.xyz),dot(s_transform[2].xyz,IN.texcoord_2.xyz)));
		float3 binormal = cross(normal,tangent) * IN.texcoord_2.w;
		
		float4 texcoord = IN.texcoord_0;
		
		float4 color = 1.0f;
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
			bound_sphere.xyz = float3(dot(s_transform[0],bound_sphere),dot(s_transform[1],bound_sphere),dot(s_transform[2],bound_sphere));
			bound_sphere.w = s_surface_bound_sphere.w * length(float3(s_transform[0].x,s_transform[1].x,s_transform[2].x));
		#endif
		
		#include <core/shaders/guis/vertex_base.h>
		
		return OUT;
	}
	
#else
	
	struct VERTEX_IN {
		float4 position : ATTR0;
		float4 texcoord : ATTR1;
		float4 color : ATTR2;
	};
	
	uniform float4 s_gui_transform[3];
	
	/*
	 */
	VERTEX_OUT main(VERTEX_IN IN) {
		
		VERTEX_OUT OUT;
		
		float4 vertex = float4(dot(IN.position,s_gui_transform[0]),dot(IN.position,s_gui_transform[1]),dot(IN.position,s_gui_transform[2]),1.0f);
		
		float3 normal = -normalize(float3(s_gui_transform[0].z,s_gui_transform[1].z,s_gui_transform[2].z));
		float3 tangent = normalize(float3(s_gui_transform[0].x,s_gui_transform[1].x,s_gui_transform[2].x));
		float3 binormal = normalize(float3(s_gui_transform[0].y,s_gui_transform[1].y,s_gui_transform[2].y));
		
		float4 texcoord = IN.texcoord;
		
		float4 color = IN.color;
		
		#ifdef USE_ALPHA_FADE && ALPHA_FADE
			float4 bound_sphere = float4(s_surface_bound_sphere.xyz,1.0f);
			bound_sphere.xyz = float3(dot(s_transform[0],bound_sphere),dot(s_transform[1],bound_sphere),dot(s_transform[2],bound_sphere));
			bound_sphere.w = s_surface_bound_sphere.w * length(float3(s_transform[0].x,s_transform[1].x,s_transform[2].x));
		#endif
		
		#include <core/shaders/guis/vertex_base.h>
		
		return OUT;
	}
	
#endif

#endif
