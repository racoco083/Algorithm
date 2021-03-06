/*
 *  BOJ 6118. 숨바꼭질
 *
 *  시간복잡도 : O(MlogN)
 *
 *  시작점을 1이로 두고 다익스트라를 돌려 dist배열을 구한 뒤 여기서 거리가
 *  가장 큰 것의 거리, 시작 정점, 같은 거리의 정점개수를 dist크기 만에 
 *  구할 수 있다.
 *
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MXN 20002
typedef pair<int, int> pi;

vector<int> adj[MXN + 1];
int dist[MXN + 1];
int N, M;
const int INF = 2e9;

void dijk() {
	priority_queue<pi> pq;
	// 최소힙을 하면 여기서도 1이 아닌 -1을 넣어주어야 한다.
	// dist[start]값은 1로 해 두고 pq에서는 0을 넣는 실수 주의!
	pq.push({ -1, 1 });
	dist[1] = 1;
	while (!pq.empty()) {
		// test and set
		int cur = pq.top().second;
		int cost = -pq.top().first;
		pq.pop();

		if (dist[cur] < cost) continue;
		for (int i = 0; i < adj[cur].size(); i++) {
			int next = adj[cur][i];
			int nextCost = cost + 1;
			if (dist[next] > nextCost) {
				dist[next] = nextCost;
				pq.push({ -nextCost, next });
			}
		}
	}
}

int main() {
	fastio();
	cin >> N >> M;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	fill(dist + 1, dist + 1 + N, INF);
	dijk();
	int mxd = 0;// max_dist
	int mxv = 0;// max_vertex
	int mxc = 0;// max_count
	for (int i = 2; i <= N; i++) {
		if (dist[i] == INF) continue;
		if (dist[i] > mxd) {
			mxv = i;
			mxd = dist[i];
			mxc = 1;
		}
		else if (dist[i] == mxd) mxc++;
	}
	cout << mxv << ' ' << mxd - 1 << ' ' << mxc << '\n';
	return 0;
}