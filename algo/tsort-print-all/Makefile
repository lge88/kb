run: tsort-print-all
	./tsort-print-all

tsort-print-all: tsort-print-all.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr tsort-print-all *.o *.dSYM
