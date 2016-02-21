# Homework 6
# Makefile for malloc assignment
# Denny Ly, Jisoo Jung

bench: bench.o check_heap.o print_heap.o get_mem_stats.o freemem.o getmem.o align.o split.o insert.o
	gcc -Wall -g -std=c11 -o bench bench.o check_heap.o print_heap.o get_mem_stats.o freemem.o getmem.o align.o split.o insert.o

bench.o: bench.c mem.h
	gcc -Wall -g -std=c11 -c bench.c

check_heap.o: check_heap.c mem_impl.h 
	gcc -Wall -g -std=c11 -c check_heap.c

print_heap.o: print_heap.c mem.h mem_impl.h 
	gcc -Wall -g -std=c11 -c print_heap.c

get_mem_stats.o: get_mem_stats.c mem.h mem_impl.h 
	gcc -Wall -g -std=c11 -c get_mem_stats.c

freemem.o: freemem.c mem.h mem_impl.h 
	gcc -Wall -g -std=c11 -c freemem.c

getmem.o: getmem.c mem.h mem_impl.h 
	gcc -Wall -g -std=c11 -c getmem.c

align.o: align.c mem_impl.h
	gcc -Wall -g -std=c11 -c align.c

split.o:
	gcc -Wall -g -std=c11 -c split.c

insert.o:
	gcc -Wall -g -std=c11 -c insert.c

clean: 
	rm -f *.o *~ git.log hw6.tar bench

test:
	make
	./bench 10000 50 10 200 20000 1

dist:
	git log > git.log
	tar -cf hw6.tar *.h *.c Makefile git.log README.md

