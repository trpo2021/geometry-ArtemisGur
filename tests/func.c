#include "header.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

//#define PI 3.14

double find_circle_area(CircleTokens circle)
{
    return M_PI * circle.radius * circle.radius;
}

double find_circle_perimeter(CircleTokens circle)
{
    return M_PI * 2 * circle.radius;
}

#include <stdlib.h>

double distance(CircleTokens* shape_1, CircleTokens shape_2)
{
    double tmp_x = fabs(shape_1->coord_x - shape_2.coord_x);
    double tmp_y = fabs(shape_1->coord_y - shape_2.coord_y);
    return sqrt(tmp_x * tmp_x + tmp_y * tmp_y);
}

void collision(CircleTokens* shapes_array, CircleTokens* shape, int count, ShapeParameters* param)
{
    param->coll[100] = -1;
    for (int i = 0; i < count; i++)
    {
        double smaller_rad = shape->radius;
        double larger_rad = shapes_array[i].radius;

        double dist = distance(shape, shapes_array[i]);

        if ((smaller_rad + larger_rad) * (smaller_rad + larger_rad) >= dist &&
            dist + smaller_rad > larger_rad && dist + larger_rad > smaller_rad)
        {
            param->coll[i] = 1;
        }
    }
}

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

bool fill_circle_coord(CircleTokens* coords, char* input_data)
{
    bool correct_check;
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
            correct_check = exception_print(correct_check, i);
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
            correct_check = exception_print(correct_check, i);
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
            correct_check = exception_print(correct_check, i);
        }
    }
    return correct_check;
}

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

void print_figure(CircleTokens* shape, ShapeParameters* param)
{
    printf("Circle(%.2lf %.2lf, %.2lf)\n", shape->coord_x, shape->coord_y, shape->radius);
    printf("      Perimeter = %.4lf\n", param->perimeter);
    printf("      Area = %.4lf\n", param->area);
}
