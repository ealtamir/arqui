;*****************************************************************
;
;
;                       INCLUDES & EXTERN SYMBOLS
;
;
;*****************************************************************;

%include "../include/asm/macros.asm"

EXTERN  int_00
EXTERN  int_01
EXTERN  int_02
EXTERN  int_03
EXTERN  int_04
EXTERN  int_05
EXTERN  int_06
EXTERN  int_07
EXTERN  int_08
EXTERN  int_09

;*****************************************************************
;
;
;                           FUNCIONES
;
;
;*****************************************************************;

GLOBAL  _int_08_hand
GLOBAL  _int_09_hand


SECTION .text

; Handlers genéricos para rutinas de atención definidos
; a través de macros.
_int_hand_create 00
_int_hand_create 01
_int_hand_create 02
_int_hand_create 03
_int_hand_create 04
_int_hand_create 05
_int_hand_create 06
_int_hand_create 07

;********************************************
;   _int_08_hand
;       Handler para la interrupción 8
;
;********************************************;
_int_hand_create 08


;********************************************
;   _int_09_hand
;       Handler para la interrupción 9
;
;********************************************;
_int_09_hand:				
    push    ds
    push    es              ; Se salvan los registros
    pusha                   ; Carga de DS y ES con el valor del selector
    mov     ax, 10h			; a utilizar.
    mov     ds, ax          ; Selector 1, privilegios y TI en 0
    mov     es, ax                  
    in      al, 60h

    push    eax
    call    int_09          ; Llama a la función de C.
    pop     eax
    
    mov	    al, 20h			; Envio de EOI generico al PIC
	out	    20h, al
	popa                            
    pop     es
    pop     ds
    iret
