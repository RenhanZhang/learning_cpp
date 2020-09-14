objects = singleton_test.o

.PHONY: run
run: main
	./main

main: $(objects)
	g++ -o main $(objects)

singleton_test.o: singleton.h  singleton_test.cc
	g++ -c singleton_test.cc

.PHONY: clean
clean:
	rm run $(objects)