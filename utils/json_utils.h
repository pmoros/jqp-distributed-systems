// json_utils.h

#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include "cJSON.h"

typedef struct {
    const char* id;  // ID for the route
    cJSON* route;    // cJSON object for the route
} RouteData;

// Function to parse JSON data from a string and return a list of dictionaries
cJSON* parseJSON(const char* jsonStr);
// Function to parse all the routes from the root cJSON object and create an array of RouteData structures
RouteData* parseRoutes(cJSON* root, int* numRoutes);


#endif // JSON_UTILS_H
