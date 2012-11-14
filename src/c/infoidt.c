#include "../../include/c/interrupciones/definiciones.h"
#include "../../include/c/interrupciones/helpers.h"
#include "../../include/c/interrupciones/funciones_de_atencion.h"
#include "../../include/c/interrupciones/handlers.h"
#include "../../include/c/helpers.h"
#include "../../include/c/infoidt.h"

int add_idt_entry(DESCR_INT* idt_entry, unsigned int number) {
    if( number >= IDT_SIZE ) {
        return -1;
    }

    void* handlers[IDT_SIZE] = {
        (void*) &_int_00_hand,
        (void*) &_int_01_hand,
        (void*) &_int_02_hand,
        (void*) &_int_03_hand,
        (void*) &_int_04_hand,
        (void*) &_int_05_hand,
        (void*) &_int_06_hand,
        (void*) &_int_07_hand,
    };

    DESCR_INT* idt = get_idt();
    
    _Cli();
    setup_IDT_entry(
        &idt[number], 
        0x08, 
        (dword) (handlers[number]), 
        ACS_INT,
        0
    );
    _Sti();

    
}

int del_idt_entry(unsigned int entry_num) {
    if(entry_num >= IDT_SIZE) {
        return false;
    }
    DESCR_INT* idt = get_idt();

    _Cli();
    memset_custom((char*)&idt[entry_num], sizeof(DESCR_INT), 0);
    _Sti();

    return true;
}
