#ifndef GRAPH_SOLVER_H
#define GRAPH_SOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"
#include "json_utils.h"

typedef struct {
    const char* id;  // ID for this route    
    const char** best_route;  // Best route for this item
    double distance;           // Distance for the best route
} BestRouteData;


char** getStopsLabelsSequential(cJSON* routeData);
double** getDistanceMatrixSequential(cJSON* routeData);
double** allocateMemoizationTableSequential(int rows, int columns);
double fun(int i, int mask, int n, double** dist, double** memo,  int* efficientRoute, int* efficientRouteIndex);
// Function to get the best route that visits all the stops in the given list and starts and ends at the given stop
char** getBestRouteSequential(cJSON* routeData);

#endif // GRAPH_SOLVER_H