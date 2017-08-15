run: partition
	./partition

partition: partition.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr partition *.o *.dSYM
