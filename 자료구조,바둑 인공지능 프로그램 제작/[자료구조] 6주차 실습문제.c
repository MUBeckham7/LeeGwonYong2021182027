#include <stdio.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS

char pan[19][19];

int i = 0;
int x = 0;
int y = 0;
int Bcount = 0;
int Wcount = 0;
void drawpan();

void SetBlackEgg(int* a, int* b);

void SetWhiteEgg(int* a, int* b);

void widthcount();

void lengthcount();

void Tdiagonalcount();

void Bdiagonalcount();

int main() {



	for (x = 0; x < 19; x++) {
		for (y = 0; y < 19; y++) {
			pan[x][y] = '+';

		}
	}



	for (i = 0; i < 324;) {

		while (i % 2 == 0) {

			
			printf("�浹�� ����:%d\n", Bcount);
			printf("�鵹�� ����:%d\n", Wcount);
			widthcount();
			lengthcount();
			Tdiagonalcount();
			Bdiagonalcount();
			drawpan();
			printf("�浹 �����Դϴ�.\n");
			printf("x��ǥ,y��ǥ:");

			if (scanf("%d %d", &x, &y) == 0) {
				rewind(stdin);
			}

			if ((x < 0 || x >= 19) || (y < 0 || y >= 19)) {
				system("cls");
				break;
			}
			if ((x >= 0 && x <= 18) && (y >= 0 && y <= 18))
				SetBlackEgg(&x, &y);

			Sleep(300);
			system("cls");
			i++;
			Bcount++;
		}

		while (i % 2 == 1) {
			
			printf("�浹�� ����:%d\n", Bcount);
			printf("�鵹�� ����:%d\n", Wcount);
			widthcount();
			lengthcount();
			Tdiagonalcount();
			Bdiagonalcount();
			drawpan();
			printf("�鵹 �����Դϴ�.\n");
			printf("x��ǥ,y��ǥ:");
			if (scanf("%d %d", &x, &y) == 0) {
				rewind(stdin);
			}
			if ((x < 0 || x >= 19) || (y < 0 || y >= 19)) {
				system("cls");
				break;
			}
			if ((x >= 0 && x < 19) && (y >= 0 && y < 19))
				SetWhiteEgg(&x, &y);
			Sleep(300);
			system("cls");
			i++;
			Wcount++;
		}


	}




}


void drawpan() {
	for (x = 0; x < 19; x++) {
		for (y = 0; y < 19; y++) {
			printf("%c ", pan[x][y]);
		}
		printf("\n");
	}
}

void SetBlackEgg(int* a, int* b) {


	if (pan[x][y] != '+') {
		printf("�̹� ���� �����ֽ��ϴ�.\n");
		Bcount--;
		i--;
		return;
	}

	pan[x][y] = '@';

}

void SetWhiteEgg(int* a, int* b) {

	if (pan[x][y] != '+') {
		printf("�̹� ���� �����ֽ��ϴ�.\n");
		i--;
		Wcount--;
		return;
	}

	pan[x][y] = 'O';
}

void widthcount() {
	int widB = 0;
	int widW = 0;
	int Bsuc = 1;
	int Wsuc = 1;

	for (x = 0; x < 19; x++) {
		for (y = 0; y < 19; y++) {
			if (pan[x][y] == '@') {
				widB++;
				for (int z = y + 1; z < 19; z++) {
					if (pan[x][z] == '@') {
						widB++;
						Bsuc++;
					}
					else {
						y = z - 1;
						break;
					}
				}
			}


			else if (pan[x][y] == 'O') {
				widW++;
				for (int z = y + 1; z < 19; z++) {
					if (pan[x][z] == 'O') {
						widW++;
						Wsuc++;
					}
					else {
						y = z - 1;
						break;
					}
				}

			}
		}
		printf("���� %d �浹:%d �鵹:%d", x, widB, widW);

		if (Bsuc > Wsuc)
			printf("�濬��:%d\n", Bsuc);
		else if (Wsuc > Bsuc)
			printf("�鿬��:%d\n", Wsuc);
		else if (Wsuc == Bsuc)
			printf("\n");

		widB = 0;
		widW = 0;
		Bsuc = 1;
		Wsuc = 1;

	}
}

