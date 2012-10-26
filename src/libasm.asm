GLOBAL  _read_msw, _lidt
GLOBAL  _mascaraPIC1, _mascaraPIC2, _Cli, _Sti
GLOBAL  _debug

GLOBAL  _int_08_hand
GLOBAL  _int_09_hand

EXTERN  int_08
EXTERN  int_09

%macro build_frame
	push    ebp
    mov     ebp, esp
%endmacro

SECTION .text

; Interrupt Flag = 0
_Cli:
	cli				
    ret

; Interrupt Flag = 0
_Sti:
	sti			
	ret

;
_outb:
    build_frame
    mov ax, [ss:ebp+8]      ;port
    mov bx, [ss:ebp+12]     ;data
    out ax, bx
    pop ebp
    ret


; Escribe mascara del PIC 1
_mascaraPIC1:			
    build_frame
    mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
    out	    21h, al
    pop     ebp
    retn

; Escribe mascara del PIC 2
_mascaraPIC2:			
	push    ebp
    mov     ebp, esp
    mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
    out	    0A1h, al
    pop     ebp
    retn

; Obtiene la Machine Status Word
_read_msw:
    smsw    ax		
    retn

; Carga el IDTR
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

; Handler de INT 8 ( Timer tick)
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

; Debug para el BOCHS, detiene la ejecución
; Para continuar colocar en el BOCHSDBG: set $eax=0
_debug:
    push    bp
    mov     bp, sp
    push	ax

vuelve:	
    mov     ax, 1
    cmp     ax, 0
	jne     vuelve
	pop     ax
	pop     bp
    retn
