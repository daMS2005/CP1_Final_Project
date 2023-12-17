
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser.h"  // Include your parser header file

// Define the structure for the interpreter state
typedef struct {
    // Add fields relevant to the interpreter's state
    // This might include a symbol table, a pointer to the AST, etc.
} InterpreterState;

// Function to interpret the AST
void interpretAST(InterpreterState* state, ASTNode* root);

// Additional functions for interpreting specific types of nodes
// For example:
void interpretExpression(InterpreterState* state, ASTNode* node);
void interpretStatement(InterpreterState* state, ASTNode* node);
// Add more as needed

#endif // INTERPRETER_H
