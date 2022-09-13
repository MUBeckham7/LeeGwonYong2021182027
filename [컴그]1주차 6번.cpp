#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void course(int board[30][30]);

int main() {
	srand((unsigned int)time(NULL));
	int arrow;
	int n{ 1 };
	int x{}, y{};
	int max_0{}, max_1{}, max_2{}, max_3{};
	char keyword{};

	int board[30][30]{};

	int temp[30]{};
	int tempo[30]{};

	while (true) {
		arrow = rand() % 4;

		if (arrow == 0) {					//상
			max_1 = 0, max_2 = 0, max_3 = 0;
			if (max_0 == 8)
				continue;

			if (x == 0)
				continue;

			board[x--][y] = n++;
			max_0++;
		}
		else if (arrow == 1) {				//하
			max_0 = 0, max_2 = 0, max_3 = 0;
			if (max_1 == 8)
				continue;
			if (x == 29)
				continue;

			board[x++][y] = n++;
			max_1++;
		}
		else if (arrow == 2) {				//좌
			max_0 = 0, max_1 = 0, max_3 = 0;
			if (max_2 == 8)
				continue;
			if (y == 0)
				continue;

			board[x][y--] = n++;
			max_2++;
		}
		else if (arrow == 3) {				//우
			max_0 = 0, max_2 = 0, max_1 = 0;
			if (max_3 == 8)
				continue;
			if (y == 29)
				continue;

			board[x][y++] = n++;
			max_3++;
		}

		if (board[29][29] != 0)
			break;
	}

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}


		cout << endl;
		cout << "명령어 입력:";
		cin >> keyword;

		if (keyword == 'r') {
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 30; j++) {
					if (j == 0)
						cout << board[i][29] << " ";
					else
						cout << board[i][j - 1] << " ";
				}
				cout << endl;
			}
		}
}



void course(int board[30][30]) {

}