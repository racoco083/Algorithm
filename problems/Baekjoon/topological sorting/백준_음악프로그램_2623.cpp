/*
 *  BOJ 2623. 음악프로그램
 *
 *  시간복잡도 : O(N)
 *
 *  전형적인 위상정렬 문제이지만 사이클이 생길 수 있다.
 *  밑에 사이클이 생겼을 때 해결하는 방법을 적었다
 *  
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
#include <set>
using namespace std;
#define MXN 1002

vector<int> adj[MXN+1];
int indegree[MXN + 1];
vector<int> start;
vector<int> ans;
int N, M;

void dfs(int cur) {
	for (int i = 0; i < adj[cur].size(); i++) {
		int next = adj[cur][i];
		indegree[next]--;
		if (indegree[next] == 0) {
			ans.push_back(next);
			dfs(next);
		}
	}
}

int main() {
	fastio();
	cin >> N >> M;
	int a, b, RC;
	for (int i = 0; i < M; i++) {
		cin >> RC;
		cin >> a;
		for (int j = 1; j < RC; j++) {
			cin >> b;
			adj[a].push_back(b);
			indegree[b]++;
			a = b;
		}
	}
	for (int i = 1; i <= N; i++) {
		if (indegree[i]) continue;
		start.push_back(i);
		ans.push_back(i);
	}

	for (int i = 0; i < start.size(); i++) dfs(start[i]);

	// 사이클이 생기면 indegree가 0이 될 수 없는 정점이 생긴다.
	// 0이 되는 정점의 개수가 N개가 안 되면 사이클이 있다는 것이다.
	if (ans.size() != N) cout << 0 << '\n';
	else {
		for (int i = 0; i < ans.size(); i++) cout << ans[i] << '\n';
	}
	return 0;
}

/*
사이클 생기는 예제
4 1
4 1 2 3 1
*/