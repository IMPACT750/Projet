#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "color.h"
#include "game_engine.h"


int main()
{
    board_t*    board;
    bool        continue_to_play;
    int         level;

    level = 1;
    print_legend();
    do {
        printf("===================== LEVEL %d =====================\n", level);

        board = create_board(level);
        continue_to_play = game_engine(board);

        level += 1;
        free_board(board);
        reset_color_index();
    } while (continue_to_play == true);

    return (EXIT_SUCCESS);
}
