#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <cstdlib>
#include <ctime>

using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid TimerFunction(int value);

double f_rand(void);
int screen = 0;
double r1, r2, r3;
void main(int argc, char** argv) { //--- 윈도우 출력하고 콜백함수 설정 { //--- 윈도우 생성하기
	srand((unsigned int)time(NULL));

	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(300, 300); // 윈도우의 위치 지정
	glutInitWindowSize(250, 250); // 윈도우의 크기 지정
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
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMainLoop(); // 이벤트 처리 시작

}


GLvoid drawScene() {//--- 콜백 함수: 그리기 콜백 함수 { glClearColor( 0.0f, 0.0f, 1.0f, 1.0f ); // 바탕색을 ‘blue’ 로 지정
	if (screen == 0)
		glClearColor(1.0, 1.0, 1.0, 1.0);
	else if (screen == 1)
		glClearColor(1.0, 0, 0, 1.0);
	else if (screen == 2)
		glClearColor(0, 1.0, 0, 1.0);
	else if (screen == 3)
		glClearColor(0, 0, 1.0, 1.0);
	else if (screen == 4)
		glClearColor(0, 0, 0, 1.0);
	else if (screen == 5)
		glClearColor(r1, r2, r3, 1.0);
	else if (screen == 6)
		glClearColor(r1, r2, r3, 1.0);


	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다.
	glutSwapBuffers(); // 화면에 출력하기

}
GLvoid Reshape(int w, int h) { //--- 콜백 함수: 다시 그리기 콜백 함수 
	glViewport(0, 0, w, h);

}

GLvoid Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'r':
		screen = 1;
			break;
	case 'w':
		screen = 0;
		break;
	case 'g':
		screen = 2;
		break;
	case 'b':
		screen = 3;
		break;
	case 'k':
		screen = 4;
		break;
	case 'a':
		screen = 5;
		r1 = f_rand();
		r2 = f_rand();
		r3 = f_rand();
		break;
	case 't':
		screen = 6;
		break;
	case 's':
		screen = 5;
		break;
	case 'q':
		exit(0);
		break;
	}
}

GLvoid TimerFunction(int value) {

	if (screen == 6) {
		r1 = f_rand();
		r2 = f_rand();
		r3 = f_rand();
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

double f_rand(void) {
	double a;
	a = rand() / (double)RAND_MAX;
	return a;
}