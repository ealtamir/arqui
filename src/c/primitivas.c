/***************************************************************
 *
 *                  PRIMITIVAS DEL SISTEMA
 *
****************************************************************/
#include "../../include/c/definiciones.h"
#include "../../include/c/primitivas.h"
#include "../../include/c/helpers.h"
#include "../../include/c/interrupciones/helpers.h"

/***************************************************************
 *
 *                      FUNCIONES
 *
****************************************************************/
void write_to_screen(char c);

///////////////////// VARIABLES GLOBALES ///////////////////////////
// Representa la posición en la pantalla donde se escribirá el
// próximo caracter. Para minimizar los bugs que pueda introducir
// el uso de la variable, ésta sólo será utilizada en este archivo.
int tickpos = 0;


// Variables globales relacionadas al teclado.
bool l_shift_pressed = false;
bool r_shift_pressed = false;
char keypressed_buffer[KEYBOARD_BUFFER_SIZE];
char* keyboard_set_mayus = "_1234567890_+\b\tQWERTYUIOP{}\n_ASDFGHJKL;\"~_|ZXCVBNM<>?___ _";
char* keyboard_set_minus = "_1234567890-=\b\tqwertyuiop[]\n_asdfghjkl;'`_\\zxcvbnm,./___ _";
unsigned int read_kbuffer_ptr = 0;
unsigned int write_kbuffer_ptr = 0;
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
            // Could be keyboard buffer.
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

    unsigned int i = 0;          // Index varible.
    unsigned int c = 0;          // Index varible.
    unsigned int chars_read = 0;

    switch(fd) {
        case STDOUT: case STDERR:
            break;
        case STDIN:
            while( count > 0 ) {
                c = keypressed_buffer[read_kbuffer_ptr];
                if(c != '\0') {
                    if(read_kbuffer_ptr < KEYBOARD_BUFFER_SIZE - 1) {
                        read_kbuffer_ptr++;
                    } else { 
                        // Me aseguro que no se salga del buffer de teclado.
                        read_kbuffer_ptr = 0;
                    }
                    chars_read++;
                    ((char*)buffer)[i] = c;
                    i++;
                    count--;
                }
            }
            break;
        default:
            // No default case
            // TODO: RAISE AN ERROR
            break;
    }
    return chars_read;
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
    if (tickpos >= SCREEN_SIZE) {
        tickpos = 0;
    }
}


/***************************************************************
*   void fflush
*       Vacía el buffer que le corresponde al fd pasádo como 
*           parámetro. Apaga las interrupciones para que mientras
*           limpia los buffers no hayan rutinas que escriban 
*           sobre ellos.
*
****************************************************************/
void fflush(int fd) {
    _Cli();
    switch (fd) {
        case STDIN:
            read_kbuffer_ptr = 0;
            write_kbuffer_ptr = 0;
            memset_custom(keypressed_buffer, KEYBOARD_BUFFER_SIZE, '\0');
        break;
        case STDOUT:
            // No hace nada.
        break;
        case STDERR:
            // No hace nada.
        break;
        default:
            // No hace nada.
        break;
    }
    _Sti();
}

/****************************************************************/
