#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#include<iostream>
using namespace std;

int pq[11];
int pqSize;

bool pqEmpty() {
	return pqSize == 0;
}

void pqPush(int v) {
	int c = ++pqSize;
	int p = c / 2;

	while (p) {
		if (pq[p] < v) {
			pq[c] = pq[p];
			c = p, p = c / 2;
		}
		else break;
	}
	pq[c] = v;
}

void swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void pqAnotherPush(int v) {
	pq[++pqSize] = v;
	int c = pqSize;
	int p = c / 2;

	while (p) {
		if (pq[p] < pq[c]) {
			swap(pq[p], pq[c]);
			c = p, p = c / 2;
		}
		else break;
	}
}

void pqPop() {
	if (pqEmpty()) return;
	pq[1] = pq[pqSize--];
	int p = 1;
	int c = 2 * p;
	while (c <= pqSize) {
		if (c + 1 <= pqSize && pq[c] < pq[c + 1]) c++;
		if (pq[p] < pq[c]) {
			swap(pq[p], pq[c]);
			p = c, c = 2 * p;
		}
		else break;
	}
}

////최대힙
//int main() { 
//	pqSize = 0;
//	pqPush(5);
//	pqPush(1);
//	pqPush(4);
//	pqPush(2);
//	pqPush(3);
//
//	while (!pqEmpty()) {
//		cout << pq[1] << '\n';
//		pqPop();
//	}
//	return 0;
//}

//최소힙
int main() {
	pqSize = 0;
	pqPush(-5);
	pqPush(-1);
	pqPush(-4);
	pqPush(-2);
	pqPush(-3);

	while (!pqEmpty()) {
		cout << -pq[1] << '\n';
		pqPop();
	}
	return 0;
}