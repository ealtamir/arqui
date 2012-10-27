#include "../include/kasm.h"
#include "../include/definiciones.h"

DESCR_INT idt[256];		/* IDT de 10 entradas*/
IDTR idtr;				    /* IDTR */

extern void k_clear_screen();
extern void setup_IDT_entry(
    DESCR_INT *item, 
    word selector, 
    dword offset, 
    byte access,
    byte cero
); 

int tickpos = 0;

void int_08() {
    char *video = (char *) 0xb8000;
    video[tickpos] = '*';
    tickpos += 2;
}
void int_09() {
    char *video = (char *) 0xb8000;
    video[tickpos] = '^';
    tickpos += 2;
}

/**********************************************
kmain() 
Punto de entrada de código C.
*************************************************/

int kmain() 
{
    int i;
    int num;

/* Borra la pantalla. */ 

	k_clear_screen();


/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */
    
    setup_IDT_entry(&idt[8], 0x08, (dword) &_int_08_hand, ACS_INT, 0);
    setup_IDT_entry(&idt[9], 0x0008, (dword) &_int_09_hand, ACS_INT, 0);
	
/* Carga de IDTR    */

	idtr.base = 0;  
	idtr.base += (dword) &idt;  // dónde empieza la idt
	//idtr.limit = sizeof(idt)-1; // qué tamaño tiene la idt
	idtr.limit = sizeof(idt) - 1; // qué tamaño tiene la idt

	_lidt(&idtr);	

	_Cli();

/* Habilito interrupcion de teclado*/
    _mascaraPIC1(0xFD);
    _mascaraPIC2(0xFF);
        
	_Sti();

    while(1)
    {
    }
}

