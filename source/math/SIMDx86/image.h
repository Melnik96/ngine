/*
	image.h -- SIMDx86 Image Library
	Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/


#ifndef _SIMDX86_IMAGE_H
#define _SIMDX86_IMAGE_H


#ifdef __cplusplus
extern "C" {
#endif

void SIMDx86Image_SaturatedSum(unsigned char* pDest, unsigned char* pSrc, unsigned int NumBytes);
void SIMDx86Image_SaturatedSumOf(unsigned char* pOut, const unsigned char* pSrc1, const unsigned char* pSrc2, unsigned int NumBytes);

#ifdef __cplusplus
}
#endif


#endif

