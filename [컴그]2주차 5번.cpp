#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
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
void Collision_Erase();
double f_rand(void);
bool left_button;
float ox, oy;
GLfloat x_1, y_1;
double ran_r[100], ran_g[100], ran_b[100];
int x[100], y[100];
double R_ox[100], R_oy[100];
bool erase[100];
bool stop,eraser;
GLfloat eraser_x, eraser_y;
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
	glutDisplayFunc(drawScene); // 출력 함수의 지정

	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMainLoop(); // 이벤트 처리 시작

}


GLvoid drawScene() {//--- 콜백 함수: 그리기 콜백 함수 { glClearColor( 0.0f, 0.0f, 1.0f, 1.0f ); // 바탕색을 ‘blue’ 로 지정
	glClearColor(0, 0, 0.1f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기	

	if (stop == false) {
		for (int i = 0; i < 100; ++i) {
			if (x[i] == 0 && y[i] == 0) {
				x[i] = rand() % 800;
				y[i] = rand() % 600;
				convertDeviceXY2OpenglXY(x[i], y[i], &ox, &oy);
				R_ox[i] = ox, R_oy[i] = oy;
				ran_r[i] = f_rand();
				ran_g[i] = f_rand();
				ran_b[i] = f_rand();
				erase[i] = true;
			}
			if (i == 99)
				stop = true;
		}
	}

	for (int i = 0; i < 100; ++i) {
		if (erase[i] == true) {
			glColor3f(ran_r[i], ran_g[i], ran_b[i]);
			glRectf(R_ox[i], R_oy[i], R_ox[i] + 0.03f, R_oy[i] + 0.03f);
		}
	}

	if (eraser == true) {
		glColor3f(1.0, 1.0, 1.0);
		glRectf(eraser_x, eraser_y, eraser_x+0.1, eraser_y+0.1);
	}

	Collision_Erase();

	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다.
	glutSwapBuffers(); // 화면에 출력하기

}
GLvoid Reshape(int w, int h) { //--- 콜백 함수: 다시 그리기 콜백 함수 
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y) {
	convertDeviceXY2OpenglXY(x, y, &ox, &oy);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		left_button = true;
		eraser = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		left_button = false;
		eraser = false;
	}
}

void Motion(int x, int y) {
	convertDeviceXY2OpenglXY(x, y, &ox, &oy);
	if (left_button == true) {
		eraser_x = ox-0.05;
		eraser_y = oy-0.05;

		drawScene();
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

void Collision_Erase() {

	for (int i = 0; i < 100; ++i) {

		if (R_ox[i] < eraser_x && R_oy[i] < eraser_y && eraser_x < R_ox[i] + 0.03f && eraser_y < R_oy[i] + 0.03f)	//좌측 하단
			erase[i] = false;

		if (R_ox[i] < eraser_x && R_oy[i] < eraser_y + 0.1 && eraser_x < R_ox[i] + 0.03f && eraser_y + 0.1 < R_oy[i] + 0.03f) //좌측 상단
			erase[i] = false;

		if (R_ox[i] < eraser_x + 0.1 && R_oy[i] < eraser_y + 0.1 && eraser_y + 0.1 < R_oy[i] + 0.03f && eraser_x +0.1 < R_ox[i] + 0.03f) //우측 상단
			erase[i] = false;

		if(R_ox[i] < eraser_x+0.1 && eraser_y < R_oy[i]+0.03f && eraser_x+0.1 < R_ox[i]+0.03f && R_oy[i] < eraser_y)
			erase[i] = false;

		if (eraser_x < R_ox[i] && eraser_y < R_oy[i] && R_ox[i] + 0.03f < eraser_x + 0.1 && R_oy[i] + 0.03f < eraser_y + 0.1)
			erase[i] = false;

	}

}