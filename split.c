/*
 * CSE 374
 * Homework 6 
 * Denny Ly, Jisoo Jung
 *
 * split.c - Splits a free node block specified by the given memory
 * address into two free node blocks. Then it updates these nodes' fields.
 **/

#include "mem_impl.h"

node * split(node * current, uintptr_t size) {
    uintptr_t headerSize = 2 * sizeof(uintptr_t);
    uintptr_t newSize = current->size - size - headerSize;
    uintptr_t newAddress = ((uintptr_t) current) + headerSize + size;

    node * newCurrent = (node *) newAddress;
    newCurrent->size = newSize;
    newCurrent->next = current->next;

    current->size = size;
    current->next = NULL;

    return newCurrent;
}
