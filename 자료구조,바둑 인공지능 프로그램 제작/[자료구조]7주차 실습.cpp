#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS


struct LoL {
	char name[20];
	int hp;
	int mp;
	int speed;
	int range;
	char position[8];
};



struct NODE {
	struct LoL champion;
	struct NODE* next;
};



struct NODE* first = NULL;


void Array2LinkedList(struct LoL Champion[], int n) {
	struct NODE* temp;
	struct NODE* last;

	first = (struct NODE*)malloc(sizeof(struct NODE));
	first->champion = Champion[0];
	first->next = NULL;

	last = first;

	for (int i = 1; i <= n; i++) {
		temp = (struct NODE*)malloc(sizeof(struct NODE));
		temp->champion = Champion[i];
		temp->next = NULL;
		last->next = temp;
		last = temp;
		if (i == n) {
			last->next = first;
			last = first;
		}
	}


}

void Search(struct NODE* p, char* C, int n) {

	for (int i = 0; i < n; i++) {
		if (strcmp(C, p->champion.name) == 0) {
			printf("%s,%d,%d,%d,%d,%s", p->champion.name, p->champion.hp, p->champion.mp, p->champion.speed, p->champion.range, p->champion.position);

		}
		p = p->next;
	}

}
//���̿� 700 100 200 300 Top
void Insert(struct NODE* p, int n) {
	struct NODE* pre;
	for (int i = 0; i < n; i++) {

		pre = p->next;
		while (pre->next != p) {
			pre = pre->next;
		}
		pre->next = p->next;

		if (i == n - 1) {

			pre->next = p;		//���� ù��°�� ����Ǿ���� ���������� �� ���� ������Ѿ��ϴ� ���

			scanf("%s,%d,%d,%d,%d,%s\n", p->champion.name, &p->champion.hp, &p->champion.mp, &p->champion.speed, &p->champion.range, p->champion.position);

			p->next = first;	//������ ��带 �ٽ� ù��°�� ��������ִ� ���.

			//������ ��尡 ������� ������ �߻��մϴ�..
		}
		p = p->next;
	}

}

void Delete(struct NODE* p, char* C, int n) {
	struct NODE* pre;

	for (int i = 0; i < n; i++) {

		if (strcmp(C, p->champion.name) == 0) {
			pre = p->next;
			while (pre->next != p) {
				pre = pre->next;
			}
			pre->next = p->next;

		}

		if (i == 0 && strcmp(C, p->champion.name) == 0) {
			first = first->next;
		}



		p = p->next;
	}
	return;
}

void DeleteAll(struct NODE* p, char* C, int n) {
	struct NODE* pre;
	for (int i = 0; i < n; i++) {

		if (strcmp(C, p->champion.position) == 0) {
			pre = p->next;
			while (pre->next != p) {
				pre = pre->next;
			}
			pre->next = p->next;
		}

		if (i == 0 && strcmp(C, p->champion.position) == 0) {

			first = first->next;
		}

		p = p->next;
	}

}

void FindMaxHp(struct NODE* p, int n) {
	int maxhp = 0;
	for (int i = 0; i < n; i++) {
		if (maxhp < p->champion.hp)
			maxhp = p->champion.hp;

		p = p->next;
	}

	for (int i = 0; i < n; i++) {
		if (maxhp == p->champion.hp) {
			printf("%s,%d,%d,%d,%d,%s\n", p->champion.name, p->champion.hp, p->champion.mp, p->champion.speed, p->champion.range, p->champion.position);
		}

		p = p->next;
	}


}

void SortByHP(struct NODE* p, int n) {
	struct NODE* pre;
	struct NODE* prepre;
	int hp = p->champion.hp;

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < n; j++) {


			if (hp <= p->champion.hp) {
				hp = p->champion.hp;
				pre = p->next;
				prepre = pre->next;
				while (prepre->next != pre) {
					prepre = prepre->next;
				}
				while (pre->next != p) {
					pre = pre->next;
				}
				pre->next = prepre->next;
				p->next = pre->next;
				prepre->next = p->next;





			}
			p = p->next;
		}
	}


	for (int i = 0; i < n; i++) {
		printf("%s,%d,%d,%d,%d,%s\n", p->champion.name, p->champion.hp, p->champion.mp, p->champion.speed, p->champion.range, p->champion.position);
		p = p->next;
	}


}

void PrintAll(struct NODE* p, int n) {
	for (int i = 0; i <= n; i++) {
		printf("%s,%d,%d,%d,%d,%s\n", p->champion.name, p->champion.hp, p->champion.mp, p->champion.speed, p->champion.range, p->champion.position);
		p = p->next;
	}
}

int main() {
	int x = 0;

	struct LoL Champion[] = { {"����", 620, 0, 340, 175, "Top"},{ "������",523,500,335,125,"Mid" }, { "����",515,231,330,500,"Top" },{ "Ƽ��",528,267,330,500,"Top" }, { "�Ҷ�ī",535,425,325,550,"Support" }, { "����",585,275,345,125,"Jungle" }, { "����ũ��ũ",582,267,325,125,"Support" },{ "��",532,268,335,525,"Top" }, { "������",620,0,350,500,"Bot" },{ "�ú�",530,350,325,350,"Bot" }, { "�𸣰���",500,350,320,550,"Support" }, { "�ڸ�Ű",550,450,125,330,"Mid" },{ "����",619,0,350,250,"Jungle" },{ "����Ÿ �۶�ũ",500,235,330,125,"Support" }, { "�ڸ�Ű",500,340,330,500,"Mid" },{ "�ٵ�",490,300,330,300,"Support" }, { "�ٷ罺",510,250,345,570,"Bot" }, { "��",620,0,330,200,"Top" }, { "�ֽ�",500,350,330,500,"Bot" },{ "������",550,400,325,400,"Mid" } };
	char Champ[20];
	char keyword[15];
	char line[8];

	Array2LinkedList(Champion, 19);


	printf("Search/Insert/Delete/DeleteAll/PrintAll/FindMaxHp/SortByHP\n");

	while (1) {
		scanf("%s", keyword);

		if (strcmp(keyword, "Search") == 0) {
			printf("�̸�:");
			scanf("%s", Champ);
			Search(first, Champ, 20 + x);
		}
		else if (strcmp(keyword, "Insert") == 0) {
			printf("è�Ǿ��� ������ �Է��ϼ���\n");
			x++;
			Insert(first, 20 + x);

		}
		else if (strcmp(keyword, "Delete") == 0) {
			printf("�̸�:");
			scanf("%s", Champ);
			Delete(first, Champ, 20 + x);
		}
		else if (strcmp(keyword, "DeleteAll") == 0) {
			printf("�����ϰ� ���� ������ �Է��ϼ���:");
			scanf("%s", line);
			DeleteAll(first, line, 20 + x);
		}
		else if (strcmp(keyword, "PrintAll") == 0) {
			PrintAll(first, 20 + x);
		}
		else if (strcmp(keyword, "FindMaxHp") == 0) {
			FindMaxHp(first, 20 + x);
		}
		else if (strcmp(keyword, "SortByHp") == 0) {
			SortByHP(first, 20 + x);
		}
	}

}