#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void reverse_sentence(int end);

	char example[300]{};
	int i{};


int main() {
	char filename[10];
	char word;
	int end{};


	char keyword;
	cout << "input data file name:";
	cin >> filename;
	cout << endl;
	ifstream file(filename);


	while (true) {
		file.get(word);
		if (file.fail()) {
			end = i;
			break;
		}
		example[i++] = word;
	}

	for (i = 0; i < end; i++) {
		cout << example[i];
	}
	cout << endl << endl << endl;
	cout << "command: d:���� ��ü�� ������" << endl;
	cout << "\t" << " e:������ �������� ���⸦ ���� ���� �����ϱ�" << endl;
	cout << "\t f:���⸦ �������� ���� ������" << endl;
	cout << "\t g:���� ������ Ư�� ���ڿ��� �ٸ� ���ڿ��� �ٲٱ�" << endl;
	cout << "\t h: �յڿ��� �о��� �� ������ ���� �������� ����ϱ�" << endl;

	cout << endl;

	while (true) {
		cout << "Input:";
		cin >> keyword;

		if (keyword == 'd')
			reverse_sentence(end);

	}


	file.close();
}

void reverse_sentence(int end) {
	int nextline{};
	int store{};

	for (int i = 0; i < end; ++i) {

		if (example[i] == '\n') {
			store = i;
			for (i; i >= nextline; --i) {
				cout << example[i];
			}
			i = store;
		}
	}

}