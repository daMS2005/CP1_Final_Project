#include "include/parser.h"
#include <string.h> // For strcmp
#include "include/lexer.h"
#include "include/AST.h"
#include <stdio.h>




// Define the function mappings
FunctionMapping function_mappings[] = {
    {"eye", "scanf"},
    {"hand", "printf"},
    {"anabolicmeta", "getchar"},
    {"metabolism", "putchar"},
    {"cyton", "fgets"},
    {"sqrt", "sqrt"},  // Note: same name, you might want to change the intuitive name
    {"elevate", "pow"},
    {"anab", "fabs"},
    {"cranium", "ceil"},
    {"sole", "floor"},
    {"column", "strlen"},
    {"mitosis", "strcpy"},
    {NULL, NULL}  // Sentinel value to mark the end of the array
};



void parse_program(Parser *parser) {
    while (parser->current_token.type != TOKEN_EOF) {
        switch (parser->current_token.type) {
            case TOKEN_ID:{
                // Check if it's a special function name
                char *c_function_name = get_c_function_name(parser->current_token.value);
                if (c_function_name != NULL) {
                    // It's an intuitive function name, use the C equivalent
                    parser->current_token.value = c_function_name;
                    parse_function_call(parser); // Handle the function call
                } else {
                    // Handle other identifiers (like variables)
                    parse_identifier(parser);
                }
                break;
            }
            case TOKEN_EQUALS:
            case TOKEN_DOUBLE_EQ:
            case TOKEN_NOT_EQ:
            case TOKEN_LESS:
            case TOKEN_GREATER:
            case TOKEN_LESS_EQ:
            case TOKEN_GREATER_EQ:
            case TOKEN_PLUS:
            case TOKEN_MINUS:
            case TOKEN_ASTERISK:
            case TOKEN_SLASH:
            case TOKEN_PERCENT:
            case TOKEN_AMP:
            case TOKEN_PIPE:
            case TOKEN_CARET:
            case TOKEN_TILDE:
                parse_operator(parser);
                break;

            // Handling literals
            case TOKEN_INT:
            
            case TOKEN_STRING:
            case TOKEN_NUMBER:
                parse_literal(parser);
                break;

            // Handling punctuation
            case TOKEN_SEMI:
            case TOKEN_LPAREN:
            case TOKEN_RPAREN:
            case TOKEN_LBRACE:
            case TOKEN_RBRACE:
            case TOKEN_COMMA:
            case TOKEN_DOT:
            case TOKEN_COLON:
                parse_punctuation(parser);
                break;

            // Handling keywords
            case TOKEN_AUTO:
            case TOKEN_BREAK:
            case TOKEN_CASE:
            case TOKEN_CHAR:
            case TOKEN_CONST:
            case TOKEN_CONTINUE:
            case TOKEN_DEFAULT:
            case TOKEN_DO:
            case TOKEN_DOUBLE:
            case TOKEN_ELSE:
            case TOKEN_ENUM:
            case TOKEN_EXTERN:
            case TOKEN_FOR:
            case TOKEN_GOTO:
            case TOKEN_IF:
            case TOKEN_LONG:
            case TOKEN_REGISTER:
            case TOKEN_RETURN:
            case TOKEN_SHORT:
            case TOKEN_SIGNED:
            case TOKEN_SIZEOF:
            case TOKEN_STATIC:
            case TOKEN_STRUCT:
            case TOKEN_SWITCH:
            case TOKEN_TYPEDEF:
            case TOKEN_UNION:
            case TOKEN_UNSIGNED:
            case TOKEN_VOID:
            case TOKEN_VOLATILE:
            case TOKEN_WHILE:
                parse_keyword(parser);
                break;


            default:
                report_syntax_error(parser);
                break;
        }

        // Get the next token
        parser->current_token = *lexer_get_next_token(parser->lexer);
    }
}
          

