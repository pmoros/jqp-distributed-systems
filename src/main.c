#include <stdio.h>
#include <string.h>
#include "file_utils.h"
#include "json_utils.h"

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

    // Load the JSON file

    if (framework) {
        printf("Framework: %s\n", framework);
    } else {
        // sequential
        printf("No framework specified. Sequential mode.\n");

        char *jsonStr = loadFile(file_path);
        if (jsonStr) {
            // Use the file content
            printf("File content:\n%s\n", jsonStr);
            
            cJSON* root = parseJSON(jsonStr);
            
            if (root != NULL) {
                int numItems;
                ItemData* itemArray = parseItems(root, &numItems);

            if (itemArray != NULL) {
                for (int i = 0; i < numItems; i++) {
                    const char* id = itemArray[i].id;
                    cJSON* item = itemArray[i].item;

                    printf("ID: %s\n", id);
                    printf("Item: %s\n", cJSON_Print(item));
                    // Process the ID and item cJSON object
                    // Example: cJSON_Print(item) to print the item JSON
                }
                free(itemArray);
            }

                cJSON_Delete(root);
            }

            
            // Don't forget to free the memory when done
            free(jsonStr);
        } else {
            printf("Error loading the file.\n");
        }
        
    }
    printf("File Path: %s\n", file_path);     



    return 0;
}
