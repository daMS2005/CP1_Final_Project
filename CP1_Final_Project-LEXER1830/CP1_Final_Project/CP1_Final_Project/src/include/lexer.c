#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "include/token.h"

// Function Prototypes
token_T* lexer_collect_string(lexer_T* lexer);
token_T* lexer_collect_id(lexer_T* lexer);
token_T* lexer_collect_number(lexer_T* lexer);
token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token);
char* lexer_get_current_char_as_string(lexer_T* lexer);
void lexer_skip_comment(lexer_T* lexer);
void lexer_skip_multiline_comment(lexer_T* lexer);


lexer_T* init_lexer(const char* contents)
{
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];

    return lexer;
}
char lexer_peek(lexer_T* lexer)
{
    return lexer->contents[lexer->i + 1];
}
void lexer_advance(lexer_T* lexer)
{
    if (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
    {
        lexer->i += 1;
        lexer->c = lexer->contents[lexer->i];
    }
}

void lexer_skip_whitespace(lexer_T* lexer)
{
    while (lexer->c == ' ' || lexer->c == 10)
    {
        lexer_advance(lexer);
    }
}

token_T* lexer_get_next_token(lexer_T* lexer)
{
    while (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
    {
        if (isspace(lexer->c)) // This handles all whitespace characters
        {
            lexer_skip_whitespace(lexer);
            continue;
        }

        if (lexer->c == '\\' && lexer_peek(lexer) == '\\') // Single-line comment
        {
            lexer_skip_comment(lexer);
            continue;
        }

        if (lexer->c == '|' && lexer_peek(lexer) == '|') // Multi-line comment
        {
            lexer_skip_multiline_comment(lexer);
            continue;
        }

        if (isdigit(lexer->c)) // Numerical literals
        {
            return lexer_collect_number(lexer);
        }

        if (isalpha(lexer->c) || lexer->c == '_') // Identifiers (including those that start with '_')
        {
            return lexer_collect_id(lexer);
        }

        if (lexer->c == '"') // String literals
        {
            return lexer_collect_string(lexer);
        }
         if (lexer->c == '=' && lexer_peek(lexer) == '=')
        {
            lexer_advance(lexer);
            return lexer_advance_with_token(lexer, init_token(TOKEN_DOUBLE_EQ, "=="));
        }
        else if (lexer->c == '!' && lexer_peek(lexer) == '=')
        {
            lexer_advance(lexer);
            return lexer_advance_with_token(lexer, init_token(TOKEN_NOT_EQ, "!="));
        }
        else if (lexer->c == '<' && lexer_peek(lexer) == '=')
        {
            lexer_advance(lexer);
            return lexer_advance_with_token(lexer, init_token(TOKEN_LESS_EQ, "<="));
        }
        else if (lexer->c == '>' && lexer_peek(lexer) == '=')
        {
            lexer_advance(lexer);
            return lexer_advance_with_token(lexer, init_token(TOKEN_GREATER_EQ, ">="));
        }
        // Handling single characters and returning their respective tokens
        switch (lexer->c)
        {
            case '=': return lexer_advance_with_token(lexer, init_token(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer)));
            case ';': return lexer_advance_with_token(lexer, init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer)));
            case '(': return lexer_advance_with_token(lexer, init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer)));
            case ')': return lexer_advance_with_token(lexer, init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer)));
            case '{': return lexer_advance_with_token(lexer, init_token(TOKEN_LBRACE, lexer_get_current_char_as_string(lexer)));
            case '}': return lexer_advance_with_token(lexer, init_token(TOKEN_RBRACE, lexer_get_current_char_as_string(lexer)));
            case '+': return lexer_advance_with_token(lexer, init_token(TOKEN_PLUS, "+"));
            case '-': return lexer_advance_with_token(lexer, init_token(TOKEN_MINUS, "-"));
            case '*': return lexer_advance_with_token(lexer, init_token(TOKEN_ASTERISK, "*"));
            case '/': return lexer_advance_with_token(lexer, init_token(TOKEN_SLASH, "/"));
            case '%': return lexer_advance_with_token(lexer, init_token(TOKEN_PERCENT, "%"));
            case '&': return lexer_advance_with_token(lexer, init_token(TOKEN_AMP, "&"));
            case '|': return lexer_advance_with_token(lexer, init_token(TOKEN_PIPE, "|"));
            case '^': return lexer_advance_with_token(lexer, init_token(TOKEN_CARET, "^"));
            case '~': return lexer_advance_with_token(lexer, init_token(TOKEN_TILDE, "~"));
            case ',': return lexer_advance_with_token(lexer, init_token(TOKEN_COMMA, ","));
            case '.': return lexer_advance_with_token(lexer, init_token(TOKEN_DOT, "."));
            case ':': return lexer_advance_with_token(lexer, init_token(TOKEN_COLON, ":"));
            // Add more cases for other single characters as needed
            default:
                printf("Unknown token '%c'\n", lexer->c);
                exit(EXIT_FAILURE);
        }
    }

    return init_token(TOKEN_EOF, "\0"); // Return an EOF token at the end of input
}

token_T* lexer_collect_string(lexer_T* lexer)
{
    lexer_advance(lexer);

    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (lexer->c != '"')
    {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    lexer_advance(lexer);

    return init_token(TOKEN_STRING, value);
}

token_T* lexer_collect_id(lexer_T* lexer) {
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (isalnum(lexer->c) || lexer->c == '_') {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    // Check for custom keywords
    if (strcmp(value, "DIGESTION") == 0)
        return init_token(TOKEN_DIGESTION, value);
    else if (strcmp(value, "MOUTH") == 0)
        return init_token(TOKEN_MOUTH, value);
    else if (strcmp(value, "EYE") == 0)
        return init_token(TOKEN_EYE, value);
    else if (strcmp(value, "MEASURE") == 0)
        return init_token(TOKEN_MEASURE, value);
    else if (strcmp(value, "MITOSIS") == 0)
        return init_token(TOKEN_MITOSIS, value);

    return init_token(TOKEN_ID, value);
}

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token)
{
    lexer_advance(lexer);

    return token;
}

char* lexer_get_current_char_as_string(lexer_T* lexer)
{
    char* str = calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';

    return str;
}

token_T* lexer_collect_number(lexer_T* lexer) {
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';
    int decimalPointCount = 0;

    while (isdigit(lexer->c) || lexer->c == '.') {
        // Handle decimal point for floating point numbers
        if (lexer->c == '.') {
            decimalPointCount++;
        }

        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    token_type_t type = (decimalPointCount > 0) ? TOKEN_FLOAT : TOKEN_INT;
    return init_token(type, value);
}


void lexer_skip_comment(lexer_T* lexer)
{
    while (lexer->c != '\n' && lexer->c != '\0')
    {
        lexer_advance(lexer);
    }
}

void lexer_skip_multiline_comment(lexer_T* lexer)
{
    lexer_advance(lexer); // Skip the second '|'

    while (lexer->c != '\0')
    {
        if (lexer->c == '|' && lexer_peek(lexer) == '|')
        {
            lexer_advance(lexer); // Skip the closing '||'
            lexer_advance(lexer);
            return;
        }
        lexer_advance(lexer);
    }
}
