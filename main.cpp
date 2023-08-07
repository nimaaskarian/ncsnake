#include "assets.hpp"

bool playSnakeAndFruitAndReturnIsOver(Snake &snake, Fruit &fruit);
int main(int argc, char *argv[]) {
  srand((unsigned)time(NULL));

  Snake snake('O');
  Fruit fruit('#');
  bool isSnakeDead = 0;

  cursesInit();

  while (!isSnakeDead) {
    isSnakeDead = playSnakeAndFruitAndReturnIsOver(snake, fruit);
  }
  popGameOver();
  nodelay(stdscr, false);
  getch();
  nocbreak();
  endwin();
  return 0;
}

bool playSnakeAndFruitAndReturnIsOver(Snake &snake, Fruit &fruit)
{
    getmaxyx(stdscr, global::MAX_POSITION.y, global::MAX_POSITION.x);
    erase();

    fruit.drawFruit();
    snake.drawSnake();

    snake.growIfFruitEaten(fruit);

    snake.moveToOtherSideOnEdgeCollision();
    if (snake.selfCollision()) {
      return true;
    }

    switch (getch()) {
    case 'h':
    case KEY_LEFT:
      snake.turn(Direction::left);
      break;
    case 'l':
    case KEY_RIGHT:
      snake.turn(Direction::right);
      break;
    case 'j':
    case KEY_DOWN:
      snake.turn(Direction::down);
      break;
    case 'k':
    case KEY_UP:
      snake.turn(Direction::up);
      break;
    case 'q':
      return true;
    }

    snake.moveToCurrentDirection();
    delay_output(1000 / 10);
  return false;
}
