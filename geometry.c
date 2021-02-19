#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxSizeOfString 100

typedef struct
{
    int op_bracket;
    int cl_bracket;
    int space;
    int comma;
    int coordX;
    int coordY;
    double radius;
} Tokens;

int main(void)
{
    Tokens circleStruct;
    char InputData[maxSizeOfString];
    printf("Input data: \n");
    fgets(InputData, maxSizeOfString, stdin);

    char exampleOfCircle[] = "circle";
    int DataLength = strlen(InputData);

    for (int i = 0; i < DataLength; i++)
    {
        if (InputData[i] == '(')
        {
            circleStruct.op_bracket = i;
        }
        if (InputData[i] == ')')
        {
            circleStruct.cl_bracket = i;
        }
        if (InputData[i] == ',')
        {
            circleStruct.comma = i;
        }
        if (InputData[i] == ' ') //&& InputData[i - 1] == ',')
        {
            //printf("%d   ", i);
            circleStruct.space = i;
        }
    }
    char figure[circleStruct.op_bracket];
    //printf("%d", circleStruct.space);
    strncpy(figure, InputData, circleStruct.op_bracket);

    if (strcmp(figure, exampleOfCircle) != 0)
    {
        printf("Incorrect figure. Expected \"circle\"\n.");
        return -1;
    }

    for (int i = circleStruct.op_bracket + 1; i < circleStruct.space - 3; i++)
    {
        //printf("%d", circleStruct.op_bracket);
        if (isdigit(InputData[i]))
        {
            circleStruct.coordX = atoi(InputData + circleStruct.op_bracket + 1);
        }
        else
        {
            for (int j = 0; j < i; j++)
            {
                printf(" ");
            }
            printf("^\n");
            printf("Error at column %d. Expected coordination X\n", i);
            return -1;
        }
    }

    for (int i = circleStruct.space - 2; i < circleStruct.comma; i++)
    {
        if (isdigit(InputData[i]))
        {
            circleStruct.coordY = atoi(InputData + circleStruct.space - 2);
        }
        else
        {
            for (int j = 0; j < i; j++)
            {
                printf(" ");
            }
            printf("^\n");
            printf("Error at column %d. Expected coordination Y\n", i);
            return -1;
        }
    }

    for (int i = circleStruct.comma + 2; i < circleStruct.cl_bracket; i++)
    {
        if (isdigit(InputData[i]))
        {
            circleStruct.radius = atof(InputData + circleStruct.comma + 1);
        }
        else
        {
            for (int j = 0; j < i - 2; j++)
            {
                printf(" ");
            }
            printf("^\n");
            printf("Error at column %d. Expected radius\n", i);
            return -1;
        }
    }
    printf("\n%s(%d %d, %.1lf)\n", figure, circleStruct.coordX, circleStruct.coordY, circleStruct.radius);
}