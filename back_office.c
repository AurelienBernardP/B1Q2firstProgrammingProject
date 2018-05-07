#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "back_office.h"
#include "control.h"
#include "GUI.h"
#include "IA.h"

#define MIN_BOARD_SIZE 4
#define MAX_BOARD_SIZE 25


typedef enum{
   empty, yellow, red,
}piece_color;


void destroy_board(board_model *boardx){
   if(boardx == NULL){
      return;
   }
   
   if(boardx->board_matrix != NULL){
      for (int i = 0; i < boardx->nb_rows; ++i){
         if(boardx->board_matrix[i] != NULL){
            free(boardx->board_matrix[i]);
         }
      }
   } 
   free(boardx);

return;
}


board_model *init_board(unsigned short rows, unsigned short columns){
   
   if (columns < MIN_BOARD_SIZE || rows < MIN_BOARD_SIZE){
      printf("dimenssions entered can not be smaller than 4\n");
      return NULL;
   }

   if (columns > MAX_BOARD_SIZE || rows > MAX_BOARD_SIZE){
      printf("dimenssions entered can not be bigger than 25\n");
      return NULL;
   }

   board_model *boardx = malloc(sizeof(board_model));
   if (boardx == NULL){
      printf("ERROR: board_model could not be created (mem allocation)\n");
      return NULL;
   }

   boardx->nb_rows = rows;
   boardx->nb_columns = columns;
   boardx->player_moves = 0;

   boardx->board_matrix = malloc(boardx->nb_rows*sizeof(unsigned short int*));
   if(!boardx->board_matrix){
      printf("ERROR: board_model could not be created (mem allocation)\n");
      return NULL;
   }
      
   for(int r = 0; r < boardx->nb_rows;r++){
      boardx->board_matrix[r] = calloc(boardx->nb_columns, sizeof(unsigned short));
      if(!boardx->board_matrix[r]){
         printf("ERROR: board_model could not be created (mem allocation)\n");
         return NULL;
      }
   }

return boardx;
}

void reinitialize_board_model(board_model *boardx){
   assert(boardx != NULL);

   for (int i = 0; i < get_board_nb_rows(boardx); ++i){
      for (int j = 0; j < get_board_nb_columns(boardx); ++j){
         boardx->board_matrix[i][j] = 0;
      }
   }

   boardx->player_moves = 0;

return;
}

int add_pawn(board_model *boardx, unsigned int player, unsigned short column){
   assert(boardx != NULL && boardx->board_matrix != NULL);

   int i = (boardx->nb_rows - 1);
   while(i >= 0 && boardx->board_matrix[i][column] != 0){
      --i;
   }

   if(i ==(-1)){
      return (-1);// column is full
   }

   boardx->board_matrix[i][column] = player;

return 0;
}

