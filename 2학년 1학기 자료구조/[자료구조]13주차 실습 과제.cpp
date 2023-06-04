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

void drawnumber();

void OmOkAi(int Wcount);

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
		printf("스택값이 가득참.\n");
		return;
	}
	newNode->x = x;
	newNode->y = y;
	newNode->next = *Top;
	*Top = newNode;
	printf("%d  %d 이 스택안으로 들어감.\n", x, y);
}

int pop(Stack** Top) {
	Stack* temp = NULL;

	if (IsEmptyStack(*Top)) {
		printf("스택값 비어있음.\n");
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

			printf("흑돌의 갯수:%d\n", Bcount);
			printf("백돌의 갯수:%d\n", Wcount);
			widthcount();
			lengthcount();
			Tdiagonalcount();
			Bdiagonalcount();
			drawnumber();
			drawpan();
			fscanf(File, "%d개 연속", &temp);
			if (temp >= 5) {
				printf("백돌 승!\n");
				return 0;
			}
			printf("흑돌 차례입니다.\n");
			printf("명령어 입력(n,r,u):");
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
			printf("\nx좌표,y좌표:");
			if (scanf("%d %d", &x, &y) == 0) {
				rewind(stdin);
			}

			if ((x < 0 || x >= 19) || (y < 0 || y >= 19)) {
				system("cls");
				break;
			}
			if ((x >= 0 && x <= 18) && (y >= 0 && y <= 18))
				SetBlackEgg(&x, &y);
			fprintf(File, "흑돌 차례, X좌표 :%d Y좌표:%d\n", x, y);
			push(&S, x, y);


			Sleep(300);
			system("cls");
			i++;
			Bcount++;
			fclose(File);
		}

		while (i % 2 == 1) {
			File = fopen("OMOK.txt", "a+");


			printf("흑돌의 갯수:%d\n", Bcount);
			printf("백돌의 갯수:%d\n", Wcount);
			widthcount();
			lengthcount();
			Tdiagonalcount();
			Bdiagonalcount();
			drawnumber();
			drawpan();

			OmOkAi(Wcount);
			/*
			fscanf(File, "%d개 연속", &temp);
			if (temp >= 5) {
				printf("흑돌 승!\n");
				return 0;
			}
			printf("백돌 차례입니다.\n");
			printf("명령어 입력(n,r,u):");
			if (scanf(" %c", &ch) == 1) {
				if (ch == 'u') {
					pop(&S);
					push(&R, data1, data2);
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
			printf("x좌표,y좌표:");

			if (scanf("%d %d", &x, &y) == 0) {
				rewind(stdin);
			}
			if ((x < 0 || x >= 19) || (y < 0 || y >= 19)) {
				system("cls");
				break;
			}
			if ((x >= 0 && x < 19) && (y >= 0 && y < 19))
				SetWhiteEgg(&x, &y);

			fprintf(File, "백돌 차례, X좌표 :%d Y좌표:%d\n", x, y);
			push(&S, x, y);

			*/


			Sleep(300);
			system("cls");
			i++;
			Wcount++;
			fclose(File);
		}





	}



	//fclose(File);
}

void drawnumber() {
	printf("\t");
	for (int i = 0; i < 10; i++)
		printf("%d ", i);
	for (int i = 0; i < 9; i++)
		printf("%d ", i);

	printf("\n");
}


void drawpan() {
	printf("\n");
	for (x = 0; x < 19; x++) {
		printf("%d\t", x);
		for (y = 0; y < 19; y++) {

			if (pan[x][y] == '@')
				printf("○");
			else if (pan[x][y] == 'O')
				printf("●");
			else
				printf("%c ", pan[x][y]);
		}
		printf("\n");

	}
}

void SetBlackEgg(int* a, int* b) {

	if (pan[x][y] == 'X')
		pan[x][y] = '+';

	if (pan[x][y] != '+') {
		printf("이미 돌이 놓여있습니다.\n");
		Bcount--;
		i--;
		return;
	}

	pan[x][y] = '@';

}

