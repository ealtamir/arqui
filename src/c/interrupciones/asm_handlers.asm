/*****************************************************************
/
/
/                       INCLUDES & EXTERN SYMBOLS
/
/
/*****************************************************************/

%include "../include/asm/macros.asm"

EXTERN  int_08
EXTERN  int_09

/*****************************************************************
/
/
/                           FUNCIONES
/
/
/*****************************************************************/

GLOBAL  _int_08_hand
GLOBAL  _int_09_hand


SECTION .text

/********************************************
/   _int_08_hand
/       Handler para la interrupción 8
/
/********************************************/
_int_08_hand:				
    push    ds
    push    es              ; Se salvan los registros
    pusha                   ; Carga de DS y ES con el valor del selector
    mov     ax, 10h			; a utilizar.
    mov     ds, ax          ; Mi función de C utiliza ds y es
    mov     es, ax          ; con un selector por defecto. Por eso 
                            ; los debo setear.

    call    int_08          ; Llama a la función de C.

    mov	    al, 20h			; Envio de EOI generico al PIC
	out	    20h, al
	popa                            
    pop     es
    pop     ds
    iret


/********************************************
/   _int_09_hand
/       Handler para la interrupción 9
/
/********************************************/
_int_09_hand:				
    push    ds
    push    es              ; Se salvan los registros
    pusha                   ; Carga de DS y ES con el valor del selector
    mov     ax, 10h			; a utilizar.
    mov     ds, ax          ; Selector 1, privilegios y TI en 0
    mov     es, ax                  

    call    int_09          ; Llama a la función de C.

    mov	    al, 20h			; Envio de EOI generico al PIC
	out	    20h, al
	popa                            
    pop     es
    pop     ds
    iret
