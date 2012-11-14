#ifndef define_infoidt
#define define_infoidt

int add_idt_entry(DESCR_INT* idt_entry, unsigned int number);
int del_idt_entry(unsigned int entry_num);
#endif
