#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int op_bracket;
    int cl_bracket;
    int space;
    int comma;
    double coord_x;
    double coord_y;
    double radius;
} CircleTokens;

bool exception_print(bool correct_check, int position);
bool fill_circle_coord(CircleTokens* coords, char* input_data);
CircleTokens make_circle_tokens(int string_length, char* array, CircleTokens circle_struct);
void print_figure(bool correct_check, char* figure, CircleTokens circle_struct, double perimeter,
                  double area);
double find_circle_perimeter(CircleTokens circle);
double find_circle_area(CircleTokens circle);