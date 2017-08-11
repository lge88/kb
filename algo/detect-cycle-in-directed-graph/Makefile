run: detect-cycle-in-directed-graph
	./t-detect-cycle-in-directed-graph

detect-cycle-in-directed-graph: detect-cycle-in-directed-graph.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr detect-cycle-in-directed-graph *.o *.dSYM
