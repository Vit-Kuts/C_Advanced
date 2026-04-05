#include "integral.h"

#include <math.h>
#include <stdio.h>

/*
 * Метод Симпсона (парабол) для численного интегрирования
 * Использует адаптивное разбиение для достижения заданной точности
 */
double integral(func_t f, double a, double b, double eps) {
  int n = 2; /* Начальное количество подотрезков */
  double I_old, I_new;
  double h, sum;
  int i;
  int max_iterations = 1000000;

  /* Первое приближение по формуле Симпсона с 2 подотрезками */
  h = (b - a) / 2.0;
  I_old = (h / 3.0) * (f(a) + 4.0 * f(a + h) + f(b));

  do {
    n *= 2;
    h = (b - a) / n;

    /* Суммирование значений в нечётных точках */
    sum = 0.0;
    for (i = 1; i < n; i += 2) {
      sum += f(a + i * h);
    }

    /* Формула Симпсона для нечётных точек */
    I_new = (h / 3.0) * (f(a) + f(b) + 4.0 * sum);

    /* Добавление чётных точек (кроме первой и последней) */
    sum = 0.0;
    for (i = 2; i < n - 1; i += 2) {
      sum += f(a + i * h);
    }
    I_new += (h / 3.0) * 2.0 * sum;

    /* Проверка достижения точности */
    if (fabs(I_new - I_old) < eps) {
      break;
    }

    I_old = I_new;

  } while (n < max_iterations);

  return I_new;
}