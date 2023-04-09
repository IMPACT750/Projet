#ifndef UTILS_H
    #define UTILS_H

    #include "color.h"
    #include "command.h"
    #include "direction.h"

    int             char_to_int(char c);
    void            clear_stdin();
    char*           color_to_code(color_t color);
    char*           color_to_string(color_t color);
    color_t         string_to_color(char* string);
    command_type_t  string_to_command_type(char* string);
    direction_t     string_to_direction(char* string);

#endif // UTILS_H
