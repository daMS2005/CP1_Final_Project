#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "../PARSER/parser.h"

// Enumeration for the different types of nodes in the AST
typedef enum {
    NODE_TYPE_FUNCTION_CALL,             // Represents a function call
    NODE_TYPE_VARIABLE_ASSIGNMENT,       // Represents variable assignment
    NODE_TYPE_IF_STATEMENT,              // Represents an if statement
    NODE_TYPE_LOOP,                      // Represents a loop
    // ... add more node types as needed for your AST
} NodeType;

// Structure for representing nodes in the AST
typedef struct ASTNode {
    NodeType type;            // The type of the node
    char* functionName;       // Function name (for function calls)
    char* arguments;          // Arguments to the function (if any)
    struct ASTNode* left;     // Pointer to the left child (if applicable)
    struct ASTNode* right;    // Pointer to the right child (if applicable)
    // ... add other fields as needed for your AST
} ASTNode;

// Structure for maintaining the state of the interpreter
typedef struct {
    // Add fields relevant to the interpreter's state
    // For example, a symbol table, a pointer to the AST, etc.
} InterpreterState;

// Function prototypes for interpreting the AST and its nodes
void interpretAST(InterpreterState* state, ASTNode* root);                    // Interprets the entire AST
void interpretExpression(InterpreterState* state, ASTNode* node);             // Interprets an expression node
void interpretStatement(InterpreterState* state, ASTNode* node);              // Interprets a statement node
// ... add more function prototypes as needed

#endif // INTERPRETER_H
