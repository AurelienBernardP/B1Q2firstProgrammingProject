#ifndef __CONTROL__
#define __CONTROL__

#include "back_office.h"
#include "GUI.h"
#include "top10.h"
/**
 * definition of board_controler structure.
 *
 */
typedef struct control_t{
    board_vue *bv;
    board_model *bm;
    GtkWidget **buttons;
    player *current_player;
}board_controler;

/**
 * *create_board_controler
 *
 * Initialize an board opaque type structure.
 *
 * @param: *Bm, a pointer to a board_model structure.  
 * @param: *Bv, a pointer to a board_vue structure.
 * @param: *current_player a pointer to player opaque structure.    
 * 
 * @pre: *Bm point to a valid and initialized board_model structure.
 * @pre: *Bv point to a valid and initialized board_vue structure.
 * @pre: *current_player point to a valid and initialized player structure.
 *
 * @post: A board_controler structure is initialized 
 *
 * @return:
 *     pointer to initialized structure on Success
 *     NULL pointer on error.
 *
 */
board_controler *create_board_controler(board_model *Bm, board_vue *Bv, player *current_player);

/**
 * *create_menu
 *
 * Initialize a menu bar and its items that will be displayed on a window.
 *
 * @param: *window, a pointer to a GtkWidget that will contain the menu bar.  
 * @param: *controller, a pointer to a board_controler structure.
 * @param: *path a chain of characters that hold the path of a file.    
 * 
 * @pre: *window point to a valid GtkWindget.
 * @pre: *controler point to a valid and initialized board_controler structure.
 * @pre: *path point to a valid and initialized character array.
 *
 * @post: A menu_bar GtkWidget is set up.
 *
 * @return:
 *     pointer to initialized GtkWidget on Success
 *
 */
GtkWidget *create_menu(GtkWidget *window, board_controler *controler,  char* path);

/**
 * move_made
 *
 * Finds the button clicked, records the move done by the player, checks for win and makes the IA play.
 *
 * @param: *button, a pointer to the Gtk button clicked to trigger this function.  
 * @param: data, a gpointer to a board_controler structure.
 * 
 * @pre: data point to a valid and initialized board_controler structure.
 *
 * @post: A move is recorded and a response is done if necessary.
 *
 * @return:
 *     void
 *
 */
void move_made(GtkWidget *button, gpointer data);

/**
 * new_game
 *
 * Resets the game to the same values as a newly opened one.
 *
 * @param: *button, a pointer to the Gtk button clicked to trigger this function.  
 * @param: data, a gpointer to a board_controler structure.
 * 
 * @pre: data point to a valid and initialized board_controler structure.
 *
 * @post: The game is completely reset.
 *
 * @return:
 *     void
 *
 */
void new_game(GtkWidget *button, gpointer data);

#endif

