#include "graph_solver.h"

#define MAX 999999

double min(double a, double b) {
    return (a < b) ? a : b;
}

BestRouteData* getBestRoute(cJSON* routeData){        
    const int numStops = cJSON_GetArraySize(routeData);
    double** dist = getDistanceMatrix(routeData);

    const int rows = numStops + 1;
    const int columns = 1 << (numStops + 1);
    double** memo = allocateMemoizationTable(rows, columns);
    
    double ans = MAX;
    for (int i = 0; i < numStops; i++){
        // try to go from node 1 visiting all nodes in
        // between to i then return from i taking the
        // shortest route to 1        
        printf("Mask initial %d\n", (1 << (numStops + 1)) - 1);
        ans = min(ans, fun(i, (1 << (numStops + 1)) - 1, numStops, dist, memo) + dist[i][0]);        
        }
 
    printf("The cost of most efficient tour = %lf\n", ans);
 
    free(memo);

    return 0;    

}


double fun(int i, int mask, int n, double** dist, double** memo)
{
    // base case
    // if only ith bit and 1st bit is set in our mask,
    // it implies we have visited all other nodes already
    if (mask == ((1 << i) | 15)){
        printf("aaa %lf\n", dist[1][i]);
        return dist[1][i];
    }
    // memoization
    if (memo[i][mask] != 0)
        return memo[i][mask];
 
    double res = MAX; // result of this sub-problem
 
    // we have to travel all nodes j in mask and end the
    // path at ith node so for every node j in mask,
    // recursively calculate cost of travelling all nodes in
    // mask except i and then travel back from node j to
    // node i taking the shortest path take the minimum of
    // all possible j nodes
 
    for (int j = 0; j < n; j++)
        if ((mask & (1 << j)) && j != i && j != 1){
        
            res = min(res, fun(j, mask & (~(1 << i)), n, dist, memo)
                                    + dist[i][j]);

            printf("%lf ", res);

            }
        
    return memo[i][mask] = res;
}

double** allocateMemoizationTable(int rows, int columns){
    double** memo = (double**)malloc(rows * sizeof(double*));
    if (memo == NULL) {
        // Handle memory allocation failure
        exit(1);  // You can choose an appropriate error handling mechanism
    }

    // Allocate memory for each row (an array of ints)
    for (int i = 0; i < rows; i++) {
        memo[i] = (double *)malloc(columns * sizeof(double));
        if (memo[i] == NULL) {
            // Handle memory allocation failure
            exit(1);  // You can choose an appropriate error handling mechanism
        }
        for (int j = 0; j < columns; j++) {
            memo[i][j] = 0; // Initialize memoization table with -1            
        }        
    }
    
    return memo;
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