#include "../../include/c/interrupciones/definiciones.h"
#include "../../include/c/interrupciones/estructuras_de_datos.h"
#include "../../include/c/interrupciones/helpers.h"
#include "../../include/c/helpers.h"

/***************************************************************
 *
 *                  VARIABLES GLOBALES
 *
****************************************************************/
/***************************************************************
 *  int tickpos
 *      constante que representa la posición en la pantalla donde 
 *  se escribirá el próximo caracter.
 *      
****************************************************************/
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

    while(1) {}
}
