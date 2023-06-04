#include <iostream>
#include <windows.h>

using namespace std;

/* 4번
void printAstar(int a) {
	
	
			cout << "*";
			Sleep(1000);
		

}*/

void PrintStars(int a) {
	
	for (int i = 0; i < a; i++) {
		for (int j = 0; j <= i; j++) {
			cout << "*";
		}
		cout << "\n";
	}
}

int main() {
	/* 1번
	int i = 0;

	while (true) {
		for (i = 0; i < 4; i++) {
			for (int j = 0; j<=i; j++) {
				cout << "*";
				Sleep(1000);
			}
			cout << "\n";
		}

		if (i == 4)
			break;
	}
	*/

	/* 2번
	int i{};
	int a{};
	cout << "출력할 줄 수를 입력하세요:";
	cin >> a;

	while (true) {
		for (i = 0; i < a; i++) {
			for (int j = 0; j <=i; j++) {
				cout << "*";
				Sleep(1000);
			}
			cout << "\n";
		}

		if (i == a)
			break;
	}*/

	/* 3번
	int i{};
	int a{};
	cout << "출력할 줄 수를 입력하세요:";
	cin >> a;

	while (true) {
		for (i = 1; i < a+1; i++) {
			for (int j = 1; j <= i; j++) {
				cout << j;
				Sleep(1000);
			}
			cout << "\n";
		}

		if (i == a+1)
			break;
	}
	*/
	
	/* 4번
	int i{};
	int a{};
	cout << "출력할 줄 수를 입력하세요:";
	cin >> a;

	
	for (i = 0; i < a; i++) {
		for (int j = 0; j <= i; j++) {
			printAstar(a);
		}
		cout << "\n";
	}
	*/

	int a{};
	cout << "출력할 줄 수를 입력하세요:";
	cin >> a;

	PrintStars(a);
	

}