void SetWhiteEgg(int* a, int* b) {

	if (pan[x][y] == 'X')
		pan[x][y] = '+';

	if (pan[x][y] != '+') {
		printf("이미 돌이 놓여있습니다.\n");
		i--;
		Wcount--;
		return;
	}

	pan[x][y] = 'O';
}

void widthcount() {
	int widB = 0;
	int widW = 0;
	int Bsuc[19] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int Wsuc[19] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int tmpx[11] = { 1,1,1,1,1,1,1,1,1,1 };
	int tmpy[11] = { 1,1,1,1,1,1,1,1,1,1 };
	int cnt = 0;
	int cmt = 0;
	int tmp = 1;
	for (x = 0; x < 19; x++) {
		for (y = 0; y < 19; y++) {
			if (pan[x][y] == '@') {
				widB++;
				for (int z = y + 1; z < 20; z++) {
					if (pan[x][z] == '@') {
						widB++;
						Bsuc[x]++;
						tmpx[cnt] = Bsuc[x];

					}

					else {
						tmpx[cnt] = Bsuc[x];
						Bsuc[x] = 1;
						cnt++;

						y = z - 1;
						break;
					}
				}
			}


			else if (pan[x][y] == 'O') {
				widW++;
				for (int z = y + 1; z < 20; z++) {
					if (pan[x][z] == 'O') {
						widW++;
						Wsuc[x]++;
						tmpy[cmt] = Wsuc[x];
					}

					else {
						tmpy[cmt] = Wsuc[x];
						Wsuc[x] = 1;
						cmt++;
						y = z - 1;
						break;
					}
				}

			}

		}

		for (cnt = 0; cnt < 9; cnt++) {
			if (tmpx[cnt] > tmpx[cnt + 1])
				Bsuc[x] = tmpx[cnt];
			else if (tmpx[cnt] < tmpx[cnt + 1])
				Bsuc[x] = tmpx[cnt + 1];
		}

		for (cmt = 0; cmt < 9; cmt++) {
			if (tmpy[cmt] > tmpy[cmt + 1])
				Wsuc[x] = tmpy[cmt];
			else if (tmpy[cmt] < tmpy[cmt + 1])
				Wsuc[x] = tmpy[cmt + 1];
		}


		if (Bsuc[x] > Wsuc[x]) {
			if (Bsuc[x] >= 5) {
				temp = Bsuc[x];
				fprintf(File, "흑돌 %d개 연속\n", temp);
			}

			for (y = 0; y < 19; y++) {
				if (pan[x][y] == '@') {
					for (int z = y + 1; z < 20; z++) {
						if (pan[x][z] == '@')
							tmp++;

						else {
							if (tmp == Bsuc[x]) {
								if (pan[x][z] == '+' && z < 19) {
									printf("%d,%d\t", x, z);
									if (tmp == 2) {
										z++;
										if (pan[x][z] == '@'){}
											//pan[x][z - 1] = 'X';
										z--;
									}
									if (tmp > 2){}
										//pan[x][z] = 'X';
								}
								for (int i = 1; i <= tmp; i++) {
									printf("%d,%d\t", x, z - i);
								}
								if (pan[x][z - (tmp + 1)] == '+' && (z - (tmp + 1)) >= 0) {
									printf("%d,%d\t", x, z - (tmp + 1));
									if (tmp == 2) {
										if (pan[x][z - (tmp + 2)] == '@'){}
											//pan[x][z - (tmp + 1)] = 'X';
									}
									if (tmp > 2){}
										//pan[x][z - (tmp + 1)] = 'X';
								}
								printf("\n");
							}
							y = z - 1;
							tmp = 1;
							break;
						}
					}

				}
			}


		}

		else if (Wsuc[x] > Bsuc[x]) {
			if (Wsuc[x] >= 5) {
				temp = Wsuc[x];
				fprintf(File, "백돌 %d개 연속\n", temp);
			}

			for (y = 0; y < 19; y++) {
				if (pan[x][y] == 'O') {
					for (int z = y + 1; z < 20; z++) {
						if (pan[x][z] == 'O')
							tmp++;

						else {
							if (tmp == Wsuc[x]) {
								if (pan[x][z] == '+' && z < 19) {
									printf("%d,%d\t", x, z);
									if (tmp == 2) {
										z++;
										if (pan[x][z] == 'O'){}
											//pan[x][z - 1] = 'X';

										z--;
									}
									if (tmp > 2){}
										//pan[x][z] = 'X';
								}
								for (int i = 1; i <= tmp; i++) {
									printf("%d,%d\t", x, z - i);
								}
								if (pan[x][z - (tmp + 1)] == '+' && (z - (tmp + 1)) >= 0) {
									printf("%d,%d", x, z - (tmp + 1));
									if (tmp == 2) {
										if (pan[x][z - (tmp + 2)] == 'O'){}
											//pan[x][z - (tmp + 1)] = 'X';
									}
									if (tmp > 2){}
										//pan[x][z - (tmp + 1)] = 'X';
								}
								printf("\n");
							}
							y = z - 1;
							tmp = 1;
							break;
						}
					}

				}
			}
		}
		else if (Wsuc[x] == Bsuc[x])
			//printf("\n");



			widB = 0;
		widW = 0;
		for (cnt = 0; cnt < 9; ++cnt) {
			tmpx[cnt] = 1;
		}
		for (cmt = 0; cmt < 9; ++cmt) {
			tmpy[cmt] = 1;
		}
		cnt = 0;
		cmt = 0;
	}
}

