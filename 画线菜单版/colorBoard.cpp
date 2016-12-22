#include<GL\glut.h>
#include <stdlib.h>
#include<stdio.h>

extern float R;
extern float G;
extern float B;
void drawColorBoard(int boardX,int boardY,int width,int height) {
	GLsizei dw;
	int n, i;
	dw = 1;
	n = (height - 1) / dw;
	GLsizei r, g, b;
	for (i = 0; i<n; i++)
	{
		//绘制应力云图的关键就是下面的这五种不同的颜色对应关系
		//根据自己需要可以设置不同的等级，四种也是可以的
		if (i >= 0 && i <= n / 5)
		{
			r = 255;
			g = i * 255 / (n / 5);
			b = 0;
		}
		else if (i>n / 5 && i <= 2 * n / 5)
		{
			r = 255 - (i - n / 5) * 255 / (n / 5);
			g = 255;
			b = 0;
		}
		else if (i>2 * n / 5 && i <= 3 * n / 5)
		{
			r = 0;
			g = 255;
			b = (i - 2 * n / 5) * 255 / (n / 5);
		}
		else if (i>3 * n / 5 && i <= 4 * n / 5)
		{
			r = 0;
			g = 255 - (i - 3 * n / 5) * 255 / (n / 5);
			b = 255;
		}
		else
		{
			r = (i - 4 * n / 5) * 255 / (n / 5);
			g = 0;
			b = 255;
		}
		glColor4f(r / 255.0f, g / 255.0f, b / 255.0f,25/255);
		glRectf(boardX, 1.0*i*dw + boardY,width+ boardX, 1.0*(i + 1)*dw+boardY);
	}
}
void chooseColor(int height,int Y) {
	int n = height;
	int i = height-Y;
	int r, g, b;
	if (i >= 0 && i <= n / 5)
	{
		r = 255;
		g = i * 255 / (n / 5);
		b = 0;
	}
	else if (i>n / 5 && i <= 2 * n / 5)
	{
		r = 255 - (i - n / 5) * 255 / (n / 5);
		g = 255;
		b = 0;
	}
	else if (i>2 * n / 5 && i <= 3 * n / 5)
	{
		r = 0;
		g = 255;
		b = (i - 2 * n / 5) * 255 / (n / 5);
	}
	else if (i>3 * n / 5 && i <= 4 * n / 5)
	{
		r = 0;
		g = 255 - (i - 3 * n / 5) * 255 / (n / 5);
		b = 255;
	}
	else
	{
		r = (i - 4 * n / 5) * 255 / (n / 5);
		g = 0;
		b = 255;
	}
	R = r / 255.0;
	G = g / 255.0;
	B = b / 255.0;
}
void showColor(int winWidth,int winHeight,int X,int Y) {
	if (X - 50 > winWidth-300&&X + 50 < winWidth&&Y+120<winHeight&&Y-50>0) {
		glColor3f(1.0, 1.0, 1.0);
		glRectf(X - 50, Y + 20, X + 50, Y + 120);
		glColor3f(R, G, B);
		glRectf(X - 45, Y + 25, X + 45, Y + 115);
		printf("%d", Y);
		glFlush();
	}else if (X - 50 < winWidth - 300&& Y + 120>winHeight) {
		glColor3f(1.0, 1.0, 1.0);
		glRectf(X + 20, Y - 20, X + 120, Y - 120);
		glColor3f(R, G, B);
		glRectf(X + 25, Y - 25, X + 115, Y - 115);
		glFlush();
	}else if (X + 50 > winWidth && Y + 120>winHeight) {
		
		glColor3f(1.0, 1.0, 1.0);
		glRectf(X - 20, Y - 20, X - 120, Y - 120);
		glColor3f(R, G, B);
		glRectf(X - 25, Y - 25, X - 115, Y - 115);
		glFlush();
	}
	else if (X - 50 < winWidth - 300 && Y-50<0) {
		glColor3f(1.0, 1.0, 1.0);
		glRectf(X + 20, Y + 20, X + 120, Y + 120);
		glColor3f(R, G, B);
		glRectf(X + 25, Y + 25, X + 115, Y + 115);
		glFlush();
	}
	else if (X + 50 > winWidth &&Y - 50<0) {
		glColor3f(1.0, 1.0, 1.0);
		glRectf(X - 20, Y + 20, X - 120, Y + 120);
		glColor3f(R, G, B);
		glRectf(X - 25, Y + 25, X - 115, Y + 115);
		glFlush();
	}else if (Y + 120>winHeight) {
		glColor3f(1.0, 1.0, 1.0);
		glRectf(X - 50, Y - 20, X + 50, Y - 120);
		glColor3f(R, G, B);
		glRectf(X - 45, Y - 25, X + 45, Y - 115);
		glFlush();
	}else if (Y - 50 < 0) {
		glColor3f(1.0, 1.0, 1.0);
		glRectf(X - 50, Y + 20, X + 50, Y + 120);
		glColor3f(R, G, B);
		glRectf(X - 45, Y + 25, X + 45, Y + 115);
		glFlush();
	}
	else if (X - 50 < winWidth - 300) {
		glColor3f(1.0, 1.0, 1.0);
		glRectf(X +20, Y -50, X + 120, Y + 50);
		glColor3f(R, G, B);
		glRectf(X +25, Y - 45, X + 115, Y + 45);
		glFlush();
	}
	else if (X + 50 > winWidth) {
		glColor3f(1.0, 1.0, 1.0);
		glRectf(X - 20, Y - 50, X - 120, Y + 50);
		glColor3f(R, G, B);
		glRectf(X - 25, Y - 45, X - 115, Y + 45);
		glFlush();
	}
	

}