#include "../../../include/c/stdlibs/ctype.h"
#include "../../../include/c/definiciones.h"
/***************************************************************
*
*                          ctype 
*
****************************************************************/
/***************************************************************
*
*   Las siguientes funciones buscan imitar la funcionalidad de 
*   alguna de las funciones que incluye C en su librería ctype.
*
****************************************************************/
bool isupper(int c) {
    return ('A' <= c && c <= 'Z') ? true : false;
}


bool islower(int c) {
    return ('a' <= c && c <= 'z') ? true : false;
}


bool isdigit(int c) {
    return ('0' <= c && c <= '9') ? true : false;
}


bool isalpha(int c) {
    return (isupper(c) || islower(c)) ? true : false;
}


bool isalnum(int c) {
    return (isalpha(c) || isdigit(c)) ? true : false;
}

bool ishex(int c) {
    return ( ('A' <= c && 'Z' >= c)
            || ('a' <= c && 'z' >= c)
            || isdigit(c)) ? true : false;
}


/****************************************************************/
