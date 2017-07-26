all: client server

client: client.cc Msg.hh
	g++ -std=c++11 -g $^ -o $@

server: server.cc Msg.hh
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr client server *.o *.dSYM
