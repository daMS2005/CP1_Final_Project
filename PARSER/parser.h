#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>

// Define the different types of tokens
typedef enum {
    TOKEN_IDENTIFIER, 
    TOKEN_KEYWORD, 
    TOKEN_LITERAL, 
    TOKEN_OPERATOR,
    TOKEN_EOF  // End of file/input token
    // Add other token types as needed
} TokenType;

// Structure for a token
typedef struct {
    TokenType type;
    char* value; // Ensure proper memory management for these strings
} Token;

// Parser state structure
typedef struct {
    Token currentToken;
    Token lookaheadToken;
    // Add other state information as needed
} ParserState;

// Function declarations for parser operations (implement these in parser.c)
void getNextToken(ParserState* state);
void parseProgram(ParserState* state);
void parseStatement(ParserState* state);
void parseExpression(ParserState* state);
void parseFunctionCall(ParserState* state);

#endif // PARSER_H
