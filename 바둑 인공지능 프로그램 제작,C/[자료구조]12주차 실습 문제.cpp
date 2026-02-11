#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node {
	char position[10];
	char name[20];
	int hp;
	int attack;
	int defence;
	struct Node* next;
};
Node* first;
Node* last;
void addSingle(char* position, char* name, int hp, int attack, int defence, int i) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->position, position);
	strcpy(newNode->name, name);
	newNode->hp = hp;
	newNode->attack = attack;
	newNode->defence = defence;
	newNode->next = nullptr;
	if (first == nullptr)
		first = newNode;
	if (last == nullptr)
		last = newNode;
	else {
		last->next = newNode;
		last = newNode;
	}
}
void PrintAll_SL() {
	Node* current = first;
	while (current) {
		printf("%s %s %d %d %d\n", current->position, current->name, current->hp, current->attack, current->defence);
		current = current->next;
	}
}
void SortByName(int i) {
	Node* current = first;
	char temp1[10], temp2[20];
	int tmp1=0, tmp2=0, tmp3=0, cnt=0;
	while (current) {
		if (current->next == nullptr)
			current = first;

		if (strcmp(current->name, current->next->name) == 1) {
			strcpy(temp1, current->position);
			strcpy(temp2, current->name);
			tmp1 = current->hp;
			tmp2 = current->attack;
			tmp3 = current->defence;

			strcpy(current->position, current->next->position);
			strcpy(current->name, current->next->name);
			current->hp = current->next->hp;
			current->attack = current->next->attack;
			current->defence = current->next->defence;

			strcpy(current->next->position, temp1);
			strcpy(current->next->name, temp2);
			current->next->hp = tmp1;
			current->next->attack = tmp2;
			current->next->defence = tmp3;
		}
		current = current->next;
		cnt++;
		if (cnt == i * (i - 1))
			break;
	}
}

struct BinNode {
	char position[10];
	char name[20];
	int hp;
	int attack;
	int defence;
	struct BinNode* left, * right;
};

BinNode* createNode(char* position, char* name, int hp, int attack, int defence) {
	BinNode* newNode = (BinNode*)malloc(sizeof(BinNode));
	if (newNode != NULL) {
		newNode->left = NULL;
		newNode->right = NULL;
		strcpy(newNode->position, position);
		strcpy(newNode->name, name);
		newNode->hp = hp;
		newNode->attack = attack;
		newNode->defence = defence;
	}
	return newNode;
}

void Insert(struct BinNode** Bin, char* position, char* name, int hp, int attack, int defence) {
	BinNode* head = *Bin;
	if (head == NULL) {
		(*Bin) = createNode(position, name, hp, attack, defence);
		return;
	}
	if (strcmp(name, head->name) == 0)
		return;
	if (strcmp(name, head->name) == 1)
		return Insert(&(head->left), position, name, hp, attack, defence);
	else
		return Insert(&(head->right), position, name, hp, attack, defence);
}

void SearchByName(struct BinNode** Bin, char* champion) {
	BinNode* head = *Bin;
	if (head == NULL)
		return;
	if (strcmp(champion, head->name) == 0) {
		printf("%s %s %d %d %d\n", head->position, head->name, head->hp, head->attack, head->defence);
	}
	if (strcmp(champion, head->name) == 1)
		SearchByName(&(head->left), champion);
	else
		SearchByName(&(head->right), champion);
}

void PrintTreeNode(struct BinNode* Bin) {
	if (Bin == NULL)
		return;

	printf("%s %s %d %d %d\n", Bin->position, Bin->name, Bin->hp, Bin->attack, Bin->defence);

	PrintTreeNode(Bin->left);

	PrintTreeNode(Bin->right);
}

void DeleteNode(struct BinNode* Bin, char* champion) {
	BinNode* parent, * p, * succ, * succ_parent, * child;
	parent = NULL;
	p = Bin;

	while ((p != NULL) && (strcmp(champion, p->name) != 0)) {
		parent = p;
		if (strcmp(champion, p->name) == 1)
			p = p->left;
		else
			p = p->right;
	}
	if (p == NULL)
		return;
	if ((p->left == NULL) && (p->right == NULL)) {
		if (parent != NULL) {
			if (parent->left == p)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else
			Bin = NULL;
	}
	else if ((p->left == NULL) && (p->right == NULL)) {
		if (p->left != NULL)
			child = p->left;
		else
			child = p->right;

		if (parent != NULL) {
			if (parent->left == p)
				parent->left = child;
			else
				parent->right = child;
		}
		else
			Bin = child;
	}
	else {
		succ_parent = p;
		succ = p->left;
		while (succ->right != NULL) {
			succ_parent = succ;
			succ = succ->right;
		}
		if (succ_parent->left = succ)
			succ_parent->left = succ->left;
		else
			succ_parent->right = succ->left;

		strcpy(p->name, succ->name);
		p = succ;
	}
}

int main() {
	char ch;
	char position[10];
	char name[20];
	int hp;
	int attack;
	int defence;
	char temp[20];
	char champion[20];
	int k = 0, i = 0;
	struct BinNode* Bin = NULL;
	FILE* file=NULL;
	file = fopen("LOLDic.txt.crdownload", "r");

	while (1) {
		printf("PrintAll_SL==1 / SortByName==2 /SearchByName==3 / Insert==4 / Delete==5 / PrintALL_BT==6\n");
		scanf("%d", &k);

		if (k == 1) {
			while (ch = fgetc(file)) {
				fscanf(file, "%s %s %d %d %d", position, name, &hp, &attack, &defence);
				if (strcmp(temp, name) == 0)
					break;
				addSingle(position, name, hp, attack, defence, i++);
				strcpy(temp, name);
			}
			PrintAll_SL();
		}
		if (k == 2) {
			while (ch = fgetc(file)) {
				fscanf(file, "%s %s %d %d %d", position, name, &hp, &attack, &defence);
				if (strcmp(temp, name) == 0)
					break;
				addSingle(position, name, hp, attack, defence, i++);
				strcpy(temp, name);
			}
			SortByName(i);
		}
		if (k == 3) {
			printf("찾고싶은 챔피언:");
			scanf("%s", champion);
			while (ch = fgetc(file)) {
				fscanf(file, "%s %s %d %d %d", position, name, &hp, &attack, &defence);
				if (strcmp(temp, name) == 0)
					break;
				Insert(&Bin, position, name, hp, attack, defence);
				strcpy(temp, name);
			}
			SearchByName(&Bin, champion);
		}
		if (k == 4) {
			while (ch = fgetc(file)) {
				fscanf(file, "%s %s %d %d %d", position, name, &hp, &attack, &defence);
				if (strcmp(temp, name) == 0)
					break;
				Insert(&Bin, position, name, hp, attack, defence);
				strcpy(temp, name);
			}
			printf("챔피언의 정보를 입력하시오(position name hp attack defence)\n");
			scanf("%s %s %d %d %d", position, &name, &hp, &attack, &defence);
			Insert(&Bin, position, name, hp, attack, defence);
		}
		if (k == 5) {
			printf("삭제하고싶은 챔피언:");
			scanf("%s", champion);
			while (ch = fgetc(file)) {
				fscanf(file, "%s %s %d %d %d", position, name, &hp, &attack, &defence);
				if (strcmp(temp, name) == 0)
					break;
				Insert(&Bin, position, name, hp, attack, defence);
				strcpy(temp, name);
			}
			DeleteNode(Bin, champion);
		}
		if (k == 6) {
			PrintTreeNode(Bin);
		}
	}
}
