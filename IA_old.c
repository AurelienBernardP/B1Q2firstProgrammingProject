#include <stdio.h>
#include <stdlib.h>

//#include "back_office.h"
//#include "IA.h"

/*
board *IA_play(board *boardx){
   assert(boardx != NULL);

   try_to_win(boardx);

   try_block_win(boardx);

   try_make_3(boardx);

   try_block_3(boardx);

   random_play(board *boardx)

}
*/

static int try_to_win(board *boardx){
   assert(boardx != NULL);
   int do_win = 0;
   
   do_win = horizontal_try_to_win(boardx);
   if (do_win){
   	  return 1;
   }

   do_win = vertical_try_to_win(boardx);
   if (do_win){
   	  return 1;
   }

   do_win = horizontal_try_to_win(boardx);
   if (do_win){
   	  return 1;
   }

   do_win = diagonal1_try_to_win(boardx);
   if (do_win){
   	  return 1;
   }

   do_win = diagonal2_try_to_win(boardx);
   if (do_win){
   	  return 1;
   }
return 0;
}

static int try_block_win(board *boardx){
   assert(boardx != NULL);

   int do_block_win = 0;

   do_block_win = try_block_horizontal_win(boardx);
   if (do_block_win){
   	  return 1;
   }

   do_block_win = try_block_vertical_win(boardx);
   if (do_block_win){
   	  return 1;
   }

   do_block_win = try_block_diagonal1_win(boardx);
   if (do_block_win){
   	  return 1;
   }

   do_block_win = try_block_diagonal2_win(boardx);
   if (do_block_win){
   	  return 1;
   }
return 0;
}

/*static int try_make_3(board *boardx){
   assert(boardx != NULL);
   int do_3 = 0;

   do_3 = try_block_horizontal_win(boardx);
   if (do_block_win){
   	  return 1;
   }

   do_3 = try_block_vertical_win(boardx);
   if (do_block_win){
   	  return 1;
   }

   do_3 = try_block_diagonal1_win(boardx);
   if (do_block_win){
   	  return 1;
   }

   do_3 = try_block_diagonal2_win(boardx);
   if (do_block_win){
   	  return 1;
   }
return 0;
}*/

/*static int try_block_3(board *boardx){
   assert(boardx != NULL);

}*/

/*static int random_play(board *boardx){
   assert(boardx != NULL);

}*/

static int horizontal_try_to_win(board *boardx){
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
        if(player_2_count == 3 && ((j + 1) < boardx->nb_columns) && boardx->board_matrix[i][j+1] == 0 && (boardx->board_matrix[i+1][j+1] != 0 || i ==(boardx->nb_rows - 1))){
           add_pawn(boardx, 2, j);
           if (succesfull == 0){
           	  return 2;
           }
        }//return 2 if AI wins 
      }
   }//end for, horizontal (left to right)check for possible win

   	for (int i = (boardx->nb_rows - 1); i >= 0; --i){
      player_2_count = 0;
      for (int j = boardx->nb_columns; j > 0; --j){
         if(boardx->board_matrix[i][j] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;
         }
        if(player_2_count==3 && ((j - 1) >= 0) && boardx->board_matrix[i][j-1] == 0 ){
           add_pawn(boardx, 2, j);
           if (succesfull == 0){
           	  return 2;
           }
        }//return 2 if AI wins 
      }
   }//end for, horizontal (right to left)check for possible win
return 0; //if no posiblity of wining horizontaly
}

static int vertical_try_to_win(board *boardx){
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
        if(player_2_count == 3 && ((j - 1) >= 0) && boardx->board_matrix[j-1][i] == 0 ){
           add_pawn(boardx, 2, i);
           if (succesfull == 0){
           	  return 2;
           }
        }//return 2 if player 2(IA) wins 
      }
   }//end for, vertical check
return 0; //after board has been checked verticaly and no player has won yet, 0 returned
}

