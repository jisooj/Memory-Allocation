/*
 * CSE 374
 * Homework 6 
 * Denny Ly, Jisoo Jung
 *
 * mem.h - function prototypes for memory management package
 * public interface package
 **/

#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Returns a pointer to a new block of storage with
// at least the given size of bytes of memory
void * getmem(uintptr_t size);

// Puts the given storage block back to free storage
void freemem(void * p);

// Stores the statistics of the current state
// of the memory manager in the given values. The information
// stored are the number of bytes used by the memory manager, bytes
// in the free list and the number of blocks on the free list
void get_mem_stats(uintptr_t * total_size,
                   uintptr_t * total_free,
                   uintptr_t * n_free_blocks);

// Prints the address and length of each of
// the free blocks currently in our free list
// on to the given file
void print_heap(FILE * f);

#endif
