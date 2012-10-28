#ifndef interrupciones_handlers
#define interrupciones_handlers
/***************************************************************
 *
 *              HANDLERS DE INTERRUPCIONES
 *
****************************************************************/
// Están implementados en ASSEMBLER.

#include "../definiciones.h"
/***************************************************************
 *  void _int_08_hand
 *      Llamado por la IRQ0 es activado por la interrupción del timer.
 *
****************************************************************/
void _int_08_hand();      


/***************************************************************
 *  void _int_09_hand
 *      Llamado por la IRQ1 es activado por la interrupción de teclado.
 *
****************************************************************/
void _int_09_hand();      



#endif
