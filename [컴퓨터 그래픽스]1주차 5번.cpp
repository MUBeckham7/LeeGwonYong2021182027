#include <iostream>

using namespace std;

class Data {
public:

	int x;
	int y;
	int z;
	int cnt;
};

void manual();
void Print_list(int cnt,int i,int x,int y,int z);

bool desc(int a, int b) {
	return a > b;
}

int main() {

	manual();

	char keyword;
	Data data[10]{};
	int n{};
	int far[10];
	int close[10];
	int temp{};
	int k{};
	int s_count{};


	while (true) {
		cout << "명령어 입력:";
		cin >> keyword;

		switch (keyword) {

		case '+': case'=':
			cout << "데이터 입력:";
			
			for (int i = 0; i < 10; ++i) {
				if (data[i].cnt == 0) {
					cin >> data[i].x;
					cin >> data[i].y;
					cin >> data[i].z;
					data[i].cnt = 1;
					break;
				}
					

			}

			for (int i = 0; i < 10; ++i) {
				Print_list(data[i].cnt,i,data[i].x, data[i].y, data[i].z);
			}
			break;
		case '-': case '_':
			for (int i = 0; i < 10; ++i) {
				if (data[i].cnt == 0) {

					if (i == 0) {
						data[i].cnt = 0;
						break;
					}
						

					data[i - 1].cnt = 0;
					break;
				}
			}
			for (int i = 0; i < 10; ++i) {
				Print_list(data[i].cnt,i, data[i].x, data[i].y, data[i].z);
			}

			break;
		case 'e': case 'E':
			cout << "데이터 입력:";
			for (int i = 9; i >= 0; --i) {
				if (data[i].cnt == 1) {
					if (i == 9)
						break;
					data[i + 1].cnt = data[i].cnt;
					data[i].cnt = 0;
					data[i + 1].x = data[i].x;
					data[i + 1].y = data[i].y;
					data[i + 1].z = data[i].z;
				}
				
			}
			for (int i = 0; i < 10; ++i) {
				if (data[i].cnt == 0) {
					cin >> data[i].x;
					cin >> data[i].y;
					cin >> data[i].z;
					data[i].cnt = 1;
					break;
				}
			}


			for (int i = 0; i < 10; ++i) {
				Print_list(data[i].cnt,i, data[i].x, data[i].y, data[i].z);
			}
			break;
		case 'd': case 'D':
			for (int i = 0; i < 10; ++i) {
				if (data[i].cnt == 1) {
					data[i].cnt = 0;
					break;
				}
			}
			for (int i = 0; i < 10; ++i) {
				Print_list(data[i].cnt,i, data[i].x, data[i].y, data[i].z);
			}
			break;
		case 'i': case 'I':
			for (int i = 0; i < 10; ++i) {
				if (data[i].cnt == 1)
					n++;
			}
				cout << "리스트 길이: " << n<<endl;

			break;
		case 'c': case'C':
			for (int i = 0; i < 10; ++i) {
				data[i].cnt = 0;
			}
			break;
		case 'm': case'M':

			for (int i = 0; i < 10; ++i) {
				far[i] = (data[i].x * data[i].x + data[i].y * data[i].y + data[i].z * data[i].z);
			}

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 9 - i; j++) {
					if (far[j] < far[j + 1]) {
						temp = far[j];
						far[j] = far[j + 1];
						far[j + 1] = temp;

					}
				}
			}


			for (int i = 0; i < 10; ++i) {
				if (far[0] == (data[i].x * data[i].x + data[i].y * data[i].y + data[i].z * data[i].z)) {
					cout <<"(" << data[i].x<<"," << data[i].y<<"," << data[i].z<<")" << endl;
				}
			}
			break;
		case 'n': case'N':
			for (int i = 0; i < 10; ++i) {
				close[i] = (data[i].x * data[i].x + data[i].y * data[i].y + data[i].z * data[i].z);

				if (data[i].cnt == 1)
					k++;
			}

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 9 - i; j++) {
						if (close[j] < close[j + 1]) {
							temp = close[j];
							close[j] = close[j + 1];
							close[j + 1] = temp;
						}
				}
			}

			for (int i = 0; i < 10; ++i) {

				if(close[k-1]== (data[i].x * data[i].x + data[i].y * data[i].y + data[i].z * data[i].z))
					cout << "(" << data[i].x << "," << data[i].y << "," << data[i].z << ")" << endl;

				
			}
			break;
		case 's': case'S':


			if (s_count == 0) {
				for (int i = 0; i < 10; ++i) {
					far[i] = (data[i].x * data[i].x + data[i].y * data[i].y + data[i].z * data[i].z);

					if (data[i].cnt == 1)
						k++;
				}

				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 9 - i; j++) {
						if (far[j] < far[j + 1]) {
							temp = far[j];
							far[j] = far[j + 1];
							far[j + 1] = temp;
						}
					}
				}
				for (int k = 0; k < 10; k++) {
					for (int i = 0; i < 10; ++i) {
						if (data[i].cnt == 1 && far[k] == (data[i].x * data[i].x + data[i].y * data[i].y + data[i].z * data[i].z)) {
							cout << k << ":" << "(" << data[i].x << "," << data[i].y << "," << data[i].z << ")" << endl;
						}
					}
				}

				for (k; k < 10; k++) {
					cout << k << ":" << endl;
				}

				s_count = 1;
				break;
			}
			else if(s_count == 1){
				for (int i = 0; i < 10; ++i) {
					Print_list(data[i].cnt, i, data[i].x, data[i].y, data[i].z);
				}
				
				s_count = 0;
				break;
			}
			break;
		case 'q': case'Q':

			break;
		}


		k = 0;
	}
}

void manual() {
	cout << " + : 리스트의 맨 위에 입력" << endl;
	cout << " - : 리스트의 맨 위에서 삭제" << endl;
	cout << " e : 리스트의 맨 아레에 입력" << endl;
	cout << " d : 리스트의 맨 아레에서 삭제" << endl;
	cout << " i : 리스트의 저장된 점의 개수를 출력하라" << endl;
	cout << " c : 리스트를 비운다. 리스트를 비운 후 다시 입력하면 0번 부터 저장된다." << endl;
	cout << " m : 원점에서 가장 먼거리에 있는 점의 좌표값을 출력하라." << endl;
	cout << " n : 원점에서 가장 가까운 거리에 있는 점의 좌표값을 출력한다." << endl;
	cout << " s : 원점과의 거리를 정렬하여 오름차순(내림차순)으로 정렬하여 출력한다.\n (인덱스 0번부터 빈 칸없이 저장하여 출력한다. 다시 s를 누르면 원래의 인덱스 위치에서 출력한다.)" << endl;
	cout << " q : 프로그램을 종료한다." << endl << endl << endl;
}

void Print_list(int cnt,int i,int x,int y,int z) {
	if (cnt == 0) {
		cout<<i<<":" << endl;
	}
	else if(cnt == 1)
	cout << i << ":" << "(" << x << "," << y << "," << z << ")" << endl;

}
