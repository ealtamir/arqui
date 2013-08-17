#include "../../include/c/definiciones.h"
#include "../../include/c/video.h"
#include "../../include/c/stdlibs/string.h"
#include "../../include/c/stdlibs/ctype.h"
#include "../../include/c/helpers.h"
#include "../../include/c/shell.h"
#include "../../include/c/malloc.h"
#include "../../include/c/infoidt.h"
#include "../../include/c/tests.h"

void parse_shell_input(char* input_str);
void init_fcall_vector();

void print_test(char* params);
void divide_by_cero(char* params);
void test_command(char* params);
void help(char* params);

unsigned int loaded_commands = 0;

typedef struct {
    char* f_name;
    char* help;
    void (*f)(char*);
} f_call;

#define FCALL_VECTOR_SIZE       50

f_call commands[FCALL_VECTOR_SIZE];

/***************************************************************
* int shell
*
****************************************************************/
int shell() {
    const char *prompt = "#> ";
    char c = '\0';
    char input_buffer[SCREEN_WIDTH - 4]; //TODO: MAGIC NUMBER
    unsigned int prompt_len = strlen_custom(prompt);
    unsigned int i = 0;

    init_fcall_vector();
    memset_custom(input_buffer, sizeof(input_buffer), '\0');

    set_col(0); set_row(0);
    clear_vscreen();
    print_vscreen();

    while(1) {
        print_str(prompt);
        print_vscreen();
        c = '\0';
        while( c != '\n' ) {
            c = getc();
            if( (isdigit(c) == true || isalpha(c) == true || c == ' ')
                    && i < sizeof(input_buffer)  ) {
                print_chr(c);
                input_buffer[i] = c;
                i++;
                print_vscreen();
            } else if ( c == '\b' && get_col() >= sizeof(prompt)) {
                backspace();
                i--;
                input_buffer[i] = '\0';
                print_vscreen();
            }
        }
        if( input_buffer[0] != '\0' ) {
            parse_shell_input(input_buffer);
        }
        newline();
        i = 0;
        memset_custom(input_buffer, sizeof(input_buffer), '\0');
    }
    return 0;
}
void parse_shell_input(char* input_str) {
    char cmd_name[SCREEN_WIDTH];
    char* params = 0;
    bool f_called = false;
    unsigned int i = 0;
    unsigned int len = 0;

    memset_custom(cmd_name, sizeof(cmd_name), '\0');

    sscanf_custom(input_str, "%s", cmd_name);
    len = strlen_custom(cmd_name);

    // No estoy pisando código ajeno porque
    // input_str es bastante grande.
    params = &input_str[len + 1];

    for(i = 0; i < FCALL_VECTOR_SIZE; i++) {
        if( strcmp(commands[i].f_name, cmd_name) == 0 ) {
            commands[i].f(params);
            f_called = true;
        }
    }
    if(f_called == false) {
        newline();
        vprintf_custom("Ese comando no existe. ");
        vprintf_custom("Escribe \'help\' para obtener una lista de comandos.");
    }

}

void init_fcall_vector() {
    unsigned int i = 0;

    memset_custom((char*)commands, sizeof(commands), 0);

    commands[i].f_name = "testcommand";
    commands[i].help = "Comando de prueba para chequear el funcionamiento del shell.";
    commands[i].f = (void (*)()) &test_command;
    i++;

    commands[i].f_name = "help";
    commands[i].help = "Imprime los comandos disponibles para el usuario.";
    commands[i].f = (void (*)()) &help;
    i++;

    commands[i].f_name = "malloc";
    commands[i].help = "Le permite al usuario alocar memoria y ver la memoria alocada.";
    commands[i].f = (void (*)()) &malloc_command;
    i++;

    commands[i].f_name = "free";
    commands[i].help = "Permite liberar memoria que fue alocada previamente por el usuario.";
    commands[i].f = (void (*)()) &free_command;
    i++;

    commands[i].f_name = "infoidt";
    commands[i].help = "Permite al usuario activar y desactivar interrupciones.";
    commands[i].f = (void (*)()) &infoidt_command;
    i++;

    commands[i].f_name = "dividebyzero";
    commands[i].help = "Hace una division por cero. Util para probar la int 00.";
    commands[i].f = (void (*)()) &divide_by_cero;
    i++;

    commands[i].f_name = "printtests";
    commands[i].help = "Imprime varios strings para testear la funcion printf.";
    commands[i].f = (void (*)()) &print_test;
    i++;

    loaded_commands = i;
}

void q_to_continue(unsigned int row, unsigned int col, int clear) {
    char c = '\0';
    unsigned prev_row = get_row();
    unsigned prev_col = get_col();

    set_row(row); set_col(col);
    vprintf_custom("Presiona \'q\' para continuar...");
    print_vscreen();

    while(1) {
        c = getc();
        if(c == 'q'){
            break;
        }
    }
    if( clear != 0) {
        set_row(0); set_col(0);
        clear_vscreen();
    }
}

void test_command(char* params) {
    clear_vscreen();
    set_row(2); set_col(2);
    vprintf_custom("Is this just real life? Is this just fantasy...");
    q_to_continue(4, 4, 1);
}

void help(char* params) {
    unsigned int i = 0;

    clear_vscreen();
    set_col(1); set_row(1);
    for(i = 0; i < loaded_commands; i++) {
        vprintf_custom("%s", commands[i].f_name);
        set_col(15);
        vprintf_custom("%s", commands[i].help);
        newline();
        set_col(1);
    }
    q_to_continue(SCREEN_LENGTH - 1, 1, 1);

}

void divide_by_cero(char* params) {
    newline();
    vprintf_custom("Intentando dividir por cero.");
    q_to_continue(5, 2, 0);

    int a = 0;

    a++;
    a++;
    a++;
    a--;
    a--;
    a--;

    1 / a;
    1 / a;
    1 / a;
    1 / a;
}

void print_test(char* params) {
    clear_vscreen();

    vprintf_tests();

    q_to_continue(SCREEN_LENGTH-1, 2, 1);
}
