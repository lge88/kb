run: consistent-hashing
	./consistent-hashing

consistent-hashing: consistent-hashing.cc ConsistentHashPlanner.hh UserStore.hh
	g++ -std=c++11 -lsqlite3 -g $< -o $@

clean:
	rm -fr consistent-hashing *.o *.dSYM
