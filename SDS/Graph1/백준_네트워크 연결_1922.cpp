/*
 *  최소 스패닝 트리 문제로 크루스컬 알고리즘을 사용하여 풀었다.
 *  여기서 주의할 점은 간선을 이어줄 때 이 간선을 이으면 현재의 
 *  트리에서 사이클을 만드는지를 merge 함수에서 체크하고 사이클을
 *  만들면 현재 간선을 버리고 아니면 이어준다.
 *  이런 이유로 크루스컬 알고리즘에서는 union-find가 쓰인다.
 */
#include <iostream>
#include <algorithm>
using namespace std;
#define MXM 100001
#define MXN 1001

class Edge {
public:
	int u, v, w;
	Edge() {}
	Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};

int N, M;
Edge edge[MXM];
int ei;
int pa[MXN];
int le[MXN];
int ans;

bool cmp(const Edge& a, const Edge& b) {
	return a.w < b.w;
}

// 정점 u의 root정점을 찾으며 방문한 모든 노드의
// 부모 노드를 루트로 바꾼다.
int find(int u) {
	if (u == pa[u]) return u;
	return pa[u] = find(pa[u]);
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

// u와 v의 부모가 같은 부모라면 같은 트리에 있다는 뜻으로
// 이 둘이 합쳐지면 사이클이 생긴다. 그러므로 이 둘을 잇는
// 간선은 연결되면 안 된다. 부모가 다르다면 간선을 이어 준다.
bool merge(int u, int v) {
	u = find(u), v = find(v);
	if (u == v) return false;
	if (le[u] > le[v]) swap(u, v);
	pa[u] = v;
	le[v]++;
	return true;
}

int main() {
	cin >> N >> M;
	ans = 0;
	for (int i = 1; i <= N; i++) pa[i] = i, le[i] = 1;
	int a, b, w;
	ei = 0;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> w;
		edge[ei++] = Edge(a, b, w);
	}
	// 최소비용부터 접근하기 위해 비용기준으로 오름차순 한다.
	sort(edge, edge + ei, cmp);

	int ans = 0;
	for (int i = 0; i < ei; i++) {
		int u = edge[i].u;
		int v = edge[i].v;
		int w = edge[i].w;
		// merge가 수행되어 u와 v가 병합되었을 때만
		// ans에 현재 간선 비용을 누적한다.
		if (merge(u, v)) ans += w;
	}
	cout << ans << '\n';
	return 0;
}