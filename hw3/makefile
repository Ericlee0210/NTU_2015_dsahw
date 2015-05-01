target=3_4_1 3_4_2
CPPFLAG= -O3 -std=c++11 -Wall

all: $(target)

%: %.cpp
	g++ $(CPPFLAG) $< -o $@
3_4_1: 3_4_1.cpp 3_4_1_func.cpp 3_4_1_func.h 3_4_1_container.h
	g++ $(CPPFLAG) 3_4_1.cpp 3_4_1_func.cpp -o $@
3_4_2: 3_4_2.cpp 3_4_2_func.cpp 3_4_2_func.h 3_4_2_container.h
	g++ $(CPPFLAG) 3_4_2.cpp 3_4_2_func.cpp -o $@

run1:
	./3_4_1
run2:
	./3_4_2
clean:
	rm 3_4_1 3_4_2
	
