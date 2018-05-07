#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "back_office.h"
#include "IA.h"

/**
 * is_there_support
 *
 * Verifies that the piece will fall where intended as it has something under to support it.
 *
 * @param: *boardx, a pointer to a board_model structure.
 * @param: nb_row, row where the 'disk' should be placed.
 * @param: nb_column, column where the play is made.
 *
 * @pre:  boardx != NULL
 * @post: The check is done.
 *
 * @return:
 *     0 if there is no support.
 *     1 if there is a support
 */
static int is_there_support(board_model *boardx, int nb_row, int nb_column){
   assert(boardx != NULL);

   if ((nb_row + 1) > boardx->nb_rows ){
      return 0; // error, this should not happen
   }
   if ((nb_row + 1 ) == boardx->nb_rows){
      return 1; // the base will hold the disk
   }
   
   if (get_board_disk_value(boardx, (nb_row + 1), nb_column) != 0 ){
      return 1;// there is a disk that will support an other disk;
   }

return 0;
}

/**
 * move_is_in_board
 *
 * Verifies that the move intended by the IA is inside the board bounds.
 *
 * @param: *boardx, a pointer to a board_model structure.
 * @param: nb_row, row where the 'disk' should be placed.
 * @param: nb_column, column where the play is made.
 *
 * @pre:  boardx != NULL
 * @post: The check is done.
 *
 * @return:
 *     0 if out of bounds.
 *     1 if inbounds. 
 */
static int move_is_in_board(board_model *boardx, int nb_row, int nb_column){
   assert(boardx != NULL);

   if(nb_row < 0 || nb_row >= get_board_nb_rows(boardx)){
      return 0;
   }
   if (nb_column < 0 || nb_column >= get_board_nb_columns(boardx)){
      return 0;
   }
   
return 1; // if position is inside board, return 1 (True);
}

/**
 * move_is_fair
 *
 * combines move_is_in_board and is_there_support to know if the IA should attempt the move.
 *
 * @param: *boardx, a pointer to a board_model structure.
 * @param: nb_row, row where the 'disk' should be placed.
 * @param: nb_column, column where the play is made.
 *
 * @pre:  boardx != NULL
 * @post: The check is done.
 *
 * @return:
 *     0 if it is not a good decision from the IA.
 *     1 if it is a acceptable decision from the IA. 
 */
static int move_is_fair(board_model *boardx, int nb_row, int nb_column){
   assert(boardx != NULL);

   if(move_is_in_board(boardx, nb_row, nb_column) && is_there_support(boardx, nb_row, nb_column)){
      if(get_board_disk_value(boardx, nb_row, nb_column) == 0){
         return 1; //if the intedend move id in a free space inside the board and will be supported to stay in the intended place.
      }
   }

return 0;// if one of the criteria is not respected
}

/**
 * horizontal_try_add_to_x
 *
 * Function that tries to connect x disks horizontally in a connect 4 game if possible
 *
 * @param: *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been checked horizontally for the possibility to connect x and move is made if possible.
 *
 * @return:
 *         2 if move could be done
 *         0 if there was no possibility of adding one more 'disk' to the row.    
 */
static int horizontal_try_add_to_x(board_model *boardx, int nb_to_add_to){
   assert(boardx != NULL);

   int player_2_count = 0;
   int succesfull = 1;
   for (int i = (boardx->nb_rows - 1); i >= 0; --i){
      player_2_count = 0;
      for (int j = 0; j < boardx->nb_columns; ++j){
         if(boardx->board_matrix[i][j] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;
         }
         if(player_2_count == nb_to_add_to && move_is_fair(boardx,(i),(j+1))){
            succesfull = add_pawn(boardx, 2, j+1);
            if (succesfull == 0){
               return 2;
            }
         }//return 2 if AI did join nb_to_add_to 
      }
   }//end for, horizontal (left to right)check for possible win

   for (int i = (boardx->nb_rows - 1); i >= 0; --i){
      player_2_count = 0;
      for (int j = (boardx->nb_columns - 1); j >= 0; --j){
         if(boardx->board_matrix[i][j] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;
         }
         if(player_2_count== nb_to_add_to && move_is_fair(boardx,(i),(j-1))){
            succesfull = add_pawn(boardx, 2, j-1);
            if (succesfull == 0){
               return 2;
            }
         }//return 2 if AI wins 
      }
   }//end for, horizontal (right to left)check for possible win

return 0; 
}

