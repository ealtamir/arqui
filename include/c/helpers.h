#ifndef helpers
#define helpers
/***************************************************************
 *
 *              FUNCIONES DE GENERALES
 *
****************************************************************/

#include "definiciones.h"

#ifndef WHITE_TXT
#define WHITE_TXT 0x07 
#endif

/***************************************************************
*   void showSplashScreen
*
****************************************************************/
void showSplashScreen();


/***************************************************************
 *   void wait
 *       Espera una determinada cantidad de tiempo
 *
 *   Recibe:
 *       time: La cantidad de tiempo de tiempo que debe esperar la función.
****************************************************************/
void wait(int time);


/***************************************************************
 *   k_clear_screen
 *       Borra la pantalla utilizando WHITE_TXT como color.
 *
****************************************************************/
void k_clear_screen();


/***************************************************************
*   void memset_custom
*       Recibe un puntero a void y a partir de ese puntero setea
*           'size' cantidad de bytes con 'value'.
*
*   Recibe:
*       ptr: Puntero a void.
*       size: Tamaño en bytes de la sección de memoria a setear.
*       value: Valor con el cual se setea la memoria.
*
****************************************************************/
void memset_custom(char *ptr, int size, char value);


/***************************************************************
*   void reset_tickpos
*       Setea la posición del tick para que quede en la posición
*           0 de la pantalla.
*
****************************************************************/
void reset_tickpos();


/***************************************************************
 * unsigned int _read_msw
 *
****************************************************************/
unsigned int _read_msw();


#endif
