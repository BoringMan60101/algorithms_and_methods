/*
------------------------------------------------------------------
Метод Рунге-Кутта с проверкой точности и выводом таблицы в консоль
------------------------------------------------------------------
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//-2 0 -2
double f(double x, double y) { return (3.0f*sin(x*y)*sin(x*y))/x - y; }
void swap(double *a, double *b);
void get_a_b_y0_n_eps(double *a, double *b, double *y0, unsigned *n, double *eps);

double method_Runge_Kutta(double a, double b, double y0, unsigned n, unsigned flag)
{
    double x, y, h, k1, k2, k3, k4;
    h = (b - a) / (n * 1.0f);
    x = a;
    y = y0;
    if(flag)
        printf("X\t\t\tY\n%.2lf\t\t\t%.2lf\n", x, y);
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
        if(flag)
            printf("%.2lf\t\t\t%.2lf\n", x, y);
        x += h;
        y0 = y;
    }
    return y;
}


int main()
{
    double a, b, y0, eps;
    unsigned n;
    get_a_b_y0_n_eps(&a, &b, &y0, &n, &eps);
    while(1)
    {
        if (fabs(method_Runge_Kutta(a, b, y0, n, 0) - method_Runge_Kutta(a, b, y0, 2*n, 0)) < eps)
        {
            method_Runge_Kutta(a, b, y0, n, 1);
            break;
        }
        n *= 2;
    }
    return 0;
}


void swap(double *a, double *b)
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}


void get_a_b_y0_n_eps(double *a, double *b, double *y0, unsigned *n, double *eps)
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
    printf("Enter exactitude (eps) -> ");
    scanf("%lf", &float_val);
    *eps = float_val;
    if(*a > *b)
        swap(a, b);
}
