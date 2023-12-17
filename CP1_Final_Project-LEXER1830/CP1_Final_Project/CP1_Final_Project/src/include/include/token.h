#ifndef TOKEN_H
#define TOKEN_H

// Enumeration for different token types
typedef enum {
    TOKEN_ID,          // Identifier
    TOKEN_EQUALS,      // =
    TOKEN_DOUBLE_EQ,   // ==
    TOKEN_NOT_EQ,      // !=
    TOKEN_LESS,        // <
    TOKEN_GREATER,     // >
    TOKEN_LESS_EQ,     // <=
    TOKEN_GREATER_EQ,  // >=
    TOKEN_PLUS,        // +
    TOKEN_MINUS,       // -
    TOKEN_ASTERISK,    // *
    TOKEN_SLASH,       // /
    TOKEN_PERCENT,     // %
    TOKEN_INT,         // Integer literal
    TOKEN_FLOAT,       // Float literal
    TOKEN_STRING,      // String literal
    TOKEN_SEMI,        // ;
    TOKEN_LPAREN,      // (
    TOKEN_RPAREN,      // )
    TOKEN_LBRACE,      // {
    TOKEN_RBRACE,      // }
    TOKEN_COMMA,       // ,
    TOKEN_DOT,         // .
    TOKEN_COLON,       // :
    TOKEN_AMP,         // &
    TOKEN_PIPE,        // |
    TOKEN_CARET,       // ^
    TOKEN_TILDE,       // ~
    TOKEN_QUESTION,    // ?
    TOKEN_EOF, 
    TOKEN_NUMBER,        // End-of-file
    TOKEN_DIGESTION,
    TOKEN_MOUTH,
    TOKEN_EYE,
    TOKEN_MEASURE,
    TOKEN_MITOSIS,
    TOKEN_NUMBER,
    // Add other token types as necessary
} token_type_t;

// Structure for a token
typedef struct TOKEN_STRUCT {
    token_type_t type; // The type of the token
    char* value;       // The value of the token (e.g., the actual string for an identifier)
} token_T;

// Function to initialize a new token
token_T* init_token(token_type_t type, const char* value);

#endif // TOKEN_H
