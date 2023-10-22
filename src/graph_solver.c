#include "graph_solver.h"

#define MAX_STOPS 10


BestRouteData* getBestRoute(cJSON* routeData){
    return -1;        
}

char** getStopsLabels(cJSON* routeData){
    int numStops = cJSON_GetArraySize(routeData);
    char** stopsLabels = (char**)malloc(numStops * sizeof(char*));

    cJSON* current = routeData->child;    
    int i = 0;    
    while (current != NULL){
        char* key = current->string;
        stopsLabels[i] = key;
        current = current->next;
        i++;
    }

    return stopsLabels;
}