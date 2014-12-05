/*
	codemod.h -- Code Modification
	Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#ifdef __cplusplus
extern "C" {
#endif


extern int SIMDx86Code_MakeReadWriteExec(void* pFunctionAddress, unsigned int Bytes);
extern int SIMDx86Code_MakeReadExec(void* pFunctionAddress, unsigned int Bytes);



#ifdef __cplusplus
}
#endif
