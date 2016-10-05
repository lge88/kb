run: clrs-heap-sort
	./clrs-heap-sort

clrs-heap-sort: clrs-heap-sort.cc
	g++ -std=c++11 -g $^ -o $@

run-MaxPriorityQueueTest: MaxPriorityQueueTest
	./MaxPriorityQueueTest

MaxPriorityQueueTest: MaxPriorityQueue.hh MaxPriorityQueueTest.cc
	g++ -std=c++11 -I../ -g MaxPriorityQueueTest.cc -o $@

clean:
	rm -fr clrs-heap-sort *.o *.dSYM
