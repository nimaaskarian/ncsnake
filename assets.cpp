#include "assets.hpp"
#include <curses.h>
#include <utility>
#include <fstream>

namespace global {
Position MAX_POSITION(0,0);
} // namespace settings

void cursesInit() {
  initscr();
  cbreak();
  curs_set(0);
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
}

void popGameOver() {
  erase();
  mvprintw(global::MAX_POSITION.y / 2, ((global::MAX_POSITION.x / 2) - 9), "GAME OVER");
  mvprintw(global::MAX_POSITION.y / 2 + 1, ((global::MAX_POSITION.x / 2) - 17),
           "Press any key to exit ...");
  refresh();
}

Position::Position() {
  this->y = (rand() % (global::MAX_POSITION.y - 10) + 5);
  this->x = (rand() % (global::MAX_POSITION.y - 20) + 10);
}

bool Position::operator==(Position &obj) 
{
  return obj.x == this->x && obj.y == this->y;
}

Position::Position(int y, int x) {
  this->y = y;
  this->x = x;
}

Fruit::Fruit(char character) : character(character), postion() {
}

void Fruit::drawFruit() {
  mvprintw(this->postion.y, this->postion.x, "%c", this->character);
}

void Fruit::setRandomPosition() {
    this->postion.y = (rand() % (global::MAX_POSITION.y - 10) + 5);
    this->postion.x = (rand() % (global::MAX_POSITION.x - 20) + 10);
}

auto Snake::head() 
{
  return bodyPositions.begin();
}

void Snake::drawSnake() {
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

void Snake::growIfFruitEaten(Fruit &fruit)
{
  if (*head() == fruit.postion) {
    fruit.setRandomPosition();
    bodyPositions.insert(head(),nextPosition());
  }

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

void Snake::moveToCurrentDirection() {

  bodyPositions.insert(head(), nextPosition());
  bodyPositions.pop_back();
}

bool Snake::selfCollision() {

  // snake collision
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

Snake::Snake(char bodyCharacter) {
  this->currentDirection = right;
  this->bodyCharacter = bodyCharacter;
  for (int i{4}; i >= 0; i--)
    bodyPositions.push_back(Position(0, i));
}
