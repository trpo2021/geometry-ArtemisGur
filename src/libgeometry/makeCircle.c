#include "header.h"
#include <stdlib.h>

int fill_circle_coord(CircleTokens* coords, char* input_data)
{
    for (int i = coords->op_bracket + 1; i < coords->space; i++)
    {
        char* tmp_double = &input_data[i];
        char* tmp;
        double temp = strtod(tmp_double, &tmp);
        if (*tmp == input_data[coords->space])
        {
            coords->coord_x = temp;
            break;
        }
        else
            return i; // exception_print(correct_check, i);
    }

    for (int i = coords->space + 1; i < coords->comma; i++)
    {
        char* tmp_double = &input_data[i];
        char* tmp;
        double temp = strtod(tmp_double, &tmp);
        if (*tmp == input_data[coords->comma])
        {
            coords->coord_y = temp;
            break;
        }
        else
            return i; // exception_print(correct_check, i);
    }

    for (int i = coords->comma + 1; i < coords->cl_bracket; i++)
    {
        char* tmp_double = &input_data[i];
        char* tmp;
        double temp = strtod(tmp_double, &tmp);
        if (*tmp == input_data[coords->cl_bracket])
        {
            coords->radius = temp;
            break;
        }
        else
        {
            return i; // exception_print(correct_check, i);
        }
    }
    return -1;
}