void lengthcount() {

	int lenB = 0;
	int lenW = 0;
	int Bsuc = 1;
	int Wsuc = 1;

	for (y = 0; y < 19; y++) {
		for (x = 0; x < 19; x++) {
			if (pan[x][y] == '@') {
				lenB++;
				for (int z = x + 1; z < 19; z++) {
					if (pan[z][y] == '@') {
						lenB++;
						Bsuc++;
					}
					else {
						x = z - 1;
						break;
					}
				}
			}


			else if (pan[x][y] == 'O') {
				lenW++;
				for (int z = x + 1; z < 19; z++) {
					if (pan[z][y] == 'O') {
						lenW++;
						Wsuc++;
					}
					else {
						x = z - 1;
						break;
					}
				}

			}
		}
		printf("���� %d �浹:%d �鵹:%d", y,	lenB, lenW);

		if (Bsuc > Wsuc)
			printf("�濬��:%d\n", Bsuc);
		else if (Wsuc > Bsuc)
			printf("�鿬��:%d\n", Wsuc);
		else if (Wsuc == Bsuc)
			printf("\n");

		lenB = 0;
		lenW = 0;
		Bsuc = 1;
		Wsuc = 1;

	}

}


void Tdiagonalcount() {
	int TdiaB = 0;
	int TdiaW = 0;
	int Bsuc = 1;
	int Wsuc = 1;

	for (int sum = 0; sum < 37; sum++) {
		for (int x = 0; x < 19; x++) {
			for (int y = 0; y < 19; y++) {
				if (sum == x + y) {
					if (pan[x][y] == '@') {
						TdiaB++;
						for (int z = x+1 , k = y-1; z<19 || k > 0; z++, k--) {
							if (pan[z][k] == '@') {
								TdiaB++;
								Bsuc++;
							}
							else {
								x = z-1;
								y = k+1;
								break;
							}
						}

					}
					else if (pan[x][y] == 'O') {
						TdiaW++;
						for (int z = x+1, k = y-1; z<19 || k > 0 ; z++, k--) {
							if (pan[z][k] == 'O') {
								TdiaW++;
								Wsuc++;
							}
							else {
								x = z-1;
								y = k+1;
								break;
							}
						}

					}


				}
			}
		}

		printf("����밢��:%d �浹:%d �鵹:%d", sum, TdiaB, TdiaW);

		if (Bsuc > Wsuc)
			printf("�濬��:%d\n", Bsuc);
		else if (Wsuc > Bsuc)
			printf("�鿬��:%d\n", Wsuc);
		else if (Wsuc == Bsuc)
			printf("\n");

		TdiaB = 0;
		TdiaW = 0;
		Bsuc = 1;
		Wsuc = 1;





	}

}


void Bdiagonalcount() {
	int BdiaB = 0;
	int BdiaW = 0;
	int Bsuc = 1;
	int Wsuc = 1;

	for (int sum = -18; sum < 19; sum++) {
		for (int x = 0; x < 19; x++) {
			for (int y = 0; y < 19; y++) {
				if (sum == y-x) {
					if (pan[x][y] == '@') {
						BdiaB++;
						for (int z = x + 1, k = y + 1; z < 20 || k<20; z++, k++) {
							if (pan[z][k] == '@') {
								BdiaB++;
								Bsuc++;
							}
							else {
								x = z - 1;
								y = k - 1;
								break;
							}
						}

					}
					else if (pan[x][y] == 'O') {
						BdiaW++;
						for (int z = x + 1, k = y + 1; z < 20 || k<20; z++, k++) {
							if (pan[z][k] == 'O') {
								BdiaW++;
								Wsuc++;
							}
							else {
								x = z - 1;
								y = k - 1;
								break;
							}
						}

					}


				}
			}
		}

		printf("����밢��:%d �浹:%d �鵹:%d", sum+18, BdiaB, BdiaW);

		if (Bsuc > Wsuc)
			printf("�濬��:%d\n", Bsuc);
		else if (Wsuc > Bsuc)
			printf("�鿬��:%d\n", Wsuc);
		else if (Wsuc == Bsuc)
			printf("\n");

		BdiaB = 0;
		BdiaW = 0;
		Bsuc = 1;
		Wsuc = 1;


	}

}

