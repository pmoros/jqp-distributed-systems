#ifndef GRAPH_SOLVER_H
#define GRAPH_SOLVER_H

#include "json_utils.h"

typedef struct {
    const char* id;  // ID for this route    
    const char** best_route;  // Best route for this item
    double distance;           // Distance for the best route
} BestRouteData;


ItemData* getDepartureStop(cJSON* routeData);

#endif // GRAPH_SOLVER_H