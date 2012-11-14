#include "../../include/c/malloc.h"
#include "../../include/c/helpers.h"
#include "../../include/c/video.h"

#define SAFE_ADDRESS    (1024*1024*2)

typedef struct {
    unsigned int* ptr_to_segment_start;
} memory_segment;

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
            //if(debug == 1) {
            //    set_col(0); set_row(0);
            //    vprintf_custom("min size: %d, accumulated_mem: %d, next_segment: %x, pos: %x", minimum_segment_size, accumulated_mem, next_segment, &accumulated_mem);
            //    print_vscreen();
            //}


            // Mientras no haya acumulado la memoria que pide el usuario
            // y aún siga dentro de la memoria del registro y el 
            // próximo segmento también esté libre.
            while(size > accumulated_mem 
                    && (void*)next_segment < (void*)user_space_start 
                    && next_segment->ptr_to_segment_start == 0) {
                accumulated_mem += minimum_segment_size;
                i++;
                next_segment++;
            }
            //if(debug == 1) {
            //    set_col(0); set_row(1);
            //    vprintf_custom("min size: %d, accumulated_mem: %d, next_segment: %x", minimum_segment_size, accumulated_mem, next_segment);
            //    print_vscreen();
            //    while(1) {}
            //}

            if( size <= accumulated_mem ) {
                return_ptr = (void*)(user_space_start + starting_index*minimum_segment_size);
                last_found = &next_segment[-1]; // Último que encontré
                next_segment = first_found;
                allocated_space += accumulated_mem - minimum_segment_size;
                //if(debug == 1) {
                //    set_col(0); set_row(1);
                //    vprintf_custom("first found: %x, last found: %x, return ptr: %x, starting index: %d", first_found, last_found, return_ptr, starting_index );
                //    print_vscreen();
                //    while(1) {}
                //}
                while( next_segment <= last_found ) {
                    next_segment->ptr_to_segment_start = return_ptr;
                    next_segment++;
                }
                //if(debug == 1) {
                //    next_segment = first_found;
                //    while( next_segment <= last_found ) {
                //        if( next_segment->ptr_to_segment_start != return_ptr) {
                //            set_row(10);
                //            vprintf_custom("FALLO - next segment: %x", next_segment);
                //            print_vscreen();
                //            while(1) {}
                //        }
                //        next_segment++;
                //    }
                //    set_row(10);
                //    vprintf_custom("FUNCIONO");
                //    print_vscreen();
                //    while(1) {}
                //}
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
void free(unsigned int* ptr) {
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
            break;
        }
    }
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
}


/***************************************************************
*   void init_mem
*       calculates the amount of RAM in memory
*
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
