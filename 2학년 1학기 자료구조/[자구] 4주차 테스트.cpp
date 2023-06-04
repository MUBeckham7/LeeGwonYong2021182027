#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

struct LOL {
	char name[20];
	int hp;
	int mp;
	int speed;
	int range;
	char position[15];
};

struct LOL Champion[150] = {{"가렌", 620, 0, 340, 175, "top"},{"갈리오", 562, 500, 335, 125, "mid"},{"베인", 515, 231, 330, 550, "bot"},{"티모", 528, 267, 330, 500, "top"},{"소라카", 535, 425, 325, 550, "support"},{"녹턴", 585, 275, 345, 125, "jungle"},{"블리츠크랭크", 582, 267, 325, 125, "support"},{"퀸", 532, 268, 335, 525, "top"},{"아펠리오스", 620, 0, 350, 500, "bot"},{"시비르", 530, 300, 325, 350, "bot"},{"모르가나", 500, 350, 320, 550, "support"},{"코르키", 550, 450, 125, 330,"mid"},{"리 신", 619, 0, 350, 250, "jungle"},{"레나타 글라스크", 500, 235, 330, 125, "support"},{"르블랑", 500, 340, 330, 500, "mid"},{"바드", 490, 300, 330, 300, "support"},{"바루스", 510, 250, 345, 570, "bot"},{"쉔", 620, 0, 330, 200, "top"},{"애쉬", 500, 350, 330, 500, "bot"},{"라이즈", 550, 400, 325, 400, "mid"}, };
int i = 0;

void Search(char* C) {
	for (int i = 0; i < 150; ++i) {
		if (strcmp(C, Champion[i].name) == 0)
			printf("%s,%d,%d,%d,%d,%s", Champion[i].name, Champion[i].hp, Champion[i].mp, Champion[i].speed, Champion[i].range, Champion[i].position);
	}
}

void Insert() {
	for (i = 0; i < 150; ++i) {
		if (Champion[i].name[0] == NULL)
			break;
	}
	printf("챔피언의 정보를 입력하세요.\n");
	scanf("%s %d %d %d %d %s", Champion[i].name, &Champion[i].hp, &Champion[i].mp, &Champion[i].speed, &Champion[i].range, Champion[i].position);
	return;
}

void Delete(char* C) {
	for (i = 0; i < 150; i++) {
		if (strcmp(C, Champion[i].name) == 0) {
			strcpy(Champion[i].name, Champion[i + 1].name);
			Champion[i].hp = Champion[i + 1].hp;
			Champion[i].mp = Champion[i + 1].mp;
			Champion[i].speed = Champion[i + 1].speed;
			Champion[i].range = Champion[i + 1].range;
			strcpy(Champion[i].position, Champion[i+1].position);
			break;
		}
	}

	for (i; i < 150; i++) {
		if (i == 149)
			break;

		strcpy(Champion[i].name, Champion[i + 1].name);
		Champion[i].hp = Champion[i + 1].hp;
		Champion[i].mp = Champion[i + 1].mp;
		Champion[i].speed = Champion[i + 1].speed;
		Champion[i].range = Champion[i + 1].range;
		strcpy(Champion[i].position, Champion[i+1].position);
		
	}
}

void DeleteAll(char* L) {
	for (int i = 0; i < 150; i++) {
		if (strcmp(L, Champion[i].position) == 0) {
			printf("%s,%s\n", Champion[i].name, Champion[i].position);
			Delete(Champion[i].name);
		}
	}
	for (int i = 0; i < 150; i++) {
		if (strcmp(L, Champion[i].position) == 0) {	
			Delete(Champion[i].name);
		}
	}

}

void FindMaxHp() {
	int maxhp = 0;
	maxhp = Champion[0].hp;

	for (int i = 0; i < 150; i++) {
		if (maxhp < Champion[i].hp)
			maxhp = Champion[i].hp;
	}

	for (int i = 0; i < 150; ++i) {
		if (maxhp == Champion[i].hp) {
			printf("%s,%d,%d,%d,%d,%s\n", Champion[i].name, Champion[i].hp, Champion[i].mp, Champion[i].speed, Champion[i].range, Champion[i].position);

		}
	}
}

void SortByHp() {
	int temp = 0;
	char tmp[20];
	char tm[15];
	for (int j = 0; j < 150; ++j) {
		for (int i = 0; i < 149; ++i) {
			if (Champion[i].hp < Champion[i + 1].hp) {
				strcpy(tmp, Champion[i].name);
				strcpy(Champion[i].name, Champion[i + 1].name);
				strcpy(Champion[i + 1].name, tmp);
				temp = Champion[i].hp;
				Champion[i].hp = Champion[i + 1].hp;
				Champion[i + 1].hp = temp;
				temp = Champion[i].mp;
				Champion[i].mp = Champion[i + 1].mp;
				Champion[i + 1].mp = temp;
				temp = Champion[i].speed;
				Champion[i].speed = Champion[i + 1].speed;
				Champion[i + 1].speed = temp;
				temp = Champion[i].range;
				Champion[i].range = Champion[i + 1].range;
				Champion[i + 1].range = temp;
				strcpy(tm, Champion[i].position);
				strcpy(Champion[i].position, Champion[i + 1].position);
				strcpy(Champion[i + 1].position, tm);
			}
		}
	}
	return;
}

int main() {
	char Champ[20];
	char keyword[15];
	char line[15];

	printf("Search/Insert/Delete/DeleteAll/FindMaxHp/SortByHP/PrintAll중에 하나를 입력하세요\n");

	while (1) {
		scanf("%s", keyword);

		if (strcmp(keyword, "Search") == 0) {
			printf("찾고 싶은 챔피언을 입력하세요\n");
			scanf(" %[^\n]s", Champ);
			Search(Champ);
		}
		if (strcmp(keyword, "Insert") == 0) {
			Insert();
		}
		if (strcmp(keyword, "Delete") == 0) {
			printf("삭제하고 싶은 챔피언을 입력하세요\n");
			scanf(" %[^\n]s", Champ);
			Delete(Champ);
		}
		if (strcmp(keyword, "DeleteAll") == 0) {
			printf("삭제하고 싶은 포지션을 입력하세요\n");
			scanf("%s", line);
			DeleteAll(line);
		}
		if (strcmp(keyword, "FindMaxHp") == 0) {
			FindMaxHp();
		}

		if (strcmp(keyword, "SortByHp") == 0) {
			SortByHp();
		}


		if (strcmp(keyword, "PrintAll") == 0) {
			for (int i = 0; i < 150; ++i) {
				if(Champion[i].name[0] != 0)
					printf("%s,%d,%d,%d,%d,%s\n", Champion[i].name, Champion[i].hp, Champion[i].mp, Champion[i].speed, Champion[i].range, Champion[i].position);

			}
		}
	}


}