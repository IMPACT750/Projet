#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "cell.h"
#include "color.h"
#include "utils.h"
char*       generate_file_name(int level);
int         read_dimension(FILE* stream, char* dimension);
cell_t***   read_content(FILE* stream, board_t* board);


board_t* create_board(int level)
{
    board_t*    board;
    char*       filename;
    FILE*       stream;

    board = malloc(sizeof(board_t));
    filename = generate_file_name(level);
    if ((stream = fopen(filename, "r")) == NULL) {
        printf("[ERROR] Cannot open file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }
    board->level = level;
    board->number_of_entrypoints = 0;
    board->height = read_dimension(stream, "height");
    board->width = read_dimension(stream, "width");
    board->content = read_content(stream, board);

    free(filename);
    fclose(stream);

    return (board);
}

void free_board(board_t* board)
{
    for (int y = 0; y < board->height; y += 1) {
        for (int x = 0; x < board->width; x += 1) {
            free_cell(board->content[y][x]);
        }
        free(board->content[y]);
    }
    free(board->content);
    free(board);
}

void print_board(board_t* board)
{
    // Print the top border.
    printf("┌");
    for (int x = 0; x < board->width; x += 1) {
        printf("─");
        if (x != board->width - 1) {
            printf("┬");
        }
    }
    printf("┐\n");

    // Print the content.
    for (int y = 0; y < board->height; y += 1) {
        printf("│");
        for (int x = 0; x < board->width; x += 1) {
            print_cell(board->content[y][x]);
            if (x != board->width - 1) {
                printf("│");
            }
        }
        printf("│\n");
        // Print the middle border.
        if (y != board->height - 1) {
            printf("├");
            for (int x = 0; x < board->width; x += 1) {
                printf("─");
                if (x != board->width - 1) {
                    printf("┼");
                }
            }
            printf("┤\n");
        }
    }

    // Print the bottom border.
    printf("└");
    for (int x = 0; x < board->width; x += 1) {
        printf("─");
        if (x != board->width - 1) {
            printf("┴");
        }
    }
    printf("┘\n");
}

// Utility functions -----------------------------------------------------------
char* generate_file_name(int level)
{
    int     count; // Count the number of digits in the level number.
    char*   buffer;
    int     number;

    count = 0;
    number = level;
    while (number != 0) {
        number /= 10;
        count += 1;
    }
    buffer = malloc(sizeof(char) * (count + 11));
    sprintf(buffer, "level/%d.txt", level);

    return (buffer);
}

cell_t*** read_content(FILE* stream, board_t* board)
{
    color_t     color;
    cell_t***   content;
    char*       file_line;
    cell_type_t type;
    int         value;

    content = malloc(sizeof(cell_t**) * board->height);
    for (int y = 0; y < board->height; y += 1) {
        file_line = malloc(sizeof(char) * (board->width + 2));
        fgets(file_line, board->width + 2, stream);
        file_line[board->width + 1] = '\0'; // delete the '\n' character.
        content[y] = malloc(sizeof(cell_t*) * board->width);
        for (int x = 0; x < board->width; x += 1) {
            if (file_line[x] == '.') {
                color = COLOR_NONE;
                type = CELL_EMPTY;
                value = 0;
            }
            else if (file_line[x] == 'X') {
                color = get_next_color();
                type = CELL_ENTRYPOINT; 
                value = 0;
                board->number_of_entrypoints += 1;
            }
            else {
                if (file_line[x] <= '0' || '9' <= file_line[x]) {
                    printf("[ERROR] Invalid character '%c' in input file, expected a digit between 0 and 9.\n", file_line[x]);
                    exit(EXIT_FAILURE);
                }
                color = COLOR_NONE;
                type = CELL_NUMBER;
                value = char_to_int(file_line[x]);
            }
            content[y][x] = create_cell(color, type, value);
        }
        free(file_line);
    }

    return (content);
}

int read_dimension(FILE* stream, char* dimension)
{
    char* format;
    int   value;

    format = malloc(sizeof(char) * (strlen(dimension) + 5));
    sprintf(format, "%s=%%d\n", dimension);
    fscanf(stream, format, &value);

    free(format);

    return (value);
}
