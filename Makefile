
bin/sort_tester : obj/sort_tester.o obj/sort_lib.o obj/heap_sort.o obj/binary_tree_sort.o
	g++ -o bin/sort_tester obj/sort_tester.o obj/sort_lib.o obj/heap_sort.o obj/binary_tree_sort.o

obj/sort_tester.o : src/sort_tester.cpp
	g++ -c src/sort_tester.cpp -o $@

obj/sort_lib.o : src/sort_lib.c
	gcc -c src/sort_lib.c -o $@

obj/heap_sort.o : src/heap_sort.c
	gcc -c src/heap_sort.c -o $@

obj/binary_tree_sort.o : src/binary_tree_sort.c
	gcc -c src/binary_tree_sort.c -o $@

clean :
	rm -f bin/sort_tester obj/*.o
