run: multi-thread-logger
	./multi-thread-logger

multi-thread-logger: multi-thread-logger.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr multi-thread-logger *.o *.dSYM
