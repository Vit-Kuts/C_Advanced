#ifndef FLAGS_H_
#define FLAGS_H_

#include <stdbool.h>
#include <stdint.h>

/* Структура для установки флагов */
typedef struct {
  int help;
  int intersections;
  int iterations;
  int area;
  int test;
} flag_and_pfram_t;

void FLAGS_FlagAnalysis(int arg, char *argv[]);
#endif /*FLAGS_H_*/