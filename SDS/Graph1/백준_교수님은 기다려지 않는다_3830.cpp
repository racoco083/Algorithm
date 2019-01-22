#include "stdafx.h"

// 기준 루트 노드가 없다. 그래서 유니온 파인드를 사용하여 트리를 합쳐 나가면
// 레벨이 가장 높은 노드가 루트가 되도록 하였다. 이 트리를 기준으로 하여
// 모든 노드의 dist값에 루트와의 거리차이를 담았다. 그래서 특정 두 정점(a, b)의
// 거리를 구할 때 a정점과 root와의 차이, b정점과 root와의 차이를 이용하여
// 두 정점의 거리 차이를 구할 수 있다.

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;
typedef long long ll;
#define MXN 500005

int N, M;
int par[MXN];//부모
int dist[MXN];//해당 인덱스의 정점과 루트와의 거리
int level[MXN];//트리의 level

int find(int u) {
	if (u == par[u]) return u;
	// 밑의 두 줄의 코드 순서 바꾸면 틀린다.
	// 각 dist는 root와의 거리차를 담는다.
	int rv = find(par[u]);// root_value
	dist[u] += dist[par[u]];
	return par[u] = rv;
}

void merge(int u, int v, int w) {
	int ua = find(u); //u_ancestor
	int va = find(v);
	if (u == v) return;
	// 거리라고 적었는데 문제에선 무게로 되어 있다. 거리라 생각해도 된다.
	if (level[ua] > level[va]) {
		// va는 root 였는데 ua의 자식이 되었다. 그래서 ua와의 거리 차를
		// dist[va]에 담는다. va는 루트였었으니 dist[va]는 0이다. 
		// v가 u보다 w 만큼 거리가 더 멀다. dist[v] va와v의 거리차이이다.
		// dist[u]는 u와 ua와의 거리차이이다. 그래서 밑과 같은 dist공식이 나온다.
		dist[va] = dist[u] - dist[v] + w;
		par[va] = ua;
	}
	else {
		// 밑의 코드는 ua가 va의 자식으로 들어가는 것으로 v가 u보다
		// w만큼 더 머니 위와는 다르게 w를 빼준다.
		dist[ua] = dist[v] - dist[u] - w;
		par[ua] = va;
		if (level[ua] == level[va]) ++level[va];
	}
}

int main() {
	fastio();
	while (1) {
		cin >> N >> M;
		if (N == 0 && M == 0) break;
		for (int i = 1; i <= N; i++) par[i] = i, level[i] = 1, dist[i] = 0;
		char s;
		for (int i = 0; i < M; i++) {
			cin >> s;
			int a, b, w;
			if (s == '!') {//merge한다.
				cin >> a >> b >> w;
				merge(a, b, w);
			}
			else {//값을 찾는다.
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
? 2 3
! 2 3 100
? 2 3
? 1 3
! 4 3 150
? 4 1
0 0
*/

/*
UNKNOWN
100
200
-50
*/