run: custom-allocator
	./custom-allocator

custom-allocator: custom-allocator.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr custom-allocator *.o *.dSYM
