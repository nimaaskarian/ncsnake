ncsnake.o: main.cpp assets.cpp assets.hpp
	g++ main.cpp assets.cpp -lncurses -o ncsnake.o
clean:
	rm ncsnake.o

install: ncsnake.o
	cp -f ncsnake.o /bin/ncsnake
	chmod 755 /bin/ncsnake
