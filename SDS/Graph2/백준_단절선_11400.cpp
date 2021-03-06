/*
 *  BOJ 11400. 단절선
 *
 *  단절선이 될 수 있는 조건은 현 정점의 자식 정점이 
 *  직, 간접적으로 현 정점보다 먼저 방문된 정점에 연결되어 있지 
 *  않다면 단절선이 될 수 있다.
 *
 */

#include <iostream>
#include <vector>
#include <string.h>
#include <set>
using namespace std;
#define MXN 100002

typedef pair<int, int> pi;

int N, M;
vector<int> adj[MXN];
int vn[MXN];
set<pi> ans;
int vi;

int min(int a, int b) {
	return a > b ? b : a;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int dfs(int c, int p) {
	int ret = vn[c] = ++vi;
	for (int i = 0; i < adj[c].size(); i++) {
		int next = adj[c][i];
		// 단절선이 될 수 있는 조건은 현 정점의 자식 정점이 직, 간접적으로 현 정점보다
		// 먼저 방문된 정점에 연결되어 있지 않다면 단절선이 될 수 있다. 
		// 자식노드는 부모노드와도 연결이 되어 있어 부모노드의 vn값을 ret에 갱신시켜버리면
		// 단절선인데도 단절선을 담을 수 없다. 예를 들어 1-2는 단절선이다.
		// 1의 vn[1] == 1이고 2를 방문하여 2의 vn[2] == 2이다. 2는 다시 1을 방문하여
		// ret = 1값을 리턴하게 된다. 1은 그 값을 받아서 자신의 vn[1]과 비교해
		// 그 값이 더 크다면 1과 2는 단절선이 될 수 있지만 같은 값이므로 단절선이 되지
		// 않도록 만든다. 단절선인데도 단절선이 아니게 되므로 부모 정점도 매개변수로
		// 같이 던저주어 2의 다음 값이 부모정점이면 무시하도록 처리하여 답을 구했다.
		if (next == p) continue;
		if (vn[next] == -1) {
			int tmp = dfs(next, c);
			ret = min(tmp, ret);
			if (vn[c] < tmp) ans.insert({ min(c, next), max(c, next) });
		}
		else ret = min(ret, vn[next]);
	}
	return ret;
}

int main() {
	cin >> N >> M;
	memset(vn, -1, sizeof(vn));
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int i = 1; i <= N; i++) {
		if (vn[i] != -1) continue;
		dfs(i, 0);
	}
	cout << ans.size() << '\n';
	for (set<pi> ::iterator it = ans.begin(); it != ans.end(); it++) {
		cout << (*it).first << ' ' << (*it).second << '\n';
	}
	return 0;
}





