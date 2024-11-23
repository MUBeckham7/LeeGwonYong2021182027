#include <stdio.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
char pan[19][19];

int i = 0;
int x = 0;
int y = 0;
int c;
int Bcount = 0;
int Wcount = 0;
FILE* File;
int temp;
int data1 = 0;
int data2 = 0;
char ch;
void drawpan();

void SetBlackEgg(int* a, int* b);

void SetWhiteEgg(int* a, int* b);

void widthcount();

void lengthcount();

void Tdiagonalcount();

void Bdiagonalcount();



typedef struct ListStack {
	int x;
	int y;
	struct ListStack* next;
}Stack;


int IsEmptyStack(Stack* Top) {
	return (Top == NULL);
}

void push(Stack** Top, int x, int y) {
	Stack* newNode = NULL;

	newNode = (Stack*)malloc(sizeof(Stack));
	if (newNode == NULL) {
		printf("���ð��� ������.\n");
		return;
	}
	newNode->x = x;
	newNode->y = y;
	newNode->next = *Top;
	*Top = newNode;
	printf("%d  %d �� ���þ����� ��.\n", x, y);
}

int pop(Stack** Top) {
	Stack* temp = NULL;

	if (IsEmptyStack(*Top)) {
		printf("���ð� �������.\n");
		return INT_MIN;
	}
	else {

		temp = *Top;
		*Top = temp->next;
		data1 = temp->x;
		data2 = temp->y;
		free(temp);

	}
	return data1, data2;
}

