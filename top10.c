#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "top10.h"

struct player_t{
   char name[21];
   unsigned int score;
   char top10_file[21];
};

char *get_player_name(player *user){
   assert(user != NULL);
   return user->name;
}

void change_player_score(player *user, int new_score){
   assert(user != NULL);
   
   user->score = new_score;
   return; 
}

char *get_path(player *user){
   assert(user != NULL);

   return user->top10_file;
}

player *init_player(char* name, char* path){
   assert(name != NULL);

   player *new_player = malloc(sizeof(player));
   if (new_player == NULL) {
      printf("error allocating memory for new player data\n");
      return NULL;
   }
   strcpy(new_player->name, name);
   if(new_player->name == NULL){
     printf("error coping players name\n" );
     return NULL;
   }
   strcpy(new_player->top10_file, path);
   if(new_player->top10_file == NULL){
     printf("error coping path name\n" );
     return NULL;
   }
   new_player->score = 0;
   return new_player;
}

static player *init_top_array(){
   player *array = malloc(11 * sizeof(player));
   if (array == NULL) {
      printf("error allocating memory space for top players array\n");
      return NULL;
   }
   return array;
}

void destroy_players_array(player *array){
   assert(array != NULL);
   free(array);
   return;
}

static int place_players_in_array(FILE *fp,player *top_array, player *current_player ){
   assert(fp != NULL);
   int nb_players = 0;
   while(!feof(fp) && nb_players < 10){
      int i= 0;
      char full_line[30] = {'\0'};
      fgets(full_line,20 , fp);
      while(full_line[i] != '.' && full_line[i] != '\n' && i<30){
         if (i > 26){
           printf("top file content has a mistake\n");
           strcpy(top_array[nb_players].name,current_player->name);
           top_array[nb_players].score = current_player->score;
           nb_players++;
           return nb_players;
         }
         i++;
      }
      i++;
      char name[21] = {'\0'};
      int j = 0;
      while(full_line[i] != ' ' && j< 20 ){
         name[j] = full_line[i];
         i++;
         j++;
      }
      strcpy(top_array[nb_players].name, name);// put name in to structure array

      i++;
      while(full_line[i] - '0' < 0 && full_line[i] - '0' > 9){
        i++;
      }
      int player_score = 0;
      while(i<30 && full_line[i] != '\n' && full_line[i] != '\0' && full_line[i] != ' '){
         player_score*=10;
         player_score += (full_line[i] - '0');
         if((full_line[i] - '0') > 9 && full_line[i] - '0' < 0){
            printf("error computing nb plays from file\n");
            return (nb_players);
         }
         i++;
         
       }

      top_array[nb_players].score = player_score;
      nb_players++;
   }
   strcpy(top_array[nb_players].name,current_player->name);
   top_array[nb_players].score = current_player->score;
   nb_players++;
   return nb_players;
}


static int sort_array_best_to_worse(player *top_array, int nb_players){
   assert(top_array != NULL);
   int i= 0;
   for(i=0; i<=nb_players; i++){
      for(int j = i; j > 0 && top_array[j-1].score > top_array[j].score; j--){
         player *tmp_player = malloc(sizeof(player));
         if (tmp_player == NULL) {
            printf("error sorting top players list\n");
            return (-1);
         }
         *tmp_player = top_array[j];
         top_array[j] = top_array[j-1];
         top_array[j-1] = *tmp_player;
         free(tmp_player);
      }
    }
   return 0;
}

void top10_file_gestion(char * path, player *current_player){
   assert(path != NULL);

   player *top_players_array = init_top_array();
   int error_code = 0;
   int nb_players = 0;

   FILE *fp = fopen(path, "r");
   if (fp == NULL) {
     top_players_array = NULL;
   }else{
       nb_players = place_players_in_array(fp, top_players_array, current_player);
       if (nb_players <= 0) {
       top_players_array = NULL;
       }else{
         error_code = sort_array_best_to_worse(top_players_array, nb_players);
         if (error_code){
          fclose(fp);
          free(top_players_array);
          current_player->score = 0;
           return;
         }
       }
   }
   fclose(fp);
   fp = fopen(path, "w");
   if(top_players_array == NULL){
     fprintf(fp, "1.%s %u \n",current_player->name,current_player->score );
   }else{
      for (int i = 0; i < 10 && i< nb_players; i++){

         fprintf(fp, "%d.%s %u \n",(i+1) ,top_players_array[i].name, top_players_array[i].score );
      }
   }
  current_player->score = 0;
  free(top_players_array);
  fclose(fp);

  return;
}
