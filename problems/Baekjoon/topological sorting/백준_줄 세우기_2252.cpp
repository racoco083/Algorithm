/*
 *  BOJ 2252. 줄 세우기
 *
 *  시간복잡도 : O(M)
 *
 *  입력으로 받은 간선을 이용해 indegree를 구한 다음
 *  indegree가 0인 값들을 시작점으로 하여 간선을 지나면 indegree를 지우면서
 *  indgree가 0일 때 다음 노드로 갈 수 있도록 하여 dfs를 돌려
 *  cur값을 출력한다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#define MXN 32002

vector<int> adj[MXN+1];
vector<int> start;
int indegree[MXN + 1];
int N, M;

void dfs(int cur) {
	cout << cur << ' ';
	for (int i = 0; i < adj[cur].size(); i++) {
		int next = adj[cur][i];
		indegree[next]--;
		if (indegree[next] == 0) dfs(next);
	}
}

int main() {
	fastio();
	cin >> N >> M;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		indegree[b]++;
	}
	for (int i = 1; i <= N; i++) {
		if (indegree[i]) continue;
		start.push_back(i);
	}

	for (int i = 0; i < start.size(); i++) dfs(start[i]);
	
	return 0;
}