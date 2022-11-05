#define _CRT_SECURE_NO_WARNINGS

#pragma comment (lib,"freeglut.lib")
#pragma commet (lib,"glew32.lib")
#pragma comment (lib,"glew32.lib")
#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glut.h>
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
BOOL one = false, two = false, three = false, four = false , five=false, six=false,seven =false,eight =false,nine = false,ten =false;
int number_one = 0, number_two = 0, number_three = 0, number_four = 0, number_five = 0, number_six = 0, number_seven = 0, number_eight = 0, number_nine = 0, number_ten = 0;
GLfloat x_1, y_1;
void main(int argc, char** argv) { //--- 윈도우 출력하고 콜백함수 설정 { //--- 윈도우 생성하기
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
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
	glClearColor(0, 0, 0.1f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	glEnable(GL_DEPTH_TEST);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0, 300, 0);
	glVertex3f(0, -300, 0);
	glVertex3f(-400, 0, 0);
	glVertex3f(400, 0, 0);
	glEnd();

	glPushMatrix();
	glRotatef(0.0f, 1.0f, 1.0f, 0.0f);

	glutSolidCube(1.2f);
	if (six == true) {
		glColor3f(0.0f, 0.0f, 0.2f);
		glBegin(GL_QUADS);					//정육면체 앞쪽
		glVertex3f(-170, -220, 0);
		glVertex3f(30, -220, 0);
		glVertex3f(30, 150, 0);
		glVertex3f(-170, 150, 0);
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-170, -220, 0);
		glVertex3f(30, -220, 0);
		glVertex3f(30, 150, 0);
		glVertex3f(-170, 150, 0);
		glEnd();
	}
	if (two == true) {
		glColor3f(0.3f, 0.1f, 0.9f);
		glBegin(GL_QUADS);					//정육면체 윗면
		glVertex3f(-170, 150, 0);
		glVertex3f(-100, 220, 0);
		glVertex3f(100, 220, 0);
		glVertex3f(30, 150, 0);
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-170, 150, 0);
		glVertex3f(-100, 220, 0);
		glVertex3f(100, 220, 0);
		glVertex3f(30, 150, 0);
		glEnd();
	}
	if (three == true) {
		glColor3f(0.4f, 0.0f, 0.2f);
		glBegin(GL_QUADS);					//정육면체 오른쪽
		glVertex3f(30, -220, 0);
		glVertex3f(100, -150, 0);
		glVertex3f(100, 220, 0);
		glVertex3f(30, 150, 0);
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		glVertex3f(30, -220, 0);
		glVertex3f(100, -150, 0);
		glVertex3f(100, 220, 0);
		glVertex3f(30, 150, 0);
		glEnd();
	}	
	if (four == true) {
		glColor3f(0.1f, 0.7f, 0.8f);
		glBegin(GL_QUADS);					//정육면체 왼쪽
		glVertex3f(-100, -150, 0);
		glVertex3f(-170, -220, 0);
		glVertex3f(-170, 150, 0);
		glVertex3f(-100, 220, 0);
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-100, -150, 0);
		glVertex3f(-170, -220, 0);
		glVertex3f(-170, 150, 0);
		glVertex3f(-100, 220, 0);
		glEnd();
	}
	if (five == true) {
		glColor3f(0.5f, 0.5f, 0.5f);
		glBegin(GL_QUADS);					//정육면체 뒷쪽
		glVertex3f(-100, -150, 0);
		glVertex3f(100, -150, 0);
		glVertex3f(100, 220, 0);
		glVertex3f(-100, 220, 0);
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-100, -150, 0);
		glVertex3f(100, -150, 0);
		glVertex3f(100, 220, 0);
		glVertex3f(-100, 220, 0);
		glEnd();
	}
	if (one == true) {
		glColor3f(0.7f, 0.5f, 0.2f);
		glBegin(GL_QUADS);					//정육면체 아랫면
		glVertex3f(-100, -150, 0);
		glVertex3f(-170, -220, 0);
		glVertex3f(30, -220, 0);
		glVertex3f(100, -150, 0);
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-100, -150, 0);
		glVertex3f(-170, -220, 0);
		glVertex3f(30, -220, 0);
		glVertex3f(100, -150, 0);
		glEnd();
	}
	if (ten == true) {
		glColor3f(0.0f, 0.9f, 0.9f);
		glBegin(GL_TRIANGLES);					//정육면체 앞쪽
		glVertex3f(0, 50, 0);
		glVertex3f(150, -100, 0);
		glVertex3f(-100, -250, 0);
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 50, 0);
		glVertex3f(150, -100, 0);
		glVertex3f(-100, -250, 0);
		glEnd();
	}

	if (seven == true) {
		glColor3f(0.9f, 0.9f, 0.2f);
		glBegin(GL_TRIANGLES);					//정사면체 아랫쪽
		glVertex3f(0, -100, 0);
		glVertex3f(150, -100, 0);
		glVertex3f(-100, -250, 0);
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, -100, 0);
		glVertex3f(150, -100, 0);
		glVertex3f(-100, -250, 0);
		glEnd();
	}
	if (eight == true) {
		glColor3f(0.4f, 0.2f, 0.3f);
		glBegin(GL_TRIANGLES);					//정사면체 왼쪽
		glVertex3f(0, -100, 0);
		glVertex3f(-100, -250, 0);
		glVertex3f(0, 50, 0);
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, -100, 0);
		glVertex3f(-100, -250, 0);
		glVertex3f(0, 50, 0);
		glEnd();
	}
	if (nine == true) {
		glColor3f(0.8f, 0.0f, 0.6f);
		glBegin(GL_TRIANGLES);					//정육면체 오른쪽
		glVertex3f(0, -100, 0);
		glVertex3f(0, 50, 0);
		glVertex3f(150, -100, 0);
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, -100, 0);
		glVertex3f(0, 50, 0);
		glVertex3f(150, -100, 0);
		glEnd();
	}


	glPopMatrix();
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다.

	glutSwapBuffers(); // 화면에 출력하기
	glDisable(GL_DEPTH_TEST);
}
GLvoid Reshape(int w, int h) { //--- 콜백 함수: 다시 그리기 콜백 함수
	GLdouble nRange = 300.0f;
	

	glViewport(0, 0, w, h);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	if (w <= h) {
		glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange,nRange);
	}
	else
		glOrtho(-nRange * h / w, nRange * h / w, -nRange , nRange , -nRange, nRange);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

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
	case '1':
		number_one++;
		if (number_one % 2 == 1)
			one = true;
		else
			one = false;
		break;
	case '2':
		number_two++;
		if (number_two % 2 == 1)
			two = true;
		else
			two = false;
		break;
	case '3':
		number_three++;
		if (number_three % 2 == 1)
			three = true;
		else
			three = false;
		break;
	case '4':
		number_four++;
		if (number_four % 2 == 1)
			four = true;
		else
			four = false;
		break;
	case '5':
		number_five++;
		if (number_five % 2 == 1)
			five = true;
		else
			five = false;
		break;
	case '6':
		number_six++;
		if (number_six % 2 == 1)
			six = true;
		else
			six = false;
		break;
	case '7':
		number_seven++;
		if (number_seven % 2 == 1)
			seven = true;
		else
			seven = false;
		break;
	case '8':
		number_eight++;
		if (number_eight % 2 == 1)
			eight = true;
		else
			eight = false;
		break;
	case '9':
		number_nine++;
		if (number_nine % 2 == 1)
			nine = true;
		else
			nine = false;
		break;
	case '0':
		number_ten++;
		if (number_ten % 2 == 1)
			ten = true;
		else
			ten = false;
		break;
	case 'a':
		number_one++;
		number_two++;
		if (number_one % 2 == 1 && number_two % 2 == 1) {
			one = true;
			two = true;
		}
		else {
			one = false;
			two = false;
		}
		break;
	case 'b':
		number_three++;
		number_four++;
		if (number_three % 2 == 1 && number_four % 2 == 1) {
			three = true;
			four = true;
		}
		else {
			three = false;
			four = false;
		}
		break;
	case 'c':
		number_five++;
		number_six++;
		if (number_five % 2 == 1 && number_six % 2 == 1) {
			five = true;
			six = true;
		}
		else {
			five = false;
			six = false;
		}
		break;
	case 'e':
		number_seven++;
		number_eight++;
		seven = true;
		if (number_eight % 2 == 1) {
			seven = true;
			eight = true;
		}
		else {
			seven = false;
			eight = false;
		}
		break;
	case 'f':
		number_seven++;
		number_nine++;
		seven = true;
		if ( number_nine % 2 == 1) {
			seven = true;
			nine = true;
		}
		else {
			seven = false;
			nine = false;
		}
		break;
	case 'g':
		number_seven++;
		number_ten++;
		seven = true;
		if (number_ten % 2 == 1) {
			seven = true;
			ten = true;
		}
		else {
			seven = false;
			ten = false;
		}
		break;
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