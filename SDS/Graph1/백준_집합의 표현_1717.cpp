#include <iostream>
using namespace std;
#define MXN 1000001

int N, M;
int pa[MXN];// parent
// 경사 이진트리가 생길 경우의 시간복잡도를 줄이기 위해 level사용
int le[MXN];// level

// 현재 노드에서 루트 노드까지 방문하면서 방문한 모든 노드의
// 부모를 최고 조상 루트로 갱신시킨다.
int find(int u) {
	if (u == pa[u]) return u;
	return pa[u] = find(pa[u]);
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

// 두 개의 트리를 병합한다.
void merge(int u, int v) {
	u = find(u), v = find(v);
	// 두 트리의 루트가 같으면 병합이 된 상태로 return한다.
	if (u == v) return;
	// 항상 v가 u의 부모가 되로록 하여 코드의 양을 줄였다.
	if (le[u] > le[v]) swap(u, v);
	pa[u] = v;
	le[v]++;
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) pa[i] = i, le[i] = 1;
	int a, b, c;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		if (a == 0) {// merge
			merge(b, c);
		}
		else {// find
			b = find(b);
			c = find(c);
			if (b != c) cout << "NO" << '\n';
			else cout << "YES" << '\n';
		}
	}
	return 0;
}