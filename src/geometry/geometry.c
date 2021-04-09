#include <libgeometry/header.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE_OF_STRING 1000

int main(void)
{
    int number_of_figures = 0;
    char input_data[MAX_SIZE_OF_STRING];
    int length = 1;
    printf("Enter the data or \"0\" to exit the app: \n");
    CircleTokens* array_of_shapes = malloc(sizeof(CircleTokens));
    char example_of_circle[] = "circle";
    char figure[7];
    ShapeParameters* parameters = malloc(sizeof(ShapeParameters));

    while (*fgets(input_data, MAX_SIZE_OF_STRING, stdin) != '0')
    {
        int data_length = strlen(input_data);
        array_of_shapes = realloc(array_of_shapes, sizeof(CircleTokens) * length);
        parameters = realloc(parameters, sizeof(ShapeParameters) * length);
        CircleTokens circle_struct;
        circle_struct = make_circle_tokens(data_length, input_data, circle_struct);
        strncpy(figure, input_data, circle_struct.op_bracket);

        if (strcmp(figure, example_of_circle) != 0)
        {
            printf("Incorrect figure. Expected \"circle\" or \"triangle\".\n.");
            return -1;
        }
        if (fill_circle_coord(&circle_struct, input_data) != -1)
        {
            exception_print(fill_circle_coord(&circle_struct, input_data));
            return -1;
        }
        array_of_shapes[number_of_figures] = circle_struct;
        parameters[number_of_figures].perimeter = find_circle_perimeter(circle_struct);
        parameters[number_of_figures].area = find_circle_area(circle_struct);
        number_of_figures++;
        length++;
    }
    printf("\n\n\n");
    for (int i = 0; i < number_of_figures; i++)
    {
        int j = 0;
        printf("%d.  ", i + 1);
        print_figure(&array_of_shapes[i], &parameters[i]);
        collision(array_of_shapes, &array_of_shapes[i], number_of_figures, &parameters[i]);
        printf("      intersects:\n");

        while (parameters[i].coll[j] != -1)
        {
            if (parameters[i].coll[j] == 1)
                printf("        %d. Circle\n", j + 1);
            j++;
        }
        printf("\n");
    }
    printf("\n");
}
