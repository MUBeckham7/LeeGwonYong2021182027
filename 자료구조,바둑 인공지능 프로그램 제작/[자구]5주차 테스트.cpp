#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS //프로젝트 속성/ 일반 /sdl 검사 아니오

struct LoL {
	char name[20];
	int hp;
	int mp;
	int speed;
	int range;
	char position[8];
};

struct LoL Champion[50] = { {}, { "가렌", 620, 0, 340, 175, "top"},{},{}, {"갈리오", 562, 500, 335, 125, "mid"},{"베인", 515, 231, 330, 550, "bot"},{}, {"티모", 528, 267, 330, 500, "top"},{},{},{}, {"소라카", 535, 425, 325, 550, "support"},{},{}, {"녹턴", 585, 275, 345, 125, "jungle"},{"블리츠크랭크", 582, 267, 325, 125, "support"},{},{},{}, {"퀸", 532, 268, 335, 525, "top"},{}, {"아펠리오스", 620, 0, 350, 500, "bot"},{},{}, {"시비르", 530, 300, 325, 350, "bot"},{"모르가나", 500, 350, 320, 550, "support"},{"코르키", 550, 450, 125, 330, "mid"},{"리 신", 619, 0, 350, 250, "jungle"},{},{},{},{}, {"레나타 글라스크", 500, 235, 330, 125, "support"},{"르블랑", 500, 340, 330, 500, "mid"},{"바드", 490, 300, 330, 300, "support"},{},{},{}, {"바루스", 510, 250, 345, 570, "bot"},{"쉔", 620, 0, 330, 200, "top"},{}, {"애쉬", 500, 350, 330, 500, "bot"},{},{}, {"라이즈", 550, 400, 325, 400, "mid"},{},{},{},{},{} };
int i = 0;
char temp[20];
int maxhp = 0;
int temphp = 0;
int j = 0;
int z = 0;

void Search(char* C) {
	if (i == 51) {
		i = 0;
		return;
	}

	if (i == 0)
		strcpy(temp, C);

	if (strcmp(temp, Champion[i].name) == 0) {
		printf("%s,%d,%d,%d,%d,%s\n", Champion[i].name, Champion[i].hp, Champion[i].mp,Champion[i].speed,Champion[i].range,Champion[i].position );
	}
	Search(Champion[i++].name);
}

void Insert() {
	if (Champion[i].name[0] == 0) {
		printf("챔피언의 정보를 입력하세요.\n");
		scanf("%s %d %d %d %d %s", Champion[i].name, &Champion[i].hp, &Champion[i].mp,&Champion[i].speed,&Champion[i].range,Champion[i].position);
		i = 0;
		return;
	}

	i++;
	Insert();
}

void Delete(char* C) {
	if (i == 51) {
		i = 0;
		return;
	}

	if (i == 0)
		strcpy(temp, C);

	if (strcmp(temp, Champion[i].name) == 0) {
		strcpy(Champion[i].name,"");
	}
	Delete(Champion[i++].name);
}

void PrintAll() {

	if (Champion[i].name[0] != 0) {
		printf("%s,%d,%d,%d,%d,%s\n", Champion[i].name, Champion[i].hp, Champion[i].mp, Champion[i].speed, Champion[i].range, Champion[i].position);
	}
	
	i++;
	if (i == 51) {
		i = 0;
		return;
	}
	PrintAll();
}

void DeleteAll(char* C) {

	if (strcmp(C, Champion[i].position) == 0) {
		strcpy(Champion[i].name, "");
	}

	i++;
	if (i == 51) {
		i = 0;
		return;
	}
	DeleteAll(C);
}

void FindMaxHp() {
	
	if (maxhp < Champion[i].hp)
		maxhp = Champion[i].hp;

	if (temphp == Champion[i].hp) {
		if(Champion[i].name[0] != 0)
		printf("%s,%d,%d,%d,%d,%s\n", Champion[i].name, Champion[i].hp, Champion[i].mp, Champion[i].speed, Champion[i].range, Champion[i].position);

	}
	
	i++;

	if (i == 51) {
		temphp = maxhp;
		i = 0;
		j++;
	}
	if (j == 2) {
		i = 0;
		j = 0;
		return;
	}
	FindMaxHp();

}

void SortByHp() {

	if (Champion[i].name == "")
		i++;

	if (Champion[i].name != "") {
		for (z = i + 1; z < 51; z++) {
			if (Champion[z].name != "")
				break;
		}
	}

	if (Champion[i].hp < Champion[z].hp) {
		strcpy(temp, Champion[i].name);
		strcpy(Champion[i].name, Champion[z].name);
		strcpy(Champion[z].name, temp);
		temphp = Champion[i].hp;
		Champion[i].hp = Champion[z].hp;
		Champion[z].hp = temphp;
		temphp = Champion[i].mp;
		Champion[i].mp = Champion[z].mp;
		Champion[z].mp = temphp;
		temphp = Champion[i].speed;
		Champion[i].speed = Champion[z].speed;
		Champion[z].speed = temphp;
		temphp = Champion[i].range;
		Champion[i].range = Champion[z].range;
		Champion[z].range = temphp;
		strcpy(temp, Champion[i].position);
		strcpy(Champion[i].position, Champion[z].position);
		strcpy(Champion[z].position, temp);
	}
	i++;
	if (i == 51) {
		j++;
		i = 0;
	}
	if (j == 50) {
		i = 0;
		j = 0;
		return;
	}

	SortByHp();
}

int main() {

	char Champ[20];
	char keyword[15];
	char line[8];

	printf("Search/Insert/Delete/DeleteAll/PrintAll/FindMaxHp/SortByHp 중에 하나를 입려하세요\n");

	while (1) {
		scanf("%s", keyword);

		if (strcmp(keyword, "Search") == 0) {
			printf("찾고싶은 챔피언의 이름을 입려하시오\n");
			scanf(" %[^\n]s", Champ);
			Search(Champ);
		}
		if (strcmp(keyword, "Insert") == 0) {
			Insert();
		}
		if (strcmp(keyword, "Delete") == 0) {
			printf("삭제하고 싶은 챔피언의 이름을 입력하시오\n");
			scanf(" %[^\n]s", Champ);
			Delete(Champ);
		}
		if (strcmp(keyword, "DeleteAll") == 0) {
			printf("삭제하고 싶은 포지션을 입력하시오\n");
			scanf("%s", line);
			DeleteAll(line);
		}
		if (strcmp(keyword, "PrintAll") == 0) {
			PrintAll();
		}
		if (strcmp(keyword, "FindMaxHp") == 0) {
			FindMaxHp();
		}
		if (strcmp(keyword, "SortByHp") == 0) {
			SortByHp();
		}
	}
}
