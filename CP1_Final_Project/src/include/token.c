#include "include/token.h"
#include <stdlib.h>
#include <string.h> 

token_T* init_token(token_type_t type, const char* value)
{
    token_T* token = calloc(1, sizeof(struct TOKEN_STRUCT));
    token->type = type;
    token->value = strdup(value); // Duplicate the string

    return token;
}
