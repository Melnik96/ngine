; getisa_x86.asm -- x86 specific ISA reporting
; Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

%include "SIMDx86asm.inc"

EXPORT_SYMBOL(SIMDx86_GetCPUSupportedISA)

section .bss
LocalISA:
	resd	1

section .text

BEGIN_SYMBOL(SIMDx86_GetCPUSupportedISA)
	;First, check for CPUID bit capability

	pushfd			;save eflags on stack
	pop eax			;pop into eax...
	mov ecx, eax	;and save into ecx

	xor eax, 0x200000	;Attempt to toggle the ID bit (Only possible if CPU supports CPUID)
	push eax			;Place new toggled eflags on stack...
	popfd				;and back into CPU 

	pushfd				;save eflags *back* onto the stack						
	pop edx				;and get into edx
	push ecx			;Place original eflags back onto stack...
	popfd				;and back into the CPU
	xor eax, edx		;XOR the toggled with the newly saved -- should be zero
	jz HasCPUID			;No CPUID supported (386, 486)

	;Processor cannot do CPUID (386, some 486)
	mov eax, SIMDX86ISA_BIT(SIMDX86ISA_USE_GENERIC)
	ret

	HasCPUID:
	
	push ebx	;save ebx as it is non-volatile according to ABI
	
	;Initialize the CPU ISA bits to default (SIMDX86ISA_USE_GENERIC)
	mov dword [LocalISA], SIMDX86ISA_BIT(SIMDX86ISA_USE_GENERIC)
	
	mov eax, 0x80000000		;Load eax with the query value
	cpuid					;Get highest supported value (destroys eax)
	
	cmp eax, 0x80000000		;Check if eax is still the same (i.e. no higher function)
	jbe TryStdCPUFeatures	;Cannot access extended functions -> no 3DNow!
	
	mov eax, 0x80000001		;Load eax with the query value
	cpuid					;Get extended processor features (destroys eax, edx)

	;=====================
	;Detect 3DNow Plus (and MMX Plus), aka Enhanced 3DNow!
	;=====================

	push edx				;Save value of edx
	and edx,0x40400000		;Mask bit 30 and 22 (3DNow!+ bit and MMX+ bit -- must have both)
	cmp edx,0x40400000		;Make sure *both* bits are set ('test' instruction with 'jz' can fail)
	pop edx					;Restore
	jz Try3DNow				
	or dword [LocalISA], SIMDX86ISA_BIT(SIMDX86ISA_USE_3DNOWPLUS)

	;=====================
	;Detect 3DNow
	;=====================
	Try3DNow:
	test edx, 0x80000000	;Test bit 31 (3DNow! bit)
	jz TryStdCPUFeatures	;If ZF is set, then 3DNow! isn't supported
	or dword [LocalISA], SIMDX86ISA_BIT(SIMDX86ISA_USE_3DNOW)
	
	
	
	TryStdCPUFeatures:
	
	mov eax, 0	;Get highest query for eax
	cpuid		;perform query (destroys eax, ebx, ecx, edx)
	
	cmp eax,0	;check if eax is still zero (i.e. cannot read processor features)
	jz NoStdCPUFeatures
	
	mov eax, 1	;Standard processor features
	cpuid		;perform query (destroys eax, edx)
	
	;=====================
	;Detect MMX
	;=====================
	test edx, 0x800000	;Test bit 23 (MMX bit)
	jz TrySSSE3
	or dword [LocalISA], SIMDX86ISA_BIT(SIMDX86ISA_USE_MMX)

	;=====================
	;Detect SSSE3 (Supplimental SSE3)
	;=====================
	TrySSSE3:
	test ecx, 0x200		;Test bit 9 of ecx (SSSE3 bit)
	jz TrySSE3
	or dword [LocalISA], SIMDX86ISA_BIT(SIMDX86ISA_USE_SSSE3)

	;=====================
	;Detect SSE3
	;=====================
	TrySSE3:
	test ecx, 0x1		;Test bit 0 of ecx (SSE3 bit)
	jz TrySSE2
	or dword [LocalISA], SIMDX86ISA_BIT(SIMDX86ISA_USE_SSE3)


	;=====================
	;Detect SSE2
	;=====================
	TrySSE2:
	test edx, 0x4000000		;Test bit 26 (SSE2 bit)
	jz TrySSE
	or dword [LocalISA], SIMDX86ISA_BIT(SIMDX86ISA_USE_SSE2)

	;=====================
	;Detect SSE
	;=====================
	TrySSE:
	test edx, 0x2000000		;Test bit 25 (SSE bit)
	jz TrySSE
	or dword [LocalISA], SIMDX86ISA_BIT(SIMDX86ISA_USE_SSE)
	
	

	NoStdCPUFeatures:		;If directly jumping here, then LocalISA == SIMDX86ISA_BIT(SIMDX86ISA_USE_GENERIC)
	pop ebx
	mov eax, [LocalISA]
	ret
END_SYMBOL(SIMDx86_GetCPUSupportedISA)