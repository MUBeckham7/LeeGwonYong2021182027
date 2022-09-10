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
		cout << "��ɾ� �Է�:";
		cin >> keyword;

		switch (keyword) {

		case '+': case'=':
			cout << "������ �Է�:";
			
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
			cout << "������ �Է�:";
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
				cout << "����Ʈ ����: " << n<<endl;

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
	cout << " + : ����Ʈ�� �� ���� �Է�" << endl;
	cout << " - : ����Ʈ�� �� ������ ����" << endl;
	cout << " e : ����Ʈ�� �� �Ʒ��� �Է�" << endl;
	cout << " d : ����Ʈ�� �� �Ʒ����� ����" << endl;
	cout << " i : ����Ʈ�� ����� ���� ������ ����϶�" << endl;
	cout << " c : ����Ʈ�� ����. ����Ʈ�� ��� �� �ٽ� �Է��ϸ� 0�� ���� ����ȴ�." << endl;
	cout << " m : �������� ���� �հŸ��� �ִ� ���� ��ǥ���� ����϶�." << endl;
	cout << " n : �������� ���� ����� �Ÿ��� �ִ� ���� ��ǥ���� ����Ѵ�." << endl;
	cout << " s : �������� �Ÿ��� �����Ͽ� ��������(��������)���� �����Ͽ� ����Ѵ�.\n (�ε��� 0������ �� ĭ���� �����Ͽ� ����Ѵ�. �ٽ� s�� ������ ������ �ε��� ��ġ���� ����Ѵ�.)" << endl;
	cout << " q : ���α׷��� �����Ѵ�." << endl << endl << endl;
}

void Print_list(int cnt,int i,int x,int y,int z) {
	if (cnt == 0) {
		cout<<i<<":" << endl;
	}
	else if(cnt == 1)
	cout << i << ":" << "(" << x << "," << y << "," << z << ")" << endl;

}
