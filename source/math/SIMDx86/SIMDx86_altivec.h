/*
	SIMDx86_altivec.h -- AltiVec helper functions
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	AltiVec code written by Konstantinos Margaritis
	Under LGPL License
	Part of SIMDx86 Project
*/

#ifndef _SIMDX86_ALTIVEC_H
#define _SIMDX86_ALTIVEC_H

//	y = vec_madd(vec_nmsub(vec,vec_madd(y,y,_0),v1),vec_madd(y,v05,_0),y);		\
//	y = vec_madd(vec_nmsub(vec,vec_madd(y,y,_0),v1),vec_madd(y,v05,_0),y);		\
//	inv = vec_sel(vec_madd(vec,y,_0),_0,vec_cmpeq(vec,_0));				\

#define SPLAT_VECTOR(v, vs)				\
{							\
	vec_st(vs, 0, (float *)v);			\
}

#define SPLAT_MATRIX(m, vs)				\
{							\
	vec_st(vs, 0, (float *)m);			\
	vec_st(vs, 16, (float *)m);			\
	vec_st(vs, 32, (float *)m);			\
	vec_st(vs, 48, (float *)m);			\
}

#define LOAD_VECTOR(vr, vs)				\
{							\
	vr = vec_ld(0, (float *)vs);			\
}

#define STORE_VECTOR(vr, vs)				\
{							\
	vec_st(vr,  0, (float *)vs);			\
}

#define LOAD_MATRIX(m, vm1, vm2, vm3, vm4)		\
{							\
	vm1 = vec_ld(0,  (float *)m);			\
	vm2 = vec_ld(16, (float *)m);			\
	vm3 = vec_ld(32, (float *)m);			\
	vm4 = vec_ld(48, (float *)m);			\
}

#define STORE_MATRIX(m, vm1, vm2, vm3, vm4)		\
{							\
	vec_st(vm1,  0, (float *)m);			\
	vec_st(vm2, 16, (float *)m);			\
	vec_st(vm3, 32, (float *)m);			\
	vec_st(vm4, 48, (float *)m);			\
}

#endif
