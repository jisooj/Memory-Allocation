/*
 * CSE 374
 * Homework 6 
 * Denny Ly, Jisoo Jung
 *
 * print_heap.c - Prints the address and length of each of
 * the free blocks currently in our free list on to the
 * given file.
 **/

#include "mem_impl.h"
#include "mem.h"

void print_heap(FILE * f) {
  node * current = front;
  while (current) {
    uintptr_t address = (uintptr_t) current;
    fprintf(f, "Address: %lu, Size: %lu\n", address, current->size);
    current = current->next;
  }
}
