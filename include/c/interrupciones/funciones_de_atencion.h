#ifndef interrupciones_rutinas_de_atencion
#define interrupciones_rutinas_de_atencion

#include "../definiciones.h"

/***************************************************************
 *
 *              FUNCIONES DE ATENCIÓN A INTERRUPCIONES
 *
****************************************************************/

/***************************************************************
 *  void int_* 
 *      Funciones de atención de interrupción para ser seteadas
 *          por el comando infoidt
 *      
****************************************************************/
void int_00();
void int_01();
void int_02();
void int_03();
void int_04();
void int_05();
void int_06();
void int_07();


/***************************************************************
 *  void int_08
 *      
****************************************************************/
void int_08();


/***************************************************************
 *  void int_09
 *
****************************************************************/
void int_09(unsigned char scancode);


/***************************************************************/

#endif
