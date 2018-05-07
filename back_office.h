
#ifndef __MODEL__
#define __MODEL__

/**
 * definition of board_model structure.
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
 * @pre: *boardx point to a valid and initialized board_model structure
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
 * Initialaise an board_model structure.
 *
 * @param rows, a value stored as a character, the number of horizontal lines on the board.       
 *                          
 * @param column, a value stored as a character, the number of vertical lines on the board.
 *
 * @pre: rows >= 0, columns >= 0
 * @post: A board_model structure is initialzed 
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
 * @param *boardx, a pointer to a board_model structure.        
 *      
 * @param player, the player(1 or 2) to put a disk on the board.
 *
 * @param column, the number of the column in which the disk is played.
 *
 * @pre: column in range (0, nb_columns), *boardx point to a valid and initialized board_model , player = 1 or 2
 * @post: The board is modified
 *
 * @return:
 *     1 on error.
 *     0 on success.
 *
 */
int add_pawn(board_model *boardx, unsigned int player, unsigned short column);

/**
 * reintialize_board_model
 *
 * reinitialize the model of the previously created board model .
 *
 * @param *boardx, a pointer to a board_model structure. 
 *
 * @pre: *boardx point to a valid and initialized board_model
 * @post: A board_model structure is reinitialized to the same values as a newly initialized board_model.
 *
 * @return:
 *      Void function, no return.
 *
 */
void reinitialize_board_model(board_model *boardx);

/**
 * check_win
 *
 * checks if one of the player has connected 4 pieces in a row.
 *
 * @param *boardx, a pointer to a board_model structure.
 * 
 *
 * @pre: *boardx pointer to a valid and initialized board_model structure
 * @post: board_model is unchanged and has been checked for a winner. 
 *
 * @return:
 *     The number of the wining player (1 or 2), or 0 is no player has won yet.
 * 
 */
int check_win(board_model *boardx);

/**
 * get_board_nb_rows
 *
 * gets the number of rows in the 2d array of board_model
 *
 * @param *boardx, a pointer to a board_model structure.
 * 
 *
 * @pre: *boardx point to a valid and initialized board_model structure.
 * @post: board_model is unchanged. 
 *
 * @return:
 *     The number of rows in the array.
 * 
 */
int get_board_nb_rows(board_model *boardx);

/**
 * get_board_nb_columns
 *
 * Gets the number of columns in the 2d array of board_model
 *
 * @param *boardx, a pointer to a board_model structure.
 * 
 *
 * @pre: *boardx point to a valid and initialized board_model structure.
 * @post: board_model is unchanged. 
 *
 * @return:
 *     The number of columns in the array.
 *
 */
int get_board_nb_columns(board_model *boardx);

/**
 * get_board_disk_value
 *
 * Gets the value of an element in the 2d array of board_model, which represents the player that is filling that spot of the board.
 *
 * @param *boardx, a pointer to a board_model structure.
 * @param row, row in which the element is.
 * @param column, column in which the element is.
 * 
 *
 * @pre: *boardx point to a valid and initialized board_model structure.
 * @post: board_model is unchanged. 
 *
 * @return:
 *     integer, the value of the element .
 *     -1 on error.
 */
int get_board_disk_value(board_model *boardx, unsigned int row, unsigned int column);

/**
 * column_is_full
 *
 * Checks if the column of the 2d array is full of element different of 0.
 *
 * @param *boardx, a pointer to a board_model structure.
 * @param nb_column, column to be checked.
 * 
 *
 * @pre: *boardx point to a valid and initialized board_model structure.
 * @post: board_model is unchanged. 
 *
 * @return:
 *     1 if the column is full.
 *     0 if there is at least one element equal to 0 in the column.
 *
 */
int column_is_full(board_model *boardx ,unsigned int nb_column);

#endif