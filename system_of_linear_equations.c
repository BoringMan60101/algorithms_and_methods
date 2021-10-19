#include <stdio.h>
#include <math.h>
#define EPS 0.001

double d_1(double x11, double x10)
{
    return fabs(x11 - x10);
}

double d_2(double x21, double x20)
{
    return fabs(x21 - x20);
}

double d_3(double x31, double x30)
{
    return fabs(x31 - x30);
}

double max(double a, double b)
{
    return a > b ? a : b;
}

double max_delta(double d1, double d2, double d3)
{
    return max(max(d1, d2), d3);
}

int main()
{
    int n = 3;
    double a[n][n];
    double x10 = 0.0f, x20 = 0.0f, x30 = 0.0f, x11, x21, x31;
    double b1 = 32.0f, b2 = 57.0f, b3 = 8.0f;
    a[0][0] = 11.0f;
    a[0][1] = 1.8f;
    a[0][2] = 2.7f;
    a[1][0] = 4.8f;
    a[1][1] = 37.0f;
    a[1][2] = 4.1f;
    a[2][0] = 2.8f;
    a[2][1] = 2.1f;
    a[2][2] = 33.0f;
    printf("Equations system\n");
    printf("%.2f*X1 + %.2f*X2 + %.2f*X3 = %.2f\n", a[0][0], a[0][1], a[0][2], b1);
    printf("%.2f*X1 + %.2f*X2 + %.2f*X3 = %.2f\n", a[1][0], a[1][1], a[1][2], b2);
    printf("%.2f*X1 + %.2f*X2 + %.2f*X3 = %.2f\n", a[2][0], a[2][1], a[2][2], b3);
    x11 = (b1 - a[0][1]*x20 - a[0][2]*x30)/a[0][0];
    x21 = (b2 - a[1][0]*x10 - a[1][2]*x30)/a[1][1];
    x31 = (b3 - a[0][1]*x20 - a[0][2]*x30)/a[2][2];
    while(max_delta(d_1(x11, x10), d_2(x21, x20), d_3(x31, x30)) >= EPS)
    {
        x10 = x11;
        x20 = x21;
        x30 = x31;
        x11 = (b1 - a[0][1]*x20 - a[0][2]*x30)/a[0][0];
        x21 = (b2 - a[1][0]*x10 - a[1][2]*x30)/a[1][1];
        x31 = (b3 - a[2][0]*x10 - a[2][1]*x20)/a[2][2];
    }
    printf("Solution {%.3f; %.3f; %.3f}\n", x11, x21, x31);
    printf("Cheking them \n");
    printf("%.2f\n", a[0][0]*x11 + a[0][1]*x21 + a[0][2]*x31);
    printf("%.2f\n", a[1][0]*x11 + a[1][1]*x21 + a[1][2]*x31);
    printf("%.2f", a[2][0]*x11 + a[2][1]*x21 + a[2][2]*x31);
    return 0;
}
