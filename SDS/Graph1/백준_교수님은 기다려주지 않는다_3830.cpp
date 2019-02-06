// 기준 루트 노드가 없다. 그래서 유니온 파인드를 사용하여 트리를 합쳐 나가면
// 레벨이 가장 높은 노드가 루트가 되도록 하였다. 이 트리를 기준으로 하여
// 모든 노드의 dist값에 루트와의 거리차이를 담았다. 그래서 특정 두 정점(a, b)의
// 거리를 구할 때 a정점과 root와의 차이, b정점과 root와의 차이를 이용하여
// 두 정점의 거리 차이를 구할 수 있다.

#include <iostream>
using namespace std;
#define MXN 100002

typedef long long ll;

int N, M;
int par[MXN];
int le[MXN];
ll dist[MXN];

/*
밑의 예제를 예로 들어 느낌표까지 쿼리를 다 처리하면
  1
2   3
    4
2와 3의 부모는 1, 4의 부모는 3인 트리가 된다.
하지만 기준점이 루트인 1이므로 dist[4]의 값은 150이 되어야 하는데
-100으로 기준점이 3일때의 값을 유지하고 있다.

       1    2    3    4
dist   0   100  250  -100
? 2 4 를 수행하면 4가 2 보다 얼마나 더 큰지를 물어본다.
이 대 find함수를 통해 정점4를 정점1과 바로 연결해버리면서 루트1로부터의
무게값 150을 갱신한다. 밑의 코드와 같이 dist[4]값을 갱신하는 방법은 간단하다.
루트까지 재귀적으로 방문하여 루트의 부모는 루트이므로 루트를 리턴하고
그 다음은 정점 3이 리턴되고 정점4에서 dist[4]는 -100이고 dist[4] += dist[1] + dist[3]을
해주게 되어 150으로 갱신된다. 이것은 루트 1과 4의 무게차이이며 4의 부모도 1로 바뀌어
   1
2  3   4
와 같이 그래프가 바뀐다.
*/

int find(int u) {
	if (u == par[u]) return u;
	int next = find(par[u]);
	dist[u] += dist[par[u]];
	return par[u] = next;
}

/*
dist값 갱신하는 부분이 핵심이다.밑의 예제로 예를 들어보자
!1 2 100 = > 1 - 2, dist[1] == 0, dist[2] == 100이 된다.
!3 4 - 100 = > 3 - 4 dist[3] == 0, dist[4] == -100이 된다.
!2 4 50 = > 2의 루트 1과 4의 루트 3의 레벨이 같으므로
1이 3의 루트가 된다고 가정하자.이때 루트1로 부터 무게 dist[3]값을 구한다.
2는 1보다 100 더 무겁고 4는 2보다 50 더 무거우므로 4는 1보다 150더 무겁다.
3은 4보다 100 더 무거우므로 dist[3]은 250이 되어야 한다.
dist[3] = dist[2] - dist[4] + w가 된다.
반대로 3이 1의 루트가 된다고 가정하자.이때 루트3로 부터 무제 dist[1]값을 구한다.
3은 4보다 100 더 무겁다 4는 2보다 50 더 무겁다. 2는 1보다 100 더 무겁다.
dist[1] = -250이 되는 것을 알 수 있다.
dist[1] = dist[4] - dist[2] - w가 된다.
*/

void merge(int a, int b, int w) {
	int ra = find(a);
	int rb = find(b);
	if (le[ra] >= le[rb]) {
		dist[rb] = dist[a] - dist[b] + w;
		if (le[ra] == le[rb]) le[ra]++;
		par[rb] = ra;
	}
	else {
		dist[ra] = dist[b] - dist[a] - w;
		par[ra] = par[rb];
	}
}

int main() {
	while (1) {
		cin >> N >> M;
		if (N == 0 && M == 0) break;
		for (int i = 1; i <= N; i++) par[i] = i, le[i] = 1, dist[i] = 0;
		char c;
		int a, b, w;
		for (int i = 0; i < M; i++) {
			cin >> c;
			if (c == '!') {
				cin >> a >> b >> w;
				merge(a, b, w);
			}
			else {
				cin >> a >> b;
				if (find(a) == find(b)) cout << dist[b] - dist[a] << '\n';
				else cout << "UNKNOWN" << '\n';
			}
		}
	}
	return 0;
}

/*
4 7
! 1 2 100
! 3 4 -100
! 2 4 50
? 2 4
? 1 3
? 3 1
0 0
*/