/**
 * vertical_try_add_to_x
 *
 * Function that tries to connect x disks vertically in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been checked vertically for the plausibility to connect x and move is made if possible
 *
 * @return:
 *         2 if move could be done
 *         0 if there was no possibility of adding one more 'disk' to the row.
 */
static int vertical_try_add_to_x(board_model *boardx, int nb_to_add_to){
   assert(boardx != NULL);

   int player_2_count = 0;
   int succesfull = 1;
   
   for (int i = 0; i < boardx->nb_columns; ++i){
      player_2_count = 0;
      for (int j = (boardx->nb_rows-1); j >= 0; --j){
         if(boardx->board_matrix[j][i] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;            
         }
         if(player_2_count == nb_to_add_to && ((j - 1) >= 0) && boardx->board_matrix[j-1][i] == 0 ){
            succesfull = add_pawn(boardx, 2, i);
            if (succesfull == 0){
               return 2;
            }
         }//return 2 if player 2(IA) wins 
      }
   }//end for, vertical check

return 0; //after board_model has been checked vertically and no player has won yet, 0 returned
}

/**
 * diagonal1_try_add_to_x
 *
 * Function that tries to connect x disks diagonally in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been checked in a positive gradient diagonal for the possibility to connect x and move is made if possible
 *
 * @return:
 *         2 if move could be done
 *         0 if there was no possibility of adding one more 'disk' to the row.    
 */
static int diagonal1_try_add_to_x(board_model *boardx, int nb_to_add_to){
   assert(boardx != NULL);

   int player_2_count = 0;
   int succesfull = 1;

   for (int i = (boardx->nb_rows -1); i >= 0 ; --i){
      int y = i;
      player_2_count = 0;
      for (int j = 0; j < boardx->nb_columns && y >= 0; ++j){
         if(boardx->board_matrix[y][j] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;            
         }
         if(player_2_count == nb_to_add_to &&move_is_fair(boardx,(y-1),(j+1))){
            succesfull = add_pawn(boardx, 2, j+1);
            if (succesfull == 0){
               return 2;
            }
         }//return 2 if player 2(IA) wins 
         y--;
      }
   }//end for, top left (bottom to top)triangle of matrix has been checked for win

   for (int i = 0; i < boardx->nb_columns; ++i){
      int y = (boardx->nb_rows - 1);
      player_2_count = 0;
      for (int j = i; j < boardx->nb_columns  && y >= 0; ++j){
         if(boardx->board_matrix[y][j] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;            
         }
         if(player_2_count == nb_to_add_to && move_is_fair(boardx,(y-1),(j+1))){
            succesfull = add_pawn(boardx, 2, j+1);
            if (succesfull == 0){
               return 2;
            }
         }//return 2 if player 2(IA) wins 
         --y;
      }
   }//end for, bottom right triangle (bottom to top)of matrix has been checked for possible win
   
   for (int i = 0; i < boardx->nb_rows; ++i){
      int y = (boardx->nb_columns - 1);

      player_2_count = 0;
      for (int j = i; j < boardx->nb_rows && y >= 0; ++j){
         if(boardx->board_matrix[j][y] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;            
         }
         if(player_2_count == nb_to_add_to && move_is_fair(boardx,(j+1),(y-1))){
            succesfull = add_pawn(boardx, 2, y-1);
            if (succesfull == 0){
               return 2;
            }
         }//return 2 if player 2(IA) wins 
         --y;
      }
   }//end for, bottom right triangle (top to botom)of matrix has been checked for possible win

   for (int i = (boardx->nb_columns-1); i >= 0; --i){
      int y = 0;

      player_2_count = 0;
      for (int j = i; j >=0 && y < boardx->nb_rows; --j){
         if(boardx->board_matrix[y][j] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;            
         }
         if(player_2_count == nb_to_add_to && move_is_fair(boardx,(y+1),(j-1))){
            succesfull = add_pawn(boardx, 2, j-1);
            if (succesfull == 0){
               return 2;
            }
         }//return 2 if player 2(IA) wins 
         ++y;
      }
   }//end for, top left triangle (top to bottom)of matrix has been checked for possible win
      
return 0; //no player has won yet
}

