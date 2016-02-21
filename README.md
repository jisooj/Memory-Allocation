# CSE 374 Homework 6 : Memory Management 
## Denny Ly, Jisoo Jung

## Contributions
  Jisoo worked on:
    getmem.c, check_heap.c, mem.h, print_heap.c, bench.c, Makefile

  Denny worked on:
    freemem.c, get_mem_stats.c, mem_impl.h, bench.c, Makefile

## Heap List
  Heap list is organized in ascending order based on addresses of the header of the blocks. None of the blocks in the list are touching each other. The header of the blocks consist of a size and a pointer to the next block in the list.

  When getmem() is called, the program traverses through the list from the front and until there is a block size big enough for the requested amount. The chosen block should also have enough memory leftover to be greater than the defined threshold in the program. Once the block is chosen, the user shall receive the top of the block and the leftover memory stays in the free storage. If no block is big enough, the program will get a big enough block from the underlying system. The block will then be cut into two pieces, the user gets the top section and the leftover bottom section of the block will be placed back into the free storage. The location of the new block will depend on the address.

  When freemem() is called, the program traverses through the free storage until the location of the given block is discovered based off of its address. The function will then determine if the given block needs to be concatenated with the adjacent blocks by looking if the address of the given block is continuous with the two adjacent blocks. If no concatenation needs to be done, the block is just inserted into the list at that location.

## Additional Features
  Current implementation is a simplified version of memory management without neat optimizations. It has the following features:

  - getmem always starts scanning the free list from the beginning when it is looking for a block of suitable size
  - each block in the free list only contains header. No footer is added to optimize free operation.


## Summary of Results
  CPU TIME is generally around .004 seconds when running 10000 trials. The amount of bytes used from the underlying system is generally around 280000 bytes for every run.

## Summary of Resources
  Didn't look at online resources to implement getmem() and freemem(). Used information taught in class to make this program.
