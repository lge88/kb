run: static-link
	./static-link

%.o: %.cc
	g++ -std=c++11 -g $^ -c -o $@

static-link: static-link.o A.o
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr static-link *.o *.dSYM
