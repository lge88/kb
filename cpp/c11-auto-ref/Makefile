run: c11-auto-ref
	./c11-auto-ref

c11-auto-ref: c11-auto-ref.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr c11-auto-ref *.o *.dSYM
