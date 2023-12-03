#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Token types
typedef enum {
    KEYWORD,
    IDENTIFIER,
    SYMBOL,
    LITERAL,
    COMMENT,
    UNKNOWN
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char* value;
    int position;
} Token;

// Lexer function
void tokenize(char* code, Token** tokens, int* numTokens) {
    *numTokens = 0;
    *tokens = NULL;
    
    int position = 0;
    
    while (code[position] != '\0') {
        // Skip whitespace
        if (isspace(code[position])) {
            position++;
            continue;
        }

        // Keywords
        if (sscanf(&code[position], "%*[^a-zA-Z]%n", &position) == 0) {
            char keyword[32];
            if (sscanf(&code[position], "%31[a-zA-Z]%n", keyword, &position) == 1) {
                *tokens = realloc(*tokens, (*numTokens + 1) * sizeof(Token));
                (*tokens)[*numTokens].type = KEYWORD;
                (*tokens)[*numTokens].value = strdup(keyword);
                (*tokens)[*numTokens].position = position - strlen(keyword);
                (*numTokens)++;
                continue;
            }
        }

        // Identifiers
        if (sscanf(&code[position], "%*[a-zA-Z_]%n", &position) == 0) {
            char identifier[32];
            if (sscanf(&code[position], "%31[a-zA-Z0-9_]%n", identifier, &position) == 1) {
                *tokens = realloc(*tokens, (*numTokens + 1) * sizeof(Token));
                (*tokens)[*numTokens].type = IDENTIFIER;
                (*tokens)[*numTokens].value = strdup(identifier);
                (*tokens)[*numTokens].position = position - strlen(identifier);
                (*numTokens)++;
                continue;
            }
        }

      
        if (strchr("=+-*/(){};,", code[position]) != NULL) {
            *tokens = realloc(*tokens, (*numTokens + 1) * sizeof(Token));
            (*tokens)[*numTokens].type = SYMBOL;
            (*tokens)[*numTokens].value = malloc(2);
            (*tokens)[*numTokens].value[0] = code[position];
            (*tokens)[*numTokens].value[1] = '\0';
            (*tokens)[*numTokens].position = position;
            (*numTokens)++;
            position++;
            continue;
        }

        if (sscanf(&code[position], "%*[^0-9]%n", &position) == 0) {
            char literal[32];
            if (sscanf(&code[position], "%31[0-9]%n", literal, &position) == 1) {
                *tokens = realloc(*tokens, (*numTokens + 1) * sizeof(Token));
                (*tokens)[*numTokens].type = LITERAL;
                (*tokens)[*numTokens].value = strdup(literal);
                (*tokens)[*numTokens].position = position - strlen(literal);
                (*numTokens)++;
                continue;
            }
        }

        
        if (strncmp(&code[position], "//", 2) == 0) {
            while (code[position] != '\0' && code[position] != '\n') {
                position++;
            }
            continue;
        }

       
        *tokens = realloc(*tokens, (*numTokens + 1) * sizeof(Token));
        (*tokens)[*numTokens].type = UNKNOWN;
        (*tokens)[*numTokens].value = malloc(2);
        (*tokens)[*numTokens].value[0] = code[position];
        (*tokens)[*numTokens].value[1] = '\0';
        (*tokens)[*numTokens].position = position;
        (*numTokens)++;
        position++;
    }
}


void freeTokens(Token* tokens, int numTokens) {
    for (int i = 0; i < numTokens; i++) {
        free(tokens[i].value);
    }
    free(tokens);
}


int main() {
    char code[] = "int main() { // This is a comment\n"
                  "    if (x == 5) {\n"
                  "        return x;\n"
                  "    } else {\n"
                  "        return -1;\n"
                  "    }\n"
                  "}\n";

    Token* tokens;
    int numTokens;

    tokenize(code, &tokens, &numTokens);

    for (int i = 0; i < numTokens; i++) {
        printf("Type: %d, Value: %s, Position: %d\n", tokens[i].type, tokens[i].value, tokens[i].position);
    }

    freeTokens(tokens, numTokens);

    return 0;
}
