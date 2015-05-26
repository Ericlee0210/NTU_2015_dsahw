CPPFLAG= -O1 -std=c++11 -Wall

all: $(target)

system: system.cpp binomial_heap.h
	g++ $(CPPFLAG) system.cpp -o $@

run:
	./system

clean:
	rm system
