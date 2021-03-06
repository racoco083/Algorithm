#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;
#define MXK 17
#define MXN 100001

class Edge {
public:
	int n, w;
	Edge() {}
	Edge(int _n, int _w) : n(_n), w(_w) {}
};

int N, M;
vector<Edge> edge[MXN];
int par[MXK + 1][MXN];
int pmx[MXK + 1][MXN];
int pmi[MXK + 1][MXN];
int depth[MXN];

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a > b ? b : a;
}

void init() {
	memset(depth, -1, sizeof(depth));
	for (int k = 0; k <= MXK; k++) {
		for (int i = 1; i <= N; i++) {
			pmx[k][i] = 0;
			pmi[k][i] = 2e9;
		}
	}
	par[0][1] = 1;
	depth[1] = 0;
	queue<int> qu;
	qu.push(1);
	while (!qu.empty()) {
		int cur = qu.front();
		qu.pop();
		for (int i = 0; i < edge[cur].size(); i++) {
			int next = edge[cur][i].n;
			int cost = edge[cur][i].w;
			if (depth[next] != -1) continue;
			depth[next] = depth[cur] + 1;
			par[0][next] = cur;
			pmx[0][next] = cost;
			pmi[0][next] = cost;
			qu.push(next);
		}
	}
}

/*
1 2 80
2 3 75
3 4 70
4 5 65
5 6 60
6 7 55
7 8 50
8 9 45
9 10 40
10 11 35
11 12 30
12 13 25
13 14 20
14 15 15

이 상태에서 정점들의 pmx sparse table을 만든다고 하면

    1    2    3    4    5    6    7    8    9    10    11    12    13    14    15
0   0   80   75   70   65   60   55   50   45    40    35    30    25    20    15
1   0   80   80   75   70   65   60   55   50    45    40    35    30    25    20
2   0   80   80   80   80   75   70   65   60    55    50    45    40    35    30
3   0   80   80   80   80   80   80   80   80    75    70    65    60    55    50
4   0   80   80   80   80   80   80   80   80    80    80    80    80    80    80
이 되고 1이 루트이다. par[0][2]가 1과 2사이의 경로 값이다. 예를 들어
pmx[2][6] == max(pmx[k - 1][i], pmx[k - 1][par[k-1][i]]) == max(65, pmx[1][par[1][6]])
== max(65, pmx[1][4]) == max(65, 75) == 75가 된다.
k를 1부터 1씩 증가시키며 값을 구해 이전의 k값을 이용해서 현재의 pmx[k][i]값을 구한다.
3,4,5,6 정점 중에 가장 긴 도로 값을 6에 저장한다.pmx[1][6]은 4,5,6사이 경로 중 가장 긴 값이고,
pmx[1][par[1][6]] == pmx[1][4] 2,3,4사이 경로 중 가장 긴 값이고 이 둘 경로 중 더 큰 값을
pmx[2][6]에 넣어주는 것을 반복해주면 pmx에 대한 sparse table이 만들어진다.
*/

void make_sparse_tree() {
	for (int k = 1; k <= MXK; k++) {
		for (int i = 1; i <= N; i++) {
			// n번 노드의 2^k 단계 위의 부모는 
			// n번 노드의 2^(k-1) 단계 위의 있는 노드의 2^(k-1) 단계 위에 있는 노드이다.
			par[k][i] = par[k - 1][par[k - 1][i]];
			// n번 노드부터 2^k 단계 위의 부모노드까지중 가장 긴 도로는 아래 두 도로중 긴 도로이다. 
			// 1. n번 노드부터 n번 노드의  2^(k-1) 단계 위의 부모노드 사이에서 가장 긴 도로
			// 2. n번 노드의  2^(k-1) 단계 위의 부모노드부터 n번 노드의 2^(k-1) 단계 위의 부모노드있는 노드의 2^(k-1) 위에 있는 부모노드 사이에서 가장 긴 도로
			pmx[k][i] = max(pmx[k - 1][i], pmx[k - 1][par[k - 1][i]]);
			// n번 노드부터 2^k 단계 위의 부모노드까지중 가장 짧은 도로는 아래 두 도로중 짧은 도로이다. 
			// 1. n번 노드부터 n번 노드의  2^(k-1) 단계 위의 부모노드 사이에서 가장 짧은 도로
			// 2. n번 노드의  2^(k-1) 단계 위의 부모노드부터 n번 노드의 2^(k-1) 단계 위의 부모노드있는 노드의 2^(k-1) 위에 있는 부모노드 사이에서 가장 짧은 도로
			pmi[k][i] = min(pmi[k - 1][i], pmi[k - 1][par[k - 1][i]]);
		}
	}
}

int main() {
	cin >> N;
	int a, b, w;
	for (int i = 1; i < N; i++) {
		cin >> a >> b >> w;
		edge[a].push_back(Edge(b, w));
		edge[b].push_back(Edge(a, w));
	}
	init();
	make_sparse_tree();
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		int mxv = 0, miv = 2e9;

		if (depth[a] > depth[b]) swap(a, b);
		// 밑의 주석 친 코드를 추가해서 틀렸다. a가 lca일 수도 있다.
		// 그런 경우에는 a의 부모노드는 포함하면 안 되는데 밑의 코드때문에
		// 무조건 포함이 된 것이다.
		// mxv = pmx[0][a];
		// miv = pmi[0][a];
		for (int k = MXK; k >= 0; k--) {
			if (depth[a] <= depth[par[k][b]]) {
				mxv = max(mxv, pmx[k][b]);
				miv = min(miv, pmi[k][b]);
				b = par[k][b];
			}
		}

		for (int k = MXK; k >= 0; k--) {
			if (par[k][a] != par[k][b]) {
				// a와b가 같이 올라가므로 항상 두 정점의 max, min값을 같이
				// 비교해주어야 한다.
				mxv = max(mxv, max(pmx[k][a], pmx[k][b]));
				miv = min(miv, min(pmi[k][a], pmi[k][b]));
				a = par[k][a];
				b = par[k][b];
			}
		}

		// 문제 설명에 보면 a, b가 다른점으로 주어져도 트리를 타고 올라가면서
		// a와 b의 값이 같아질 수 있다. 예를 들어 경사이진트리인 경우에 그런 경우에는
		// a가 곧 lca이다. 그 밖에는 a와 b의 부모가 lca이므로 밑과 같이 처리
		if (a != b) {
			miv = min(miv, min(pmi[0][a], pmi[0][b]));
			mxv = max(mxv, max(pmx[0][a], pmx[0][b]));
		}
		cout << miv << ' ' << mxv << '\n';
	}
	return 0;
}
