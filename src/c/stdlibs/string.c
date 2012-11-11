#include "../../../include/c/stdlibs/string.h"

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

/****************************************************************/