void lengthcount() {

	int lenB = 0;
	int lenW = 0;
	int Bsuc[19] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int Wsuc[19] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int tmpx[11] = { 1,1,1,1,1,1,1,1,1,1 };
	int tmpy[11] = { 1,1,1,1,1,1,1,1,1,1 };
	int cnt = 0;
	int cmt = 0;
	int tmp = 1;

	for (y = 0; y < 19; y++) {
		for (x = 0; x < 19; x++) {
			if (pan[x][y] == '@') {
				lenB++;
				for (int z = x + 1; z < 20; z++) {
					if (pan[z][y] == '@') {
						lenB++;
						Bsuc[y]++;
						tmpx[cnt] = Bsuc[y];
					}

					else {
						tmpx[cnt] = Bsuc[y];
						Bsuc[y] = 1;
						cnt++;
						x = z - 1;
						break;
					}
				}
			}


			else if (pan[x][y] == 'O') {
				lenW++;
				for (int z = x + 1; z < 20; z++) {
					if (pan[z][y] == 'O') {
						lenW++;
						Wsuc[y]++;
						tmpy[cmt] = Wsuc[y];
					}
					else {
						tmpy[cmt] = Wsuc[y];
						Wsuc[y] = 1;
						cmt++;
						x = z - 1;
						break;
					}
				}

			}
		}

		for (cnt = 0; cnt < 9; cnt++) {
			if (tmpx[cnt] > tmpx[cnt + 1])
				Bsuc[y] = tmpx[cnt];
			else if (tmpx[cnt] < tmpx[cnt + 1])
				Bsuc[y] = tmpx[cnt + 1];
		}

		for (cmt = 0; cmt < 9; cmt++) {
			if (tmpy[cmt] > tmpy[cmt + 1])
				Wsuc[y] = tmpy[cmt];
			else if (tmpy[cmt] < tmpy[cmt + 1])
				Wsuc[y] = tmpy[cmt + 1];
		}

		if (Bsuc[y] > Wsuc[y]) {
			if (Bsuc[y] >= 5) {
				temp = Bsuc[y];
				fprintf(File, "흑돌 %d개 연속\n", temp);
			}
			for (x = 0; x < 19; x++) {
				if (pan[x][y] == '@') {
					for (int z = x + 1; z < 20; z++) {
						if (pan[z][y] == '@')
							tmp++;
						else {
							if (tmp == Bsuc[y]) {
								if (pan[z][y] == '+' && z < 19) {
									printf("%d,%d\t", z, y);
									if (tmp == 2) {
										z++;
										if (pan[z][y] == '@'){}
											//pan[z - 1][y] = 'X';

										z--;
									}
									if (tmp > 2){}
										//pan[z][y] = 'X';
								}
								for (int i = 1; i <= tmp; i++) {
									printf("%d,%d\t", z - i, y);
								}
								if (pan[z - (tmp + 1)][y] == '+' && (z - (tmp + 1) >= 0)) {
									printf("%d,%d\t", z - (tmp + 1), y);
									if (tmp == 2) {
										if (pan[z - (tmp + 2)][y] == '@'){}
											//pan[z - (tmp + 1)][y] = 'X';
									}
									if (tmp > 2){}
										//pan[z - (tmp + 1)][y] = 'X';
								}

								printf("\n");
							}
							x = z - 1;
							tmp = 1;
							break;
						}
					}
				}
			}
		}
		else if (Wsuc[y] > Bsuc[y]) {
			if (Wsuc[y] >= 5) {
				temp = Wsuc[y];
				fprintf(File, "백돌 %d개 연속\n", temp);
			}
			for (x = 0; x < 19; x++) {
				if (pan[x][y] == 'O')
					for (int z = x + 1; z < 20; z++) {
						if (pan[z][y] == 'O')
							tmp++;
						else {
							if (tmp == Wsuc[y]) {
								if (pan[z][y] == '+' && z < 19) {
									printf("%d,%d\t", z, y);
									if (tmp == 2) {
										z++;
										if (pan[z][y] == 'O'){}
											//pan[z - 1][y] = 'X';

										z--;
									}
									if (tmp > 2){}
										//pan[z][y] = 'X';
								}
								for (int i = 1; i <= tmp; i++) {
									printf("%d,%d\t", z - i, y);
								}
								if (pan[z - (tmp + 1)][y] == '+' && (z - (tmp + 1) >= 0)) {
									printf("%d,%d\t", z - (tmp + 1), y);
									if (tmp == 2) {
										if (pan[z - (tmp + 2)][y] == 'O'){}
											//pan[z - (tmp + 1)][y] = 'X';
									}
									if (tmp > 2){}
										//pan[z - (tmp + 1)][y] = 'X';
								}

								printf("\n");
							}
							x = z - 1;
							tmp = 1;
							break;
						}
					}
			}
		}
		else if (Wsuc[y] == Bsuc[y]) {

		}

		lenB = 0;
		lenW = 0;
		for (cnt = 0; cnt < 9; ++cnt) {
			tmpx[cnt] = 1;
		}
		for (cmt = 0; cmt < 9; ++cmt) {
			tmpy[cmt] = 1;
		}
		cnt = 0;
		cmt = 0;

	}

}


