#include <stdio.h>
#include <string.h>
#include <omp.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include "file_utils.h"
#include "json_utils.h"
#include "graph_solver.h"
#include "graph_solver_openmp.h"

extern void kernel_wrapper(int numStops, int mask, double **dist, double *memo, int *efficientRoute);

// Define a global flag for debugging
int debug_flag = 0;

void printHelp()
{
    printf("Description: A tool for finding the best path through a graph in a JSON file.\n");
    printf("Usage: jgs [OPTIONS] FILE_PATH\n");
    printf("  --framework   Specify the framework (e.g., OpenMP, CUDA, MPI)\n");
    printf("  -h, --help    Display this help message\n");
    printf("  --debug       Enable debug mode\n");
}

int main(int argc, char *argv[])
{
    char *framework = NULL;
    char *file_path = NULL;

    // Parse command line arguments
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--framework") == 0 && i + 1 < argc)
        {
            framework = argv[i + 1];
            i++; // Skip the next argument as it's the framework value
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            printHelp();
            return 0;
        }
        else if (strcmp(argv[i], "--debug") == 0)
        {
            debug_flag = 1; // Enable debug mode
        }
        else
        {
            // Assuming the last non-flag argument is the file path
            file_path = argv[i];
        }
    }

    // Check if a file path was provided
    if (file_path == NULL)
    {
        printf("Error: Please provide a FILE_PATH.\n");
        printHelp();
        return 1;
    }

    // Load the JSON file

    if (framework)
    {
        printf("Framework: %s\n", framework);
        if (strcmp(framework, "OpenMP") == 0)
        {
            printf("OpenMP mode.\n");

            char *jsonStr = loadFile(file_path);
            if (jsonStr)
            {
                cJSON *root = parseJSON(jsonStr);

                if (root != NULL)
                {
                    int numItems;
                    ItemData *routesArray = parseItems(root, &numItems);

                    if (routesArray != NULL)
                    {
#pragma omp parallel for
                        for (int i = 0; i < numItems; i++)
                        {
                            const char *routeId = routesArray[i].id;
                            cJSON *routeStops = routesArray[i].item;

                            printf("\nID: %s\n", routeId);
                            if (debug_flag)
                            {
                                printf("Route stops: %s\n", cJSON_Print(routeStops));
                                printf("\n");
                            }

                            char **bestRoute = getBestRouteOpenmp(routeStops);
                            printf("Best route: \n");
#pragma omp parallel for
                            for (int i = 0; i < cJSON_GetArraySize(routeStops); i++)
                            {
                                printf("%s ", bestRoute[i]);
                            }
                            printf("\n");
                        }
                        free(routesArray);
                    }

                    cJSON_Delete(root);
                }

                // Don't forget to free the memory when done
                free(jsonStr);
            }
            else
            {
                printf("Error loading the file.\n");
            }
        }
        else if (strcmp(framework, "CUDA") == 0)
        {
            printf("CUDA mode.\n");
            char *jsonStr = loadFile(file_path);
            if (jsonStr)
            {
                cJSON *root = parseJSON(jsonStr);

                if (root != NULL)
                {
                    int numItems;
                    ItemData *routesArray = parseItems(root, &numItems);

                    if (routesArray != NULL)
                    {
                        for (int i = 0; i < numItems; i++)
                        {
                            const char *routeId = routesArray[i].id;
                            cJSON *routeStops = routesArray[i].item;
                            const int numStops = cJSON_GetArraySize(routeStops);

                            printf("\nID: %s\n", routeId);

                            double **dist = getDistanceMatrixOpenmp(routeStops);

                            const int rows = numStops + 1;
                            const int columns = numStops + 1;
                            double **memo = allocateMemoizationTableOpenmp(rows, 1 << columns);
                            int *efficientRoute = (int *)malloc(numStops * sizeof(int));
                            int *efficientRouteIndex = (int *)malloc(sizeof(int));
                            *efficientRouteIndex = 0;

                            for (int i = 0; i < numStops; i++)
                            {
                                efficientRoute[i] = -1;
                            }

                            // call kernel_wrapper for func call
                            kernel_wrapper(numStops, (1 << (numStops + 1)) - 1, dist, *memo, efficientRoute);

                            char **stopsLabels = getStopsLabelsOpenmp(routeStops);
                            char **efficientRouteLabels = (char **)malloc(numStops * sizeof(char *));
                            for (int i = 0; i < numStops; i++)
                            {
                                efficientRouteLabels[i] = '\0';
                            }

                            // get the labels for the efficient route
                            for (int i = 0; i < numStops; i++)
                            {
                                efficientRouteLabels[i] = stopsLabels[efficientRoute[i]];
                                printf("stop %i: %i", i, efficientRoute[i]);
                            }                            

                            // free memory
                            for (int i = 0; i < numStops; i++)
                            {
                                free(dist[i]);
                            }

                            free(dist);
                            // free(stopsLabels);
                            free(efficientRoute);
                            free(efficientRouteIndex);

//                             printf("Best route: \n");
// #pragma omp parallel for
//                             for (int i = 0; i < numStops; i++)
//                             {
//                                 printf("%s ", efficientRouteLabels[i]);
//                             }
//                             printf("\n");
                        }
                        free(routesArray);
                    }

                    cJSON_Delete(root);
                }

                // Don't forget to free the memory when done
                free(jsonStr);
            }
            else if (strcmp(framework, "MPI") == 0)
            {
                printf("MPI mode.\n");
            }
            else
            {
                printf("Invalid framework.\n");
            }
        }
        else
        {
            // Sequential
            printf("No framework specified. Sequential mode.\n");

            char *jsonStr = loadFile(file_path);
            if (jsonStr)
            {
                cJSON *root = parseJSON(jsonStr);

                if (root != NULL)
                {
                    int numItems;
                    ItemData *routesArray = parseItems(root, &numItems);

                    if (routesArray != NULL)
                    {
                        for (int i = 0; i < numItems; i++)
                        {
                            const char *routeId = routesArray[i].id;
                            cJSON *routeStops = routesArray[i].item;

                            printf("\nID: %s\n", routeId);
                            if (debug_flag)
                            {
                                printf("Route stops: %s\n", cJSON_Print(routeStops));
                                printf("\n");
                            }

                            char **bestRoute = getBestRouteSequential(routeStops);
                            printf("Best route: \n");
                            for (int i = 0; i < cJSON_GetArraySize(routeStops); i++)
                            {
                                printf("%s ", bestRoute[i]);
                            }
                            printf("\n");
                        }
                        free(routesArray);
                    }

                    cJSON_Delete(root);
                }

                // Don't forget to free the memory when done
                free(jsonStr);
            }
            else
            {
                printf("Error loading the file.\n");
            }
        }
        printf("File Path: %s\n", file_path);

        return 0;
    }
}