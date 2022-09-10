#include <iostream>

using namespace std;

class data {
public:

	int x;
	int y;
	int z;
};


int main() {


	cout << " + : 리스트의 맨 위에 입력" << endl;
	cout << " - : 리스트의 맨 위에서 삭제" << endl;
	cout << " e : 리스트의 맨 아레에 입력" << endl;
	cout << " d : 리스트의 맨 아레에서 삭제" << endl;
	cout << " i : 리스트의 저장된 점의 개수를 출력하라" << endl;
	cout << " c : 리스트를 비운다. 리스트를 비운 후 다시 입력하면 0번 부터 저장된다." << endl;
	cout << " m : 원점에서 가장 먼거리에 있는 점의 좌표값을 출력하라." << endl;
	cout << " n : 원점에서 가장 가까운 거리에 있는 점의 좌표값을 출력한다." << endl;
	cout << " s : 원점과의 거리를 정렬하여 오름차순으로 정렬하여 출력한다.\n (인덱스 0번부터 빈 칸없이 저장하여 출력한다. 다시 s를 누르면 원래의 인덱스 위치에서 출력한다.)" << endl;
	cout << " q : 프로그램을 종료한다." << endl << endl << endl;


	char keyword;

	while (true) {
		cout << "명령어 입력:";
		cin >> keyword;

		switch (keyword) {

		case '+': case'=':

			break;
		case '-': case '_':

			break;
		case 'e': case 'E':

			break;
		case 'd': case 'D':

			break;
		case 'i': case 'I':

			break;
		case 'c': case'C':
			
			break;
		case 'm': case'M':

			break;
		case 'n': case'N':

			break;
		case 's': case'S':

			break;
		case 'q': case'Q':

			break;
		}

	}


}