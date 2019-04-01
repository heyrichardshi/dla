all:
	g++ -o dla dla.cpp main.cpp -std=c++11
clean: 
	$(RM) dla