/**
 * diagonal2_try_add_to_x
 *
 * Function that tries to connect x disks diagonally in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been checked in a negative gradient diagonal for the possibility to connect x and move is made if possible
 *
 * @return:
 *         2 if move could be done
 *         0 if there was no possibility of adding one more 'disk' to the row.
 */
static int diagonal2_try_add_to_x(board_model *boardx, int nb_to_add_to){
   assert(boardx != NULL);

   int player_2_count = 0;
   int succesfull = 1;

   for (int i = (boardx->nb_columns - 1); i >= 0 ; i--){
      int y = (boardx->nb_rows - 1);
      player_2_count = 0;
      for (int j = i ; j >= 0 && y >= 0; --j){
         if(boardx->board_matrix[y][j] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;            
         }
         if(player_2_count == nb_to_add_to && move_is_fair(boardx,(y-1),(j-1))){
            succesfull = add_pawn(boardx, 2, j-1);
            if (succesfull == 0){
               return 2;
            }
         }//return 2 if player 2(IA) wins 
         --y;
      }
   }//end for, bottom left triangle (bottom to top)of matrix has been checked for win
    
   for (int i = (boardx->nb_rows - 1); i >= 0 ; i--){
      int y = (boardx->nb_columns - 1);
      player_2_count = 0;
      for (int j = i ; j >= 0 && y >= 0; --j){
         if(boardx->board_matrix[j][y] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;       
         }
         if(player_2_count == nb_to_add_to && move_is_fair(boardx,(j-1),(y-1))){
            succesfull = add_pawn(boardx, 2, j-1);
            if (succesfull == 0){
               return 2;
            }//return 2 if player 2(IA) wins 
         --y;
         }
      }
   }//end for, top right triangle(bottom to top) of matrix has been checked for win
   
   for (int i = 0; i < boardx->nb_rows; i++){
      int y = 0;
      player_2_count = 0;
      for (int j = i ; j < boardx->nb_rows && y < boardx->nb_columns; ++j){
         if(boardx->board_matrix[j][y] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;       
         }
         if(player_2_count == nb_to_add_to && move_is_fair(boardx,(j+1),(y+1))){
            succesfull = add_pawn(boardx, 2, y+1);
            if (succesfull == 0){
               return 2;
            }//return 2 if player 2(IA) wins 
         ++y;
         }
      }
   }//end for, bottom left triangle(top to bottom) of matrix has been checked for win
    
   for (int i = 0; i < boardx->nb_columns; ++i){
      int y = 0;

      player_2_count = 0;
      for (int j = i; j < boardx->nb_columns && y < boardx->nb_rows; ++j){
         if(boardx->board_matrix[y][j] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;            
         }
         if(player_2_count == nb_to_add_to && move_is_fair(boardx,(y+1),(j+1))){
            succesfull = add_pawn(boardx, 2, j+1);
            if (succesfull == 0){
               return 2;
            }
         }//return 2 if player 2(IA) wins 
         ++y;
      }
   }//end for, top right triangle (top to bottom)of matrix has been checked for possible win
     
return 0;
}

/**
 * try_block_horizontal_x_in_row
 *
 * Function that tries to block x disks horizontally in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been checked horizontally for the possibility to block x and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was no possibility of blocking the x in a row of the other player 
 */
