#include <graphics.h>
#include <stdio.h>
#include <math.h>
#define MAX_W 1000
#define MAX_H 1000
//#define SCALE 50.0f
#define EPS 0.01f
#define X0 500
#define Y0 500


double scale = 50.0f; //Масштаб "в единице будет 50 пикселей"
const double a = -(MAX_W / (scale*2.0f)), b = scale*(MAX_W / (scale*2.0f)); //boundary points [a; b]

void print_menu();
void print_approx_curve(int selected_curve);
void draw_axes(); 
double f_x(double x); 
double df_dx(double x);
void function_graph(); 
void metod_bisektsiy(double a, double b); //приближенно находит значение корня на каждом отрезке [a;b] с точностью до EPS
void print_roots(); //печать найденных значений для корней



int main()
{
	initwindow(MAX_W+10, MAX_H); 
	draw_axes();
	function_graph();
	print_roots(); 
	getch();
	closegraph();
	return 0;
} 


double f_x(double x)
{
	return  sin(x); //Собственно сама функция
}


double df_dx(double x)
{
	return cos(x); //Производная
}


void draw_axes() 
{
  char screen_txt[10]; //Для печати текста на экране
    outtextxy(X0 - 15, Y0 + 15, "O"); //Точка О(0; 0)
  line(0, Y0, MAX_W, Y0); //Ось Ox
  line(MAX_W - 10, Y0-10, MAX_W, Y0); //Верхняя часть "стрелочки" на оси Ох
  line(MAX_W - 10, Y0+10, MAX_W, Y0); //Нижняя часть "стрелочки" на оси Ох
  outtextxy(MAX_W-10, Y0+10, "X");
  outtextxy(X0 + 1.0f*scale - 5, Y0 + 10, "1"); 
  line(X0, 0, X0, MAX_H); //Ось Оу
  line(X0 + 10, 10, X0, 0); //Правая часть "стрелочки" на оси Оy
  line(X0 - 10, 10, X0, 0); //Левая часть "стрелочки" на оси Oy
  outtextxy(X0 - 15, 10, "Y"); 
  outtextxy(X0 - 15, Y0 - 1.0f*scale - 5, "1");
  for (int i = 1; i <= (MAX_W - X0) / scale; i++) //Вертикальные отметки на левой части оси Ох
    line(X0 - scale*i, Y0 - 3, X0 - scale*i, Y0 + 3); 
  for (int i = 1; i <= (MAX_W - X0) / scale; i++) //Вертикальные отметки на правой части оси Ох
    line(X0 + scale*i, Y0 - 3, X0 + scale*i, Y0 + 3); 
  for(int i = 0; i <= (MAX_W - X0) / scale; i++) //Горизонтальные отметки на верхней части оси Оу
	line(X0 - 3, Y0 - scale*i, X0 + 3, Y0 - scale*i); 
  for(int i = 0; i <= (MAX_W - X0) /scale; i++) //Вертикальные отметки на нижней части оси Ох
	line(X0 - 3, Y0 + scale*i, X0 + 3, Y0 + scale*i); 
}


void function_graph() 
{
  double x, cor_x, cor_y;//X принимает все значения с сегмента [-A; B] (B = A), cor_x(y) - "координаты" Х и (Y) в масштабе экрана.
  double h = 1.0f/(scale*5); //"Густота точек" с которой строится график функции
  for (x = 0; x <= (MAX_W - X0)/scale; x += h) //Левая часть графика
  {
	cor_x = X0 - scale*x; //От стартовой координаты X0 отнимаем, т.к. печатаем левую часть, значение Х, умноженное на масштаб 
	cor_y = Y0 - scale*f_x(-x); //Передаём в функцию отрицательные значения Х, т.к. находимся слева от нуля
	if (cor_x >= 0 && cor_x < MAX_W+1 && cor_y >= 0 && cor_y < MAX_H+1) //Проверка границ экрана
    	putpixel(cor_x, cor_y, RED); //Точка графика
  }
  for (x = 0; x <= MAX_W / 2.0f*scale; x += h) //Правая часть графика
  {
	cor_x = X0 + scale*x; //К стартовой точке Х0 прибавляем значение х, умноженное на масштаб
	cor_y = Y0 - scale*f_x(x); //от У0 отнимаем значение функции, т.к. в этой библиотеке положительные игреки идут вниз.
	if (cor_x >= 0 && cor_x < MAX_W+1 && cor_y >= 0 && cor_y < MAX_H+1) 
    	putpixel(cor_x, cor_y, RED);
  }
}


void metod_bisektsiy(double a, double b)
{
	char root_value[10];
    double c = ((a + b) / 2.0f);
    while(fabs(a-b) >= EPS)
    {
        if (f_x(a)*f_x(c) < 0)
            b = c;
        else 
            a = c;
        c = ((a + b) / 2.0f);
    }
    sprintf(root_value, "%.3lf", c); 
    outtextxy(X0 + scale*c, Y0 + scale*2.5f, root_value); //Рядом с точкой, где у функции корень, будет напечатано её значение, для этого учитывается масштаб
    line(X0 + scale*c, Y0+1, X0 + scale*c, Y0 + scale*2.0f);  //Вертикальная линия "стрелочки", указывающей на примерную точку с корнем на оси Ох
    line(X0 + scale*c - 5, Y0+6, X0 + scale*c, Y0); //Левая часть "стрелочки"
    line(X0 + scale*c + 5, Y0+6, X0 + scale*c, Y0); //Правая часть "стрелочки"
    
}


void print_roots()
{
	double x = a; 
    double dx = 0.1f; //Шаг прохода по отрезку [a;b]
    while(x < b)
    {
        if ((f_x(x)*f_x(x+dx) < 0) && (df_dx(x)*df_dx(x+dx) > 0))
			metod_bisektsiy(x, x+dx);
        x += dx;
    }
}
