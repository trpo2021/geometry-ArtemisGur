#include <libgeometry/header.h>
#include <string.h>
#define MAX_SIZE_OF_STRING 1000

int main(void)
{
    int number_of_figures = 0;
    char input_data[MAX_SIZE_OF_STRING];
    int length = 1;
    printf("Enter the data or \"0\" to exit the app: \n");
    bool correct_check = true;
    CircleTokens* array_of_shapes = malloc(sizeof(CircleTokens));
    char example_of_circle[] = "circle";
    char figure[7];

    while (*fgets(input_data, MAX_SIZE_OF_STRING, stdin) != '0')
    {
        int data_length = strlen(input_data);
        array_of_shapes = realloc(array_of_shapes, sizeof(CircleTokens) * length);
        CircleTokens circle_struct;
        circle_struct = make_circle_tokens(data_length, input_data, circle_struct);
        strncpy(figure, input_data, circle_struct.op_bracket);

        if (strcmp(figure, example_of_circle) != 0)
        {
            printf("Incorrect figure. Expected \"circle\" or \"triangle\".\n.");
            return -1;
        }

        correct_check = fill_circle_coord(&circle_struct, input_data);
        array_of_shapes[number_of_figures] = circle_struct;

        print_figure(correct_check, figure, circle_struct, find_circle_perimeter(circle_struct),
                     find_circle_area(circle_struct));
        number_of_figures++;
        length++;
        printf("\n");
    }
}