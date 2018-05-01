
#ifndef __MODEL__
#define __MODEL__

//#include <gtk/gtk.h>
//#include <gdk/gdkkeysyms.h>
/**
 * Initialization of opaque type board
 *
 */
typedef struct board_t{
    unsigned short nb_rows;
    unsigned short nb_columns;
    unsigned short **board_matrix;
    unsigned short player_moves;
}board_model;

/**
 * destroy_board
 *
 * Frees the alocated memory for the board opaque type.
 *
 * @param *boardx, a pointer to a board structure.  
 *
 * @pre: *boardx point to a valid and initialized board 
 * @post: A board structure is Freed from memory
 *
 * @return:
 *      Void function, no return.
 *
 */
void destroy_board(board_model *boardx);
/**
 * *init_board
 *
 * Initialaise an board opaque type structure.
 *
 * @param rows, a value stored as a character, the number of horizontal lines on the board.       
 *                          
 * @param column, a value stored as a character, the number of vertical lines on the board.
 *
 * @pre: rows >= 0, columns >= 0
 * @post: A board structure is initialzed 
 *
 * @return:
 *     pointer to initialized structure on Success
 *     NULL pointer on error.
 *
 */
board_model *init_board(unsigned short rows, unsigned short columns);

/**
 * add_pawn
 *
 * Adds a piece in on the game board.
 *
 * @param *boardx, a pointer to a board structure.        
 *      
 * @param player, the player(1 or 2) to put a disk on the board.
 *
 * @param column, the number of the column in which the disk is played.
 *
 * @pre: column in range (0, nb_columns), *boardx point to a valid and initialized board , player = 1 or 2
 * @post: The board is modified
 *
 * @return:
 *     1 on error.
 *     0 on success.
 *
 */
int add_pawn(board_model *boardx, unsigned int player, unsigned short column);

/**
 * check_win
 *
 * checks if one of the player has conected 4 pieces in a row.
 *
 * @param *boardx, a pointer to a board structure.
 * 
 *
 * @pre: *boardx point to a valid and initialized board 
 * @post: board is unchanged and has been checked for a winner. 
 *
 * @return:
 *     The number of the wining player (1 or 2), or 0 is no player has won yet.
 *  
 *
 */
int check_win(board_model *boardx);



int get_board_nb_rows(board_model *boardx);

int get_board_nb_columns(board_model *boardx);

int get_board_disk_value(board_model *boardx, unsigned int row, unsigned int column);

int column_is_full(board_model *boardx ,unsigned int nb_column);

#endif