static int try_block_horizontal_x_in_row(board_model *boardx,int nb_to_block){
   assert(boardx != NULL);

   int succesfull = 1;
   int player_1_count = 0;

   for (int i = (boardx->nb_rows - 1); i >= 0; --i){
      player_1_count = 0;
      for (int j = 0; j < boardx->nb_columns; ++j){
         if(boardx->board_matrix[i][j] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;
         }
         if(player_1_count == nb_to_block && move_is_fair(boardx,(i),(j+1))){
            succesfull = add_pawn(boardx, 2, j+1);
            if (succesfull == 0){
               return 1;
            }
         }//return 1 if win of player 1 blocked 
      }
   }//end for, horizontal (left to right)check for possible win
   
    for (int i = (boardx->nb_rows - 1); i >= 0; --i){
      player_1_count = 0;
      for (int j = boardx->nb_columns; j > 0; --j){
         if(boardx->board_matrix[i][j] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;
         }
         if(player_1_count == nb_to_block && ((j - 1) >= 0) && move_is_fair(boardx,(i),(j-1))){
            succesfull = add_pawn(boardx, 2, j-1);
            if (succesfull == 0){
               return 1;
            }
         }//return 1 if win of player 1 blocked 
      }
   }//end for, horizontal (right to left)check for possible win

return 0; //if no block took place
}

/**
 * try_block_vertical_x_in_row
 *
 * Function that tries to block x disks vertically in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been checked vertically for the possibility to block x and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was no possibility of blocking the x in a row of the other player.
 */
static int try_block_vertical_x_in_row(board_model *boardx, int nb_to_block){
   assert(boardx != NULL);

   int player_1_count = 0;
   int succesfull = 1;

   for (int i = 0; i < boardx->nb_columns; ++i){
      player_1_count = 0;
      for (int j = (boardx->nb_rows-1); j >= 0; --j){
         if(boardx->board_matrix[j][i] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;            
         }
         if(player_1_count == nb_to_block && ((j - 1) >= 0) && move_is_fair(boardx,(j-1),(i)) ){
            succesfull = add_pawn(boardx, 2, i);
            if (succesfull == 0){
               return 1;
            }
         }//return 1 if win of player 1 blocked 
      }
   }//end for, vertical check for possible win

return 0; //if no block took place
}

/**
 * try_block_diagonal1_x_in_row
 *
 * Function that tries to block x disks diagonally in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been checked in a positive gradient diagonal for the possibility to block x and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was no possibility of blocking the x in a row of the other player.  
 */
static int try_block_diagonal1_x_in_row(board_model *boardx, int nb_to_block){
   assert(boardx != NULL);

   int player_1_count = 0;
   int succesfull = 1;

   for (int i = (boardx->nb_rows -1); i >= 0 ; --i){
      int y = i;
      player_1_count = 0;
      for (int j = 0; j < boardx->nb_columns && y >= 0; ++j){
         if(boardx->board_matrix[y][j] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;            
         }
         if(player_1_count == nb_to_block &&move_is_fair(boardx,(y-1),(j+1))){
            succesfull = add_pawn(boardx, 2, j+1);
            if (succesfull == 0){
               return 1;
            }
         }//return 1 if player 2(IA) blocks a wins 
      y--;
      }
   }//end for, top left triangle (bottom to top)of matrix has been checked for block
 
   for (int i = 0; i < boardx->nb_columns; ++i){
      int y = i;
      player_1_count = 0;
      for (int j = (boardx->nb_rows-1); j >= 0 && y < boardx->nb_columns; --j){
         if(boardx->board_matrix[j][y] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;            
         }
         if(player_1_count == nb_to_block && move_is_fair(boardx,(j-1),(y+1))){
            succesfull = add_pawn(boardx, 2, y+1);
            if (succesfull == 0){
               return 1;
            }
         }//return 2 if player 2(IA) wins 
      ++y;
      }
   }//end for, bottom right triangle (bottom to top)of matrix has been checked for possible block
    
   for (int i = 0; i < boardx->nb_rows; ++i){
      int y = (boardx->nb_columns-1);

      player_1_count = 0;
      for (int j = i; j < boardx->nb_rows && y >= 0; ++j){
         if(boardx->board_matrix[j][y] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;            
         }
         if(player_1_count == nb_to_block && move_is_fair(boardx,(j+1),(y-1))){
            succesfull = add_pawn(boardx, 2, y-1);
            if (succesfull == 0){
               return 1;
            }
         }//return 2 if player 2(IA) wins 
      --y;
      }
   }//end for, bottom right triangle (top to botom)of matrix has been checked for possible block
       
   for (int i = (boardx->nb_columns-1); i >= 0; --i){
      int y = 0;

      player_1_count = 0;
      for (int j = i; j >=0 && y < boardx->nb_rows; --j){
         if(boardx->board_matrix[y][j] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;            
         }
         if(player_1_count == nb_to_block && move_is_fair(boardx,(y+1),(j-1))){
            succesfull = add_pawn(boardx, 2, j-1);
            if (succesfull == 0){
               return 1;
            }
         }//return 2 if player 2(IA) wins 
      ++y;
      }
   }//end for, top left triangle (top to botom)of matrix has been checked for possible block
      
return 0; //if no block took place
}
/**
 * try_block_diagonal2_x_in_row
 *
 * Function that tries to block x disks diagonaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been cheked in a negative gradient diagonal for the posibility to block x and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was no possibility of blocking the x in a row of the other player.  
 */
