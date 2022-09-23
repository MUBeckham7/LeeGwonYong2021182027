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
double f_rand(void);
bool left_button;
float ox;
float oy;
GLfloat x_1 = -0.1f;
GLfloat y_1 = -0.1f;
GLfloat x_2 = -0.4f;
GLfloat y_2 = -0.4f;
bool a{},b{};
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
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutMainLoop(); // �̺�Ʈ ó�� ����

}


GLvoid drawScene() {//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� { glClearColor( 0.0f, 0.0f, 1.0f, 1.0f ); // �������� ��blue�� �� ����
	glClearColor(0, 0, 0.1f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(x_1,y_1,x_1+0.2f,y_1+0.2f);
	glColor3f(0.6f, 0.2f, 0);
	glRectf(x_2, y_2, x_2 + 0.2f, y_2 + 0.2f);
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�

}
GLvoid Reshape(int w, int h) { //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y) {
	convertDeviceXY2OpenglXY(x, y, &ox, &oy);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (x_1 < ox && ox < x_1 + 0.2f && y_1 < oy && oy < y_1+0.2f) {
			left_button = true;
			a = true;
		}
		if (x_2 < ox && ox < x_2 + 0.2f && y_2 < oy && oy < y_2 + 0.2f) {
			left_button = true;
			b = true;
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		a = false;
		b = false;

	}
}

void Motion(int x, int y) {
	convertDeviceXY2OpenglXY(x, y, &ox, &oy);
	if ( a == true && left_button == true) {
		//cout << ox << "," << oy <<",";
		//cout << Garo << "," << Sero << endl;
	}
	if (b == true && left_button == true) {
		cout << "B ����";
	}
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
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
