#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "include/token.h"



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
    lexer_advance(lexer); // Skip the opening quote

    char* value = calloc(1, sizeof(char)); // Start with an empty string
    value[0] = '\0';

    while (lexer->c != '"' && lexer->c != '\0')
    {
        if (lexer->c == '\\') // Handle escape sequences
        {
            lexer_advance(lexer); // Skip the backslash
            switch (lexer->c)
            {
                case 'n': value = realloc(value, strlen(value) + 2);
                          strcat(value, "\n");
                          break;
                case 't': value = realloc(value, strlen(value) + 2);
                          strcat(value, "\t");
                          break;
                // Add other escape sequences as needed
                default:
                          value = realloc(value, strlen(value) + 2);
                          strncat(value, &lexer->c, 1); // Append the literal character
            }
        }
        else
        {
            size_t len = strlen(value);
            value = realloc(value, len + 2); // Resize the buffer
            value[len] = lexer->c;            // Append the current character
            value[len + 1] = '\0';           // Null-terminate the string
        }
        lexer_advance(lexer); // Move to the next character
    }

    lexer_advance(lexer); // Skip the closing quote

    return init_token(TOKEN_STRING, value); // Return a string token with the collected value
}

token_T* lexer_collect_id(lexer_T* lexer)
{
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';
 
    while (isalnum(lexer->c) || lexer->c == '_') // Allow identifiers to start with an underscore
    {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);
        lexer_advance(lexer);
    }

    token_type_t token_type = get_keyword_token_type(value);
    if (token_type != TOKEN_ID) // If it's a keyword
    {
        free(value); // Free the string as it's not needed for keywords
        return init_token(token_type, NULL);
    }

    return init_token(TOKEN_ID, value); // Return as a regular identifier
}
token_type_t get_keyword_token_type(const char* str) {
    if (strcmp(str, "auto") == 0) return TOKEN_AUTO;
    else if (strcmp(str, "break") == 0) return TOKEN_BREAK;
    else if (strcmp(str, "case") == 0) return TOKEN_CASE;
    else if (strcmp(str, "char") == 0) return TOKEN_CHAR;
    else if (strcmp(str, "const") == 0) return TOKEN_CONST;
    else if (strcmp(str, "continue") == 0) return TOKEN_CONTINUE;
    else if (strcmp(str, "default") == 0) return TOKEN_DEFAULT;
    else if (strcmp(str, "do") == 0) return TOKEN_DO;
    else if (strcmp(str, "double") == 0) return TOKEN_DOUBLE;
    else if (strcmp(str, "else") == 0) return TOKEN_ELSE;
    else if (strcmp(str, "enum") == 0) return TOKEN_ENUM;
    else if (strcmp(str, "extern") == 0) return TOKEN_EXTERN;
    else if (strcmp(str, "float") == 0) return TOKEN_FLOAT;
    else if (strcmp(str, "for") == 0) return TOKEN_FOR;
    else if (strcmp(str, "goto") == 0) return TOKEN_GOTO;
    else if (strcmp(str, "if") == 0) return TOKEN_IF;
    else if (strcmp(str, "int") == 0) return TOKEN_INT;
    else if (strcmp(str, "long") == 0) return TOKEN_LONG;
    else if (strcmp(str, "register") == 0) return TOKEN_REGISTER;
    else if (strcmp(str, "return") == 0) return TOKEN_RETURN;
    else if (strcmp(str, "short") == 0) return TOKEN_SHORT;
    else if (strcmp(str, "signed") == 0) return TOKEN_SIGNED;
    else if (strcmp(str, "sizeof") == 0) return TOKEN_SIZEOF;
    else if (strcmp(str, "static") == 0) return TOKEN_STATIC;
    else if (strcmp(str, "struct") == 0) return TOKEN_STRUCT;
    else if (strcmp(str, "switch") == 0) return TOKEN_SWITCH;
    else if (strcmp(str, "typedef") == 0) return TOKEN_TYPEDEF;
    else if (strcmp(str, "union") == 0) return TOKEN_UNION;
    else if (strcmp(str, "unsigned") == 0) return TOKEN_UNSIGNED;
    else if (strcmp(str, "void") == 0) return TOKEN_VOID;
    else if (strcmp(str, "volatile") == 0) return TOKEN_VOLATILE;
    else if (strcmp(str, "while") == 0) return TOKEN_WHILE;

    return TOKEN_ID; // Not a keyword
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
