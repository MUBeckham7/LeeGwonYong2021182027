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
void TimerFunction(int value);
double f_rand(void);
void collision_wall_1(GLfloat x, GLfloat y);
void collision_wall_2(GLfloat x, GLfloat y);
void collision_wall_3(GLfloat x, GLfloat y);
void collision_wall_4(GLfloat x, GLfloat y);
bool left_button;
float ox, oy;
GLfloat x_1, y_1, x_2 , y_2 ,x_3, y_3 ,x_4,y_4,x_5,y_5;
GLfloat temp_x1, temp_y1, temp_x2, temp_y2, temp_x3, temp_y3, temp_x4, temp_y4, temp_x5, temp_y5;
GLfloat box1_r = f_rand(), box1_g = f_rand(), box1_b = f_rand();
GLfloat box2_r = f_rand(), box2_g = f_rand(), box2_b = f_rand();
GLfloat box3_r = f_rand(), box3_g = f_rand(), box3_b = f_rand();
GLfloat box4_r = f_rand(), box4_g = f_rand(), box4_b = f_rand();
GLfloat box5_r = f_rand(), box5_g = f_rand(), box5_b = f_rand();
int box_count{};
bool a, b, c, d, e;
bool key_a, key_i, key_c, key_s, key_m, key_r, key_q;
bool wall_left1, wall_bottom1, wall_top1, wall_right1;
bool wall_left2, wall_bottom2, wall_top2, wall_right2;
bool wall_left3, wall_bottom3, wall_top3, wall_right3;
bool wall_left4, wall_bottom4, wall_top4, wall_right4;
bool left_x1, right_x1, top_y1, bottom_y1;
bool left_x2, right_x2, top_y2, bottom_y2;
bool left_x3, right_x3, top_y3, bottom_y3;
bool left_x4, right_x4, top_y4, bottom_y4;
int count_a{}, count_b{}, count_c{}, count_d{};
double size_x1 = 1, size_x2 =1 , size_y2=1 , size_y3=1 , size_x4 =1 , size_y4 =1;
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
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMainLoop(); // 이벤트 처리 시작

}


