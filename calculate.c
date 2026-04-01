#include "calculate.h"
#include "integral.h"
#include "root.h"

/* Глобальная переменная для подсчёта вызовов функций (для тестирования) */
static int function_calls = 0;

/* Заданные функции */
double f1(double x) {
    function_calls++;
    return 0.6 * x + 3.0;
}

double f2(double x) {
    function_calls++;
    return pow(x - 2.0, 3.0) - 1.0;
}

double f3(double x) {
    function_calls++;
    if (fabs(x) < 1e-12) {
        return 1e12;  /* Защита от деления на ноль */
    }
    return 3.0 / x;
}

/* Производные функций */
double df1(double x) {
    function_calls++;
    return 0.6;
}

double df2(double x) {
    function_calls++;
    return 3.0 * pow(x - 2.0, 2.0);
}

double df3(double x) {
    function_calls++;
    return -3.0 / (x * x);
}

/* Поиск точки пересечения двух функций */
double find_intersection(func_t f, func_t g, deriv_t df, deriv_t dg, 
                         double a, double b, double eps, int *iters) {
    return root(f, g, a, b, df, dg, eps, iters);
}

/* Поиск всех точек пересечения */
void CALCULATE_find_all_intersections(int show_iterations) {
    double eps = 1e-7;
    int iters1, iters2, iters3;
    double x1, x2, x3;
    
    printf("\n=== Finding curve intersections ===\n");
    
    /* Intersection of f1 and f2 */
    printf("\n1. Intersection of f1(x)=0.6x+3 and f2(x)=(x-2)^3-1:\n");
    x1 = find_intersection(f1, f2, df1, df2, 0.0, 10.0, eps, &iters1);
    printf("   x = %.2f, f1(x)=%.2f, f2(x)=%.2f\n", x1, f1(x1), f2(x1));
    if (show_iterations) {
        printf("   Iterations: %d\n", iters1);
    }
    
    /* Intersection of f1 and f3 */
    printf("\n2. Intersection of f1(x)=0.6x+3 and f3(x)=3/x:\n");
    x2 = find_intersection(f1, f3, df1, df3, 0.5, 5.0, eps, &iters2);
    printf("   x = %.2f, f1(x)=%.2f, f3(x)=%.2f\n", x2, f1(x2), f3(x2));
    if (show_iterations) {
        printf("   Iterations: %d\n", iters2);
    }
    
    /* Intersection of f2 and f3 */
    printf("\n3. Intersection of f2(x)=(x-2)^3-1 and f3(x)=3/x:\n");
    x3 = find_intersection(f2, f3, df2, df3, 3.0, 4.0, eps, &iters3);
    printf("   x = %.2f, f2(x)=%.2f, f3(x)=%.2f\n", x3, f2(x3), f3(x3));
    if (show_iterations) {
        printf("   Iterations: %d\n", iters3);
    }
}

/* Вычисление площади фигуры */
void CALCULATE_compute_area(void) {
    double eps = 1e-6;
    double x_f1f2, x_f1f3, x_f2f3;
    double total_area;
    int iters;
    
    printf("\n=== Calculating area ===\n");
    
    /* Find all intersection points */
    x_f1f2 = root(f1, f2, 0.0, 10.0, df1, df2, 1e-7, &iters);
    x_f1f3 = root(f1, f3, 0.5, 5.0, df1, df3, 1e-7, &iters);
    x_f2f3 = root(f2, f3, 3.0, 4.0, df2, df3, 1e-7, &iters);
    
    printf("\nIntersection points:\n");
    printf("  f1 and f2: x = %.2f\n", x_f1f2);
    printf("  f1 and f3: x = %.2f\n", x_f1f3);
    printf("  f2 and f3: x = %.2f\n", x_f2f3);
    
    /* Determine integration boundaries */
    double left = (x_f1f2 < x_f2f3) ? x_f1f2 : x_f2f3;
    double right = (x_f1f2 > x_f2f3) ? x_f1f2 : x_f2f3;
    double mid = x_f1f3;
    
    /* Adjust split point if outside boundaries */
    if (mid <= left || mid >= right) {
        mid = (left + right) / 2.0;
    }
    
    printf("\nIntegration boundaries:\n");
    printf("  left = %.2f\n", left);
    printf("  split = %.2f\n", mid);
    printf("  right = %.2f\n", right);
    
    /* Difference functions for integration */
    double diff_f1_f3(double x) {
        return f1(x) - f3(x);
    }
    
    double diff_f2_f3(double x) {
        return f2(x) - f3(x);
    }
    
    /* Calculate area */
    double area_part1 = integral(diff_f1_f3, left, mid, eps);
    double area_part2 = integral(diff_f2_f3, mid, right, eps);
    total_area = area_part1 + area_part2;
    
    printf("\nResults:\n");
    printf("  Part 1 (f1 - f3 on [%.2f, %.2f]): %.2f\n", left, mid, area_part1);
    printf("  Part 2 (f2 - f3 on [%.2f, %.2f]): %.2f\n", mid, right, area_part2);
    printf("  Total area = %.2f\n", total_area);
}