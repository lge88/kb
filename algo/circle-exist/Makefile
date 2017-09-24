run: circle-exist
	./circle-exist

circle-exist: circle-exist.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr circle-exist *.o *.dSYM
