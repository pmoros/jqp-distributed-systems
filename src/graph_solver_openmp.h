#ifndef GRAPH_SOLVER_OPENMP_H
#define GRAPH_SOLVER_OPENMP_H

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"
#include "json_utils.h"

char** getStopsLabelsOpenmp(cJSON* routeData);
double** getDistanceMatrixOpenmp(cJSON* routeData);
double** allocateMemoizationTableOpenmp(int rows, int columns);
double funOpenmp(int i, int mask, int n, double** dist, double** memo,  int* efficientRoute, int* efficientRouteIndex);
// funOpenmpction to get the best route that visits all the stops in the given list and starts and ends at the given stop
char** getBestRouteOpenmp(cJSON* routeData);

#endif // GRAPH_SOLVER_OPENMP_H