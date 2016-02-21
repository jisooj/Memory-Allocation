/**
 * CSE 374
 * Homework 6
 * Denny Ly, Jisoo Jung
 *
 * align.c - rounds up the given address such that it's divisible by 16.
 **/

#include "mem_impl.h"

uintptr_t align(uintptr_t address) {
  uintptr_t boundary = 2 * sizeof(uintptr_t);
  if (address % boundary == 0) {
    return address;
  } else {
    return address + (boundary - address % boundary);
  }
}
