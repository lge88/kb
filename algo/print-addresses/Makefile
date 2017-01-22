run: print-addresses
	./print-addresses

print-addresses: print-addresses.cc
	g++-6 -std=c++11 -g $^ -o $@

clean:
	rm -fr print-addresses *.o *.dSYM
