#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
// Academy Award List application(Generic Coding 버젼)
// General Linear List를 Multilinked List로 구현하여 제출한 경우는 Extra Point를 부여함
// 단, link는 Year와 영화제목의 알파벳/가나다 순서 등 2개로 설정함. 또한 아래 Test Case에 대한 해석이 약간 수정되어야 함.
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

// 함수 원형 선언
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
			printf("\n\n=========년도 오름차순으로 전체 출력==========\n");
			printAll_year(record);

			printf("\n\n=========영화 이름 알파벳순으로 전체 출력==========\n");
			printAll_movie_name(record);

			printf("\n\n=========감독 알페벳순으로 전체 출력==========\n\n");
			printAll_director(record);
			break;
		case 'S':
			if (record->head_year == NULL) {
				printf("\tthis list is empty\n");
				break;
			}
			printf("\n\n=========년도로 검색==========\n");
			printf("\tyear: "); scanf("%d", &year);
			searchNode_show_year(record, year);
			
			printf("\n\n=========영화 이름으로 검색==========\n");
			printf("\tmovie_name: "); scanf("%d", movie_name);
			searchNode_show_movie_name(record, movie_name);
			
			break;
		case 'I':
			// insert a node to the list
			//임의의 “년도, 영화제목, 감독이름”을 사용자로부터(키보드) 입력 받아 삽입
			printf("\tyear: "); scanf("%d", &year);
			printf("\tmovie name: "); scanf("%s", movie_name);
			printf("\tdirector: "); scanf("%s", director);
			addNodeList(record, year, movie_name, director);
			break;
		case 'D':
			//delete a node from the list using link
			// 임의의  “년도, 영화제목, 감독이름”을 사용자로부터(키보드) 입력 받아 삭제
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
			printf("\n\t메뉴를 다시 확인하세요.\n");
		}
		system("pause");
		system("cls");
	}
}// main 끝

List* createList() {
	// List 생성
	List* pNewList = (List*)malloc(sizeof(List));
	if (pNewList == NULL)
		return NULL;
	pNewList->count = 0; // node 수 0으로 초기화
	pNewList->head_year = NULL;
	pNewList->head_movie_name = NULL;
	pNewList->head_director = NULL;

	return pNewList;
}

void _insertList(List* pList, ListNode* pPre[], ListNode* pLoc[], int year, char movie_name[], char director[]) {
	// list에 node 삽입

	// pPre[0], pLoc[0] => year(년도 오름차순)
	// pPre[1], pLoc[1] => movie_name(알파벳순)
	// pPre[2], pLoc[2] => director(알파벳순)

	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));//노드 생성

	// 데이터 노드에 입력
	pNewNode->year = year;
	strcpy(pNewNode->movie_name, movie_name);
	strcpy(pNewNode->director, director);

	//앞 노드와 연결
	if (pPre[0] == NULL) {
		//list 제일 앞에 삽입
		pList->head_year = pNewNode;
	}
	else {
		// list 중간이나 젤 뒤에 삽입
		pPre[0]->link_year = pNewNode;
	}

	if (pPre[1] == NULL) {
		//list 제일 앞에 삽입
		pList->head_movie_name = pNewNode;
	}
	else {
		// list 중간이나 젤 뒤에 삽입
		pPre[1]->link_movie_name = pNewNode;
	}

	if (pPre[1] == NULL) {
		//list 제일 앞에 삽입
		pList->head_director = pNewNode;
	}
	else {
		// list 중간이나 젤 뒤에 삽입
		pPre[2]->link_director = pNewNode;
	}

	// 뒤 노드와 연결
	pNewNode->link_year = pLoc[0];
	pNewNode->link_movie_name = pLoc[1];
	pNewNode->link_director = pLoc[2];

	pList->count++; // 노드 수 증가
}

bool _searchList_year(List* pList, ListNode** ppPre, ListNode** ppLoc, int year) {
	// link_year를 이용해서 알파벳순으로 검사 진행
	// 입력 받은 year가 존재하는지 검사
	for (*ppPre = NULL, *ppLoc = pList->head_year; *ppLoc != NULL; *ppPre = *ppLoc, *ppLoc = (*ppLoc)->link_year) {
		if ((*ppLoc)->year == year)// 입력한 year를 list에서 찾으면
			return true;
		else if ((*ppLoc)->year > year)
			// 현재 확인 중인 값이 찾으려는 값보다 큰 경우 이후에 찾으려는 데이터가 나올 수 없어서 찾기 종료
			// 확인 중인 값은 이전에 확인했던 값보다 항상 크다.
			break;
	}
	return false;
}

