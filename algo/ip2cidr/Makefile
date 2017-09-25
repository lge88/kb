run: ip2cidr
	./ip2cidr

ip2cidr: ip2cidr.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr ip2cidr *.o *.dSYM
