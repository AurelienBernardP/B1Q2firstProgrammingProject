#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <back_office.h>

#define MIN_BOARD_SIZE 4
#define MAX_BOARD_SIZE 20

struct board_t{
    unsigned short nb_rows;
    unsigned short nb_columns;
    unsigned short board_matrix**;

};

typedef enum{
empty, yellow, red,
}piece_color;


static void destroy_board(board *boardx){
   if(boardx == NULL){
      return;
   }
   
   if(boardx->board_matrix != NULL){
      for (int i = 0; i < boardx->nb_lines; ++i){
         if(boardx->board_matrix[i] != NULL){
            free(boardx->board_matrix[i]);
         }
      }
   } 
   free(boardx);
return;
}


board *init_board(char rows, char columns){

   unsigned short clmns = (columns - '0');
   unsigned short rws = (rows - '0');
   
   if (clmns < MIN_BOARD_SIZE || rws < MIN_BOARD_SIZE)
   {
    printf("dimenssions entered can not be smaller than 4\n");
    return NULL;
   }
   if (clmns > MAX_BOARD_SIZE || rws > MAX_BOARD_SIZE)
   {
      printf("dimenssions entered can not be bigger than 20\n");
      return NULL;
   }
   board *boardx = malloc(sizeof(board));
   if (boardx==NULL)
   {
      printf("ERROR: Board could not be created (mem allocation)\n");
      return NULL:
   }

   boardx->nb_rows = rws;
   boardx->nb_columns = clmns;

   boardx->board_matrix = malloc(boardx->nb_rows*sizeof(unsigned short int*));
      if(!boardx->board_matrix)
      {
         printf("ERROR: Board could not be created (mem allocation)\n");
         return NULL:
      }
      for(int r = 0; r < boardx->nb_rows;r++){
         boardx->board_matrix[r] = calloc(boardx->nb_columns*sizeof(unsigned short));
         if(!boardx->board_matrix[r])
         {
            printf("ERROR: Board could not be created (mem allocation)\n");
            return NULL:
         }
      }
return boardx;
}

int add_pawn(board *boardx, unsigned int player, unsigned short column){
   assert(boardx != NULL && boardx->board_matrix != NULL a);
   
   int i = nb_rows;
   while(i<=0 && boardx->board_matrix[i][column] != 0){
      --i;
   }
   if(i<0){
/*        printf("player %ud, error this column is already full\n",player);*/
      return 1;
   }
   boardx->board_matrix[i][column] = player;
return 0;
}

int check_win(board *boardx){
   assert(boardx != NULL);
   int wining_player = 0;

   horizontal_check_win(boardx);
   if(wining_player){
      return wining_player;
   }

   vertical_check_win(boardx);
   if(wining_player){
      return wining_player;
   }

   diagonal1_check_win(boardx);
   if(wining_player){
      return wining_player;
   }

   diagonal2_check_win(boardx);

return wining_player;
}

static int horizontal_check_win(board *boardx){
   assert(boardx != NULL);
   
   unsigned short player_1_count = 0;
   unsigned short player_2_count = 0;
   
   for (int i = 0; i < boardx->nb_rows; ++i){
      int y = 0
      player_1_count = 0;
      player_2_count = 0;
      for (int j = i; j < boardx->nb_columns; ++j){
         if(boardx->board_matrix[j][y] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;
            if(boardx->board_matrix[j][y] == 2){
               player_2_count++;
            }
            if (boardx->board_matrix[j][y] == 2){
               player_2_count = 0;
               player_1_count = 0;
            }
         }
        if(player_1_count>=4){
           return 1;
        }//return 1 if player 1 wins 
        if(player_2_count>=4){
           return 2;
        }//return 2 if player 2(IA) wins
        ++y; 
      }
   }//end for, horizontal check
return 0; //after board has been checked horizontaly and no player has won yet, 0 returned
}

