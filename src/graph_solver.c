#include "graph_solver.h"

#define MAX_STOPS 10


BestRouteData* getBestRoute(cJSON* routeData){
    // Get the departure stop
    ItemData* departureStop = getDepartureStop(routeData);
    if (departureStop == NULL) {
        return NULL;
    }
}