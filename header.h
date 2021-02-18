#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    TokenWord = 0,
    TokenNumber = 1,
    TokenOpBracket = '(',
    TokenComma = ',',
    TokenClBracket = ')'
} TokenType;

typedef struct
{
    char *data;
    TokenType type;
    unsigned int column;
    unsigned int line;
} Token;


typedef struct
{
    Token *data;
    size_t size;
} TokenList;

typedef enum
{
    FigureCircle = 0,
    FigureNone = -1
} FigureType;

typedef struct
{
    double x;
    double y;
} Point;

typedef struct
{
    Point position;
    double radius;
} Circle;

typedef struct
{
    void *data;
    FigureType type;
} Figure;

typedef enum
{
    LexerDefault,
    LexerWord,
    LexerNumber
} LexerState;

static const Token CIRCLE_TEMPLATE[] = {
    {.data = "circle", .type = TokenWord},
    {.data = "(", .type = TokenOpBracket},
    {.data = "double", .type = TokenNumber},
    {.data = "double", .type = TokenNumber},
    {.data = ",", .type = TokenComma},
    {.data = "double", .type = TokenNumber},
    {.data = ")", .type = TokenClBracket}};

char *read_file(const char *filename);
char *concat_string(char *first, char *last);
char *to_lower_string(char *string);
char **split_string(int *length, char *string, char *separator);
char *append_char(const char *string, char c);
void print_exception(const char *data, int column);
bool try_parse_number(const char *string, double *result);
Figure *parse_line(TokenList *tokens, const char *string);
void parse(char **lines, int length);
Token create_token_from_char(char c, int line, int column);
Token create_token_from_string(char *string, TokenType type, int line, int column);
TokenList *token_list_init(TokenList *this);
TokenList *token_list_add(TokenList *this, Token item);
void token_list_remove(TokenList *this, int index);
void token_list_dispose(TokenList *this);
TokenList *lex(const char *data, size_t length, int line);
Circle *create_circle(TokenList *tokens, const char *string);
Figure *create_figure(FigureType type, void *data);
int main(int argc, char **argv);