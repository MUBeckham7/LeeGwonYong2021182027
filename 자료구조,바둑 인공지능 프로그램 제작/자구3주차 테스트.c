#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

struct LoL {
	char name[20];
	int Hp;
	int Mp;
	int Speed;
	int Range;
	char Position[8];
};

struct LoL Champion[150] = { {"가렌",620,0,340,175,"Top"},{"갈리오",562,500,335,125,"Mid"},{"베인",515,231,330,500,"Top"},{"티모",528,267,330,500,"Top"},{"소라카",535,425,325,550,"Support"},{"녹턴",585,275,345,125,"Jungle"},{"블리츠크랭크",582,267,325,125,"Support"},{"퀸",532,268,335,525,"Top"},{"웅장지",620,0,350,500,"Bot"},{"시비르",530,350,325,350,"Bot"},{"모르가나",500,350,320,550,"Support"},{"코르키",550,450,125,330,"Mid"},{"리신",619,0,350,250,"Jungle"},{"레나타 글라스크",500,235,330,125,"Support"},{"코르키",500,340,330,500,"Mid"},{"바드",490,300,330,300,"Support"},{"바루스",510,250,345,570,"Bot"},{"쉔",620,0,330,200,"Top"},{"애쉬",500,350,330,500,"Bot"},{"라이즈",550,400,325,400,"Mid"} };
int i = 0;

void Search(char* C) {
	for (int i = 0; i < 150; ++i) {
		if (strcmp(C,Champion[i].name)==0) {
			printf("%s,%d,%d,%d,%d,%s\n", Champion[i].name, Champion[i].Hp, Champion[i].Mp, Champion[i].Speed, Champion[i].Range, Champion[i].Position);
			
		}
	

	}
}
void Insert() {
	for (i = 0; i < 150; i++) {
		if (Champion[i].name[0] == NULL)
			break;
	}

	printf("이름:");
	scanf("%s", Champion[i].name);
	printf("체력:");
	scanf("%d", &Champion[i].Hp);
	printf("마나:");
	scanf("%d", &Champion[i].Mp);
	printf("스피드:");
	scanf("%d", &Champion[i].Speed);
	printf("사거리:");
	scanf("%d", &Champion[i].Range);
	printf("포지션:");
	scanf("%s", &Champion[i].Position);

	printf("%s,%d,%d,%d,%d,%s\n", Champion[i].name, Champion[i].Hp, Champion[i].Mp, Champion[i].Speed, Champion[i].Range, Champion[i].Position);

	return;
}

void Delete(char* C) {
	for (i = 0; i < 150; i++) {
		if (strcmp(C, Champion[i].name) == 0) {
			strcpy(Champion[i].name, Champion[i + 1].name);
			Champion[i].Hp = Champion[i + 1].Hp;
			Champion[i].Mp = Champion[i + 1].Mp;
			Champion[i].Speed = Champion[i + 1].Speed;
			Champion[i].Range = Champion[i + 1].Range;
			strcpy(Champion[i].Position, Champion[i + 1].Position);
			break;
		}
	}
	for (i; i < 150; i++) {
		if (i == 149)
			break;
		strcpy(Champion[i].name, Champion[i + 1].name);
		Champion[i].Hp = Champion[i + 1].Hp;
		Champion[i].Mp = Champion[i + 1].Mp;
		Champion[i].Speed = Champion[i + 1].Speed;
		Champion[i].Range = Champion[i + 1].Range;
		strcpy(Champion[i].Position, Champion[i + 1].Position);
	}


}

int main() {

	char Champ[15];
	char keyword[15];

	printf("Search/Insert/Delete/PrintAll 중에 하나를 입력하세요\n");

	while (1) {
		scanf("%s", keyword);

		if (strcmp(keyword, "Search") == 0) {
			printf("찾고싶은 챔피언의 이름을 입력하세요\n");
			scanf("%s", Champ);
			Search(Champ);
		}
		if (strcmp(keyword, "Insert") == 0) {
			Insert();
		}
		if (strcmp(keyword, "Delete") == 0) {
			printf("삭제하고 싶은 챔피언의 이름을 입력하세요\n");
			scanf("%s", Champ);
			Delete(Champ);
		}
		if (strcmp(keyword, "PrintAll") == 0) {
			for (int i = 0; i < 150; i++) {
				if (Champion[i].name[0] != 0) {
					printf("%s,%d,%d,%d,%d,%s\n", Champion[i].name, Champion[i].Hp, Champion[i].Mp, Champion[i].Speed, Champion[i].Range, Champion[i].Position);
				}
			}
		}

	}

}
