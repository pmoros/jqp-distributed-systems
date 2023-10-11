#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to display help message
void print_help() {
    printf("Usage: jgs <command> [options] <file_path>\n");
    printf("Commands:\n");
    printf("  describe --levels <n> <file_path> : Describe a file\n");
    printf("  sum <field.subfield> <file_path>  : Calculate the sum\n");
    printf("  mean <field.subfield> <file_path> : Calculate the mean\n");
    printf("  median <field.subfield> <file_path> : Calculate the median\n");
    printf("  count <field.subfield> <file_path> : Count items\n");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Missing command or file path.\n");
        print_help();
        return 1;
    }

    char *command = argv[1];
    const char *file_path = argv[argc - 1];

    if (strcmp(command, "describe") == 0) {
        if (argc != 6 || strcmp(argv[2], "--levels") != 0) {
            printf("Invalid 'describe' command. Use 'jgs describe --levels <n> <file_path>'.\n");
            return 1;
        }
        int levels = atoi(argv[3]);
        // Implement 'describe' logic
        printf("Running 'describe' with levels: %d, file path: %s\n", levels, file_path);
    } else if (strcmp(command, "sum") == 0 || strcmp(command, "mean") == 0 || strcmp(command, "median") == 0 || strcmp(command, "count") == 0) {
        if (argc != 4) {
            printf("Invalid '%s' command. Use 'jgs %s <field.subfield> <file_path>'.\n", command, command);
            return 1;
        }
        const char *field = argv[2];
        // Implement logic for sum, mean, median, and count
        printf("Running '%s' for field: %s, file path: %s\n", command, field, file_path);
    } else {
        printf("Unknown command: %s\n", command);
        print_help();
        return 1;
    }

    return 0;
}