static int vertical_check_win(board *boardx){
   assert(boardx != NULL);
   
   unsigned short player_1_count = 0;
   unsigned short player_2_count = 0;
   
   for (int i = 0; i < boardx->nb_columns; ++i){
      player_1_count = 0;
      player_2_count = 0;
      for (int j = 0; j < boardx->nb_rows; ++j){
         if(boardx->board_matrix[j][i] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;
            if(boardx->board_matrix[j][i] == 2){
               player_2_count++;
            }  
            if (boardx->board_matrix[j][i] == 2){
               player_2_count = 0;
               player_1_count = 0;
            }
         }
        if(player_1_count>=4){
           return 1;
        }//return 1 if player 1 wins 
        if(player_2_count>=4){
           return 2;
        }//return 2 if player 2(IA) wins 
      }
   }//end for, vertical check
return 0; //board has been checked verticaly and no player has won yet, 0 returned
}

static int diagonal1_check_win(board *boardx){
   assert(boardx != NULL);
   
   unsigned short player_1_count = 0;
   unsigned short player_2_count = 0;
   
   for (int i = (boardx->nb_rows -1); i >= 0 ; --i){
      int y = i;
      player_2_count = 0;
      player_1_count = 0;
      for (int j = 0; j < boardx->nb_columns && y >= 0; ++j){
         if(boardx->board_matrix[y][j] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;
            if(boardx->board_matrix[y][j] == 2){
               player_2_count++;
            }  
            if (boardx->board_matrix[y][j] == 2){
               player_2_count = 0;
               player_1_count = 0;
            }
         }
        if(player_1_count>=4){
           return 1;
        }//return 1 if player 1 wins 
        if(player_2_count>=4){
           return 2;
        }//return 2 if player 2(IA) wins 
        y--;
      }
   }//end for, top left triangle of matrix has been checked for win

   for (int i = 0; i < boardx->nb_columns; ++i){
      int y = i;
      player_2_count = 0;
      player_1_count = 0;
      for (int j = boardx->nb_rows; j >= 0 && y < boardx->nb_columns; --j){
         if(boardx->board_matrix[j][y] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;
            if(boardx->board_matrix[j][y] == 2){
               player_2_count++;
            }  
            if (boardx->board_matrix[j][y] == 2){
               player_2_count = 0;
               player_1_count = 0;
            }
         }
        if(player_1_count>=4){
           return 1;
        }//return 1 if player 1 wins 
        if(player_2_count>=4){
           return 2;
        }//return 2 if player 2(IA) wins 
        ++y;
      }
   }//end for, bottom right triangle of matrix has been checked for win

return 0; //no player has won yet
}//end diagonal 1 check

static int diagonal2_check_win(board *boardx){
   assert(boardx != NULL);

   unsigned short player_1_count = 0;
   unsigned short player_2_count = 0;
   
   for (int i = 0; i < boardx->nb_rows ; i++){
      int y = i;
      player_2_count = 0;
      player_1_count = 0;
      for (int j = 0; j < boardx->nb_columns && y y < boardx->nb_rows; ++j){
         if(boardx->board_matrix[j][y] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;
            if(boardx->board_matrix[j][y] == 2){
               player_2_count++;
            }  
            if (boardx->board_matrix[j][y] == 2){
               player_2_count = 0;
               player_1_count = 0;
            }
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

   for (int i = (boardx->nb_rows - 1); i >= 0 ; i--){
      int y = (boardx->nb_columns-1);
      player_2_count = 0;
      player_1_count = 0;
      for (int j = (boardx->nb_rows - 1) ; j >= 0 && y >= 0; --j){
         if(boardx->board_matrix[j][y] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;
            if(boardx->board_matrix[j][y] == 2){
               player_2_count++;
            }  
            if (boardx->board_matrix[j][y] == 2){
               player_2_count = 0;
               player_1_count = 0;
            }
         }
        if(player_1_count>=4){
           return 1;
        }//return 1 if player 1 wins 
        if(player_2_count>=4){
           return 2;
        }//return 2 if player 2(IA) wins 
        --y;
      }
   }//end for, bottom right triangle of matrix has been checked for win
   
return 0;// if no player has won yet
}//end diagonal2_check_win.

int get_board_nb_rows(board *boardx){
  assert(boardx != NULL);
  return boardx->nb_rows;
}

int get_board_nb_columns(board *boardx){
   assert(boardx != NULL);
   return boardx->nb_columns;
}

int get_board_disk_value(board *boardx, unsigned int row, unsigned int column){
   assert(boardx != NULL);
   if(column >= boardx->nb_columns || row >= boardx->nb_rows){
      printf("error: Disk value couldnt be fetched\n");
      return(-1);
   }
   return boardx->board_matrix[row][column];
}