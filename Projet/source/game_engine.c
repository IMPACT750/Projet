#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "chain.h"
#include "color.h"
#include "command.h"
#include "direction.h"
#include "game_engine.h"
#include "utils.h"
command_t*  ask_user_command();
void        cancel_move(board_t* board, chain_t** chains, color_t color);
void        erase_chain(board_t* board, chain_t** chains, color_t color);
bool        execute_command(board_t* board, chain_t** chains, command_t* command);
bool        game_is_over(board_t* board);
void        move_head_chain(board_t* board, chain_t** chains, color_t color, direction_t direction);
void        restart_level(board_t* board, chain_t** chains);


bool game_engine(board_t* board)
{
    chain_t**   chains;
    command_t*  command;
    bool        continue_to_play;

    chains = create_chains(board);
    continue_to_play = true;
    while (continue_to_play == true && game_is_over(board) == false) {
        print_board(board);
        command = ask_user_command();
        continue_to_play = execute_command(board, chains, command);

        free_command(command);
    }
    print_board(board);

    free_chains(chains, board->number_of_entrypoints);

    return (continue_to_play);
}

// Utility functions -----------------------------------------------------------
command_t*  ask_user_command()
{
    color_t         color;
    char            buffer[32];
    direction_t     direction;
    command_type_t  type;

    color = COLOR_NONE;
    direction = DIRECTION_NONE;
    printf("> ");
    if (scanf("%s", buffer) == EOF) {
        return (create_command(color, direction, COMMAND_QUIT));
    }
    type = string_to_command_type(buffer);
    if (type == COMMAND_MOVE || type == COMMAND_CANCEL || type == COMMAND_ERASE) {
        scanf("%s", buffer);
        color = string_to_color(buffer);
        if (type == COMMAND_MOVE) {
            scanf("%s", buffer);
            direction = string_to_direction(buffer);
        }
    }
    clear_stdin();

    return (create_command(color, direction, type));
}

bool execute_command(board_t* board, chain_t** chains, command_t* command)
{
    switch (command->type) {
        case COMMAND_MOVE:
            move_head_chain(board, chains, command->color, command->direction);
            break;
        case COMMAND_CANCEL:
            cancel_move(board, chains, command->color);
            break;
        case COMMAND_ERASE:
            erase_chain(board, chains, command->color);
            break;
        case COMMAND_RESTART:
            restart_level(board, chains);
            break;
        case COMMAND_QUIT:
            return (false);
        case COMMAND_LEGEND:
            print_legend();
            break;
        case COMMAND_NONE:
        default:
            printf("< The command you entered was not understood. Use the \"legend\" command for more details.\n");
            break;
    }

    return (true);
}

bool game_is_over(board_t* board)
{
    for (int y = 0; y < board->height; y += 1) {
        for (int x = 0; x < board->width; x += 1) {
            if (board->content[y][x]->is_assigned == false) {
                return (false);
            }
        }
    }

    return (true);
}

bool update_position(int* y, int* x, direction_t direction)
{
    switch (direction) {
        case DIRECTION_UP:
            (*y) -= 1;
            break;
        case DIRECTION_DOWN:
            (*y) += 1;
            break;
        case DIRECTION_LEFT:
            (*x) -= 1;
            break;
        case DIRECTION_RIGHT:
            (*x) += 1;
            break;
        case DIRECTION_NONE:
        default:
            printf("< The <DIRECTION> you entered was not understood. Use the \"legend\" command for more details.\n");
            return (false);
    }
    return (true);
}

// Command functions -----------------------------------------------------------
void cancel_move(board_t* board, chain_t** chains, color_t color)
{
    chain_t*    old_head;

    if (color == COLOR_NONE || (int)color > board->number_of_entrypoints) {
        printf("< The <COLOR> you entered does not exist on the board.\n");
        return;
    }
    if (chains[color - 1]->previous == NULL) {
        printf("< There is no move to cancel.\n");
        return;
    }
    old_head = chains[color - 1];
    chains[color - 1] = old_head->previous;
    old_head->content->is_assigned = false;
    old_head->content->color = COLOR_NONE;

    free(old_head);
}

void erase_chain(board_t* board, chain_t** chains, color_t color)
{
    if (color == COLOR_NONE || (int)color > board->number_of_entrypoints) {
        printf("< The <COLOR> you entered does not exist on the board.\n");
        return;
    }
    while (chains[color - 1]->content->type != CELL_ENTRYPOINT) {
        cancel_move(board, chains, color);
    }
}

void move_head_chain(board_t* board, chain_t** chains, color_t color, direction_t direction)
{
    chain_t*    new_head;
    int         new_x;
    int         new_y;

    if (color == COLOR_NONE || (int)color > board->number_of_entrypoints) {
        printf("< The <COLOR> you entered does not exist on the board.\n");
        return;
    }
    new_x = chains[color - 1]->x;
    new_y = chains[color - 1]->y;
    if (update_position(&new_y, &new_x, direction) == false) {
        return;
    }

    // Checking all impossible moves.
    // - Impossible move : out of the board.
    if (new_x < 0 || new_x >= board->width || new_y < 0 || new_y >= board->height) {
        printf("< Please stay inside the board.\n");
        return;
    }
    // - Impossible move : overlap on a cell already assigned.
    if (board->content[new_y][new_x]->is_assigned == true) {
        if (board->content[new_y][new_x]->type == CELL_NUMBER || board->content[new_y][new_x]->type == CELL_ENTRYPOINT) {
            printf("< Please don't overlap on a cell already assigned.\n");
        }
        else if (board->content[new_y][new_x]->type == CELL_EMPTY) {
            printf("< Please don't overlap with an empty cell.\n");
        }
        else {
            printf("[ERROR] Internal error : cell not consistent.\n");
        }
        return;
    }
    // - Impossible move : overlap on a cell with a smaller value.
    if (chains[color - 1]->content->value > board->content[new_y][new_x]->value) {
        printf("< Please don't overlap with a smaller cell.\n");
        return;
    }

    // Update the head of the chain.
    new_head = create_chain(board->content[new_y][new_x], new_y, new_x);
    new_head->content->is_assigned = true;
    new_head->content->color = chains[color - 1]->content->color;
    new_head->previous = chains[color - 1];
    chains[color - 1] = new_head;
}

void restart_level(board_t* board, chain_t** chains)
{
    for (int index = 0; index < board->number_of_entrypoints; index += 1) {
        erase_chain(board, chains, (color_t)(index + 1));
    }
}

void print_legend()
{
    printf("COLOR       = {\"RED\", \"GREEN\", \"YELLOW\", \"BLUE\", \"PURPLE\", \"CYAN\"}\n");
    printf("DIRECTION   = {\"UP\", \"DOWN\", \"LEFT\", \"RIGHT\"}\n");
    printf("Commands :\n");
    printf("  - move <COLOR> <DIRECTION>    : Allows you to move the head of a chain.\n");
    printf("  - cancel <COLOR>              : Cancel the previous move.\n");
    printf("  - erase <COLOR>               : Erase a chain.\n");
    printf("  - restart                     : Restart the level.\n");
    printf("  - quit                        : Quit the game.\n");
    printf("  - legend                      : Display this legend.\n");
}
