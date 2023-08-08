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
  Position(int=0, int=0);
  bool operator ==(Position &);
  static Position random();
  int y;
  int x;
};

namespace global {
extern Position MAX_POSITION;
extern unsigned int velocity;
extern unsigned int score;
} // namespace settings

class Fruit {
private:
  Position position;
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
  std::vector<Position>::iterator head();
  Position nextPosition();
  void addToHead();
  void moveToOtherSideOnEdgeCollision();
  void initSnake();
  void drawSnake();
  void turn(Direction);
  void moveToCurrentDirection();
  bool selfCollision();
  bool hasReachedFruit(Fruit &);
};
