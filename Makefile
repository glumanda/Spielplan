spielplan2: main.o konstellationen.o spielplan2.o
	g++ main.o konstellationen.o spielplan2.o -o spielplan2
spielplan: main.o konstellationen.o spielplan.o
	g++ main.o konstellationen.o spielplan.o -o spielplan
spielplan3: main.o konstellationen.o spielplan3.o
	g++ main.o konstellationen.o spielplan3.o -o spielplan3
main.o: main.cpp spielplan.hpp spielplan2.hpp spielplan3.hpp
	g++ -c main.cpp
konstellation.o: konstellationen.cpp konstellationen.hpp 
	g++ -c konstellationen.cpp
spielplan.o: spielplan.cpp spielplan.hpp konstellationen.hpp
	g++ -c spielplan.cpp
spielplan2.o: spielplan2.cpp spielplan2.hpp konstellationen.hpp
	g++ -c spielplan2.cpp
spielplan3.o: spielplan3.cpp spielplan3.hpp konstellationen.hpp
	g++ -c spielplan3.cpp
clean:
	rm *.o spielplan spielplan2 spielplan3