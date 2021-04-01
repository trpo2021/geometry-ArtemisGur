#include "header.h"
#include <math.h>
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
