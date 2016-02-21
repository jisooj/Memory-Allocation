/*
 * CSE 374
 * Homework 6 
 * Denny Ly, Jisoo Jung
 *
 * mem_impl.h - function prototypes for memory management package 
 * private interface package.
 **/

#ifndef MEM_IMPL_H
#define MEM_IMPL_H

#include <stdint.h>
#include <stdlib.h>

#define MIN_SIZE 96

// Rename free_node to node
typedef struct free_node node;

// node definition that holds its block size
// and a reference to the next block
struct free_node {
  uintptr_t size;
  struct free_node* next;
};

// Front of the freelist
extern node * front;

// Status of the memory manager
extern uintptr_t totalSize;
extern uintptr_t totalFree;
extern uintptr_t nFreeBlocks;

/* 
 * Verifies whether the free list has problems or not. 
 * The program terminates if it finds one of the following is false:
 * - Block addresses are in strictly increasing order
 * - Positive block sizes and size at least the minimum size
 * - No overlap in block addresses
 * - Block addresses not touching
 */
void check_heap();

// Rounds up the given address to address that's multiple of 16 bytes.
uintptr_t align(uintptr_t address);

// Splits a free node block specified by the given memory address into
// two free node blocks. Then it updates these nodes' fields.
node * split(node * current, uintptr_t size);

// Inserts the given node to free list such that block addresses
// are in increasing order.
void insert(node * newNode);

#endif