int main() {


	File = fopen("OMOK.txt", "w");
	fclose(File);

	Stack* S = NULL;
	Stack* R = NULL;

	for (x = 0; x < 19; x++) {
		for (y = 0; y < 19; y++) {
			pan[x][y] = '+';

		}
	}



	for (i = 0; i < 324;) {

		while (i % 2 == 0) {
			File = fopen("OMOK.txt", "a+");

			printf("�浹�� ����:%d\n", Bcount);
			printf("�鵹�� ����:%d\n", Wcount);
			widthcount();
			lengthcount();
			Tdiagonalcount();
			Bdiagonalcount();
			drawpan();
			fscanf(File, "%d�� ����", &temp);
			if (temp >= 5) {
				printf("�鵹 ��!\n");
				return 0;
			}
			printf("�浹 �����Դϴ�.\n");
			printf("��ɾ� �Է�(n,r,u):");
			if (scanf(" %c", &ch) == 1) {
				if (ch == 'u') {
					pop(&S);
					push(&R, data1, data2);
					if (i == 0) {
						i++;
					}
					i--;
					pan[data1][data2] = '+';
					Wcount--;
					rewind(stdin);
					system("cls");
					break;
				}
				else if (ch == 'r') {
					if (pop(&R) == INT_MIN) {
						break;
					}
					
					i++;
					pan[data1][data2] = '@';
					Bcount++;
					rewind(stdin);
					system("cls");
					break;
				}
				else if (ch == 'n') {
					rewind(stdin);
				}
				else if (ch == 'q') {
					fclose(File);
					return 0;
				}
			}
			printf("\nx��ǥ,y��ǥ:");
			if (scanf("%d %d", &x, &y) == 0) {
				rewind(stdin);
			}

			if ((x < 0 || x >= 19) || (y < 0 || y >= 19)) {
				system("cls");
				break;
			}
			if ((x >= 0 && x <= 18) && (y >= 0 && y <= 18))
				SetBlackEgg(&x, &y);
			fprintf(File, "�浹 ����, X��ǥ :%d Y��ǥ:%d\n", x, y);
			push(&S, x, y);


			Sleep(300);
			system("cls");
			i++;
			Bcount++;
			fclose(File);
		}

		while (i % 2 == 1) {
			File = fopen("OMOK.txt", "a+");


			printf("�浹�� ����:%d\n", Bcount);
			printf("�鵹�� ����:%d\n", Wcount);
			widthcount();
			lengthcount();
			Tdiagonalcount();
			Bdiagonalcount();
			drawpan();
			fscanf(File, "%d�� ����", &temp);
			if (temp >= 5) {
				printf("�浹 ��!\n");
				return 0;
			}
			printf("�鵹 �����Դϴ�.\n");
			printf("��ɾ� �Է�(n,r,u):");
			if (scanf(" %c", &ch) == 1) {
				if (ch == 'u') {
					pop(&S);
					push(&R,data1,data2);
					i--;
					pan[data1][data2] = '+';
					Bcount--;
					rewind(stdin);
					system("cls");
					break;
				}
				else if (ch == 'r') {
					if (pop(&R) == INT_MIN) {
						break;
					}
					i++;
					pan[data1][data2] = 'O';
					Wcount++;
					rewind(stdin);
					system("cls");
					break;
				}
				else if (ch == 'n') {
					rewind(stdin);
				}
				else if (ch == 'q') {
					fclose(File);
					return 0;
				}
			}
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

			fprintf(File, "�鵹 ����, X��ǥ :%d Y��ǥ:%d\n", x, y);
			push(&S, x, y);




			Sleep(300);
			system("cls");
			i++;
			Wcount++;
			fclose(File);
		}





	}



	//fclose(File);
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
					else if (pan[x][z] == 'O') {
						widW++;
						Bsuc = 0;
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
					else if (pan[x][z] == '@') {
						widB++;
						Wsuc = 0;
					}
					else {
						y = z - 1;
						break;
					}
				}

			}
		}
		printf("���� %d �浹:%d �鵹:%d", x, widB, widW);

		if (Bsuc > Wsuc) {
			printf("�濬��:%d\n", Bsuc);
			if (Bsuc >= 5) {
				temp = Bsuc;
				fprintf(File, "�浹 %d�� ����\n", temp);
			}
		}

		else if (Wsuc > Bsuc) {
			printf("�鿬��:%d\n", Wsuc);
			if (Wsuc >= 5) {
				temp = Bsuc;
				fprintf(File, "�鵹 %d�� ����\n", temp);
			}
		}
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
		printf("���� %d �浹:%d �鵹:%d", y, lenB, lenW);

		if (Bsuc > Wsuc) {
			printf("�濬��:%d\n", Bsuc);
			if (Bsuc >= 5) {
				temp = Bsuc;
				fprintf(File, "�浹 %d�� ����\n", temp);
			}
		}
		else if (Wsuc > Bsuc) {
			printf("�鿬��:%d\n", Wsuc);
			if (Wsuc >= 5) {
				temp = Bsuc;
				fprintf(File, "�鵹 %d�� ����\n", temp);
			}
		}
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
						for (int z = x + 1, k = y - 1; z < 20 || k > -1; z++, k--) {
							if (pan[z][k] == '@') {
								TdiaB++;
								Bsuc++;

							}
							else {
								
								x = z - 1;
								y = k + 1;
								break;
							}
						}

					}
					else if (pan[x][y] == 'O') {
						TdiaW++;
						for (int z = x + 1, k = y - 1; z < 20 || k > -1; z++, k--) {
							if (pan[z][k] == 'O') {
								TdiaW++;
								Wsuc++;
							}
							else {
								x = z - 1;
								y = k + 1;
								break;
							}
						}

					}


				}
			}
		}

		printf("����밢��:%d �浹:%d �鵹:%d", sum, TdiaB, TdiaW);

		if (Bsuc > Wsuc) {
			printf("�濬��:%d\n", Bsuc);
			if (Bsuc >= 5) {
				temp = Bsuc;
				fprintf(File, "�浹 %d�� ����\n", temp);
			}
		}
		else if (Wsuc > Bsuc) {
			printf("�鿬��:%d\n", Wsuc);
			if (Wsuc >= 5) {
				temp = Bsuc;
				fprintf(File, "�鵹 %d�� ����\n", temp);
			}
		}
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
				if (sum == y - x) {
					if (pan[x][y] == '@') {
						BdiaB++;
						for (int z = x + 1, k = y + 1; z < 20 || k < 20; z++, k++) {
							if (pan[z][k] == '@') {
								BdiaB++;
								Bsuc++;
							}
							else {
								Bsuc = 1;
								x = z - 1;
								y = k - 1;
								break;
							}
						}

					}
					else if (pan[x][y] == 'O') {
						BdiaW++;
						for (int z = x + 1, k = y + 1; z < 20 || k < 20; z++, k++) {
							if (pan[z][k] == 'O') {
								BdiaW++;
								Wsuc++;
							}
							else {
								Wsuc = 1;
								x = z - 1;
								y = k - 1;
								break;
							}
						}

					}


				}
			}
		}

		printf("����밢��:%d �浹:%d �鵹:%d", sum + 18, BdiaB, BdiaW);

		if (Bsuc > Wsuc) {
			printf("�濬��:%d\n", Bsuc);
			if (Bsuc >= 5) {
				temp = Bsuc;
				fprintf(File, "�浹 %d�� ����\n", temp);
			}
		}
		else if (Wsuc > Bsuc) {
			printf("�鿬��:%d\n", Wsuc);
			if (Wsuc >= 5) {
				temp = Bsuc;
				fprintf(File, "�鵹 %d�� ����\n", temp);
			}
		}
		else if (Wsuc == Bsuc)
			printf("\n");

		BdiaB = 0;
		BdiaW = 0;
		Bsuc = 1;
		Wsuc = 1;


	}

}