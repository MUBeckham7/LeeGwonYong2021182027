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
	glutDisplayFunc(drawScene); // ��� �Լ��� ����

	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutMainLoop(); // �̺�Ʈ ó�� ����

}


GLvoid drawScene() {//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� { glClearColor( 0.0f, 0.0f, 1.0f, 1.0f ); // �������� ��blue�� �� ����
	glClearColor(0, 0, 0.1f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�	

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

	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�

}
GLvoid Reshape(int w, int h) { //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
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

		if (R_ox[i] < eraser_x && R_oy[i] < eraser_y && eraser_x < R_ox[i] + 0.03f && eraser_y < R_oy[i] + 0.03f)	//���� �ϴ�
			erase[i] = false;

		if (R_ox[i] < eraser_x && R_oy[i] < eraser_y + 0.1 && eraser_x < R_ox[i] + 0.03f && eraser_y + 0.1 < R_oy[i] + 0.03f) //���� ���
			erase[i] = false;

		if (R_ox[i] < eraser_x + 0.1 && R_oy[i] < eraser_y + 0.1 && eraser_y + 0.1 < R_oy[i] + 0.03f && eraser_x +0.1 < R_ox[i] + 0.03f) //���� ���
			erase[i] = false;

		if(R_ox[i] < eraser_x+0.1 && eraser_y < R_oy[i]+0.03f && eraser_x+0.1 < R_ox[i]+0.03f && R_oy[i] < eraser_y)
			erase[i] = false;

		if (eraser_x < R_ox[i] && eraser_y < R_oy[i] && R_ox[i] + 0.03f < eraser_x + 0.1 && R_oy[i] + 0.03f < eraser_y + 0.1)
			erase[i] = false;

	}

}