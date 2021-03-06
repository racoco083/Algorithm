#include<iostream>
using namespace std;
#define MAX 10

int qu[MAX];
int front, rear;

bool qFull() {
	if ((rear + 1) % MAX == front) return true;
	return false;
}

bool qEmpty() {
	if (rear == front) return true;
	return false;
}

void qPush(int v) {// 넣고 인덱스 올려야 한다!!
	if (qFull()) return;
	qu[rear] = v;
	rear = (rear + 1) % MAX;
}

void qPop() {
	if (qEmpty()) return;
	front = (front + 1) % MAX;
}

int main() {
	front = 9, rear = 9;
	qPush(5);
	qPush(4);
	qPush(3);
	qPush(2);
	qPush(1);
	while (!qEmpty()) {
		cout << qu[front] << ' ';
		qPop();
	}
	return 0;
}
