/*
 * CSE 374
 * Homework 6 
 * Denny Ly, Jisoo Jung
 *
 * getmem.c - Returns a pointer to a new block of storage with at least
 * the given size of bytes of memory. Block will be aligned on a 16
 * byte boundary. The given size should be greater than 0. The function
 * will return NULL if the given value is negative or getmem cannot 
 * satisfy the request.
 **/

#include "mem_impl.h"
#include "mem.h"
#include <assert.h>

#define INITIAL_CAPACITY 10000
#define THRESHOLD 96
#define EXTRA_SIZE 100000

void * getmem(uintptr_t size) {
  check_heap();

  if (size <= 0) {
    return NULL;
  }

  uintptr_t headerSize = 2 * sizeof(uintptr_t);
  // Only used for the first call the getmem
  if (!front) {
    // initialize free list with a large block of memory
    uintptr_t requestSize = align(INITIAL_CAPACITY);
    front = (node *) malloc(requestSize);
    front->size = requestSize - headerSize;
    front->next = NULL;
    totalSize += requestSize;
    totalFree += requestSize;
    nFreeBlocks++;
  }

  // front will never be NULL at this point
  assert(front != NULL);

  // Returning too small block will violate
  // heap condition 2 when it's freed later.
  // Make size to be multiple of 16 bytes
  if (size < MIN_SIZE) {
    size = MIN_SIZE;
  }
  size = align(size);
  assert(size % (2 * sizeof(void*)) == 0);

  // front case: spliting the first block
  if (front->size >= size + THRESHOLD + headerSize) {
    node * remainderFront = split(front, size);
    void * userBlock = (void *) (((uintptr_t) front) + headerSize);
    front = remainderFront;
    totalFree -= (size + sizeof(node));
    return userBlock;
  }

  // middle, end case (here, free list has at least one block):
  // spliting the non-first block
  node * prev = front;
  node * current = front->next;
  while (current) {
    if (current->size >= size + THRESHOLD + headerSize) {
      node * remainderFront = split(current, size);
      void * userBlock = (void *) (((uintptr_t) current) + headerSize);
      prev->next = remainderFront;
      totalFree -= (size + sizeof(node));
      return userBlock;
    } else {
      prev = current;
      current = current->next;
    }
  }

  // block with enough size not found in the free list.
  // request a new block with at least the 'size'
  uintptr_t requestSize = align(size + EXTRA_SIZE);
  node * newNode = (node *) malloc(requestSize);
  newNode->size = requestSize - headerSize;
  newNode->next = NULL;
  totalSize += requestSize;
  totalFree += (requestSize - (size + sizeof(node)));
  nFreeBlocks++;

  // end case: malloc
  // 1. newFront = split(newNode, size);
  // 2. insert(newNode);
  // 3. return (void *) ((uintptr_t) newNode + headerSize);
  node * remainderFront = split(newNode, size);
  insert(remainderFront);
  void * userBlock = (void *) (((uintptr_t) newNode) + headerSize);

  check_heap();
  return userBlock;
}

