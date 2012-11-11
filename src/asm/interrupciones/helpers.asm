;*****************************************************************
;
;                       INCLUDES & EXTERN SYMBOLS
;
;*****************************************************************;
%include "../include/asm/macros.asm"

;*****************************************************************
;
;                           FUNCIONES
;
;*****************************************************************;
GLOBAL  _Cli
GLOBAL  _Sti
GLOBAL  _lidt
GLOBAL  _mascaraPIC1
GLOBAL  _mascaraPIC2
GLOBAL  _keyboardin



SECTION .text
;********************************************
;   _Cli
;       Apaga el flag the interrupciones (I=0).
;
;********************************************;
_Cli:
	cli				
    ret

;********************************************
;   _Sti
;       Prende el flag the interrupciones (I=1).
;
;********************************************;
_Sti:
	sti			
	ret
;********************************************
;   _mascaraPIC1:
;       Enmascara el PIC1 o "Master" con la máscara pasada
;   como parámetro.
;
;********************************************;
_mascaraPIC1:			
    build_frame
    mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
    out	    21h, al
    pop     ebp
    retn

;********************************************
;   _mascaraPIC2:
;       Enmascara el PIC2 o "Slave" con la máscara pasada
;   como parámetro.
;
;********************************************;
_mascaraPIC2:			
	push    ebp
    mov     ebp, esp
    mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
    out	    0A1h, al
    pop     ebp
    retn

;********************************************
;   _lidt:
;       Carga el IDTR con el valor pasado como parámetro.
;   Recibe un puntero a una estructura IDTR.
;
;********************************************;
_lidt:				
    push    ebp
    mov     ebp, esp
    push    ebx
    mov     ebx, [ss:ebp + 6] ; ds:bx = puntero a IDTR 
	rol	    ebx, 16		    	
	lidt    [ds:ebx]          ; carga IDTR
    pop     ebx
    pop     ebp
    retn

;********************************************
;   _keyboardin
;       Recibe como primer parámetro, un puerto y como 
;   segundo, un dato. La función le envía al puerto el dato
;
;********************************************;
_keyboardin: 
    build_frame
    in eax, 0x60
    pop ebp
    ret


;********************************************;
