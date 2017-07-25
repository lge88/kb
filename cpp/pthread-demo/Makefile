run: demo
	./demo

demo: demo.cc
	g++ -std=c++11 -g -pthread $^ -o $@

clean:
	rm -fr demo *.o *.dSYM
