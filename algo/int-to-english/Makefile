run: int-to-english
	./int-to-english

int-to-english: int-to-english.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr int-to-english *.o *.dSYM
