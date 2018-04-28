

#ifndef __ARTIFICIALINTELIGENCE__
#define __ARTIFICIALINTELIGENCE__
#include "back_office.h"
/**
 * IA_play
 *
 * makes one play on in a connect 4 game.
 *
 * @param *boardx, a pointer to a board structure.
 *
 * @pre:  boardx != NULL
 * @post: one play has been done on a conectc 4 board.
 *
 * @return:
 *     Void function.
 */
void IA_play(board *boardx);

/**
 * random_play
 *
 * Function to play randomly on the board
 *
 * @param *boardx, a pointer to a board structure.  
 *
 * @pre:  boardx != NULL
 * @post: one play has been done on a conectc 4 board.
 *
 * @return:
 *     1 when move is done
 */
static int random_play(board *boardx);

/**
 * try_to_win
 *
 * Function that tries to connect 4 if possible
 *
 * @param *boardx, a pointer to a board structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board has been cheked for the posibility to connect 4 and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not the possibility of wining    
 */
static int try_to_win(board *boardx);

/**
 * try_block_win
 *
 * Function  that tries to stop the other player from connecting 4
 *
 * @param *boardx, a pointer to a board structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board has been cheked for the posibility to block 4 and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not any win to block    
 */
static int try_block_win(board *boardx);

/**
 * try_to_make_3
 *
 * Function that tries to connect 3 if possible
 *
 * @param *boardx, a pointer to a board structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board has been cheked for the posibility to connect 3 and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not the possibility of wining    
 */
static int try_to_make_3(board *boardx);

/**
 * try_block_3
 *
 * Function  that tries to stop the other player from connecting 3
 *
 * @param *boardx, a pointer to a board structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board has been cheked for the posibility to block 3 and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not any win to block    
 */
static int try_block_3(board *boardx);

/**
 * horizontal_try_to_do_x
 *
 * Function that tries to connect x disks horizontaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board has been cheked horizontaly for the posibility to connect x and move is made if possible
 *
 * @return:
 *         2 if move could be done
 *         0 if there was not the possibility of wining    
 */
static int horizontal_try_to_do_x(board *boardx, int nb_to_do);

/**
 * vertical_try_to_do_x
 *
 * Function that tries to connect x disks verticaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board has been cheked verticaly for the posibility to connect x and move is made if possible
 *
 * @return:
 *         2 if move could be done
 *         0 if there was not the possibility of wining    
 */
static int vertical_try_to_do_x(board *boardx, int nb_to_do);

/**
 * diagonal1_try_x_in_row
 *
 * Function that tries to connect x disks diagonaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board has been cheked in a positive gradient diagonal for the posibility to connect x and move is made if possible
 *
 * @return:
 *         2 if move could be done
 *         0 if there was not the possibility of wining    
 */
static int diagonal1_try_x_in_row(board *boardx, int nb_to_do);

/**
 * diagonal2_try_x_in_row
 *
 * Function that tries to connect x disks diagonaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board has been cheked in a negative gradient diagonal for the posibility to connect x and move is made if possible
 *
 * @return:
 *         2 if move could be done
 *         0 if there was not the possibility of wining    
 */
static int diagonal2_try_x_in_row(board *boardx, int nb_to_do);

/**
 * try_block_horizontal_x_in_row
 *
 * Function that tries to block x disks horizontaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board has been cheked horizontaly for the posibility to block x and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not the possibility of wining    
 */
static int try_block_horizontal_x_in_row(board *boardx,int nb_to_block);

/**
 * try_block_vertical_x_in_row
 *
 * Function that tries to block x disks verticaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board has been cheked verticaly for the posibility to block x and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not the possibility of wining    
 */
static int try_block_vertical_x_in_row(board *boardx, int nb_to_block);

/**
 * try_block_diagonal2_x_in_row
 *
 * Function that tries to block x disks diagonaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board has been cheked in a positive gradient diagonal for the posibility to block x and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not the possibility of wining    
 */
static int try_block_diagonal1_x_in_row(board *boardx, int nb_to_block);

/**
 * try_block_diagonal2_x_in_row
 *
 * Function that tries to block x disks diagonaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board has been cheked in a negative gradient diagonal for the posibility to block x and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not the possibility of wining    
 */
static int try_block_diagonal2_x_in_row(board *boardx, int nb_to_block);
#endif