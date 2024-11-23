#include <iostream>
#include <cstdlib>

using namespace std;

int a1{}, b1{}, c1{}, d1{}, e1{}, f1{}, g1{}, h1{}, i1{};
int a2{}, b2{}, c2{}, d2{}, e2{}, f2{}, g2{}, h2{}, i2{};

void esc();
void ProcMulti();
void ProcPlus();
void ProcMinus();
void ProcDeter();
void ProcTrans();
void ProcConversion();

int main() {

	srand((unsigned int)time(NULL));


	char keyword{};

	esc();


	cout << "|" << a1 << " " << b1 << " " << c1 << "|" << "  ";
	cout << "|" << a2 << " " << b2 << " " << c2 << "|" << endl;
	cout << "|" << d1 << " " << e1 << " " << f1 << "|" << "  ";
	cout << "|" << d2 << " " << e2 << " " << f2 << "|" << endl;
	cout << "|" << g1 << " " << h1 << " " << i1 << "|" << "  ";
	cout << "|" << g2 << " " << h2 << " " << i2 << "|" << endl;

	cout << endl << endl;

	while (true) {

		cout << "명령어 입력:";
		cin >> keyword;

		if (keyword == 'm') {
			ProcMulti();
		}

		else if (keyword == 'a') {
			ProcPlus();
		}

		else if (keyword == 'd') {
			ProcMinus();
		}

		else if (keyword == 'r') {
			ProcDeter();
		}

		else if (keyword == 't') {
			ProcTrans();
		}
		else if (keyword == 'h') {
			ProcConversion();
		}
		else if (keyword == 's') {
			esc();

			cout << "|" << a1 << " " << b1 << " " << c1 << "|" << "  ";
			cout << "|" << a2 << " " << b2 << " " << c2 << "|" << endl;
			cout << "|" << d1 << " " << e1 << " " << f1 << "|" << "  ";
			cout << "|" << d2 << " " << e2 << " " << f2 << "|" << endl;
			cout << "|" << g1 << " " << h1 << " " << i1 << "|" << "  ";
			cout << "|" << g2 << " " << h2 << " " << i2 << "|" << endl;

			cout << endl << endl;

		}
		else if (keyword == 'q') {
			return 0;
		}

	}
}

void esc() {

	a1 = rand() % 3;
	b1 = rand() % 3;
	c1 = rand() % 3;
	d1 = rand() % 3;
	e1 = rand() % 3;
	f1 = rand() % 3;
	g1 = rand() % 3;
	h1 = rand() % 3;
	i1 = rand() % 3;

	a2 = rand() % 3;
	b2 = rand() % 3;
	c2 = rand() % 3;
	d2 = rand() % 3;
	e2 = rand() % 3;
	f2 = rand() % 3;
	g2 = rand() % 3;
	h2 = rand() % 3;
	i2 = rand() % 3;
}

void ProcMulti() {
	cout << "| " << a1 * a2 + b1 * d2 + c1 * g2 << " " << a1 * b2 + b1 * e2 + c1 * h2 << " " << a1 * c2 + b1 * f2 + c1 * i2 << " |" << endl;
	cout << "| " << d1 * a2 + e1 * d2 + f1 * g2 << " " << d1 * b2 + e1 * e2 + f1 * h2 << " " << d1 * c2 + e1 * f2 + f1 * i2 << " |" << endl;
	cout << "| " << g1 * a2 + h1 * d2 + i1 * g2 << " " << g1 * b2 + h1 * e2 + i1 * h2 << " " << g1 * c2 + h1 * f2 + i1 * i2 << " |" << endl;
}

void ProcPlus() {
	cout << "| " << a1 + a2 << " " << b1 + b2 << " " << c1 + c2 << " |" << endl;
	cout << "| " << d1 + d2 << " " << e1 + e2 << " " << f1 + f2 << " |" << endl;
	cout << "| " << g1 + g2 << " " << h1 + h2 << " " << i1 + i2 << " |" << endl;
}

void ProcMinus() {
	cout << "| " << a1 - a2 << " " << b1 - b2 << " " << c1 - c2 << " |" << endl;
	cout << "| " << d1 - d2 << " " << e1 - e2 << " " << f1 - f2 << " |" << endl;
	cout << "| " << g1 - g2 << " " << h1 - h2 << " " << i1 - i2 << " |" << endl;
}