static int diagonal1_try_to_win(board *boardx){
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
        if(player_2_count == 3 &&((y-1)>=0 && (j+1)<boardx->nb_columns) && (boardx->board_matrix[y-1][j+1] == 0 && boardx->board_matrix[y][j+1] != 0)){
           add_pawn(boardx, 2, j+1);
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
        if(player_2_count == 3 && ((j-1) >= 0 && (y+1) < boardx->nb_columns) && (boardx->board_matrix[j-1][y+1] == 0 && boardx->board_matrix[j][y+1] != 0)){
           add_pawn(boardx, 2, y+1);
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
        if(player_2_count == 3 && ((j+1) < boardx->nb_rows && (y-1) >= 0) && (boardx->board_matrix[j+1][y-1] == 0 && (boardx->board_matrix[j+2][y-1] != 0 ||(j+2) == boardx->nb_rows))){
           add_pawn(boardx, 2, y-1);
           if (succesfull == 0){
           	  return 2;
           }
        }//return 2 if player 2(IA) wins 
        --y;
      }
   }//end for, bottom right triangle (top to botom)of matrix has been checked for possible win

   for (int i = (boardx->nb_columns-1); i >= 0; --i){
      int y = 0;

      player_1_count = 0;
      for (int j = i; j >=0 && y < boardx->nb_rows; --j){
         if(boardx->board_matrix[y][j] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;            
         }
        if(player_2_count == 3 && ((j-1) >= 0 && (y+1) < boardx->nb_columns) && (boardx->board_matrix[y+1][j-1] == 0 && ((boardx->board_matrix[j+2][y+1] != 0) || (j+2) == boardx->nb_rows))){
           add_pawn(boardx, 2, j-1);
           if (succesfull == 0){
           	  return 2;
           }
        }//return 2 if player 2(IA) wins 
        ++y;
      }
   }//end for, top left triangle (top to botom)of matrix has been checked for possible win

return 0; //no player has won yet
}

static int diagonal2_try_to_win(board *boardx){
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
        if(player_2_count == 3 && ((y-1) >= 0 && (j-1) >= 0) && (boardx->board_matrix[y-1][j-1] == 0 && boardx->board_matrix[y][j-1] != 0)){
           add_pawn(boardx, 2, j-1);
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
        if(player_2_count == 3 && ((y-1) >= 0 && (j-1) >= 0) && (boardx->board_matrix[j-1][y-1] == 0 && boardx->board_matrix[j][y-1] != 0)){
           add_pawn(boardx, 2, j-1);
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
        if(player_2_count == 3 && ((y+1) y < boardx->nb_columns && (j+1) < boardx->nb_rows) && (boardx->board_matrix[j+1][y+1] == 0 && (boardx->board_matrix[j+2][y+1] != 0 || (j + 2) == boardx->nb_rows))){
           add_pawn(boardx, 2, y+1);
           if (succesfull == 0){
           	  return 2;
           }//return 2 if player 2(IA) wins 
        ++y;
        }
      }
   }//end for, bottom left triangle(top to bottom) of matrix has been checked for win

   for (int i = (boardx->nb_columns-1); i >= 0; --i){
      int y = 0;

      player_1_count = 0;
      for (int j = i; j >=0 && y < boardx->nb_rows; ++j){
         if(boardx->board_matrix[y][j] == 2){
            player_2_count++;
         }else{
            player_2_count = 0;            
         }
        if(player_2_count == 3 && ((j+1) < boardx->nb_columns && (y+1) < boardx->nb_rows) && (boardx->board_matrix[y+1][j-1] == 0 && && (boardx->board_matrix[y+2][j+1] != 0 || (y + 2) == boardx->nb_rows))){
           add_pawn(boardx, 2, j+1);
           if (succesfull == 0){
           	  return 2;
           }
        }//return 2 if player 2(IA) wins 
        ++y;
      }
   }//end for, top right triangle (top to botom)of matrix has been checked for possible win

return 0;
}

