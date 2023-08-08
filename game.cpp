#include <curses.h>
#include <utility>

#include "game.hpp"

#define SNAKE_INITIAL_BODY 4

Position::Position(int y, int x) 
{
  this->y = y;
  this->x = x;
}

Position Position::random()
{
  Position p;
  p.y = (rand() % (global::MAX_POSITION.y - 10) + 5);
  p.x = (rand() % (global::MAX_POSITION.x - 20) + 10);

  return p;
}

bool Position::operator==(Position &obj) 
{
  return obj.x == this->x && obj.y == this->y;
}

Fruit::Fruit(char character)
{
  this->character = character;
  this->position = Position::random();
}

void Fruit::drawFruit() 
{
  mvprintw(this->position.y, this->position.x, "%c", this->character);
}

void Fruit::setRandomPosition() 
{
  this->position = Position::random();
}

std::vector<Position>::iterator Snake::head() 
{
  return bodyPositions.begin();
}

void Snake::drawSnake() 
{
  for (auto &t : bodyPositions) {
    mvprintw(t.y, t.x, "%c", bodyCharacter);
  }
  refresh();
}

void Snake::turn(Direction direction)
{
  int directionDifference = abs(direction-currentDirection);
  // up, right, down, left
  // 1 , 2    , 3   , 4
  if (directionDifference != 2)
    currentDirection = direction;
}

void Snake::addToHead()
{
  bodyPositions.insert(head(),nextPosition());
}

bool Snake::hasReachedFruit(Fruit &fruit)
{
  if (*head() == fruit.position) 
    return true;
  
  return false;
}

Position Snake::nextPosition()
{
  Position nextPosition(head()->y, head()->x);
  switch (currentDirection) {
  case right:
    nextPosition.x++;
    break;
  case left:
    nextPosition.x--;
    break;
  case up:
    nextPosition.y--;
    break;
  case down:
    nextPosition.y++;
    break;
  }
  return nextPosition;
}

void Snake::moveToCurrentDirection() 
{
  addToHead();
  bodyPositions.pop_back();
}

bool Snake::selfCollision() 
{
  int index = 0;
  for (auto position : bodyPositions) {
    int subindex = 0;
    for (auto subPosition : bodyPositions) {
      if (subindex != index && position == subPosition)
        return true;
      subindex++;
    }
    index++;
  }
  return false;
}

void Snake::moveToOtherSideOnEdgeCollision()
{
  if (head()->x < 0) {
    head()->x = global::MAX_POSITION.x;
    return;
  }
  if (head()->x >= global::MAX_POSITION.x) {
    head()->x = 0;
    return;
  }

  if (head()->y < 0) {
    head()->y = global::MAX_POSITION.y;
    return;
  }
  if (head()->y >= global::MAX_POSITION.y) {
    head()->y = 0;
    return;
  }
}

Snake::Snake(char bodyCharacter) 
{
  this->currentDirection = right;
  this->bodyCharacter = bodyCharacter;
  for (int i{SNAKE_INITIAL_BODY}; i >= 0; i--)
    bodyPositions.push_back(Position(0, i));
}
