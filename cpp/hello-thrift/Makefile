
ranker: ranker.o gen-cpp/libScoringThrift.a
	g++ -L/usr/local/lib -lthrift $^ -o $@

client: client.o gen-cpp/libScoringThrift.a
	g++ -L/usr/local/lib -lthrift $^ -o $@

%.o: %.cc
	g++ -std=c++11 -I./gen-cpp -I/usr/local/include -c $< -o $@
