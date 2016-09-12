test: GraphTest
	./GraphTest

GraphTest: GraphTest.cc *.hh
	g++ -std=c++11 -I../ -g GraphTest.cc -o $@

run: clrs-graph-template-v1
	./clrs-graph-template-v1

clrs-graph-template-v1: clrs-graph-template-v1.cc *.hh
	g++ -std=c++11 clrs-graph-template-v1.cc -o $@

clean:
	rm clrs-graph-template-v1 *.o
