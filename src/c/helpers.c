#include "../../include/c/definiciones.h"
/***************************************************************
 *
 *                      FUNCIONES 
 *
****************************************************************/
/***************************************************************
*   k_clear_screen
*       Borra la pantalla en modo texto color.
*
****************************************************************/
void k_clear_screen() 
{
	char *vidmem = (char *)0xb8000;
	unsigned int i = 0;

	while(i < (SCREEN_WIDTH * SCREEN_LENGTH * CHAR_SIZE)) {
		vidmem[i]='X';
		i++;
		vidmem[i] = WHITE_TXT;
		i++;
	};
}


/****************************************************************/
