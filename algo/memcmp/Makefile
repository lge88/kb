run: memcmp
	./memcmp

memcmp: memcmp.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr memcmp *.o *.dSYM