int try_block_horizontal_win(board *boardx){
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
        if(player_1_count == 3 && ((j + 1) < boardx->nb_columns) && boardx->board_matrix[i][j+1] == 0 ){
           add_pawn(boardx, 2, j+1);
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
        if(player_1_count==3 && ((j - 1) >= 0) && boardx->board_matrix[i][j-1] == 0 ){
           add_pawn(boardx, 2, j-1);
           if (succesfull == 0){
           	  return 1;
           }
        }//return 1 if win of player 1 bloked 
      }
   }//end for, horizontal (right to left)check for possible win
return 0; //if no block took place
}

static int try_block_vertical_win(board *boardx){
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
        if(player_1_count == 3 && ((j - 1) >= 0) && boardx->board_matrix[j][i-1] == 0 ){
           add_pawn(boardx, 2, i-1);
           if (succesfull == 0){
           	  return 1;
           }
        }//return 1 if win of player 1 bloked 
      }
   }//end for, vertical check for possible win
return 0; //if no block took place
}

static int try_block_diagonal1_win(board *boardx){
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
        if(player_1_count == 3 &&((y-1)>=0 && (j+1)<boardx->nb_columns) && (boardx->board_matrix[y-1][j+1] == 0 && boardx->board_matrix[y][j+1] != 0)){
           add_pawn(boardx, 2, j+1);
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
      for (int j = boardx->nb_rows; j >= 0 && y < boardx->nb_columns; --j){
         if(boardx->board_matrix[j][y] == 1){
            player_1_count++;
         }else{
            player_1_count = 0;            
         }
        if(player_1_count == 3 && ((j-1) >= 0 && (y+1) < boardx->nb_columns) && (boardx->board_matrix[j-1][y+1] == 0 && boardx->board_matrix[j][y+1] != 0)){
           add_pawn(boardx, 2, y+1);
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
        if(player_1_count == 3 && ((j+1) < boardx->nb_rows && (y+1) < boardx->nb_columns) && (boardx->board_matrix[j+1][y+1] == 0 && (boardx->board_matrix[j+2][y+1] != 0 ||(j+2) == boardx->nb_rows))){
           add_pawn(boardx, 2, y-1);
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
        if(player_1_count == 3 && ((j-1) >= 0 && (y+1) < boardx->nb_columns) && (boardx->board_matrix[y+1][j-1] == 0 && ((boardx->board_matrix[j+2][y+1] != 0) ||(j+2) == boardx->nb_rows))){
           add_pawn(boardx, 2, y+1);
           if (succesfull == 0){
           	  return 1;
           }
        }//return 2 if player 2(IA) wins 
        ++y;
      }
   }//end for, top left triangle (top to botom)of matrix has been checked for possible block

return 0; //if no block took place
}

static int try_block_diagonal2_win(board *boardx){
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
        if(player_1_count == 3 && ((y-1) >= 0 && (j-1) >= 0) && (boardx->board_matrix[y-1][j-1] == 0 && boardx->board_matrix[y][j-1] != 0)){
           add_pawn(boardx, 2, j-1);
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
        if(player_1_count == 3 && ((y-1) >= 0 && (j-1) >= 0) && (boardx->board_matrix[j-1][y-1] == 0 && boardx->board_matrix[j][y-1] != 0)){
           add_pawn(boardx, 2, y-1);
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
        if(player_1_count == 3 && ((y+1) y < boardx->nb_columns && (j+1) < boardx->nb_rows) && (boardx->board_matrix[j+1][y+1] == 0 && (boardx->board_matrix[j+2][y+1] != 0 || (j + 2) == boardx->nb_rows))){
           add_pawn(boardx, 2, y+1);
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
        if(player_1_count == 3 && ((j+1) < boardx->nb_columns && (y+1) < boardx->nb_rows) && (boardx->board_matrix[y+1][j-1] == 0 && && (boardx->board_matrix[y+2][j+1] != 0 || (y + 2) == boardx->nb_rows))){
           add_pawn(boardx, 2, j+1);
           if (succesfull == 0){
           	  return 1;
           }
        }//return 2 if player 2(IA) wins 
        ++y;
      }
   }//end for, top right triangle (top to botom)of matrix has been checked for possible win

return 0;//if no block took place
}

