/***************************************************************
 *
 *                  PRIMITIVAS DEL SISTEMA
 *
****************************************************************/
#include "../../include/c/definiciones.h"
#include "../../include/c/primitivas.h"
#include "../../include/c/helpers.h"

/***************************************************************
 *
 *                      FUNCIONES
 *
****************************************************************/
void write_to_screen(char c);

///////////////////// VARIABLE GLOBAL ///////////////////////////
// Representa la posición en la pantalla donde se escribirá el
// próximo caracter. Para minimizar los bugs que pueda introducir
// el uso de la variable, ésta sólo será utilizada en este archivo.
int tickpos = 0;
/////////////////////////////////////////////////////////////////

// NOTA:
// Como los sistema POSIX, éste kernel utilizará el stdin, stdout
// y el stderr; el primero mapeado con el teclado y los dos últimos
// con el monitor. 
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
size_t __write(int fd, const void* buffer, size_t count) {

    unsigned int i = 0;          // Index varible.

    switch(fd) {
        case STDOUT: case STDERR:
            for(i = 0; i < count; i++) {
                write_to_screen( ((char *) buffer)[i] );
            }
            break;
        case STDIN:
            // TODO: SHOULD WRITE TO THE KEYBOARD BUFFER.
            break;
        default:
            // No default case
            // TODO: RAISE AN ERROR
            break;
    }
    // TODO: REGRESAR EL VALOR ADECUADO.
    return count;
}

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
size_t __read(int fd, void* buffer, size_t count) {
    // TODO
}

/***************************************************************
*   void reset_tickpos
*       Setea la posición del tick para que quede en la posición
*           0 de la pantalla.
*
****************************************************************/
void reset_tickpos() {
    tickpos = 0;
}

/***************************************************************
*   void write_to_screen
*       Escribe en la pantalla actualizando el tickpos con cada 
*           iteración.
*
*
****************************************************************/
void write_to_screen(char c) {
    char* screen = (char *) SCREEN_ADDRESS;
    screen[tickpos] = c;
    tickpos++;
}

/****************************************************************/
