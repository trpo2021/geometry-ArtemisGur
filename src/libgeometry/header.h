#pragma once
#include <stdbool.h>

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

typedef struct
{
    double perimeter;
    double area;
    int coll[100];
} ShapeParameters;

void exception_print(int position);
int fill_circle_coord(CircleTokens* coords, char* input_data);
CircleTokens make_circle_tokens(int string_length, char* array, CircleTokens circle_struct);
void print_figure(CircleTokens* shape, ShapeParameters* param);
double find_circle_perimeter(CircleTokens circle);
double find_circle_area(CircleTokens circle);
double distance(CircleTokens* shape_1, CircleTokens shape_2);
double radius_check(CircleTokens* shape_1, CircleTokens shape_2);
void collision(CircleTokens* shapes_array, CircleTokens* shape, int count, ShapeParameters* param);