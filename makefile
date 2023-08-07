snake-game.o: main.cpp assets.cpp assets.hpp
	g++ main.cpp assets.cpp -lncurses -o snake-game.o
clean:
	rm snake-game.o
