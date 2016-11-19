run: tail
	./tail

tail: tail.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr tail *.o *.dSYM
