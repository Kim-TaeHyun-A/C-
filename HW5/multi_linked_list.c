#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
// Academy Award List application(Generic Coding ����)
// General Linear List�� Multilinked List�� �����Ͽ� ������ ���� Extra Point�� �ο���
// ��, link�� Year�� ��ȭ������ ���ĺ�/������ ���� �� 2���� ������. ���� �Ʒ� Test Case�� ���� �ؼ��� �ణ �����Ǿ�� ��.
typedef struct tListNode {
	int year;
	char movie_name[100];
	char director[50];
	struct tListNode* link_year;
	struct tListNode* link_movie_name;
	struct tListNode* link_director;
}ListNode;
typedef struct {
	int count;
	ListNode* head_year;
	ListNode* head_movie_name;
	ListNode* head_director;
}List;

// �Լ� ���� ����
List* createList();

void _insertList(List* pList, ListNode* pPre[], ListNode* pLoc[], int year, char movie_name[], char director[]);

bool _searchList_year(List* pList, ListNode** ppPre, ListNode** ppLoc, int year);
bool _searchList_movie_name(List* pList, ListNode** ppPre, ListNode** ppLoc, char movie_name[]);
bool _searchList_director(List* pList, ListNode** ppPre, ListNode** ppLoc, char director[]);

void addNodeList(List* pList, int year, char movie_name[], char director[]);

void searchNode_show_year(List* pList, int year);
void searchNode_show_movie_name(List* pList, char movie_name[]);
void searchNode_show_director(List* pList, char director[]);

void printAll_year(List* pList);
void printAll_movie_name(List* pList);
void printAll_director(List* pList);

void removeList(List* pList, int year, char movie_name[], char director[]);
void _deleteList_year(List* pList, ListNode* pPre, ListNode* pLoc);
void _deleteList_movie_name(List* pList, ListNode* pPre, ListNode* pLoc);
void _deleteList_director(List* pList, ListNode* pPre, ListNode* pLoc);

int main() {
	char menu;
	int year; char movie_name[50]; char director[20]; // to get three data from user
	List* record = createList();
	while (1) {
		printf("===========menu=========\n"
			"P : print all list of awarded prictures\n"
			"S : search\n"
			"I : insert a node to the list\n"
			"D : delete a node from the list\n"
			"Q : quit\n"
			">>>"); scanf("%c", &menu);
		switch (menu) {
		case 'P':
			//print all list of awarded pictures
			if (record->head_year == NULL) {
				printf("\tthis list is empty\n");
				break;
			}
			printf("\n\n=========�⵵ ������������ ��ü ���==========\n");
			printAll_year(record);

			printf("\n\n=========��ȭ �̸� ���ĺ������� ��ü ���==========\n");
			printAll_movie_name(record);

			printf("\n\n=========���� ���亪������ ��ü ���==========\n\n");
			printAll_director(record);
			break;
		case 'S':
			if (record->head_year == NULL) {
				printf("\tthis list is empty\n");
				break;
			}
			printf("\n\n=========�⵵�� �˻�==========\n");
			printf("\tyear: "); scanf("%d", &year);
			searchNode_show_year(record, year);
			
			printf("\n\n=========��ȭ �̸����� �˻�==========\n");
			printf("\tmovie_name: "); scanf("%d", movie_name);
			searchNode_show_movie_name(record, movie_name);
			
			break;
		case 'I':
			// insert a node to the list
			//������ ���⵵, ��ȭ����, �����̸����� ����ڷκ���(Ű����) �Է� �޾� ����
			printf("\tyear: "); scanf("%d", &year);
			printf("\tmovie name: "); scanf("%s", movie_name);
			printf("\tdirector: "); scanf("%s", director);
			addNodeList(record, year, movie_name, director);
			break;
		case 'D':
			//delete a node from the list using link
			// ������  ���⵵, ��ȭ����, �����̸����� ����ڷκ���(Ű����) �Է� �޾� ����
			if (record->head_year == NULL) {
				printf("\tthis list is empty\n");
				break;
			}
			printf("\tyear: "); scanf("%d", &year);
			printf("\tmovie name: "); scanf("%s", movie_name);
			printf("\tdirector: "); scanf("%s", director);
			removeList(record, year, movie_name, director);
			break;
		case 'Q':
			printf("\nend the program\n");
			return;
		default:
			printf("\n\t�޴��� �ٽ� Ȯ���ϼ���.\n");
		}
		system("pause");
		system("cls");
	}
}// main ��

