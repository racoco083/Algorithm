#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MXN 10

int N, M;
vector<int> adj[MXN + 1];
int indegree[MXN + 1];
queue<int> qu;

int main() {
	cin >> N >> M;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		indegree[b]++;
		adj[a].push_back(b);
	}
	
	for (int i = 1; i <= N; i++) {
		if (!indegree[i]) qu.push(i);
	}

	while (!qu.empty()) {
		int cur = qu.front();
		qu.pop();
		cout << cur << ' ';
		for (int i = 0; i < adj[cur].size(); i++) {
			int next = adj[cur][i];
			indegree[next]--;
			if (!indegree[next]) qu.push(next);
		}
	}
	
	return 0;
}

/*
5 5
1 2
2 3
3 4
1 4
4 5
*/