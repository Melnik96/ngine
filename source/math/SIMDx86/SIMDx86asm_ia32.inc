; SIMDx86asm_32.inc -- SIMDx86 Assembly Language Defines (NASM/YASM)
; Written by by Carl Skeps, 2006 (carl.skeps@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project
BITS 32

; Alignment Constants
CODE_ALIGNMENT EQU 10H ; Force code alignment to OWORD boundary
STACK_ALIGNMENT EQU 10H ;Force stack alignment to OWORD boundary

; Macro: ALIGN_CODE
; Description: Aligns code to %1 bytes
; Arguments: Code alignment value
%macro ALIGN_CODE 1

	ALIGN %1 

%endmacro ; ALIGN_CODE

; Macro: ALIGN_STACK
; Description: Aligns the stack to %1 bytes
; Arguments: Stack alignment value
%macro ALIGN_STACK 1

	MOV EAX, %1 - 1
	NOT EAX
	AND ESP, EAX

%endmacro ; ALIGN_STACK

; Macro: PROLOGUE
; Description: Aligns the code to the nearest OWORD and
; 	initializes the base pointer to point at the top of the stack
%macro PROLOGUE 0

	ALIGN_CODE CODE_ALIGNMENT
	PUSH EBP
	MOV EBP, ESP

%endmacro ; PROLOGUE_NO_STACK

; Macro: PROLOGUE
; Description: Initializes and reserves %1 bytes on the stack 
; Arguments: Bytes to reserved on stack
; On Exit:
;	EBP points at original stack base + sizeof ( EBP )
;	ESP points at top of aligned stack
;	Function args and return value are at EBP + ARG_OFFSET
;	Stack args are at ESP + ARG_OFFSET
%macro PROLOGUE 1

	PROLOGUE
	ALIGN_STACK STACK_ALIGNMENT
	SUB ESP, %1

%endmacro ; PROLOGUE

; Macro: EPILOGUE
; Description: Initializes a stack and 
; Arguments: Bytes to reserved on stack
%macro EPILOGUE 0

	MOV ESP, EBP
	POP EBP

%endmacro ; EPILOGUE