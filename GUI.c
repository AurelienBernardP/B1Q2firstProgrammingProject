#include<stdlib.h>
#include<gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include <assert.h>
#include "GUI.h"
#include "back_office.h"

GtkWidget *make_window(board_model *boardx){
   
   GtkWidget *pF = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(pF), "Puissance 4");
   gtk_window_set_default_size(GTK_WINDOW(pF),(get_board_nb_columns(boardx)*50), (get_board_nb_rows(boardx)*50));
   g_signal_connect(G_OBJECT(pF), "destroy", G_CALLBACK(gtk_main_quit), NULL);


return pF;
}

board_vue *create_board_vue(board_model* boardx){
   assert(boardx != NULL);

  board_vue *board_v = malloc(sizeof(board_vue));
  if (board_v == NULL){
     printf("error alocating memory space for on screen board\n");
     return NULL;
  }
  board_v->bm = boardx;

    board_v->image_table = malloc(get_board_nb_rows(boardx) * sizeof(GtkWidget**));
  if (board_v->image_table == NULL){
     printf("memory allocation error for image loading 1\n");
     return NULL;
  }
  for (int i = 0; i < get_board_nb_rows(boardx); ++i){
      board_v->image_table[i] = malloc(get_board_nb_columns(boardx) * sizeof(GtkWidget*));
      if (board_v->image_table[i] == NULL){
        printf("memory allocation error for image loading\n");
        return NULL;
      }
   }

  for (int i = 0; i < get_board_nb_rows(boardx); ++i){
     for (int j = 0; j < get_board_nb_columns(boardx); ++j){
          board_v->image_table[i][j] = gtk_image_new_from_file("bleu.gif");
     }
  }

  board_v->gtk_table = gtk_table_new(get_board_nb_rows(boardx), get_board_nb_columns(boardx), TRUE);

  for (int i = 0; i < get_board_nb_rows(boardx); ++i){
     for (int j = 0; j < get_board_nb_columns(boardx); ++j){
          gtk_table_attach(GTK_TABLE(board_v->gtk_table), board_v->image_table[i][j] ,j,(j+1),i,(i+1),GTK_EXPAND,GTK_EXPAND,0,0);
     }
  }
return board_v;
}

int redraw_board(board_model *boardx, GtkWidget *pTable, board_vue *bv){
   assert(boardx != NULL && pTable != NULL && bv != NULL);
	for (int i = 0; i < get_board_nb_rows(boardx); ++i){
	   for (int j = 0; j < get_board_nb_columns(boardx); ++j){
        switch(get_board_disk_value(boardx,i ,j)){

           case 0:
              bv->image_table[i][j] = gtk_image_new_from_file("bleu.gif");
              break;

           case 1:
              bv->image_table[i][j] = gtk_image_new_from_file("jaune.gif");
              break;

           case 2:
              bv->image_table[i][j] = gtk_image_new_from_file("rouge.gif");
              break;

           default:
              return (-1);
        }
     }

  }
  for (int i = 0; i < get_board_nb_rows(boardx); ++i){
     for (int j = 0; j < get_board_nb_columns(boardx); ++j){
          gtk_table_attach(GTK_TABLE(bv->gtk_table), bv->image_table[i][j] ,j,(j+1),i,(i+1),GTK_EXPAND,GTK_EXPAND,0,0);

     }
  }
  gtk_widget_show_all(pTable);
return 0;
}

void show_aide(GtkWidget *widget, gpointer window) {
    
  GtkWidget *aide_popup;
  aide_popup = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Puissance 4 \nAurélien Bernard \n20176639 \nCours INFO0030");
  gtk_window_set_title(GTK_WINDOW(aide_popup), "Info");
  gtk_dialog_run(GTK_DIALOG(aide_popup));
  gtk_widget_destroy(aide_popup);
  return;
}

void show_you_won(GtkWidget *widget, gpointer window) {
    
  GtkWidget *you_won;
  you_won = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "CONGRATULATIONS! \nyou have won this game! \nskill or just luck?  ¯|_(ツ)_/¯ \n try again just to bu sure! ;D");
  gtk_window_set_title(GTK_WINDOW(you_won), "YOU WON!");
  gtk_dialog_run(GTK_DIALOG(you_won));
  gtk_widget_destroy(you_won);
  return;
}

void show_you_lose(GtkWidget *widget, gpointer window) {
    
  GtkWidget *you_lose;
  you_lose = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "GAME_OVER \n    YOU   LOSE \n\n you can try again with:\n     Nouvelle Partie");
  gtk_window_set_title(GTK_WINDOW(you_lose), "GAME OVER");
  gtk_dialog_run(GTK_DIALOG(you_lose));
  gtk_widget_destroy(you_lose);
  return;
}

void new_game_popup(GtkWidget *widget, gpointer window) {
    
  GtkWidget *new_game;
  new_game = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Nouvelle partie !\n    Bonne chance!");
  gtk_window_set_title(GTK_WINDOW(new_game), "NEW GAME");
  gtk_dialog_run(GTK_DIALOG(new_game));
  gtk_widget_destroy(new_game);
  return;
}