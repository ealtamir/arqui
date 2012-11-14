#include "../../include/c/interrupciones/definiciones.h"
#include "../../include/c/definiciones.h"
#include "../../include/c/interrupciones/helpers.h"
#include "../../include/c/helpers.h"
#include "../../include/c/video.h"
#include "../../include/c/shell.h"
#include "../../include/c/multiboot.h"
#include "../../include/c/malloc.h"
#include "../../include/c/primitivas.h"

/***************************************************************
*  void kmain
*      Función principal por donde empieza a ejecutarse el kernel.
*
****************************************************************/
void kmain(multiboot_info_t* mbd, unsigned int magic) {

    // Inicializo el sistema de interrupciones.
    initInterrupts();

    //Seteo las máscaras de los PICs
    // 0xFF: apaga todas las ints.
    // 0xFE: sólo timertick.
    // 0xFD: sólo teclado.
    // 0xFC: teclado y timertick
    setPicMasks(0xFC, 0xFF);

    // Borro la pantalla
    clear_vscreen();
    print_vscreen();

    // Hago todas las configuraciones de la memoria
    init_system_mem(mbd);

    shell();

    while(1) {}
}
