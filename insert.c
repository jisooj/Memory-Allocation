/*
 * CSE 374
 * Homework 6 
 * Denny Ly, Jisoo Jung
 *
 * insert.c - inserts the given node to free list such that block
 * addresses are in increasing order.
 **/

#include "mem_impl.h"
#include "mem.h"
#include <assert.h>

void insert(node * newNode) {
  // Sanity check to make sure insert function
  // is not called before the first call to getmem.
  // Also, inserting NULL won't do anything.
  if (!front || !newNode) {
    return;
  }

  uintptr_t newNodeAddress = (uintptr_t) newNode;

  // Given block goes to front of free storage
  if (newNodeAddress < (uintptr_t) front) {
    newNode->next = front;
    front = newNode;
    return;
  }

  // Given block goes to middle of free storage
  node* current = front;
  node* nextNode = front->next;
  while (current && nextNode) {
    if (newNode > current && newNode < nextNode) {
      newNode->next = nextNode;
      current->next = newNode;
      return;
    } else {
      current = nextNode;
      nextNode = nextNode->next;
    }
  }

  // Given block goes to end of the freelist
  current->next = newNode;
  return;
}
