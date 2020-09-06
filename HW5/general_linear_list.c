#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
// Academy Award List application(Generic Coding ����)
// linear list
typedef struct tListNode {
	int year;
	char movie_name[100];
	char director[50];
	struct tListNode* link;
}ListNode;
typedef struct {
	int count;
	ListNode* head;
}List;

List* createList();
void _insertList(List* pList, ListNode* pPre, ListNode* pLoc, int year, char movie_name[], char director[]);
bool _searchList_year(List* pList, ListNode** ppPre, ListNode** ppLoc, int year);
void addNodeList(List* pList, int year, char movie_name[], char director[]);
void searchNode_show(List* pList, int year);
void addNodeList(List* pList, int year, char movie_name[], char director[]);
void searchNode_show(List* pList, int year);
void printAll(List* pList);
void removeList(List* pList, int year, char movie_name[], char director[]);
void _deleteList(List* pList, ListNode* pPre, ListNode* pLoc, char movie_name[], char director[]);

int main() {
	char menu;
	int year; char movie_name[50], director[20]; // to get three data from user
	List* record = createList();
	while (1) {
		printf("===========menu=========\n"
			"P : print all list of awarded prictures\n"
			"S : search for a year\n"
			"I : insert a node to the list\n"
			"D : delete a node from the list\n"
			"Q : quit\n"
			">>>"); scanf("%c", &menu);
		switch (menu) {
		case 'P':
			//print all list of awarded pictures
			printAll(record);
			break;
		case 'S': 
			// search for a year
			printf("\tyear: "); scanf("%d", &year);
			searchNode_show(record, year);
			break;
		case 'I':
			// insert a node to the list
			//������ ���⵵, ��ȭ����, �����̸����� ����ڷκ���(Ű����) �Է� �޾� ����
			printf("\tyear: "); scanf("%d", &year);
			printf("\tmovie name: "); scanf("%s", movie_name);
			printf("\tdirector: "); scanf("%s", director);
			addNodeList(record, year, movie_name, director);
			break;
		case 'D'://delete a node from the list
			// ������  ���⵵, ��ȭ����, �����̸����� ����ڷκ���(Ű����) �Է� �޾� ����
			if (record->head == NULL) {
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
}
List* createList() { // List ����
	List* pNewList = (List*)malloc(sizeof(List));
	if (pNewList == NULL)
		return NULL;
	pNewList->count = 0; // node �� 0���� �ʱ�ȭ
	pNewList->head = NULL;

	return pNewList;
}
void _insertList(List* pList, ListNode* pPre, ListNode* pLoc, int year, char movie_name[], char director[]) {
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));//��� ����

	// ������ ��忡 �Է�
	pNewNode->year = year;
	strcpy(pNewNode->movie_name, movie_name);
	strcpy(pNewNode->director, director);

	//�� ���� ����
	if (pPre == NULL) //list ���� �տ� ����
		pList->head = pNewNode;
	else // list �߰��̳� �� �ڿ� ����
		pPre->link = pNewNode;
	// �� ���� ����
	pNewNode->link = pLoc;

	pList->count++; // ��� �� ����
}
bool _searchList_year(List* pList, ListNode** ppPre, ListNode** ppLoc, int year) {
	for (*ppPre = NULL, *ppLoc = pList->head; *ppLoc != NULL; *ppPre = *ppLoc, *ppLoc = (*ppLoc)->link) {
		if ((*ppLoc)->year == year)// �Է��� year�� list���� ã����
			return true;
		else if ((*ppLoc)->year > year)
			// ���� Ȯ�� ���� ���� ã������ ������ ū ��� ���Ŀ� ã������ �����Ͱ� ���� �� ��� ã�� ����
			// Ȯ�� ���� ���� ������ Ȯ���ߴ� ������ �׻� ũ��.
			break;
	}
	return false;
}
void addNodeList(List* pList, int year, char movie_name[], char director[]) {
	// list�� node �߰�
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _searchList_year(pList, &pPre, &pLoc, year);
	if (!found) // �ش� year�� ����� data�� �����Ƿ� ���ο� ������ ���԰���
		_insertList(pList, pPre, pLoc, year, movie_name, director);
}
void searchNode_show(List* pList, int year) {
	// �Է��� year�� ���� ���� ���
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _searchList_year(pList, &pPre, &pLoc, year);
	if (found)
		printf("\t\n%d�⿡ %s�� %s�� �����߽��ϴ�.\n", pLoc->year, pLoc->movie_name, pLoc->director);
	else
		printf("\t\n�Է��� �⵵�� ���󳻿��� ã�� �� �����ϴ�.\n");
}

void printAll(List* pList) {
	// list�� ����� ��� ���� ���(year ��������)
	int n = 0;
	if (pList->count == 0) {//list�� ����� node�� ����.
		printf("\t\nthis list is empty\n");
		return;
	}
	ListNode* pLoc = pList->head; // ���� ��ġ�� head�� ����Ű�� node, �� ù ��° node
	while (++n <= pList->count) { // ���������� ��� node�� ����Ѵ�.
		printf("\t\nnum%d: %d�⿡ %s(��)�� %s(��)�� �����߽��ϴ�.\n\n", n, pLoc->year, pLoc->movie_name, pLoc->director);
		pLoc = pLoc->link;
	}
}

void removeList(List* pList, int year, char movie_name[], char director[]) {
	// node �ϳ� ����
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _searchList_year(pList, &pPre, &pLoc, year);

	if (found) // �Էµ� ������ ������ node������ ����
		_deleteList(pList, pPre, pLoc, movie_name, director);
	else
		printf("\tthe node does not exist\n");
}

void _deleteList(List* pList, ListNode* pPre, ListNode* pLoc, char movie_name[], char director[]) {
	// �Էµ� ������ ����� ����� ������ �������� �Ǵ��ϰ�
	// node �ϳ� ����
	if (strcmp(pLoc->movie_name, movie_name) || strcmp(pLoc->director, director) != 0) {
		// �Էµ� ������ ����� ������ ������ Ȯ��
		printf("\t��ȭ �����̳� ������ �ٸ��ϴ�.\n");
		return;
	}
	
	if (pPre == NULL) // ù node ������ ��
		pList->head = pLoc->link;
	else
		pPre->link = pLoc->link;
	free(pLoc);
	pList->count--; // ��� �� ����
	printf("\t������ �����߽��ϴ�.\n");
}

//����ڷκ��� �Է� ���� ������ General Linear List�� �ش� ��ġ�� ������.
//����Ʈ�� year key�� ���ĵǾ� �ֵ��� �����϶�.

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