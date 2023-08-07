#pragma once

#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <vector>

enum Direction {up = 1, right, down ,left};


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

namespace global {
extern Position MAX_POSITION;
} // namespace settings

class Fruit {
private:
  Position postion;
  char character;
  friend class Snake;

public:
  Fruit(char);
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
  void moveToOtherSideOnEdgeCollision();
  void initSnake();
  void drawSnake();
  void turn(Direction);
  void moveToCurrentDirection();
  bool selfCollision();
  void growIfFruitEaten(Fruit &);
};
