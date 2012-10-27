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
 * unsigned int _read_msw
 *
****************************************************************/
unsigned int _read_msw();

#endif
