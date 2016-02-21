/*
 * CSE 374
 * Homework 6 
 * Denny Ly, Jisoo Jung
 *
 * check_heap.c - verifies whether the free list has problems or not. 
 * The program terminates if it finds one of the following is false:
 * - Block addresses are in strictly increasing order
 * - Positive block sizes and size at least the minimum size
 * - No overlap in block addresses
 * - Block addresses not touching  
 **/

#include "mem_impl.h"
#include <assert.h>

// global variable needs to be initialized to a constant value
// node * front = (node *) malloc(size); does not work
node * front = NULL;
uintptr_t totalSize = 0;
uintptr_t totalFree = 0;
uintptr_t nFreeBlocks = 0;

void check_heap() {
  uintptr_t headerSize = 2 * sizeof(void *);
  node * current = front;
  while (current && current->next) {
    // Test 1: address in strictly increasing order
    assert(current < current->next);

    // Test 2: positive size at least MIN_SIZE
    assert(current->size > 0);
    assert(current->size >= MIN_SIZE);
    uintptr_t tail_first = (uintptr_t) current + headerSize + current->size;
    uintptr_t head_second = (uintptr_t) current->next;

    // Test 3: No overlap in block addresses
    assert(tail_first < head_second);

    // Test 4: Block addresses not touching
    assert(tail_first != head_second);
    current = current->next;
  }

  // Test 2: end node checking; positive size and at least MIN_SIZE
  if (current) {
    assert(current->size > 0);
    assert(current->size >= MIN_SIZE);
  }
}
