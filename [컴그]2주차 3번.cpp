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
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(R1x1+Garo, R1y1+Sero, R1x2+Garo, R1y2+Sero);
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�

}
GLvoid Reshape(int w, int h) { //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
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
			GLvoid drawScene(); {//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� { glClearColor( 0.0f, 0.0f, 1.0f, 1.0f ); // �������� ��blue�� �� ����
				glClearColor(0, 0, 0.1f, 0.1f);
				glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
				glColor3f(1.0f, 1.0f, 1.0f);
				if (drag == 0)
					glRectf(R1x1 + Garo, R1y1 + Sero, R1x2 + Garo, R1y2 + Sero);

				if (drag == 1)
					glRectf(R1x1 + Garo, R1y1 + Sero, R1x2 + Garo, R1y2 + Sero);
				// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.
				glutSwapBuffers(); // ȭ�鿡 ����ϱ�

			}
		}
	
		//cout << Garo << "," << Sero << endl;
	}
}