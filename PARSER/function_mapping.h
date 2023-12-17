#ifndef FUNCTION_MAPPING_H
#define FUNCTION_MAPPING_H

// Define a structure for mapping EVA function names to standard C function names
typedef struct {
    char* evaName;  // Name in EVA language
    char* cName;    // Corresponding standard C function name
} FunctionMapping;

// Array of function mappings
static const FunctionMapping functionMappings[] = {
    {"MALLOC", "malloc"},
    {"PRINTF", "printf"},
    {"SCANF", "scanf"},
    {"STRLEN", "strlen"},
    {"STRCPY", "strcpy"},
    {"DIGESTION", "free"},
    {"MOUTH", "puts"},
    {"EYE", "gets"},
    {"MEASURE", "sizeof"},
    {"MITOSIS", "fork"}
    // Add other mappings as needed
};

#endif // FUNCTION_MAPPING_H
