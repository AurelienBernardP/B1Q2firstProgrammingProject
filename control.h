#ifndef __CONTROL__
#define __CONTROL__

#include "back_office.h"
#include "GUI.h"

typedef struct control_t{
    board_vue *bv;
    board_model *bm;
    GtkWidget **buttons;
}board_controler;

board_controler *create_board_controler(board_model *Bm, board_vue *Bv);

GtkWidget *create_menu(GtkWidget *window, board_controler *controler);

void move_made(GtkWidget *button, gpointer data);

void new_game(GtkWidget *button, gpointer data);

unsigned short find_column_clicked(board_controler *controler,GtkWidget *button);

int play_turn(board_model *boardx, GtkWidget *pTable, board_vue *bv, unsigned short column);

#endif

