#include "../../include/c/interrupciones/definiciones.h"
#include "../../include/c/interrupciones/estructuras_de_datos.h"
#include "../../include/c/interrupciones/helpers.h"

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
int tickpos = 0;

extern void k_clear_screen();

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
    setPicMasks(0xFD, 0xFF);

    while(1) {}
}
