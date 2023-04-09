#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "cell.h"
#include "chain.h"
#include "color.h"
#include "utils.h"


chain_t* create_chain(cell_t* content, int y, int x)
{
    chain_t* chain;

    chain = malloc(sizeof(chain_t));
    chain->content = content;
    chain->previous = NULL;
    chain->y = y;
    chain->x = x;

    return (chain);
}

chain_t** create_chains(board_t* board)
{
    chain_t**   chains;
    int         index;

    chains = malloc(sizeof(chain_t*) * board->number_of_entrypoints);
    index = 0;
    for (int y = 0; y < board->height; y += 1) {
        for (int x = 0; x < board->width; x += 1) {
            if (board->content[y][x]->type == CELL_ENTRYPOINT) {
                chains[index] = create_chain(board->content[y][x], y, x);
                index += 1;
            }
        }
    }

    return (chains);
}

void free_chain(chain_t* chain)
{
    chain_t*    current;
    chain_t*    previous;

    current = chain;
    while (current != NULL) {
        previous = current->previous;
        free(current);
        current = previous;
    }
}

void free_chains(chain_t** chains, int number_of_entrypoints)
{
    for (int index = 0; index < number_of_entrypoints; index += 1) {
        free_chain(chains[index]);
    }
    free(chains);
}

void print_chain(chain_t* chain)
{
    chain_t* current;

    current = chain;
    while (current != NULL) {
        printf("(%d, %d) => ", current->y, current->x);
        current = current->previous;
    }
    printf("END\n");
}

void print_chains(chain_t** chains, int number_of_entrypoints)
{
    color_t color;
    char*   color_name;

    printf("Chains :\n");
    for (int index = 0; index < number_of_entrypoints; index += 1) {
        color = chains[index]->content->color;
        color_name = color_to_string(color);

        printf("  - ");
        print_string_in_color(color, color_name);
        printf(" : ");
        print_chain(chains[index]);
    }
}
