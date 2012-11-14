#ifndef interrupciones_helpers
#define interrupciones_helpers
/*****************************************************************
*
*                   FUNCIONES
*
*****************************************************************/
#include "../definiciones.h"     
#include "handlers.h"

/***************************************************************
*   void setup_IDT_entry *   Inicializa un descriptor de la IDT
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
);


/***************************************************************
 *  void initInterrupts
 *      Inicializa la IDT y carga las rutinas de atención.
 *
****************************************************************/
void initInterrupts();


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
void setPicMasks(byte pic1_mask, byte pic2_mask); 

DESCR_INT* get_idt();

/*****************************************************************
*
*                   RUTINAS DE BAJO NIVEL
*
*****************************************************************/
/*****************************************************************
*   void _lidt
*       Carga el registro IDTR con el valor que se le pase como parámetor.
*
*   Recibe:
*       idtr: Una estructura con base (posición de memoria absoluta 
*           donde estará la IDT) y límite (tamaño que tendrá 
*           la IDT).
*
*****************************************************************/
void _lidt (IDTR *idtr);


/*****************************************************************
*   void _mascaraPIC1
*       Enmascara el PIC maestro.
*
*   Recibe:
*       mascara: Byte con el cual  enmascarar el PIC.
*
*****************************************************************/
void _mascaraPIC1 (byte mascara); 


/*****************************************************************
*   void _mascaraPIC2
*       Enmascara el PIC esclavo.
*
*   Recibe:
*       mascara: Byte con el cual  enmascarar el PIC.
*
*****************************************************************/
void _mascaraPIC2 (byte mascara); 


/*****************************************************************
*   void _Cli
*       Apaga las interrupciones (I=0).
*
*****************************************************************/
void _Cli();    


/*****************************************************************
*   void _Sli
*       Prende las interrupciones (I=1).
*
*****************************************************************/
void _Sti();	 

/*****************************************************************
*   int _in
*       Lee la tecla presionada del teclado.
*
*****************************************************************/
int _keyboardin();	 


/*****************************************************************
* void _get_ebx
*
*****************************************************************/
dword _get_ebx();

/***************************************************************/

#endif
