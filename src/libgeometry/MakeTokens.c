#include "header.h"

CircleTokens make_circle_tokens(int string_length, char* array, CircleTokens circle_struct)
{
    for (int i = 0; i < string_length; i++)
    {
        if (array[i] == '(')
        {
            circle_struct.op_bracket = i;
        }
        if (array[i] == ')')
        {
            circle_struct.cl_bracket = i;
        }
        if (array[i] == ',')
        {
            circle_struct.comma = i;
        }
        if (array[i] == ' ' && array[i - 1] == ',')
        {
            continue;
        }
        else if (array[i] == ' ')
        {
            circle_struct.space = i;
        }
    }
    return circle_struct;
}