#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#define MAX_W 1000
#define MAX_H 1000
//#define SCALE 50.0f
#define EPS 0.01f
#define X0 500
#define Y0 500


double scale = 50; //Масштаб "в единице будет 'scale' пикселей". Пока как глобальная, но потом нужно исправить

void get_data_table(int values_number, double X[], double Y[]); //Для ввода экспериментальных значений с клавиатуры
double sum_up_x(int val_num, double X[]); //Сумма Xi i = 1,n
double sum_up_y(int val_num, double Y[]); //Сумма Yi i = 1,n
double sum_up_xx(int val_num, double X[]); //Сумма Xi*Xi i = 1,n
double sum_up_xy(int val_num, double X[], double Y[]); //Сумма Xi*Yi = 1,n
void draw_axes(); //Рисует оси
void print_points_from_table(int items_num, double X[], double Y[]); //Наносит введённые точки
double straight_line(double x, double a, double b) { return a*x + b; } //Аппроксимирующая прямая вида y = Ax + B
void draw_approx_line(double a, double b); //Проводит аппроксимирующую прямую


int main()
{
	double Sx, Sy, Sxx, Sxy, det, det_a, det_b, a, b;
	int n; //Количество экспериментальных значений (точек)
	printf("Enter number of exeprimental values -> ");
	scanf("%d", &n);
	double X[n], Y[n];
	get_data_table(n, X, Y); //Ввод экспериментальных значений с клавиатуры значений (записываются в массивы)
	//Вычисление коффицинтов приближающей прямой
	Sx = sum_up_x(n, X);
	Sy = sum_up_y(n, Y);
	Sxx = sum_up_xx(n, X);
	Sxy = sum_up_xy(n, X, Y);
	det = n*Sxx - Sx*Sx;
	det_a = n*Sxy - Sx*Sy;
	det_b = Sy*Sxx - Sxy*Sx;
	a = det_a / det; //Коэффициенты находятся с помощью метода Крамера
	b = det_b / det;
	initwindow(MAX_W+10, MAX_H); //Открытие окна с графикой
	draw_axes(); //Рисует оси
	print_points_from_table(n, X, Y); //Наносит введённые точки
	draw_approx_line(a, b); //Проводит аппроксимирующую прямую
	getch(); //Чтобы окно сразу же не закрылось
	closegraph();
	return 0;
} 


void get_data_table(int values_number, double X[], double Y[]) //Для ввода экспериментальных значений с клавиатуры
{
	double value;
	for(int i = 0; i < values_number; i++)
	{
		printf("Enter X[%d] -> ", i+1);
		scanf("%lf", &value);
		X[i] = value;
		printf("Enter Y[%d] -> ", i+1);
		scanf("%lf", &value);
		Y[i] = value;
	}
	printf("\n");
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


double sum_up_x(int val_num, double X[])
{
    double Sx = 0.0f;
    for(int i = 0; i < val_num; i++)
      Sx += X[i];
    return Sx;
}


double sum_up_y(int val_num, double Y[])
{
    double Sy = 0.0f;
    for(int i = 0; i < val_num; i++)
      Sy += Y[i];
    return Sy;
}


double sum_up_xx(int val_num, double X[])
{
    double Sxx = 0.0f;
    for(int i = 0; i < val_num; i++)
      Sxx += (X[i]*X[i]);
    return Sxx;
}


double sum_up_xy(int val_num, double X[], double Y[])
{
    double Sxy = 0.0f;
    for(int i = 0; i < val_num; i++)
      Sxy += (X[i]*Y[i]);
    return Sxy;
}


void print_points_from_table(int items_num, double X[], double Y[])
{
	setcolor(GREEN);
	for(int i = 0; i < items_num; i++)
	{
		circle(X0 + scale*X[i], Y0 - scale*Y[i], 1); //prints point X_i(X[i]; Y[i]) 
		circle(X0 + scale*X[i], Y0 - scale*Y[i], 2); //prints point X_i(X[i]; Y[i]) 
		circle(X0 + scale*X[i], Y0 - scale*Y[i], 3); //prints point X_i(X[i]; Y[i]) 
	}		
}


void draw_approx_line(double a, double b) //Принимает "выбранную кривую, как бы её формулу", и соответсвующие коэффициенты
{
  double x, cor_x, cor_y;//cor_x(y) - "координаты" Х и (Y) в масштабе экрана.
  double h = 1.0f/(scale*5.0f); //"Густота точек" с которой строится график функции
  for (x = 0; x <= (MAX_W - X0)/scale; x += h) //Левая часть графика
  {
	cor_x = X0 - scale*x; //От стартовой координаты X0 отнимаем, т.к. печатаем левую часть, значение Х, умноженное на масштаб 
	cor_y = Y0 - scale*straight_line(-x, a, b); //Передаём в функцию отрицательные значения Х, т.к. находимся слева от нуля
	if (cor_x >= 0 && cor_x < MAX_W+1 && cor_y >= 0 && cor_y < MAX_H+1) //Проверка границ экрана
    	putpixel(cor_x, cor_y, RED); //Точка графика
  }
  for (x = 0; x <= MAX_W / 2.0f*scale; x += h) //Правая часть графика
  {
	cor_x = X0 + scale*x; //К стартовой точке Х0 прибавляем значение х, умноженное на масштаб
	cor_y = Y0 - scale*straight_line(x, a, b); //от У0 отнимаем значение функции, т.к. в этой библиотеке положительные игреки идут вниз.
	if (cor_x >= 0 && cor_x < MAX_W+1 && cor_y >= 0 && cor_y < MAX_H+1) 
    	putpixel(cor_x, cor_y, RED);
  }
}
