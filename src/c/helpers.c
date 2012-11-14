#include "../../include/c/definiciones.h"
#include "../../include/c/helpers.h"
#include "../../include/c/primitivas.h"
#include "../../include/c/stdlibs/ctype.h"
#include "../../include/c/stdlibs/string.h"
#include "../../include/c/video.h"

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

typedef struct {
    bool minus;
    char specifier;
    char rep;
    char width[5];
    char precision[5];
} Format;

typedef enum { 
    STARTING_PARSE,
    MINUS_FOUND,
    READING_WIDTH,
    POINT_FOUND,
    READING_PRECISION,
    REP_CHAR_FOUND
} PRINTF_STATES;

unsigned int  process_params(
    char format,
    Format format_spec,
    va_list *args,
    FILE* stream
);

unsigned int parse_fspecifier(
    char* format,
    Format* format_spec
);

void __stack_chk_fail(void);
void printstr(char *s);
int fprintf_custom(FILE *stream, char *format, va_list *args);
int fscanf_custom(FILE *stream, const char *format, va_list *args);
int process_int(int fd, Format format_spec, va_list* args);
int process_str(int fd, Format format_spec, va_list* args);
int process_unsgn(int fd, Format format_spec, va_list* args);
int process_hex(int fd, Format format_spec, va_list* args);

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
int fscanf_custom(FILE *stream, const char* format, va_list *args) {
    char c = '\0';
    char input[256];
    unsigned int buffer_size = 0;
    unsigned int i = 0;     
    
    buffer_size = sizeof(input);
    memset_custom(input, sizeof(input), '\0');

    while(i < sizeof(input) && c != '\n') {
        c = getc(); 
        input[i] = c;
        i++;
    }
    // Reemplazo el último caracter por \0.
    input[i-1] = '\0' ;
    printf_custom("%s", input);
    return i - 1; // Resto porque dejo i adelantado.

}


