;*****************************************************************
;
;
;                           MACROS
;
;
;*****************************************************************;

;********************************************
;   MACRO: build_frame
;       Construye el stack frame.
;
;********************************************;
%macro build_frame 0
	push    ebp
    mov     ebp, esp
%endmacro

%macro _int_hand_create 1
GLOBAL _int_%1_hand:
_int_%1_hand:
    push    ds
    push    es              ; Se salvan los registros
    pusha                   ; Carga de DS y ES con el valor del selector
    mov     ax, 10h			; a utilizar.
    mov     ds, ax          ; Mi función de C utiliza ds y es
    mov     es, ax          ; con un selector por defecto. Por eso 
                            ; los debo setear.

    call    int_%1          ; Llama a la función de C.

    mov	    al, 20h			; Envio de EOI generico al PIC
	out	    20h, al
	popa                            
    pop     es
    pop     ds
    iret

%endmacro
