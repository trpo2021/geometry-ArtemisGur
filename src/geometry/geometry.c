#include <libgeometry/header.h>
#include <string.h>
#define MAX_SIZE_OF_STRING 1000

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

    if (strcmp(figure, example_of_circle) != 0) {
        printf("Incorrect figure. Expected \"circle\" or \"triangle\".\n.");
        return -1;
    }

    correct_check = fill_circle_coord(&circle_struct, input_data);

    print_figure(
            correct_check,
            figure,
            circle_struct,
            find_circle_perimeter(circle_struct),
            find_circle_area(circle_struct));
}