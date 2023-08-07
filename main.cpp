#include "assets.hpp"

int main(int argc, char *argv[]) {
  srand((unsigned)time(NULL));

  Snake snake(settings::SNAKECHAR);
  Fruit fruit;

  cursesInit();

  while (!settings::GAMEOVER) {
    getmaxyx(stdscr, settings::maxy, settings::maxx);
    erase();

    fruit.drawFruit();
    snake.drawSnake();

    snake.growIfFruitEaten(fruit);

    if (snake.collision()) {
      settings::GAMEOVER = 1;
    }

    // ->
    settings::inputChar = getch();

    switch (settings::inputChar) {
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
      settings::GAMEOVER = 1;
      break;
    }

    snake.moveToCurrentDirection();
    delay_output(1000 / 10);
  }
  popGameOver();
  nodelay(stdscr, FALSE);
  getch();
  nocbreak();
  endwin();
  return 0;
}
