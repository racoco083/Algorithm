// 크루스칼 알고리즘
// - 그래프의 각 선의 가중치와 그 선과 연결된 두 정점을 담은 배열을 정렬하여
// 가중치가 가장 작은 선부터 그래프에 추가하여 그래프를 만든다.이때 상호 배타적 조합 이용해
// if (find[u] == find[v]) 같은 트리에 있다는 뜻으로 이 경우에는 무시해준다.
// 이렇게 계속 가중치가 작은 것부터 담으면 최소스패닝 트리가 만들어진다.
// 시간복잡도는 | E | log | E | 이다.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DisjointSet {
public:
	vector<int> parent, rank;
	DisjointSet(int n) : parent(n), rank(n, 1) {
		for (int i = 0; i < n; i++) parent[i] = i;
	}
	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}
	void merge(int u, int v) {
		u = find(u), v = find(v);
		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) rank[v]++;
	}
};// 각 정점의 번호를 알 필요없이 각 정점의 부모의 번호만 알면된다.
  // 처음 초기화 시에는 모든 점들이 연결되어 있지 않으니 자기자신이 부모다.
  // rank는 만들어지는 트리의 높이를 최소화 하기 위해서이다.

const int MAX_V = 100;
int V;
vector<pair<int, int>> adj[MAX_V];
int visited[MAX_V][MAX_V];
int kruskal(vector<pair<int, int>>& selected) {
	int ret = 0;
	selected.clear();
	vector<pair<int, pair<int, int>>> edges;
	for (int here = 0; here < V; here++) {
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].second;
			if (visited[here][there] != -1) continue;
			else visited[there][here] = 1;
			// 위 if-else 두 코드에 의해 간선이 무방향 그래프에서 간선
			// 의 개수가 6개면 edges에는 양방향으로 해서 12개가 
			// 저장되는데, 그걸 막고 중복을 제거한 6개만 저장되도록 한다.
			// 위의 두코드가 없어도 잘 돌아가긴 한다.
			edges.push_back(make_pair(adj[here][i].first, make_pair(here, there)));
		}
	}
	cout << edges.size() << endl;// 6이 나와야 한다.
	sort(edges.begin(), edges.end());
	DisjointSet sets(V);
	for (int i = 0; i < edges.size(); i++) {
		int cost = edges[i].first;
		int u = edges[i].second.first;
		int v = edges[i].second.second;
		if (sets.find(u) == sets.find(v)) continue;
		sets.merge(u, v);
		// 위의 두 코드는 자주 실수하는 부분이며 이 알고리즘에서 가장 중요한
		// 부분이다 조심하자!!
		selected.push_back(make_pair(u, v));
		ret += cost;
	}
	return ret;
}

void main() {
	V = 4;
	memset(visited, -1, sizeof(visited));
	vector<pair<int, int>> selected;
	int ret = 0;
	adj[0].push_back(make_pair(2, 1));
	adj[1].push_back(make_pair(2, 0));
	adj[0].push_back(make_pair(7, 2));
	adj[2].push_back(make_pair(7, 0));
	adj[0].push_back(make_pair(6, 3));
	adj[3].push_back(make_pair(6, 0));
	adj[1].push_back(make_pair(5, 2));
	adj[2].push_back(make_pair(5, 1));
	adj[1].push_back(make_pair(4, 3));
	adj[3].push_back(make_pair(4, 1));
	adj[2].push_back(make_pair(3, 3));
	adj[3].push_back(make_pair(3, 2));
	ret = kruskal(selected);
	cout << ret;// 답은 9가 나와야 한다.
}
