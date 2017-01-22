run: lru-cache
	./lru-cache

lru-cache: lru-cache.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr lru-cache *.o *.dSYM
