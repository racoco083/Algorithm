/*
 *  BOJ 1197. 최소 스패닝 트리
 *
 *  시간복잡도 : O(ElogE)
 *
 *  kruskal algorithm 
 * 
 */

#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MXN 10001

class Edge {
public:
	int a, b, c;
	Edge(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
	Edge() {}
};

int N, M;
vector<Edge> edge;
int par[MXN + 1];
int level[MXN + 1];

bool cmp(const Edge &a, const Edge &b) {
	return a.c < b.c;
}

void init(int n) {
	for (int i = 1; i <= n; i++) {
		par[i] = i;
		level[i] = 1;
	}
}

int find(int u) {
	if (par[u] == u) return u;
	return par[u] = find(par[u]);
}

bool merge(int u, int v) {
	u = find(u);
	v = find(v);
	if (u == v) return false;
	if (level[u] > level[v]) swap(u, v);
	if (level[u] == level[v]) level[v]++;
	par[u] = v;
	return true;
}

int main() {
	fastio();
	cin >> N >> M;
	init(N);
	int a, b, c;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		edge.push_back(Edge(a, b, c));
	}
	sort(edge.begin(), edge.end(), cmp);

	int edgeCnt = 0;
	int edgeSum = 0;
	for (int i = 0; i < edge.size(); i++) {
		int u = edge[i].a;
		int v = edge[i].b;
		int c = edge[i].c;
		if (merge(u, v)) {
			edgeSum += c;
			edgeCnt++;
		}
		if (edgeCnt == N - 1) break;
	}
	cout << edgeSum << '\n';
	return 0;
}