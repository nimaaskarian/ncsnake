#include <ncurses.h>
#include <utility>

#include "game.hpp"

#define SNAKE_INITIAL_BODY 4

namespace game {
  Position maxPosition(0,0);
  unsigned int velocity = 2;
  unsigned int score = 0;
} 

Position::Position(int y, int x) 
{
  this->y = y;
  this->x = x;
}

Position Position::random()
{
  Position p;
  p.y = (rand() % (game::maxPosition.y - 10) + 5);
  p.x = (rand() % (game::maxPosition.x - 20) + 10);

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
  for (auto it = head()+1; it < bodyPositions.end(); it++) {
    if (*it == *head())
      return true;
  }
  return false;
}

void Snake::moveToOtherSideOnEdgeCollision()
{
  if (head()->x < 0) {
    head()->x = game::maxPosition.x;
    return;
  }
  if (head()->x >= game::maxPosition.x) {
    head()->x = 0;
    return;
  }

  if (head()->y < 0) {
    head()->y = game::maxPosition.y;
    return;
  }
  if (head()->y >= game::maxPosition.y) {
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
