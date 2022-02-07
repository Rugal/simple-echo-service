#include <assert.h>
#include <poll.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Asynchronization.h"
#include "log4c.h"

FileDescriptorPool* createFileDescriptorPool(int capacity)
{
  assert(capacity > 0);
  FileDescriptorPool* pool = malloc(sizeof(FileDescriptorPool));
  assert(NULL != pool);
  bzero(pool, sizeof(FileDescriptorPool));
  pool->capacity = capacity;
  pool->size = 0;
  pool->fds = malloc(pool->capacity * sizeof(struct pollfd));
  assert(NULL != pool->fds);
  bzero(pool->fds, pool->capacity * sizeof(struct pollfd));
  return pool;
}

void freeFileDescriptorPool(FileDescriptorPool* pool)
{
  assert(NULL != pool);
  assert(NULL != pool->fds);
  free(pool->fds);
  pool->fds = NULL;
  free(pool);
}

struct pollfd* addToPool(FileDescriptorPool* pool, int fd)
{
  assert(NULL != pool);
  if (pool->size >= pool->capacity) {
    pool->capacity *= 2;
    LOG_TRACE("Extend capacity to [%d]", pool->capacity);
    pool->fds = realloc(pool->fds, pool->capacity * sizeof(struct pollfd));
  }
  // if enough size
  LOG_DEBUG("Add new FD into pool [%d]", fd);
  struct pollfd* current = pool->fds + pool->size;
  bzero(current, sizeof(struct pollfd));
  current->fd = fd;
  LOG_DEBUG("Pool size is [%d]", ++pool->size);
  return current;
}

bool removeFromPool(FileDescriptorPool* pool, int index)
{
  assert(NULL != pool);
  struct pollfd current = pool->fds[index];
  pool->fds[index] = pool->fds[--(pool->size)];
  LOG_DEBUG("Remove FD [%d@%d] from pool", current.fd, index);
  LOG_DEBUG("Pool size is [%d]", pool->size);
  return true;
}
