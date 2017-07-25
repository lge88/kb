run: in-struct
	./in-struct

in-struct: in-struct.cc
	g++ -std=c++11 -Wl,-rpath,/home/y/lib64 -g $^ -o $@

clean:
	rm -fr in-struct *.o *.dSYM
