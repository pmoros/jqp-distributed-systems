#include <stdio.h>
#include <string.h>

void printHelp() {
    printf("Description: A tool for finding the best path through a graph in a JSON file.\n");
    printf("Usage: jgs [OPTIONS] FILE_PATH\n");    
    printf("  --framework   Specify the framework (e.g., OpenMP, CUDA, MPI)\n");
    printf("  -h, --help    Display this help message\n");
}

int main(int argc, char *argv[]) {
    char *framework = NULL;
    char *file_path = NULL;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--framework") == 0 && i + 1 < argc) {
            framework = argv[i + 1];
            i++; // Skip the next argument as it's the framework value
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printHelp();
            return 0;
        } else {
            // Assuming the last non-flag argument is the file path
            file_path = argv[i];
        }
    }

    // Check if a file path was provided
    if (file_path == NULL) {
        printf("Error: Please provide a FILE_PATH.\n");
        printHelp();
        return 1;
    }

    // Your code to use the 'framework' and 'file_path' variables goes here

    if (framework) {
        printf("Framework: %s\n", framework);
    } else {
        printf("No framework specified.\n");
    }
    printf("File Path: %s\n", file_path);

    return 0;
}
