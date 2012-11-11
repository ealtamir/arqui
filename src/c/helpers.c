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
    void **param,
    int width,
    int precision,
    int rep,
    bool minus
);

unsigned int parse_fspecifier(
    const char* format, 
    unsigned int params_seen, 
    unsigned int* chars_seen,
    void **param
);

void __stack_chk_fail(void);

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
    unsigned int j = 0;                 // Index
    unsigned int params_seen = 0;       // Número de parámetros
    unsigned int chars_seen = 0;        // Número de chars impresos.
    unsigned int printd_chars = 0;      // Número de chars impresos.
    
    // Puntero al parámetro que voy a usar a continuación
    // Los parámetros están inmediatamente después del string de
    // format. Sumo 1 para incluir el null character.
    void *param = format - strlen_custom(format) + 1;

    for(j = 0; j < 300; j++) {
        putc_custom(((char*)format)[j]);
    }
    
    // El string apuntado por format debe terminar con un
    // caracter '\0'.
    for(i = 0; format[i] != '\0'; i++) {
        if(format[i] == '%') {
            printd_chars += parse_fspecifier(
                format,
                params_seen,
                &chars_seen,
                &param
            );
            params_seen++;
            
            // Adelanto hasta el fin del especificador.
            i += chars_seen;
        } else {
            putc_custom(format[i]);
            printd_chars++;
        }
    }
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
    unsigned int params_seen,
    unsigned int* chars_seen,
    void **param
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
        param,
        atoi(width),
        atoi(precision),
        rep,
        minus
    );
}

/***************************************************************
*   unsigned int  print_param
*
****************************************************************/
unsigned int  print_param(
    char format,
    void **param,
    int width,
    int precision,
    int rep,
    bool minus
) {
    unsigned int i = 0;             // index
    unsigned int str_len = 0;
    char *str = *param;

    str_len = strlen_custom(str);

    switch(format) {
        case 'd':case 'i':  // integer
            break;
        case 'o':           // unsigned octal number
            break;
        case 'x': case 'X': // Prints in hex
            break;
        case 'u':           // unsigned decimal number
            break;
        case 'c':           // single character
            break;
        case 's':           // string
            // it must end with \0 or the number of chars
            // must be given by the precision.
            printf_custom("Hasta aca llego!");
            printf_custom(str);

            for(i = 0; i < str_len; i++) {
                putc_custom(str[i]);
            }
            (*param) -= str_len - 1;
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
    return str_len;
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

void __stack_chk_fail(void) {
}
/****************************************************************/
