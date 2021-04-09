#include "header.h"
#include <stdio.h>

void exception_print(int position)
{
    for (int j = 0; j < position; j++)
    {
        printf(" ");
    }
    printf("^\n");
    printf("Error at column %d. Expected number.\n", position);
}