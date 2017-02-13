run: vector-init-perf
	./vector-init-perf

vector-init-perf: vector-init-perf.cc
	g++ -I../../common -O3 $^ -o $@
	# g++-6 -I../../common -std=c++11 -O3 $^ -o $@
	# g++-6 -I../../common -O3 $^ -o $@
#g++-6 -I../../common -std=c++11 -g $^ -o $@

clean:
	rm -fr vector-init-perf *.o *.dSYM
