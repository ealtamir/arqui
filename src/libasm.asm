GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL  _debug

EXTERN  int_08


SECTION .text

; limpia flag de interrupciones
_Cli:
	cli				
    ret


; habilita interrupciones por flag
_Sti:
	sti			
	ret


; Escribe mascara del PIC 1
_mascaraPIC1:			
	push    ebp
    mov     ebp, esp
    mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
    out	    21h,al
    pop     ebp
    retn


; Escribe mascara del PIC 2
_mascaraPIC2:			
	push    ebp
    mov     ebp, esp
    mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
    out	    0A1h,al
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
    mov     ebx, [ss: ebp + 6] ; ds:bx = puntero a IDTR 
	rol	    ebx, 16		    	
	lidt    [ds: ebx]          ; carga IDTR
    pop     ebx
    pop     ebp
    retn

; Handler de INT 8 ( Timer tick)
_int_08_hand:				
    push    ds
    push    es              ; Se salvan los registros
    pusha                   ; Carga de DS y ES con el valor del selector
    mov     ax, 10h			; a utilizar.
    mov     ds, ax
    mov     es, ax                  
    call    int_08          ; Llama a la función de C.
    mov	    al, 20h			; Envio de EOI generico al PIC
	out	    20h, al
	popa                            
    pop     es
    pop     ds
    iret


; Debug para el BOCHS, detiene la ejecució; Para continuar colocar en el BOCHSDBG: set $eax=0
;
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
