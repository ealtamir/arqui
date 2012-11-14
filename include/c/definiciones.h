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
#define TOTAL_WIDTH         SCREEN_WIDTH*CHAR_SIZE
#define SCREEN_SIZE         SCREEN_WIDTH * SCREEN_LENGTH * CHAR_SIZE

// Atributo de video. Letras blancas, fondo negro
#define WHITE_TXT               0x0007 
#define SPACE                   0x2000
#define EMPTY_SPACE             ((WHITE_TXT << 0x08) | (SPACE >> 0x08))
#define SET_CHAR(c)             ((WHITE_TXT << 0x08) | (c))
#define BLINK_COLOR             0x78
#define SET_CHAR_BLINK_ON(c)    ((BLINK_COLOR) << 0x08 | (c))
#define POINTER_BLINK_SPEED     10
#define OS_PID	                0

// File Descriptors POSIX.
#define STDIN               0
#define STDOUT              1
#define STDERR              2

// File Descriptors custom.
#define VCONSOLE            3

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

typedef unsigned short          multiboot_uint16_t;
typedef unsigned int            multiboot_uint32_t;
typedef unsigned long long      multiboot_uint64_t;

/*************************************************************
 *
 *                  ESTRUCTURAS DE DATOS
 * 	
*************************************************************/
/********************************************
 *  FILE   
 *      Estructura que describe un stream. 
 *      NOTA: No copia con toda fidelidad la estructura 
 *      definida por UNIX. Fue modificada para facilitar su
 *      uso.
 *
 *  Elementos:
 *      fd: File Descriptor
 *      size: Tamaño del stream.
 *      buff_ptr: Puntero al buffer de donde se obtiene
 *          el stream (cuando aplique).
*********************************************/
typedef struct {
    int fd;
    unsigned int size;
    char *buff_ptr;
} FILE;

/********************************************
 *  DESCR_SEG   
 *      Descriptor de segmento para la Global Descriptor Table
 *        
 *  Elementos:
 *      limit: Tamaño del segmento al que apunta 
 *          el descriptor.
 *      base: Dirección absoluta de donde empieza 
 *          el segmento (base address).
 *      access: permisos de acceso y otras opciones. 
 *      attribs: parte alta del límite (últimos 4 bits) 
 *          y otros attributos del segmento. 
*********************************************/
typedef struct {
    word limit;
    word base_l;

    byte base_m;
    byte access;
    byte attribs;
    byte base_h;
} DESCR_SEG;


/********************************************
 *  DESCR_INT   
 *      Descriptor de interrupción para la Interrupt
 *  Descriptor Table. 
 *        
 *  Elementos:
 *      offset: Dirección absoluta donde se encuentra la
 *          rutina de atención de interrupción.
 *      selector: Selector del descriptor de segmento para
 *          el segmento en donde se encuentra la rutina
 *          de atención.
 *      cero: Bytes nulos por especificación del fabricante.
 *      access: Propiedades de acceso de la interrupción.
*********************************************/
typedef struct {
    word offset_l;
    word selector;
    byte cero;
    byte access;
    word offset_h;
} DESCR_INT;


/********************************************
 *  IDTR   
 *      Estructura que se utiliza para setear la posición
 *  de la IDT a través de la instrucción lidt.
 *
 *  Elementos:
 *      base: Dirección absoluta de la IDT. 
 *      limit: Tamaño de la IDT.
*********************************************/
typedef struct {
    word  limit;
    dword base;
} IDTR;

struct multiboot_aout_symbol_table
 {
   multiboot_uint32_t tabsize;
   multiboot_uint32_t strsize;
   multiboot_uint32_t addr;
   multiboot_uint32_t reserved;
 };
 typedef struct multiboot_aout_symbol_table multiboot_aout_symbol_table_t;
     
/* The section header table for ELF. */
struct multiboot_elf_section_header_table
{
  multiboot_uint32_t num;
  multiboot_uint32_t size;
  multiboot_uint32_t addr;
  multiboot_uint32_t shndx;
};
typedef struct multiboot_elf_section_header_table multiboot_elf_section_header_table_t;



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
