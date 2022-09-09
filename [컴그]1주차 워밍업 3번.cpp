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
	cout << "command: d:문장 전체를 뒤집기" << endl;
	cout << "\t" << " e:동일한 간격으로 띄어쓰기를 일정 개수 삽입하기" << endl;
	cout << "\t f:띄어쓰기를 기준으로 문자 뒤집기" << endl;
	cout << "\t g:문자 내부의 특정 문자열을 다른 문자열로 바꾸기" << endl;
	cout << "\t h: 앞뒤에서 읽었을 때 어디까지 같은 문자인지 출력하기" << endl;

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