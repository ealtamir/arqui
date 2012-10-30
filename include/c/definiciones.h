#ifndef _definiciones_
#define _definiciones_

/*************************************************************
 *
 *                      DEFINICIONES GENERALES
 * 	
*************************************************************/
#define CHAR_SIZE           2
#define SCREEN_LENGTH       25
#define SCREEN_WIDTH        80 
#define SCREEN_ADDRESS      0xB8000
#define SCREEN_SIZE         SCREEN_WIDTH * SCREEN_LENGTH * CHAR_SIZE

// Atributo de video. Letras blancas, fondo negro
#define WHITE_TXT           0x07 

#define OS_PID	            0

// File Descriptors POSIX.
#define STDIN               0
#define STDOUT              1
#define STDERR              2

/*************************************************************
 *
 *                      TIPOS DE DATOS GLOBALES
 * 	
*************************************************************/
typedef unsigned char byte;
typedef short int word; 
typedef int dword;

typedef int size_t;
typedef short int ssize_t;


/*************************************************************
 *
 *                  ENUMS Y OTRAS CONSTANTES
 * 	
*************************************************************/
typedef enum eINT_80 { WRITE=0, READ } tINT_80;
typedef enum eUSER { U_KERNEL=0, U_NORMAL } tUSERS;
typedef enum { false, true } bool;

#endif

/*************************************************************/
