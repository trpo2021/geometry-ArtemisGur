#include "header.h"

char *concat_string(char *first, char *last)
{
    char *result = malloc(sizeof(char) * (strlen(first) + strlen(last) + 1));
    if (!result)
    {
        perror("malloc");
        exit(-1);
    }
    memcpy(result, first, strlen(first));
    memcpy(result + strlen(first), last, strlen(last) + 1);
    return result;
}

char *to_lower_string(char *string)
{
    for (int i = 0; string[i]; i++)
    {
        string[i] = tolower(string[i]);
    }
    return string;
}

char **split_string(int *length, char *string, char *separator)
{
    char **result = NULL;
    char *p = strtok(string, separator);
    *length = 0;
    while (p)
    {
        result = realloc(result, sizeof(char *) * ++(*length));
        if (!result)
        {
            perror("realloc");
            exit(-1);
        }
        result[(*length) - 1] = p;
        p = strtok(NULL, separator);
    }
    return result;
}

char *append_char(const char *string, char c)
{
    size_t sz = strlen(string);
    char *result = malloc(sz + 2);
    if (!result)
    {
        perror("malloc");
        exit(-1);
    }
    strcpy(result, string);
    result[sz] = c;
    result[sz + 1] = '\0';
    return result;
}

char *read_file(const char *filename)
{
    FILE *stream;
    char *outp = "";
    char *line = NULL;
    size_t len = 0;
    size_t nread;
    stream = fopen(filename, "r");
    if (!stream)
    {
        perror("fopen");
        exit(-2);
    }
    while ((nread = getline(&line, &len, stream)) != -1)
    {
        outp = concat_string(outp, line);
    }
    free(line);
    fclose(stream);
    return outp;
}

void print_exception(const char *data, int column)
{
    for (int i = 0; i < strlen(data); i++)
    {
        printf("%c", data[i]);
    }
    printf("\n");
    for (int i = 0; i < column; i++)
    {
        printf(" ");
    }
    printf("^\n");
}

Token create_token_from_char(char c, int line, int column)
{
    char *data = "";
    data = append_char(data, c);
    Token token = {.data = data,
                   .type = (TokenType)c,
                   .line = line,
                   .column = column};
    return token;
}

Token create_token_from_string(char *string, TokenType type, int line, int column)
{
    Token token = {
        .data = concat_string("", string),
        .type = type,
        .line = line,
        .column = column};
    return token;
}

TokenList *token_list_init(TokenList *this)
{
    this = malloc(sizeof(TokenList));
    Token *data;
    data = malloc(sizeof(Token));
    if (data == NULL)
    {
        printf("Unable to allocate memory, exiting.\n");
        free(data);
        exit(-1);
    }
    else
    {
        this->data = data;
        this->size = 0;
    }
    return this;
}

TokenList *token_list_add(TokenList *this, Token item)
{
    Token *data;
    this->size += 1;
    data = realloc(this->data, this->size * sizeof(Token));
    if (data == NULL)
    {
        printf("Unable to reallocate memory, exiting.\n");
        free(data);
        exit(-1);
    }
    else
    {
        this->data = data;
        this->data[this->size - 1] = item;
    }
    return this;
}

void token_list_remove(TokenList *this, int index)
{
    TokenList temp;
    Token *pointer;
    token_list_init(&temp);
    for (int i = index; i < this->size; i++)
    {
        this->data[i] = this->data[i + 1];
    }
    this->size -= 1;
    for (int i = 0; i < this->size; i++)
    {
        token_list_add(&temp, this->data[i]);
    }
    pointer = realloc(temp.data, temp.size * sizeof(Token));
    if (pointer == NULL)
    {
        printf("Unable to reallocate memory, exiting.\n");
        free(pointer);
        exit(-1);
    }
    this->data = pointer;
}

void token_list_dispose(TokenList *this)
{
    free(this->data);
    this->data = NULL;
    this->size = 0;
}
TokenList *lex(const char *data, size_t length, int line)
{
    LexerState ls = LexerDefault;
    TokenList *tokens = NULL;
    tokens = token_list_init(tokens);
    char *token_content = "";
    bool has_error = false;
    for (int column = 0; column < length; column++)
    {
        char c = data[column];
        switch (ls)
        {
        case LexerDefault:
            if (isalpha(c))
            {
                token_content = append_char(token_content, c);
                ls = LexerWord;
            }
            else if (isdigit(c) || c == '-')
            {
                token_content = append_char(token_content, c);
                ls = LexerNumber;
            }
            else if (c == TokenComma || c == TokenOpBracket || c == TokenClBracket)
            {
                tokens = token_list_add(tokens, create_token_from_char(c, line, column));
            }
            else if (c != ' ')
            {
                print_exception(data, column);
                printf("Unexpected token %c at line %d and column %d\n\n", c, line, column);
                has_error = true;
            }
            break;
        case LexerWord:
            if (isalpha(c))
            {
                token_content = append_char(token_content, c);
                if (column + 1 >= strlen(data))
                {
                    tokens = token_list_add(tokens, create_token_from_string(token_content, TokenWord, line, column - strlen(token_content)));
                    free(token_content);
                    ls = LexerDefault;
                }
            }
            else
            {
                tokens = token_list_add(tokens, create_token_from_string(token_content, TokenWord, line, column - strlen(token_content)));
                free(token_content);
                token_content = "";
                --column;
                ls = LexerDefault;
            }
            break;
        case LexerNumber:
            if (c == '.' || isdigit(c))
            {
                token_content = append_char(token_content, c);
                if (column + 1 >= strlen(data))
                {
                    tokens = token_list_add(tokens, create_token_from_string(token_content, TokenNumber, line, column - strlen(token_content)));
                    free(token_content);
                    ls = LexerDefault;
                }
            }
            else
            {
                tokens = token_list_add(tokens, create_token_from_string(token_content, TokenNumber, line, column - strlen(token_content)));
                free(token_content);
                token_content = "";
                --column;
                ls = LexerDefault;
            }
            break;
        }
    }
    if (has_error)
    {
        return NULL;
    }
    return tokens;
}

