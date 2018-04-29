#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
//#include "back_office.h"
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include <gdk/gdkkeysyms.h>
#include "GUI.h"


int main(int argc, char **argv){


   char *optstring = ":f:n:::l::c::h::";
   char *top_score_path ;
   char *player_name = ""
   unsigned int lines_in_board = 7;
   unsigned int columns_in_board = 6;
   unsigned short *nb_turns = 0;

   while((val = getopt(argc, argv, optstring)) !=EOF){
      switch(val){
         case 'f':
            strcpy(top_score_path, optarg);
            printf("path to top score file is: %s\n", top_score_path);
            break;
          case 'n':
            printf("Have fun and Good luck %s!!\n",optarg);
            break;
          case 'l':
            lines_in_board = 0;
            for (int i = 0; i < strlen(optarg); ++i){
               lines_in_board*=10;
               lines_in_board += (optarg[i] - '0');
               if((optarg[i] - '0') > 9){
                  printf("error computing nb lines\n");
                  return 0;
               }
             }
             break;
          case 'h':
             printf("Help:\n   -f[write file path]\n   -n[enter player's name]\n   -l /-c[number of lines/columns]",);
             break;
          case 'c':
             columns_in_board = 0;
             for (int i = 0; i < strlen(optarg); ++i){
                columns_in_board*=10;
                columns_in_board += (optarg[i] - '0');
                if((optarg[i] - '0') > 9){
                   printf("error computing nb columns\n");
                   return 0;
                }
             }

            break;
         case '?':
            printf("unknown option: %c, try -h for help\n", optopt);
            return 0;
         case ':':
            printf("missing arg: %c, try -h for help.\n", optopt);
            return 0;
         default:
            printf("unknown option: %c, try -h for help.\n", optopt);
            return 0;
      }
   }

   printf("number of line = %u\n", lines_in_board);
   printf("number of columns = %u\n", columns_in_board);

   GtkWidget *window;
   GtkWidget *GUIboard;
   GtkWidget *menu;
   GtkWidget *megabox;

   board_model *game_board = init_board(lines_in_board, columns_in_board);
   board_vue *vue = // init vue board function 
   board_controler *controler = create_board_controler(game_board, board_vue *Bv){;

//making_buttons and putting in a container (Zone 3)
   GtkWidget *buttons_box = gtk_hbox_new(TRUE, 0);
   GtkWidget column_button[] = malloc(columns_in_board * sizeof(GtkWidget));
  

   for (int i = 0; i < columns_in_board; ++i){
     controler->buttons[i] =  gtk_button_new_with_label("");
     g_signal_connect(G_OBJECT(controler->buttons[i]), "clicked", G_CALLBACK(move_made), controler);
   }

   
   for (int i = 0; i < columns_in_board; ++i){
    gtk_box_pack_start(GTK_BOX(buttons_box), column_button[i], TRUE, TRUE, 0);
   }

   ///signal connect to be added



/*

put buttons in megabox

*/


   
   gtk_init(&argc, &argv);

   window = make_window();
   GUIboard = create_zone1(window);
   menu = create_zone2(window);
   

   megabox = gtk_vbox_new(FALSE, 0);
   gtk_container_add(GTK_CONTAINER(window),megabox);

   gtk_box_pack_start(GTK_BOX(megabox),menu, FALSE,FALSE,3);
   gtk_box_pack_start(GTK_BOX(megabox),GUIboard, TRUE,TRUE,0);
   gtk_box_pack_start(GTK_BOX(megabox),buttons_box, TRUE,TRUE,0);

   gtk_widget_show_all(window);
   gtk_main();

   //g_signal_connect(G_OBJECT(pQuitBtn), "clicked",G_CALLBACK(gtk_main_quit), NULL);
	
   return EXIT_SUCCESS;
}