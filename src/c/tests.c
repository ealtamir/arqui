#include "../../include/c/interrupciones/definiciones.h"
#include "../../include/c/helpers.h"
#include "../../include/c/video.h"
#include "../../include/c/malloc.h"
#include "../../include/c/primitivas.h"
#include "../../include/c/tests.h"

extern unsigned int allocated_space;
extern unsigned int user_memory_size;

/***************************************************************
*   void malloc_tests
*      
*
****************************************************************/
void malloc_tests() {
    
    unsigned int row = 3;
    unsigned int col = 3;

    unsigned int size1 = 30000000;
    unsigned int* test_ptr1 = malloc_custom(size1, 0);
    set_row(row); set_col(col);
    vprintf_custom("1 Asked: %d, starts at: %x", size1, test_ptr1);
    set_row(row++); set_col(col + 40);
    vprintf_custom("mem left: %d", user_memory_size - allocated_space);

    unsigned int size2 = 1000;
    unsigned int* test_ptr2 = malloc_custom(size2, 0);
    set_row(row); set_col(col);
    vprintf_custom("2 Asked: %d, starts at: %x", size2, test_ptr2);
    set_row(row++); set_col(col + 40);
    vprintf_custom("mem left: %d", user_memory_size - allocated_space);

    unsigned int size3 = 0x00A00000; // 10MB
    unsigned int* test_ptr3 = malloc_custom(size3, 0);
    set_row(row); set_col(col);
    vprintf_custom("3 Asked: %d, starts at: %x", size3, test_ptr3);
    set_row(row++); set_col(col + 40);
    vprintf_custom("mem left: %d", user_memory_size - allocated_space);

    unsigned int size4 = 0x00A00000; // 10MB
    unsigned int* test_ptr4 = malloc_custom(size4, 0);
    set_row(row); set_col(col);
    vprintf_custom("4 Asked: %d, starts at: %x", size4, test_ptr4);
    set_row(row++); set_col(col + 40);
    vprintf_custom("mem left: %d", user_memory_size - allocated_space);

    unsigned int size5 = 0x00100000; // 1MB
    unsigned int* test_ptr5 = malloc_custom(size5, 1);
    set_row(row); set_col(col);
    vprintf_custom("5 Asked: %d, starts at: %x", size5, test_ptr5);
    set_row(row++); set_col(col + 40);
    vprintf_custom("mem left: %d", user_memory_size - allocated_space);

    unsigned int size6 = 0x00100000; // 1MB
    unsigned int* test_ptr6 = malloc_custom(size6, 0);
    set_row(row); set_col(col);
    vprintf_custom("6 Asked: %d, starts at: %x", size6, test_ptr6);
    set_row(row++); set_col(col + 40);
    vprintf_custom("mem left: %d", user_memory_size - allocated_space);

    unsigned int size7 = 0x00100000; // 1MB
    unsigned int* test_ptr7 = malloc_custom(size7, 0);
    set_row(row); set_col(col);
    vprintf_custom("7 Asked: %d, starts at: %x", size7, test_ptr7);
    set_row(row++); set_col(col + 40);
    vprintf_custom("mem left: %d", user_memory_size - allocated_space);

    unsigned int size8 = 0x00400000; // 4MB
    unsigned int* test_ptr8 = malloc_custom(size8, 0);
    set_row(row); set_col(col);
    vprintf_custom("8 Asked: %d, starts at: %x", size8, test_ptr8);
    set_row(row++); set_col(col + 40);
    vprintf_custom("mem left: %d", user_memory_size - allocated_space);

    unsigned int size9 = 0x00100000; // 64KB
    unsigned int* test_ptr9 = malloc_custom(size9, 0);
    set_row(row); set_col(col);
    vprintf_custom("9 Asked: %d, starts at: %x", size9, test_ptr9);
    set_row(row++); set_col(col + 40);
    vprintf_custom("mem left: %d", user_memory_size - allocated_space);

    unsigned int size10 = 0x00100000; // 64KB
    unsigned int* test_ptr10 = malloc_custom(size10, 0);
    set_row(row); set_col(col);
    vprintf_custom("10 Asked: %d, starts at: %x", size10, test_ptr10);
    set_row(row++); set_col(col + 40);
    vprintf_custom("mem left: %d", user_memory_size - allocated_space);

    unsigned int size11 = 0x00100000; // 64KB
    unsigned int* test_ptr11 = malloc_custom(size11, 0);
    set_row(row); set_col(col);
    vprintf_custom("11 Asked: %d, starts at: %x", size11, test_ptr11);
    set_row(row++); set_col(col + 40);
    vprintf_custom("mem left: %d", user_memory_size - allocated_space);

    free(test_ptr6);
    set_row(row); set_col(col);
    vprintf_custom("Released: %x (bytes)", size7);
    set_row(row++); set_col(col + 40);
    vprintf_custom("mem left: %d", user_memory_size - allocated_space);

    free(test_ptr7);
    set_row(row); set_col(col);
    vprintf_custom("Released: %x (bytes)", size7);
    set_row(row++); set_col(col + 40);
    vprintf_custom("mem left: %d", user_memory_size - allocated_space);

    test_ptr9 = malloc_custom(size9, 0);
    set_row(row); set_col(col);
    vprintf_custom("12 Asked: %d, starts at: %x", size9, test_ptr9);
    set_row(row++); set_col(col + 40);
    vprintf_custom("mem left: %d", user_memory_size - allocated_space);


    print_vscreen();
}

/***************************************************************
*   void printf_tests
*      
*
****************************************************************/
void printf_tests() {
    set_tickpos(4, 2);
    printf_custom("Esto es una prueba: %x %x %x %x", 1000, 10000, 1000000, 99999999);
    set_tickpos(5, 2);
    printf_custom("Esto es una prueba: %d %d %d %d", 1000, 10000, 1000000, 99999999);
    set_tickpos(6, 2);
    printf_custom("Esto es una prueba: %x %d %x %d", 1000, 10000, 1000000, 99999999);
    set_tickpos(7, 2);
    printf_custom("Esto es una prueba: %x %d %s %x", 1000, 10000, "Hello!!", 99999999);
    set_tickpos(10, 2);
    printf_custom("Esto es una prueba: %s %s", "dos strings muuuuuuuuuuuy largooooooos", "012345678901234567890123456789001234567890123456789");
    printf_custom("Esto es una prueba, estoy imprimiendo al stdout y no a la consola virtual: %x %d %s %x", 1000, 10000, "Hello!!", 99999999);
}

/***************************************************************
*   void vprintf_tests
*      
*
****************************************************************/
void vprintf_tests() {
    set_col(2); set_row(4);
    vprintf_custom("Esto es una prueba: %x %x %x %x", 1000, 10000, 1000000, 99999999);
    set_col(2); set_row(5);
    vprintf_custom("Esto es una prueba: %d %d %d %d", 1000, 10000, 1000000, 99999999);
    set_col(2); set_row(6);
    vprintf_custom("Esto es una prueba: %x %d %x %d", 1000, 10000, 1000000, 999999);
    set_col(2); set_row(7);
    vprintf_custom("Esto es una prueba: %x %d %s %x", 1000, 10000, "Hello!!", 99999999);
    set_col(2); set_row(10);
    vprintf_custom("Esto es una prueba: %s %s", "dos strings muuuuuuuuuuuy largooooooos", "012345678901234567890123456789001234567890123456789");
    print_vscreen();
}