void parse_operator(Parser *parser) {
    // The current token is an operator.
    // Here you can add logic depending on the operator type.
    // This example simply prints the operator and moves on.

    switch (parser->current_token.type) {
        case TOKEN_PLUS:
            printf("Operator: +\n");
            break;
        case TOKEN_MINUS:
            printf("Operator: -\n");
            break;
        case TOKEN_ASTERISK:
            printf("Operator: *\n");
            break;
        case TOKEN_SLASH:
            printf("Operator: /\n");
            break;
        // ... handle other operators ...
        default:
            printf("Unknown operator\n");
    }

    // Move to the next token
    parser->current_token = *lexer_get_next_token(parser->lexer);
}
void parse_literal(Parser *parser) {
    // Check the type of the literal and handle it accordingly
    switch (parser->current_token.type) {
        case TOKEN_INT:
            printf("Integer literal: %s\n", parser->current_token.value);
            // Here, you might convert the string to an integer
            // and store it or use it in an expression
            break;
        case TOKEN_FLOAT:
            printf("Float literal: %s\n", parser->current_token.value);
            // Similar to integer, but convert to float
            break;
        case TOKEN_STRING:
            printf("String literal: %s\n", parser->current_token.value);
            // Handle the string literal
            break;
        case TOKEN_NUMBER: // Assuming this is a generic number, could be int or float
            printf("Number literal: %s\n", parser->current_token.value);
            // Determine if it's an int or float and handle accordingly
            break;
        // Add other literal types if necessary
        default:
            printf("Unknown literal type\n");
    }

    // Move to the next token
    parser->current_token = *lexer_get_next_token(parser->lexer);
}
void parse_punctuation(Parser *parser) {
    // Check the type of the punctuation and handle it accordingly
    switch (parser->current_token.type) {
        case TOKEN_SEMI:
            printf("Semicolon found.\n");
            // Typically indicates the end of a statement
            // Handle end of statement logic here
            break;
        case TOKEN_LPAREN:
            printf("Left parenthesis found.\n");
            // Could be the start of an expression or function call
            // Handle accordingly
            break;
        case TOKEN_RPAREN:
            printf("Right parenthesis found.\n");
            // Typically indicates the end of an expression or function call
            // Handle closing logic here
            break;
        case TOKEN_LBRACE:
            printf("Left brace found.\n");
            // Often indicates the start of a block (e.g., function body, if statement)
            // Handle block start logic here
            break;
        case TOKEN_RBRACE:
            printf("Right brace found.\n");
            // Often indicates the end of a block
            // Handle block end logic here
            break;
        case TOKEN_COMMA:
            printf("Comma found.\n");
            // Used to separate items in a list (e.g., function arguments)
            // Handle list separation logic here
            break;
        case TOKEN_DOT:
            printf("Dot found.\n");
            // Used in structures (struct access) or floating point literals
            // Handle accordingly
            break;
        case TOKEN_COLON:
            printf("Colon found.\n");
            // Used in labels or ternary operator
            // Handle accordingly
            break;
        // Add other punctuation types if necessary
        default:
            printf("Unknown punctuation type\n");
    }

    // Move to the next token
    parser->current_token = *lexer_get_next_token(parser->lexer);
}
void parse_keyword(Parser *parser) {
    // Depending on the keyword, the handling logic will differ
    switch (parser->current_token.type) {
        case TOKEN_IF:
             printf("If keyword found.\n");
    // Assume parse_expression is a function that parses an expression and
    // parse_block is a function that parses a block of code.
    parse_expression(parser);  // Parse the condition of the if-statement
    parse_block(parser);       // Parse the block that runs if the condition is true
    break;
        case TOKEN_WHILE:
               printf("While keyword found.\n");
    parse_expression(parser);  // Parse the condition of the while loop
    parse_block(parser);       // Parse the block that runs as long as the condition is true
    break;
       case TOKEN_RETURN:
    printf("Return keyword found.\n");
    parse_expression(parser);  // Parse the expression to return
    // Ensure that there's a semicolon after the return statement
    if (parser->current_token.type != TOKEN_SEMI) {
        report_syntax_error(parser);
    } else {
        parser->current_token = *lexer_get_next_token(parser->lexer);  // Move past the semicolon
    }
    break;
        case TOKEN_INT:
        case TOKEN_CHAR:
            printf("Type specifier keyword found: %s\n", parser->current_token.value);
            // Handle type specifiers for declarations
            break;
        // ... other cases for different keywords ...
        case TOKEN_FOR:
            printf("For keyword found.\n");
            // Handle for-loop logic here
            break;
        case TOKEN_BREAK:
            printf("Break keyword found.\n");
            // Handle break statement logic here
            break;
        case TOKEN_CONTINUE:
            printf("Continue keyword found.\n");
            // Handle continue statement logic here
            break;
        // ... add other keyword cases as needed ...
        default:
            printf("Unknown keyword\n");
    }

    // Move to the next token
    parser->current_token = *lexer_get_next_token(parser->lexer);
}

