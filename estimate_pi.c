#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#include <math.h>

int main()
{
  //P = PI/4 ~ k/n ==> PI ~4*(k/n)
  //(float) rand() / RAND_MAX * (max - min) + min
  /*
  unsigned long long n, k = 0;
  long double x, y;
  srand(time(NULL));
  printf ("Enter N -> ");
  scanf ("%lld", &n);
  for (int i = 1; i <= n; i++)
  {
    x = (long double) rand() / RAND_MAX * (1.0f);
    y = (long double) rand() / RAND_MAX * (1.0f);
    if(x*x + y*y <= 1.0f)
        k++;
  }
  printf("PI ~ %lf\n", (4.0f*k)/n);
  */

  //допилить чтобы N вводилось про компиляции м.б.

  long long unsigned n;
  long double PI = 0.0f;
  printf ("Enter N -> ");
  scanf ("%llu", &n);
  for(unsigned i = 0; i <= n; i++)
  {
      if(!(i % 2))
        PI += 4.0f/(2.0f*i+1.0f);
      else
        PI += -4.0f/(2.0f*i+1.0f);
  }
  printf("PI ~ %.64Lf\n", PI);
  return 0;
}
