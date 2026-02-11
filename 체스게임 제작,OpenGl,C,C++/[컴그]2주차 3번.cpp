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
void Keyboard(unsigned char key, int x, int y);
double f_rand(void);
bool left_button;
float ox;
float oy;
GLfloat x_1 = -0.1f;
GLfloat y_1 = -0.1f;
GLfloat x_2 = -0.1f;
GLfloat y_2 = -0.1f;
GLfloat x_3 = -0.1f;
GLfloat y_3 = -0.1f;
GLfloat x_4 = -0.1f;
GLfloat y_4 = -0.1f;
GLfloat x_5 = -0.1f;
GLfloat y_5 = -0.1f;
GLfloat g1, s1, g2, s2, g3, s3 ,g4,s4 ,g5,s5;
bool a, b, c, d,e;
int box{}, box1{}, box2{}, box3{}, box4{};
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
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMainLoop(); // 이벤트 처리 시작

}


GLvoid drawScene() {//--- 콜백 함수: 그리기 콜백 함수 { glClearColor( 0.0f, 0.0f, 1.0f, 1.0f ); // 바탕색을 ‘blue’ 로 지정
	glClearColor(0, 0, 0.1f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(x_1 + g1, y_1 + s1, x_1 + g1 + 0.2f, y_1 + s1 + 0.2f);

	if (box1 == 1) {
		glColor3f(0.6f, 0.2f, 0);
		glRectf(x_2 + g2, y_2 + s2, x_2 + g2 + 0.2f, y_2 + s2 + 0.2f);
	}

	if (box2 == 1) {
		glColor3f(0.2f, 0.7f, 0.3f);
		glRectf(x_3 + g3, y_3 + s3, x_3 + g3 + 0.2f, y_3 + s3 + 0.2f);
	}

	if (box3 == 1) {
		glColor3f(0, 0.1f, 0.9f);
		glRectf(x_4 + g4, y_4 + s4, x_4 + g4 + 0.2f, y_4 + s4 + 0.2f);
	}
	if (box4 == 1) {
		glColor3f(0.9f, 0.4f, 0.3f);
		glRectf(x_5 + g5, y_5 + s5, x_5 + g5 + 0.2f, y_5 + s5 + 0.2f);
	}

	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다.
	glutSwapBuffers(); // 화면에 출력하기

}
GLvoid Reshape(int w, int h) { //--- 콜백 함수: 다시 그리기 콜백 함수 
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y) {
	convertDeviceXY2OpenglXY(x, y, &ox, &oy);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (x_1 + g1 < ox && ox < x_1 + g1 + 0.2f && y_1 + s1< oy && oy < y_1 + s1 + 0.2f) {
			left_button = true;
			a = true;
		}
		if (box1 == 1 && x_2 + g2< ox && ox < x_2 + g2 + 0.2f && y_2 + s2 < oy && oy < y_2 + s2 + 0.2f) {
			left_button = true;
			b = true;
		}
		if (box2 == 1 && x_3 + g3 < ox && ox < x_3 + g3 + 0.2f && y_3 + s3 < oy && oy < y_3 + s3 + 0.2f) {
			left_button = true;
			c = true;
		}
		if (box3 == 1 && x_4 + g4 < ox && ox < x_4 + g4 + 0.2f && y_4 + s4 < oy && oy < y_4 + s4 + 0.2f) {
			left_button = true;
			d = true;
		}
		if (box4 == 1 && x_5 + g5 < ox && ox < x_5 + g5 + 0.2f && y_5 + s5 < oy && oy < y_5 + s5 + 0.2f) {
			left_button = true;
			e = true;
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		a = false;
		b = false;
		c = false;
		d = false;
		e = false;
	}
}

void Motion(int x, int y) {
	convertDeviceXY2OpenglXY(x, y, &ox, &oy);
	if (a == true &&left_button == true && ( b == true || c == true || d == true || e== true)) {
		a = false;
	}
	if (b == true && left_button == true && (c == true || d == true || e == true )) {
		b = false;
	}
	if (c == true && left_button == true && (d == true || e == true )) {
		c = false;
	}
	if (d == true && left_button == true && (e == true )) {
		d = false;
	}


	if (a == true && left_button == true) {
		//cout << Garo << "," << Sero << endl;
		g1 = ox - x_1;
		s1 = oy - y_1;
		drawScene();
	}
	if (b == true && left_button == true) {
		g2 = ox - x_2;
		s2 = oy - y_2;
		drawScene();
	}
	if (c == true && left_button == true) {
		g3 = ox - x_3;
		s3 = oy - y_3;
		drawScene();
	}
	if (d == true && left_button == true) {
		g4 = ox - x_4;
		s4 = oy - y_4;
		drawScene();
	}
	if (e == true && left_button == true) {
		g5 = ox - x_5;
		s5 = oy - y_5;
		drawScene();
	}


}

void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		box++;
		if (box == 1) {
			box1 = 1;
		}
		if (box == 2) {
			box2 = 1;
		}
		if (box == 3) {
			box3 = 1;
		}
		if (box == 4) {
			box4 = 1;
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
