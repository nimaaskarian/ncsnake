snake-game.o: main.cpp assets.cpp assets.hpp
	g++ main.cpp assets.cpp -lncurses -o snake-game.o
clean:
	rm snake-game.o

install: snake-game.o
	cp -f snake-game.o /bin/snake-game
	chmod 755 /bin/snake-game
