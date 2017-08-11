run: tsort
	./tsort <data/00.in

tsort: tsort.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr tsort *.o *.dSYM
