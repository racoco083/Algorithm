/*
 *  위상정렬이란 방향 그래프에 존재하는 각 정점들의 
 *  선행 순서를 위배하지 않으면서 모든 정점을 나열하는 것이다.
 *  각 정점의 진입차수를 구해 진입 차수가 0인 정점을 
 *  시작 정점들로하여 이 정점들의 자식 정점을 방문하는데
 *  방문할 때마다 자식 정점의 진입차수를 1씩 줄여 
 *  연결된 간선을 지운다. 자식 정점의 진입차수가 0이 되면
 *  이 정점을 qu에 넣어서 이 자식의 자식 노드를 방문할 수 
 *  있도록 해 준다.
 */

#include <iostream>
#include <vector>
using namespace std;
#define MXN 32003

int N, M;
int ind[MXN];// indegree
vector<int> adj[MXN];
int qu[MXN];
int h, r;// head, rear

bool empty() {
	return h == r;
}

int main() {
	cin >> N >> M;
	h = r = 0;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		ind[b]++;
	}

	for (int i = 1; i <= N; i++) {
		// 지입 차수가 0인 정점들에서 시작하면 된다.
		if (!ind[i]) qu[r++] = i;
	}

	while (!empty()) {
		int cur = qu[h++];
		// 큐에서 뺀 순위대로 출력하면 위상정렬이 된다.
		cout << cur << ' ';
		for (int i = 0; i < adj[cur].size(); i++) {
			// 여러 부모노드에서 next 정점으로 가는 간선이 있을 수 있지만
			// next의 진입 차수를 1씩 감소시키며 0이 될 때에만 qu에 담는다.
			// 그래서 총 한 번만 큐에 담겨 출력된다. 그리고 이 진입차수가
			// 0이 될때에만 next의 자식 노드로 갈 수 있다. 그래서 무조건
			// next가 출력되고 next의 자식이 출력된다.
			int next = adj[cur][i];
			ind[next]--;
			if (ind[next] == 0)
				qu[r++] = next;
		}
	}
	return 0;
}