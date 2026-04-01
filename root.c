#include "root.h"
#include <math.h>
#include <stdio.h>

/* 
 * Функция для вычисления значения h(x) = f(x) - g(x)
 */
static double h(func_t f, func_t g, double x) {
    return f(x) - g(x);
}

/* 
 * Функция для вычисления производной h'(x) = f'(x) - g'(x)
 */
static double dh(deriv_t df, deriv_t dg, double x) {
    return df(x) - dg(x);
}

/*
 * Комбинированный метод (метод хорд + метод Ньютона)
 */
double root(func_t f, func_t g, double a, double b,
           deriv_t df, deriv_t dg, double eps, int *iterations) {
    double ha, hb;
    double x_chord, x_newton, x_new;
    double chord_diff, newton_diff;
    int iter = 0;
    int max_iter = 1000;
    
    /* Вычисляем значения функции на концах отрезка */
    ha = h(f, g, a);
    hb = h(f, g, b);
    
    /* Проверяем, что на концах отрезка функция имеет разные знаки */
    if (ha * hb >= 0) {
        fprintf(stderr, "Error: No root or even number of roots on interval [%f, %f]\n", a, b);
        fprintf(stderr, "  h(a)=%f, h(b)=%f\n", ha, hb);
        *iterations = -1;
        return 0.0;
    }
    
    /* Выбор начальных приближений */
    if (ha < 0) {
        x_chord = b;
        x_newton = a;
    } else {
        x_chord = a;
        x_newton = b;
    }
    
    *iterations = 0;
    x_new = (a + b) / 2.0;
    
    do {
        iter++;
        
        /* Шаг метода хорд */
        double fa = h(f, g, x_chord);
        double fb = h(f, g, x_newton);
        if (fabs(fb - fa) > 1e-12) {
            x_chord = x_newton - fb * (x_newton - x_chord) / (fb - fa);
        }
        
        /* Шаг метода Ньютона */
        double dh_val = dh(df, dg, x_newton);
        if (fabs(dh_val) > 1e-12) {
            x_newton = x_newton - h(f, g, x_newton) / dh_val;
        }
        
        /* Новое приближение - среднее арифметическое */
        x_new = (x_chord + x_newton) / 2.0;
        
        /* Проверка на выход за пределы отрезка */
        if (x_new < a || x_new > b) {
            x_new = (a + b) / 2.0;
        }
        
        /* Критерий останова */
        chord_diff = fabs(x_new - x_newton);
        newton_diff = fabs(x_new - x_chord);
        
        x_chord = x_new;
        x_newton = x_new;
        
        if (iter > max_iter) {
            fprintf(stderr, "Warning: Maximum iterations reached\n");
            break;
        }
        
    } while ((chord_diff > eps || newton_diff > eps) && iter < max_iter);
    
    *iterations = iter;
    return x_new;
}