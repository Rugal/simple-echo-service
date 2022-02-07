#ifndef ASYNCHRONIZATIONH
#define ASYNCHRONIZATIONH

#include <poll.h>
#include <stdbool.h>

typedef struct {
  struct pollfd* fds;
  int size;
  int capacity;
} FileDescriptorPool;

/**
 * @brief Create a File Descriptor Pool object, initialize it with given capacity and 0 start size
 * 
 * @param capacity initial capacity, will auto extend if size growing
 * @return FileDescriptorPool* the created object
 */
FileDescriptorPool* createFileDescriptorPool(int capacity);

/**
 * @brief Free File Descriptor Pool object safely
 * 
 * @param pool the pool object that is not nullable
 */
void freeFileDescriptorPool(FileDescriptorPool* pool);

/**
 * @brief Add new FileDescriptor into the pool
 * 
 * @param pool target FDP object to add to
 * @param fd the FileDescriptor to add
 * @return struct pollfd* The added element
 */
struct pollfd* addToPool(FileDescriptorPool* pool, int fd);

/**
 * @brief Remove element at index in pool
 * 
 * @param pool Target FDP object
 * @param index the index at element to remove from
 * @return bool true
 */
bool removeFromPool(FileDescriptorPool* pool, int index);

#endif ASYNCHRONIZATIONH
