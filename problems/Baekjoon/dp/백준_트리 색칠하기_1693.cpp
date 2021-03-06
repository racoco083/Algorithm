/*
 *  BOJ 1693. 트리 색칠하기
 *
 *  cache[i][j] : i번째 node에 대해서 j를 색칠했을 때, 그 서브 트리의 최솟값 
 *  메모이제이션을 통해 각 노드에서 자식을 방문하여 가능한 모든 색깔을 넣어 자식의 최소값을 구한다.
 *  이렇게 구한 모든 자식의 최솟값을 다 더해서 리턴하는 것을 재귀적으로 반복하면 된다.
 *
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#define MAX 100001

double N;
int cc;// color_count
vector<int> adj[MAX];
int cache[MAX][18];
int visited[MAX];
const int INF = 2e9;

int min(int a, int b) {
	return a > b ? b : a;
}

int log2N(double n) {
	int ret = 0;
	while (n >= 2.0) {
		ret++;
		n /= 2.0;
	}
	if (n != 1.0) ret++;
	return ret;
}

// 아무 정점에서 시작해도 되지만 1번 정점을 루트로 했다.
// 각 노드의 레벨은 정해져 있다. 노드의 레벨이 dfs를 도는 동안 변경됐다면
// dp를 적용할 수 없다. 노드의 레벨이 달라져도 적용되는 경우(백준의 카드게임)도 있지만
// 여기서는 시작 노드를 기점으로 모든 노드의 레벨이 고정되어 있다.

int dfs(int v, int c) {// vertex, color
					   // cache[v][c] 이 값은 처음에 ret = 0으로 초기화 된다.
					   // 그 말은 자식노드들에 의해서 값이 정해진다!!
	int &ret = cache[v][c];
	if (ret != -1) return ret;
	ret = 0;
	visited[v] = true;
	for (int i = 0; i < adj[v].size(); i++) {
		int n = adj[v][i];
		if (visited[n]) continue;
		// chos는 자식 n정점으로 가서 얻을 수 있는 색깔 점수의 최소값을 담는다.
		int chos = INF;
		// 자식의 색깔을 가능한 색깔 다 넣어서 그 값중에 가장 작은 값을 리턴 받는다.
		for (int j = 1; j <= cc; j++) {
			if (j != c) chos = min(chos, dfs(n, j) + j);
		}
		// ret는 모든 자식의 최소색깔의 합을 가져야 한다.
		ret += chos;
	}
	visited[v] = false;
	return ret;
}

int main() {
	fastio();
	cin >> N;
	// N개의 노드에 대해서 색깔의 개수는 log2N개로 커버 가능하다.
	// 경사이진트리면 색깔 두개만 있으면 되고, 완전이진트리일 경우에는
	// log2N개면 된다.
	cc = log2N(N + 1.0);// mask_cnt;
	int a, b;
	for (int i = 1; i < N; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	memset(cache, -1, sizeof(cache));
	int ans = INF;
	for (int i = 1; i <= cc; i++) {
		ans = min(ans, dfs(1, i) + i);
	}
	cout << ans << '\n';

	return 0;
}