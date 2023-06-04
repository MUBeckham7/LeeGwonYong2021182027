#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

struct Node {
	char position[20];
	char name[30];
	int hp;
	int attack;
	int defence;
	struct Node* next;
};

struct Node* head;
struct Node* L;

void MAKESINGLE(int num, char* pos, char* name, int hp, int attack, int defence) {
	struct Node* List = (struct Node*)malloc(sizeof(struct Node));
	if (List == NULL)
		return;
	if (num == 0) {
		head = List;
	}
	if (List->next == NULL) {
		List = List->next;
	}

	strcpy(List->position, pos);
	strcpy(List->name, name);
	List->hp = hp;
	List->attack = attack;
	List->defence = defence;
	List->next = NULL;
	
	
}

void PrintSL(struct Node* p,int num) {

	for (int i = 0 ; i < num; i++) {
		printf("%s %s %d %d %d", p->position, p->name, p->hp, p->attack, p->defence);
		p = p->next;
	}

}

int main() {

	char keyword[30];
	int num;
		char temp[30];
		char ch;
		char position[20];
		char name[30];
		int hp;
		int attack;
		int defence;
		int i = 0;
		FILE* file;
		file = fopen("LOLDic.txt", "r");
		
	while (1) {
		printf("PrintSL/PrintDL/SortnameSL/SortnameDL/FindTargetSL/FindTargetDL\n");
		scanf("%s", keyword);

		if (strcmp(keyword, "PrintSL") == 0) {
			while (ch = fgetc(file)) {
			fscanf(file, "%s %s %d %d %d\n", position, name, &hp, &attack, &defence);
			if (strcmp(temp, name) == 0) {
				break;
			}
			else {
				strcpy(temp, name);
			}
			MAKESINGLE(i++,position, name, hp, attack, defence);
		}
			PrintSL(head,i);
		}
		
	}

}