#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#pragma comment (lib,"freeglut.lib")
#pragma commet (lib,"glew32.lib")
#pragma comment (lib,"glew32.lib")

#include <gl/glew.h> //--- �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iterator>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
void convertDeviceXY2OpenglXY(int x, int y, float* ox, float* oy);
void Motion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void DrawCircle(int x, int y, int rad, int degree, int check, double tmpX, double tmpY);
double f_rand(void);
bool left_button;
float ox, oy;
GLfloat x_1, y_1;
GLfloat r=0.0f, g=0.0f, b=0.1f;

typedef struct {
	int x, y;
	double rad;
	double SaveRad;
	int check;
	int degree;
	double tmpX, tmpY;
} Shape;

vector<Shape> circle;
vector<Shape>::iterator iter;


void main(int argc, char** argv) { //--- ������ ����ϰ� �ݹ��Լ� ���� { //--- ������ �����ϱ�
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("Example1"); // ������ ����(������ �̸�)
		//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK
		) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutMainLoop(); // �̺�Ʈ ó�� ����
}
GLvoid drawScene() {//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� { glClearColor( 0.0f, 0.0f, 1.0f, 1.0f ); // �������� ��blue�� �� ����
	glClearColor(r, g, b, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.

	for (iter = circle.begin(); iter != circle.end(); ++iter)
	{
		DrawCircle(iter->x, iter->y, iter->rad, iter->degree, iter->check, iter->tmpX, iter->tmpY);
	}


	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) { //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 0, 600, -1, 1);
}
GLvoid Mouse(int button, int state, int x, int y) {
	srand((unsigned int)time(NULL));

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Shape s;

		s.x = x;
		s.y = 600 - y;
		s.rad = 5;
		s.SaveRad = s.rad;
		s.check = rand() % 2;
		s.degree = 0;
		s.tmpX = 0;
		s.tmpY = 0;

		circle.push_back(s);

		if (circle.size() == 11) circle.erase(circle.begin());

		r = f_rand();
		g = f_rand();
		b = f_rand();
	}
}
void Motion(int x, int y) {
	convertDeviceXY2OpenglXY(x, y, &ox, &oy);
	if (left_button == true) {
	}
}
void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	}
}
double f_rand(void) {
	double a;
	a = rand() / (double)RAND_MAX;
	return a;
}
void convertDeviceXY2OpenglXY(int x, int y, float* ox, float* oy)
{
	int w = 800;
	int h = 600;
	*ox = (float)((x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0)));
	*oy = -(float)((y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0)));
}
void TimerFunction(int value) {

	srand((unsigned int)time(NULL));

	for (iter = circle.begin(); iter != circle.end(); ++iter)
	{
		if (iter->degree >= 120)
			iter->degree = 120;
		else
			iter->degree += 1;
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}
void DrawCircle(int x, int y, int rad, int degree, int check, double tmpX, double tmpY)
{
	double angle;

	glColor3f(1.0f, 1.0f, 1.0f);

	glPointSize(3.0);
	glBegin(GL_POINTS);

	for (int i = 0; i < degree; ++i)
	{
		angle = (i * 3.141592) / 10;

		if (check == 0)
		{
			if (i <= 60)
			{
				tmpX = (rad + i / 2) * cos(angle) + x;
				tmpY = (rad + i / 2) * sin(angle) + y;
			}
			else
			{
				tmpX = (rad - (140 - i) / 2) * cos(-angle) + x + 70;
				tmpY = (rad - (140 - i) / 2) * sin(-angle) + y;
			}
		}
		else
		{
			if (i <= 60)
			{
				tmpX = (rad + i / 2) * cos(-angle) + x;
				tmpY = (rad + i / 2) * sin(-angle) + y;
			}
			else
			{
				tmpX = (rad - (140 - i) / 2) * cos(angle) + x + 70;
				tmpY = (rad - (140 - i) / 2) * sin(angle) + y;
			}
		}

		glVertex2f(tmpX, tmpY);
	}

	glEnd();
}