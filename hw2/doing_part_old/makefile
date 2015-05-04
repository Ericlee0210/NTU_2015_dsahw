target=demo
CPPFLAG= -O3 -std=c++11 -Wall

all: $(target)
 
%: %.cpp
	g++ $(CPPFLAG) $< -o $@
demo: demo.cpp raw_data.cpp raw_data.h func.h func.cpp
	g++ $(CPPFLAG) demo.cpp raw_data.cpp func.cpp -o $@

rundemo:
	./demo spec_10000.txt
clean:
	rm demo
