#include "header.h"

bool exception_print(bool correct_check, int position)
{
    for (int j = 0; j < position; j++)
    {
        printf(" ");
    }
    printf("^\n");
    printf("Error at column %d. Expected number.\n", position);
    return correct_check = false;
}