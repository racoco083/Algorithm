/*
 *  BOJ 5179. 거의 최단 경로
 *  
 *  다익스트라로 S에서 D까지의 최단 경로를 구한다. 
 *  구한 dist값을 통해 D부터 시작해서 S까지 가는 경로를 뒤져서
 *  거리가 가장 짧은 경로들의 간선을 adj에서 지워준다.
 *  다 지우고 나서 다시 다익스트라를 하면 두 번째 최단경로가
 *  나온다. 이 값을 출력하면 된다.
 * 
 */

#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
#define MXN 502

typedef pair<int, int> pi;

int N, M, S, D;
// 정점들 간 간선을 지우기 위해 2차원 행렬을 사용하였다.
// vector<int> adj[MXN]을 사용하면 지우기가 여간 어려운게 아니다.
int adj[MXN][MXN];

int dist[MXN];
const int INF = 2e9;

void bfs() {
	dist[S] = 0;
	priority_queue<pi> pq;
	pq.push({ 0, S });
	while (!pq.empty()) {
		int cur = pq.top().second;
		int cost = -pq.top().first;
		pq.pop();
		if (dist[cur] < cost) continue;
		for(int i=0; i<N; i++){
			if (adj[cur][i] == INF || cur == i) continue;
			int next = i;
			int nextCost = cost + adj[cur][i];
			if (dist[next] > nextCost) {
				dist[next] = nextCost;
				pq.push({ -nextCost, next });
			}
		}
	}
}

void rmpath() {// remove_path
	queue<int> qu;
	qu.push(D);
	while (!qu.empty()) {
		int cur = qu.front();
		qu.pop();
		for (int i = 0; i < N; i++) {
			if (dist[i] + adj[i][cur] == dist[cur]) {
				adj[i][cur] = INF;
				qu.push(i);
				// 최단 경로가 여러개 일 수 있다. 모든 최단 경로를 없애주어야 한다.
				// 문제를 잘 못 읽어 한개의 최단경로만 지우기 위해 break를 해서 
				// 헤맸다.
			}
		}
	}
}

int main() {
	while (1) {
		cin >> N >> M;
		if (N == 0 && M == 0) break;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				adj[i][j] = INF;
			}
		}
		for (int i = 0; i < N; i++) dist[i] = INF;
		cin >> S >> D;
		int a, b, w;
		for (int i = 0; i < M; i++) {
			cin >> a >> b >> w;
			adj[a][b] = w;
		}
		bfs();
		rmpath();
		for (int i = 0; i < N; i++) dist[i] = INF;
		bfs();
		if (dist[D] == INF) cout << -1 << '\n';
		else cout << dist[D] << '\n';
	}	
	return 0;
}