run: page-splitter
	./page-splitter

page-splitter: page-splitter.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr page-splitter *.o *.dSYM
