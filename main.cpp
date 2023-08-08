#include "game.hpp"

unsigned int numberLength(int n, int base=10);
bool playSnakeAndFruitAndReturnIsOver(Snake &snake, Fruit &fruit);
void cursesInit();
void popGameOver();

int main(int argc, char *argv[]) {
  srand((unsigned)time(NULL));
  int fruitCount;

  Snake snake('O');
  Fruit fruit('#');
  bool isSnakeDead = false;

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
    getmaxyx(stdscr, game::maxPosition.y, game::maxPosition.x);
    erase();

    fruit.drawFruit();
    snake.drawSnake();

    if (snake.hasReachedFruit(fruit)) {
      snake.addToHead();
      fruit.setRandomPosition();
      game::score++;
    }

    snake.moveToOtherSideOnEdgeCollision();
    if (snake.selfCollision()) {
      return true;
    }

    switch (getch()) {
    case 'h':
    case 'a':
    case KEY_LEFT:
      snake.turn(Direction::left);
      break;
    case 'l':
    case 'd':
    case KEY_RIGHT:
      snake.turn(Direction::right);
      break;
    case 'j':
    case 's':
    case KEY_DOWN:
      snake.turn(Direction::down);
      break;
    case 'k':
    case 'w':
    case KEY_UP:
      snake.turn(Direction::up);
      break;
    case 'q':
      return true;
    }

    snake.moveToCurrentDirection();
    delay_output(1000 / (10 * game::velocity));
  return false;
}

void cursesInit() 
{
  initscr();
  cbreak();
  curs_set(0);
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
}

void popGameOver() 
{
  erase();
  Position gameOverPosition(game::maxPosition.y/2, game::maxPosition.x/2);

  mvprintw(gameOverPosition.y, gameOverPosition.x - 4, "GAME OVER");
  mvprintw(gameOverPosition.y+2,gameOverPosition.x - 3 - numberLength(game::score)/2,
           "Score: %d", game::score);

  mvprintw(gameOverPosition.y+1,gameOverPosition.x - 12,
           "Press any key to exit ...");
  refresh();
}

unsigned int numberLength(int n, int base)
{
  unsigned int length = 0;
  do {
       ++length; 
       n /= base;
  } while (n);

  return length;
}
