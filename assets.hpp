#pragma once

#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <vector>

enum Direction {up = 1, right, down ,left};

namespace settings {
extern char SNAKECHAR;
extern char FRUITCHAR;
extern int maxy, maxx;
extern bool GAMEOVER;
extern int inputChar;
} // namespace settings

void cursesInit();
void popGameOver();

class Position {
public:
  Position();
  Position(int, int);
  bool operator ==(Position &);
  void randomPos();
  int y;
  int x;
};

class Fruit {
private:
  Position postion;
  char character;
  friend class Snake;

public:
  Fruit();
  Fruit(Position);
  void drawFruit();
  void setRandomPosition();
};
class Snake {
public:
  char bodyCharacter;
  std::vector<Position> bodyPositions;
  Direction currentDirection;
  Snake(char );
  auto head();
  Position nextPosition();
  void initSnake();
  void drawSnake();
  void turn(Direction);
  void moveToCurrentDirection();
  bool collision();
  void growIfFruitEaten(Fruit &);
};
