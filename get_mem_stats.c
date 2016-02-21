/*
 * CSE 374
 * Homework 6 
 * Denny Ly, Jisoo Jung
 *
 * get_mem_stats.c - Stores the statistics of the current state
 * of the memory manager in the given values. The information
 * stored are the number of bytes used by the memory manager, bytes
 * in the free list and the number of blocks on the free list.
 **/

#include "mem_impl.h"
#include "mem.h"

void get_mem_stats(uintptr_t * total_size,
                   uintptr_t * total_free,
                   uintptr_t * n_free_blocks) {
  *total_size = totalSize;
  *total_free = totalFree;
  *n_free_blocks = nFreeBlocks;
}
