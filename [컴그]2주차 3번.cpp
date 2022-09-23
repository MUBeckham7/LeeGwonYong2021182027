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
double f_rand(void);
int screen = 0;
GLfloat ox;
GLfloat oy;
GLfloat R1x1 = -0.1f;
GLfloat R1y1 = -0.1f;
GLfloat R1x2 = 0.1f;
GLfloat R1y2 = 0.1f;
GLfloat Garo{};
GLfloat Sero{};
bool left_button;
int drag = 0;
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
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(R1x1+Garo, R1y1+Sero, R1x2+Garo, R1y2+Sero);
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다.
	glutSwapBuffers(); // 화면에 출력하기

}
GLvoid Reshape(int w, int h) { //--- 콜백 함수: 다시 그리기 콜백 함수 
	glViewport(0, 0, w, h);

}

GLvoid Mouse(int button, int state, int x, int y) {
	convertDeviceXY2OpenglXY(x, y, &ox, &oy);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (ox > R1x1 && oy > R1y1 && ox < R1x2 && oy < R1y2) {
			drag = 1;
			left_button = true;

		}
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

void Motion(int x, int y) {
	convertDeviceXY2OpenglXY(x, y, &ox, &oy);
	if (left_button == true) {
		//cout << ox << "," << oy <<",";
		Garo = ox - R1x1;
		Sero = oy - R1y1;

		if (drag == 1) {
			GLvoid drawScene(); {//--- 콜백 함수: 그리기 콜백 함수 { glClearColor( 0.0f, 0.0f, 1.0f, 1.0f ); // 바탕색을 ‘blue’ 로 지정
				glClearColor(0, 0, 0.1f, 0.1f);
				glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
				glColor3f(1.0f, 1.0f, 1.0f);
				if (drag == 0)
					glRectf(R1x1 + Garo, R1y1 + Sero, R1x2 + Garo, R1y2 + Sero);

				if (drag == 1)
					glRectf(R1x1 + Garo, R1y1 + Sero, R1x2 + Garo, R1y2 + Sero);
				// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다.
				glutSwapBuffers(); // 화면에 출력하기

			}
		}
	
		//cout << Garo << "," << Sero << endl;
	}
}