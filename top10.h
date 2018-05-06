#ifndef __TOP10__
#define __TOP10__

struct player_t;

typedef struct player_t player;

char *get_player_name(player *user);

char *get_path(player *user);

player *init_player(char *name, char *path);

char *get_player_name(player *user);

void change_player_score(player *user, int new_score);

void top10_file_gestion(char *path, player *current_player);

void destroy_players_array(player *array);

#endif
