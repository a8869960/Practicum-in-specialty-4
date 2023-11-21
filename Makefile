FLAGS=-O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format -c

all: main.o functions.o other_functions.o
	g++ -pthread main.o functions.o other_functions.o

main.o: main.cpp functions.h
	g++ $(FLAGS) main.cpp

functions.o: functions.cpp functions.h
	g++ $(FLAGS) functions.cpp

other_functions.o: other_functions.cpp
	g++ $(FLAGS) other_functions.cpp

clean:
	rm -f *.o *.out