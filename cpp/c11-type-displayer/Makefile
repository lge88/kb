run: c11-type-displayer
	./c11-type-displayer

c11-type-displayer: c11-type-displayer.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr c11-type-displayer *.o *.dSYM
