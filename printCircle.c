#include "header.h"

void print_figure(bool correct_check, char *figure, CircleTokens circle_struct, double perimeter, double area)
{
    if (correct_check)
    {
        printf("\n%s(%.2lf %.2lf, %.2lf)\n", figure, circle_struct.coordX, circle_struct.coordY, circle_struct.radius);
        printf("Perimeter = %.4lf\n", perimeter);
        printf("Area = %.4lf\n", area);
    }
}
