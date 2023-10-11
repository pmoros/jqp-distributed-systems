// json_utils.c

#include "json_utils.h"
#include "cJSON.h"

cJSON* parseJSON(const char* jsonStr) {
    cJSON* root = cJSON_Parse(jsonStr);
    if (root == NULL) {
        return NULL; // JSON parsing error
    }

    return root; // Return the root cJSON object
}

// json_utils.c

RouteData* parseRoutes(cJSON* root, int* numRoutes) {
    if (!cJSON_IsObject(root)) {
        return NULL; // The root object is not as expected
    }

    int count = cJSON_GetArraySize(root);
    if (count == 0) {
        *numRoutes = 0;
        return NULL; // No routes found
    }

    RouteData* routeArray = (RouteData*)malloc(count * sizeof(RouteData));
    if (routeArray == NULL) {
        *numRoutes = 0;
        return NULL; // Memory allocation error
    }

    cJSON* currentRoute = root->child;
    int i = 0;
    while (currentRoute != NULL) {
        routeArray[i].id = currentRoute->string; // Get the ID
        routeArray[i].route = currentRoute; // Get the cJSON object for the route
        i++;
        currentRoute = currentRoute->next;
    }

    *numRoutes = count;
    return routeArray;
}