/**
 * horizontal_check_win
 *
 * checks if one of the player has connected 4 pieces horizontaly in a row.
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
static int horizontal_check_win(board_model *boardx){
   assert(boardx != NULL);
   
   unsigned short player_1_count = 0;
   unsigned short player_2_count = 0;
   
   for (int i = 0; i < boardx->nb_rows; ++i){
      player_1_count = 0;
      player_2_count = 0;
      for (int j = 0; j < boardx->nb_columns; ++j){
         switch(boardx->board_matrix[i][j]){
            case(1):
               player_1_count++;
               player_2_count = 0;
               break;               
            case(2):
               player_2_count++;
               player_1_count = 0;
               break;
            default :
               player_1_count = 0;
               player_2_count = 0;
               break;
         }

         if(player_1_count>=4){
            return 1;
         }//return 1 if player 1 wins 
         if(player_2_count>=4){
            return 2;
         }//return 2 if player 2(IA) wins
      }
   }//end for, horizontal check

return 0; //after board_model has been checked horizontaly and no player has won yet, 0 returned
}

/**
 * vertical_check_win
 *
 * checks if one of the player has connected 4 pieces verticaly in a row.
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
static int vertical_check_win(board_model *boardx){
   assert(boardx != NULL);
   
   unsigned short player_1_count = 0;
   unsigned short player_2_count = 0;
   
   for (int i = 0; i < boardx->nb_columns; ++i){
      player_1_count = 0;
      player_2_count = 0;
      for (int j = 0; j < boardx->nb_rows; ++j){
         switch(boardx->board_matrix[j][i]){
            case(1):
               player_1_count++;
               player_2_count = 0;
               break;               
            case(2):
               player_2_count++;
               player_1_count = 0;
               break;
            default :
               player_1_count = 0;
               player_2_count = 0;
               break;
         }
         if(player_1_count>=4){
            return 1;
         }//return 1 if player 1 wins 
         if(player_2_count>=4){
            return 2;
         }//return 2 if player 2(IA) wins 
      }
   }//end for, vertical check
return 0; //board_model has been checked verticaly and no player has won yet, 0 returned
}

/**
 * diagonal1_check_win
 *
 * checks if one of the player has connected 4 pieces in a row, in positive gradient diagonal .
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
static int diagonal1_check_win(board_model *boardx){
   assert(boardx != NULL);
   
   unsigned short player_1_count = 0;
   unsigned short player_2_count = 0;
   
   for (int i = (boardx->nb_rows -1); i >= 0 ; --i){
      int y = i;
      player_2_count = 0;
      player_1_count = 0;
      for (int j = 0; j < boardx->nb_columns && y >= 0; ++j){
         switch(boardx->board_matrix[y][j]){
            case(1):
               player_1_count++;
               player_2_count = 0;
               break;               
            case(2):
               player_2_count++;
               player_1_count = 0;
               break;
            default :
               player_1_count = 0;
               player_2_count = 0;
               break;
         }
         if(player_1_count>=4){
            return 1;
         }//return 1 if player 1 wins 
         if(player_2_count>=4){
            return 2;
         }//return 2 if player 2(IA) wins 
         y--;
      }
   }//end for, bottom right triangle of matrix has been checked for win

   for (int i = 0; i < boardx->nb_columns; ++i){
      int y = i;
      player_2_count = 0;
      player_1_count = 0;
      for (int j = (boardx->nb_rows - 1); j >= 0 && y < boardx->nb_columns; --j){
         switch(boardx->board_matrix[j][y]){
            case(1):
               player_1_count++;
               player_2_count = 0;
               break;               
            case(2):
               player_2_count++;
               player_1_count = 0;
               break;
            default :
               player_1_count = 0;
               player_2_count = 0;
               break;
         }
         if(player_1_count >= 4){
            return 1;
         }//return 1 if player 1 wins 
         if(player_2_count >= 4){
            return 2;
         }//return 2 if player 2(IA) wins 
         ++y;
      }
   }//end for, bottom right triangle of matrix has been checked for win

return 0; //no player has won yet
}//end diagonal 1 check

/**
 * diagonal2_check_win
 *
 * checks if one of the player has connected 4 pieces in a row, in negative gradient diagonal .
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
static int diagonal2_check_win(board_model *boardx){
   assert(boardx != NULL);

   unsigned short player_1_count = 0;
   unsigned short player_2_count = 0;
   
   for (int i = 0; i < boardx->nb_columns ; i++){
      int y = i;
      player_2_count = 0;
      player_1_count = 0;
      for (int j = 0; j < boardx->nb_rows && y < boardx->nb_columns; ++j){
         switch(boardx->board_matrix[j][y]){
            case(1):
               player_1_count++;
               player_2_count = 0;
               break;               
            case(2):
               player_2_count++;
               player_1_count = 0;
               break;
            default :
               player_1_count = 0;
               player_2_count = 0;
               break;
         }
         if(player_1_count>=4){
            return 1;
         }//return 1 if player 1 wins 
         if(player_2_count>=4){
            return 2;
         }//return 2 if player 2(IA) wins 
         ++y;
      }
   }//end for, top right triangle of matrix has been checked for win

   for (int i = 0; i < boardx->nb_rows ; i++){
      int y = i;
      player_2_count = 0;
      player_1_count = 0;
      for (int j = 0 ; j < boardx->nb_columns && y < boardx->nb_rows; ++j){
         switch(boardx->board_matrix[y][j]){
            case(1):
               player_1_count++;
               player_2_count = 0;
               break;               
            case(2):
               player_2_count++;
               player_1_count = 0;
               break;
            default :
               player_1_count = 0;
               player_2_count = 0;
               break;
         }
         if(player_1_count >= 4){
            return 1;
         }//return 1 if player 1 wins 
         if(player_2_count >= 4){
            return 2;
         }//return 2 if player 2(IA) wins 
         y++;
      }
   }//end for, bottom right triangle of matrix has been checked for win
   
return 0;// if no player has won yet
}//end diagonal2_check_win.

int check_win(board_model *boardx){
   assert(boardx != NULL);
   
   int wining_player = 0;
   wining_player = horizontal_check_win(boardx);
   if(wining_player){
      return wining_player;
   }

   wining_player = vertical_check_win(boardx);
   if(wining_player){
      return wining_player;
   }

   wining_player = diagonal1_check_win(boardx);
   if(wining_player){
      return wining_player;
   }

   wining_player = diagonal2_check_win(boardx);

return wining_player;
}



int get_board_nb_rows(board_model *boardx){
  assert(boardx != NULL);
  return boardx->nb_rows;
}

int get_board_nb_columns(board_model *boardx){
   assert(boardx != NULL);
   return boardx->nb_columns;
}

int get_board_disk_value(board_model *boardx, unsigned int row, unsigned int column){
   assert(boardx != NULL);
   if(column >= boardx->nb_columns || row >= boardx->nb_rows){
      printf("error: Disk value couldnt be fetched\n");
      return(-1);
   }
   return boardx->board_matrix[row][column];
}

int column_is_full(board_model *boardx ,unsigned int nb_column){
   assert(boardx != NULL);

   if(boardx->board_matrix[0][nb_column] != 0){
      return 1;
   }else{
      return 0;
   }
return 0;
}