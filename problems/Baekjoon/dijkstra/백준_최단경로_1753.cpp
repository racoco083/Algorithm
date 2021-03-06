/*
 *  BOJ 1753. 최단경로
 *  
 *  시간복잡도 : O(ElogV)
 *  공간복잡도 : O(V^2)
 * 
 *  (V : 정점의 수, E : 간선의 수)
 *  우선순위 큐 사용 시 O(ElogV)으로 시간상의 이점이 발생하게 된다.
 *  a b w : a->b로의 가중치 w
 *  1 2 2
 *  1 5 1
 *  1 4 3
 *  5 3 4
 *  5 4 5
 *  2 3 1
 *  1-5간선이 제일 비용이 적으므로 5에서 3과 4의 거리를 갱신한다.
 *  나중에는 2에서 3을 가는 것이 비용이 더 적으므로 3이 또 갱신된다.
 *  4도 마찬가지로 1에서 4로 가는 것이 비용이 더 적으므로 갱신된다.
 *  그래서 E개의 간선을 모두 조사하면서 우선순위큐에는 최악의 경우 
 *  E개의 간선이 들어갔다 나올 수 있다. 그러므로 시간복잡도는 
 *  O(ElogE)이다. 알고리즘 문제의 대개의 경우 E는 V^2보다 작다.
 *  무방향 그래프에서 간선의 최대개수는 V(V-1)/2이다. 방향그래프니
 *  V(V-1)/2*2를 해주면 V(V-1)이 된다. 그러면 E를 V^2으로 바꿀 수 있다.
 *  빅오계산이니까 ElogV^2 == 2ElogV == ElogV, V<E<V^2이므로
 *  시간복잡도를 최대한 작게 보이게 하기 위해서 앞에 E를 V^2으로 바꾸지
 *  않는다. 하지만 로그의 값은 E보다 V가 되는것이 더 작아보인다.
 * 
 *  만약 여기서 pq대신 그냥 queue를 사용한다면 모든 간선에 대해서
 *  모든 정점을 방문해 주어야하니 시간복잡도는 O(EV)가 된다.
 *  그러므로 TLE가 뜨게 된다.
 *  
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





















