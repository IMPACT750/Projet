#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "color.h"


cell_t* create_cell(color_t color, cell_type_t type, int value)
{
    cell_t* cell;

    cell = malloc(sizeof(cell_t));
    cell->color = color;
    cell->is_assigned = (type == CELL_NUMBER) ? false : true;
    cell->type = type;
    cell->value = value;

    return (cell);
}

void free_cell(cell_t* cell)
{
    free(cell);
}

void print_cell(cell_t* cell)
{
    switch (cell->type) {
        case CELL_EMPTY:
            printf(" ");
            break;
        case CELL_ENTRYPOINT:
            print_string_in_color(cell->color, "X");
            break;
        case CELL_NUMBER:
            print_int_in_color(cell->color, cell->value);
            break;
    }
}
