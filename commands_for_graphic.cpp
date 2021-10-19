/*
http://dmshefer.narod.ru/C_Graph.pdf
https://kpolyakov.spb.ru/school/c/faq.htm
--------------------------------------------------
Task #1 - draw different functions
Task #2 - draw function and show F(x) and X values
--------------------------------------------------
---------------------------------

WINDOW FUNCTIONS
---------------------------------
initgraph(int *GrType, int *GrMod, char *Path); 
DETECTED - max available Graphics type (return int value)
If you give GrType = DETECTED, then GrMd automatically becomes a maxinum mode
We consider *path as " ", which means that *.bgi files are located in working catalog
graphresult() always returns GrOk if everything is OK
closegraph() stops graphic mode and turns on text mode, it cleans the screen!
---------------------------------

---------------------------------
DRAWING FUNCTIONS
---------------------------------
line(int x1,int y1,int x2,int y2) 
rectangle(int x1,int y1,int x2,int y2) 
bar(int x1,int y1,int x2,int y2)
bar3d(int x1,int y1,int x2,int y2,int h) 
ellipse(int x,int y,int rx,int ry)
fillellipse(int x,int y,int rx,int ry) 
arc(int x,int y,int Alfa1,int Alf2,int r) 
outtextxy(int x,int y,char *St)
putpixel(int x, int y, char Color) 
Color=getpixel(int x,int y)
floodfill(int x,int y,char Color) 
cleardevice() clears screen

setcolor(char Color) sets drawing color
setbkcolor(char Color) changes ALL colors on the screen!
---------------------------------

---------------------------------
DRAWING PARAMETERS
---------------------------------
setlinestyle(<patter>, int Bit, char h) sets style and thickness of lines
SOLID_LINE 0
DOTTED_LINE 1
CENTER_LINE 2
DASHED_LINE 3
---------------------------------

---------------------------------
FUNCTIONS TO GET INFORMATION
---------------------------------
MaxX=getmaxx() gets max value on X axis 
MaxY=getmaxy() gets max value on Y axis
---------------------------------


int main()
{
	
	int GrType, GrMod;
	GrType=DETECT; //Got graphic type for the monitor
	initgraph(&GrType,&GrMod," ");
	//initwindow(800, 600); //We can use this function instead initgrapgh() 
	if(graphresult() != grOk)
	{
		printf("\nGraphics Error!\n"); 
		exit(EXIT_FAILURE);
	} 
	
}

*/
