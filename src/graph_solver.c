#include "graph_solver.h"


ItemData* getDepartureStop(cJSON* routeData) {
    // Return the first stop in the route
    cJSON* departureStop = routeData->child;
    if (departureStop == NULL) {
        return NULL;
    }
    else {
        ItemData* itemData = (ItemData*)malloc(sizeof(ItemData));
        if (itemData == NULL) {
            return NULL;
        }

        itemData->id = departureStop->string;
        itemData->item = departureStop;
        return itemData;
    }
}