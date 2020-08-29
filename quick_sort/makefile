objects = quick_sort_test.o quick_sort.o

.PHONY: run
run: main
	./main

main: $(objects)
	g++ -o main $(objects)

quick_sort_test.o: quick_sort.h  quick_sort_test.cc
	g++ -c quick_sort_test.cc

quick_sort.o: quick_sort.cc
	g++ -c quick_sort.cc

.PHONY: clean
clean:
	rm run $(objects)