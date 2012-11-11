#ifndef primitivas
#define primitivas
/***************************************************************
 *
 *                  PRIMITIVAS DEL SISTEMA
 *
****************************************************************/
#include "definiciones.h"
#include "helpers.h"


/***************************************************************
 *
 *                      FUNCIONES
 *
****************************************************************/
int (*player)(void);

// // // //  // // // //  // // // //  // // // //  // // // //  
// NOTA:
// Como los sistema POSIX, éste kernel utilizará el stdin, stdout
// y el stderr; el primero mapeado con el teclado y los dos últimos
// con el monitor. 
// // // //  // // // //  // // // //  // // // //  // // // //  

/***************************************************************
 *   size_t __write
 *       Primitiva de escritura del sistema. 
 *
 *   Recibe:
 *      fd: File Descriptor, característica de los sistemas POSIX que 
 *          definen la fuentes de lectura y escritura a partir de 
 *          archivos.
 *      buffer: Puntero al lugar donde se va a escribir.
 *      count: Cantidad de bytes que se escribirán.
****************************************************************/
size_t __write(int fd, const void* buffer, size_t count);

/***************************************************************
 *   size_t __read
 *       Primitiva de lectura del sistema.
 *
 *   Recibe:
 *      fd: File Descriptor, característica de los sistemas POSIX que 
 *          definen la fuentes de lectura y escritura a partir de 
 *          archivos.
 *      buffer: Puntero al lugar donde se va a leer.
 *      count: Cantidad de bytes que se leerán.
****************************************************************/
size_t __read(int fd, void* buffer, size_t count);

/***************************************************************
 *
 *  void reset_tickpos
 *
****************************************************************/
// TODO: Sacar esto y escribir un controlador de video apropiado.
void reset_tickpos();

#endif

/****************************************************************/