bool _searchList_movie_name(List* pList, ListNode** ppPre, ListNode** ppLoc, char movie_name[]) {
	// link_movie_name을 이용해서 알파벳순으로 검사 진행
	// 입력 받은 movie_name이 존재하는지 검사
	for (*ppPre = NULL, *ppLoc = pList->head_movie_name; *ppLoc != NULL; *ppPre = *ppLoc, *ppLoc = (*ppLoc)->link_movie_name) {
		if (strcmp((*ppLoc)->movie_name, movie_name) == 0)// 입력한 movie_name을 list에서 찾으면
			return true;
		else if (strcmp((*ppLoc)->movie_name, movie_name) > 0)
			// 문자열은 아스키코드를 이용해서 알파벳 순으로 배열
			// strcmp("aab","aaa") > 0
			// strcmp("aab","aac") < 0
			// 현재 확인 중인 값이 찾으려는 값보다 큰 경우 이후에 찾으려는 데이터가 나올 수 없어서 찾기 종료
			// 확인 중인 값은 이전에 확인했던 값보다 항상 크다.
			break;
	}
	return false;
}

bool _searchList_director(List* pList, ListNode** ppPre, ListNode** ppLoc, char director[]) {
	// link_director을 이용해서 알파벳순으로 검사 진행
	// 입력 받은 director가 존재하는지 검사
	for (*ppPre = NULL, *ppLoc = pList->head_director; *ppLoc != NULL; *ppPre = *ppLoc, *ppLoc = (*ppLoc)->link_director) {
		if (strcmp((*ppLoc)->director, director) == 0)// 입력한 movie_name을 list에서 찾으면
			return true;
		else if (strcmp((*ppLoc)->director, director) > 0)
			// 문자열은 아스키코드를 이용해서 알파벳 순으로 배열
			// strcmp("aab","aaa") > 0
			// strcmp("aab","aac") < 0
			// 현재 확인 중인 값이 찾으려는 값보다 큰 경우 이후에 찾으려는 데이터가 나올 수 없어서 찾기 종료
			// 확인 중인 값은 이전에 확인했던 값보다 항상 크다.
			break;
	}
	return false;
}

void addNodeList(List* pList, int year, char movie_name[], char director[]) { 
	// list에 node 추가
	//동일한 내용을 가진 데이터 저장 불가
	ListNode* pPre[3] = { NULL }, * pLoc[3] = { NULL };
	// pPre[0], pLoc[0] => year(년도 오름차순)
	// pPre[1], pLoc[1] => movie_name(알파벳순)
	// pPre[2], pLoc[2] => director(알파벳순)
	bool found = _searchList_year(pList, &pPre[0], &pLoc[0], year);
	if (found) // 데이터 삽입 불가(year 동일)
		return;
	found = _searchList_movie_name(pList, &pPre[1], &pLoc[1], movie_name);
	if (found) // 데이터 삽입 불가(movie_name 동일)
		return;
	found = _searchList_director(pList, &pPre[2], &pLoc[2], director);
	if (!found) // 새로운 데이터 삽입가능
		_insertList(pList, pPre, pLoc, year, movie_name, director);
}

void searchNode_show_year(List* pList, int year) {
	// 입력한 year때의 수상 내역 출력
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _searchList_year(pList, &pPre, &pLoc, year);
	if (found)
		printf("\t\n%d년에 %s로 %s가 수상했습니다.\n", pLoc->year, pLoc->movie_name, pLoc->director);
	else
		printf("\t\n입력한 년도의 수상내역을 찾을 수 없습니다.\n");
}

void searchNode_show_movie_name(List* pList, char movie_name[]) {
	// 입력한 movie_name의 수상 내역 출력
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _searchList_movie_name(pList, &pPre, &pLoc, movie_name);
	if (found)
		printf("\t\n%d년에 %s로 %s가 수상했습니다.\n", pLoc->year, pLoc->movie_name, pLoc->director);
	else
		printf("\t\n입력한 영화 이름의 수상내역을 찾을 수 없습니다.\n");
}

void searchNode_show_director(List* pList, char director[]) {
	// 입력한 director의 수상 내역 출력
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _searchList_director(pList, &pPre, &pLoc, director);
	if (found)
		printf("\t\n%d년에 %s로 %s가 수상했습니다.\n", pLoc->year, pLoc->movie_name, pLoc->director);
	else
		printf("\t\n입력한 감독의 수상내역을 찾을 수 없습니다.\n");
}

void printAll_year(List* pList) {
	// list에 저장된 모든 내용 출력(year 오름차순)
	int n = 0;
	if (pList->count == 0) {//list에 저장된 node가 없다.
		printf("\t\nthis list is empty\n");
		return;
	}
	ListNode* pLoc = pList->head_year; // 현재 위치는 head_year가 가리키는 node, 즉 첫 번째 node
	while (++n <= pList->count) { // 순차적으로 모든 node를 출력한다.
		printf("\t\nnum%d: %d년에 %s(으)로 %s(이)가 수상했습니다.\n\n", n, pLoc->year, pLoc->movie_name, pLoc->director);
		pLoc = pLoc->link_year;
	}
}

