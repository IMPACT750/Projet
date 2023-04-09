#ifndef COLOR_H
#define COLOR_H

    typedef enum {
        COLOR_NONE      = 0,
        COLOR_RED       = 1,
        COLOR_GREEN     = 2,
        COLOR_YELLOW    = 3,
        COLOR_BLUE      = 4,
        COLOR_PURPLE    = 5,
        COLOR_CYAN      = 6,
    } color_t;

    color_t get_next_color();
    void    print_int_in_color(color_t color, int value);
    void    print_string_in_color(color_t color, char* string);
    void    reset_color_index();

#endif // COLOR_H
