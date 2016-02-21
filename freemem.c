/*
 * CSE 374
 * Homework 6 
 * Denny Ly, Jisoo Jung
 *
 * freemem.c - Puts the given storage block back to free storage. 
 * freemem will not do anything if the pointer p equals to NULL
 *
 * preconditions:
 * - p must be one of the values acquried from getmem
 * - there's no expected behavior if p has already been freed
 *   or if p is not a storage block from getmem (might crash)
 **/

#include "mem_impl.h"
#include "mem.h"

void freemem(void* p) {
  check_heap();
  if (p) {
    node* prev = NULL;
    node* current = front;
    node* given = (node*) ((uintptr_t) p - sizeof(node));
    node* end_block = (node*) ((uintptr_t) given + given->size + sizeof(node));

    // Updates total number of bytes inside the free list
    totalFree += given->size + sizeof(node);

    // Traverses through the FreeList
    while (current && (end_block > current)) {
      prev = current;
      current = current->next;
    }

    // Currently looking at the beginning of free storage
    if (prev == NULL) {
      if (end_block == front) {  // Merge w/ first block in storage
        given->next = front->next;
        given->size = given->size + front->size + sizeof(node);
      } else {  // Insert block to the beginning of storage
        given->next = front;
        nFreeBlocks++;
      }
      front = given;
      return;
    }

    // Acquires the address of the next adjacent block
    node* end_last_block = (node*) ((uintptr_t) prev
                                    + prev->size
                                    + sizeof(node));

    // Currently looking at the end of free storage
    if (current == NULL) {  // Insert to the end of free storage
      prev->next = given;
      given->next = NULL;
      nFreeBlocks++;
      return;
    }

    // Currently looking inside of free storage
    if (end_block == current && given == end_last_block) {
      // Connect to the two adjacent blocks
      prev->size = prev->size + given->size + current->size + 32;
      prev->next = current->next;
      nFreeBlocks--;
    } else if (given == end_last_block) {
      // Connect to bottom of the left block
      prev->size = prev->size + given->size + 16;
    } else if (end_block == current) {
      // Connect to top of the right block
      given->next = current->next;
      prev->next = given;
      given->size = given->size + current->size + 16;
    } else {  // Insert block in the middle of the two adjacent blocks
      given->next = current;
      prev->next = given;
      nFreeBlocks++;
    }
  }
  check_heap();
}
