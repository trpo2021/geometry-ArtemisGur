#include "ctest.h"
#include "libgeometry/header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTEST(equal, test)
{
    int a = 5, b = 2;
    ASSERT_EQUAL(7, a + b);
}

CTEST(area_suite, test_1)
{
    CircleTokens circle;
    circle.radius = 4;
    double rad = find_circle_area(circle);
    ASSERT_DBL_NEAR_TOL(50.24, rad, 0.2);
}

CTEST(perimeter_suite, test_2)
{
    CircleTokens circle;
    circle.radius = 3.2;
    double perim = find_circle_perimeter(circle);
    ASSERT_DBL_NEAR_TOL(20.096, perim, 0.2);
}

CTEST(distance_suite, test_1)
{
    CircleTokens circle_1;
    circle_1.coord_x = 1;
    circle_1.coord_y = 2;
    CircleTokens circle_2;
    circle_2.coord_x = 3.5;
    circle_2.coord_y = 4.1;

    double real_dist = distance(&circle_1, circle_2);
    ASSERT_DBL_NEAR_TOL(3.26, real_dist, 0.5);
}

CTEST(distance_suite, test_2)
{
    CircleTokens circle_1;
    circle_1.coord_x = 4.2;
    circle_1.coord_y = 2.6;
    CircleTokens circle_2;
    circle_2.coord_x = 6.4;
    circle_2.coord_y = 1.3;

    double real_dist = distance(&circle_1, circle_2);
    ASSERT_DBL_NEAR_TOL(2.553, real_dist, 0.5);
}

CTEST(figure_suite, test_1)
{
    char input[] = "circle(a 1, 2)";
    int data_length = strlen(input);
    CircleTokens circle_struct;
    circle_struct = make_circle_tokens(data_length, input, circle_struct);
    int i = fill_circle_coord(&circle_struct, input);
    ASSERT_EQUAL(7, i);
}

CTEST(figure_suite, test_2)
{
    char input[] = "circle(1 n, 2)";
    int data_length = strlen(input);
    CircleTokens circle_struct;
    circle_struct = make_circle_tokens(data_length, input, circle_struct);
    int i = fill_circle_coord(&circle_struct, input);
    ASSERT_EQUAL(9, i);
}

CTEST(figure_suite, test_3)
{
    char input[] = "circle(- 1, 2)";
    int data_length = strlen(input);
    CircleTokens circle_struct;
    circle_struct = make_circle_tokens(data_length, input, circle_struct);
    int i = fill_circle_coord(&circle_struct, input);
    ASSERT_EQUAL(7, i);
}

CTEST(figure_suite, test_5)
{
    char input[] = "circle(2 12, 2)";
    int data_length = strlen(input);
    CircleTokens circle_struct;
    circle_struct = make_circle_tokens(data_length, input, circle_struct);
    int i = fill_circle_coord(&circle_struct, input);
    ASSERT_EQUAL(-1, i);
}

CTEST(figure_suite, test_6)
{
    char input[] = "circle(4.2 1.6, 2.2)";
    int data_length = strlen(input);
    CircleTokens circle_struct;
    circle_struct = make_circle_tokens(data_length, input, circle_struct);
    bool correct_check = fill_circle_coord(&circle_struct, input);
    ASSERT_TRUE(correct_check);
}

CTEST(collision_suite, test_1)
{
    CircleTokens* array_of_shapes = malloc(sizeof(CircleTokens));
    ShapeParameters* parameters = malloc(sizeof(ShapeParameters));

    array_of_shapes[0].coord_x = 1;
    array_of_shapes[0].coord_y = 1;
    array_of_shapes[0].radius = 2.5;

    array_of_shapes[1].coord_x = 0;
    array_of_shapes[1].coord_y = 0;
    array_of_shapes[1].radius = 3;

    array_of_shapes[2].coord_x = 2;
    array_of_shapes[2].coord_y = 3;
    array_of_shapes[2].radius = 3;

    array_of_shapes[3].coord_x = 10;
    array_of_shapes[3].coord_y = 10;
    array_of_shapes[3].radius = 2;

    collision(array_of_shapes, &array_of_shapes[2], 3, &parameters[2]);

    ASSERT_EQUAL(1, parameters[2].coll[0]);
    ASSERT_EQUAL(1, parameters[2].coll[1]);
    ASSERT_EQUAL(0, parameters[2].coll[2]);
}