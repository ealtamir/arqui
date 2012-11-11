#include "../../include/c/definiciones.h"
#include "../../include/c/helpers.h"
#include "../../include/c/primitivas.h"
#include "../../include/c/stdlibs/ctype.h"
#include "../../include/c/stdlibs/string.h"

/***************************************************************
 *
 *                      FUNCIONES 
 *
****************************************************************/

#define va_start(v,l) __builtin_va_start(v,l)
#define va_arg(v,l)   __builtin_va_arg(v,l)
#define va_end(v)     __builtin_va_end(v)
#define va_copy(d,s)  __builtin_va_copy(d,s)

typedef __builtin_va_list va_list;

typedef enum { 
    STARTING_PARSE,
    MINUS_FOUND,
    READING_WIDTH,
    POINT_FOUND,
    READING_PRECISION,
    REP_CHAR_FOUND
} PRINTF_STATES;

unsigned int  print_param(
    char format,
    int width,
    int precision,
    int rep,
    bool minus,
    va_list *args
);

unsigned int parse_fspecifier(
    const char* format, 
    unsigned int* chars_seen,
    va_list *args
);

void __stack_chk_fail(void);
void printstr(char *s);

/***************************************************************
*   k_clear_screen
*       Borra la pantalla en modo texto color.
*
****************************************************************/
void k_clear_screen() 
{
	unsigned int i = 0;
    int whitespace = ' ';
    int result = 0;

    // TODO: Sacar esta función y utilizar un buffer a la pantalla.
    reset_tickpos();

    for (i = 0; i < SCREEN_LENGTH * SCREEN_WIDTH; i++) {
        result = putc_custom(whitespace);
        // TODO:
        //if (result == error) {
        //    // Do something.
        //}
    }

    reset_tickpos();
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

/***************************************************************
*   int fgetc
*
*
****************************************************************/
int fgetc(FILE *stream) {
    int fd = stream->fd;    // STDOUT por lo general.
    int count = 1;          // caracteres a leer.
    int buffer = 0;         // almacena el caracter leído.
    int result = 0;         // cant de chars leídos.
    fflush(STDIN);

    result = __read(fd, (void*) &buffer, count);
    return buffer;
}


/***************************************************************
*   int getc
*       Obtiene un caracter del STDIN. En este caso, el teclado.
*
*
****************************************************************/
int getc() {
    FILE stdin = get_stdin();
    return fgetc(&stdin);
}


/***************************************************************
*   int scanf
*
*
****************************************************************/
int scanf(const char *format, ... ) {
}


/***************************************************************
*   int putc_custom
*       Escribe el caracter c (convertido a unsigned char) en
*           el stdout.
*
*   Recibe:
*       c: Caracter a escribir en el stream.
*   Devuelve:
*       El caracter escrito o EOF, si hubo algún error.
*
****************************************************************/
int putc_custom(int c) {
    FILE stdout = get_stdout();
    return fputc(c, &stdout);
}


/***************************************************************
*   int fputc
*       Escribe el caracter c (convertido a un unsigned char) en
*           stream. Devuelve el caracter escrito o EOF, si hubo
*           algún error.
*
*   Recibe:
*       c: Caracter a escribir en el stream.
*       stream: Un puntero a una estructura FILE que contiene
*           información sobre el stream sobre el cual se escribirá
*           la información.
*   Devuelve:
*       El caracter escrito o EOF, si hubo algún error.
*
****************************************************************/
int fputc(int c, FILE *stream) {
    int fd = stream->fd;    // STDOUT por lo general.
    int count = 1;
    char whitespace = WHITE_TXT;

    unsigned char new_char = (unsigned char) c;

    int result = __write(fd, (const void*) &c, count);
    // TODO:
    // if (result != count) {
    //     // Do Something 
    // }
    result = __write(fd, (const void*) &whitespace, count);
    return result;
}


/***************************************************************
*   int fprintf
*       Versión general de printf que imprime la cadena format
*           al stream que se le pase y no solo al stdout.
*
*   Recibe:
*       stream: Estructura FILE que contiene información 
*           del stream.
*       format: Puntero al string a formatear e imprimir.
*       arg* cantidad variable de argumentos que indican cómo
*           será formateado el string format.
*   devuelve:
*       regresa el número de caracteres impresos. 
*
****************************************************************/
int fprintf(FILE *stream, char *format, ... ) {

}


/***************************************************************
*   int printf
*       Convierte, formatea e imprime la cadena de caracteres 
*           format en el stdout. La cadena apuntada por format
*           debe terminar con el null character '\0'.
*
*   Recibe:
*       format: Puntero al string a formatear e imprimir.
*       arg*: Cantidad variable de argumentos que indican cómo
*           será formateado el string format.
*   Devuelve:
*       Regresa el número de caracteres impresos. 
*
****************************************************************/
int printf_custom(char *format, ... ) {
    // Cuenta la cantidad de parámetros que se le pasan a la función
    // a partir de la cantidad de especificadores de formato %
    // que contenga el string.
    
    // bool leave = false;
    unsigned int i = 0;                 // Index
    unsigned int params_seen = 0;       // Número de parámetros
    unsigned int chars_seen = 0;        // Número de chars impresos.
    unsigned int printd_chars = 0;      // Número de chars impresos.

    void* param = format;

    va_list args;
    va_start(args, format);

    for(i = 0; format[i] != '\0'; i++) {
        if(format[i] == '%') {
            printd_chars += parse_fspecifier(
                format + i,
                &chars_seen,
                &args
            );
            params_seen++;
            
            // Adelanto hasta el fin del especificador.
            i += chars_seen;
        } else {
            putc_custom(format[i]);
            printd_chars++;
        }
    }
    va_end(args);
    return printd_chars;
}


/***************************************************************
*   unsigned int parse_fspecifier
*       Parsea el especificador de formato que obtiene del
*           string "format".
*
*   Recibe:
*       format: Puntero al string a formatear e imprimir.
*       params_seen: Cantidad de especificadores que ya procesé.
*       param: Puntero a la lista de parámetros.
*       chars_seen: Señala cuántos caracteres del especificador de 
*           formato se leyeron.
*   Devuelve:
*       Regresa la cantidad de caracteres impresos.
*
****************************************************************/
unsigned int parse_fspecifier(
    const char* format,
    unsigned int* chars_seen,
    va_list *args
) {
    
    PRINTF_STATES state = STARTING_PARSE;
    bool minus = false;                 // Dice si aparece un símbolo de '-'
    char c = 0;
    char rep = 0;                       // Dice si aparece h o l.
    char width[5];                      // Dígitos que representan el width.
    char precision[5];                  // Dígitos que representan la precisión.
    unsigned int i = 0;
    unsigned int j = 0;
    
    memset_custom(width, sizeof(width), 0);
    memset_custom(precision, sizeof(precision), 0);
    
    c = format[i];
    // Justo depués de  encontrar un % espero leer h, l, una cifra
    // representando el width o una representando precision, pero
    // no un caracter que indica el formato, por eso me detengo
    // si encuentro un caracter alfabético.
    while(isalpha(c) == false || c == 'h' || c == 'l') {
        switch(c) {
            case '%':
                // No hace nada.
                break;
            case '-':
                minus = true;
                state = MINUS_FOUND;
                break;
            case '.':
                state = POINT_FOUND;
                j = 0;
                break;
            case '1': case '2': case '3':
            case '4': case '5': case '6':
            case '7': case '8': case '9':
                if (state == MINUS_FOUND
                    || state == STARTING_PARSE
                    || state == READING_WIDTH) {
                    state = READING_WIDTH;
                    if( j < sizeof(width) - 1) // Ultimo lugar de width es \0
                        width[j++] = c;
                }
                else if (state == POINT_FOUND
                         || state == READING_PRECISION) {
                    state = READING_PRECISION;
                    if( j < sizeof(precision) - 1) // Ultimo lugar de width es \0
                        precision[j++] = c;
                }
                break;
            case 'h':
                if (rep == 0
                    && state != POINT_FOUND
                    && state != MINUS_FOUND)
                    rep = 'h';
                else
                    // TODO: STOP EXECUTION
                    break;
            case 'l':
                if (rep == 0
                    && state != POINT_FOUND
                    && state != MINUS_FOUND)
                    rep = 'l';
                else
                    // TODO: STOP EXECUTION
                    break;
            default:
                // TODO: STOP EXECUTION
                break;
        }
        if ( state == POINT_FOUND ) {
            // TODO: STOP EXECUTION
        }
        i++;
        c = format[i];
    }
    // Indica cuantos caracteres se leyeron
    // apenas se encontró el % del especificador
    // (incluye a % en la cuenta).
    *chars_seen = i;
    
    return print_param(
        format[i],
        atoi(width),
        atoi(precision),
        rep,
        minus,
        args
    );
}

/***************************************************************
*   unsigned int  print_param
*
****************************************************************/
unsigned int  print_param(
    char format,
    int width,
    int precision,
    int rep,
    bool minus,
    va_list *args
) {
    int num = 0;                    
    unsigned int i = 0;             // index
    unsigned int chars_num = 0;     // Chars impresos
    char* str = 0;                  // Uso para apuntar a strings
    char num_str[20];


    switch(format) {
        case 'd':case 'i':  // integer
            num = va_arg(*args, int);
            itoa(num, num_str, sizeof(num_str));
            chars_num = strlen_custom(num_str);
            printstr(num_str);
            break;
        case 'o':           // unsigned octal number
            break;
        case 'x': case 'X': // Prints in hex
            break;
        case 'u':           // unsigned decimal number
            break;
        case 'c':           // single character
            break;
        case 's':           // \0 terminated string
            chars_num = strlen_custom(str);
            str = va_arg(*args, char* );
            printstr(str);
            break;
        case 'f':           // double
            break;
        case 'e':case 'E':  // double exp notation
            break;
        case '%':           // prints %
            break;
        case '.':
            break;
        default:
            // TODO: STOP EXECUTION.
            break;
    }
    return chars_num;
}


/****************************************************************
*   FILE get_stdout
*       Devuelve una estructura que representa el stdout.      
*
****************************************************************/
void printstr(char *s) {
    unsigned int i = 0;
    for(i = 0; s[i] != '\0'; i++) {
        putc_custom(s[i]);
    }
}

/****************************************************************
*   FILE get_stdout
*       Devuelve una estructura que representa el stdout.      
*
****************************************************************/
FILE get_stdout() {
    FILE stdout = { STDOUT, 0, 0 };
    return stdout;
}
/****************************************************************
*   FILE get_stdout
*       Devuelve una estructura que representa el stdout.      
*
****************************************************************/
FILE get_stdin() {
    FILE stdin = { STDIN, 0, 0 };
    return stdin;
}

void __stack_chk_fail(void) {
}
/****************************************************************/
