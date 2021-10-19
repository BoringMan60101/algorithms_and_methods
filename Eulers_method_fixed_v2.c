/*
-------------------------------------------------------------------------
Исправленный метод Эйлера проверокой точности и выводом таблицы в консоль

Вариант - 20
-------------------------------------------------------------------------
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//0  1  0.8
double f(double x, double y) { return 2.0f*x*y; }
void get_a_b_y0_n_eps(double *a, double *b, double *y0, unsigned *n, double *eps);
void swap(double *a, double *b);
double Eulers_method(double a, double b, double y0, unsigned n, unsigned flag)
{
    double x, y, h;
    h = (b - a) / (n * 1.0f);
    x = a;
    y = y0;
    if(flag)
        printf("X\t\t\tY\n%.2lf\t\t\t%.2lf\n", x, y);
    for (int i = 1; i <= n; i++)
    {
        y = y0 + (h/2.0f)*(f(x, y) + f(x + h, y + h*f(x,y)));
        x += h;
        y0 = y;
        if(flag)
            printf("%.2lf\t\t\t%.2lf\n", x, y);
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
        if (fabs(Eulers_method(a, b, y0, n, 0) - Eulers_method(a, b, y0, 2*n, 0)) < eps)
        {
            Eulers_method(a, b, y0, n, 1);
            break;
        }
        n *= 2;
    }
    return 0;
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

void swap(double *a, double *b)
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}
