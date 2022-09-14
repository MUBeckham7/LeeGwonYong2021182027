#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	char filename[10];
	char word;
	int word_count{};
	int number_count{};
	int capital_count{};
	int space{};

	cout << "input data file name:";
	cin >> filename;
	cout << endl;
	ifstream file(filename);


	while (true) {
		file.get(word);
		if (file.fail())
			break;

		cout << word;

		if (word == ' ' || word == '\n') {
			word_count++;
			space = 0;
		}
		else if (space == 0 && word >= 0x30 && word <= 0x39) {
			number_count++;
			space = 1;

			
		}
		else if (space == 1 && ((word >= 0x61 && word <= 0x7A) || (word >= 0x41 && word <= 0x5A))) {
				number_count--;
			}
		else if (space == 0 && word >= 0x41 && word <= 0x5A) {
			capital_count++;
			space = 2;
		}

	}



	file.close();
	cout << endl << endl << endl;
	cout << "word count:" << word_count - number_count <<endl;
	cout << "number count:" << number_count << endl;
	cout << "Capital word:" <<capital_count<< endl;
}