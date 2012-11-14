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

GLOBAL  _read_msw
GLOBAL  _get_ebx


SECTION .text

;********************************************
;   _outb
;       Recibe como primer parámetro, un puerto y como 
;   segundo, un dato. La función le envía al puerto el dato
;
;********************************************;
;_outb:
;    build_frame
;    mov ax, [ss:ebp+8]      ;port
;    mov bx, [ss:ebp+12]     ;data
;    out ax, bx
;    pop ebp
;    ret


;********************************************
;   get_ebx
;
;
;********************************************;
_get_ebx:
    build_frame
    mov     eax, ebx
    pop     ebp

;********************************************
;   _read_msw:
;       Lee el registro de control CR0 y lo devuelve.
;
;********************************************;
_read_msw:
    smsw    ax		
    retn

;*****************************************************************;
