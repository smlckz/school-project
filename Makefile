# a Makefile for my school project
# use GNU make to build it 

EXES = poly array-stack array-queue sllist-stack sllist-queue

all: $(EXES)

poly: poly.c

array-stack.c sllist-stack.c: stack.h common.h ;
array-queue.c sllist-queue.c: queue.h common.h ;

array-stack: array-stack.c stack.c
array-queue: array-queue.c queue.c
sllist-stack: sllist-stack.c stack.c
sllist-queue: sllist-queue.c queue.c

gen: $(EXES) 
	for F in $(EXES) ; do \
		./$$F >$$F.out.txt ; \
	done

test: $(EXES)
	for F in $(EXES) ; do \
		./$$F | diff -q ./$$F.out.txt - || exit 1 ; \
	done

clean:
	rm -f *.o
	rm -f $(EXES)

