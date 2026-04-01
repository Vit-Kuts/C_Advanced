#ifndef INTEGRAL_H
#define INTEGRAL_H

/* 
 * Тип указателя на функцию одной переменной
 */
typedef double (*func_t)(double x);

/*
 * Функция вычисления определённого интеграла методом Симпсона
 * 
 * Параметры:
 *   f - интегрируемая функция
 *   a, b - пределы интегрирования
 *   eps - требуемая точность
 * 
 * Возвращает:
 *   приближенное значение интеграла
 */
double integral(func_t f, double a, double b, double eps);

#endif /* INTEGRAL_H */