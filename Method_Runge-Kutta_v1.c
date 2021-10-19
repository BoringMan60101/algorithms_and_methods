/*
----------------------------------------------------
Метод Рунге-Кутта просто с выводом таблицы в консоль
----------------------------------------------------
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//-2 0 -2
double f(double x, double y) { return (3.0f*sin(x*y)*sin(x*y))/x - y; }
void get_a_b_y0_n_eps(double *a, double *b, double *y0, unsigned *n);
void swap(double *a, double *b);


int main()
{
    double a, b, x, y, y0, h, k1, k2, k3, k4;
    unsigned n;
    get_a_b_y0_n_eps(&a, &b, &y0, &n);
    h = (b - a) / (n * 1.0f);
    printf("X\t\t\tY\n");
    x = a;
    y = y0;
    printf("%.2lf\t\t\t%.2lf\n", x, y);
    k1 = f(x, y);
    k2 = f(x + h/2.0f, y + (k1*h)/2.0f);
    k3 = f(x + h/2.0f, y + (k2*h)/2.0f);
    k4 = f(x + h, y + k2*h);
    for (int i = 1; i <= n; i++)
    {

        y = y0 + (h/6.0f)*(k1 + 2.0f*k2 + 2.0f*k3 + k4);
        k1 = f(x, y);
        k2 = f(x + h/2.0f, y + (k1*h)/2.0f);
        k3 = f(x + h/2.0f, y + (k2*h)/2.0f);
        k4 = f(x + h, y + k2*h);
        x += h;
        y0 = y;
        printf("%.2lf\t\t\t%.2lf\n", x, y);
    }
    return 0;
}


void get_a_b_y0_n_eps(double *a, double *b, double *y0, unsigned *n)
{
    double float_val;
    unsigned int_val;
    printf("Enter A -> ");
    scanf("%lf", &float_val);
    *a = float_val;
    printf("Enter B -> ");
    scanf("%lf", &float_val);
    *b = float_val;
    printf("Enter Y0 -> ");
    scanf("%lf", &float_val);
    *y0 = float_val;
    printf("Enter N -> ");
    scanf("%u", &int_val);
    *n = int_val;
    if(*a > *b)
        swap(a, b);
}


void swap(double *a, double *b)
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}
