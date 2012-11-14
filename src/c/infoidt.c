#include "../../include/c/interrupciones/definiciones.h"
#include "../../include/c/interrupciones/helpers.h"

int add_idt_entry(DESCR_INT* idt_entry, unsigned int number) {
    if( number >= IDT_SIZE ) {
        return -1;
    }
    _Cli();
    _Sti();

    
}
int del_idt_entry(unsigned int entry_num) {
}
