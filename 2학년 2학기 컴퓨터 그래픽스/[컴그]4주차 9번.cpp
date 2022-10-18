#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#pragma comment (lib,"freeglut.lib")
#pragma commet (lib,"glew32.lib")
#pragma comment (lib,"glew32.lib")

#include <gl/glew.h> //--- 필요한 헤더파일 include
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


void main(int argc, char** argv) { //--- 윈도우 출력하고 콜백함수 설정 { //--- 윈도우 생성하기
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("Example1"); // 윈도우 생성(윈도우 이름)
		//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK
		) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMainLoop(); // 이벤트 처리 시작
}
GLvoid drawScene() {//--- 콜백 함수: 그리기 콜백 함수 { glClearColor( 0.0f, 0.0f, 1.0f, 1.0f ); // 바탕색을 ‘blue’ 로 지정
	glClearColor(r, g, b, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다.

	for (iter = circle.begin(); iter != circle.end(); ++iter)
	{
		DrawCircle(iter->x, iter->y, iter->rad, iter->degree, iter->check, iter->tmpX, iter->tmpY);
	}


	glutSwapBuffers(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h) { //--- 콜백 함수: 다시 그리기 콜백 함수 
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