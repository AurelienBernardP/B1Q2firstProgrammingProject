typedef struct control_t{
    board_vue bv;
    board_model bm;
    GtkWidget *buttons;
}board_controler;

board_controler *create_board_controler(board_model *Bm, board_vue *Bv);

static void buttons_sesitivity_update(board_controler *board_c, board_model *boardx);

void move_made(GtkWidget *button, gpointer data);

unsigned short find_column_clicked(board_controler *controler,GtkWidget *button);

