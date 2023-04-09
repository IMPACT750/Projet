#ifndef CHAIN_H
#define CHAIN_H

    #include "board.h"
    #include "cell.h"

    typedef struct chain {
        cell_t*         content;
        struct chain*   previous;
        int             x;
        int             y;
    } chain_t;

    chain_t*    create_chain(cell_t* content, int y, int x);
    chain_t**   create_chains(board_t* board);
    void        free_chain(chain_t* chain);
    void        free_chains(chain_t** chain, int number_of_entrypoints);
    void        print_chain(chain_t* chain);
    void        print_chains(chain_t** chain, int number_of_entrypoints);

#endif // CHAIN_H
