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
void DrawFirst();
void DrawSecond();
void DrawThird();
void DrawFourth();
double f_rand(void);
bool left_button;
float ox, oy;
GLfloat x_1, y_1;
GLfloat first_x1 = 0.3f, first_y1 = 0.3f, first_x2 = 0.7f, first_y2 = 0.3f, first_x3 = 0.5f, first_y3 = 0.7f, first_x4 = 0.5f, first_y4 = 0.7f;
GLfloat second_x1=-0.7f, second_y1=0.3f , second_x2 = -0.3f, second_y2 = 0.7f, second_x3 = -0.3f, second_y3 = 0.7f;
GLfloat third_x1 = -0.3f, third_y1 = -0.3f, third_x2 = -0.7f, third_y2 = -0.3f, third_x3 = -0.7f, third_y3 = -0.7f, third_x4 = -0.3f, third_y4 = -0.7f, third_x5 = -0.3f, third_y5 = -0.3f;
GLfloat fourth_x1 = 0.5f, fourth_y1 = -0.1f, fourth_x2 = 0.7f, fourth_y2 = -0.25f, fourth_x3 = 0.6f, fourth_y3 = -0.5f, fourth_x4 = 0.4f, fourth_y4 = -0.5f, fourth_x5 = 0.3f, fourth_y5 = -0.25f;

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
	glVertex3f(0.0f, -1.0f,0.0f);
	glVertex3f(0.0f, 1.0f,0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();

	DrawFirst();
	DrawSecond();
	DrawThird();
	DrawFourth();

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) { //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
	glViewport(0, 0, w, h);
}
GLvoid Mouse(int button, int state, int x, int y) {
	convertDeviceXY2OpenglXY(x, y, &ox, &oy);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {


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

	if (second_x2 >= -0.5f) 
		second_x2 -= 0.01f;
	if (second_y3 >= 0.31f)
		second_y3 -= 0.01f;
		
	if (first_x3 >= 0.31f)
		first_x3 -= 0.01f;
	if (first_x4 <= 0.7f)
		first_x4 += 0.01f;

	if (third_x1 >= -0.5f) 
		third_x1 -= 0.01f;
	if (third_y1 <= -0.1f)
		third_y1 += 0.01f;
	if (third_y2 <= -0.25f)
		third_y2 += 0.01f;
	if (third_x3 <= -0.6f)
		third_x3 += 0.01f;
	if (third_y3 <= -0.5f)
		third_y3 += 0.01f;
	if (third_x4 >= -0.4f)
		third_x4 -= 0.01f;
	if (third_y4 <= -0.5f)
		third_y4 += 0.01f;
	if (third_y5 <= -0.25f)
		third_y5 += 0.01f;


	if(fourth_x2 > 0.5f)
		fourth_x2 -= 0.01f;
	if (fourth_x3 > 0.5f)
		fourth_x3 -= 0.01f;
	if (fourth_x4 < 0.5f)
		fourth_x4 += 0.01f;
	if (fourth_x5 < 0.5f)
		fourth_x5 += 0.01f;
	if (fourth_y1 > -0.4f)
		fourth_y1 -= 0.01f;
	if (fourth_y2 >= -0.4f)
		fourth_y2 -= 0.01f;
	if (fourth_y3 <= -0.4f)
		fourth_y3 += 0.01f;
	if (fourth_y4 <= -0.4f)
		fourth_y4 += 0.01f;
	if (fourth_y5 >= -0.4f)
		fourth_y5 -= 0.01f;


	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void DrawFirst() {
	glColor3f(0.1f, 0.3f, 0.7f);

	glBegin(GL_TRIANGLES);
	glVertex3f(first_x2, first_y2, 0.0f);
	glVertex3f(first_x1, first_y1, 0.0f);
	glVertex3f(first_x3, first_y3, 0.0f);

	if (first_x3 < 0.5f) {
		glColor3f(0.1f, 0.6f, 0.7f);
	glVertex3f(first_x2, first_y2, 0.0f);
	glVertex3f(first_x3, first_y3, 0.0f);
	glVertex3f(first_x4, first_y4, 0.0f);
	}
	
	glEnd();
}

void DrawSecond() {

	glColor3f(0.7f, 0.1f, 0.3f);
	if (second_y3 < 0.31f)
		glBegin(GL_TRIANGLES);
	else
		glBegin(GL_LINE_LOOP);
	glVertex3f(second_x1, second_y1, 0.0f);
	glVertex3f(second_x2, second_y2, 0.0f);
	glVertex3f(second_x3, second_y3, 0.0f);
	glEnd();

}

void DrawThird() {

	glColor3f(0.8f, 0.7f, 0.1f);
	glBegin(GL_TRIANGLES);
	glVertex3f(third_x1, third_y1, 0.0f);
	glVertex3f(third_x2, third_y2, 0.0f);
	glVertex3f(third_x3, third_y3, 0.0f);

	glColor3f(0.1f, 0.7f, 0.8f);
	glVertex3f(third_x1, third_y1, 0.0f);
	glVertex3f(third_x4, third_y4, 0.0f);
	glVertex3f(third_x3, third_y3, 0.0f);


	if (third_x1 <= 0.3f) {
		glColor3f(0.7f, 1.0f, 0.1f);
		glVertex3f(third_x1, third_y1, 0.0f);
		glVertex3f(third_x4, third_y4, 0.0f);
		glVertex3f(third_x5, third_y5, 0.0f);
	}
	//
	glEnd();
}

void DrawFourth() {
	glColor3f(0.7f, 0.0f, 0.1f);
	glBegin(GL_POLYGON);
	glVertex3f(fourth_x1, fourth_y1, 0.0f);
	glVertex3f(fourth_x2, fourth_y2, 0.0f);
	glVertex3f(fourth_x3, fourth_y3, 0.0f);
	glVertex3f(fourth_x4, fourth_y4, 0.0f);
	glVertex3f(fourth_x5, fourth_y5, 0.0f);

	glEnd();
}