#include<stdlib.h>
#include<gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
//#include"back_office.h"
#include <assert.h>
#include "GUI.h"

GtkWidget *make_window(){
   
   GtkWidget *pF = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(pF), "Puissance 4");
   gtk_window_set_default_size(GTK_WINDOW(pF),(get_board_nb_rows*50), (get_board_nb_columns*50));
   g_signal_connect(G_OBJECT(pF), "destroy", G_CALLBACK(gtk_main_quit), NULL);


return pF;
}

GtkWidget *create_zone1(board* boardx){

  GtkWidget *pTable = gtk_table_new(get_board_nb_rows(boardx), get_board_nb_columns(boardx), TRUE);//has to be changed to numbers in board, tis is just a test
  GtkWidget ***image_table; 
  image_table = malloc(get_board_nb_rows(boardx) * sizeof(GtkWidget**));
  if (!image_table){
     printf("memory allocation error for image loading\n");
     return NULL;
  }
  for (int i = 0; i < get_board_nb_rows(boardx); ++i){
      image_table[i] = malloc(get_board_nb_columns(boardx) * sizeof(GtkWidget*));
      if (image_table[i] == NULL){
        printf("memory allocation error for image loading\n");
        return NULL;
      }
   }

  for (int i = 0; i < get_board_nb_rows(boardx); ++i){
     for (int j = 0; j < get_board_nb_columns(boardx); ++j){
          image_table[i][j] = gtk_image_new_from_file("bleu.gif");
     }
  }
  for (int i = 0; i < get_board_nb_rows(boardx); ++i){
     for (int j = 0; j < get_board_nb_columns(boardx); ++j){
          gtk_table_attach(GTK_TABLE(pTable), image_table[i][j] ,j,(j+1),i,(i+1),GTK_EXPAND,GTK_EXPAND,0,0);
     }
  }
//free if posible
return pTable;
}


GtkWidget *create_zone2(GtkWidget *window){
   assert(window != NULL);
   GtkWidget *menu_bar = gtk_menu_bar_new();
   GtkWidget *menu_partie = gtk_menu_new();
   GtkWidget *menu_aide = gtk_menu_new();
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
//mneumonic is not working well xd 
   g_signal_connect(G_OBJECT(item_quit),"activate",G_CALLBACK(gtk_main_quit), NULL);

return menu_bar;
}


int modif_board_gui(GtkWidget *pTable, board *boardx, GtkWidget *buttons){
   assert(window != NULL && boardx != NULL);

   int error_code = 0;

   error_code = modif_zone1(boardx, pTable);
   if(error_code){
      printf("Error updating the board\n");
      return 1;
   }
   
    modif_zone3(buttons,boardx);
return 0;
}

static int modif_zone1(board *boardx,GtkWidget *pTable){
   assert(boardx != NULL && pTable != NULL);

    GtkWidget ***image_table;

    image_table = malloc(get_board_nb_rows(boardx) * sizeof(GtkWidget**));
    if (!image_table){
       printf("memory allocation error for image loading\n");
       return NULL;
    }
    for (int i = 0; i < get_board_nb_rows(boardx); ++i){
      image_table[i] = malloc(get_board_nb_columns * sizeof(GtkWidget*));
      if (image_table[i] == NULL){
        printf("memory allocation error for image loading\n");
        return NULL;
      }
   }

	for (int i = 0; i < get_board_nb_rows(boardx); ++i){
	   for (int j = 0; j < get_board_nb_columns(boardx); ++j){

     switch(get_board_disk_value(boardx,i ,j)){

        case 0:
          image_table[i][j] = gtk_image_new_from_file("bleu.gif");
           break;

        case 1:
            image_table[i][j] = gtk_image_new_from_file("jaune.gif");
           break;

        case 2:
             image_table[i][j] = gtk_image_new_from_file("rouge.gif");
           break;

        default:
             return (-1)
     }
               gtk_table_attach(GTK_TABLE(pTable), image_table[i][j] ,j,(j+1),i,(i+1),GTK_EXPAND,GTK_EXPAND,0,0);

	   }
	}

   for (int i = 0; i < get_board_nb_rows(boardx); ++i){
      for (int j = 0; j < get_board_nb_columns(boardx); ++j){
          gtk_table_attach(GTK_TABLE(pTable), image_table[i][j] ,j,(j+1),i,(i+1),GTK_EXPAND,GTK_EXPAND,0,0);
     }
  }
return 0;
}

static void modif_zone3(GtkWidget buttons[], board *boardx){

   for (int i = 0; i < get_board_nb_columns(boardx); ++i){
     if(column_is_full(boardx ,i)){
         buttons[i].sesitive = false
     }
   }
}
