#include "include/AST.h"

// Function to create a new AST node of the given type
AST_T* init_ast(int type) {
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    if (ast == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    ast->type = type;
    ast->compound_size = 0;
    ast->compound_value = NULL;

    // Initialize other fields based on the type
    switch (type) {
        case AST_VARIABLE_DEFINITION:
            ast->variable_definition_value = NULL;
            break;
        case AST_FUNCTION_DEFINITION:
            ast->function_definition_body = NULL;
            ast->function_definition_args = NULL;
            ast->function_definition_args_size = 0;
            break;
        // ... Initialize other types as needed ...
    }

    return ast;
}

// Example of a function to free an AST node
void free_ast(AST_T* ast) {
    if (ast == NULL) return;

    // Free child nodes or other dynamically allocated fields
    switch (ast->type) {
        case AST_VARIABLE_DEFINITION:
            free(ast->variable_definition_variable_name);
            free_ast(ast->variable_definition_value);
            break;
        case AST_FUNCTION_DEFINITION:
            free(ast->function_definition_name);
            for (size_t i = 0; i < ast->function_definition_args_size; i++) {
                free_ast(ast->function_definition_args[i]);
            }
            free(ast->function_definition_args);
            free_ast(ast->function_definition_body);
            break;
        // ... Free other types as needed ...
    }

    // Finally, free the node itself
    free(ast);
}

// Additional functions for manipulating AST nodes can be added here
// For example, functions to add child nodes, set node values, etc.
