// json_utils.h

#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include "cJSON.h"

typedef struct {
    const char* id;  // ID for the item
    cJSON* item;      // cJSON object for the item
} ItemData;

// Function to parse JSON data from a string and return a list of dictionaries
cJSON* parseJSON(const char* jsonStr);
// Function to parse all the items from the root cJSON object and create an array of ItemData structures
ItemData* parseItems(cJSON* root, int* numItems);


#endif // JSON_UTILS_H
