run: http-rank
	./http-rank

http-rank: http-rank.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr http-rank *.o *.dSYM
