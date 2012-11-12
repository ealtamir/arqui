#include "../../../include/c/definiciones.h"
#include "../../../include/c/interrupciones/funciones_de_atencion.h"
#include "../../../include/c/primitivas.h"
#include "../../../include/c/interrupciones/helpers.h"
#include "../../../include/c/stdlibs/string.h"
#include "../../../include/c/helpers.h"
#include "../../../include/c/video.h"


/***************************************************************
 *
 *              FUNCIONES DE ATENCIÓN A INTERRUPCIONES
 *
****************************************************************/
#define L_SHIFT_PRESSED     0x2A
#define R_SHIFT_PRESSED     0x36
#define L_SHIFT_REALEASED   0xAA
#define R_SHIFT_REALEASED   0xB6
#define PRINT_KBUFFER       0x38

int cursor_blink_timer = 0;

// Variables externa declaradas en primitivas.c
extern char keypressed_buffer[];
extern char* keyboard_set_minus;
extern char* keyboard_set_mayus;
extern unsigned int write_kbuffer_ptr;
extern bool l_shift_pressed;
extern bool r_shift_pressed;

/***************************************************************
 *  void int_08
 *      Rutina de atención del timertick
 *      
****************************************************************/
void int_08() {
    _Cli();
    cursor_blink_timer++;
    if( cursor_blink_timer == POINTER_BLINK_SPEED) {
        blink_pointer_toggle();
        cursor_blink_timer = 0;
    }
    _Sti();
}


/***************************************************************
 *  void int_09
 *      Rutina de atención del teclado
 *
****************************************************************/
void int_09(unsigned char scancode) {
    _Cli();
    size_t result = 0;
    const char whitespace = WHITE_TXT;
    char* keys = 0;
    int i = 0;

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
        case PRINT_KBUFFER:
            i = 0;
            while(i < KEYBOARD_BUFFER_SIZE) {
                putc_custom(keypressed_buffer[i++]);
            }
            printf_custom(" %d ", write_kbuffer_ptr);
        break;
        default:
            keys = (l_shift_pressed || r_shift_pressed) ? 
                keyboard_set_mayus : keyboard_set_minus;
            keys -= 1;
            if( scancode >= 0x01 && scancode <= 0x3A && keys[scancode] != '_' ) {
                if(write_kbuffer_ptr >= KEYBOARD_BUFFER_SIZE) {
                    write_kbuffer_ptr = 0;
                } 
                keypressed_buffer[write_kbuffer_ptr] = keys[scancode];
                write_kbuffer_ptr++;
            }
        break;
    }
    _Sti();
}


/***************************************************************/
