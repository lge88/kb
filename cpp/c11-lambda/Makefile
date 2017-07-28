run: lambda
	./lambda

lambda: lambda.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr lambda *.o *.dSYM
