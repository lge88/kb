run: hardware
	./hardware

hardware: hardware.cc
	g++ -lboost_thread-mt -g $^ -o $@

clean:
	rm -fr hardware *.o *.dSYM