/***************************************************************
*   int scanf
*
*
****************************************************************/
int scanf(const char *format, ... ) {
    int read_chars;
    va_list args;

    va_start(args, format);
    FILE stdin = get_stdin();
    read_chars = fscanf_custom(&stdin, format, &args);
    va_end(args);

    return read_chars;
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
*   int vputc_custom
*   
*
****************************************************************/
int vputc_custom(int c) {
    FILE vconsole = get_vconsole();
    return fputc(c, &vconsole);
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
    int result = 0;
    char whitespace = WHITE_TXT;

    unsigned char new_char = (unsigned char) c;

    switch(fd) {
        case STDOUT:
            result = __write(fd, (const void*) &c, count);
            // TODO:
            // if (result != count) {
            //     // Do Something 
            // }
            result = __write(fd, (const void*) &whitespace, count);
        break;
        case VCONSOLE:
            print_chr((char)c);
        break;
    }
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
int fprintf_custom(FILE *stream, char *format, va_list *args) {
    // Cuenta la cantidad de parámetros que se le pasan a la función
    // a partir de la cantidad de especificadores de formato %
    // que contenga el string.
    
    unsigned int i = 0;                 // Index
    unsigned int chars_seen = 0;        // Número de chars impresos.
    int printd_chars = 0;      // Número de chars impresos.
    Format format_spec;

    for(i = 0; format[i] != '\0'; i++) {
        if(format[i] == '%') {
            i += parse_fspecifier(
                format + i, // Puntero al % actual.
                &format_spec
            );
            printd_chars += process_params(
                format[i],
                format_spec,
                args,
                stream
            );

        } else {
            fputc(format[i], stream);
            printd_chars++;
        }
    }
    return printd_chars;

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
    int printed_chars = 0;
    va_list args;

    va_start(args, format);
    FILE stdout = get_stdout();
    printed_chars = fprintf_custom(&stdout, format, &args);
    va_end(args);

    return printed_chars;
}

/***************************************************************
*   int vprintf_custom
*       Imprime el string en la consola virtual definida en
*           el archivo video.c
****************************************************************/
int vprintf_custom(char *format, ... ) {
    int printd_chars = 0;
    va_list args;

    va_start(args, format);
    FILE vconsole = get_vconsole();
    printd_chars = fprintf_custom(&vconsole, format, &args);
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
unsigned int parse_fspecifier(char* format, Format* format_spec) {

    PRINTF_STATES state = STARTING_PARSE;
    char c = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    
    memset_custom(format_spec->width, sizeof(format_spec->width), 0);
    memset_custom(format_spec->precision, sizeof(format_spec->precision), 0);
    
    // Justo depués de  encontrar un % espero leer h, l, una cifra
    // representando el width o una representando precision, pero
    // no un caracter que indica el formato, por eso me detengo
    // si encuentro un caracter alfabético.
    c = format[i];
    while(isalpha(c) == false || c == 'h' || c == 'l') {
        switch(c) {
            case '%':
                // No hace nada.
                break;
            case '-':
                format_spec->minus = true;
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
                    if( j < sizeof(format_spec->width) - 1) // Ultimo lugar de width es \0
                        format_spec->width[j++] = c;
                }
                else if (state == POINT_FOUND
                         || state == READING_PRECISION) {
                    state = READING_PRECISION;
                    if( j < sizeof(format_spec->precision) - 1) // Ultimo lugar de width es \0
                        format_spec->precision[j++] = c;
                }
                break;
            case 'h':
                if (format_spec->rep == 0
                    && state != POINT_FOUND
                    && state != MINUS_FOUND)
                    format_spec->rep = 'h';
                else
                    // TODO: STOP EXECUTION
                    break;
            case 'l':
                if (format_spec->rep == 0
                    && state != POINT_FOUND
                    && state != MINUS_FOUND)
                    format_spec->rep = 'l';
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
        // Get next char in the format specifier string.
        i++;
        c = format[i];
    }
    return i;
}

/***************************************************************
*   unsigned int  process_params
*
****************************************************************/
unsigned int  process_params(
    char format,
    Format format_spec,
    va_list *args,
    FILE* stream
) {
    unsigned int chars_num = 0;     // Chars impresos o leídos.


    switch(format) {
        case 'd':case 'i':  // integer
            chars_num = process_int(stream->fd, format_spec, args);
            break;
        case 'o':           // unsigned octal number
            break;
        case 'x': case 'X': // Prints in hex
            chars_num = process_hex(stream->fd, format_spec, args);
            break;
        case 'u':           // unsigned decimal number
            chars_num = process_unsgn(stream->fd, format_spec, args);
            break;
        case 'c':           // single character
            break;
        case 's':           // \0 terminated string
            chars_num = process_str(stream->fd, format_spec, args);
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
int process_hex(int fd, Format format_spec, va_list* args) {
    char num_str[20];
    unsigned int len = 0;
    unsigned int num = 0;

    memset_custom(num_str, sizeof(num_str), '\0');
    num = va_arg(*args, unsigned int);
    toHex(num, num_str, 1);

    switch(fd) {
        case STDOUT:
            printstr(num_str);
            len = strlen_custom(num_str);
        break;
        case VCONSOLE:
            print_str(num_str);
            len = strlen_custom(num_str);
        break;
    }
    return len;
}

int process_unsgn(int fd, Format format_spec, va_list* args) {
    unsigned int num = 0;
    unsigned int len = 0;
    char num_str[20];

    memset_custom(num_str, sizeof(num_str), '\0');
    num = va_arg(*args, unsigned int);
    itoa(num, num_str, sizeof(num_str));

    switch(fd) {
        case STDOUT:
            printstr(num_str);
            len = strlen_custom(num_str);
        break;
        case VCONSOLE:
            print_str(num_str);
            len = strlen_custom(num_str);
        break;
    }
    return len;
}
int process_int(int fd, Format format_spec, va_list* args) {
    int num = 0;
    unsigned int len = 0;
    char num_str[20];

    memset_custom(num_str, sizeof(num_str), '\0');
    num = va_arg(*args, int);
    itoa(num, num_str, sizeof(num_str));

    switch(fd) {
        case STDOUT:
            printstr(num_str);
            len = strlen_custom(num_str);
        break;
        case VCONSOLE:
            print_str(num_str);
            len = strlen_custom(num_str);
        break;
    }
    return len;
}

int process_str(int fd, Format format_spec, va_list* args) {
    char* str = 0;
    unsigned int len = 0;
    str = va_arg(*args, char* );
    
    switch(fd) {
        case STDOUT:
            printstr(str);
            len = strlen_custom(str);
        break;
        case VCONSOLE:
            print_str(str);
            len = strlen_custom(str);
        break;
    }
    return len;
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


/****************************************************************
*   FILE get_stdout
*       Devuelve una estructura que representa el stdout.      
*
****************************************************************/
FILE get_vconsole() {
    FILE vconsole = { VCONSOLE, 0, 0 };
    return vconsole;
}

void __stack_chk_fail(void) {
}
/****************************************************************/
