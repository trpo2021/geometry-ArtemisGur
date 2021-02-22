#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE_OF_STRING 100

typedef struct
{
    int op_bracket;
    int cl_bracket;
    int space;
    int comma;
    double coordX;
    double coordY;
    double radius;
} CircleTokens;

bool exception_print(bool correct_check, int position, char *input_data)
{
    for (int j = 0; j < position; j++)
    {
        printf(" ");
    }
    printf("^\n");
    printf("Error at column %d. Expected coordination.\n", position);
    return correct_check = false;
}

bool fill_circle_coord(CircleTokens *coords, char *input_data)
{
    bool correct_check;
    for (int i = coords->op_bracket + 1; i < coords->space; i++)
    {
        char *tmp_double = &input_data[i];
        char *tmp;
        double temp = strtod(tmp_double, &tmp);
        if (*tmp == input_data[coords->space])
        {
            coords->coordX = temp;
            break;
        }
        else
            correct_check = exception_print(correct_check, i, &coords);
    }

    for (int i = coords->space + 1; i < coords->comma; i++)
    {
        char *tmp_double = &input_data[i];
        char *tmp;
        double temp = strtod(tmp_double, &tmp);
        if (*tmp == input_data[coords->comma])
        {
            coords->coordY = temp;
            break;
        }
        else
            correct_check = exception_print(correct_check, i, &coords);
    }

    for (int i = coords->comma + 1; i < coords->cl_bracket; i++)
    {
        char *tmp_double = &input_data[i];
        char *tmp;
        double temp = strtod(tmp_double, &tmp);
        if (*tmp == input_data[coords->cl_bracket])
        {
            coords->radius = temp;
            break;
        }
        else
        {
            correct_check = exception_print(correct_check, i, &coords);
        }
    }
    return correct_check;
}
CircleTokens make_circle_tokens(int string_length, char *array, CircleTokens circle_struct)
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
            int somthing_wrong = i;
        }
        else if (array[i] == ' ')
        {
            circle_struct.space = i;
        }
    }
    return circle_struct;
}

int main(void)
{
    CircleTokens circle_struct;
    char input_data[MAX_SIZE_OF_STRING];
    printf("Input data: \n");
    fgets(input_data, MAX_SIZE_OF_STRING, stdin);
    bool correct_check = true;

    char example_of_circle[] = "circle";
    int data_length = strlen(input_data);

    circle_struct = make_circle_tokens(data_length, input_data, circle_struct);

    char figure[circle_struct.op_bracket];
    strncpy(figure, input_data, circle_struct.op_bracket);

    if (strcmp(figure, example_of_circle) != 0)
    {
        printf("Incorrect figure. Expected \"circle\".\n.");
        return -1;
    }
    correct_check = fill_circle_coord(&circle_struct, input_data);

    if (correct_check)
        printf("\n%s(%.2lf %.2lf, %.2lf)\n", figure, circle_struct.coordX, circle_struct.coordY, circle_struct.radius);
    else
        return -1;
}