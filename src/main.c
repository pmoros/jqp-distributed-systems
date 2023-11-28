#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utils.h"
#include "json_utils.h"
#include "graph_solver.h"

int main(int argc, char *argv[])
{
    char *file_path = argv[1];
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

                MPI_Init(NULL, NULL);

                // Get the number of processes
                int world_size;
                MPI_Comm_size(MPI_COMM_WORLD, &world_size);

                printf("world size: %i", world_size);

                // Get the rank of the process
                int world_rank;
                MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

                // Broadcast the total number of items to all processes
                MPI_Bcast(&numItems, 1, MPI_INT, 0, MPI_COMM_WORLD);

                // Calculate the number of items each process will handle
                int items_per_process = numItems / world_size;
                int remainder = numItems % world_size;

                int start_index = world_rank * items_per_process;
                int end_index = (world_rank + 1) * items_per_process + (world_rank == world_size - 1 ? remainder : 0);


                for (int i = start_index; i < end_index; i++)
                {
                    const char *routeId = routesArray[i].id;
                    cJSON *routeStops = routesArray[i].item;

                    printf("Process %d - ID: %s\n", world_rank, routeId);

                    char **bestRoute = getBestRouteSequential(routeStops);
                    printf("Best route: \n");
                    for (int i = 0; i < cJSON_GetArraySize(routeStops); i++)
                    {
                        printf("%s ", bestRoute[i]);
                    }
                    printf("\n");
                }

                MPI_Finalize();

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