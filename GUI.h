#ifndef __GTKGUI__
#define __GTKGUI__

//#include <gtk/gtk.h>
//#include <gdk/gdkkeysyms.h>
//#include <gdk/gdk.h>

typedef struct vue_t{
   GtkWidget ***image_table;
   board *board_model;
   GtkWidget *board_vue;
}

GtkWidget *make_window();

GtkWidget *create_zone1(board *boardx);

GtkWidget *create_zone2(GtkWidget *window);



#endif