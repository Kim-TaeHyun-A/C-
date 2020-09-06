// Queue ADT C++�� ����
#include<iostream>
using namespace std;

template<typename T>
class QueueList;

// QueueNOde ����
template<typename T>
class QueueNode {
	friend QueueList<T>; // QueueList�� QueueNode ��� ����
private:
	T data;
	QueueNode* next;
public:
	QueueNode(const T); // ������ = createNode
};

template<typename T>
QueueNode<T>::QueueNode(const T data) { // ������ ����
	this->data = data;
	next = NULL;
}
//QueueNode ��

template<typename T>
class QueueList { // head node
private:
	QueueNode<T>* head, * rear;
	int count; // element ��
public:
	QueueList(); //������ = createqueue
	void enqueue(const T);
	void dequeue();
	void ShowAll();
};

//QueueList �Լ� ���� ����
template<typename T>
QueueList<T>::QueueList():count(0) {
	//������ = createqueue
	head = rear = NULL;
}

template<typename T>
void QueueList<T>::enqueue(const T data) {
	QueueNode<T>* tmpNode = new QueueNode<T>(data);
	if (count == 0) {
		// queue ó������ �������� ��
		head = tmpNode;
		rear = tmpNode;
	}
	else {
		// ���� �Ǿ��ִ� queue�� node �߰�
		// front�� ���� ����
		rear->next = tmpNode;
		rear = tmpNode;
	}
	// queue������ node �� ����
	count++;
}

template<typename T>
void QueueList<T>::dequeue() {
	if (head == NULL) {
		cout << "empty queue(dequeue)" << endl;
		return;
	}
	// queue�� ���� �տ� �ִ� node�� ������
	QueueNode<T>* tmpNode = head;
	head = head->next;
	delete tmpNode;
	count--;
}

template<typename T>
void QueueList<T>::ShowAll() {
	// queue�� node�� ��ü ���
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
//QueueList �Լ� ���� ��

int main() {
	QueueList<int> test;

	test.ShowAll();// empty queue ���
	cout << "=====================" << endl;
	// data�� queue�� �߰�(2->4->8)
	test.enqueue(2);
	test.ShowAll();
	cout << "=====================" << endl;
	test.enqueue(4);
	test.ShowAll();
	cout << "=====================" << endl;
	test.enqueue(6);
	test.ShowAll();
	cout << "=====================" << endl;
	// 2�� dequeue
	test.dequeue();
	test.ShowAll();
	cout << "=====================" << endl;
	// 4�� dequeue
	test.dequeue();
	test.ShowAll();
	cout << "=====================" << endl;
	// data�� queue�� �߰�(8)
	test.enqueue(8);
	test.ShowAll();
	cout << "=====================" << endl;
	// 6�� dequeue
	test.dequeue();
	test.ShowAll();
	cout << "=====================" << endl;
	// 8�� dequeue
	test.dequeue();
	test.ShowAll();
	cout << "=====================" << endl;
	// empty queue���� dequeue�õ�
	test.dequeue();
	test.ShowAll();

	cout << endl << "=====================" << endl;
	QueueList<float> test2;
	// data�� queue�� �߰�(2.2->4.4->8.8)
	test2.enqueue(2.2);
	test2.ShowAll();
	cout << "=====================" << endl;
	test2.enqueue(4.4);
	test2.ShowAll();
	cout << "=====================" << endl;
	test2.enqueue(6.6);
	test2.ShowAll();
	cout << "=====================" << endl;
	// 2.2�� dequeue
	test2.dequeue();
	test2.ShowAll();
	cout << "=====================" << endl;
	// 4.4�� dequeue
	test2.dequeue();
	test2.ShowAll();
	cout << "=====================" << endl;
	// data�� queue�� �߰�(8.8)
	test2.enqueue(8.8);
	test2.ShowAll();
	cout << "=====================" << endl;
	// 6.6�� dequeue
	test2.dequeue();
	test2.ShowAll();
	cout << "=====================" << endl;
	// 8.8�� dequeue
	test2.dequeue();
	test2.ShowAll();
}