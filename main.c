#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flags.h"

/* Функция ожидания нажатия клавиши в Windows */
void wait_for_keypress(void) {
  printf("\nPress Enter to exit...");
  getchar();
}

int main(int argc, char *argv[]) {
  FLAGS_FlagAnalysis(argc, argv);
  wait_for_keypress();
  return 0;
}