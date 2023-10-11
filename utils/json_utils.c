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


ItemData* parseItems(cJSON* root, int* numItems) {
    if (!cJSON_IsObject(root)) {
        return NULL; // The root object is not as expected
    }

    int count = cJSON_GetArraySize(root);
    if (count == 0) {
        *numItems = 0;
        return NULL; // No items found
    }

    ItemData* itemArray = (ItemData*)malloc(count * sizeof(ItemData));
    if (itemArray == NULL) {
        *numItems = 0;
        return NULL; // Memory allocation error
    }

    cJSON* currentItem = root->child;
    int i = 0;
    while (currentItem != NULL) {
        itemArray[i].id = currentItem->string; // Get the ID
        itemArray[i].item = currentItem; // Get the cJSON object for the item
        i++;
        currentItem = currentItem->next;
    }

    *numItems = count;
    return itemArray;
}


