/*
 * CSE 374
 * Homework 6 
 * Denny Ly, Jisoo Jung
 *
 * bench.c - test bench program for memory management package. 
 * bench randomly calls getmem and freemem many times to allocate
 * and free random sizes. Takes command-line argument for 
 * various parameters and performs default behavior if there's none.
 *
 * Synopsis: 
 * bench [ntrials [pctget [pctlarge [small_limit [large_limit [random_seed]]]]]]
 * - ntrials: number of getmem + freemem calls
 * - pctget: getmem/freemem ratio to be called. 
 *   e.g. 30 may have 3 calls to getmem and 7 calls to freemem
 * - pctlarge: percent to call large memory blocks
 * - small_limit: largest size of a small block - in bytes
 * - large_limit: largest size of a large block - in bytes
 * - random_seed: initial seed value for random number generator
 **/

#include "mem.h"
#include <time.h>

int main(int argc, char * argv[]) {
  int args[] = {10000, 50, 10, 200, 20000, time(NULL)};
  for (int i = 0; i < argc - 1; i++) {
    args[i] = atoi(argv[i + 1]);
  }

  srand(args[5]);
  double time_passed;
  int prob;
  int total_ptr = 0;
  int oneTenth = args[0] / 10;
  uintptr_t stat0 = 0;
  uintptr_t stat1 = 0;
  uintptr_t stat2 = 0;
  uintptr_t* total_size = &stat0;
  uintptr_t* total_free = &stat1;
  uintptr_t* n_free_blocks = &stat2;
  clock_t start = clock();
  void ** ptrList = (void **) malloc(args[0] * sizeof(void *));

  for (int i = 0; i < args[0]; i++) {
    if (i % oneTenth == 0 && i != 0) {
      printf("    %d percent done\n", i / oneTenth * 10);
      get_mem_stats(total_size, total_free, n_free_blocks);
      time_passed = ((double) (clock() - start)) / CLOCKS_PER_SEC;
      printf("    CPU TIME: %f seconds\n", time_passed);
      printf("    %lu bytes used by underlying system\n", stat0);
      printf("    %lu blocks on the free list\n", stat2);
      if (stat2 != 0) {
        printf("    Average of %lu bytes per free block\n\n", stat1 / stat2);
      } else {
        printf("    Average of 0 bytes per free block\n\n");
      }
    }
    prob = rand() % 100;
    if (prob < args[1]) {  // getmem
      prob = rand() % 100;
      uintptr_t requestSize;
      if (prob < args[2]) {
        requestSize = (uintptr_t) (rand() % (args[4] - args[3]) + args[3]);
      } else {
        requestSize = (uintptr_t) (rand() % args[3]);
      }
      ptrList[total_ptr] = getmem(requestSize);
      total_ptr++;
    } else {  // freemem
      if (total_ptr > 0) {
        int index = rand() % total_ptr;
        freemem(ptrList[index]);
        ptrList[index] = ptrList[total_ptr - 1];
        total_ptr--;
      }
    }
  }
  printf("    100 percent done\n");
  get_mem_stats(total_size, total_free, n_free_blocks);
  time_passed = ((double) (clock() - start)) / CLOCKS_PER_SEC;
  printf("    CPU TIME: %f seconds\n", time_passed);
  printf("    %lu bytes used by underlying system\n", stat0);
  printf("    %lu blocks on the free list\n", stat2);
  if (stat2 != 0) {
    printf("    Average of %lu bytes per free block\n\n", stat1 / stat2);
  } else {
    printf("    Average of 0 bytes per free block\n\n");
  }
  printf("All tests passed\n");
  free(ptrList);
  return EXIT_SUCCESS;
}
