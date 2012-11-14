#include "../../include/c/malloc.h"
#include "../../include/c/helpers.h"
#include "../../include/c/video.h"
#include "../../include/c/stdlibs/string.h"
#include "../../include/c/stdlibs/ctype.h"
#include "../../include/c/shell.h"
#include "../../include/c/tests.h"

#define SAFE_ADDRESS        (1024*1024*2)
#define INFO_TABLE_SIZE     50 

typedef struct {
    unsigned int* ptr_to_segment_start;
} memory_segment;

typedef struct {
    void* ptr;
    unsigned int size;
} alloc_memory;

alloc_memory info[INFO_TABLE_SIZE];

unsigned int system_memory_size = 0;
unsigned int user_memory_size = 0;

byte* user_space_start = 0;

memory_segment* malloc_registry = 0;
unsigned int minimum_segment_size = 0;
unsigned int segments_amount = 0;
unsigned int allocated_space = 0;


/***************************************************************
* void init_system_mem
*
****************************************************************/
void init_system_mem(multiboot_info_t* mbd) {
    init_mem(mbd);
    init_malloc_data();
}


/***************************************************************
* int malloc_custom
*
****************************************************************/
void* malloc_custom(unsigned int size, int debug) {
    unsigned int i = 0;
    unsigned int starting_index = 0;
    unsigned int accumulated_mem = 0;
    unsigned int* return_ptr = 0;
    memory_segment* first_found = 0;
    memory_segment* last_found = 0;
    memory_segment* next_segment = 0;

    // Empiezo búsqueda en cada puntero a segmento.
    for(i = 0; i < segments_amount; i++) {
        next_segment = &malloc_registry[i];

        // Veo si hay algún segmento que esté libre. En caso 
        // afirmativo busco en los segmentos siguientes hasta
        // encontrar suficientes para alocar la memoria necesaria.
        if( next_segment->ptr_to_segment_start == 0 ) {
            starting_index = i;
            i++;
            first_found = next_segment;
            next_segment = &first_found[0];
            accumulated_mem += minimum_segment_size;
            while(size > accumulated_mem 
                    && (void*)next_segment < (void*)user_space_start 
                    && next_segment->ptr_to_segment_start == 0) {
                accumulated_mem += minimum_segment_size;
                i++;
                next_segment++;
            }

            if( size <= accumulated_mem ) {
                return_ptr = (void*)(user_space_start + starting_index*minimum_segment_size);
                last_found = &next_segment[-1]; // Último que encontré
                next_segment = first_found;
                allocated_space += accumulated_mem - minimum_segment_size;
                while( next_segment <= last_found ) {
                    next_segment->ptr_to_segment_start = return_ptr;
                    next_segment++;
                }
                return return_ptr;
            } else if((void*)next_segment >= (void*)user_space_start) {
                // No hay memoria disponible.
                return 0; 
            } else { 
                // No encontré un bloque de memoria contigua lo suficientemente grande
                accumulated_mem = 0;
                first_found = 0;
                next_segment = 0;
                starting_index = 0;
            }
        }
    }
}

/***************************************************************
* void free
*
****************************************************************/
void* free(unsigned int* ptr) {
    unsigned int i = 0;
    memory_segment* first_found = 0;
    memory_segment* last_found = 0;
    memory_segment* segment = (memory_segment*)malloc_registry;
    
    for(i = 0; i < segments_amount; i++) {
        if(segment[i].ptr_to_segment_start == ptr) {
            while(segment[i].ptr_to_segment_start == ptr) {
                segment[i].ptr_to_segment_start = 0;
                allocated_space -= minimum_segment_size;
                i++;
            }
            for( i = 0; i < INFO_TABLE_SIZE; i++ ) {
                if( info[i].ptr == ptr ) {
                    info[i].ptr = 0;
                    info[i].size = 0;
                    break;
                }
            }
            return ptr;
        }
    }
    return 0;
}


/***************************************************************
* int malloc_custom
*
****************************************************************/
void init_malloc_data() {

    if(system_memory_size == 0) {
        vprintf_custom("System memory size is 0.");
        print_vscreen();
        while(1) {}
    }

    bool show_data = true;
    unsigned int i = 0;
    unsigned int table_size = 0;
    unsigned int check = 0;

    memset_custom((char*)info, sizeof(info), 0);
    
    // Aloco el 10% de mi memoria total para mi 
    // registro de headers de memoria.
    table_size = (unsigned int)(system_memory_size * 0.1);
    malloc_registry = (memory_segment*)SAFE_ADDRESS;

    user_space_start = (byte*)(SAFE_ADDRESS + table_size + sizeof(memory_segment));
    user_memory_size = (unsigned int)(system_memory_size - (unsigned int)user_space_start);

    segments_amount = (unsigned int)(table_size / sizeof(memory_segment));
    minimum_segment_size = (unsigned int)(user_memory_size / segments_amount);

    memset_custom((char*)malloc_registry, table_size, 0);

    // Imprime las características del mapa de memoria.
    if(show_data == true) {
        clear_vscreen();
        set_row(3); set_col(0);
        vprintf_custom("Memory Table Size: %x", table_size);
        set_row(4); set_col(0);
        vprintf_custom("Malloc Registry Start: %x", malloc_registry);
        set_row(5); set_col(0);
        vprintf_custom("Total Memory Size: %x", system_memory_size);
        set_row(6); set_col(0);
        vprintf_custom("User Space Start: %x", user_space_start);
        set_row(7); set_col(0);
        vprintf_custom("User Memory Size: %x", user_memory_size);
        set_row(8); set_col(0);
        vprintf_custom("Number of Table Segments: %d", segments_amount);
        set_row(9); set_col(0);
        vprintf_custom("Minimum Allocable Space: %d(bytes)", minimum_segment_size);
        set_row(10); set_col(0);
        vprintf_custom("Memory Header Size: %x", sizeof(memory_segment));
        print_vscreen();
    }

    q_to_continue(SCREEN_LENGTH - 1, 2, 1);
}


