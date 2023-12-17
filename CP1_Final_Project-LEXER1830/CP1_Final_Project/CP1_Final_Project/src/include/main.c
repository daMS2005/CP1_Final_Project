#include "include/lexer.h"
#include "include/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("Enter your code (press ENTER to submit):\n");

    char input[1024]; // Buffer for input; adjust size as needed
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    // Remove newline character if present
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    lexer_T* lexer = init_lexer(input);

    token_T* token = lexer_get_next_token(lexer);
    while (token->type != TOKEN_EOF) {
        // Print token information (for testing)
        printf("Token: %d, Value: %s\n", token->type, token->value);

        // Free the previous token
        free(token->value);
        free(token);

        // Get the next token
        token = lexer_get_next_token(lexer);
    }

    // Clean up (free lexer, last token, etc.)
    free(lexer);

    return 0;
}
