#include "../../include/interrupciones/helpers.h"

/***************************************************************
 *
 *                      FUNCIONES 
 *
****************************************************************/
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
*
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


/***************************************************************
 *  void initInterrupts
 *      Inicializa la IDT y carga las rutinas de atención.
 *
 *  Recibe:
 *      Un puntero a la IDT.       
 *
****************************************************************/
void initInterrupts(DESCR_INT *idt) {

    IDTR idtr;  // Para cargar el IDTR.

    // Cargo los descriptores en la IDT
    // Debido a que el PIC1 está mapeado a partir de la interrupción
    // 8, empiezo a definir mis rutinas ahí.
    setup_IDT_entry(&idt[8], 8, (dword) &_int_08_hand, ACS_INT, 0);
    setup_IDT_entry(&idt[9], 8, (dword) &_int_09_hand, ACS_INT, 0);

    idtr.base = (dword) idt;
    idtr.limit = sizeof(idt) - 1;
    _lidt(&idtr);
}

/***************************************************************
 *  void setPicMasks
 *      Setea las máscaras del PIC maestro y esclavo. Cuando el 
 *  bit en una posición del PIC es 0, deja pasar la interrupción.
 *
 *  Recibe:
 *      pic1_mask: máscara para el PIC maestro.
 *      pic2_mask: máscara para el PIC esclavo.
 *      
****************************************************************/
void setPicMasks(byte pic1_mask, byte pic2_mask) {
    
    // Deshabilito las interrupciones
	_Cli();

    _mascaraPIC1(pic1_mask);
    _mascaraPIC2(pic2_mask);
        
    // Vuelvo a habilitar las interrupciones
	_Sti();
}
