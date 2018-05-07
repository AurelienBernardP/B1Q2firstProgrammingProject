#ifndef __TOP10__
#define __TOP10__

struct player_t;
/**
 * definition of player opaque structure.
 *
 */
typedef struct player_t player;

/**
 * *get_player_name
 *
 * Gets the name of a player from a player opaque structure.
 *
 * @param: *user, a pointer to a player structure.  
 * 
 * @pre: *user point to a valid and initialized player structure.
 *
 * @post: the name string is returned.
 *
 * @return:
 *     pointer to the char array.
 *
 */
char *get_player_name(player *user);

/**
 * *get_path
 *
 * Gets the path of the file where top players information is stored from a player opaque structure.
 *
 * @param: *user, a pointer to a player structure.  
 * 
 * @pre: *user point to a valid and initialized player structure.
 *
 * @post: the path string is returned.
 *
 * @return:
 *     pointer to the char array.
 *
 */
char *get_path(player *user);

/**
 * *init_player
 *
 * Initialaise a player opaque structure.
 *
 * @param: *name, a pointer to a characters array.  
 * @param: *path, a pointer to a characters array.  
 * 
 * @pre: *name point to a valid and initialized array.
 * @pre: *path point to a valid and initialized array.
 *
 * @post: A player structure is initialized 
 *
 * @return:
 *     pointer to initialized structure on Success
 *     NULL pointer on error.
 *
 */
player *init_player(char *name, char *path);

/**
 * change_player_score
 *
 * Gets the score of a player stored in a player opaque structure.
 *
 * @param: *user, a pointer to a player structure.
 * @param: new_score, the new score of the player.
 * 
 * @pre: *user point to a valid and initialized player structure.
 *
 * @post: the score in the structure is modified.
 *
 * @return:
 *     void.
 *
 */
void change_player_score(player *user, int new_score);

/**
 * top10_file_gestion
 *
 * updates the content of the top 10 players file.
 *
 * @param: *current_player, a pointer to a player structure.
 * @param: *path, a pointer to a characters array.  
 * 
 * @pre: *current_player point to a valid and initialized player structure.
 * @pre: *path point to a valid and initialized array.
 *
 * @post: the top10 file has been updated
 *
 * @return:
 *     void.
 *
 */
void top10_file_gestion(char *path, player *current_player);

/**
 * destroy_players_array
 *
 * frees the allocated memory space used for an array of players
 *
 * @param: *array, a pointer to a player structure array.
 * 
 * @pre: *array point to a valid and initialized array of player.
 *
 * @post: memory is freed.
 *
 * @return:
 *     void.
 *
 */
void destroy_players_array(player *array);

#endif