List* createList() {
	// List ����
	List* pNewList = (List*)malloc(sizeof(List));
	if (pNewList == NULL)
		return NULL;
	pNewList->count = 0; // node �� 0���� �ʱ�ȭ
	pNewList->head_year = NULL;
	pNewList->head_movie_name = NULL;
	pNewList->head_director = NULL;

	return pNewList;
}

void _insertList(List* pList, ListNode* pPre[], ListNode* pLoc[], int year, char movie_name[], char director[]) {
	// list�� node ����

	// pPre[0], pLoc[0] => year(�⵵ ��������)
	// pPre[1], pLoc[1] => movie_name(���ĺ���)
	// pPre[2], pLoc[2] => director(���ĺ���)

	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));//��� ����

	// ������ ��忡 �Է�
	pNewNode->year = year;
	strcpy(pNewNode->movie_name, movie_name);
	strcpy(pNewNode->director, director);

	//�� ���� ����
	if (pPre[0] == NULL) {
		//list ���� �տ� ����
		pList->head_year = pNewNode;
	}
	else {
		// list �߰��̳� �� �ڿ� ����
		pPre[0]->link_year = pNewNode;
	}

	if (pPre[1] == NULL) {
		//list ���� �տ� ����
		pList->head_movie_name = pNewNode;
	}
	else {
		// list �߰��̳� �� �ڿ� ����
		pPre[1]->link_movie_name = pNewNode;
	}

	if (pPre[1] == NULL) {
		//list ���� �տ� ����
		pList->head_director = pNewNode;
	}
	else {
		// list �߰��̳� �� �ڿ� ����
		pPre[2]->link_director = pNewNode;
	}

	// �� ���� ����
	pNewNode->link_year = pLoc[0];
	pNewNode->link_movie_name = pLoc[1];
	pNewNode->link_director = pLoc[2];

	pList->count++; // ��� �� ����
}

bool _searchList_year(List* pList, ListNode** ppPre, ListNode** ppLoc, int year) {
	// link_year�� �̿��ؼ� ���ĺ������� �˻� ����
	// �Է� ���� year�� �����ϴ��� �˻�
	for (*ppPre = NULL, *ppLoc = pList->head_year; *ppLoc != NULL; *ppPre = *ppLoc, *ppLoc = (*ppLoc)->link_year) {
		if ((*ppLoc)->year == year)// �Է��� year�� list���� ã����
			return true;
		else if ((*ppLoc)->year > year)
			// ���� Ȯ�� ���� ���� ã������ ������ ū ��� ���Ŀ� ã������ �����Ͱ� ���� �� ��� ã�� ����
			// Ȯ�� ���� ���� ������ Ȯ���ߴ� ������ �׻� ũ��.
			break;
	}
	return false;
}

bool _searchList_movie_name(List* pList, ListNode** ppPre, ListNode** ppLoc, char movie_name[]) {
	// link_movie_name�� �̿��ؼ� ���ĺ������� �˻� ����
	// �Է� ���� movie_name�� �����ϴ��� �˻�
	for (*ppPre = NULL, *ppLoc = pList->head_movie_name; *ppLoc != NULL; *ppPre = *ppLoc, *ppLoc = (*ppLoc)->link_movie_name) {
		if (strcmp((*ppLoc)->movie_name, movie_name) == 0)// �Է��� movie_name�� list���� ã����
			return true;
		else if (strcmp((*ppLoc)->movie_name, movie_name) > 0)
			// ���ڿ��� �ƽ�Ű�ڵ带 �̿��ؼ� ���ĺ� ������ �迭
			// strcmp("aab","aaa") > 0
			// strcmp("aab","aac") < 0
			// ���� Ȯ�� ���� ���� ã������ ������ ū ��� ���Ŀ� ã������ �����Ͱ� ���� �� ��� ã�� ����
			// Ȯ�� ���� ���� ������ Ȯ���ߴ� ������ �׻� ũ��.
			break;
	}
	return false;
}

