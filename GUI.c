#include <stdlib.h>
#include <gtk/gtk.h>

int init_gtk(){
   
   GtkWidget *pFenetre;
   gtk_init(&argc, &argv);

   pFenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_windget_show(pFenetre);
   
   gtk_main();

}

int create_zone1(GtkWidget *window, int nb_rows, int nb_columns){
	assert(window != NULL);
    
    GtkImage *empty_disk = gtk_image_new_from_file("bleu.gif");
    GtkImage *red_disk = gtk_image_new_from_file("rouge.gif");
    GtkImage *yellow_disk = gtk_image_new_from_file("jaune.gif");
	GtkWidget *pTable = gtk_table_new(nb_rows, nb_columns, TRUE);
	
	for (int i = 0; i < nb_rows; ++i){
	   for (int j = 0; j < nb_columns; ++j){
          gtk_table_attach(GTK_TABLE(pTable),empty_disk,j,(j+1),i,(i+1),GTK_EXPAND,GTK_EXPAND,0,0);
	   }
	}
}

int create_zone2(GtkWidget *window){
   assert(window != NULL);




}

int create_zone3(GtkWidget *window){
   assert(window != NULL);


}

int modif_gtk(GtkWidget *window, board *boardx){
   assert(window != NULL && boardx != NULL);

   int error_code = 0;

   error_code = modif_zone1(window, boardx);
   if(error_code){
      printf("Error updating the board\n");
      return 1;
   }
   
   error_code = modif_zone3(window,boardx);
      if(error_code){
      printf("Error updating the board\n");
      return 1;
   }

return 0;
}

int modif_zone1(GtkWidget *window, board *boardx){
   assert(window != NULL && boardx != NULL);

	for (int i = 0; i < get_board_nb_rows(boardx); ++i){
	   for (int j = 0; j < get_board_nb_columns(boardx); ++j){

	      if(get_board_disk_value(boardx, i, j) == 0){
          gtk_table_attach(GTK_TABLE(pTable),empty_disk,j,(j+1),i,(i+1),GTK_EXPAND,GTK_EXPAND,0,0);
          }else{
          	if(get_board_disk_value(boardx, i, j) == 1){
               gtk_table_attach(GTK_TABLE(pTable),red_disk,j,(j+1),i,(i+1),GTK_EXPAND,GTK_EXPAND,0,0);
          	}else{
          	   if(get_board_disk_value(boardx, i, j)== 2){
          	   gtk_table_attach(GTK_TABLE(pTable),yellow_disk,j,(j+1),i,(i+1),GTK_EXPAND,GTK_EXPAND,0,0);
          	   }else{
          	   	return (-1)
          	   }
          	}
          }
	   }
	}
return 0;
}

int modif_zone3(GtkWidget *window, board *boardx){


}