#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#define MAX_COLUNAS 500

char caracteres[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#@$%";


int main() {
  initscr();
  noecho();
  curs_set(FALSE);
  nodelay(stdscr, TRUE);
  
  if (has_colors()) {
    start_color();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    init_pair(2, COLOR_WHITE, COLOR_BLACK);
  }

  int linhas, colunas;
  getmaxyx(stdscr, linhas, colunas);

  int pos_y[MAX_COLUNAS];
  for (int i = 0; i < colunas; i++) {
    pos_y[i] = rand() % linhas;
  }

  char caracteres[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#@$%";
  int qtd_caracteres = strlen(caracteres);

  while (getch() == ERR) {
    getmaxyx(stdscr, linhas, colunas);

    for (int x = 0; x < colunas; x++) {
      char c = caracteres[rand() % qtd_caracteres];
      attron(COLOR_PAIR(2));
      mvaddch(pos_y[x], x, c);
      attroff(COLOR_PAIR(2));

      if (pos_y[x] > 0) {
        attron(COLOR_PAIR(1));
        mvaddch(pos_y[x] - 1, x, caracteres[rand() % qtd_caracteres]);
        attroff(COLOR_PAIR(1));
      }

      int rastro = pos_y[x] - (rand() % 15 + 5);
      if (rastro >= 0) {
        mvaddch(rastro, x, ' ');
      }

      pos_y[x]++;

      if (pos_y[x] >= linhas) {
        pos_y[x] = 0;
      }
    }
    refresh();
    usleep(50000);
  }

  endwin();

  return 0;
}
