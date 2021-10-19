#include <stdlib.h>
#include <stdio.h>
#include <math.h>


double f(double x)  { return (x-1)*(x-1) - 0.5f*exp(x); }
double df_dx(double x)  { return 2.0f*(x-1.0f) - 0.5f*exp(x); }
double df_dx_2(double x)  { return 2.0f - 0.5f*exp(x);  }
void metod_bisektsiy(double a, double b, double eps);
void metod_xord(double a, double b, double eps);
void metod_kasatelnix(double a, double b, double eps);
void comb_metod(double a, double b, double eps);
void metod_prostix_iteraciy(double a, double b, double eps);

void find_segments_and_approx_root_by_5_ways(double a, double b)
{
    double dx = 0.1f, eps;
    double x = a;
    int j = 0; //счётчик корней
    printf("Enter exactitude -> ");
    scanf("%lf", &eps);
    while(x < b)
    {
        if ((f(x)*f(x+dx) < 0) && (df_dx(x)*df_dx(x+dx) > 0))
        {
            j += 1;
            printf("\nSegment[%d] [%.1f ; %.1f] contains a root\n", j, x, x+dx);
            metod_bisektsiy(x, x+dx, eps);
            metod_xord(x, x+dx, eps);
            metod_kasatelnix(x, x+dx, eps);
            comb_metod(x, x+dx, eps);
            metod_prostix_iteraciy(x, x+dx, eps);
        }
        x += dx;
    }
}


int main()
{
    double a = -50.0f, b = 50.0f;
    printf("Uravnenie (x-1)^2 - 0.5e^x = 0 \n");
    find_segments_and_approx_root_by_5_ways(a, b);
    return 0;
}


void metod_bisektsiy(double a, double b, double eps)
{
    double c = (a + b) / 2.0f;
    while(fabs(a-b) >= eps)
    {
        if (f(a)*f(c) < 0)
            b = c;
        else
            a = c;
        c = (a + b) / 2.0f;
    }
    printf("Metod bisektsiy approximates -> %.5lf\n", c);
}


void metod_xord(double a, double b, double eps)
{
    double c1, c2;
    c1 = (a*f(b) - b*f(a))/(f(b)- f(a));
    do
    {
        if (f(a)*f(c1) < 0)
            b = c1;
        else
            a = c1;
        c2 = (a*f(b) - b*f(a))/(f(b)- f(a));
        c1 = c2;
    } while(fabs(c2-c1) >= eps);
    printf("Metod xord approximates -> %.5lf\n", c1);
}


void metod_kasatelnix(double a, double b, double eps)
{
    double x0, x1;
    if (f(a)*df_dx_2(a) > 0) //определяем начальную точку
        x0 = a;
    else
        x0 = b;
    x1 = x0 - f(x0)/df_dx(x0);
    while(fabs(x1 - x0) >= eps)
    {
        x0 = x1;
        x1 = x0 - f(x0)/df_dx(x0);
    }
    printf("Metod xord kasatelnix -> %.5lf\n", x1);
}


void comb_metod(double a, double b, double eps)
{
    double a1, b1;
    if (f(a)*df_dx_2(a) > 0)
    {
        a1 = a - f(a)/df_dx(a);
        b1 = (a*f(b) - b*f(a)) / (f(b) - f(a));
    }
    else
    {
        a1 = (a*f(b) - b*f(a)) / (f(b) - f(a));
        b1 = b - f(b)/df_dx(b);
    }
    while(fabs(a1 - b1) >= eps)
    {
            a = a1;
            b = b1;
            if (f(a)*df_dx_2(a) > 0)
            {
                a1 = a - f(a)/df_dx(a);
                b1 = (a*f(b) - b*f(a)) / (f(b) - f(a));
            }
            else
            {
                a1 = (a*f(b) - b*f(a)) / (f(b) - f(a));
                b1 = b - f(b)/df_dx(b);
            }
    }
    printf("Metod combinirovanniy -> %.5lf\n", (a1 + b1)/2.0f);
}



void metod_prostix_iteraciy(double a, double b, double eps)
{
    double c, x0, x1;
    if ( (df_dx(a) > 0) && (fabs(df_dx(a)) > fabs(df_dx(b))) )
        c = -1.0f/fabs(df_dx(a));
    else
        c = 1.0f/fabs(df_dx(b));
    x0 = (a + b) / 2.0f;
    x1 = x0 + c*f(x0);
    while(fabs(x1 - x0) >= eps)
    {
        x0 = x1;
        x1 = x0 + c*f(x0);
    }
    printf("Metod prostix iteraciy -> %.5lf\n", x1);
}
