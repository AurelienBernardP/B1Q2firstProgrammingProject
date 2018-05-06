#include "back_office.h"
#include "GUI.h"
#include "control.h"
#include "IA.h"
#include "top10.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>


board_controler *create_board_controler(board_model *Bm, board_vue *Bv, player* current_player ){
   assert(Bm != NULL && Bv != NULL && current_player != NULL );

   board_controler *board_c = malloc(sizeof(board_controler));
   if (board_c == NULL){
   	printf("Error allocating memory space for board controller\n");
   	return NULL;
   }
   board_c->bv = Bv;
   board_c->bm = Bm;
   board_c->current_player = current_player;
   board_c->buttons = malloc(get_board_nb_columns(Bm) * sizeof(GtkWidget*));
   if(board_c->buttons == NULL){
      printf("Error allocating memory space for buttons\n");
      return NULL;
   }
   for (int i = 0; i < get_board_nb_columns(Bm); ++i){
     board_c->buttons[i] =  gtk_button_new_with_label("");
     g_signal_connect(G_OBJECT(board_c->buttons[i]), "clicked", G_CALLBACK(move_made), board_c);
   }
return board_c;
}

GtkWidget *create_menu(GtkWidget *window, board_controler *controler, char* path){
   assert(window != NULL && controler != NULL && path != NULL);
   GtkWidget *menu_bar = gtk_menu_bar_new();
   GtkWidget *menu_partie = gtk_menu_new();
   GtkAccelGroup *accelerator = gtk_accel_group_new();
   gtk_window_add_accel_group(GTK_WINDOW(window), accelerator);

   GtkWidget *item_partie,*item_new_game, *item_top_scores, *item_aide, *item_quit;
   item_partie = gtk_menu_item_new_with_mnemonic("_Partie");
   item_new_game = gtk_menu_item_new_with_mnemonic("_Nouvelle Partie");
   item_top_scores = gtk_menu_item_new_with_mnemonic("_Top score");
   item_aide = gtk_menu_item_new_with_mnemonic("_Aide");
   item_quit = gtk_menu_item_new_with_mnemonic("_Quitter");

   gtk_widget_add_accelerator(item_quit, "activate",accelerator, GDK_q, GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

   gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_partie),menu_partie);

   gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie),item_new_game);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie),item_top_scores);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie),item_quit);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),item_partie);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),item_aide);

   g_signal_connect(G_OBJECT(item_aide),"activate",G_CALLBACK(show_aide), NULL);
   g_signal_connect(G_OBJECT(item_quit),"activate",G_CALLBACK(gtk_main_quit), NULL);
   g_signal_connect(G_OBJECT(item_new_game),"activate",G_CALLBACK(new_game), controler);
   g_signal_connect(G_OBJECT(item_top_scores),"activate",G_CALLBACK(show_top_list), path);
   
return menu_bar;
}

void move_made(GtkWidget *button, gpointer data){
   board_controler *controler = (board_controler*)data;
   assert(controler != NULL);

  int error_code = 0;

	unsigned short column_of_button = find_column_clicked(controler, button);
	if (column_of_button == get_board_nb_columns(controler->bm)){
	   printf("button clicked not found\n");
	   return;
	}

  if (column_is_full(controler->bm, column_of_button)){
     return; // nothing done if the column is full
  }

    error_code = play_turn(controler->bm, controler->bv->gtk_table,controler->bv, column_of_button, controler->current_player);
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

void new_game(GtkWidget *button, gpointer data){
   board_controler *controler = (board_controler*)data;
   assert(controler != NULL);

   reinitialize_board_model(controler->bm);
   
   redraw_board(controler->bm, controler->bv->gtk_table, controler->bv);

   new_game_popup( NULL);

   return;
}

int play_turn(board_model *boardx, GtkWidget *pTable, board_vue *bv, unsigned short column, player* current_player){
   assert(boardx != NULL && pTable != NULL && bv != NULL && current_player != NULL);
  
   int wining_player = 0;
   int error_code = 0;
   wining_player = check_win(boardx);
   if (wining_player){
     printf("player %d won\n",wining_player );
   }
   switch(wining_player){
      case 1:
          show_you_won(NULL);
          return 0;
      case 2:
         show_you_lose(NULL);
         return 0;
      default :
         break;//continue, NOP

    }

   add_pawn(boardx, 1, column);
   
   boardx->player_moves += 1;
   wining_player = check_win(boardx);
   if (wining_player){
     printf("player %d won\n",wining_player );
   }
   switch(wining_player){
      case 1:
          error_code = redraw_board(boardx, pTable, bv);
          change_player_score(current_player, boardx->player_moves );
          top10_file_gestion(get_path(current_player), current_player);
          show_you_won(NULL );
          return 0;
      case 2:
          show_you_lose( NULL);         
         return 0;
      default :
         break;//continue, NOP
    }
   
   IA_play(boardx);
  
   error_code = redraw_board(boardx, pTable, bv);
   if(error_code){
      return 1;
   }
   wining_player = check_win(boardx);
   switch(wining_player){
      case 1:
          show_you_won(NULL );
          return 0;
      case 2:
         show_you_lose(NULL);
         return 0;
      default :
         break;//continue, NOP
    }
     if (wining_player){
     printf("player %d won\n",wining_player );
   }
   return 0; 
}