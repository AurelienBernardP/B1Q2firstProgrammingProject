#ifndef __GTKGUI__
#define __GTKGUI__

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gdk/gdk.h>

#include "back_office.h"

/**
 * definition of board_vue structure.
 *
 */
typedef struct vue_t{
   GtkWidget ***image_table;
   board_model *bm;
   GtkWidget *gtk_table;
}board_vue;

/**
 * *make_window
 *
 * Creates and initializes a Gtk window.
 *
 * @param: *boardx, a pointer to a board_model structure.  
 * 
 * @pre: *boardx point to a valid and initialized board_model structure.
 *
 * @post: A Gtk Window is created.
 *
 * @return:
 *     pointer to initialized GtkWidget window on Success
 *
 */
GtkWidget *make_window(board_model *boardx);

/**
 * *create_board_vue
 *
 * Initialaise an board opaque type structure.
 *
 * @param: *boardx, a pointer to a board_model structure.  
 * 
 * @pre: *boardx point to a valid and initialized board_model structure.
 *
 * @post: A board_vue structure is initialized 
 *
 * @return:
 *     pointer to initialized structure on Success
 *     NULL pointer on error.
 *
 */
board_vue *create_board_vue(board_model *boardx);

/**
 * redraw_board
 *
 * refresh the visible image of the board on the screen.
 *
 * @param: *boardx, a pointer to a board_model structure.  
 * @param: *pTable, a pointer to a GtkWidget, a table on which the images are attached.  
 * @param: *bv, a pointer to a board_vue structure.  
 * 
 * @pre: *boardx point to a valid and initialized board_model structure.
 * @pre: *bv point to a valid and initialized board_vue structure.
 * @pre: *pTable point to a valid and initialized GtkWidget table.
 *
 * @post: board_vue structure and widget pointed by pTable are modified
 *
 * @return:
 *     0 on Success
 *     -1 on error.
 *
 */
int redraw_board(board_model *boardx, GtkWidget *pTable, board_vue *bv);

/**
 * show_aide
 *
 * Pop up window with information is created and displayed.
 *
 * @param: void
 * 
 * @pre: none
 *
 * @post: A dialog window is displayed
 *
 * @return:
 *     void
 *
 */
void show_aide(void);

/**
 * show_you_won
 *
 * Pop up window with information is created and displayed.
 *
 * @param: void
 * 
 * @pre: none
 *
 * @post: A dialog window is displayed
 *
 * @return:
 *     void
 *
 */
void show_you_won( void);

/**
 * show_you_lose
 *
 * Pop up window with information is created and displayed.
 *
 * @param: void
 * 
 * @pre: none
 *
 * @post: A dialog window is displayed
 *
 * @return:
 *     void
 *
 */
void show_you_lose( void);

/**
 * new_game_popup
 *
 * Pop up window with information is created and displayed.
 *
 * @param: void
 * 
 * @pre: none
 *
 * @post: A dialog window is displayed
 *
 * @return:
 *     void
 *
 */
void new_game_popup( void);

/**
 * show_top_list
 *
 * Pop up window with top players records from a file is created and displayed.
 *
 * @param: *button, unused compulsory argument, a pointer to the button pressed to start this function. 
 * @param: data, gpointer containing pointer to a chain of characters 
 * 
 * @pre: data is a valid pointer pointing to an initialized sting.
 *
 * @post: A dialog window is displayed with the top players, file content is not changed.
 *
 * @return:
 *     void
 *
 */
void show_top_list(GtkWidget *button, gpointer data);


#endif