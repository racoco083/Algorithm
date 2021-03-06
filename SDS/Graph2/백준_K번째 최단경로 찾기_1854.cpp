/*
 *  BOJ 1854. K번째 최단경로 찾기
 *
 *  시간복잡도 : O(ElogV), E : 간선의 개수, V : 정점의 개수
 *  최단경로 문제를 보면 시간복잡도가 왜 이렇게 나오는지 알 수 있다.
 *  각 정점의 K번째 최단경로를 찾는다고 해서 그냥 다익스트라 시간복잡도에서 
 *  시간이 더 걸린다거나 하지 않는다. 
 *
 *  다익스트라 알고리즘을 활용하는데 다른점은 dist배열에서 N개의
 *  pq가 있는 배열이 되었다는 것이다. 최대힙을 활용하여 dist[i]의 사이즈가
 *  K보다 작으면 dist[i]에 nextCost를 집어 넣고 아니면 dist[i]의 가장 큰 값과
 *  비교해서 nextCost가 더 작다면 dist[i]에 가장 큰 값을 빼고 nextCost를
 *  집어넣는다. 모든 정점의 K번째 이하 dist까지 구하고 각 정점의 dist사이즈가
 *  K보다 작다면 K번째 dist가 만들어질 수 없으므로 -1을 그밖에는 K번째 정점을
 *  출력하면 된다.
 * 
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MXN 1002
typedef pair<int, int> pi;

int N, M, K;
vector<pi> adj[MXN];
priority_queue<int> dist[MXN];

void dijk() {
	priority_queue<pi> pq;
	pq.push({ 0, 1 });
	dist[1].push(0);
	while (!pq.empty()) {
		int cur = pq.top().second;
		int cost = -pq.top().first;
		pq.pop();
		for (int i = 0; i < adj[cur].size(); i++) {
			int next = adj[cur][i].second;
			int nextCost = adj[cur][i].first + cost;
			if (dist[next].size() < K) {
				dist[next].push(nextCost);
				pq.push({ -nextCost, next });
			}
			else if (nextCost < dist[next].top()) {
				dist[next].pop();
				dist[next].push(nextCost);
				pq.push({ -nextCost, next });
			}
		}
	}
}

int main() {
	cin >> N >> M >> K;
	int a, b, w;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> w;
		adj[a].push_back({ w, b });
	}

	dijk();
	for (int i = 1; i <= N; i++) {
		if (dist[i].size() < K) cout << -1 << '\n';
		else cout << dist[i].top() << '\n';
	}
	return 0;
}