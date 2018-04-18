#include "IA.c"
#include "back_office.h"

void IA_play(board *boardx);

static int random_play(board *boardx);

static int try_to_win(board *boardx);

static int try_block_win(board *boardx);

static int try_to_make_3(board *boardx);

static int try_block_3(board *boardx);

static int horizontal_try_to_do_x(board *boardx, int nb_to_do);

static int vertical_try_to_do_x(board *boardx, int nb_to_do);

static int diagonal1_try_x_in_row(board *boardx, int nb_to_do);

static int diagonal2_try_x_in_row(board *boardx, int nb_to_do);

static int try_block_horizontal_x_in_row(board *boardx,int nb_to_block);

static int try_block_vertical_x_in_row(board *boardx, int nb_to_block);

static int try_block_diagonal1_x_in_row(board *boardx, int nb_to_block);

static int try_block_diagonal2_x_in_row(board *boardx, int nb_to_block);