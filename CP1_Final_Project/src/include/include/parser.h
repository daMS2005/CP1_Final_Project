#ifndef PARSER_H
#define PARSER_H

#include "lexer.h" // For lexer_T and token_T
#include "AST.h"   // For ASTNode definitions (ensure this file exists)

// Function Mapping Structure
typedef struct {
    char *intuitive_name;
    char *c_name;
} FunctionMapping;

// Declare the function mappings (definitions will be in parser.c)
extern FunctionMapping function_mappings[];

// Parser Structure
typedef struct PARSER_STRUCT {
    lexer_T *lexer;
    token_T current_token;
    // Add more fields as needed
} Parser;

// Function Prototypes
Parser* init_parser(lexer_T* lexer);
void parse_program(Parser *parser);
void parse_identifier(Parser *parser);
void parse_number(Parser *parser);
void parse_string_literal(Parser *parser);
void parse_operator(Parser *parser);
void parse_literal(Parser *parser);
void parse_punctuation(Parser *parser);
void parse_keyword(Parser *parser);
void report_syntax_error(Parser *parser);
void parse_function_call(Parser *parser);
char* get_c_function_name(const char *name);

#endif // PARSER_H
