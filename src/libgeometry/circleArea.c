#include "header.h"
#define PI 3.14

double find_circle_area(CircleTokens circle)
{
    double area = PI * circle.radius * circle.radius;
    return area;
}