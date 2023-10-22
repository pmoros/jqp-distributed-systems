#ifndef GRAPH_SOLVER_H
#define GRAPH_SOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include "json_utils.h"

typedef struct {
    const char* id;  // ID for this route    
    const char** best_route;  // Best route for this item
    double distance;           // Distance for the best route
} BestRouteData;


char** getStopsLabels(cJSON* routeData);
double** getDistanceMatrix(cJSON* routeData);
// Function to get the best route that visits all the stops in the given list and starts and ends at the given stop
BestRouteData* getBestRoute(cJSON* routeData);

#endif // GRAPH_SOLVER_H