void Tdiagonalcount() {
	int TdiaB = 0;
	int TdiaW = 0;
	int Bsuc[37] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int Wsuc[37] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int tmpx[11] = { 1,1,1,1,1,1,1,1,1,1 };
	int tmpy[11] = { 1,1,1,1,1,1,1,1,1,1 };
	int cnt = 0;
	int cmt = 0;
	int tmp = 1;


	for (int sum = 0; sum < 37; sum++) {
		for (int x = 0; x < 19; x++) {
			for (int y = 0; y < 19; y++) {
				if (sum == x + y) {
					if (pan[x][y] == '@') {
						TdiaB++;
						for (int z = x + 1, k = y - 1; z < 20 || k > -1; z++, k--) {
							if (pan[z][k] == '@') {
								TdiaB++;
								Bsuc[sum]++;
								tmpx[cnt] = Bsuc[sum];
							}
							else {
								tmpx[cnt] = Bsuc[sum];
								Bsuc[sum] = 1;
								cnt++;
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
								Wsuc[sum]++;
								tmpy[cmt] = Wsuc[sum];
							}
							else {
								tmpy[cmt] = Wsuc[sum];
								Wsuc[sum] = 1;
								cmt++;
								x = z - 1;
								y = k + 1;
								break;
							}
						}

					}


				}
			}
		}


		for (cnt = 0; cnt < 9; cnt++) {
			if (tmpx[cnt] > tmpx[cnt + 1])
				Bsuc[sum] = tmpx[cnt];
			else if (tmpx[cnt] < tmpx[cnt + 1])
				Bsuc[sum] = tmpx[cnt + 1];
		}
		for (cmt = 0; cmt < 9; cmt++) {
			if (tmpy[cmt] > tmpy[cmt + 1])
				Wsuc[sum] = tmpy[cmt];
			else if (tmpy[cmt] < tmpy[cmt + 1])
				Wsuc[sum] = tmpy[cmt + 1];
		}



		if (Bsuc[sum] > Wsuc[sum]) {
			if (Bsuc[sum] >= 5) {
				temp = Bsuc[sum];
				fprintf(File, "흑돌 %d개 연속\n", temp);
			}
			for (int x = 0; x < 19; x++) {
				for (int y = 0; y < 19; y++) {
					if (sum == x + y) {
						if (pan[x][y] == '@') {
							for (int z = x + 1, k = y - 1; z<20 || k > -1; z++, k--) {
								if (pan[z][k] == '@')
									tmp++;
								else {
									if (tmp == Bsuc[sum]) {
										if (pan[z][k] == '+' && (z<20 || k > -1)) {
											printf("%d,%d\t", z, k);
											if (tmp == 2) {
												z++;
												k--;

												if (pan[z][k] == '@'){}
													//pan[z - 1][k + 1] = 'X';


												z--;
												k++;
											}
											if (tmp > 2){}
												//pan[z][k] = 'X';
										}
										for (int i = 1; i <= tmp; i++) {
											printf("%d,%d\t", z - i, k + i);
										}
										if (pan[z - (tmp + 1)][k + (tmp + 1)] == '+' && (z - (tmp + 1) <= 20 || k + (tmp + 1) >= 0)) {
											printf("%d,%d\t", z - (tmp + 1), k + (tmp + 1));
											if (tmp == 2) {
												if (pan[z - (tmp + 2)][k + (tmp + 2)] == '@'){}
													//pan[z - (tmp + 1)][k + (tmp + 1)] = 'X';
											}
											if (tmp > 2){}
												//pan[z - (tmp + 1)][k + (tmp + 1)] = 'X';
										}

										printf("\n");
									}
									x = z - 1;
									y = k + 1;
									tmp = 1;
									break;
								}
							}
						}
					}
				}
			}
		}
		else if (Wsuc[sum] > Bsuc[sum]) {
			if (Wsuc[sum] >= 5) {
				temp = Wsuc[sum];
				fprintf(File, "백돌 %d개 연속\n", temp);
			}
			for (int x = 0; x < 19; x++) {
				for (int y = 0; y < 19; y++) {
					if (sum == x + y) {
						if (pan[x][y] == 'O') {
							for (int z = x + 1, k = y - 1; z<20 || k > -1; z++, k--) {
								if (pan[z][k] == 'O')
									tmp++;
								else {
									if (tmp == Wsuc[sum]) {
										if (pan[z][k] == '+' && (z<20 || k > -1)) {
											printf("%d,%d\t", z, k);
											if (tmp == 2) {
												z++;
												k--;

												if (pan[z][k] == 'O'){}
													//pan[z - 1][k + 1] = 'X';


												z--;
												k++;
											}
											if (tmp > 2){}
												//pan[z][k] = 'X';
										}
										for (int i = 1; i <= tmp; i++) {
											printf("%d,%d\t", z - i, k + i);
										}
										if (pan[z - (tmp + 1)][k + (tmp + 1)] == '+' && (z - (tmp + 1) <= 20 || k + (tmp + 1) >= 0)) {
											printf("%d,%d\t", z - (tmp + 1), k + (tmp + 1));
											if (tmp == 2) {
												if (pan[z - (tmp + 2)][k + (tmp + 2)] == 'O'){}
													//pan[z - (tmp + 1)][k + (tmp + 1)] = 'X';
											}
											if (tmp > 2){}
												//pan[z - (tmp + 1)][k + (tmp + 1)] = 'X';
										}


										printf("\n");
									}
									x = z - 1;
									y = k + 1;
									tmp = 1;
									break;
								}
							}
						}
					}
				}
			}
		}
		else if (Wsuc[sum] == Bsuc[sum]) {

		}

		TdiaB = 0;
		TdiaW = 0;
		for (cnt = 0; cnt < 9; ++cnt) {
			tmpx[cnt] = 1;
		}
		for (cmt = 0; cmt < 9; ++cmt) {
			tmpy[cmt] = 1;
		}
		cnt = 0;
		cmt = 0;
	}

}


