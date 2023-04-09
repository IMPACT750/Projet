#include <stdio.h>

#include "color.h"
#include "utils.h"


int COLOR_INDEX = 0;

color_t get_next_color()
{
    color_t color;

    COLOR_INDEX += 1;
    color = (color_t)COLOR_INDEX;
    if (color >= COLOR_CYAN) {
        printf("[WARNING] Not enough color (%d).\n", color);
    }

    return (color);
}

void print_int_in_color(color_t color, int value)
{
    char*   color_code;
    char*   none_code;

    color_code = color_to_code(color);
    none_code = color_to_code(COLOR_NONE);
    printf("%s%d%s", color_code, value, none_code);
}

void print_string_in_color(color_t color, char* string)
{
    char*   color_code;
    char*   none_code;

    color_code = color_to_code(color);
    none_code = color_to_code(COLOR_NONE);
    printf("%s%s%s", color_code, string, none_code);
}

void reset_color_index()
{
    COLOR_INDEX = 0;
}
