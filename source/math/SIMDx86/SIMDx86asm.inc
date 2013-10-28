; SIMDx86asm.inc -- SIMDx86 Assembly Language Defines (NASM/YASM)
; Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
; Contributions by Carl Skeps, 2006 (carl.skeps@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

%ifndef SIMDX86_ASM
%define SIMDX86_ASM

%ifdef PLATFORM_X64

%include "SIMDx86asm_x64.inc"

%elifdef PLATFORM_IA32

%include "SIMDx86asm_ia32.inc"

%elifdef PLATFORM_IA64

%include "SIMDx86asm_ia64.inc"

%else

%error Platform not defined

%endif

%ifdef ELF ;ELF targets such as Linux, Free/Net/OpenBSD, Solaris

	%define EXPORT_SYMBOL( sym ) GLOBAL sym
	%define BEGIN_SYMBOL( sym ) sym:
	%define END_SYMBOL( sym ) end_ %+ sym:
	%macro SIZE_SYMBOL 1
		section .data
		GLOBAL size_ %+ %1
		size_ %+ %1: dd (end_ %+ %1) - %1	
		section .text
	%endmacro

%else	;Non-ELF targets such as MS-DOS, Win32, ReactOS

	%define EXPORT_SYMBOL( sym ) GLOBAL _ %+ sym
	%define BEGIN_SYMBOL( sym ) _ %+ sym:
	%define END_SYMBOL( sym ) end_ %+ sym:
	%macro SIZE_SYMBOL 1
		GLOBAL _ %+ size_ %+ %1
		_ %+ size_ %+ %1: dd (end_ %+ %1) - (_ %+ %1)	
	%endmacro
	
	
;	%define SIZE_SYMBOL( sym )  _ %+ size_ %+ sym: dd (end_ %+ sym) - (_ %+ sym)

%endif

%define OVERLAY_SIZE_SMALL		32			; 32 bytes of code
%define OVERLAY_SIZE_MEDIUM		128			; 128 bytes of code
%define OVERLAY_SIZE_LARGE		512			; 512 bytes of code
%define OVERLAY_SIZE_HUGE		1024		; 1KB of code

%define SIMDX86ISA_BIT( bit ) 		(1 << bit)

%define SIMDX86ISA_USE_GENERIC		0
%define SIMDX86ISA_USE_MMX			1
%define SIMDX86ISA_USE_EMMX			2
%define SIMDX86ISA_USE_3DNOW		3
%define SIMDX86ISA_USE_3DNOWPLUS	4
%define SIMDX86ISA_USE_SSE			5
%define SIMDX86ISA_USE_SSE2			6
%define SIMDX86ISA_USE_SSE3			7
%define SIMDX86ISA_USE_SSSE3		8
%define SIMDX86ISA_USE_SSE4			9
%define SIMDX86ISA_USE_BEST			10
%define SIMDX86ISA_MAX				11

%endif
