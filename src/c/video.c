#include "../../include/c/definiciones.h"
#include "../../include/c/primitivas.h"
#include "../../include/c/video.h"
#include "../../include/c/interrupciones/helpers.h"

/***************************************************************
*
*                       FUNCIONES
*
****************************************************************/

word virtual_screen[SCREEN_LENGTH][SCREEN_WIDTH];
unsigned int row = 0;
unsigned int col = 0;

void set_row(unsigned int lrow) { row = lrow; }
void set_col(unsigned int lcol) { col = lcol; }
int get_row() { return row; }
int get_col() { return col; }



void blink_pointer_toggle() {
    char c = 0;
    word pos_data = virtual_screen[row][col];
    c = (char) pos_data;
    pos_data >>= 0x08;
    if( pos_data == WHITE_TXT ) {
        set_pos(row, col, SET_CHAR_BLINK_ON(c));
    } else {
        set_pos(row, col, SET_CHAR(c));
    }
    print_vscreen();
}
void clear_blink() {
    word w = virtual_screen[row][col];
    char c = (char) w;
    set_pos(row, col, SET_CHAR(c));
}

void newline() {
    setPicMasks(0xFD, 0xFF);
    clear_blink();
    if( row + 1 != SCREEN_LENGTH) {
        col = 0;
        row++;
    } else {
        oneline_up();
        col = 0;
    }
    setPicMasks(0xFC, 0xFF);
}

void times_newline(unsigned int i) {
    while(i > 0) {
        newline();
        i--;
    }
}

void backspace() {
    setPicMasks(0xFD, 0xFF);
    clear_blink();
    if( col - 1 >= 0) {
        col--;
        set_pos(row, col, SET_CHAR(' '));
    } else if ( row > 0 ) {
        row--;
        col = SCREEN_WIDTH - 1;
        set_pos(row, col, SET_CHAR(' '));
    }
    setPicMasks(0xFC, 0xFF);
}

void show_vscreen() {
    int i = 0;
    for(i = 0; i < 70; i++) {
        putc_custom(virtual_screen[0][i]);
    }
}

void set_pos(int row, int col, word w) {
    if( row < SCREEN_LENGTH && col < SCREEN_WIDTH) {
        virtual_screen[row][col] = w;
    }
}
void increment_pos() {
    if(col < SCREEN_WIDTH) {
        col++;
    } else if (row < SCREEN_LENGTH) {
        col = 0;
        row++;
    } else {
        // do something else
    }
    if (col == SCREEN_WIDTH) {
        col = 0;
        row++;
    } else if (row == SCREEN_LENGTH) {
        oneline_up();
        row = SCREEN_LENGTH - 1;
    }
}

void print_chr(char c) {
    set_pos(row, col, (word)SET_CHAR(c));
    increment_pos();
}

void print_str(const char* s) {
    unsigned int i = 0;

    for( i = 0; s[i] != '\0'; i++ ) {
        print_chr(s[i]);
    }
}

int print_vscreen() {
    int ret_val = 0;

    reset_tickpos();
    ret_val = __write(STDOUT, virtual_screen, SCREEN_SIZE);
    reset_tickpos();
    return ret_val;
}

void fill_screen(char c) {
    unsigned int i = 0;
    unsigned int j = 0;

    for( i = 0; i < SCREEN_LENGTH; i++ ) {
        for( j = 0; j < SCREEN_WIDTH; j++ ) {
            virtual_screen[i][j] = (word) SET_CHAR(c);
        }
    }
}

void clear_vscreen() {
    fill_screen(' ');
}

void oneline_up() {
    unsigned int i = 0;
    unsigned int line = 1;
    unsigned int previous_line = 0;

    for(line = 1; line < SCREEN_LENGTH; line++ ) {
        for(i = 0; i < SCREEN_WIDTH; i++) {
            virtual_screen[previous_line][i] = virtual_screen[line][i];
        }
        previous_line++;
    }
    for(i = 0; i < SCREEN_WIDTH; i++) {
        virtual_screen[previous_line][i] = EMPTY_SPACE;
    }
}