/***************************************************************
*   void init_mem
*       Calcula la cantidad de RAM que tiene la máquina.
*
****************************************************************/
unsigned int init_mem(multiboot_info_t* mbd) {
    unsigned int largest_len = 0;
    //unsigned long safe_addr = (unsigned long)kmain + SAFE_DISTANCE + 1;

    memory_map_t* mmap = (memory_map_t*)mbd->mmap_addr;
    while(mmap < (memory_map_t*)(mbd->mmap_addr + mbd->mmap_length) ) {

        if( mmap->length_low > largest_len) {
            largest_len = mmap->length_low;
        }

        mmap = (memory_map_t*) ((unsigned int)mmap + mmap->size + sizeof(unsigned int));
    }

    system_memory_size = (unsigned int)(largest_len);
}

/***************************************************************
*   void malloc_command
*       Calcula la cantidad de RAM que tiene la máquina.
*
****************************************************************/
void malloc_command(char* params) {
    char option[20];
    unsigned int size = 0;
    unsigned int i = 0;

    memset_custom(option, sizeof(option), 0);

    sscanf_custom(params, "%s %d", option, &size);

    if( strcmp(option, "get") == 0 ) {
        if( size > minimum_segment_size ) {
            void* ptr = malloc_custom(size, 0);
            newline();
            if(ptr == 0) {
                vprintf_custom("No hay espacio para alocar %d bytes.", size);
            } else {
                for(i = 0; info[i].ptr != 0; i++) {}

                if( i < INFO_TABLE_SIZE ) {
                    vprintf_custom("Se aloco la memoria. Esta en la direccion %x", ptr);

                    info[i].ptr = ptr;
                    info[i].size = size;
                } else {
                    newline();
                    vprintf_custom("No puedes alocar mas memoria porque llenaste la"
                            "tabla que tiene las referencias de las alocaciones, y que"
                            "usa el comando malloc info.");
                }
            }
        } else {
            newline();
            vprintf_custom("Debes pedir %d bytes o mas.", minimum_segment_size);
        }
    } else if( strcmp(option, "info") == 0) {
        clear_vscreen();
        set_col(2); set_row(1);
        vprintf_custom("Los valores de la izquierda son la direcciones "
                "en donde empieza cada segmento, los de la derecha son los "
                "tamanos de los mismos.");
        set_col(2); set_row(3);
        for(i = 0; i < INFO_TABLE_SIZE; i++) {
            if( info[i].ptr != 0 ) {
                set_col(2);
                vprintf_custom("%x %d", info[i].ptr, info[i].size);
                newline();
                if( i > SCREEN_WIDTH - 3 ) {
                    set_col(20); set_row(3);
                }
            }
        }
        if (i == 0) {
            vprintf_custom("Aun no alocaste ninguna porcion de memoria.");
        }
    } else if( strcmp(option, "") == 0 ) {
        newline();
        vprintf_custom("Debes ingresar al menos una opcion para"
                " ser usada por esta funcion.");
    } else if(strcmp(option, "test") == 0) {
        malloc_tests(); 
        q_to_continue(SCREEN_LENGTH - 1, 2, 1);
    } else {
        newline();
        vprintf_custom("El comando que ingresaste no es valido.");
    }
    print_vscreen();

}

void free_command(char* params) {
    char option[20];
    bool leave = false;
    unsigned int address = 0;
    unsigned int i = 0;
    unsigned int len = 0;
    void* result = 0;

    len = strlen_custom(params);
    memset_custom(option, sizeof(option), 0);

    sscanf_custom(params, "%s", option);

    if( strcmp(option, "info") == 0 ) {
        newline();
        set_col(2);
        vprintf_custom("Usa el comando \'free\' seguido de una direccion"
                " de memoria en base hexadecimal (es decir el numero precedido"
                " por 0x o 0X), para liberar la porcion de memoria que empieza"
                " en ese lugar.");
    } else {
        for(i = 0; i < len; i++) {
            if( ishex(option[i] == false) ) {
                leave = true;
                break;
            }
        }
        //compruebo que el numero esté en hexa
        if( leave == false 
                && option[0] == '0'
                && (option[1] == 'x' || option[1] == 'X')) {
            sscanf_custom(option, "%x", &address);
            
            result = (void*)free((unsigned int*)address);
            if( result == (void*)address) {
                newline(); set_col(2);
                vprintf_custom("La memoria con direccion %x fue liberada.", address);
            } else {
                newline(); set_col(2);
                vprintf_custom("No existe ningun segmento de memoria alocado"
                        "en esa direccion.");
            }
        } else {
            newline(); set_col(2);
            vprintf_custom("Debes ingresar un direccion de memoria en "
                    "hexa para liberar esa porcion de memoria.");
        }
    }
}
