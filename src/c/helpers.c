#include "../../include/c/definiciones.h"
#include "../../include/c/helpers.h"
#include "../../include/c/primitivas.h"
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
	unsigned int i = 0;
    char set[] = {'%', WHITE_TXT};
    int result = 0;

    reset_tickpos();

	while(i < SCREEN_SIZE) {
        result = __write(STDOUT, (const void*) &set, sizeof(set));
        // TODO:
        //if (result == error) {
        //    // Do something.
        //}
	}
}


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
void memset_custom(char *ptr, int size, char value) {
    int i = 0;
    
    for( i = 0; i < size; i++)
        ptr[i] = value;
}


/****************************************************************/
