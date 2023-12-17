#include "intepreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to map EVA function names to C function names and execute them
void executeFunction(const char* functionName, const char* args) {
    if (strcmp(functionName, "MALLOC") == 0) {
        // Equivalent to malloc in C
        // Additional code to handle arguments and call malloc
    } else if (strcmp(functionName, "PRINTF") == 0) {
        printf("%s", args); // Directly using printf for simplicity
    } else if (strcmp(functionName, "SCANF") == 0) {
        scanf("%s", args); // Directly using scanf for simplicity
    } else if (strcmp(functionName, "STRLEN") == 0) {
        // Equivalent to strlen in C
        // Additional code to handle arguments and call strlen
    } else if (strcmp(functionName, "STRCPY") == 0) {
        // Equivalent to strcpy in C
        // Additional code to handle arguments and call strcpy
    } else if (strcmp(functionName, "DIGESTION") == 0) {
        // Equivalent to free in C
        // Additional code to handle arguments and call free
    } else if (strcmp(functionName, "MOUTH") == 0) {
        puts(args); // Directly using puts for simplicity
    } else if (strcmp(functionName, "EYE") == 0) {
        // Equivalent to gets in C
        // Additional code to handle arguments and call gets
    } else if (strcmp(functionName, "MEASURE") == 0) {
        // Equivalent to sizeof in C
        // Additional code to handle arguments and call sizeof
    } else if (strcmp(functionName, "MITOSIS") == 0) {
        // Equivalent to fork in C
        // Additional code to handle arguments and call fork
    } else {
        fprintf(stderr, "Unknown function: %s\n", functionName);
    }
}

// Main entry point for the interpreter
void interpretAST(InterpreterState* state, ASTNode* root) {
    // Assuming ASTNode has a type that denotes a function call
    // and a field for the function name and arguments
    if (root->type == NODE_TYPE_FUNCTION_CALL) {
        executeFunction(root->functionName, root->arguments);
    }
    // Add more interpretation logic as needed for other node types
}

// ... Additional interpreter functions ...
