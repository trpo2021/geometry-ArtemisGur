#include "header.h"
#include <stdio.h>

void print_figure(CircleTokens* shape, ShapeParameters* param)
{
    printf("Circle(%.2lf %.2lf, %.2lf)\n", shape->coord_x, shape->coord_y, shape->radius);
    printf("      Perimeter = %.4lf\n", param->perimeter);
    printf("      Area = %.4lf\n", param->area);
}
