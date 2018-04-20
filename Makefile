
sort_tester : sort_tester.o sort_lib.o heap_sort.o binary_tree_sort.o
	g++ -o sort_tester sort_tester.o sort_lib.o heap_sort.o binary_tree_sort.o

sort_tester.o : sort_tester.cpp
	g++ -c sort_tester.cpp

sort_lib.o : sort_lib.c
	gcc -c sort_lib.c

heap_sort.o : heap_sort.c
	gcc -c heap_sort.c

binary_tree_sort.o : binary_tree_sort.c
	gcc -c binary_tree_sort.c

clean :
	rm -f sort_tester *.o
