/* Copyright (C) 2005-2010, Unigine Corp. All rights reserved.
 *
 * File:    fragment_antialisaing_sample.shader
 * Desc:    Render antialiasing sample shader
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

/* s_texture_0 is screen texture
 * s_texture_1 is deferred depth texture
 */

#include <core/shaders/common/fragment_base.h>

/******************************************************************************\
*
* OpenGL
*
\******************************************************************************/

#ifdef OPENGL

uniform sampler2D s_texture_0;
uniform SAMPLER_2DMS s_texture_1;

/*
 */
void main() {
	
	half4 color = texture2D(s_texture_0,gl_TexCoord[0].xy);
	
	half depth_0 = getDeferredDepth(texture2DDeferredNorm(s_texture_1,gl_TexCoord[1].xy));
	half depth_1 = getDeferredDepth(texture2DDeferredNorm(s_texture_1,gl_TexCoord[1].zw));
	half depth_2 = getDeferredDepth(texture2DDeferredNorm(s_texture_1,gl_TexCoord[2].xy));
	half depth_3 = getDeferredDepth(texture2DDeferredNorm(s_texture_1,gl_TexCoord[2].zw));
	
	if(abs(depth_0 - depth_1) > 1e-4f && abs(depth_2 - depth_3) > 1e-4f) {
		color += texture2D(s_texture_0,gl_TexCoord[1].xy);
		color += texture2D(s_texture_0,gl_TexCoord[1].zw);
		color += texture2D(s_texture_0,gl_TexCoord[2].xy);
		color += texture2D(s_texture_0,gl_TexCoord[2].zw);
		color *= (1.0f / 5.0f);
	}
	
	gl_FragColor = color;
}

/******************************************************************************\
*
* Direct3D9
*
\******************************************************************************/

#elif DIRECT3D9

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 color = tex2D(s_texture_0,IN.texcoord_0);
	
	half depth_0 = getDeferredDepth(tex2D(s_texture_1,IN.texcoord_1.xy));
	half depth_1 = getDeferredDepth(tex2D(s_texture_1,IN.texcoord_1.zw));
	half depth_2 = getDeferredDepth(tex2D(s_texture_1,IN.texcoord_2.xy));
	half depth_3 = getDeferredDepth(tex2D(s_texture_1,IN.texcoord_2.zw));
	
	[branch] if(abs(depth_0 - depth_1) > 1e-4f && abs(depth_2 - depth_3) > 1e-4f) {
		color += tex2Dlod(s_texture_0,half4(IN.texcoord_1.xy,0.0f,0.0f));
		color += tex2Dlod(s_texture_0,half4(IN.texcoord_1.zw,0.0f,0.0f));
		color += tex2Dlod(s_texture_0,half4(IN.texcoord_2.xy,0.0f,0.0f));
		color += tex2Dlod(s_texture_0,half4(IN.texcoord_2.zw,0.0f,0.0f));
		color *= (1.0f / 5.0f);
	}
	
	return color;
}

/******************************************************************************\
*
* Direct3D10/Direct3D11
*
\******************************************************************************/

#elif DIRECT3D10 || DIRECT3D11

Texture2D s_texture_0 : register(t0);
TEXTURE_2DMS s_texture_1 : register(t1);

struct FRAGMENT_IN {
	float4 position : SV_POSITION;
	float2 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
};

/*
 */
float4 main(FRAGMENT_IN IN) : SV_TARGET {
	
	half4 color = s_texture_0.Sample(s_sampler_0,IN.texcoord_0);
	
	half depth_0 = getDeferredDepth(texture2DDeferredNorm(s_texture_1,s_sampler_1,IN.texcoord_1.xy));
	half depth_1 = getDeferredDepth(texture2DDeferredNorm(s_texture_1,s_sampler_1,IN.texcoord_1.zw));
	half depth_2 = getDeferredDepth(texture2DDeferredNorm(s_texture_1,s_sampler_1,IN.texcoord_2.xy));
	half depth_3 = getDeferredDepth(texture2DDeferredNorm(s_texture_1,s_sampler_1,IN.texcoord_2.zw));
	
	[branch] if(abs(depth_0 - depth_1) > 1e-4f && abs(depth_2 - depth_3) > 1e-4f) {
		color += s_texture_0.SampleLevel(s_sampler_0,IN.texcoord_1.xy,0.0f);
		color += s_texture_0.SampleLevel(s_sampler_0,IN.texcoord_1.zw,0.0f);
		color += s_texture_0.SampleLevel(s_sampler_0,IN.texcoord_2.xy,0.0f);
		color += s_texture_0.SampleLevel(s_sampler_0,IN.texcoord_2.zw,0.0f);
		color *= (1.0f / 5.0f);
	}
	
	return color;
}

/******************************************************************************\
*
* PlayStation3
*
\******************************************************************************/

#elif PLAYSTATION3

##pragma disablepc all

uniform sampler2D s_texture_0 : TEXUNIT0;
uniform sampler2D s_texture_1 : TEXUNIT1;

struct FRAGMENT_IN {
	float2 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
	float4 texcoord_2 : TEXCOORD2;
};

/*
 */
half4 main(FRAGMENT_IN IN) : COLOR {
	
	half4 color = h4tex2D(s_texture_0,IN.texcoord_0);
	
	half depth_0 = getDeferredDepth(h4tex2D(s_texture_1,IN.texcoord_1.xy));
	half depth_1 = getDeferredDepth(h4tex2D(s_texture_1,IN.texcoord_1.zw));
	half depth_2 = getDeferredDepth(h4tex2D(s_texture_1,IN.texcoord_2.xy));
	half depth_3 = getDeferredDepth(h4tex2D(s_texture_1,IN.texcoord_2.zw));
	
	[branch] if(abs(depth_0 - depth_1) > 1e-4f && abs(depth_2 - depth_3) > 1e-4f) {
		color += h4tex2D(s_texture_0,IN.texcoord_1.xy);
		color += h4tex2D(s_texture_0,IN.texcoord_1.zw);
		color += h4tex2D(s_texture_0,IN.texcoord_2.xy);
		color += h4tex2D(s_texture_0,IN.texcoord_2.zw);
		color *= (1.0f / 5.0f);
	}
	
	return color;
}

#endif
