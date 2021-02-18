#include "header.h"

int main(int argc, char **argv)
{
    char *data = to_lower_string(read_file(argv[1]));
    int length = 0;
    char **array = split_string(&length, data, "\n\r");
    parse(array, length);
}