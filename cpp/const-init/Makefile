run: init
	./init

init: init.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr init *.o *.dSYM
