#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "command.h"
#include "direction.h"


int char_to_int(char c)
{
    return (c - '0');
}

void clear_stdin()
{
    char c;

    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

char* color_to_code(color_t color)
{
    switch (color) {
        case COLOR_RED:
            return ("\033[31m");
        case COLOR_GREEN:
            return ("\033[32m");
        case COLOR_YELLOW:
            return ("\033[33m");
        case COLOR_BLUE:
            return ("\033[34m");
        case COLOR_PURPLE:
            return ("\033[35m");
        case COLOR_CYAN:
            return ("\033[36m");
        case COLOR_NONE:
        default:
            return ("\033[0m");
    }
}

char* color_to_string(color_t color)
{
    switch (color) {
        case COLOR_RED:
            return ("RED");
        case COLOR_GREEN:
            return ("GREEN");
        case COLOR_YELLOW:
            return ("YELLOW");
        case COLOR_BLUE:
            return ("BLUE");
        case COLOR_PURPLE:
            return ("PURPLE");
        case COLOR_CYAN:
            return ("CYAN");
        case COLOR_NONE:
        default:
            return ("NONE");
    }
}

color_t string_to_color(char* string)
{
    if (strcmp(string, "RED") == 0) {
        return (COLOR_RED);
    }
    else if (strcmp(string, "GREEN") == 0) {
        return (COLOR_GREEN);
    }
    else if (strcmp(string, "YELLOW") == 0) {
        return (COLOR_YELLOW);
    }
    else if (strcmp(string, "BLUE") == 0) {
        return (COLOR_BLUE);
    }
    else if (strcmp(string, "PURPLE") == 0) {
        return (COLOR_PURPLE);
    }
    else if (strcmp(string, "CYAN") == 0) {
        return (COLOR_CYAN);
    }
    else {
        return (COLOR_NONE);
    }
}

command_type_t string_to_command_type(char* string)
{
    if (strcmp(string, "move") == 0) {
        return (COMMAND_MOVE);
    }
    else if (strcmp(string, "cancel") == 0) {
        return (COMMAND_CANCEL);
    }
    else if (strcmp(string, "erase") == 0) {
        return (COMMAND_ERASE);
    }
    else if (strcmp(string, "restart") == 0) {
        return (COMMAND_RESTART);
    }
    else if (strcmp(string, "quit") == 0) {
        return (COMMAND_QUIT);
    }
    else if (strcmp(string, "legend") == 0) {
        return (COMMAND_LEGEND);
    }
    else {
        return (COMMAND_NONE);
    }
}

direction_t string_to_direction(char* string)
{
    if (strcmp(string, "UP") == 0) {
        return (DIRECTION_UP);
    }
    else if (strcmp(string, "DOWN") == 0) {
        return (DIRECTION_DOWN);
    }
    else if (strcmp(string, "LEFT") == 0) {
        return (DIRECTION_LEFT);
    }
    else if (strcmp(string, "RIGHT") == 0) {
        return (DIRECTION_RIGHT);
    }
    else {
        return (DIRECTION_NONE);
    }
}
