#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include<iostream>
#include <windows.h>
#include <string>
#include <cmath>
using namespace std;
void drawColorBoard(int boardX, int boardY, int width, int height);
void chooseColor(int height, int Y);
void showColor(int winWidth, int winHeight, int X, int Y);
/*  Set initial display-window size. */
GLsizei winWidth = 1300, winHeight = 800;

/*  Set range for world coordinates.  */
GLfloat xwcMin = 0.0, xwcMax = 225.0;
GLfloat ywcMin = 0.0, ywcMax = 225.0;

//画图
static int g_x1, g_y1, g_x2, g_y2, Eraser;
float R = 1.0, G = 0.0, B = 0.0;
static int g_left_button_state = 0;//0-up,1-down
static void draw(), clean();
static void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);//set display-window color to white;
	glMatrixMode(GL_PROJECTION);//set projection parameters;
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);//投影矩阵范围
}
static void mouseMotionFunc(GLint x, GLint y)
{
	if (x > winWidth - 300) {
		g_left_button_state = 0;
		chooseColor(winHeight, y);
		drawColorBoard(winWidth - 300, 0, 302, winHeight);
		showColor(winWidth,winHeight,x, winHeight-y);
		return;
	}
	if (0 == g_left_button_state) return;
	g_x2 = x;
	g_y2 = y;
	if (Eraser == 0) {
		glLineWidth(5.0);//set line width
		glColor3f(R, G, B);//set point segment color to red;
		draw();//不能调用glutPostRedisplay()重绘窗口
	}
	else {
		glLineWidth(30.0);//set line width
		glColor3f(1.0, 1.0, 1.0);//set point segment color to red;
		clean();
	}
	g_x1 = g_x2;
	g_y1 = g_y2;
}
static void draw()
{
	static int l_flag = 0;
	if (0 == l_flag)
	{
		//glClear(GL_COLOR_BUFFER_BIT);//clear display window
		glColor3f(1.0, 0.0, 0.0);//set point segment color to red;
		drawColorBoard(winWidth - 300, 0, 302, winHeight);
		glFlush();
		l_flag = 1;
		return;
	}
	glBegin(GL_LINES);
	glVertex2i(g_x1, winHeight - g_y1);
	glVertex2i(g_x2, winHeight - g_y2);
	glEnd();
	drawColorBoard(winWidth - 300, 0, 302, winHeight);
	glFlush();
}
static void clean()
{
	glPointSize(100);
	glBegin(GL_POINTS);
	glVertex2i(g_x1, winHeight - g_y1);
	glVertex2i(g_x2, winHeight - g_y2);
	glEnd();
	glColor3f(1.0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(winWidth - 301, 0);
	glVertex2i(winWidth - 301, winHeight);
	glLineWidth(10);
	glEnd();
	drawColorBoard(winWidth - 300, 0, 302, winHeight);
	glFlush();
}
static void mouseEvent(int button, int state, int x, int y)
{
	if (x > winWidth - 300) {
		g_left_button_state = 0;
		chooseColor(winHeight, y);
		return;
	}
	g_left_button_state = 0;
	if (GLUT_LEFT_BUTTON == button)
	{
		switch (state)
		{
		case GLUT_DOWN:
			g_x1 = x;
			g_y1 = y;
			g_left_button_state = 1;
			Eraser = 0;
			break;
		default:
			break;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON) {
		switch (state)
		{
		case GLUT_DOWN:
			g_x1 = x;
			g_y1 = y;
			g_left_button_state = 1;
			Eraser = 1;
			break;
		default:
			break;
		}
	}
}

void displayFcn(void)
{
	glClear(GL_COLOR_BUFFER_BIT);   //  Clear display window.
	glColor3f(1.0, 0, 0.0);
	glLineWidth(30);
	glBegin(GL_LINES);
	glVertex2i(winWidth - 301,0);
	glVertex2i(winWidth - 301, winHeight);
	glEnd();
	drawColorBoard(winWidth - 300, 0, 302, winHeight+1);
	glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	
	glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);//init glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//set display mode
	glutInitWindowPosition(30, 30);//set top-left display-window position
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("左键画图，邮件擦除");//Create display windwo
	init();
	glutDisplayFunc(displayFcn);//send graphics to display window
	glutMouseFunc(mouseEvent);//按下鼠标左键后的动作
	glutMotionFunc(mouseMotionFunc);
	glutMainLoop();//Display everything and wait
	glutReshapeFunc(winReshapeFcn);
	return 0;
}