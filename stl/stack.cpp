#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#include<iostream>
using namespace std;
#define MAX 10

int st[MAX];
int top;

bool sEmpty() {
	if (top == -1) return true;
	return false;
}

void sPush(int v) {
	st[++top] = v;
}

void sPop() {
	if (sEmpty()) return;
	--top;
}

int main() {
	top = -1;
	sPush(5);
	sPush(4);
	sPush(3);
	sPush(2);
	sPush(1);

	while (!sEmpty()) {
		cout << st[top] << ' ';
		sPop();
	}
	return 0;
}