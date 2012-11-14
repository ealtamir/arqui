#ifndef helpers
#define helpers
/***************************************************************
 *
 *              FUNCIONES DE GENERALES
 *
****************************************************************/

#include "definiciones.h"


#define va_start(v,l) __builtin_va_start(v,l)
#define va_arg(v,l)   __builtin_va_arg(v,l)
#define va_end(v)     __builtin_va_end(v)
#define va_copy(d,s)  __builtin_va_copy(d,s)

typedef __builtin_va_list va_list;

/***************************************************************
*   void showSplashScreen
*
****************************************************************/
void showSplashScreen();


/***************************************************************
 *   void wait
 *       Espera una determinada cantidad de tiempo
 *
 *   Recibe:
 *       time: La cantidad de tiempo de tiempo que debe esperar la función.
****************************************************************/
void wait(unsigned int time);


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
void memset_custom(char *ptr, int size, char value);


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
int putc_custom(int c);


/***************************************************************
*   int fgetc
*
*
****************************************************************/
int fgetc(FILE *stream);


/***************************************************************
*   int getc
*
*
****************************************************************/
int getc();


/***************************************************************
*   int vprintf_custom
*
*
****************************************************************/
int vprintf_custom(char *format, ... );


/***************************************************************
*   int scanf
*
*
****************************************************************/
int scanf(const char *format, ... );

/***************************************************************
*   int fprintf_custom
*
*
****************************************************************/
//int fprintf_custom(FILE *stream, char *format, va_list *args);


/***************************************************************
*   int fscanf_custom
*
*
****************************************************************/
//int fscanf_custom(FILE *stream, const char *format, va_list *args);


/***************************************************************
*   int vsscanf_custom
*
*
****************************************************************/
//int vsscanf_custom(const char* s, const char* format, va_list *args);


/***************************************************************
*   int sscanf_custom
*
*
****************************************************************/
//int sscanf_custom(const char* s, const char* format, ...);

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
int fputc(int c, FILE *stream);


/***************************************************************
*   int vputc_custom
*       Coloca un caracter en la consola virtual
*
****************************************************************/
int vputc_custom(int c);


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
int printf_custom(char *format, ... );

/***************************************************************
*   int vprintf_custom
*
*
****************************************************************/
int vprintf_custom(char *format, ... );


/****************************************************************
*   FILE get_stdout
*       Devuelve una estructura que representa el stdout.      
*
****************************************************************/
FILE get_stdout();


/****************************************************************
*   FILE get_stdin
*       Devuelve una estructura que representa el stdin.      
*
****************************************************************/
FILE get_stdin();

/****************************************************************
*   FILE get_vconsole
*       Devuelve una estructura que representa el stream de
*           la consola virtual utilizada por video.c.      
*
****************************************************************/
FILE get_vconsole();

/***************************************************************
 * unsigned int _read_msw
 *
****************************************************************/
unsigned int _read_msw();

int vsscanf_custom(const char* s, const char* format, va_list *args);
int sscanf_custom(const char* s, const char* format, ...);
int fscanf_custom(FILE *stream, const char *format, va_list *args);
int fprintf_custom(FILE *stream, char *format, va_list *args);

#endif
