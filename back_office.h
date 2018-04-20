struct board_t;

typedef board_t board;

static void destroy_board(board *boardx);

board *init_board(char rows, char columns);

int add_pawn(board *boardx, unsigned int player, unsigned short column);

int check_win(board *boardx);

static int horizontal_check_win(board *boardx);

static int vertical_check_win(board *boardx);

static int diagonal1_check_win(board *boardx);

static int diagonal1_check_win(board *boardx);