/***************************************************************
 *
 *              FUNCIONES DE ATENCIÓN A INTERRUPCIONES
 *
****************************************************************/
#include "../../../include/c/definiciones.h"
#include "../../../include/c/interrupciones/funciones_de_atencion.h"
#include "../../../include/c/primitivas.h"
#include "../../../include/c/interrupciones/helpers.h"
#include "../../../include/c/stdlibs/string.h"


/***************************************************************
 *  void int_08
 *      Rutina de atención del timertick
 *      
****************************************************************/
void int_08() {
    size_t result = 0;
    char set[] = {'*', WHITE_TXT};

//    result = __write(STDOUT, (const void*) &set[0], 1);
//    // TODO:
//    //  if (result == error) {
//    //      Do something
//    //  }
//    result = __write(STDOUT, (const void*) &set[1], 1);
//    // TODO:
//    //  if (result == error) {
//    //      Do something
//    //  }
}


/***************************************************************
 *  void int_09
 *      Rutina de atención del teclado
 *
****************************************************************/
#define L_SHIFT_PRESSED     0x2A
#define R_SHIFT_PRESSED     0x36
#define L_SHIFT_REALEASED   0xAA
#define R_SHIFT_REALEASED   0xB6

char keypressed_buffer[200];
char* keyboard_set_minus = "_1234567890-=\b\tqwertyuiop[]\n_asdfghjkl;'`_\\zxcvbnm,./___ _";
char* keyboard_set_mayus = "_1234567890_+\b\tQWERTYUIOP{}\n_ASDFGHJKL;\"~_|ZXCVBNM<>?___ _";
unsigned int kbuffer_ptr = 0;
unsigned int buffer_size = sizeof(keypressed_buffer);
bool l_shift_pressed = false;
bool r_shift_pressed = false;

void int_09(unsigned char scancode) {
    size_t result = 0;
    const char whitespace = WHITE_TXT;
    char* keys = 0;

    switch(scancode) {
        case L_SHIFT_PRESSED:
            l_shift_pressed = true;
        case R_SHIFT_PRESSED:
            r_shift_pressed = true;
        break;
        case L_SHIFT_REALEASED:
            l_shift_pressed = false;
        case R_SHIFT_REALEASED:
            r_shift_pressed = false;
        break;
        default:
            keys = (l_shift_pressed || r_shift_pressed) ? 
                keyboard_set_mayus : keyboard_set_minus;
            keys -= 1;
            if( scancode >= 0x01 && scancode <= 0x3A && keys[scancode] != '_' ) {
                if(kbuffer_ptr >= buffer_size) {
                    kbuffer_ptr = 0;
                } 
                keypressed_buffer[kbuffer_ptr];
            }
        break;
    }
}


/***************************************************************/
