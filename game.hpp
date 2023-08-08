#ifndef GAME_HPP
#define GAME_HPP

#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <vector>

enum Direction {up = 1, right, down ,left};

class Position {
public:
  Position(int=0, int=0);
  bool operator ==(Position &);
  static Position random();
  int y;
  int x;
};

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

namespace game {
extern Position maxPosition;
extern unsigned int velocity;
extern unsigned int score;
}
#endif
