#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
// Academy Award List application(Generic Coding 버젼)
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
			//임의의 “년도, 영화제목, 감독이름”을 사용자로부터(키보드) 입력 받아 삽입
			printf("\tyear: "); scanf("%d", &year);
			printf("\tmovie name: "); scanf("%s", movie_name);
			printf("\tdirector: "); scanf("%s", director);
			addNodeList(record, year, movie_name, director);
			break;
		case 'D'://delete a node from the list
			// 임의의  “년도, 영화제목, 감독이름”을 사용자로부터(키보드) 입력 받아 삭제
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
			printf("\n\t메뉴를 다시 확인하세요.\n");
		}
		system("pause");
		system("cls");
	}
}
List* createList() { // List 생성
	List* pNewList = (List*)malloc(sizeof(List));
	if (pNewList == NULL)
		return NULL;
	pNewList->count = 0; // node 수 0으로 초기화
	pNewList->head = NULL;

	return pNewList;
}
void _insertList(List* pList, ListNode* pPre, ListNode* pLoc, int year, char movie_name[], char director[]) {
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));//노드 생성

	// 데이터 노드에 입력
	pNewNode->year = year;
	strcpy(pNewNode->movie_name, movie_name);
	strcpy(pNewNode->director, director);

	//앞 노드와 연결
	if (pPre == NULL) //list 제일 앞에 삽입
		pList->head = pNewNode;
	else // list 중간이나 젤 뒤에 삽입
		pPre->link = pNewNode;
	// 뒤 노드와 연결
	pNewNode->link = pLoc;

	pList->count++; // 노드 수 증가
}
bool _searchList_year(List* pList, ListNode** ppPre, ListNode** ppLoc, int year) {
	for (*ppPre = NULL, *ppLoc = pList->head; *ppLoc != NULL; *ppPre = *ppLoc, *ppLoc = (*ppLoc)->link) {
		if ((*ppLoc)->year == year)// 입력한 year를 list에서 찾으면
			return true;
		else if ((*ppLoc)->year > year)
			// 현재 확인 중인 값이 찾으려는 값보다 큰 경우 이후에 찾으려는 데이터가 나올 수 없어서 찾기 종료
			// 확인 중인 값은 이전에 확인했던 값보다 항상 크다.
			break;
	}
	return false;
}
void addNodeList(List* pList, int year, char movie_name[], char director[]) {
	// list에 node 추가
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _searchList_year(pList, &pPre, &pLoc, year);
	if (!found) // 해당 year에 저장된 data가 없으므로 새로운 데이터 삽입가능
		_insertList(pList, pPre, pLoc, year, movie_name, director);
}
void searchNode_show(List* pList, int year) {
	// 입력한 year에 수상 내역 출력
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _searchList_year(pList, &pPre, &pLoc, year);
	if (found)
		printf("\t\n%d년에 %s로 %s가 수상했습니다.\n", pLoc->year, pLoc->movie_name, pLoc->director);
	else
		printf("\t\n입력한 년도의 수상내역을 찾을 수 없습니다.\n");
}

void printAll(List* pList) {
	// list에 저장된 모든 내용 출력(year 오름차순)
	int n = 0;
	if (pList->count == 0) {//list에 저장된 node가 없다.
		printf("\t\nthis list is empty\n");
		return;
	}
	ListNode* pLoc = pList->head; // 현재 위치는 head가 가리키는 node, 즉 첫 번째 node
	while (++n <= pList->count) { // 순차적으로 모든 node를 출력한다.
		printf("\t\nnum%d: %d년에 %s(으)로 %s(이)가 수상했습니다.\n\n", n, pLoc->year, pLoc->movie_name, pLoc->director);
		pLoc = pLoc->link;
	}
}

void removeList(List* pList, int year, char movie_name[], char director[]) {
	// node 하나 삭제
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _searchList_year(pList, &pPre, &pLoc, year);

	if (found) // 입력된 정보와 동일한 node있으면 삭제
		_deleteList(pList, pPre, pLoc, movie_name, director);
	else
		printf("\tthe node does not exist\n");
}

void _deleteList(List* pList, ListNode* pPre, ListNode* pLoc, char movie_name[], char director[]) {
	// 입력된 정보가 저장된 노드의 정보와 동일한지 판단하고
	// node 하나 삭제
	if (strcmp(pLoc->movie_name, movie_name) || strcmp(pLoc->director, director) != 0) {
		// 입력된 정보가 저장된 정보와 같은지 확인
		printf("\t영화 제목이나 감독이 다릅니다.\n");
		return;
	}
	
	if (pPre == NULL) // 첫 node 삭제할 때
		pList->head = pLoc->link;
	else
		pPre->link = pLoc->link;
	free(pLoc);
	pList->count--; // 노드 수 감소
	printf("\t삭제를 성공했습니다.\n");
}

//사용자로부터 입력 받은 내용은 General Linear List의 해당 위치에 삽입함.
//리스트는 year key로 정렬되어 있도록 설계하라.

//다음 Test case를 실행하여 결과를 첨부할 것.
//Insert a node into a null list
//Insert a node before the first data node//기존 노드들보다 year가 가장 앞선 데이터를 입력 받아 삽입함
//Insert a node between two data nodes
//Insert a node after the last node
//Delete to a null list
//delete all of the data nodes from the list
//Delete the first data node in the list
//Delete the node between two data nodes
//Delete the node at the end of the list
//Try to delete a node that does not exist
//Try to delete a node whose key is less than the first data node’s key
//Try to delete a node whose key is greater than the last data node’s key
//Try to delete from an empty list