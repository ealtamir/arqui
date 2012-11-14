#include "../../include/c/definiciones.h"
#include "../../include/c/video.h"
#include "../../include/c/stdlibs/string.h"
#include "../../include/c/stdlibs/ctype.h"
#include "../../include/c/helpers.h"
#include "../../include/c/shell.h"

/***************************************************************
* int shell
*
****************************************************************/

int shell() {
    const char *prompt = "#> ";
    char c = 0;
    // 3 por la longitud del prompt.
    char input_buffer[SCREEN_WIDTH - 4]; //TODO: MAGIC NUMBER
    unsigned int prompt_len = strlen_custom(prompt);
    unsigned int i = 0;

    memset_custom(input_buffer, sizeof(input_buffer), '\0');

    set_col(0);
    set_row(0);
    clear_vscreen();
    print_vscreen();
    

    while(1) {
        print_str(prompt);
        print_vscreen();
        c = '\0';
        while( c != '\n' ) {
            c = getc();
            if( (isalpha(c) == true || c == ' ') && i < sizeof(input_buffer)  ) {
                print_chr(c);
                input_buffer[i] = c;
                i++;
                print_vscreen();
            } else if ( c == '\b' && get_col() > 3) { //TODO: MAGIC NUMBER
                backspace();
                i--;
                input_buffer[i] = '\0';
                print_vscreen();
            }
        }
        newline();
        i = 0;
        memset_custom(input_buffer, sizeof(input_buffer), '\0');
    }
    return 0;
}
