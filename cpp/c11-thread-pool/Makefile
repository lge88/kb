run: thread-pool
	./thread-pool

thread-pool: ThreadPool.hh Queue.hh thread-pool.cc
	g++ -std=c++11 -pthread -g $^ -o $@

clean:
	rm -fr thread-pool *.o *.dSYM