void Bdiagonalcount() {
	int BdiaB = 0;
	int BdiaW = 0;
	int Bsuc[37] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int Wsuc[37] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int tmpx[11] = { 1,1,1,1,1,1,1,1,1,1 };
	int tmpy[11] = { 1,1,1,1,1,1,1,1,1,1 };
	int cnt = 0;
	int cmt = 0;
	int tmp = 1;


	for (int sum = -18; sum < 19; sum++) {
		for (int x = 0; x < 19; x++) {
			for (int y = 0; y < 19; y++) {
				if (sum == y - x) {
					if (pan[x][y] == '@') {
						BdiaB++;
						for (int z = x + 1, k = y + 1; z < 20 || k < 20; z++, k++) {
							if (pan[z][k] == '@') {
								BdiaB++;
								Bsuc[sum + 18]++;
								tmpx[cnt] = Bsuc[sum + 18];
							}
							else {
								tmpx[cnt] = Bsuc[sum + 18];
								Bsuc[sum + 18] = 1;
								cnt++;
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
								Wsuc[sum + 18]++;
								tmpy[cmt] = Wsuc[sum + 18];
							}
							else {
								tmpy[cmt] = Wsuc[sum + 18];
								Wsuc[sum + 18] = 1;
								cmt++;
								x = z - 1;
								y = k - 1;
								break;
							}
						}

					}


				}
			}
		}

		for (cnt = 0; cnt < 9; cnt++) {
			if (tmpx[cnt] > tmpx[cnt + 1])
				Bsuc[sum + 18] = tmpx[cnt];
			else if (tmpx[cnt] < tmpx[cnt + 1])
				Bsuc[sum + 18] = tmpx[cnt + 1];
		}
		for (cmt = 0; cmt < 9; cmt++) {
			if (tmpy[cmt] > tmpy[cmt + 1])
				Wsuc[sum + 18] = tmpy[cmt];
			else if (tmpy[cmt] < tmpy[cmt + 1])
				Wsuc[sum + 18] = tmpy[cmt + 1];
		}

		if (Bsuc[sum + 18] > Wsuc[sum + 18]) {
			if (Bsuc[sum + 18] >= 5) {
				temp = Bsuc[sum + 18];
				fprintf(File, "흑돌 %d개 연속\n", temp);
			}
			for (int x = 0; x < 19; x++) {
				for (int y = 0; y < 19; y++) {
					if (sum == y - x) {
						if (pan[x][y] == '@') {
							for (int z = x + 1, k = y + 1; z < 20 || k < 20; z++, k++) {
								if (pan[z][k] == '@')
									tmp++;
								else {
									if (tmp == Bsuc[sum + 18]) {
										if (pan[z][k] == '+' && (z < 20 || k < 20)) {
											printf("%d,%d\t", z, k);
											if (tmp == 2) {
												z++;
												k++;

												if (pan[z][k] == '@'){}
													//pan[z - 1][k - 1] = 'X';

												z--;
												k--;
											}
											if (tmp > 2){}
												//pan[z][k] = 'X';
										}
										for (int i = 1; i <= tmp; i++) {
											printf("%d,%d\t", z - i, k - i);
										}
										if (pan[z - (tmp + 1)][k - (tmp + 1)] == '+' && (z - (tmp + 1) <= 20 || k - (tmp + 1) <= 20)) {
											printf("%d,%d\t", z - (tmp + 1), k - (tmp + 1));
											if (tmp == 2) {
												if (pan[z - (tmp + 2)][k - (tmp + 2)] == '@'){}
													//pan[z - (tmp + 1)][k - (tmp + 1)] = 'X';
											}
											if (tmp > 2){}
												//pan[z - (tmp + 1)][k - (tmp + 1)] = 'X';
										}


										printf("\n");
									}
									x = z - 1;
									y = k - 1;
									tmp = 1;
									break;
								}
							}
						}
					}
				}
			}
		}
		else if (Wsuc[sum + 18] > Bsuc[sum + 18]) {
			if (Wsuc[sum + 18] >= 5) {
				temp = Wsuc[sum + 18];
				fprintf(File, "백돌 %d개 연속\n", temp);
			}
			for (int x = 0; x < 19; x++) {
				for (int y = 0; y < 19; y++) {
					if (sum == y - x) {
						if (pan[x][y] == 'O') {
							for (int z = x + 1, k = y + 1; z < 20 || k < 20; z++, k++) {
								if (pan[z][k] == 'O')
									tmp++;
								else {
									if (tmp == Wsuc[sum + 18]) {
										if (pan[z][k] == '+' && (z < 20 || k < 20)) {
											printf("%d,%d\t", z, k);
											if (tmp == 2) {
												z++;
												k++;

												if (pan[z][k] == 'O'){}
													//pan[z - 1][k - 1] = 'X';

												z--;
												k--;
											}
											if (tmp > 2){}
												//pan[z][k] = 'X';
										}
										for (int i = 1; i <= tmp; i++) {
											printf("%d,%d\t", z - i, k - i);
										}
										if (pan[z - (tmp + 1)][k - (tmp + 1)] == '+' && (z - (tmp + 1) <= 20 || k - (tmp + 1) <= 20)) {
											printf("%d,%d\t", z - (tmp + 1), k - (tmp + 1));
											if (tmp == 2) {
												if (pan[z - (tmp + 2)][k - (tmp + 2)] == 'O'){}
													//pan[z - (tmp + 1)][k - (tmp + 1)] = 'X';
											}
											if (tmp > 2){}
												//pan[z - (tmp + 1)][k - (tmp + 1)] = 'X';
										}


										printf("\n");
									}
									x = z - 1;
									y = k - 1;
									tmp = 1;
									break;

								}
							}
						}
					}
				}
			}
		}
		else if (Wsuc[sum + 18] == Bsuc[sum + 18]) {

		}

		BdiaB = 0;
		BdiaW = 0;
		for (cnt = 0; cnt < 9; ++cnt) {
			tmpx[cnt] = 1;
		}
		for (cmt = 0; cmt < 9; ++cmt) {
			tmpy[cmt] = 1;
		}
		cnt = 0;
		cmt = 0;


	}

}
//여기 고칠거.
void OmOkAi(int Wcount) {
	int OmokAiPan[19][19] = { 0, };
	int min[18] = {0,};
	int m = 0;
	for (x = 0; x < 19; x++) {
		for (y = 0; y < 19; y++) {
			if ((x > 0 && x < 18) && (y > 0 && y < 18)) {
				if (pan[x][y] == 'O') {
					if (pan[x][y + 1] == 'O') {
						OmokAiPan[x][y - 1] += 5;
						OmokAiPan[x][y + 2] += 5;
						if (pan[x][y + 2] == 'O') {
							OmokAiPan[x][y + 3] += 15;
							OmokAiPan[x][y - 1] += 15;
						}
					}
					if (pan[x + 1][y] == 'O') {
						OmokAiPan[x - 1][y] += 5;
						OmokAiPan[x + 2][y] += 5;
						if (pan[x + 2][y] == 'O') {
							OmokAiPan[x + 3][y] += 15;
							OmokAiPan[x - 1][y] += 15;
						}
					}
					if (pan[x + 1][y + 1] == 'O') {
						OmokAiPan[x + 2][y + 2] += 5;
						OmokAiPan[x - 1][y - 1] += 5;
						if (pan[x + 2][y + 2] == 'O') {
							OmokAiPan[x + 3][y + 3] += 15;
							OmokAiPan[x - 1][y - 1] += 15;
						}
					}
					if (pan[x + 1][y - 1] == 'O') {
						OmokAiPan[x + 2][y - 2] += 5;
						OmokAiPan[x - 1][y + 1] += 5;
						if (pan[x + 2][y - 2] == 'O') {
							OmokAiPan[x + 3][y - 3] += 15;
							OmokAiPan[x - 1][y + 1] += 15;
						}
					}
					OmokAiPan[x][y]++;
					OmokAiPan[x - 1][y]++;
					OmokAiPan[x + 1][y]++;
					OmokAiPan[x][y - 1]++;
					OmokAiPan[x - 1][y - 1]++;
					OmokAiPan[x + 1][y - 1]++;
					OmokAiPan[x][y + 1] ++;
					OmokAiPan[x - 1][y + 1] ++;
					OmokAiPan[x + 1][y + 1] ++;
				}
				if (pan[x][y] == '@') {
					if (pan[x][y + 1] == '@') {
						OmokAiPan[x][y - 1] -= 10;
						OmokAiPan[x][y + 2] -= 10;
						if (pan[x][y + 2] == '@') {
							OmokAiPan[x][y + 3] -= 30;
							OmokAiPan[x][y - 1] -= 30;
						}
					}
					if (pan[x + 1][y] == '@') {
						OmokAiPan[x - 1][y] -= 10;
						OmokAiPan[x + 2][y] -= 10;
						if (pan[x + 2][y] == '@') {
							OmokAiPan[x + 3][y] -= 30;
							OmokAiPan[x - 1][y] -= 30;
						}
					}
					if (pan[x + 1][y + 1] == '@') {
						OmokAiPan[x + 2][y + 2] -= 10;
						OmokAiPan[x - 1][y - 1] -= 10;
						if (pan[x + 2][y + 2] == '@') {
							OmokAiPan[x + 3][y + 3] -= 30;
							OmokAiPan[x - 1][y - 1] -= 30;
						}
					}
					if (pan[x + 1][y - 1] == '@') {
						OmokAiPan[x + 2][y - 2] -= 10;
						OmokAiPan[x - 1][y + 1] -= 10;
						if (pan[x + 2][y - 2] == '@') {
							OmokAiPan[x + 3][y - 3] -= 30;
							OmokAiPan[x - 1][y + 1] -= 30;
						}
					}
						OmokAiPan[x][y] --;
						OmokAiPan[x - 1][y]--;
						OmokAiPan[x + 1][y]--;
						OmokAiPan[x][y - 1] --;
						OmokAiPan[x - 1][y - 1] --;
						OmokAiPan[x + 1][y - 1] --;
						OmokAiPan[x][y + 1] --;
						OmokAiPan[x - 1][y + 1] --;
						OmokAiPan[x + 1][y + 1]--;
					
				}
			}
			if (min[m] > OmokAiPan[x][y]) {
				min[m++] = min[m];
				min[m] = OmokAiPan[x][y];
			}


		}

	}
	for (x = 0; x < 19; x++) {
		for (y = 0; y < 19; y++) {
			printf("%d ", OmokAiPan[x][y]);
		}
		printf("\n");
	}


	for (x = 0; x < 19; x++) {
		for (y = 0; y < 19; y++) {
			if (min[m] == OmokAiPan[x][y]) {
				if (pan[x][y] == 'O' || pan[x][y] =='@') {
					m++;
					break;
				}
				pan[x][y] = 'O';
				return;
			}
		}
	}

}