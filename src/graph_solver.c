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

double** getDistanceMatrix(cJSON* routeData){
    int numStops = cJSON_GetArraySize(routeData);
    double** distanceMatrix = (double**)malloc(numStops * sizeof(double*));

    cJSON* current = routeData->child;    
    int i = 0;    
    while (current != NULL){
        // create a row for the distance matrix
        distanceMatrix[i] = (double*)malloc(numStops * sizeof(double));
        cJSON* value = current->child;
        int j = 0;
        while(value != NULL){            
            distanceMatrix[i][j] = value->valuedouble;

            j++;
            value = value->next;                    
        }        

        i++;
        current = current->next;        
    }

    return distanceMatrix;
}