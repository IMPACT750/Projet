#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "command.h"
#include "direction.h"


command_t*  create_command(color_t color, direction_t direction, command_type_t type)
{
    command_t* command;

    command = malloc(sizeof(command_t));
    command->color = color;
    command->direction = direction;
    command->type = type;

    return (command);
}

void free_command(command_t* command)
{
    free(command);
}

void print_command(command_t* command)
{
    printf("command<%d,%d,%d>\n", command->color, command->direction, command->type);
}