static int try_block_diagonal2_x_in_row(board_model *boardx, int nb_to_block){
   assert(boardx != NULL);

   int player_1_count = 0;
   int succesfull = 1;

   for (int i = (boardx->nb_columns - 1); i >= 0 ; i--){
      int y = (boardx->nb_rows - 1);
      player_1_count = 0;
      for (int j = i ; j >= 0 && y >= 0; --j){
         if(boardx->board_matrix[y][j] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;            
         }
         if(player_1_count == nb_to_block && move_is_fair(boardx,(y-1),(j-1)) ){
            succesfull = add_pawn(boardx, 2, j-1);
            if (succesfull == 0){
               return 1;
            }
         }//return 2 if player 2(IA) blocks a win 
      --y;
      }
   }//end for, bottom right triangle (bottom to top)of matrix has been checked for win

   for (int i = (boardx->nb_rows - 1); i >= 0 ; i--){
      int y = (boardx->nb_columns-1);
      player_1_count = 0;
      for (int j = i ; j >= 0 && y >= 0; --j){
         if(boardx->board_matrix[j][y] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;       
         }
         if(player_1_count == nb_to_block && move_is_fair(boardx,(j-1),(y-1))){
            succesfull = add_pawn(boardx, 2, y-1);
            if (succesfull == 0){
               return 1;
            }//return 2 if player 2(IA) blocks win 
         }
      --y;
      }
   }//end for, bottom right triangle(bottom to top) of matrix has been checked for win

   for (int i = 0; i < boardx->nb_rows; i++){
      int y = 0;
      player_1_count = 0;
      for (int j = i ; j < boardx->nb_rows && y < boardx->nb_columns; ++j){
         if(boardx->board_matrix[j][y] == 1){
            ++player_1_count;
         }else{
            player_1_count = 0;       
         }
         if(player_1_count == nb_to_block && move_is_fair(boardx,(j+1),(y+1)) ){
            succesfull = add_pawn(boardx, 2, y+1);
            if (succesfull == 0){
               return 1;
            }//return 2 if player 2(IA) wins 
         ++y;
         }
      }
   }//end for, bottom left triangle(top to bottom) of matrix has been checked for win
   
   for (int i = 0; i < boardx->nb_columns; ++i){
      int y = i;
      player_1_count = 0;
      for (int j = 0; j < boardx->nb_rows && y < boardx->nb_columns; ++j){
         if(boardx->board_matrix[j][y] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;            
         }
         if(player_1_count == nb_to_block && move_is_fair(boardx,(j+1),(y+1))){
            succesfull = add_pawn(boardx, 2, y+1);
            if (succesfull == 0){
               return 1;
            }
         }//return 2 if player 2(IA) wins 
      ++y;
      }
   }//end for, top right triangle (top to bottom)of matrix has been checked for possible win

return 0;//if no block took place
}


