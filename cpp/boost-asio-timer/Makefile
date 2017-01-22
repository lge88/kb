run: asio-timer
	./asio-timer

asio-timer: asio-timer.cc
	g++ -std=c++11 -lboost_system -g -Wall -Werror $^ -o $@

clean:
	rm -fr asio-timer *.o *.dSYM