void ProcDeter() {
	cout << "|" << a1 << " " << b1 << " " << c1 << "|" << "\t\t" << "|" << a2 << " " << b2 << " " << c2 << "|" << endl;;
	cout << "|" << d1 << " " << e1 << " " << f1 << "|" << " = " << a1 * e1 * i1 + b1 * f1 * g1 + c1 * d1 * h1 - (a1 * f1 * h1 + b1 * d1 * i1 + c1 * e1 * g1) << "\t" << "|" << d2 << " " << e2 << " " << f2 << "|" << " = " << a2 * e2 * i2 + b2 * f2 * g2 + c2 * d2 * h2 - (a2 * f2 * h2 + b2 * d2 * i2 + c2 * e2 * g2) << endl;
	cout << "|" << g1 << " " << h1 << " " << i1 << "|" << "\t\t" << "|" << g2 << " " << h2 << " " << i2 << "|" << endl;
}

void ProcTrans() {
	cout << "|" << a1 << " " << b1 << " " << c1 << "|" << "\t\t" << "|" << a1 << " " << d1 << " " << g1 << "|" << endl;;
	cout << "|" << d1 << " " << e1 << " " << f1 << "|" << " -> " << "\t" << "|" << b1 << " " << e1 << " " << h1 << "|" << " = " << a1 * e1 * i1 + d1 * h1 * c1 + g1 * b1 * f1 - (a1 * h1 * f1 + d1 * b1 * i1 + g1 * e1 * c1) << endl;
	cout << "|" << g1 << " " << h1 << " " << i1 << "|" << "\t\t" << "|" << c1 << " " << f1 << " " << i1 << "|" << endl;
	cout << endl << endl;

	cout << "|" << a2 << " " << b2 << " " << c2 << "|" << "\t\t" << "|" << a2 << " " << d2 << " " << g2 << "|" << endl;
	cout << "|" << d2 << " " << e2 << " " << f2 << "|" << " -> \t" << "|" << b2 << " " << e2 << " " << h2 << "|" << " = " << a2 * e2 * i2 + b2 * f2 * g2 + c2 * d2 * h2 - (a2 * f2 * h2 + b2 * d2 * i2 + c2 * e2 * g2) << endl;
	cout << "|" << g2 << " " << h2 << " " << i2 << "|" << "\t\t" << "|" << c2 << " " << f2 << " " << i2 << "|" << endl;
}

void ProcConversion() {

	int x1 = 0;
	int x2 = 1;
			
	cout << "|" << a1 << " " << b1 << " " << c1 << "|" <<"\t\t" << "|" << a1 << " " << b1 << " " << c1 <<" " << x1 << "|" << endl;
	cout << "|" << d1 << " " << e1 << " " << f1 << "|" << " -> "<<"\t" << "|" << d1 << " " << e1 << " " << f1 <<" " << x1 << "|" << " = " << a1 * ((e1*i1*x2) - (h1*f1*x2)) -b1*((d1*i1*x2)-(f1*g1*x2))+c1*((d1*h1*x2)-(e1*g1*x2))  << endl;
	cout << "|" << g1 << " " << h1 << " " << i1 << "|" << "\t\t" << "|" << g1 << " " << h1 << " " << i1 <<" " << x1 << "|" << endl;
	cout << "\t\t" << "|" << x1 << " "<< x1 << " " << x1 << " "<< x2 << "|" << endl;

	cout << endl;

	cout << "|" << a2 << " " << b2 << " " << c2 << "|" << "\t\t" << "|" << a2 << " " << b2 << " " << c2 << " " << x1 << "|" << endl;
	cout << "|" << d2 << " " << e2 << " " << f2 << "|" << " -> " << "\t" << "|" << d2 << " " << e2 << " " << f2 << " " << x1 << "|" << " = " << a2 * ((e2 * i2 * x2) - (h2 * f2 * x2)) - b2 * ((d2 * i2 * x2) - (f2 * g2 * x2)) + c2 * ((d2 * h2 * x2) - (e2 * g2 * x2)) << endl;
	cout << "|" << g2 << " " << h2 << " " << i2 << "|" << "\t\t" << "|" << g2 << " " << h2 << " " << i2 << " " << x1 << "|" << endl;
	cout << "\t\t" << "|" << x1 << " " << x1 << " " << x1 << " " << x2 << "|" << endl;

}
