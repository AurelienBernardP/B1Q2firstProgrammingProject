#ifndef __GTKGUI__
#define __GTKGUI__

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gdk/gdk.h>

#include "back_office.h"

typedef struct vue_t{
   GtkWidget ***image_table;
   board_model *bm;
   GtkWidget *gtk_table;
}board_vue;

GtkWidget *make_window(board_model *boardx);

board_vue *create_board_vue(board_model *boardx);



int redraw_board(board_model *boardx, GtkWidget *pTable, board_vue *bv);

void show_aide(void);

void show_you_won( gpointer window);

void show_you_lose( gpointer window);

void new_game_popup( gpointer window);

#endif