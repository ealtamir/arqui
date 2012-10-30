/***************************************************************
 *
 *              FUNCIONES DE ATENCIÓN A INTERRUPCIONES
 *
****************************************************************/
#include "../../../include/c/definiciones.h"
#include "../../../include/c/interrupciones/funciones_de_atencion.h"
#include "../../../include/c/primitivas.h"

/***************************************************************
 *  void int_08
 *      
****************************************************************/
void int_08() {
    size_t result = 0;
    char set[] = {'*', WHITE_TXT};

    result = __write(STDOUT, (const void*) &set[0], 1);
    // TODO:
    //  if (result == error) {
    //      Do something
    //  }
    result = __write(STDOUT, (const void*) &set[1], 1);
    // TODO:
    //  if (result == error) {
    //      Do something
    //  }
}


/***************************************************************
 *  void int_09
 *
****************************************************************/
void int_09() {
    size_t result = 0;
    char set[] = {'^', WHITE_TXT};

    result = __write(STDOUT, (const void*) &set[0], 1);
    // TODO:
    //  if (result == error) {
    //      Do something
    //  }
    result = __write(STDOUT, (const void*) &set[1], 1);
    // TODO:
    //  if (result == error) {
    //      Do something
    //  }
}


/***************************************************************/
