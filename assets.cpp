#include "assets.hpp"
#include <curses.h>
#include <utility>
#include <fstream>

namespace settings {
char SNAKECHAR{'o'};
char FRUITCHAR{'#'};
int maxy{0};
int maxx{0};
int inputChar;
bool GAMEOVER{0};
} // namespace settings

void cursesInit() {
  initscr();
  cbreak();
  curs_set(0);
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
}

void popGameOver() {
  erase();
  mvprintw(settings::maxy / 2, ((settings::maxx / 2) - 9), "GAME_OVER");
  mvprintw(settings::maxy / 2 + 1, ((settings::maxx / 2) - 17),
           "Press any key to exit ...");
  refresh();
}

Position::Position() {
  this->y = (rand() % (settings::maxy - 10) + 5);
  this->x = (rand() % (settings::maxy - 20) + 10);
}

bool Position::operator==(Position &obj) 
{
  return obj.x == this->x && obj.y == this->y;
}

Position::Position(int y, int x) {
  this->y = y;
  this->x = x;
}

Fruit::Fruit() : character(settings::FRUITCHAR), postion() {
}

Fruit::Fruit(Position position) : character(settings::FRUITCHAR) 
{
  this->postion = position;
}

void Fruit::drawFruit() {
  mvprintw(this->postion.y, this->postion.x, "%c", this->character);
}

void Fruit::setRandomPosition() {
    this->postion.y = (rand() % (settings::maxy - 10) + 5);
    this->postion.x = (rand() % (settings::maxx - 20) + 10);
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

bool Snake::collision() {

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

  // screen collision
  if (head()->x < 0 || head()->x >= settings::maxx)
    return true;
  else if (head()->y < 0 || head()->y >= settings::maxy)
    return true;
  return false;
}

Snake::Snake(char bodyCharacter) {
  this->currentDirection = right;
  this->bodyCharacter = bodyCharacter;
  for (int i{4}; i >= 0; i--)
    bodyPositions.push_back(Position(0, i));
}
