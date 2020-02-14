#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "ArrayList.h"

#define DEFAULT_ARRAY_LENGTH 8

struct ArrayList
{
  void **array;
  int size;
  int capacity;
};

ArrayList *createArrayList()
{
  ArrayList *l = malloc(sizeof(ArrayList));
  l->capacity = DEFAULT_ARRAY_LENGTH;
  l->size = 0;
  l->array = malloc(l->capacity * sizeof(void *));
  bzero(l->array, sizeof(l->capacity * sizeof(void *)));
  return l;
}

void freeArrayList(ArrayList *c)
{
  assert(c != NULL);
  for (int i = c->size - 1; i >= 0; --i)
  {
    remove(c, i);
  }
  free(c->array);
  free(c);
}

static void *extend(ArrayList *c)
{
  assert(c != NULL);
  c->capacity *= 2;
  void **newArray = malloc(c->capacity * sizeof(void *));
  for (int i = 0; i < c->size; ++i)
  {
    newArray[i] = c->array[i];
  }
  free(c->array);
  c->array = newArray;
}

void add(ArrayList *c, void *data)
{
  assert(c != NULL);
  if (c->size >= c->capacity)
  {
    extend(c);
  }
  c->array[c->size++] = data;
}

void removeAt(ArrayList *c, int index)
{
  assert(c != NULL);
  assert(index >= 0 && index < c->size);
  for (int i = index; i < c->size; ++i)
  {
    c->array[i] = c->array[i + 1];
  }
  c->array[--c->size] = NULL;
}

void *get(ArrayList *c, int index)
{
  assert(c != NULL);
  assert(index >= 0 && index < c->size);
  return c->array[index];
}

int size(ArrayList *c)
{
  assert(c != NULL);
  return c->size;
}

bool isEmpty(ArrayList *c)
{
  assert(c != NULL);
  return c->size == 0;
}