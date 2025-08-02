#include <Arduino.h>
#include <cstdlib>
#include "str_ops.h"


bool str_to_int(const char *str, int& i)
{
    char *str_end;
    int new_i = strtol(str, &str_end, 0);
    if (*str_end != '\0')
        return false; // i not changed
    i = new_i;
    return true;
}
