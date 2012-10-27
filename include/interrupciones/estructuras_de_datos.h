#ifndef _interrupciones_
#define _interrupciones_

/*************************************************************
 *
 *                  ESTRUCTURAS DE DATOS
 * 	
 ************************************************************/
#include "../definiciones.h"

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

#endif

/***************************************************************/
