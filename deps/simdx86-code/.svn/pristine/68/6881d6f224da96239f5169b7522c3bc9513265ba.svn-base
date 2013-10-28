/*
	codemod_win32 -- Code Modification (Win32)
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#include <windows.h>

int SIMDx86Code_MakeReadWriteExec(void* pFunctionAddress, unsigned int NumBytes)
{
	DWORD oldprot;

	/* VirtualProtect() returns zero if it fails for any reason */
	return (VirtualProtect(pFunctionAddress, NumBytes, PAGE_EXECUTE_READWRITE, &oldprot) != 0);
}

int SIMDx86Code_MakeReadExec(void* pFunctionAddress, unsigned int NumBytes)
{
	DWORD oldprot;

	/* VirtualProtect() returns zero if it fails for any reason */
	return (VirtualProtect(pFunctionAddress, NumBytes, PAGE_EXECUTE_READ, &oldprot) != 0);
}

