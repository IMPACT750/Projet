#ifndef BOARD_H
    #define BOARD_H

    #include "cell.h"

    typedef struct {
        cell_t***   content;
        int         height;
        int         level;
        int         number_of_entrypoints;
        int         width;
    } board_t;

    board_t*    create_board(int level);
    void        free_board(board_t* board);
    void        print_board(board_t* board);

#endif // BOARD_H