bool try_parse_number(const char *string, double *result)
{
    bool has_dot = false;
    if (isdigit(string[0]) || (string[0] == '-' && isdigit(string[1])))
    {
        for (int i = 1; i < strlen(string); i++)
        {
            if (string[i] == '.' && i + 1 < strlen(string))
            {
                if (has_dot)
                    return false;
                has_dot = true;
            }
            else if (!isdigit(string[i]))
            {
                return false;
            }
        }
        *result = strtod(string, NULL);
        return true;
    }
    return false;
}

Circle *create_circle(TokenList *tokens, const char *string)
{
    if (tokens->size < sizeof(CIRCLE_TEMPLATE) / sizeof(CIRCLE_TEMPLATE[0]))
    {
        print_exception(string, tokens->data[tokens->size - 1].column);
        printf("Unexpected signature. Circle expected <(>[ ]<double>[ ]<double>[ ]<,>[ ]<double>[ ]<)>\n");
        return NULL;
    }
    Circle *circle = NULL;
    double numbers[3];
    for (int i = 0, pos = 0; i < sizeof(CIRCLE_TEMPLATE) / sizeof(CIRCLE_TEMPLATE[0]); i++)
    {
        if (tokens->data[i].type == CIRCLE_TEMPLATE[i].type)
        {
            if (tokens->data[i].type == TokenNumber)
            {
                if (!try_parse_number(tokens->data[i].data, &numbers[pos++]))
                {
                    print_exception(string, tokens->data[i].column);
                    printf("Unexpected token %s at line %d and column %d, expected <double>\n",
                           tokens->data[i].data,
                           tokens->data[i].line,
                           tokens->data[i].column);
                    return NULL;
                }
            }
        }
        else
        {
            print_exception(string, tokens->data[i].column);
            printf("Unexpected token %s at line %d and column %d, expected <%s>\n",
                   tokens->data[i].data,
                   tokens->data[i].line,
                   tokens->data[i].column,
                   CIRCLE_TEMPLATE[i].data);
            return NULL;
        }
    }
    if (tokens->size > sizeof(CIRCLE_TEMPLATE) / sizeof(CIRCLE_TEMPLATE[0]))
    {
        print_exception(string, tokens->data[sizeof(CIRCLE_TEMPLATE) / sizeof(CIRCLE_TEMPLATE[0])].column);
        printf("Unexpected token %s\n", tokens->data[sizeof(CIRCLE_TEMPLATE) / sizeof(CIRCLE_TEMPLATE[0])].data);
        return NULL;
    }
    circle = malloc(sizeof(Circle));
    circle->position.x = numbers[0];
    circle->position.y = numbers[1];
    circle->radius = numbers[2];
    return circle;
}

Figure *create_figure(FigureType type, void *data)
{
    Figure *figure = NULL;
    figure = malloc(sizeof(Figure));
    figure->type = type;
    figure->data = data;
    return figure;
}

Figure *parse_line(TokenList *tokens, const char *string)
{
    if (tokens == NULL)
    {
        return NULL;
    }
    if (tokens->data[0].type == TokenWord)
    {
        if (strcmp(tokens->data[0].data, CIRCLE_TEMPLATE[0].data) == 0)
        {
            Circle *circle = create_circle(tokens, string);
            if (circle)
            {
                return create_figure(FigureCircle, circle);
            }
            return NULL;
        }
        else
        {
            print_exception(string, tokens->data[0].column);
            printf("Unexpected word %s. Expected 'circle', 'triangle' or 'polygon'\n", tokens->data[0].data);
            return NULL;
        }
    }
    else
    {
        print_exception(string, tokens->data[0].column);
        printf("Unexpected token %s. Expected word.\n", tokens->data[0].data);
        return NULL;
    }
}

void parse(char **lines, int length)
{
    for (int line = 0; line < length; line++)
    {
        TokenList *tokens = lex(lines[line], strlen(lines[line]), line + 1);
        Figure *f = parse_line(tokens, lines[line]);
        if (f)
        {
            Circle *cir = (Circle *)f->data;
            printf("Circle. Point: [%.2lf, %.2lf], Radius: %.4lf\n",
                   cir->position.x,
                   cir->position.y,
                   cir->radius);
        }
    }
    return;
}