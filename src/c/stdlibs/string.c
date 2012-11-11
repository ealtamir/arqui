#include "../../../include/c/stdlibs/string.h"
#include "../../../include/c/definiciones.h"
#include "../../../include/c/helpers.h"

/***************************************************************
 *
 *                      FUNCIONES 
 *
****************************************************************/
/****************************************************************
*   int strlen_custom
*
****************************************************************/
unsigned int strlen_custom(const char* str) {
    int i = 0;
    while( str[i] == '\0' ) {
        i++;
    }
    return i;
}

/****************************************************************
*   unsigned int atoi
*       Devuelve la representación decimal de un número en ASCII.
*
****************************************************************/
unsigned int atoi(const char *s) {
    unsigned int buffer = 0;
    int count = 1;
    int i = 0;  // Index
    while( s[i] != '\0' ) { i++; }
    --i;
    while( i >= 0 ) {
        buffer += (s[i] - '0') * count;
        count *= 10;
        --i;
    }
    return buffer;
}


/****************************************************************
*   void itoa
*       Devuelve la representación en ASCII de un dígito que se le
*           pasa como parámetro.
*
****************************************************************/
void itoa(int value, char *sp, int buff_size) {
    bool is_minus = 0;
    char tmp[16];
    char *tp = tmp;
    int i = 0;
    unsigned int v = 0;

    memset_custom(sp, buff_size, '\0');

    is_minus = (value < 0) ? true : false;

    if (is_minus) {
        v = -value;
    } else {
        v = (unsigned)value;
    }    

    while (v || tp == tmp) {
        i = v % 10;     // obtengo el dígito menos significativo
        v /= 10;        // refuzco en 1 cifra el número 
        if (i < 10)
          *tp++ = i+'0';
        else
          *tp++ = i + 'a' - 10;
    }

    if (is_minus) {
        *sp++ = '-'; // Agrego el negativo si hace falta.
    }
    while (tp > tmp) {
        *sp++ = *--tp; // pongo en el orden correcto el número.
    }
}
/****************************************************************/
