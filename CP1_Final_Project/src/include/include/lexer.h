#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <stddef.h>


typedef struct LEXER_STRUCT
{
    char c;
    const char* contents;  
    char* src;   // Pointer to the source code
    size_t src_size; // Length of the source code
    size_t i;    // Current position in the source code     // Current character
} lexer_T;



lexer_T* init_lexer(const char* contents);
void lexer_advance(lexer_T* lexer);
void lexer_skip_whitespace(lexer_T* lexer);
token_T* lexer_get_next_token(lexer_T* lexer);
token_T* lexer_collect_number(lexer_T* lexer);
token_T* lexer_collect_string(lexer_T* lexer);
token_T* lexer_collect_id(lexer_T* lexer);
token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token);
char* lexer_get_current_char_as_string(lexer_T* lexer);
void lexer_skip_comment(lexer_T* lexer);
void lexer_skip_multiline_comment(lexer_T* lexer);
char lexer_peek(lexer_T* lexer);



#endif