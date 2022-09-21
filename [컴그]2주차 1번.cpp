#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
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
void main(int argc, char** argv) { //--- ������ ����ϰ� �ݹ��Լ� ���� { //--- ������ �����ϱ�
	srand((unsigned int)time(NULL));

	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(300, 300); // �������� ��ġ ����
	glutInitWindowSize(250, 250); // �������� ũ�� ����
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
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutMainLoop(); // �̺�Ʈ ó�� ����

}


GLvoid drawScene() {//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� { glClearColor( 0.0f, 0.0f, 1.0f, 1.0f ); // �������� ��blue�� �� ����
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


	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�

}
GLvoid Reshape(int w, int h) { //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
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