#define _CRT_SECURE_NO_WARNINGS

#pragma comment (lib,"freeglut.lib")
#pragma comment (lib,"glew32.lib")
#pragma comment (lib,"glew32.lib")

#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <cstdlib>
#include <ctime>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
void convertDeviceXY2OpenglXY(int x, int y, float* ox, float* oy);
void Motion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
double f_rand(void);
bool left_button;
float ox, oy;
bool first_drag = false,second_drag = false , third_drag=false,fourth_drag = false,big_drag = false;
GLfloat x_1 = 0.5f, y_1 = 0.5f, x_2=-0.5f, y_2=0.5f, x_3=-0.5f, y_3=-0.5f, x_4=0.5f, y_4=-0.5f;
GLfloat tempx1, tempy1, tempx2, tempy2, tempx3, tempy3, tempx4, tempy4;
GLfloat tempx, tempy;
int temp=0;
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
	glClearColor(0, 0, 0.1f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.3f, 0.2f, 0.7f);
	glVertex3f(x_2, y_2, 0.0f);
	glColor3f(7.0f, 0.2f, 0.3f);
	glVertex3f(x_1, y_1, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.3f, 0.2f, 0.7f);
	glVertex3f(x_3, y_3, 0.0f);
	glColor3f(7.0f, 0.2f, 0.3f);
	glVertex3f(x_2, y_2, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.3f, 0.2f, 0.7f);
	glVertex3f(x_4, y_4, 0.0f);
	glColor3f(7.0f, 0.2f, 0.3f);
	glVertex3f(x_3, y_3, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.3f, 0.2f, 0.7f);
	glVertex3f(x_4,y_4 , 0.0f);
	glColor3f(7.0f, 0.2f, 0.3f);
	glVertex3f(x_1, y_1, 0.0f);
	glEnd();

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) { //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
	glViewport(0, 0, w, h);
}
GLvoid Mouse(int button, int state, int x, int y) {
	convertDeviceXY2OpenglXY(x, y, &ox, &oy);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (x_1-0.2f < ox && ox < x_1+0.2f && y_1-0.2f < oy && oy < y_1+0.2f) 
			left_button = true,first_drag = true;
		if (x_2 - 0.2f < ox && ox < x_2 + 0.2f && y_2 - 0.2f < oy && oy < y_2 + 0.2f)
			left_button = true, second_drag = true;
		if (x_3 - 0.2f < ox && ox < x_3 + 0.2f && y_3 - 0.2f < oy && oy < y_3 + 0.2f)
			left_button = true, third_drag = true;
		if (x_4 - 0.2f < ox && ox < x_4 + 0.2f && y_4 - 0.2f < oy && oy < y_4 + 0.2f)
			left_button = true, fourth_drag = true;
		if (x_2 + 0.2f < ox && ox < x_1 - 0.2f && x_3 + 0.2f && x_4 - 0.2f && y_3 + 0.2f < oy && oy < y_2 - 0.2f && y_4 + 0.2f < oy && oy < y_1 - 0.2f) {
			left_button = true, big_drag = true;
			if (temp == 0) {
				tempx = ox;
				tempy = oy;
				tempx1 = x_1;
				tempy1 = y_1;
				tempx2 = x_2;
				tempy2 = y_2;
				tempx3 = x_3;
				tempy3 = y_3;
				tempx4 = x_4;
				tempy4 = y_4;
			}
			temp++;
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		left_button = false;
		first_drag = false;
		second_drag = false;
		third_drag = false;
		fourth_drag = false;
		big_drag = false;
		temp = 0;
	}
}
void Motion(int x, int y) {
	convertDeviceXY2OpenglXY(x, y, &ox, &oy);
	float k, r;
	if (left_button == true) {
		if (first_drag == true) {
			x_1 = ox;
			y_1 = oy;
			drawScene();
		}
		if (second_drag == true) {
			x_2 = ox;
			y_2 = oy;
			drawScene();
		}
		if (third_drag == true) {
			x_3 = ox;
			y_3 = oy;
			drawScene();
		}
		if (fourth_drag == true) {
			x_4 = ox;
			y_4 = oy;
			drawScene();
		}
		if (big_drag == true) {
			k = ox - tempx;
			r = oy - tempy;
			x_1 = tempx1 + k;
			x_2 = tempx2 + k;
			x_3 = tempx3 + k;
			x_4 = tempx4 + k;
			y_1 = tempy1 + r;
			y_2 = tempy2 + r;
			y_3 = tempy3 + r;
			y_4 = tempy4 + r;
			cout << x_1 << endl;
			//cout << k << "," << r << endl;
			drawScene();
		}
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
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

