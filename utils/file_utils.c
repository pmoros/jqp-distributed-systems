// file_utils.c

#include "file_utils.h"
#include <stdlib.h>

char *loadFile(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        return NULL; // File not found or unable to open
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        fclose(file);
        return NULL; // Memory allocation error
    }

    size_t result = fread(buffer, 1, file_size, file);
    if (result != file_size) {
        fclose(file);
        free(buffer);
        return NULL; // Error reading file
    }

    buffer[file_size] = '\0'; // Null-terminate the string

    fclose(file);
    return buffer;
}
