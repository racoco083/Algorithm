#include <iostream>
using namespace std;
#define MXN 5

int par[MXN + 1];
int level[MXN + 1];

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int find(int u) {
	if (u == par[u]) return u;
	return par[u] = find(par[u]);
}

void merge(int u, int v) {
	u = find(u);
	v = find(v);
	if (u == v) return;//실수 하는 부분으로 까먹지 않도록 조심하자!
	if (level[u] > level[v]) swap(u, v);
	par[u] = v;
	if (level[u] == level[v]) ++level[v];
}

void init() {
	for (int i = 1; i <= MXN; i++) {
		level[i] = 1;
		par[i] = i;
	}
}

void print() {
	for (int i = 1; i <= MXN; i++) {
		cout << par[i] << '\n';
	}
}

int main() {
	init();
	merge(1, 2);
	merge(1, 3);
	merge(4, 5);
	merge(1, 4);

	print();
}