GLvoid drawScene() {//--- 콜백 함수: 그리기 콜백 함수 { glClearColor( 0.0f, 0.0f, 1.0f, 1.0f ); // 바탕색을 ‘blue’ 로 지정
	glClearColor(0, 0, 0.1f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	if (a == true) {
		glColor3f(box1_r, box1_g, box1_b);
		glRectf(x_1*size_x1, y_1, x_1 + 0.1f, y_1 + 0.1f);
	}
	if (b == true) {
		glColor3f(box2_r, box2_g, box2_b);
		glRectf(x_2*size_x2, y_2*size_y2, x_2 + 0.1f, y_2 + 0.1f);
	}
	if (c == true) {
		glColor3f(box3_r, box3_g, box3_b);
		glRectf(x_3, y_3, x_3 + 0.1f, (y_3 + 0.1f) * size_y3);
	}
	if (d == true) {
		glColor3f(box4_r, box4_g, box4_b);
		glRectf(x_4, y_4, (x_4 + 0.1f)*size_x4, (y_4 + 0.1f)*size_y4);
	}
	if (e == true) {
		glColor3f(box5_r, box5_g, box5_b);
		glRectf(x_5, y_5, x_5 + 0.1f, y_5 + 0.1f);
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
		cout << ox << "," << oy << endl;
		box_count++;
		if (box_count == 1) {
			a = true;
			x_1 = ox - 0.05f;
			y_1 = oy - 0.05f;
			temp_x1 = x_1;
			temp_y1 = y_1;
		}
		if (box_count == 2) {
			b = true;
			x_2 = ox - 0.05f;
			y_2 = oy - 0.05f;
			temp_x2 = x_2;
			temp_y2 = y_2;
		}
		if (box_count == 3) {
			c = true;
			x_3 = ox - 0.05f;
			y_3 = oy - 0.05f;
			temp_x3 = x_3;
			temp_y3 = y_3;
		}
		if (box_count == 4) {
			d = true;
			x_4 = ox - 0.05f;
			y_4 = oy - 0.05f;
			temp_x4 = x_4;
			temp_y4 = y_4;
		}
		if (box_count == 5) {
			e = true;
			x_5 = ox - 0.05f;
			y_5 = oy - 0.05f;
			temp_x5 = x_5;
			temp_y5 = y_5;
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
	case 'i':
		if (key_i == false)
			key_i = true;
		else
			key_i = false;
		break;
	case 'c':
		if (key_c == false)
			key_c = true;
		else
			key_c = false;
		break;
	case 's':
		key_a = false;
		key_i = false;
		key_c = false;
		break;
	case 'm':
		if (key_m == false)
			key_m = true;
		else
			key_m = false;
		break;
	case 'r':
		a = false, b = false, c = false, d = false, e = false;
		box_count = 0;
		break;
	case 'q':
		exit(0);
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

	if (key_a == true) {			//(-,-)왼쪽 아래 방향		//(+,+)오른쪽 위 방향   //(-,+) 왼쪽 위 방향  //(+,-) 오른쪽 아래 방향
		if (a == true) {
			if (wall_top1 == false && wall_right1 == false && wall_bottom1 == false && wall_left1 == false) {
				x_1 -= 0.01f;
				y_1 -= 0.01f;
			}
			collision_wall_1(x_1, y_1);
			if (wall_left1 == true) {
				x_1 += 0.01f;
				y_1 -= 0.01f;
			}
			if (wall_bottom1 == true) {

				x_1 += 0.01f;
				y_1 += 0.01f;
			}
			if (wall_right1 == true) {
				x_1 -= 0.01f;
				y_1 += 0.01f;
			}
			if (wall_top1 == true) {
				x_1 -= 0.01f;
				y_1 -= 0.01f;
			}
		}
		if (b == true) {
			if (wall_top2 == false && wall_right2 == false && wall_bottom2 == false && wall_left2 == false) {
				x_2 += 0.01f;
				y_2 += 0.01f;
			}
			collision_wall_2(x_2, y_2);
			if (wall_left2 == true) {
				x_2 += 0.01f;
				y_2 -= 0.01f;
			}
			if (wall_bottom2 == true) {

				x_2 += 0.01f;
				y_2 += 0.01f;
			}
			if (wall_right2 == true) {
				x_2 -= 0.01f;
				y_2 += 0.01f;
			}
			if (wall_top2 == true) {
				x_2 -= 0.01f;
				y_2 -= 0.01f;
			}


		}
		if (c == true) {
			if (wall_top3 == false && wall_right3 == false && wall_bottom3 == false && wall_left3 == false) {
				x_3 -= 0.01f;
				y_3 += 0.01f;
			}
			collision_wall_3(x_3, y_3);
			if (wall_left3 == true) {
				x_3 += 0.01f;
				y_3 += 0.01f;
			}
			if (wall_bottom3 == true) {

				x_3 -= 0.01f;
				y_3 += 0.01f;
			}
			if (wall_right3 == true) {
				x_3 -= 0.01f;
				y_3 -= 0.01f;
			}
			if (wall_top3 == true) {
				x_3 += 0.01f;
				y_3 -= 0.01f;
			}


		}
		if (d == true) {
			if (wall_top4 == false && wall_right4 == false && wall_bottom4 == false && wall_left4 == false) {
				x_4 += 0.01f;
				y_4 -= 0.01f;
			}
			collision_wall_4(x_4, y_4);
			if (wall_left4 == true) {
				x_4 += 0.01f;
				y_4 -= 0.01f;
			}
			if (wall_bottom4 == true) {

				x_4 += 0.01f;
				y_4 += 0.01f;
			}
			if (wall_right4 == true) {
				x_4 -= 0.01f;
				y_4 += 0.01f;
			}
			if (wall_top4 == true) {
				x_4 -= 0.01f;
				y_4 -= 0.01f;
			}
		}

	}
	//--------------------------각 개체 대각선 이동

	if (key_i == true) {

		if (a == true) {																			//아래 오른쪽
			if (top_y1 == false && bottom_y1 == false && left_x1 == false && right_x1 == false) {
				y_1 -= 0.01f;
			}

			if (y_1 < -1) {
				bottom_y1 = false, right_x1 = true;
				x_1 += 0.01f;
				count_a++;
				if (count_a == 10) {
					count_a = 0, right_x1 = false, top_y1 = true;
				}
			}
			if (top_y1 == true)
				y_1 += 0.01f;

			if (y_1 + 0.1f > 1) {
				top_y1 = false, right_x1 = true;
				x_1 += 0.01f;
				count_a++;
				if (count_a == 10)
					count_a = 0, right_x1 = false, bottom_y1 = true;
			}

			if (bottom_y1 == true)
				y_1 -= 0.01f;
		}

		if (b == true) {
			if (top_y2 == false && bottom_y2 == false && left_x2 == false && right_x2 == false) {
				y_2 += 0.01f;
			}

			if (y_2 + 0.1f > 1) {
				top_y2 = false, left_x2 = true;
				x_2 -= 0.01f;
				count_b++;
				if (count_b == 10) {
					count_b = 0, left_x2 = false, bottom_y2 = true;
				}
			}

			if (bottom_y2 == true)
				y_2 -= 0.01f;

			if (y_2 < -1) {
				bottom_y2 = false, left_x2 = true;
				x_2 -= 0.01f;
				count_b++;
				if (count_b == 10)
					count_b = 0, left_x2 = false, top_y2 = true;
			}

			if (top_y2 == true)
				y_2 += 0.01f;
		}

		if (c == true) {
			if (top_y3 == false && bottom_y3 == false && left_x3 == false && right_x3 == false) {
				x_3 += 0.01f;
			}
			if (x_3 + 0.1f > 1) {
				right_x3 = false, bottom_y3 = true;
				y_3 -= 0.01f;
				count_c++;
				if (count_c == 10)
					count_c = 0, bottom_y3 = false, left_x3 = true;
			}
			if (left_x3 == true)
				x_3 -= 0.01f;

			if (x_3 < -1) {
				left_x3 = false, bottom_y3 = true;
				y_3 -= 0.01f;
				count_c++;
				if (count_c == 10)
					count_c = 0, bottom_y3 = false, right_x3 = true;
			}
			if (right_x3 == true)
				x_3 += 0.01f;
		}

		if (d == true) {
			if (top_y4 == false && bottom_y4 == false && left_x4 == false && right_x4 == false)
				x_4 -= 0.01f;
			if (x_4 < -1) {
				left_x4 = false, top_y4 = true;
				y_4 += 0.01f;
				count_d++;
				if (count_d == 10)
					count_d = 0, top_y4 = false, right_x4 = true;
			}
			if (right_x4 == true)
				x_4 += 0.01f;

			if (x_4 + 0.1f > 1) {
				right_x4 = false, top_y4 = true;
				y_4 += 0.01f;
				count_d++;
				if (count_d == 10)
					count_d = 0, top_y4 = false, left_x4 = true;
			}
			if (left_x4 == true)
				x_4 -= 0.01f;


		}

	}
	//--------------------------각 개체 지그재그 이동

	if (key_c == true) {
		
		if (a == true) {
			size_x1 += 0.01;
		}

		if (b == true) {
			size_x2 += 0.01;
			size_y2 += 0.01;
		}

		if (c == true) {
			size_y3 += 0.01;
		}

		if (d == true) {
			size_x4 += 0.01;
			size_y4 += 0.01;
		}

	}
	//--------------------------각 개체 크기 변환

	if (key_m == true) {

		if (a == true) {
			if (temp_x1 < x_1)
				x_1 -= 0.01;

			if (temp_y1 < y_1)
				y_1 -= 0.01;

			if (temp_x1 > x_1)
				x_1 += 0.01;

			if (temp_y1 > y_1)
				y_1 += 0.01;
		}

		if (b == true) {
			if (temp_x2 < x_2)
				x_2 -= 0.01;

			if (temp_y2 < y_2)
				y_2 -= 0.01;

			if (temp_x2 > x_2)
				x_2 += 0.01;

			if (temp_y2 > y_2)
				y_2 += 0.01;
		}

		if (c == true) {
			if (temp_x3 < x_3)
				x_3 -= 0.01;

			if (temp_y3 < y_3)
				y_3 -= 0.01;

			if (temp_x3 > x_3)
				x_3 += 0.01;

			if (temp_y3 > y_3)
				y_3 += 0.01;
		}

		if (d == true) {
			if (temp_x4 < x_4)
				x_4 -= 0.01;

			if (temp_y4 < y_4)
				y_4 -= 0.01;

			if (temp_x4 > x_4)
				x_4 += 0.01;

			if (temp_y4 > y_4)
				y_4 += 0.01;
		}

		if (e == true) {
			if (temp_x5 < x_5)
				x_5 -= 0.01;

			if (temp_y5 < y_5)
				y_5 -= 0.01;

			if (temp_x5 > x_5)
				x_5 += 0.01;

			if (temp_y5 > y_5)
				y_5 += 0.01;
		}

	}
	//--------------------------각 개체 원 위치 이동

		glutPostRedisplay();
		glutTimerFunc(100, TimerFunction, 1);

}


void collision_wall_1(GLfloat x, GLfloat y) {

	if (x < -1) {
		wall_top1= false ,wall_right1 = false, wall_bottom1 = false ,wall_left1 = true;
	}
	if (y < -1) {
		wall_top1 = false, wall_right1 = false, wall_bottom1 = true, wall_left1 = false;
	}
	if (x + 0.1f > 1) {
		wall_top1 = false, wall_right1 = true, wall_bottom1 = false, wall_left1 = false;
	}
	if (y + 0.1f > 1) {
		wall_top1 = true, wall_right1 = false, wall_bottom1 = false, wall_left1 = false;
	}

}
void collision_wall_2(GLfloat x, GLfloat y) {

	if (x < -1) {
		wall_top2 = false, wall_right2 = false, wall_bottom2 = false, wall_left2 = true;
	}
	if (y < -1) {
		wall_top2 = false, wall_right2 = false, wall_bottom2 = true, wall_left2 = false;
	}
	if (x + 0.1f > 1) {
		wall_top2 = false, wall_right2 = true, wall_bottom2 = false, wall_left2 = false;
	}
	if (y + 0.1f > 1) {
		wall_top2 = true, wall_right2 = false, wall_bottom2 = false, wall_left2 = false;
	}

}
void collision_wall_3(GLfloat x, GLfloat y) {

	if (x < -1) {
		wall_top3 = false, wall_right3 = false, wall_bottom3 = false, wall_left3 = true;
	}
	if (y < -1) {
		wall_top3 = false, wall_right3 = false, wall_bottom3 = true, wall_left3 = false;
	}
	if (x + 0.1f > 1) {
		wall_top3 = false, wall_right3 = true, wall_bottom3 = false, wall_left3 = false;
	}
	if (y + 0.1f > 1) {
		wall_top3 = true, wall_right3 = false, wall_bottom3 = false, wall_left3 = false;
	}

}
void collision_wall_4(GLfloat x, GLfloat y) {

	if (x < -1) {
		wall_top4 = false, wall_right4 = false, wall_bottom4 = false, wall_left4 = true;
	}
	if (y < -1) {
		wall_top4 = false, wall_right4 = false, wall_bottom4 = true, wall_left4 = false;
	}
	if (x + 0.1f > 1) {
		wall_top4 = false, wall_right4 = true, wall_bottom4 = false, wall_left4 = false;
	}
	if (y + 0.1f > 1) {
		wall_top4 = true, wall_right4 = false, wall_bottom4 = false, wall_left4 = false;
	}

}