bool _searchList_director(List* pList, ListNode** ppPre, ListNode** ppLoc, char director[]) {
	// link_director�� �̿��ؼ� ���ĺ������� �˻� ����
	// �Է� ���� director�� �����ϴ��� �˻�
	for (*ppPre = NULL, *ppLoc = pList->head_director; *ppLoc != NULL; *ppPre = *ppLoc, *ppLoc = (*ppLoc)->link_director) {
		if (strcmp((*ppLoc)->director, director) == 0)// �Է��� movie_name�� list���� ã����
			return true;
		else if (strcmp((*ppLoc)->director, director) > 0)
			// ���ڿ��� �ƽ�Ű�ڵ带 �̿��ؼ� ���ĺ� ������ �迭
			// strcmp("aab","aaa") > 0
			// strcmp("aab","aac") < 0
			// ���� Ȯ�� ���� ���� ã������ ������ ū ��� ���Ŀ� ã������ �����Ͱ� ���� �� ��� ã�� ����
			// Ȯ�� ���� ���� ������ Ȯ���ߴ� ������ �׻� ũ��.
			break;
	}
	return false;
}

void addNodeList(List* pList, int year, char movie_name[], char director[]) { 
	// list�� node �߰�
	//������ ������ ���� ������ ���� �Ұ�
	ListNode* pPre[3] = { NULL }, * pLoc[3] = { NULL };
	// pPre[0], pLoc[0] => year(�⵵ ��������)
	// pPre[1], pLoc[1] => movie_name(���ĺ���)
	// pPre[2], pLoc[2] => director(���ĺ���)
	bool found = _searchList_year(pList, &pPre[0], &pLoc[0], year);
	if (found) // ������ ���� �Ұ�(year ����)
		return;
	found = _searchList_movie_name(pList, &pPre[1], &pLoc[1], movie_name);
	if (found) // ������ ���� �Ұ�(movie_name ����)
		return;
	found = _searchList_director(pList, &pPre[2], &pLoc[2], director);
	if (!found) // ���ο� ������ ���԰���
		_insertList(pList, pPre, pLoc, year, movie_name, director);
}

void searchNode_show_year(List* pList, int year) {
	// �Է��� year���� ���� ���� ���
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _searchList_year(pList, &pPre, &pLoc, year);
	if (found)
		printf("\t\n%d�⿡ %s�� %s�� �����߽��ϴ�.\n", pLoc->year, pLoc->movie_name, pLoc->director);
	else
		printf("\t\n�Է��� �⵵�� ���󳻿��� ã�� �� �����ϴ�.\n");
}

void searchNode_show_movie_name(List* pList, char movie_name[]) {
	// �Է��� movie_name�� ���� ���� ���
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _searchList_movie_name(pList, &pPre, &pLoc, movie_name);
	if (found)
		printf("\t\n%d�⿡ %s�� %s�� �����߽��ϴ�.\n", pLoc->year, pLoc->movie_name, pLoc->director);
	else
		printf("\t\n�Է��� ��ȭ �̸��� ���󳻿��� ã�� �� �����ϴ�.\n");
}

void searchNode_show_director(List* pList, char director[]) {
	// �Է��� director�� ���� ���� ���
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _searchList_director(pList, &pPre, &pLoc, director);
	if (found)
		printf("\t\n%d�⿡ %s�� %s�� �����߽��ϴ�.\n", pLoc->year, pLoc->movie_name, pLoc->director);
	else
		printf("\t\n�Է��� ������ ���󳻿��� ã�� �� �����ϴ�.\n");
}

void printAll_year(List* pList) {
	// list�� ����� ��� ���� ���(year ��������)
	int n = 0;
	if (pList->count == 0) {//list�� ����� node�� ����.
		printf("\t\nthis list is empty\n");
		return;
	}
	ListNode* pLoc = pList->head_year; // ���� ��ġ�� head_year�� ����Ű�� node, �� ù ��° node
	while (++n <= pList->count) { // ���������� ��� node�� ����Ѵ�.
		printf("\t\nnum%d: %d�⿡ %s(��)�� %s(��)�� �����߽��ϴ�.\n\n", n, pLoc->year, pLoc->movie_name, pLoc->director);
		pLoc = pLoc->link_year;
	}
}

void printAll_movie_name(List* pList) {
	// list�� ����� ��� ���� ���(movie_name ���ĺ���)
	int n = 0;
	if (pList->count == 0) {//list�� ����� node�� ����.
		printf("\t\nthis list is empty\n");
		return;
	}
	ListNode* pLoc = pList->head_movie_name; // ���� ��ġ�� head_movie_name�� ����Ű�� node, �� ù ��° node
	while (++n <= pList->count) { // ���������� ��� node�� ����Ѵ�.
		printf("\t\nnum%d: %d�⿡ %s(��)�� %s(��)�� �����߽��ϴ�.\n\n", n, pLoc->year, pLoc->movie_name, pLoc->director);
		pLoc = pLoc->link_movie_name;
	}
}

