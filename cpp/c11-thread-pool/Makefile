run: thread-pool
	./thread-pool

thread-pool: *.hh thread-pool.cc
	g++ -std=c++11 -pthread -O3 thread-pool.cc -o $@

clean:
	rm -fr thread-pool *.o *.dSYM
