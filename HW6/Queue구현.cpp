// Queue ADT C++로 구현
#include<iostream>
using namespace std;

template<typename T>
class QueueList;

// QueueNOde 시작
template<typename T>
class QueueNode {
	friend QueueList<T>; // QueueList가 QueueNode 사용 가능
private:
	T data;
	QueueNode* next;
public:
	QueueNode(const T); // 생성자 = createNode
};

template<typename T>
QueueNode<T>::QueueNode(const T data) { // 생성자 정의
	this->data = data;
	next = NULL;
}
//QueueNode 끝

template<typename T>
class QueueList { // head node
private:
	QueueNode<T>* head, * rear;
	int count; // element 수
public:
	QueueList(); //생성자 = createqueue
	void enqueue(const T);
	void dequeue();
	void ShowAll();
};

//QueueList 함수 정의 시작
template<typename T>
QueueList<T>::QueueList():count(0) {
	//생성자 = createqueue
	head = rear = NULL;
}

template<typename T>
void QueueList<T>::enqueue(const T data) {
	QueueNode<T>* tmpNode = new QueueNode<T>(data);
	if (count == 0) {
		// queue 처음으로 생성했을 때
		head = tmpNode;
		rear = tmpNode;
	}
	else {
		// 생성 되어있는 queue에 node 추가
		// front는 변동 없음
		rear->next = tmpNode;
		rear = tmpNode;
	}
	// queue에서의 node 수 증가
	count++;
}

template<typename T>
void QueueList<T>::dequeue() {
	if (head == NULL) {
		cout << "empty queue(dequeue)" << endl;
		return;
	}
	// queue의 제일 앞에 있는 node가 삭제됨
	QueueNode<T>* tmpNode = head;
	head = head->next;
	delete tmpNode;
	count--;
}

template<typename T>
void QueueList<T>::ShowAll() {
	// queue의 node들 전체 출력
	QueueNode<T>* tmphead = head;
	if (tmphead == NULL) {
		cout << "empty queue(ShowAll)" << endl;
		return;
	}
	cout << "[front]-";
	while (tmphead) {
		cout << tmphead->data<<'-';
		tmphead = tmphead->next;
	}
	cout << "[rear]" << endl;
}
//QueueList 함수 정의 끝

int main() {
	QueueList<int> test;

	test.ShowAll();// empty queue 출력
	cout << "=====================" << endl;
	// data를 queue에 추가(2->4->8)
	test.enqueue(2);
	test.ShowAll();
	cout << "=====================" << endl;
	test.enqueue(4);
	test.ShowAll();
	cout << "=====================" << endl;
	test.enqueue(6);
	test.ShowAll();
	cout << "=====================" << endl;
	// 2를 dequeue
	test.dequeue();
	test.ShowAll();
	cout << "=====================" << endl;
	// 4를 dequeue
	test.dequeue();
	test.ShowAll();
	cout << "=====================" << endl;
	// data를 queue에 추가(8)
	test.enqueue(8);
	test.ShowAll();
	cout << "=====================" << endl;
	// 6를 dequeue
	test.dequeue();
	test.ShowAll();
	cout << "=====================" << endl;
	// 8를 dequeue
	test.dequeue();
	test.ShowAll();
	cout << "=====================" << endl;
	// empty queue에서 dequeue시도
	test.dequeue();
	test.ShowAll();

	cout << endl << "=====================" << endl;
	QueueList<float> test2;
	// data를 queue에 추가(2.2->4.4->8.8)
	test2.enqueue(2.2);
	test2.ShowAll();
	cout << "=====================" << endl;
	test2.enqueue(4.4);
	test2.ShowAll();
	cout << "=====================" << endl;
	test2.enqueue(6.6);
	test2.ShowAll();
	cout << "=====================" << endl;
	// 2.2를 dequeue
	test2.dequeue();
	test2.ShowAll();
	cout << "=====================" << endl;
	// 4.4를 dequeue
	test2.dequeue();
	test2.ShowAll();
	cout << "=====================" << endl;
	// data를 queue에 추가(8.8)
	test2.enqueue(8.8);
	test2.ShowAll();
	cout << "=====================" << endl;
	// 6.6를 dequeue
	test2.dequeue();
	test2.ShowAll();
	cout << "=====================" << endl;
	// 8.8를 dequeue
	test2.dequeue();
	test2.ShowAll();
}