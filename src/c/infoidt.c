#include "../../include/c/interrupciones/definiciones.h"
#include "../../include/c/interrupciones/helpers.h"
#include "../../include/c/interrupciones/funciones_de_atencion.h"
#include "../../include/c/interrupciones/handlers.h"
#include "../../include/c/helpers.h"
#include "../../include/c/infoidt.h"
#include "../../include/c/video.h"
#include "../../include/c/stdlibs/string.h"

#define USABLE_INT_HANDLERS     10

int add_idt_entry(unsigned int number) {
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

void infoidt_command(char* params) {
    char option[20];
    unsigned int size = 0;
    unsigned int i = 0;
    DESCR_INT* idt = get_idt(); // get idt table.

    memset_custom(option, sizeof(option), 0);

    sscanf_custom(params, "%s %d", option, &size);

    if( strcmp(option, "info" ) == 0) {
        for(i = 0; i < USABLE_INT_HANDLERS; i++ ) {
            if(idt[i].selector != 0) {
                newline(); set_col(2); 
                vprintf_custom("La interrupcion %d esta activada.", i);
            }
        }
    } else if( strcmp(option, "add") == 0 ) {
        if( size < USABLE_INT_HANDLERS) {
            if(idt[i].selector == 0) {
                add_idt_entry(size);
                newline();
                vprintf_custom("La interrupcion ha sido agregada.");
            } else {
                newline();
                vprintf_custom("Esa interrupcion ya esta activada.");
            }
        } else {
            newline();
            vprintf_custom("La interrupcion se pasa del rango, elije una menor a"
                    " %d", USABLE_INT_HANDLERS);
        }

         
    } else if( strcmp(option, "del") == 0) {
        if( size < USABLE_INT_HANDLERS ) {
            del_idt_entry(size);
            newline();
            vprintf_custom("La interrupcion ha sido borrada.");
        } else {
            newline();
            vprintf_custom("La interrupcion se pasa del rango, elije una menor a"
                    " %d", USABLE_INT_HANDLERS);
        }
    
    }else {
        newline(); set_col(2);
        vprintf_custom("Escribiste el parametro equivocado.");
    }
}
