// heap_ADT_select Kth element
#include<stdio.h>
#include<math.h> // pow �Լ�(ũ�� ���� -> ����)
#include<stdbool.h> // bool datatype
#include<string.h>

// head node ����ü
typedef struct {
	void** heapAry;
	int last; // index of last element
	int size;
	int (*compare)(void* arg1, void* arg2);
	int maxSize;
}HEAP;

// datatype �� compare �Լ�
// ���� �����Ͱ� �� ũ�� ���, ������ �����Ͱ� �� ũ�� ������ ��ȯ
// ���ڴ� �ƽ�Ű�ڵ� ��, ���ڴ� �� ��
int compareChar(char* arg1, char* arg2) {
	return strcmp(arg1, arg2);
}
int compareInt(int* arg1, int* arg2) {
	return (*arg1) - (*arg2);
}

// create heap
HEAP* heapCreate(int maxSize, int (*compare)(void* arg1, void* arg2)) {
	HEAP* heap = (HEAP*)malloc(sizeof(HEAP));
	if (!heap) // heap ���� �Ҵ� ���� �Ǵ�
		return NULL;

	heap->last = -1; // empty heap
	heap->size = 0;

	heap->compare = compare;
	heap->maxSize = (int)pow(2, ceil(log2(maxSize))) - 1;
	// �ִ� ũ��� 2^n-1 => fully binary tree
	heap->heapAry = (void**)calloc(heap->maxSize, sizeof(void*));

	return heap;
}

// reheap Up
// heapAry �迭���� childLoc�� indev�� ������ �����Ͱ� oreder property�� ���� �� �� �ֵ��� ����
void _reheapUp(HEAP* heap, int childLoc) {
	int parent = 0;
	void** heapAry = NULL;
	void* hold = NULL;

	if (childLoc) { // root(heapAry�� index = 0) �ƴϸ� -> base case
		heapAry = heap->heapAry;
		parent = (childLoc - 1) / 2;
		if (heap->compare(heapAry[childLoc], heapAry[parent]) > 0) {
			// parent�� ���ؼ� childLoc�� �� ũ�� �ڸ� �ٲ�
			// parent ���� ������ ��ȯ -> ��� Ż��(base case)
			hold = heapAry[parent];
			heapAry[parent] = heapAry[childLoc];
			heapAry[childLoc] = hold;

			_reheapUp(heap, parent);
			// �ٲ� ��ġ�� order property�� �����ϴ��� üũ�Ϸ� ����Լ� ȣ��
		}
	}
	return;
}

// insert heap
// dataPtr�� heapAry�� �ִ´�.
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
	// left child ������ return
	if ((root * 2 + 1) <= last) { // lest subtree
		// ��� �ϳ��� child ����
		leftData = heap->heapAry[root * 2 + 1];
		if ((root * 2 + 2) <= last) // right subtree
			rightData = heap->heapAry[root * 2 + 2];
		else
			rightData = NULL;

		// � child�� �� ū�� ��
		if (!rightData || heap->compare(leftData, rightData) > 0)
			largeLoc = root * 2 + 1;
		else
			largeLoc = root * 2 + 2;

		// largeLoc(�¿� subtree �� �� ū child)�� root���� ū��?
		if (heap->compare(heap->heapAry[root], heap->heapAry[largeLoc]) < 0) {
			// root�� �� �۴ٸ�
			hold = heap->heapAry[root];
			heap->heapAry[root] = heap->heapAry[largeLoc];
			heap->heapAry[largeLoc] = hold;

			_reheapDown(heap, largeLoc);
		}
	}

	return;
}

// Delete heap
// ������ �׻� root���� �Ͼ��.
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

// kth element�� ã�´�.
void* selectK(HEAP* heap, int k) {
	void* holdOut; // kth element ������ ����
	if (k > heap->size)	return NULL;

	int origHeap_size = heap->size; // ���� heap size ����

	while (--k) { // k-1 �� �ݺ�
		// heap�� �����ϴ� �迭���� ���� ū ���� �� �迭 ���� �ڷ� �ű��.
		// �� �� ���� ���ʷ� �̵��� �����Ͱ� ����Ǿ��ִ�.

		void* tempData = heap->heapAry[0];
		heapDelete(heap, &tempData); // root ����
		// ���� �Ŀ��� last index�� size�� �ϳ� �پ�� ����

		heap->heapAry[heap->last + 1] = tempData; // heap �� �ڿ� root�ֱ�
		// heap�� �ִ� total data�� �״�� ������
		// ��ġ, last�� size ���� �̷��� ����
	}
	// loop ���� �� kth element �� root�� ��ġ�ϰ� ��
	holdOut = heap->heapAry[0];

	// Reconstruct heap
	// �迭�� heap order property�� �������� ���ϴ� data�� k-1�� ����
	while (heap->last < origHeap_size - 1) {
		// heap �������� ���ϴ� element�� last �ں��� ����
			(heap->last)++;
			(heap->size)++;
		_reheapUp(heap, heap->last);
	}

	return holdOut;
}

int main() {
	int maxSize = 10;
	HEAP* test_char = NULL;

	// ������ ��
	test_char = heapCreate(maxSize, compareChar);

	for (int i = 0; i < 5; i++) {
		char* tmpchar = (char*)malloc(sizeof(char));
		printf("%d��° input(char):",i+1); scanf("%s", tmpchar);
		heapInsert(test_char, tmpchar);
	}

	printf("1��° ���ڴ� %s\n", (char*)selectK(test_char, 1));
	printf("2��° ���ڴ� %s\n", (char*)selectK(test_char, 2));
	printf("3��° ���ڴ� %s\n", (char*)selectK(test_char, 3));
	printf("4��° ���ڴ� %s\n", (char*)selectK(test_char, 4));
	printf("5��° ���ڴ� %s\n", (char*)selectK(test_char, 5));

	// ������ ��
	printf("\n======================\n");
	HEAP* test_int = heapCreate(maxSize, compareInt);

	for (int i = 0; i < 5; i++) {
		int* tmpint = (int*)malloc(sizeof(int));
		int tmp;
		printf("%d��° input(int):",i+1); scanf("%d", &(*tmpint));
		heapInsert(test_int, tmpint);
	}

	printf("1��° ���ڴ� %d\n", *(int*)selectK(test_int, 1));
	printf("2��° ���ڴ� %d\n", *(int*)selectK(test_int, 2));
	printf("3��° ���ڴ� %d\n", *(int*)selectK(test_int, 3));
	printf("4��° ���ڴ� %d\n", *(int*)selectK(test_int, 4));
	printf("5��° ���ڴ� %d\n", *(int*)selectK(test_int, 5));
}