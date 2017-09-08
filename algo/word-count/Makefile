run: word-count
	./word-count

word-count: word-count.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr word-count *.o *.dSYM
