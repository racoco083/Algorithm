#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
#define MXK 17 // 2^17 = 131072
#define MXN 100001
int N, M;
vector<int> adj[MXN];
int depth[MXN];
// 인덱스 범위값 실수 했다.
int par[MXK+1][MXN];

void init() {
	depth[1] = 0;
	par[0][1] = 1;
	queue<int> qu;
	qu.push(1);
	while (!qu.empty()) {
		int cur = qu.front();
		qu.pop();
		for (int i = 0; i < adj[cur].size(); i++) {
			int next = adj[cur][i];
			if (depth[next] != -1) continue;
			par[0][next] = cur;
			depth[next] = depth[cur] + 1;
			qu.push(next);
		}
	}
}

/*
밑과 같이 노드들이 경사트리로 연결되어 있다고 하자.
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
이 상태에서 정점들의 sparse table을 만든다고 하면

    1   2   3   4   5   6   7   8   9   10   11   12   13   14   15   
0   1   1   2   3   4   5   6   7   8    9   10   11   12   13   14
1   1   1   1   2   3   4   5   6   7    8    9   10   11   12   13
2   1   1   1   1   1   2   3   4   5    6    7    8    9   10   11   
3   1   1   1   1   1   1   1   1   1    2    3    4    5    6    7
4   1   1   1   1   1   1   1   1   1    1    1    1    1    1    1
가 된다.
par[2][5] == par[1][par[1][5]] == par[1][3] == 1
정점 5의 2^k(4, k==2)번째 조상을 구하려면 각 정점의 구해놓은 2^1번째 조상 값을 이용한다.
5의 2^1번째 조상은 3이고 3의 2^1번째 조상 1이 곧 5의 2^2번째 조상인 것을 알 수 있다. 왜냐하면
5에서 3은 높이 2가 차이가 나고, 3과 1도 높이 2가 차이가 난다. 1이 곧 5와 높이 차가 4라는 것을
알 수 있기 때문이다.
*/

void make_sparse_tree() {
	for (int k = 1; k < MXK + 1; k++) {
		for (int i = 1; i <= N; i++) {
			par[k][i] = par[k - 1][par[k - 1][i]];
		}
	}
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int main() {
	cin >> N;
	int a, b;
	for (int i = 1; i < N; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	memset(depth, -1, sizeof(depth));

	init();

	make_sparse_tree();

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		// 항상 b의 깊이가 크도록 한다.
		if (depth[a] > depth[b]) swap(a, b);
		// 두 정점 깊이 맞추기
		// a가 b보다 깊이가 7 더 작다면 b의 깊이를 올려야 한다.
		// 이 때 구해 놓은 sparse tree를 이용하면 k가 3일 때는 b의
		// 2^3번째 조상에 도달하여 a보다 더 높은 위치에 있게되어 무시하고 
		// k가 2일 때는 b의 2^2번째 조상에 도달하여 a와의 깊이차가 3이 되고 a보다 더 깊이가 깊다.
		// 그러므로 b의 값에 b의 2^2번째 조상을 대입한다.
		// k값은 점점 줄어드니 k가 1일 때는 새로 구한 정점 b의 2^1번째 조상도 a와의 깊이차가 1이 되고
		// a보다 더 깊이가 깊다. b에 새로 구한 정점값을 대입한다. 
		// k는 이제 0이되고 새로 구한 정점 b의 2^0값은 a와 높이차가 같다. 그러므로 b의 값에
		// 새로 구한 값을 대입한다. 이런식으로 깊이가 더 깊은 b를 a와 같은 높이로 만들었다.
		// 만약 입력으로 들어온 a와 b의 깊이가 같다면 이 코드는 의미가 없다.
		for (int k = MXK; k >= 0; k--) {
			if (depth[a] <= depth[par[k][b]]) {
				b = par[k][b];
			}
		}
		// lca 바로 밑까지 두 정점 다 올리기
		// 밑의 코드는 a와 b의 2^(k의 가장 큰 값) 조상을 찾으면서 k를 줄여나가면서 
		// a와 b의 2^k번째 조상이 다른지를 비교해 나간다. 2^MXK값은 거의 같을 것이다.
		// 왜냐하면 모든 정점들의 조상은 루트이기 때문이다. 하지만 우리가 구하고자 하는것은
		// a와 b의 가장 가까이 있는 공통 조상을 찾으려고 하는것이다. 그러므로 a와 b의
		// 2^k번째 조상이 다르다면 현재 깊이에서 2^k번 조상까지는 공통 조상이 없다는 뜻이다.
		// 이런식으로 a와 b의 깊이를 2^k씩 줄여나가면 마지막엔 a와 b가 lca의 자식값이 된다.
		// 만약 a와 b가 같은 정점이거나(현재 점이 곧 lca) a와 b가 lca의 자식들이라면 
		// 밑의 코드는 의미가 없다.
		for (int k = MXK; k >= 0; k--) {
			if (par[k][a] != par[k][b]) {
				a = par[k][a];
				b = par[k][b];
			}
		}
		// 처음부터 a와 b의 정점 값이 같을 수 있기 때문에 이런 처리를 해 준다.
		if (a == b) cout << a << '\n';
		else cout << par[0][a] << '\n';
	}
	return 0;
}
