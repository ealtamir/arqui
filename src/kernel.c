#include "../include/kasm.h"
#include "../include/defs.h"

DESCR_INT idt[0xA];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */

extern void k_clear_screen();
extern void setup_IDT_entry (
        DESCR_INT *item, 
        byte selector, 
        dword offset, 
        byte access,
		byte cero); 

int tickpos = 640;

void int_08() {
    char *video = (char *) 0xb8000;
    video[tickpos+=2]='*';
}

/**********************************************
kmain() 
Punto de entrada de cóo C.
*************************************************/

int kmain() 
{

    int i;
    int num;

/* Borra la pantalla. */ 

	k_clear_screen();


/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

    setup_IDT_entry( &idt[0x08], 0x08, (dword) &_int_08_hand, ACS_INT, 0);
	
/* Carga de IDTR    */

	idtr.base = 0;  
	idtr.base += (dword) &idt;
	idtr.limit = sizeof(idt)-1;

	_lidt (&idtr);	

	_Cli();

/* Habilito interrupcion de timer tick*/
    _mascaraPIC1(0xFE);
    _mascaraPIC2(0xFF);
        
	_Sti();

    while(1)
    {
    }
	
}

