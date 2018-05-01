#include "back_office.h"
#include "GUI.h"
#include "control.h"
#include "IA.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>


board_controler *create_board_controler(board_model *Bm, board_vue *Bv){
   assert(Bm != NULL && Bv != NULL);

   board_controler *board_c = malloc(sizeof(board_controler));
   if (board_c == NULL){
   	printf("Error allocating memory space for board controller\n");
   	return NULL;
   }
   board_c->bv = Bv;
   board_c->bm = Bm;

   board_c->buttons = malloc(get_board_nb_columns(Bm) * sizeof(GtkWidget*));
   if(board_c->buttons == NULL){
      printf("Error allocating memory space for buttons\n");
      return NULL;
   }

return board_c;
}

void move_made(GtkWidget *button, gpointer data){

    int error_code = 0;
	board_controler *controler = (board_controler*)data;

	unsigned short column_of_button = find_column_clicked(controler, button);
	if (column_of_button == get_board_nb_columns(controler->bm)){
	   printf("button clicked not found\n");
	   return;
	}
  printf("%hu\n",column_of_button );
  if (column_is_full(controler->bm, column_of_button)){
     return; // nothing done if the column is full
  }

    error_code = play_turn(controler->bm, controler->bv->gtk_table,controler->bv, column_of_button);
    if (error_code){
        printf("error when play is made\n");
        return;    
    }    
    return;
}

unsigned short find_column_clicked(board_controler *controler, GtkWidget *button){
    assert(controler  != NULL && button != NULL);

    unsigned short i = 0;

    while( i < get_board_nb_columns(controler->bm)){

       if(controler->buttons[i] == button){
          return i;
       }
       i++;
    }
	return i;
}

int play_turn(board_model *boardx, GtkWidget *pTable, board_vue *bv, unsigned short column){
   assert(boardx != NULL && pTable != NULL && bv != NULL);
  
   int wining_player = 0;
   int error_code = 0;
   add_pawn(boardx, 1, column);
   error_code = redraw_board(boardx, pTable, bv);
   if(error_code){
      return 1;
   }
   wining_player = check_win(boardx);
   switch(wining_player){
      case 1:
          //player one wining popup
          return 0;
      case 2:
         //player 2 wining popup
         return 0;
      default :
         ;//continue, NOP
    }
   boardx->player_moves += 1;


   IA_play(boardx);
  
   error_code = redraw_board(boardx, pTable, bv);
   if(error_code){
      return 1;
   }
   wining_player = check_win(boardx);
   switch(wining_player){
      case 1:
          //player one wining popup
          return 0;
      case 2:
         //player 2 wining popup
         return 0;
      default :
         ;//continue, NOP
    }

   return 0; 
}