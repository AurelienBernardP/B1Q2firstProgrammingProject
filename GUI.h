#ifndef __GTKGUI__
#define __GTKGUI__

//#include <gtk/gtk.h>
//#include <gdk/gdkkeysyms.h>
//#include <gdk/gdk.h>

typedef struct vue_t{
   GtkWidget ***image_table;
   board *board_model;
   GtkWidget *gtk_table;
}board_vue;

GtkWidget *make_window();

board_vue *create_board_vue(board_model* boardx);

GtkWidget *create_menu(GtkWidget *window);

int redraw_board(board_model *boardx, GtkWidget *pTable);

#endif