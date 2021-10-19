#include <math.h>
#include <stdio.h>

double f_x(double x)
{
    return sqrt(x);
}

double integral(double a, double b, int n)
{
    double h = fabs(a - b)/n, sum = 0.0f, x = a;
    for(int i = 0; i < n; i++)
    {   
        sum += f_x(x+h/2.0f);
        x += h;
    }
    return h*sum;
}


int main()
{
    double a = 0.0f, b = 1.0f, eps = 1e-9;
    int n = 2;
    while(fabs(integral(a, b, n) - integral(a, b, 2*n)) >= eps)
        n = n*2;
    printf("%lf", integral(a, b, n));
    return 0;
}

