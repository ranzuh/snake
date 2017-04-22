#include <ncurses.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdlib.h>
#include <time.h>

#define MAXWIDTH 79
#define MAXHEIGHT 23

/* checks if key has been hit or not */
int kbhit (void) {
  struct timeval tv;
  fd_set read_fd;

  tv.tv_sec=0;
  tv.tv_usec=0;
  FD_ZERO(&read_fd);
  FD_SET(0,&read_fd);

  if(select(1, &read_fd, NULL, NULL, &tv) == -1)
    return 0;

  if(FD_ISSET(0,&read_fd))
    return 1;

  return 0;
}

/* moves snake one position to the direction provided also controls the speed
   of the game using usleep function
*/
void moveSnake(int* snakeX, int* snakeY, int dirX, int dirY, int speed) {

  int x = *snakeX + dirX;
  int y = *snakeY + dirY;
  *snakeX = x;
  *snakeY = y;
  mvprintw(*snakeY, *snakeX, "S");
  usleep(100000 * speed);

}

/* checks if snake is colliding with walls */
int colliding(int snakeX, int snakeY) {
  if (snakeX < 0 || snakeX > MAXWIDTH+1) {
    return 1;
  }
  else if (snakeY < 0 || snakeY > MAXHEIGHT+1) {
    return 1;
  }
  return 0;
}

/* new random apple location if apple is eaten, if not then prints apple at
   previous location
*/
void letThereBeApple(int* appleX, int* appleY, int *appleEaten) {

  if (*appleEaten) {
    srand(time(0)); //use current time as seed for random generator
    *appleX = (rand() % MAXWIDTH)+1;
    *appleY = (rand() % MAXHEIGHT)+1;
    *appleEaten = 0;
  }

  mvprintw(*appleY, *appleX,"A");

}

/* if snake find apple get one point, also sets appleEaten to true and
   prints score and debug info
*/
void eatApple(int snakeX, int snakeY, int appleX, int appleY,
              int *appleEaten, int *score) {

  if (snakeX == appleX && snakeY == appleY) {
    *appleEaten = 1;
    *score += 1;

  }

  mvprintw(0,0,"score: %d, snakeX: %d, snakeY: %d, appleX: %d, appleY: %d",
           *score, snakeX, snakeY, appleX, appleY);
}

int main() {

  int snakeX = 79;    /* current snake xy position */
  int snakeY = 1;
  int keyPressed = 0; /* which key user pressed */
  int dirX = -1;      /* direction xy */
  int dirY = 0;
  int speed = 1;      /* controls speed of the game, higher values make slower */
  int appleX = 0;     /* current apple xy position */
  int appleY = 0;
  int appleEaten = 1; /* is apple eaten? */
  int score = 0;      /* player score */

  initscr();			/* Start curses mode 		  */
  curs_set(false);
  noecho();

  /* MAIN LOOP */
  while (!colliding(snakeX, snakeY)) {
    erase();

    letThereBeApple(&appleX, &appleY, &appleEaten);
    moveSnake(&snakeX, &snakeY, dirX, dirY, speed);
    eatApple(snakeX, snakeY, appleX, appleY, &appleEaten, &score);


    refresh();

    /* change direction with wasd */
    if (kbhit()) {
      keyPressed = getch();

      if (keyPressed == 'w') {
        dirY = -1;
        dirX = 0;
      }
      if (keyPressed == 's') {
        dirY = 1;
        dirX = 0;
      }
      if (keyPressed == 'a') {
        dirX = -1;
        dirY = 0;
      }
      if (keyPressed == 'd') {
        dirX = 1;
        dirY = 0;
      }
    }


  }
  mvprintw(12,30,"game over!");
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

	return 0;
}
