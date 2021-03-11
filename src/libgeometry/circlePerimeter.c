#include "header.h"
#define _USE_MATH_DEFINES
#include <math.h>

double find_circle_perimeter(CircleTokens circle)
{
    return M_PI * 2 * circle.radius;
}