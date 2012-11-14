#ifndef stdlibs_string
#define stdlibs_string

/***************************************************************
 *
 *                      FUNCIONES 
 *
****************************************************************/
/****************************************************************
*   unsigned int atoi
*       Devuelve la representación decimal de un número en ASCII.
*
****************************************************************/
unsigned int atoi(const char *s);


/****************************************************************
*   int strlen_custom
*
****************************************************************/
unsigned int strlen_custom(const char* str);


/****************************************************************
*   void itoa
*       Devuelve la representación en ASCII de un dígito que se le
*           pasa como parámetro.
*
****************************************************************/
void itoa(int value, char *sp, int buff_size);


/****************************************************************
*   void itoa
*       Devuelve la representación en ASCII de un dígito que se le
*           pasa como parámetro.
*
****************************************************************/
void toHex(int d, char* str, int debug);


/****************************************************************/
#endif
