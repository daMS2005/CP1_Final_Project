#ifndef PARSER_H
#define PARSER_H

// Define the different types of tokens
typedef enum {
    TOKEN_IDENTIFIER, 
    TOKEN_KEYWORD, 
    TOKEN_LITERAL, 
    TOKEN_OPERATOR
    // Add other token types as needed
} TokenType;

// Structure for a token
typedef struct {
    TokenType type;
    char* value;
} Token;

// Parser state structure
typedef struct {
    Token currentToken;
    Token lookaheadToken;
    // Add other state information as needed
} ParserState;

#endif // PARSER_H
