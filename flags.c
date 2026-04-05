#include "flags.h"
#include "calculate.h"
#include <getopt.h>
#include <stdio.h>

/* Статические функции */
static void FlagHandler(flag_and_pfram_t *temp);
static void print_help(void);

//____________________________________________________________________________
void FLAGS_FlagAnalysis(int arg, char *argv[]) {
  int32_t rez = 0;
  flag_and_pfram_t temp;

  temp.help = 0;
  temp.intersections = 0;
  temp.iterations = 0;
  temp.area = 0;
  temp.test = 0;

  static struct option long_options[] = {
      {"help", no_argument, 0, 'h'},
      {"intersections", no_argument, 0, 'i'},
      {"iterations", no_argument, 0, 'r'},
      {"area", no_argument, 0, 'a'},
      {"test", no_argument, 0, 't'},       
      {0, 0, 0, 0}
    };

  int option_index = 0;

  while ((rez = getopt_long(arg, argv, "hirat", long_options,
                            &option_index)) != -1) {
    switch (rez) {
      case 'h':
        temp.help = 1;
        break;
      case 'i':
        temp.intersections = 1;
        break;
      case 'r':
        temp.iterations = 1;
        break;
      case 'a':
        temp.area = 1;
        break;
      case 't':
        temp.test = 1;
        break;
    }
  }
  FlagHandler(&temp);
}

static void FlagHandler(flag_and_pfram_t *temp) {
  if (temp->help) {
    print_help();
  }

  if (temp->intersections) {
    int show_iterations = 0;
    CALCULATE_find_all_intersections(show_iterations);
  }

  if (temp->iterations && temp->intersections) {
    int show_iterations = 1;
    CALCULATE_find_all_intersections(show_iterations);
  }

  if (temp->area) {
    CALCULATE_compute_area();
  }

  if (temp->test) {
    printf("  -test\n");
  }
}

/* Вывод справочной информации */
static void print_help(void) {
    printf("Command line options:\n");
    printf("  -help              - display this help message\n");
    printf("  -intersections     - find and print intersection points of curves\n");
    printf("  -iterations        - print number of iterations for root finding\n");
    printf("  -area              - calculate area bounded by curves\n");
    printf("  -test              - run tests for root and integral functions\n");
    printf("\n");
    printf("Combined usage:\n");
    printf("  program -intersections -iterations  # find intersections with iteration count\n");
    printf("  program -area                        # calculate area\n");
    printf("  program -test                        # run tests\n");
}
