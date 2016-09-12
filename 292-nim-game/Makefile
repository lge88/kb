run: nim-game
	./nim-game

nim-game: nim-game.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm nim-game *.o
