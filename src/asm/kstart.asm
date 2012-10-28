;*****************************************************
; kstart.asm
;
;Punto de entrada de la imagen.
;Header para multiboot.
;******************************************************


%include "../include/asm/grub.inc"

[BITS 32] ;Generates code for 32bit architecture

[global start] ;export the start symbol
[extern kmain] ;imports the kernel.c

start:

  call kmain

  jmp $ ; si retorna de kmain se detiene


;**************************************************************
; header para el GRUB. El orden de los datos estan especificados
; en la Multiboot Specification.
;**************************************************************

; Definidos en link.ld
EXTERN code, bss, end

ALIGN 4 ; Aligns data in memory, used for performance

mboot:
    ; Numero que identifica al header
    ; debe ser 0x1BADB002
	dd MULTIBOOT_HEADER_MAGIC  

    ; Los bits de 0-15 indican requerimientos
    ; de la imagen.
	dd MULTIBOOT_HEADER_FLAGS  

    ; Los bits 16-31 indican features opcionales
	dd MULTIBOOT_CHECKSUM

; Comienzo de Offsets 8-24 del header, son validos por estar seteado el flag 16.

	dd mboot	; Dirección de comienzo del header.
	dd code		; Direccion de comienzo del segmento text.
	dd bss		; Direccion del final del segmento de datos. Implica que el 
			    ; Codigo y el dato deben estar consecutivos. ( lo cumple el formato
			    ; a.out )

	dd end		; Direccion del final del segmento bss.
	dd start	; Punto de entrada de la imagen.