void parse_identifier(Parser *parser) {
    // The current token should be an identifier.
    printf("Identifier found: %s\n", parser->current_token.value);
    
    // Here, you can add logic to handle the identifier.
    // This could involve adding it to a symbol table, checking if it's a declared variable, etc.

    // Move to the next token
    parser->current_token = *lexer_get_next_token(parser->lexer);
}


void parse_number(Parser *parser) {
    // The current token should be a number.
    printf("Number found: %s\n", parser->current_token.value);

    // Here, you can add logic to convert the string to a numerical value,
    // and then use it in expressions or store it.

    // Move to the next token
    parser->current_token = *lexer_get_next_token(parser->lexer);
}


void parse_string_literal(Parser *parser) {
    // The current token should be a string literal.
    printf("String literal found: %s\n", parser->current_token.value);

    // Example: Store the string literal value in an AST node.
    // This assumes you have a function to create AST nodes and a struct to represent them.
    ASTNode *string_node = create_ast_node(AST_STRING_LITERAL);
    string_node->value = strdup(parser->current_token.value); // Duplicate the string for storage

    // If you're handling escape sequences, you would process them here.
    // For example, replace "\\n" with '\n', "\\t" with '\t', etc.

    // You might want to add the string node to some larger structure,
    // like the current expression or statement being parsed.

    // Move to the next token
    parser->current_token = *lexer_get_next_token(parser->lexer);

    // You can return the AST node if your parser's structure uses return values for tree construction.
    // return string_node;
}



void report_syntax_error(Parser *parser) {
    // Assuming the parser and token structures have fields to track the position in the code
    int line = parser->current_token.line;
    int column = parser->current_token.column;

    printf("Syntax Error: Unexpected token '%s' at line %d, column %d.\n",
           parser->current_token.value, line, column);

    // You can add more sophisticated error reporting here.
    // This could include suggestions for fixing the error, highlighting the error context, etc.

    // Optionally, you can also implement error recovery strategies here to continue parsing
    // after encountering an error. This is especially useful for integrated development
    // environments (IDEs) that provide real-time syntax checking.
}


// Function to find C equivalent of an intuitive function name
char* get_c_function_name(const char *name) {
    for (int i = 0; function_mappings[i].intuitive_name != NULL; i++) {
        if (strcmp(name, function_mappings[i].intuitive_name) == 0) {
            return function_mappings[i].c_name;
        }
    }
    return NULL;
}

// Initialize the parser
Parser* init_parser(lexer_T* lexer) {
    Parser* parser = calloc(1, sizeof(Parser));
    if (!parser) {
        printf("Failed to allocate memory for parser\n");
        return NULL;
    }

    parser->lexer = lexer;
    parser->current_token = *lexer_get_next_token(lexer);// Dereference if necessary
    return parser;
}


void parse_function_call(Parser *parser) {
    // Assuming the function name is stored in `parser->current_token.value`
    char *function_name = parser->current_token.value;
    printf("Function call found: %s\n", function_name);

    // Expecting a left parenthesis next
    parser->current_token = *lexer_get_next_token(parser->lexer);
    if (parser->current_token.type != TOKEN_LPAREN) {
        report_syntax_error(parser);  // Report error if '(' is not found
        return;
    }

    // Now parse the function arguments
    parser->current_token = *lexer_get_next_token(parser->lexer);
    while (parser->current_token.type != TOKEN_RPAREN && parser->current_token.type != TOKEN_EOF) {
        // Handle each argument here
        // For simplicity, let's just print the argument and skip to the next token
        printf("Argument: %s\n", parser->current_token.value);
        
        // Get the next token, skipping commas if your language uses them to separate arguments
        do {
            parser->current_token = *lexer_get_next_token(parser->lexer);
        } while (parser->current_token.type == TOKEN_COMMA);

        // Additional logic for handling each argument goes here
        // This could involve parsing expressions, etc.
    }

    if (parser->current_token.type != TOKEN_RPAREN) {
        report_syntax_error(parser);  // Report error if ')' is not found
    }

    // Move past the closing parenthesis
    parser->current_token = *lexer_get_next_token(parser->lexer);

    // Additional logic to handle the end of the function call
    // This could involve adding a function call node to an AST, if you are building one
}
