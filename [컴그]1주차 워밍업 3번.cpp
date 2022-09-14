#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void reverse_sentence(int end);
void insert_word(int end);
void reverse_word(int end);
void change_word(int end, char w, char c);
void froback_same(int end);

char example[300]{};
int i{};


int main() {
	char filename[10];
	char word;
	int end{};
	int d{}, e{}, f{}, g{};
	char w;
	char c;

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


		if (keyword == 'd') {

			if (d % 2 == 0) {
				reverse_sentence(end);
				d = 1;
				cout << endl;
				continue;
			}
			if (d % 2 == 1) {
				for (i = 0; i < end; i++) {
					cout << example[i];
				}
				d = 0;
				cout << endl;
				continue;
			}
		}

		if (keyword == 'e') {
			if (e % 2 == 0) {
				insert_word(end);
				e = 1;
				cout << endl;
				continue;
			}
			else if (e % 2 == 1) {
				for (i = 0; i < end; i++) {
					cout << example[i];
				}
				e = 0;
				cout << endl;
				continue;
			}
		}

		if (keyword == 'f') {
			if (f % 2 == 0) {
				reverse_word(end);
				cout << endl;
				f = 1;
				continue;
			}
			else if (f % 2 == 1) {
				for (i = 0; i < end; i++) {
					cout << example[i];
				}
				f = 0;
				cout << endl;
				continue;
			}
		}

		if (keyword == 'g') {
			if (g % 2 == 0) {
				cout << "특정 문자:";
				cin >> w;
				cout << "바꿀 문자:";
				cin >> c;

				change_word(end, w, c);
				cout << endl;
				g = 1;
				continue;
			}
			else if (g % 2 == 1) {

				change_word(end, c, w);
				cout << endl;
				g = 0;
				continue;
			}
		}
		if (keyword == 'h') {
			froback_same(end);
			cout << endl;
		}
	}
	file.close();
}

void reverse_sentence(int end) {
	int nextline[11]{};
	int store{};
	int k{};

	for (int i = 0; i < end; ++i) {
		if (example[i] == '\n' || i == end - 1)
			nextline[++k] = i;
	}
	k = 0;
	for (int i = 0; i < end; ++i) {
		if (example[i] == '\n' || i == end - 1) {
			store = i;
			for (i; i >= nextline[k]; --i) {
				cout << example[i];
			}
			i = store;
			k++;
		}
	}
}

void insert_word(int end) {
	for (int i = 0; i <= end; ++i) {
		if (i % 5 == 0 || i % 5 == 1 || i % 5 == 2)
			cout << example[i];
		else if (i % 5 == 3)
			cout << "@@" << example[i];
		else if (i % 5 == 4)
			cout << example[i];
	}
	cout << endl;
}

void reverse_word(int end) {
	int space[100]{};
	int store{};
	int k{};

	for (int i = 0; i < end; ++i) {
		if (example[i] == ' ' || example[i] == '\n' || i == end - 1)
			space[++k] = i;
	}
	k = 0;
	for (int i = 0; i < end; ++i) {
		if (example[i] == ' ' || example[i] == '\n' || i == end - 1) {
			store = i;
			for (i; i >= space[k]; --i) {
				cout << example[i];
			}
			i = store;
			k++;
		}
	}

}

void change_word(int end, char w, char c) {

	for (int i = 0; i < end; ++i) {
		if (example[i] == w)
			example[i] = c;

		cout << example[i];
	}
	cout << endl;
}

void froback_same(int end) {
	int nextline[12]{};
	int store{};
	int k{};
	int n{};
	int spe{};
	for (int i = 0; i <= end; ++i) {
		if (example[i] == '\n' || i == end) {
			nextline[++k] = i;
		}
	}
	k = 0;
	for (int i = 0; i <= end; ++i) {
		cout << example[i];

		if (example[i] == '\n' || i == end) {

			cout << " :";
			while (true) {
				if (k == 9)
					spe = 1;
				if (example[nextline[k] + n + spe] == example[nextline[k + 1] - n - spe]) {
					cout << example[nextline[k] + n];
					n++;
				}
				else
					break;
			}
			k++;
			n = 0;
		}
	}

}