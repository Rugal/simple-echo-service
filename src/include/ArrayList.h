#ifndef ARRAYLISTH
#define ARRAYLISTH

#include <stdbool.h>

/**
 * Initialization parameter for bootstraping the system.
 */
typedef struct ArrayList ArrayList;

/**
 * Create and initialize an empty ArrayList object.
 */
ArrayList *createArrayList();

/**
 * Free ArrayList memory.
 */
void freeArrayList(ArrayList *c);

/**
 * Add new element at the end of current array.
 * If the current size exceeds the capacity, extends the array.
 */
void add(ArrayList *c, void *data);

/**
 * Remove the element at index, starting from 0.
 */
void removeAt(ArrayList *c, int index);

/**
 * Get the element at index, starting from 0.
 */
void* get(ArrayList *c, int index);

/**
 * Get size of the ArrayList.
 */
int size(ArrayList *c);

/**
 * See if the ArrayList is empty.
 */
bool isEmpty(ArrayList *c);

#endif ARRAYLISTH
