#include <stdio.h>
#include <string.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS

struct Black {
	int x;
	int y;
	int cnt;
};
struct White {
	int x;
	int y;
	int cnt;
};

int main() {
	int x = 0;
	int y = 0;
	struct Black B;
	struct White W;
	B.cnt = 0;
	W.cnt = 0;
	char pan[18][18];

	for (int x = 0; x < 18; ++x) {
		for (int y = 0; y < 18; ++y) {
			pan[x][y] = '+';
			printf("%c ", pan[x][y]);
		}
		printf("\n");
	}

	for (int i = 0; i < 324;) {

		while (i % 2 == 0) {
			printf("흑돌의 갯수:%d\n", B.cnt);
			printf("백돌의 갯수:%d\n", W.cnt);
			printf("흑돌 차례입니다.\n");
			printf("좌표를 입력하세요:");
			scanf("%d,%d", &B.x, &B.y);

			system("cls");

			pan[B.x][B.y] = '@';

			system("cls");
			for (int x = 0; x < 18; ++x) {
				for (int y = 0; y < 18; ++y) {

					printf("%c ", pan[x][y]);
				}
				printf("\n");
			}
			++B.cnt;
			++i;
		}
		
		

		while (i % 2 == 1) {
			printf("흑돌의 갯수:%d\n", B.cnt);
			printf("백돌의 갯수:%d\n", W.cnt);
			printf("백돌 차례입니다.\n");
			printf("좌표를 입력하세요:");
			scanf("%d,%d", &W.x, &W.y);

			system("cls");

			pan[W.x][W.y] = 'O';

			system("cls");
			for (int x = 0; x < 18; ++x) {
				for (int y = 0; y < 18; ++y) {

					printf("%c ", pan[x][y]);
				}
				printf("\n");
			}
			
			++W.cnt;
			++ i;
		}
		
		while (B.x == W.x && B.y == W.y) {
			printf("이미 돌이 놓여 있습니다.\n");
			printf("다른 좌표를 입력하세요.\n");
			
			if (i % 2 == 0) {
				
				pan[W.x][W.y] = 'O';
				--W.cnt;
				
			}

			if (i % 2 == 1) {
				
				pan[B.x][B.y] = '@';
				--B.cnt;
				
			}

			
			--i;
			Sleep(1000);
			system("cls");

			for (int x = 0; x < 18; ++x) {
				for (int y = 0; y < 18; ++y) {

					printf("%c ", pan[x][y]);
				}
				printf("\n");
			}


		}




	}

}