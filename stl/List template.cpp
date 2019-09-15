#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#include <stdio.h>

template <class T>
class Node {
public:
	T val;
	Node<T> *prev;
	Node<T> *next;

	~Node<T>() {}
	Node<T>() {
		prev = 0;
		next = 0;
	}

	Node<T>(T a) {
		val = a;
		prev = 0;
		next = 0;
	}
};

template <class T>
class MList {
public:
	Node<T> *Head;
	Node<T> *Tail;
	int sz;

	~MList<T>() {}
	MList<T>() {
		Head = new Node<T>();
		Tail = new Node<T>();
		Head->next = Tail;
		Tail->prev = Head;
		sz = 0;
	}

	void push_back(T a) {
		Node<T> *nn = new Node<T>(a);
		nn->next = Tail;
		nn->prev = Tail->prev;
		Tail->prev->next = nn;
		Tail->prev = nn;
		sz++;
	}

	void push_front(T a) {
		Node<T> *nn = new Node<T>(a);
		nn->next = Head->next;
		nn->prev = Head;
		Head->next->prev = nn;
		Head->next = nn;
		sz++;
	}

	void pop_back() {
		Node<T> *D = Tail->prev;
		Tail->prev = Tail->prev->prev;
		Tail->prev->next = Tail;
		delete D;
		sz--;
	}

	void pop_front() {
		Node<T> *D = Head->next;
		Head->next = Head->next->next;
		Head->next->prev = Head;
		delete D;
		sz--;
	}

	void insert(int p, T a) {
		if (p > sz) {
			printf("insert error\n");
			return;
		}

		Node<T> *nn = new Node<T>(a);
		Node<T> *cur = Head->next;
		for (int i = 0; i < p; i++) {
			cur = cur->next;
		}
		nn->next = cur;
		nn->prev = cur->prev;
		cur->prev->next = nn;
		cur->prev = nn;
		sz++;
	}

	void del(int p) {
		if (p >= sz) {
			printf("del error\n");
			return;
		}

		Node<T> *D = Head->next;
		for (int i = 0; i < p; i++) {
			D = D->next;
		}
		D->prev->next = D->next;
		D->next->prev = D->prev;
		delete D;
		sz--;
	}

	void print() {
		Node<T> *cur = Head->next;
		while (cur != Tail) {
			printf("%d ", cur->val);
			cur = cur->next;
		}
	}
};

MList<int> list;

int main() {
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.push_front(4);

	list.insert(4, 5);
	list.insert(5, 5);

	list.print();
}