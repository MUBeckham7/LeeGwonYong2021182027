#include <iostream>

using namespace std;

class data {
public:

	int x;
	int y;
	int z;
};


int main() {


	cout << " + : ����Ʈ�� �� ���� �Է�" << endl;
	cout << " - : ����Ʈ�� �� ������ ����" << endl;
	cout << " e : ����Ʈ�� �� �Ʒ��� �Է�" << endl;
	cout << " d : ����Ʈ�� �� �Ʒ����� ����" << endl;
	cout << " i : ����Ʈ�� ����� ���� ������ ����϶�" << endl;
	cout << " c : ����Ʈ�� ����. ����Ʈ�� ��� �� �ٽ� �Է��ϸ� 0�� ���� ����ȴ�." << endl;
	cout << " m : �������� ���� �հŸ��� �ִ� ���� ��ǥ���� ����϶�." << endl;
	cout << " n : �������� ���� ����� �Ÿ��� �ִ� ���� ��ǥ���� ����Ѵ�." << endl;
	cout << " s : �������� �Ÿ��� �����Ͽ� ������������ �����Ͽ� ����Ѵ�.\n (�ε��� 0������ �� ĭ���� �����Ͽ� ����Ѵ�. �ٽ� s�� ������ ������ �ε��� ��ġ���� ����Ѵ�.)" << endl;
	cout << " q : ���α׷��� �����Ѵ�." << endl << endl << endl;


	char keyword;

	while (true) {
		cout << "��ɾ� �Է�:";
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