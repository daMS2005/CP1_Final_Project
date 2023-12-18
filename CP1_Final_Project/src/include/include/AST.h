#ifndef AST_H
#define AST_H
#include <stdlib.h>

typedef struct AST_STRUCT AST_T;

// Enum for different AST node types
enum {
    AST_VARIABLE_DEFINITION,
    AST_FUNCTION_DEFINITION,
    AST_VARIABLE,
    AST_FUNCTION_CALL,
    AST_STRING,
    AST_COMPOUND,
    AST_NOOP
};

// AST structure
struct AST_STRUCT {
    int type;
    struct SCOPE_STRUCT* scope; // Make sure SCOPE_STRUCT is defined somewhere

    // ... (rest of the AST fields) ...

    /* AST_STRING */
    char* string_value;
};

// Function to create AST nodes
AST_T* create_ast_node(int type);

#endif // AST_H
