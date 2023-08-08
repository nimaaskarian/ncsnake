ncsnake.o: main.cpp game.cpp game.hpp
	g++ main.cpp game.cpp -lncurses -o ncsnake.o
clean:
	rm ncsnake.o

install: ncsnake.o
	cp -f ncsnake.o /bin/ncsnake
	chmod 755 /bin/ncsnake
