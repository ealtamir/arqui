#include "../include/kc.h"


/***************************************************************
*   k_clear_screen
*
*   Borra la pantalla en modo texto color.
****************************************************************/

void k_clear_screen() 
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
}

/***************************************************************
*   setup_IDT_entry
*   Inicializa un descriptor de la IDT
*
*   Recibe: 
*       Puntero a elemento de la IDT
*       Selector a cargar en el descriptor de interrupcion
*       Puntero a rutina de atencion de interrupcion	
*       Derechos de acceso del segmento
*       Cero
****************************************************************/

void setup_IDT_entry(
    DESCR_INT *item, 
    byte selector, 
    dword offset, 
    byte access,
    byte cero
) {
  item->selector = selector;        // descriptor de la GDT a usar
  item->offset_l = offset & 0xFFFF; // low mem address
  item->offset_h = offset >> 16;    // high mem address
  item->access = access;            // data bits
  item->cero = cero;                // non-available bits
}
