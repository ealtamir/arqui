#ifndef helpers
#define helpers
/***************************************************************
 *
 *              FUNCIONES DE GENERALES
 *
****************************************************************/

#include "definiciones.h"

#ifndef WHITE_TXT
#define WHITE_TXT 0x07 
#endif

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
 *   k_clear_screen
 *       Borra la pantalla utilizando WHITE_TXT como color.
 *
****************************************************************/
void k_clear_screen();


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
*   int fprintf
*       Versión general de printf que imprime la cadena format
*           al stream que se le pase y no solo al stdout.
*
*   Recibe:
*       stream: Estructura FILE que contiene información 
*           del stream.
*       format: Puntero al string a formatear e imprimir.
*       ...: cantidad variable de argumentos que indican cómo
*           será formateado el string format.
*   devuelve:
*       regresa el número de caracteres impresos. 
*
****************************************************************/
int fprintf(FILE *stream, char *format, ... );

/****************************************************************
*   FILE get_stdout
*       Devuelve una estructura que representa el stdout.      
*
****************************************************************/
FILE get_stdout();

/***************************************************************
 * unsigned int _read_msw
 *
****************************************************************/
unsigned int _read_msw();


#endif
