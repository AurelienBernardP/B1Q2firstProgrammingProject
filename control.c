#include "back_office.h"
#include "GUI.h"
#include "contol.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

board_controler *create_board_controler(board_model *Bm, board_vue *Bv){
   assert(Bm != NULL && Bv != NULL);

   board_controler board_c = malloc(board_controler);
   if (board_c == NULL){
   	printf("Error allocating memory space for board controler\n");
   	return NULL;
   }
   board_c->bv = Bv;
   board_c->bm = Bm;

   board_c->buttons = malloc(get_board_nb_columns(Bm) * sizeof(GtkWidget));
   if(board_c->buttons = NULL;){
      printf("Error allocating memory space for buttons\n");
      return NULL;
   }

return board_c;
}

static void buttons_sesitivity_update(board_controler *board_c, board_model *boardx){

   for (int i = 0; i < get_board_nb_columns(boardx); ++i){
     if(column_is_full(boardx ,i)){
         board_c->buttons[i].sesitive = false
     }
   }
   return;
}

void move_made(GtkWidget *button, gpointer data){

    int error_code = 0
	board_controler *controler = (board_controler *)data;

	unsigned short column_of_button = find_column_clicked(controler, button);
	if (column_of_button == get_board_nb_columns(controler->bm)){
	   printf("button clicked not found\n");
	   return;
	}

    error_code = play_turn(controler->bm, controler->board_vue->gtk_table, controler->buttons,controler->bv->***image_table ,column_of_button)
    if (error_code){
        printf("error when play is made\n");
        return;    
    }    
    return;
}

unsigned short find_column_clicked(board_controler *controler,GtkWidget *button){
    assert(controler  != NULL && button != NULL);

    unsigned short i = 0;

    while( i < get_board_nb_columns(controler->bm)){
       if(&controler->buttons[i] == button){
          return i;
       }
       i++;
    }
	return i;
}