#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "back_office.h"
#include "IA.h"

/**
 * horizontal_try_add_to_x
 *
 * Function that tries to connect x disks horizontaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been cheked horizontaly for the posibility to connect x and move is made if possible
 *
 * @return:
 *         2 if move could be done
 *         0 if there was not the possibility of wining    
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
        if(player_2_count == nb_to_add_to && ((j + 1) < boardx->nb_columns) && boardx->board_matrix[i][j+1] == 0 && (boardx->board_matrix[i+1][j+1] != 0 || i == (boardx->nb_rows - 1))){
          succesfull = add_pawn(boardx, 2, j);
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
        if(player_2_count== nb_to_add_to && ((j - 1) >= 0) && boardx->board_matrix[i][j-1] == 0 ){
          succesfull = add_pawn(boardx, 2, j);
           if (succesfull == 0){
              return 2;
           }
        }//return 2 if AI wins 
      }
   }//end for, horizontal (right to left)check for possible win
return 0; //if no posiblity of wining horizontaly
}

/**
 * vertical_try_add_to_x
 *
 * Function that tries to connect x disks verticaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been cheked verticaly for the posibility to connect x and move is made if possible
 *
 * @return:
 *         2 if move could be done
 *         0 if there was not the possibility of wining    
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
return 0; //after board_model has been checked verticaly and no player has won yet, 0 returned
}

/**
 * diagonal1_try_add_to_x
 *
 * Function that tries to connect x disks diagonaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been cheked in a positive gradient diagonal for the posibility to connect x and move is made if possible
 *
 * @return:
 *         2 if move could be done
 *         0 if there was not the possibility of wining    
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
        if(player_2_count == nb_to_add_to &&((y-1)>=0 && (j+1)<boardx->nb_columns) && (boardx->board_matrix[y-1][j+1] == 0 && boardx->board_matrix[y][j+1] != 0)){
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
         if(boardx->board_matrix[j][y] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;            
         }
        if(player_2_count == nb_to_add_to && ((j-1) >= 0 && (y+1) < boardx->nb_columns) && (boardx->board_matrix[j-1][y+1] == 0 && boardx->board_matrix[j][y+1] != 0)){
          succesfull = add_pawn(boardx, 2, y+1);
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
        if(player_2_count == nb_to_add_to && ((j+1) < boardx->nb_rows && (y-1) >= 0) && (boardx->board_matrix[j+1][y-1] == 0 && ((j+2) == boardx->nb_rows || boardx->board_matrix[j+2][y-1] != 0 ))){
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
        if(player_2_count == nb_to_add_to && ((j-1) >= 0 && (y+1) < boardx->nb_columns) && (boardx->board_matrix[y+1][j-1] == 0 && ( (j+2) == boardx->nb_rows) || (boardx->board_matrix[j+2][y+1] != 0))){
          succesfull = add_pawn(boardx, 2, j-1);
           if (succesfull == 0){
              return 2;
           }
        }//return 2 if player 2(IA) wins 
        ++y;
      }
   }//end for, top left triangle (top to botom)of matrix has been checked for possible win

return 0; //no player has won yet
}

/**
 * diagonal2_try_add_to_x
 *
 * Function that tries to connect x disks diagonaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been cheked in a negative gradient diagonal for the posibility to connect x and move is made if possible
 *
 * @return:
 *         2 if move could be done
 *         0 if there was not the possibility of wining    
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
        if(player_2_count == nb_to_add_to && ((y-1) >= 0 && (j-1) >= 0) && (boardx->board_matrix[y-1][j-1] == 0 && boardx->board_matrix[y][j-1] != 0)){
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
         if(boardx->board_matrix[y][j] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;       
         }
        if(player_2_count == nb_to_add_to && ((y-1) >= 0 && (j-1) >= 0) && (boardx->board_matrix[j-1][y-1] == 0 && boardx->board_matrix[j][y-1] != 0)){
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
        if(player_2_count == nb_to_add_to && ((y+1) < boardx->nb_columns && (j+1) < boardx->nb_rows) && (boardx->board_matrix[j+1][y+1] == 0 && ( (j + 2) == boardx->nb_rows) || boardx->board_matrix[j+2][y+1] != 0)){
          succesfull = add_pawn(boardx, 2, y+1);
           if (succesfull == 0){
              return 2;
           }//return 2 if player 2(IA) wins 
        ++y;
        }
      }
   }//end for, bottom left triangle(top to bottom) of matrix has been checked for win

   for (int i = (boardx->nb_columns-1); i >= 0; --i){
      int y = 0;

      player_2_count = 0;
      for (int j = i; j >=0 && y < boardx->nb_rows; ++j){
         if(boardx->board_matrix[y][j] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;            
         }
        if(player_2_count == nb_to_add_to && ((j+1) < boardx->nb_columns && (y+1) < boardx->nb_rows) && (boardx->board_matrix[y+1][j-1] == 0 && (boardx->board_matrix[y+2][j+1] != 0 || (y + 2) == boardx->nb_rows))){
          succesfull = add_pawn(boardx, 2, j+1);
           if (succesfull == 0){
              return 2;
           }
        }//return 2 if player 2(IA) wins 
        ++y;
      }
   }//end for, top right triangle (top to botom)of matrix has been checked for possible win

return 0;
}

/**
 * try_block_horizontal_x_in_row
 *
 * Function that tries to block x disks horizontaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been cheked horizontaly for the posibility to block x and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not the possibility of wining    
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
        if(player_1_count == nb_to_block && ((j + 1) < boardx->nb_columns) && boardx->board_matrix[i][j+1] == 0 && ((i+1) == boardx->nb_rows || boardx->board_matrix[i+1][j+1] != 0 )){
          succesfull = add_pawn(boardx, 2, j+1);
           if (succesfull == 0){
              return 1;
           }
        }//return 1 if win of player 1 bloked 
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
        if(player_1_count == nb_to_block && ((j - 1) >= 0) && boardx->board_matrix[i][j-1] == 0 && ((i+1) == boardx->nb_rows || boardx->board_matrix[i+1][j-1] != 0)){
          succesfull = add_pawn(boardx, 2, j-1);
           if (succesfull == 0){
              return 1;
           }
        }//return 1 if win of player 1 bloked 
      }
   }//end for, horizontal (right to left)check for possible win
return 0; //if no block took place
}

/**
 * try_block_vertical_x_in_row
 *
 * Function that tries to block x disks verticaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been cheked verticaly for the posibility to block x and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not the possibility of wining    
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
        if(player_1_count == nb_to_block && ((j - 1) >= 0) && boardx->board_matrix[j-1][i] == 0 ){
          succesfull = add_pawn(boardx, 2, i);
           if (succesfull == 0){
              return 1;
           }
        }//return 1 if win of player 1 bloked 
      }
   }//end for, vertical check for possible win
return 0; //if no block took place
}

/**
 * try_block_diagonal1_x_in_row
 *
 * Function that tries to block x disks diagonaly in a connect 4 game if possible
 *
 * @param *boardx, a pointer to a board_model structure.  
 *
 * @pre:  boardx != NULL
 * @post: the board_model has been cheked in a positive gradient diagonal for the posibility to block x and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not the possibility of wining    
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
        if(player_1_count == nb_to_block &&((y-1)>=0 && (j+1)<boardx->nb_columns) && (boardx->board_matrix[y-1][j+1] == 0 && boardx->board_matrix[y][j+1] != 0)){
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
        if(player_1_count == nb_to_block && ((j-1) >= 0 && (y+1) < boardx->nb_columns) && (boardx->board_matrix[j-1][y+1] == 0 && boardx->board_matrix[j][y+1] != 0)){
          succesfull = add_pawn(boardx, 2, y+1);
           if (succesfull == 0){
              return 1;
           }
        }//return 2 if player 2(IA) wins 
        ++y;
      }
   }//end for, bottom right triangle (bottom to top)of matrix has been checked for possible block

   for (int i = 0; i < boardx->nb_rows; ++i){
      int y = 0;

      player_1_count = 0;
      for (int j = i; j < boardx->nb_rows && y < boardx->nb_columns; ++j){
         if(boardx->board_matrix[j][y] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;            
         }
        if(player_1_count == nb_to_block && ((j+1) < boardx->nb_rows && (y+1) < boardx->nb_columns) && (boardx->board_matrix[j+1][y+1] == 0 && ((j+2) == boardx->nb_rows || boardx->board_matrix[j+2][y+1] != 0))){
          succesfull = add_pawn(boardx, 2, y-1);
           if (succesfull == 0){
              return 1;
           }
        }//return 2 if player 2(IA) wins 
        ++y;
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
        if(player_1_count == nb_to_block && ((j-1) >= 0 && (y+1) < boardx->nb_columns) && (boardx->board_matrix[y+1][j-1] == 0 && (((j+2) == boardx->nb_rows ) || boardx->board_matrix[j+2][y+1] != 0))){
          succesfull = add_pawn(boardx, 2, y+1);
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
 *         0 if there was not the possibility of wining    
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
        if(player_1_count == nb_to_block && ((y-1) >= 0 && (j-1) >= 0) && (boardx->board_matrix[y-1][j-1] == 0 && boardx->board_matrix[y][j-1] != 0)){
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
         if(boardx->board_matrix[y][j] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;       
         }
        if(player_1_count == nb_to_block && ((y-1) >= 0 && (j-1) >= 0) && (boardx->board_matrix[j-1][y-1] == 0 && boardx->board_matrix[j][y-1] != 0)){
          succesfull = add_pawn(boardx, 2, y-1);
           if (succesfull == 0){
              return 1;
           }//return 2 if player 2(IA) blocks win 
        --y;
        }
      }
   }//end for, bottom right triangle(bottom to top) of matrix has been checked for win

   for (int i = 0; i < boardx->nb_rows; i++){
      int y = 0;
      player_1_count = 0;
      for (int j = i ; j < boardx->nb_rows && y < boardx->nb_columns; ++j){
         if(boardx->board_matrix[j][y] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;       
         }
        if(player_1_count == nb_to_block && ((y+1) < boardx->nb_columns && (j+1) < boardx->nb_rows) && (boardx->board_matrix[j+1][y+1] == 0 && ( (j + 2) == boardx->nb_rows || boardx->board_matrix[j+2][y+1] != 0))){
          succesfull = add_pawn(boardx, 2, y+1);
           if (succesfull == 0){
              return 1;
           }//return 2 if player 2(IA) wins 
        ++y;
        }
      }
   }//end for, bottom left triangle(top to bottom) of matrix has been checked for win

   for (int i = (boardx->nb_columns-1); i >= 0; --i){
      int y = 0;

      player_1_count = 0;
      for (int j = i; j >=0 && y < boardx->nb_rows; ++j){
         if(boardx->board_matrix[y][j] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;            
         }
        if(player_1_count == nb_to_block && ((j+1) < boardx->nb_columns && (y+1) < boardx->nb_rows) && (boardx->board_matrix[y+1][j-1] == 0 && ( (y + 2) == boardx->nb_rows || boardx->board_matrix[y+2][j+1] != 0))){
          succesfull = add_pawn(boardx, 2, j+1);
           if (succesfull == 0){
              return 1;
           }
        }//return 2 if player 2(IA) wins 
        ++y;
      }
   }//end for, top right triangle (top to botom)of matrix has been checked for possible win

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
 * @post: one play has been done on a conectc 4 board.
 *
 * @return:
 *     1 when move is done
 */
static int random_play(board_model *boardx){
   assert(boardx != NULL);
   
   srand(time(NULL));
   int succesfull = 1;
   printf("random play \n");
   while(succesfull == 1){
   succesfull = add_pawn(boardx, 2, rand()%(boardx->nb_columns-1));
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
 * @post: the board_model has been cheked for the posibility to connect 4 and move is made if possible
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
 * @post: the board_model has been cheked for the posibility to block 4 and move is made if possible
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
 * @post: the board_model has been cheked for the posibility to connect 3 and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not the possibility of wining    
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
 * @post: the board_model has been cheked for the posibility to block 3 and move is made if possible
 *
 * @return:
 *         1 if move could be done
 *         0 if there was not any win to block    
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
     printf("win\n");
      return;
   }
   move_done = try_block_win(boardx);

   if(move_done){
          printf("blocked\n");
      return;
  }
  move_done = try_to_make_3(boardx);
  
  if (move_done){
         printf("make 3\n");
     return;
  }
  move_done = try_block_3(boardx);
  if(move_done){
    printf("block 3\n");
     return;
  }
  move_done = random_play(boardx);

return;
}