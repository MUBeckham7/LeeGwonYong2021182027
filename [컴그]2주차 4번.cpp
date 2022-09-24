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
void TimerFunction(int value);
double f_rand(void);
void collision_wall(GLfloat x, GLfloat y);
bool left_button;
float ox, oy;
GLfloat x_1, y_1, x_2 , y_2 ,x_3, y_3 ,x_4,y_4,x_5,y_5;
GLfloat box1_r = f_rand(), box1_g = f_rand(), box1_b = f_rand();
GLfloat box2_r = f_rand(), box2_g = f_rand(), box2_b = f_rand();
GLfloat box3_r = f_rand(), box3_g = f_rand(), box3_b = f_rand();
GLfloat box4_r = f_rand(), box4_g = f_rand(), box4_b = f_rand();
GLfloat box5_r = f_rand(), box5_g = f_rand(), box5_b = f_rand();
int box_count{};
bool a, b, c, d, e;
bool key_a, key_i, key_c, key_s, key_m, key_r, key_q;
bool wall_left, wall_bottom, wall_top, wall_right;
bool arrow_lb, arrow_lt, arrow_rb, arrow_rt;
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
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutMainLoop(); // �̺�Ʈ ó�� ����

}


GLvoid drawScene() {//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� { glClearColor( 0.0f, 0.0f, 1.0f, 1.0f ); // �������� ��blue�� �� ����
	glClearColor(0, 0, 0.1f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	if (a == true) {
		glColor3f(box1_r, box1_g, box1_b);
		glRectf(x_1, y_1, x_1 + 0.1f, y_1 + 0.1f);
	}
	if (b == true) {
		glColor3f(box2_r, box2_g, box2_b);
		glRectf(x_2, y_2, x_2 + 0.1f, y_2 + 0.1f);
	}
	if (c == true) {
		glColor3f(box3_r, box3_g, box3_b);
		glRectf(x_3, y_3, x_3 + 0.1f, y_3 + 0.1f);
	}
	if (d == true) {
		glColor3f(box4_r, box4_g, box4_b);
		glRectf(x_4, y_4, x_4 + 0.1f, y_4 + 0.1f);
	}
	if (e == true) {
		glColor3f(box5_r, box5_g, box5_b);
		glRectf(x_5, y_5, x_5 + 0.1f, y_5 + 0.1f);
	}

	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�

}
GLvoid Reshape(int w, int h) { //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y) {
	convertDeviceXY2OpenglXY(x, y, &ox, &oy);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {		
		cout << ox << "," << oy << endl;
		box_count++;
		if (box_count == 1) {
			a = true;
			x_1 = ox - 0.05f;
			y_1 = oy - 0.05f;
		}
		if (box_count == 2) {
			b = true;
			x_2 = ox - 0.05f;
			y_2 = oy - 0.05f;
		}
		if (box_count == 3) {
			c = true;
			x_3 = ox - 0.05f;
			y_3 = oy - 0.05f;
		}
		if (box_count == 4) {
			d = true;
			x_4 = ox - 0.05f;
			y_4 = oy - 0.05f;
		}
		if (box_count == 5) {
			e = true;
			x_5 = ox - 0.05f;
			y_5 = oy - 0.05f;
		}
	}

}

void Motion(int x, int y) {
	convertDeviceXY2OpenglXY(x, y, &ox, &oy);
	if (left_button == true) {

	}

}

void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		if (key_a == false)
			key_a = true;
		else
			key_a = false;
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

	if (key_a == true) {			//(-,-)���� �Ʒ� ����		//(+,+)������ �� ����   //(-,+) ���� �� ����  //(+,-) ������ �Ʒ� ����
		if (a == true) {
			if (wall_top == false&& wall_right == false && wall_bottom == false && wall_left == false) {		
				x_1 -= 0.01f;
				y_1 -= 0.01f;
			}
			collision_wall(x_1,y_1);
			if (wall_left == true) {
				x_1 += 0.01f;
				y_1 -= 0.01f;
			}
			if (wall_bottom == true) {
				x_1 += 0.01f;
				y_1 += 0.01f;
			}
			if (wall_right == true) {
				x_1 -= 0.01f;
				y_1 += 0.01f;
			}
			if (wall_top == true) {
				x_1 -= 0.01f;
				y_1 -= 0.01f;
			}
		}
		if (b == true) {
			x_2 += 0.01f;
			y_2 += 0.01f;
		}
		if (c == true) {
			x_3 -= 0.01f;
			y_3 += 0.01f;
		}
		if (d == true) {
			x_4 += 0.01f;
			y_4 -= 0.01f;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void collision_wall(GLfloat x, GLfloat y) {

	if (x < -1) {
		wall_top = false ,wall_right = false, wall_bottom = false ,wall_left = true;
	}
	if (y < -1) {
		wall_top = false, wall_right = false, wall_bottom = true, wall_left = false;
	}
	if (x + 0.1f > 1) {
		wall_top = false, wall_right = true, wall_bottom = false, wall_left = false;
	}
	if (y + 0.1f > 1) {
		wall_top = true, wall_right = false, wall_bottom = false, wall_left = false;
	}

}