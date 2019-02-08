/*
 *  BOJ 1753. 최단경로
 *  
 *  시간복잡도 : O(ElogV)
 *  공간복잡도 : O(V^2)
 * 
 *  (V : 정점의 수, E : 간선의 수)
 *  다익스트라를 일반 큐를 적용하면 O(E+V^2)의 시간복잡도 
 *  우선순위 큐 사용 시 O(ElogV)으로 시간상의 이점이 발생하게 된다.
 *  큐를 사용한다면 최악의 경우 시작점으로 부터의 각 정점의 dist값이
 *  매번 갱신될 수 있다. 밑과 같이 예를 들어보자
 *  a b w : a->b로의 가중치 w
 *  1 2 3
 *  2 3 3
 *  1 4 2
 *  1 3 2
 *  1에서 2를 거쳐 3을 간 값을 dist[3]에 갱신시켜서 6이 되었다.
 *  하지만 1에서 4를 거쳐 3으로 간 값이 가중치가 4로 더 적어 
 *  dist[3]을 갱신해 줄 수 있다. 최악의 경우에는 각 정점들을 모두
 *  방문하면서 종만북 다시 보고 update해야겠다..
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MXN 20002

typedef pair<int, int> pi;

int N, M, S;
vector<pi> adj[MXN];
int dist[MXN];

void bfs() {
	dist[S] = 0;
	priority_queue<pi> pq;
	pq.push({ 0, S });
	while (!pq.empty()) {
		int cur = pq.top().second;
		int cost = -pq.top().first;
		pq.pop();
		if (dist[cur] < cost) continue;
		for (int i = 0; i < adj[cur].size(); i++) {
			int next = adj[cur][i].second;
			int nextCost = adj[cur][i].first + cost;
			if (dist[next] > nextCost) {
				dist[next] = nextCost;
				pq.push({ -nextCost, next });
			}
		}
	}
}

int main() {
	cin >> N >> M >> S;
	int a, b, w;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> w;
		adj[a].push_back({ w, b });
	}

	for (int i = 0; i < MXN; i++) dist[i] = 2e9;
	bfs();
	for (int i = 1; i <= N; i++) {
		if (dist[i] == 2e9) cout << "INF" << '\n';
		else cout << dist[i] << '\n';
	}
	return 0;
}





















