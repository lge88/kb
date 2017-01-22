run: lexical_compare
	./lexical_compare

lexical_compare: lexical_compare.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr lexical_compare *.o *.dSYM
