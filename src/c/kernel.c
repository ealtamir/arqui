#include "../../include/c/interrupciones/definiciones.h"
#include "../../include/c/definiciones.h"
#include "../../include/c/interrupciones/helpers.h"
#include "../../include/c/helpers.h"

/***************************************************************
*  void kmain
*      Función principal por donde empieza a ejecutarse el kernel.
*
****************************************************************/
void kmain() {
    DESCR_INT idt[IDT_SIZE];	    // Creo la IDT.

    // Borro la pantalla
	k_clear_screen();

    // Inicializo el sistema de interrupciones.
    initInterrupts(idt, IDT_SIZE);

    //Seteo las máscaras de los PICs
    // 0xFF: apaga todas las ints.
    // 0xFE: sólo timertick.
    // 0xFD: sólo teclado.
    // 0xFC: teclado y timertick
    setPicMasks(0xFC, 0xFF);

    putc_custom('S');
    printf_custom("%s %s %s %d", "Hello World!", "Otro parametro", "Otro mas...  ", 1000 );
    putc_custom(' ');
    putc_custom(' ');
    putc_custom(' ');
    scanf("Hello world!");
    putc_custom('A');

}
