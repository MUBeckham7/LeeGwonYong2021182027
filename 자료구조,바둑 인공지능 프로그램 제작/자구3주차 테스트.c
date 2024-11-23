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

struct LoL Champion[150] = { {"����",620,0,340,175,"Top"},{"������",562,500,335,125,"Mid"},{"����",515,231,330,500,"Top"},{"Ƽ��",528,267,330,500,"Top"},{"�Ҷ�ī",535,425,325,550,"Support"},{"����",585,275,345,125,"Jungle"},{"����ũ��ũ",582,267,325,125,"Support"},{"��",532,268,335,525,"Top"},{"������",620,0,350,500,"Bot"},{"�ú�",530,350,325,350,"Bot"},{"�𸣰���",500,350,320,550,"Support"},{"�ڸ�Ű",550,450,125,330,"Mid"},{"����",619,0,350,250,"Jungle"},{"����Ÿ �۶�ũ",500,235,330,125,"Support"},{"�ڸ�Ű",500,340,330,500,"Mid"},{"�ٵ�",490,300,330,300,"Support"},{"�ٷ罺",510,250,345,570,"Bot"},{"��",620,0,330,200,"Top"},{"�ֽ�",500,350,330,500,"Bot"},{"������",550,400,325,400,"Mid"} };
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

	printf("�̸�:");
	scanf("%s", Champion[i].name);
	printf("ü��:");
	scanf("%d", &Champion[i].Hp);
	printf("����:");
	scanf("%d", &Champion[i].Mp);
	printf("���ǵ�:");
	scanf("%d", &Champion[i].Speed);
	printf("��Ÿ�:");
	scanf("%d", &Champion[i].Range);
	printf("������:");
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

	printf("Search/Insert/Delete/PrintAll �߿� �ϳ��� �Է��ϼ���\n");

	while (1) {
		scanf("%s", keyword);

		if (strcmp(keyword, "Search") == 0) {
			printf("ã����� è�Ǿ��� �̸��� �Է��ϼ���\n");
			scanf("%s", Champ);
			Search(Champ);
		}
		if (strcmp(keyword, "Insert") == 0) {
			Insert();
		}
		if (strcmp(keyword, "Delete") == 0) {
			printf("�����ϰ� ���� è�Ǿ��� �̸��� �Է��ϼ���\n");
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