void printAll_movie_name(List* pList) {
	// list에 저장된 모든 내용 출력(movie_name 알파벳순)
	int n = 0;
	if (pList->count == 0) {//list에 저장된 node가 없다.
		printf("\t\nthis list is empty\n");
		return;
	}
	ListNode* pLoc = pList->head_movie_name; // 현재 위치는 head_movie_name가 가리키는 node, 즉 첫 번째 node
	while (++n <= pList->count) { // 순차적으로 모든 node를 출력한다.
		printf("\t\nnum%d: %d년에 %s(으)로 %s(이)가 수상했습니다.\n\n", n, pLoc->year, pLoc->movie_name, pLoc->director);
		pLoc = pLoc->link_movie_name;
	}
}

void printAll_director(List* pList) {
	// list에 저장된 모든 내용 출력(director 알파벳순)
	int n = 0;
	if (pList->count == 0) {//list에 저장된 node가 없다.
		printf("\t\nthis list is empty\n");
		return;
	}
	ListNode* pLoc = pList->head_director; // 현재 위치는 head_director가 가리키는 node, 즉 첫 번째 node
	while (++n <= pList->count) { // 순차적으로 모든 node를 출력한다.
		printf("\t\nnum%d: %d년에 %s(으)로 %s(이)가 수상했습니다.\n\n", n, pLoc->year, pLoc->movie_name, pLoc->director);
		pLoc = pLoc->link_director;
	}
}

void removeList(List* pList, int year, char movie_name[], char director[]) {
	//입력된 정보가 저장된 노드의 정보와 동일한지 판단
	ListNode* pPre[3] = { NULL }, * pLoc[3] = { NULL };
	int flag = 0; // 잘못된 정보 있는지 확인하기 위한 변수
	
	bool found = _searchList_year(pList, &pPre[0], &pLoc[0], year);
	if (!found) { // 입력된 정보와 동일한 noded 없으면
		printf("\t입력한 년도를 가진 기록이 없습니다.\n");
		flag++; // 저장된 정보 일치하는 데이터가 없으면 +1
	}
	else
		printf("\t입력한 년도를 가진 기록을 찾을 수 있습니다.\n");

	found = _searchList_movie_name(pList, &pPre[1], &pLoc[1], movie_name);
	if (!found) { // 입력된 정보와 동일한 noded 없으면
		printf("\t입력한 영화이름을 가진 기록이 없습니다.\n");
		flag++; // 저장된 정보 일치하는 데이터가 없으면 +1
	}
	else
		printf("\t입력한 영화이름을 가진 기록을 찾을 수 있습니다.\n");

	found = _searchList_director(pList, &pPre[2], &pLoc[2], director);
	if (!found) { // 입력된 정보와 동일한 noded 없으면
		printf("\t입력한 감독이 가진 기록이 없습니다.\n\n");
		flag++; // 저장된 정보 일치하는 데이터가 없으면 +1
	}
	else
		printf("\t입력한 감독이 가진 기록을 찾을 수 있습니다.\n\n");

	if (flag > 0)	return;

	_deleteList_year(pList, pPre[0], pLoc[0]);
	_deleteList_movie_name(pList, pPre[1], pLoc[1]);
	_deleteList_director(pList, pPre[2], pLoc[2]);

	pList->count--; // 노드 수 감소
	printf("\n\t삭제를 성공했습니다.\n");
}

void _deleteList_year(List* pList, ListNode* pPre, ListNode* pLoc) {
	// year_link 하나 삭제
	if (pPre == NULL)// 첫 node 삭제할 때
		pList->head_year = pLoc->link_year;
	else
		pPre->link_year = pLoc->link_year;
}
void _deleteList_movie_name(List* pList, ListNode* pPre, ListNode* pLoc) {
	// year_link 하나 삭제
	if (pPre == NULL)// 첫 node 삭제할 때
		pList->head_movie_name = pLoc->link_movie_name;
	else
		pPre->link_movie_name = pLoc->link_movie_name;
}
void _deleteList_director(List* pList, ListNode* pPre, ListNode* pLoc) {
	// year_director 하나 삭제
	if (pPre == NULL)// 첫 node 삭제할 때
		pList->head_director = pLoc->link_director;
	else
		pPre->link_director = pLoc->link_director;
}

//사용자로부터 입력 받은 내용은 General Linear List의 해당 위치에 삽입함.

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