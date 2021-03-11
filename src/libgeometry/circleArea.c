#include "header.h"
#define _USE_MATH_DEFINES
#include <math.h>

//#define PI 3.14

double find_circle_area(CircleTokens circle)
{
    return M_PI * circle.radius * circle.radius;
}