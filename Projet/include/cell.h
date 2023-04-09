#ifndef CELL_H
    #define CELL_H

    #include <stdbool.h>

    #include "color.h"

    typedef enum {
        CELL_EMPTY,
        CELL_ENTRYPOINT,
        CELL_NUMBER,
    } cell_type_t;

    typedef struct {
        color_t     color;
        bool        is_assigned;
        cell_type_t type;
        int         value;
    } cell_t;

    cell_t* create_cell(color_t color, cell_type_t type, int value);
    void    free_cell(cell_t* cell);
    void    print_cell(cell_t* cell);

#endif // CELL_H
