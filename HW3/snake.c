#include <curses.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MIN_Y 2
#define INFO_Y 0        // Строка с информацией
#define SCORE_Y 1       // Строка со счётом
#define GAME_START_Y 2  // Начало игрового поля

enum { LEFT = 1, UP, RIGHT, DOWN, STOP_GAME = KEY_F(10) };
enum {
  MAX_TAIL_SIZE = 100,
  START_TAIL_SIZE = 3,
  MAX_FOOD_SIZE = 20,
  FOOD_EXPIRE_SECONDS = 10
};

// Здесь храним коды управления змейкой
struct control_buttons {
  int down;
  int up;
  int left;
  int right;
} control_buttons;

struct control_buttons default_controls = {KEY_DOWN, KEY_UP, KEY_LEFT,
                                           KEY_RIGHT};

typedef struct food {
  int x;
  int y;
  time_t put_time;
  char point;
  uint8_t enable;
} food_t;

/*
 Голова змейки содержит в себе
 x,y - координаты текущей позиции
 direction - направление движения
 tsize - размер хвоста
 *tail -  ссылка на хвост
 */

typedef struct snake_t {
  int x;
  int y;
  int direction;
  size_t tsize;
  struct tail_t *tail;
  struct control_buttons controls;
} snake_t;

typedef struct tail_t {
  int x;
  int y;
} tail_t;

void initTail(struct tail_t t[], size_t size) {
  struct tail_t init_t = {0, 0};
  for (size_t i = 0; i < size; i++) {
    t[i] = init_t;
  }
}

void initHead(struct snake_t *head, int x, int y) {
  head->x = x;
  head->y = y;
  head->direction = RIGHT;
}

void initSnake(snake_t *head, size_t size, int x, int y) {
  tail_t *tail = (tail_t *)malloc(MAX_TAIL_SIZE * sizeof(tail_t));
  initTail(tail, MAX_TAIL_SIZE);
  initHead(head, x, y);
  head->tail = tail;  // прикрепляем к голове хвост
  head->tsize = size;
  head->controls = default_controls;
}

//  Движение головы с учетом текущего направления движения
void go(struct snake_t *head) {
  char ch = '@';
  int max_x = 0, max_y = 0;
  getmaxyx(stdscr, max_y, max_x);
  mvprintw(head->y, head->x, " ");
  switch (head->direction) {
    case LEFT:
      if (head->x <= 0) head->x = max_x;
      mvprintw(head->y, --(head->x), "%c", ch);
      break;
    case RIGHT:
      if (head->x >= max_x - 1) head->x = 0;
      mvprintw(head->y, ++(head->x), "%c", ch);
      break;
    case UP:
      if (head->y <= GAME_START_Y) head->y = max_y - 1;
      mvprintw(--(head->y), head->x, "%c", ch);
      break;
    case DOWN:
      if (head->y >= max_y - 1) head->y = GAME_START_Y;
      mvprintw(++(head->y), head->x, "%c", ch);
      break;
    default:
      break;
  }
  refresh();
}

void changeDirection(struct snake_t *snake, const int32_t key) {
  if (key == snake->controls.down)
    snake->direction = DOWN;
  else if (key == snake->controls.up)
    snake->direction = UP;
  else if (key == snake->controls.right)
    snake->direction = RIGHT;
  else if (key == snake->controls.left)
    snake->direction = LEFT;
}

//  Движение хвоста с учетом движения головы
void goTail(struct snake_t *head) {
  char ch = '*';
  mvprintw(head->tail[head->tsize - 1].y, head->tail[head->tsize - 1].x, " ");
  for (size_t i = head->tsize - 1; i > 0; i--) {
    head->tail[i] = head->tail[i - 1];
    if (head->tail[i].y || head->tail[i].x)
      mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
  }
  head->tail[0].x = head->x;
  head->tail[0].y = head->y;
}

//  Проверка на столкновение головы с хвостом
int checkCollision(snake_t *head) {
  for (size_t i = 1; i < head->tsize; i++) {
    if (head->tail[i].x == head->x && head->tail[i].y == head->y) {
      return 1;  // Столкновение с хвостом
    }
  }
  return 0;
}

//  Проверка на поедание еды
int checkFood(snake_t *head, food_t *food) {
  if (head->x == food->x && head->y == food->y) {
    return 1;
  }
  return 0;
}

//  Увеличение длины змейки
void snakeEat(snake_t *head) { head->tsize++; }

//  Инициализация еды
void initFood(food_t *f, int max_x, int max_y) {
  int is_free = 0;

  while (!is_free) {
    f->x = rand() % (max_x - 2) + 1;
    f->y = rand() % (max_y - GAME_START_Y - 1) + GAME_START_Y + 1;
    f->put_time = time(NULL);
    f->point = '$';
    f->enable = 1;
    is_free = 1;
  }
}

//  Обновление еды
void updateFood(food_t *food, snake_t *snake, int max_x, int max_y,
                int *score) {
  time_t now = time(NULL);
  if (now - food->put_time > FOOD_EXPIRE_SECONDS) {
    // Стираем старую еду с экрана
    mvprintw(food->y, food->x, " ");
    initFood(food, max_x, max_y);
  }

  // Проверяем, съедена ли еда
  if (checkFood(snake, food)) {
    snakeEat(snake);
    (*score)++;
    // Стираем съеденную еду с экрана
    mvprintw(food->y, food->x, " ");
    initFood(food, max_x, max_y);
  }

  // Отображаем еду
  if (food->enable) {
    mvprintw(food->y, food->x, "%c", food->point);
  }
}

int main() {
  snake_t *snake = (snake_t *)malloc(sizeof(snake_t));
  initSnake(snake, START_TAIL_SIZE, 10, 10);

  initscr();
  keypad(stdscr, TRUE);
  raw();
  noecho();
  curs_set(FALSE);

  int max_x = 0, max_y = 0;
  getmaxyx(stdscr, max_y, max_x);

  // Инициализация еды
  srand(time(NULL));
  food_t food;
  initFood(&food, max_x, max_y);

  mvprintw(INFO_Y, 1, "Use arrows for control. Press 'F10' for EXIT");

  timeout(0);
  int key_pressed = 0;
  int score = 0;

  while (key_pressed != STOP_GAME) {
    key_pressed = getch();
    go(snake);
    goTail(snake);

    // Обновляем еду и проверяем поедание
    updateFood(&food, snake, max_x, max_y, &score);

    // Отображаем текущий счёт
    mvprintw(SCORE_Y, 1, "Score: %d   ", score);

    // Проверка на столкновение с самой собой
    if (checkCollision(snake)) {
      clear();
      mvprintw(max_y / 2, (max_x - 9) / 2, "GAME OVER");
      mvprintw(max_y / 2 + 1, (max_x - 15) / 2, "Final score: %d", score);
      mvprintw(max_y / 2 + 2, (max_x - 23) / 2, "Press any key to exit");
      refresh();
      timeout(-1);
      getch();
      break;
    }

    timeout(100);
    changeDirection(snake, key_pressed);
  }

  free(snake->tail);
  free(snake);
  endwin();
  return 0;
}