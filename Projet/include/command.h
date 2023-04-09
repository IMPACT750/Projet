#ifndef COMMAND_H
    #define COMMAND_H

    #include "color.h"
    #include "direction.h"

    typedef enum {
        COMMAND_NONE,
        COMMAND_MOVE,
        COMMAND_CANCEL,
        COMMAND_ERASE,
        COMMAND_RESTART,
        COMMAND_QUIT,
        COMMAND_LEGEND,
    } command_type_t;

    typedef struct {
        color_t         color;
        direction_t     direction;
        command_type_t  type;
    } command_t;

    command_t*  create_command(color_t color, direction_t direction, command_type_t type);
    void        free_command(command_t* command);
    void        print_command(command_t* command);

#endif // COMMAND_H
