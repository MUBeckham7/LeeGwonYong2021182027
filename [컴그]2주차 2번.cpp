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
double f_rand(void);
int screen = 0;
double r1 = f_rand(), r2 = f_rand(), r3=f_rand();
GLfloat x_1 = -0.7;
GLfloat y_1 = -0.7;
GLfloat x_2 = 0.7;
GLfloat y_2 = 0.7;
GLfloat ox;
GLfloat oy;
double b1 = 1.0, b2 = 1.0, b3 = 1.0;
int main(int argc, char** argv) { //--- ������ ����ϰ� �ݹ��Լ� ���� { //--- ������ �����ϱ�
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
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutMouseFunc(Mouse);
	glutMainLoop(); // �̺�Ʈ ó�� ����

}


GLvoid drawScene() {//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� { glClearColor( 0.0f, 0.0f, 1.0f, 1.0f ); // �������� ��blue�� �� ����
	

	glClearColor(b1,b2,b3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.
	glColor3f(r1,r2,r3);
	glRectf(x_1,y_1, x_2, y_2);

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�

}
GLvoid Reshape(int w, int h) { //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
	glViewport(0, 0, w, h);

}
GLvoid Mouse(int button, int state, int x, int y) {

		convertDeviceXY2OpenglXY(x, y, &ox, &oy);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {

		if ((ox > x_1 && oy > y_1) && (ox < x_2 && oy < y_2)) {
			cout << "����";

			r1 = f_rand();
			r2 = f_rand();
			r3 = f_rand();
		}
		else {
			b1 = f_rand();
			b2 = f_rand();
			b3 = f_rand();
		}
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

		if ((ox > x_1 && oy > y_1) && (ox < x_2 && oy < y_2)) {
			x_1 += 0.01f;
			y_1 += 0.01f;
			x_2 -= 0.01f;
			y_2 -= 0.01f;
		}
		else {
			x_1 -= 0.01f;
			y_1 -= 0.01f;
			x_2 += 0.01f;
			y_2 += 0.01f;
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