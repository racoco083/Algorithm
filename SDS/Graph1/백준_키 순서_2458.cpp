#include <iostream>
using namespace std;
#define MXN 502
int N, M;
int adj[MXN][MXN];

void floyd() {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (adj[i][k] && adj[k][j]) adj[i][j] = 1;
			}
		}
	}
}

int main() {
	cin >> N >> M;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		adj[a][b] = 1;
	}
	// 플로이드를 통해 1->5, 5->4가 연결되어있다면 1->4도 연결되게 해 준다.
	floyd();
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		int cnt = 0;
		// 현재 정점 i자신보다 큰 노드의 개수를 세아린다.
		for (int j = 1; j <= N; j++) if (adj[i][j]) cnt++;
		// 현재 정점 i자신보다 작은 노드의 개수를 세아린다.
		for (int j = 1; j <= N; j++) if (adj[j][i]) cnt++;
		// cnt값이 N-1이라는 것은 현재 정점 i를 제외한 모든 정점의 개수이므로
		// 현재 정점의 위치를 알 수 있다.
		if (cnt == N - 1) ans++;
	}
	cout << ans << '\n';
	return 0;
}