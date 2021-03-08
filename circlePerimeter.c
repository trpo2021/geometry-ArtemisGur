#include "header.h"
#define PI 3.14

double find_circle_perimeter(CircleTokens circle)
{
    double perimeter = 2 * PI * circle.radius;
    return perimeter;
}