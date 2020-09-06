// heap_ADT_select Kth element
#include<stdio.h>
#include<math.h> // pow 함수(크기 설정 -> 제곱)
#include<stdbool.h> // bool datatype
#include<string.h>

// head node 구조체
typedef struct {
	void** heapAry;
	int last; // index of last element
	int size;
	int (*compare)(void* arg1, void* arg2);
	int maxSize;
}HEAP;

// datatype 별 compare 함수
// 왼쪽 데이터가 더 크면 양수, 오른쪽 데이터가 더 크면 음수를 반환
// 문자는 아스키코드 비교, 숫자는 수 비교
int compareChar(char* arg1, char* arg2) {
	return strcmp(arg1, arg2);
}
int compareInt(int* arg1, int* arg2) {
	return (*arg1) - (*arg2);
}

// create heap
HEAP* heapCreate(int maxSize, int (*compare)(void* arg1, void* arg2)) {
	HEAP* heap = (HEAP*)malloc(sizeof(HEAP));
	if (!heap) // heap 공간 할당 실패 판단
		return NULL;

	heap->last = -1; // empty heap
	heap->size = 0;

	heap->compare = compare;
	heap->maxSize = (int)pow(2, ceil(log2(maxSize))) - 1;
	// 최대 크기는 2^n-1 => fully binary tree
	heap->heapAry = (void**)calloc(heap->maxSize, sizeof(void*));

	return heap;
}

// reheap Up
// heapAry 배열에서 childLoc를 indev로 가지는 데이터가 oreder property를 만족 할 수 있도록 정렬
void _reheapUp(HEAP* heap, int childLoc) {
	int parent = 0;
	void** heapAry = NULL;
	void* hold = NULL;

	if (childLoc) { // root(heapAry의 index = 0) 아니면 -> base case
		heapAry = heap->heapAry;
		parent = (childLoc - 1) / 2;
		if (heap->compare(heapAry[childLoc], heapAry[parent]) > 0) {
			// parent와 비교해서 childLoc이 더 크면 자리 바꿈
			// parent 보다 작으면 반환 -> 재귀 탈출(base case)
			hold = heapAry[parent];
			heapAry[parent] = heapAry[childLoc];
			heapAry[childLoc] = hold;

			_reheapUp(heap, parent);
			// 바뀐 위치가 order property를 만족하는지 체크하러 재귀함수 호출
		}
	}
	return;
}

// insert heap
// dataPtr을 heapAry에 넣는다.
bool heapInsert(HEAP* heap, void* dataPtr) {
	if (heap->size >= heap->maxSize)
		return false;

	++(heap->last);
	++(heap->size);
	heap->heapAry[heap->last] = dataPtr; // shape property
	_reheapUp(heap, heap->last); // oreder property
	
	return true;
}

// Reheap Down
void _reheapDown(HEAP* heap, int root) {
	void* hold = NULL;
	void* leftData = NULL;
	void* rightData = NULL;
	int largeLoc = 0;
	int last = 0;

	last = heap->last;
	// left child 없으면 return
	if ((root * 2 + 1) <= last) { // lest subtree
		// 적어도 하나의 child 존재
		leftData = heap->heapAry[root * 2 + 1];
		if ((root * 2 + 2) <= last) // right subtree
			rightData = heap->heapAry[root * 2 + 2];
		else
			rightData = NULL;

		// 어떤 child가 더 큰지 비교
		if (!rightData || heap->compare(leftData, rightData) > 0)
			largeLoc = root * 2 + 1;
		else
			largeLoc = root * 2 + 2;

		// largeLoc(좌우 subtree 중 더 큰 child)가 root보다 큰가?
		if (heap->compare(heap->heapAry[root], heap->heapAry[largeLoc]) < 0) {
			// root가 더 작다면
			hold = heap->heapAry[root];
			heap->heapAry[root] = heap->heapAry[largeLoc];
			heap->heapAry[largeLoc] = hold;

			_reheapDown(heap, largeLoc);
		}
	}

	return;
}

// Delete heap
// 삭제는 항상 root에서 일어난다.
bool heapDelete(HEAP* heap, void** dataOutPtr) {
	if (heap->size == 0)
		return false; //empty heap

	*dataOutPtr = heap->heapAry[0];
	heap->heapAry[0] = heap->heapAry[heap->last]; // shape
	(heap->last)--;
	(heap->size)--;
	_reheapDown(heap, 0); // order

	return true;
}

// kth element를 찾는다.
void* selectK(HEAP* heap, int k) {
	void* holdOut; // kth element 저장할 예정
	if (k > heap->size)	return NULL;

	int origHeap_size = heap->size; // 원래 heap size 저장

	while (--k) { // k-1 번 반복
		// heap을 만족하는 배열에서 제일 큰 값을 그 배열 제일 뒤로 옮긴다.
		// 맨 뒤 부터 차례로 이동한 데이터가 저장되어있다.

		void* tempData = heap->heapAry[0];
		heapDelete(heap, &tempData); // root 삭제
		// 삭제 후에는 last index와 size가 하나 줄어든 상태

		heap->heapAry[heap->last + 1] = tempData; // heap 젤 뒤에 root넣기
		// heap에 있는 total data는 그대로 유지됨
		// 위치, last와 size 변경 이뤄진 상태
	}
	// loop 종료 후 kth element 는 root에 위치하게 됨
	holdOut = heap->heapAry[0];

	// Reconstruct heap
	// 배열에 heap order property를 만족하지 못하는 data가 k-1개 존재
	while (heap->last < origHeap_size - 1) {
		// heap 만족하지 못하는 element는 last 뒤부터 존재
			(heap->last)++;
			(heap->size)++;
		_reheapUp(heap, heap->last);
	}

	return holdOut;
}

int main() {
	int maxSize = 10;
	HEAP* test_char = NULL;

	// 문자일 때
	test_char = heapCreate(maxSize, compareChar);

	for (int i = 0; i < 5; i++) {
		char* tmpchar = (char*)malloc(sizeof(char));
		printf("%d번째 input(char):",i+1); scanf("%s", tmpchar);
		heapInsert(test_char, tmpchar);
	}

	printf("1번째 문자는 %s\n", (char*)selectK(test_char, 1));
	printf("2번째 문자는 %s\n", (char*)selectK(test_char, 2));
	printf("3번째 문자는 %s\n", (char*)selectK(test_char, 3));
	printf("4번째 문자는 %s\n", (char*)selectK(test_char, 4));
	printf("5번째 문자는 %s\n", (char*)selectK(test_char, 5));

	// 숫자일 때
	printf("\n======================\n");
	HEAP* test_int = heapCreate(maxSize, compareInt);

	for (int i = 0; i < 5; i++) {
		int* tmpint = (int*)malloc(sizeof(int));
		int tmp;
		printf("%d번째 input(int):",i+1); scanf("%d", &(*tmpint));
		heapInsert(test_int, tmpint);
	}

	printf("1번째 숫자는 %d\n", *(int*)selectK(test_int, 1));
	printf("2번째 숫자는 %d\n", *(int*)selectK(test_int, 2));
	printf("3번째 숫자는 %d\n", *(int*)selectK(test_int, 3));
	printf("4번째 숫자는 %d\n", *(int*)selectK(test_int, 4));
	printf("5번째 숫자는 %d\n", *(int*)selectK(test_int, 5));
}