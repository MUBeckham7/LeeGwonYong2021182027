#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void restricted_area(int x, int y, int z, int r);

void coordinate(int x1,int y1, int x2, int y2, int x3, int y3, int x4, int y4);

void collision(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

int res{};

int main() {
	srand((unsigned int)time(NULL));

	int x1{}, x2{}, x3{}, x4{};
	int y1{}, y2{}, y3{}, y4{};
	char arrow;
	int cnt = 0;

	x1 = rand() % 150;
	y1 = rand() % 150;
	x2 = rand() % 150 + 200;
	y2 = rand() % 150 + 100;
	x3 = rand() % 150 + 450;
	y3 = rand() % 150 + 350;
	x4 = rand() % 150 + 650;
	y4 = rand() % 150 + 450;

	cout << "ÀÌµ¿ Ä¿¸Çµå: w,a,s,d" << endl << endl;
	cout << "Input Shape Coordinates value:" << endl;
	cout << "\t" << "Rect 1: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")" << endl;
	cout << "\t" << "Rect 2: (" << x3 << "," << y3 << ") (" << x4 << "," << y4 << ")" << endl<<endl<<endl;

	while (true) {



		if (cnt % 2 == 0) {
		cout << "1¹ø »ç°¢Çü--";
		cout << "Command:";
		cin >> arrow;

			if (arrow == 'w') {
				y1 -= 50;
				y2 -= 50;
				restricted_area(x1,y1,x2,y2);

				collision(x1, y1, x2, y2, x3, y3, x4, y4);
				
				if (res == 0) 
					coordinate(x1,y1,x2,y2,x3,y3,x4,y4);
				else if(res == 1)
					y1 += 50,y2 += 50;
				
			}
			else if (arrow == 'a') {
				x1 -= 50;
				x2 -= 50;
				restricted_area(x1, y1, x2, y2);
				collision(x1, y1, x2, y2, x3, y3, x4, y4);
				if (res == 0)
					coordinate(x1, y1, x2, y2, x3, y3, x4, y4);
				else if (res == 1)
					x1 += 50, x2 += 50;
			}
			else if (arrow == 's') {
				y1 += 50;
				y2 += 50;
				restricted_area(x1, y1, x2, y2);
				collision(x1, y1, x2, y2, x3, y3, x4, y4);
				if (res == 0)
					coordinate(x1, y1, x2, y2, x3, y3, x4, y4);
				else if (res == 1)
					y1 -= 50, y2 -= 50;
			}
			else if (arrow == 'd') {
				x1 += 50;
				x2 += 50;
				restricted_area(x1, y1, x2, y2);
				collision(x1, y1, x2, y2, x3, y3, x4, y4);
				if (res == 0)
					coordinate(x1, y1, x2, y2, x3, y3, x4, y4);
				else if (res == 1)
					x1 -= 50, x2 -= 50;
			}

			cnt = 1;

			if (res == 1)
				cnt = 0;

			res = 0;
		}


		cout << endl;

		if (cnt % 2 == 1) {
			cout << "2¹ø »ç°¢Çü--";
			cout << "Command:";
			cin >> arrow;

			if (arrow == 'w') {
				y3 -= 50;
				y4 -= 50;
				restricted_area(x3, y3, x4, y4);
				collision(x1, y1, x2, y2, x3, y3, x4, y4);
				if (res == 0)
					coordinate(x1, y1, x2, y2, x3, y3, x4, y4);
				else if (res == 1)
					y3 += 50, y4 += 50;
			}
			else if (arrow == 'a') {
				x3 -= 50;
				x4 -= 50;
				restricted_area(x3, y3, x4, y4);
				collision(x1, y1, x2, y2, x3, y3, x4, y4);
				if (res == 0)
					coordinate(x1, y1, x2, y2, x3, y3, x4, y4);
				else if (res == 1)
					x3 += 50, x4 += 50;
			}
			else if (arrow == 's') {
				y3 += 50;
				y4 += 50;
				restricted_area(x3, y3, x4, y4);
				collision(x1, y1, x2, y2, x3, y3, x4, y4);
				if (res == 0)
					coordinate(x1, y1, x2, y2, x3, y3, x4, y4);
				else if (res == 1)
					y3 -= 50, y4 -= 50;
			}
			else if (arrow == 'd') {
				x3 += 50;
				x4 += 50;
				restricted_area(x3, y3, x4, y4);
				collision(x1, y1, x2, y2, x3, y3, x4, y4);
				if (res == 0)
					coordinate(x1, y1, x2, y2, x3, y3, x4, y4);
				else if (res == 1)
					x3 -= 50, x4 -= 50;
			}

			cnt = 0;
			if (res == 1)
				cnt = 1;

			res = 0;
		}

	}
}

void restricted_area(int x, int y,int z,int r) {

	if (y < 0) {
		cout << "ÁÂÇ¥¸¦ ¹ş¾î³µ½À´Ï´Ù."<<endl;
		res = 1;
	}
	
	if (x < 0) {
		cout << "ÁÂÇ¥¸¦ ¹ş¾î³µ½À´Ï´Ù." << endl;
		res = 1;
	}
	
	if (z > 800) {
		cout << "ÁÂÇ¥¸¦ ¹ş¾î³µ½À´Ï´Ù." << endl;
		res = 1;
	}

	if (r > 600) {
		cout << "ÁÂÇ¥¸¦ ¹ş¾î³µ½À´Ï´Ù." << endl;
		res = 1;
	}

}

void coordinate(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	cout << "\t" << "Rect 1: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")" << endl;
	cout << "\t" << "Rect 2: (" << x3 << "," << y3 << ") (" << x4 << "," << y4 << ")" << endl << endl << endl;
}

void collision(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {

	if ((x3 < x2 && x1 < x4) && (y3 < y2 && y1 < y4)) {
		cout << "Ãæµ¹" << endl;
		res = 1;
	}
}