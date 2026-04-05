#include <math.h>
#include <stdio.h>
#include "integral.h"
#include "test.h"
#include "root.h"

/* Тестирование функций root и integral */
void RUN_run_tests(void) {
  double eps = 1e-6;
  int iters;
  double result;

  printf("\n=== Testing functions ===\n");

  /* Тест 1: root - поиск корня x^2 - 4 = 0 */
  printf("\nTest 1: Find root of equation x^2 - 4 = 0 on [1, 3]\n");
  double test_f(double x) { return x * x; }
  double test_g(double x) {
    (void)x;
    return 4.0;
  }
  double test_df(double x) { return 2.0 * x; }
  double test_dg(double x) {
    (void)x;
    return 0.0;
  }

  result = ROOT_root(test_f, test_g, 1.0, 3.0, test_df, test_dg, eps, &iters);
  printf("  Root: %.10f (expected 2.0)\n", result);
  printf("  Iterations: %d\n", iters);

  if (fabs(result - 2.0) < eps) {
    printf("  Test passed\n");
  } else {
    printf("  Test failed\n");
  }

  /* Тест 2: integral - интегрирование x^2 от 0 до 2 */
  printf("\nTest 2: Integrate x^2 from 0 to 2 (expected 8/3 = 2.66666667)\n");
  double square(double x) { return x * x; }

  result = INTEGRAL_integral(square, 0.0, 2.0, eps);
  printf("  Result: %.10f\n", result);

  if (fabs(result - 8.0 / 3.0) < eps) {
    printf("  Test passed\n");
  } else {
    printf("  Test failed\n");
  }

  /* Тест 3: integral - интегрирование sin(x) от 0 до π */
  printf("\nTest 3: Integrate sin(x) from 0 to pi (expected 2.0)\n");
  double sine(double x) { return sin(x); }

  result = INTEGRAL_integral(sine, 0.0, M_PI, eps);
  printf("  Result: %.10f\n", result);

  if (fabs(result - 2.0) < 1e-4) {
    printf("  Test passed\n");
  } else {
    printf("  Test failed\n");
  }

  printf("\nAll tests completed.\n");
}