void printAll_director(List* pList) {
	// list�� ����� ��� ���� ���(director ���ĺ���)
	int n = 0;
	if (pList->count == 0) {//list�� ����� node�� ����.
		printf("\t\nthis list is empty\n");
		return;
	}
	ListNode* pLoc = pList->head_director; // ���� ��ġ�� head_director�� ����Ű�� node, �� ù ��° node
	while (++n <= pList->count) { // ���������� ��� node�� ����Ѵ�.
		printf("\t\nnum%d: %d�⿡ %s(��)�� %s(��)�� �����߽��ϴ�.\n\n", n, pLoc->year, pLoc->movie_name, pLoc->director);
		pLoc = pLoc->link_director;
	}
}

void removeList(List* pList, int year, char movie_name[], char director[]) {
	//�Էµ� ������ ����� ����� ������ �������� �Ǵ�
	ListNode* pPre[3] = { NULL }, * pLoc[3] = { NULL };
	int flag = 0; // �߸��� ���� �ִ��� Ȯ���ϱ� ���� ����
	
	bool found = _searchList_year(pList, &pPre[0], &pLoc[0], year);
	if (!found) { // �Էµ� ������ ������ noded ������
		printf("\t�Է��� �⵵�� ���� ����� �����ϴ�.\n");
		flag++; // ����� ���� ��ġ�ϴ� �����Ͱ� ������ +1
	}
	else
		printf("\t�Է��� �⵵�� ���� ����� ã�� �� �ֽ��ϴ�.\n");

	found = _searchList_movie_name(pList, &pPre[1], &pLoc[1], movie_name);
	if (!found) { // �Էµ� ������ ������ noded ������
		printf("\t�Է��� ��ȭ�̸��� ���� ����� �����ϴ�.\n");
		flag++; // ����� ���� ��ġ�ϴ� �����Ͱ� ������ +1
	}
	else
		printf("\t�Է��� ��ȭ�̸��� ���� ����� ã�� �� �ֽ��ϴ�.\n");

	found = _searchList_director(pList, &pPre[2], &pLoc[2], director);
	if (!found) { // �Էµ� ������ ������ noded ������
		printf("\t�Է��� ������ ���� ����� �����ϴ�.\n\n");
		flag++; // ����� ���� ��ġ�ϴ� �����Ͱ� ������ +1
	}
	else
		printf("\t�Է��� ������ ���� ����� ã�� �� �ֽ��ϴ�.\n\n");

	if (flag > 0)	return;

	_deleteList_year(pList, pPre[0], pLoc[0]);
	_deleteList_movie_name(pList, pPre[1], pLoc[1]);
	_deleteList_director(pList, pPre[2], pLoc[2]);

	pList->count--; // ��� �� ����
	printf("\n\t������ �����߽��ϴ�.\n");
}

void _deleteList_year(List* pList, ListNode* pPre, ListNode* pLoc) {
	// year_link �ϳ� ����
	if (pPre == NULL)// ù node ������ ��
		pList->head_year = pLoc->link_year;
	else
		pPre->link_year = pLoc->link_year;
}
void _deleteList_movie_name(List* pList, ListNode* pPre, ListNode* pLoc) {
	// year_link �ϳ� ����
	if (pPre == NULL)// ù node ������ ��
		pList->head_movie_name = pLoc->link_movie_name;
	else
		pPre->link_movie_name = pLoc->link_movie_name;
}
void _deleteList_director(List* pList, ListNode* pPre, ListNode* pLoc) {
	// year_director �ϳ� ����
	if (pPre == NULL)// ù node ������ ��
		pList->head_director = pLoc->link_director;
	else
		pPre->link_director = pLoc->link_director;
}

//����ڷκ��� �Է� ���� ������ General Linear List�� �ش� ��ġ�� ������.

//���� Test case�� �����Ͽ� ����� ÷���� ��.
//Insert a node into a null list
//Insert a node before the first data node//���� ���麸�� year�� ���� �ռ� �����͸� �Է� �޾� ������
//Insert a node between two data nodes
//Insert a node after the last node
//Delete to a null list
//delete all of the data nodes from the list
//Delete the first data node in the list
//Delete the node between two data nodes
//Delete the node at the end of the list
//Try to delete a node that does not exist
//Try to delete a node whose key is less than the first data node��s key
//Try to delete a node whose key is greater than the last data node��s key
//Try to delete from an empty list