/**
 * random_play
 *
 * Function to play randomly on the board
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: one random play has been done on a connect 4 board.
 *
 * @return:
 *     1 when move is done
 */
static int random_play(board_model *boardx){
   assert(boardx != NULL);
   
   srand(time(NULL));
   int succesfull = -1;

   while(succesfull == -1){
      succesfull = add_pawn(boardx, 2, rand()%(get_board_nb_columns(boardx)-1));
   }

return 1;
} 

 /**
 * try_to_win
 *
 * Function that tries to connect 4 if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been checked for the possibility to connect 4 and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not the possibility of wining    
 */
static int try_to_win(board_model *boardx){
   assert(boardx != NULL);
   int do_win = 0;
   
   do_win = horizontal_try_add_to_x(boardx, 3);
   if (do_win){
      return 1;
   }
  
   do_win = vertical_try_add_to_x(boardx, 3);
   if (do_win){
      return 1;
   }
   
   do_win = diagonal1_try_add_to_x(boardx, 3);
   if (do_win){
      return 1;
   }
  
   do_win = diagonal2_try_add_to_x(boardx, 3);
   if (do_win){
      return 1;
   }
     
return 0;
}
/**
 * try_block_win
 *
 * Function  that tries to stop the other player from connecting 4
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been checked for the possibility to block 4 and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not any win to block    
 */
static int try_block_win(board_model *boardx){
   assert(boardx != NULL);

   int do_block_win = 0;

   do_block_win = try_block_horizontal_x_in_row(boardx,3);
   if (do_block_win){
      return 1;
   }

   do_block_win = try_block_vertical_x_in_row(boardx,3);
   if (do_block_win){
      return 1;
   }

   do_block_win = try_block_diagonal1_x_in_row(boardx,3);
   if (do_block_win){
      return 1;
   }

   do_block_win = try_block_diagonal2_x_in_row(boardx,3);
   if (do_block_win){
      return 1;
   }
 
return 0;
}
/**
 * try_to_make_3
 *
 * Function that tries to connect 3 if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been checked for the possibility to connect 3 and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not the possibility of connecting 3    
 */
static int try_to_make_3(board_model *boardx){
   assert(boardx != NULL);
   int do_3 = 0;
   
   do_3 = horizontal_try_add_to_x(boardx, 2);
   if (do_3){
      return 1;
   }

   do_3 = vertical_try_add_to_x(boardx, 2);
   if (do_3){
      return 1;
   }

   do_3 = diagonal1_try_add_to_x(boardx, 2);
   if (do_3){
      return 1;
   }

   do_3 = diagonal2_try_add_to_x(boardx, 2);
   if (do_3){
      return 1;
   }
   
return 0;
}

/**
 * try_block_3
 *
 * Function  that tries to stop the other player from connecting 3
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been checked for the possibility to block 3 and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not any 3 in a row to block    
 */
static int try_block_3(board_model *boardx){
   assert(boardx != NULL);

   int do_block_3 = 0;

   do_block_3 = try_block_horizontal_x_in_row(boardx,2);
   if (do_block_3){
      return 1;
   }
  
   do_block_3 = try_block_vertical_x_in_row(boardx,2);
   if (do_block_3){
      return 1;
   }
   
   do_block_3 = try_block_diagonal1_x_in_row(boardx,2);
   if (do_block_3){
      return 1;
   }
  
   do_block_3 = try_block_diagonal2_x_in_row(boardx,2);
   if (do_block_3){
      return 1;
   }

return 0;
}

void IA_play(board_model *boardx){
   assert(boardx != NULL);
   int move_done = 0;

   move_done = try_to_win(boardx);
   if(move_done){
      return;
   }
  
   move_done = try_block_win(boardx);
   if(move_done){
      return;
  }
  
  move_done = try_to_make_3(boardx);    
  if (move_done){
     return;
  }
 
  move_done = try_block_3(boardx);
  if(move_done){
     return;
  }
    
  move_done = random_play(boardx);
  
return;
}

