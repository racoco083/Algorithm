/*
*  BOJ 11266. 단절점
*
*  단절점을 찾는 문제로 현 노드의 방문 순서vn[c]와 자식 노드를 거쳐 자식 노드가
*  현 노드 보다 먼저 방문된 정점과 직, 간접적으로 연결되어 있다면 현 노드가
*  끊겨도 그래프는 1개 그대로이고 분할되지 않는다. 먼저 방문된 정점과
*  직, 간접적으로 연결되어 있지 않다면 현 노드가 끊기면 그래프가 둘로 나뉜다
*  현 정점이 단절점이라는 것을 뜻한다.
*
*/

#include <iostream>
#include <vector>
#include <string.h>
#include <set>
using namespace std;
#define MXN 10002

int N, M;
vector<int> adj[MXN];
int vn[MXN];// visited_number
int vi;// visited_index
set<int> ans;

int min(int a, int b) {
	return a > b ? b : a;
}

int dfs(int c, bool r, int p) {
	int ret = vn[c] = ++vi;
	int child = 0;// 이 변수는 root 노드만을 위해서 사용된다.
	for (int i = 0; i < adj[c].size(); i++) {
		int next = adj[c][i];
		// 현 노드는 부모노드를 다시 방문할 수 있으므로 의미없는 이런 경우는 부모노드 다시 방문못하게 해서 무시한다.
		if (next == p) continue;
		if (vn[next] == -1) {
			// root의 자식이 여럿이더라도 루트가 단절점이 될 수 없는 경우가 있다.
			// 다른 노드에서 자식노드를 방문하여서 실제로 루트가 방문한 노드는 1이면
			// 루트는 단절점이 될 수 없다. 예를 들어 1->2, 1->3이면 1은 단절점이다.
			// 하지만 1->2->3, 1->3이라고 한다면 1에서 2를 방문하고 2에서 3을 방문해서
			// vn[3]값이 -1이 아니다. root가 없어진다 하더라도 2와 3이 연결이 되어 있어
			// 그래프가 2개로 나누어지지 않는다. 고로 루트는 단절점이 아니다.
			child++;
			// tmp는 next자식 노드를 통해 얻은 가장 빠른 방문순서 값을 가진다.
			int tmp = dfs(next, false, c);
			ret = min(ret, tmp);
			// 경사트리일 때 루트의 정점을 단절점으로 포함시키면 안된다.
			// 만약 밑에 "!r &&" 이 부분을 뺀다면 경사트리 인데도 루트가
			// 단절점에 포함이 되어 버린다. 루트는 따로 처리해 주어야 한다.
			// vn[c] == tmp가 같은 경우가 있는데 현재정점이 사이클의 시작과 끝인 경우이다.
			// tmp가 더 작다는 것은 자식노드를 통해 경로를 따라가면 현 정점보다 먼저
			// 방문된 정점과 연결된다는 뜻으로 그 때는 현재 정점이 없어져도 자식노드는
			// 현 정점보다 더 먼저 방문된 노드로 간접 또는 직접적으로 연결되어 있어
			// 현 정점은 단절점이 될 수 없다.
			// vn[c] < tmp로 하면 
			// 1-2-3, 2-4, 3-4와 같이 연결되어 있고 1이 루트일 때 2가 단절점이 되어야 하는데
			// 단절점이 될 수 없게 된다.
			// 현재 정점의 방문순서 vn[c]는 tmp가 자신보다 값이 작으면 무시하고 같거나 작으면
			// 자신이 단절점이라는 것을 알수 있게 비교해주는 배열이다.
			if (!r && vn[c] <= tmp) ans.insert(c);
		}
		// vn[next]가 이미 방문되었다면 next정점은 조상, 형제, 자손일 수 있다.
		// vn[cur]값은 cur정점이 방문된 순서를 담는데 이것도 ret처럼 갱신시켜 주면 안 된다.
		// 이렇게 하는 예를 들어 1-2-3, 1-3이렇게 연결되어 있고 1이 루트라고 한다면, 단절점은 없어야 한다.
		// 하지만 1에서 2를 가고 2에서 1을 다시 방문하게 되면 vn[2]=1이 된다. 2에서 3을 가고 vn[3]도 1이 된다.
		// 정점2에서 3으로 부터 받은 리턴 값 tmp가 1이고 2의 vn[2]도 1이라 2가 단절점이 되어버리는 오류가 생긴다.
		else ret = min(ret, vn[next]);
	}
	if (r && child >= 2) ans.insert(c);
	// 현재 노드의 방문순서와 현재 노드에서 자식 노드들을 방문하여 얻은 가장 빨리 방문된 순서를
	// ret에 담아 리턴한다.
	return ret;
}

int main() {
	cin >> N >> M;
	int a, b;
	memset(vn, -1, sizeof(vn));
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int i = 1; i <= N; i++) {
		if (vn[i] != -1) continue;
		dfs(i, true, 0);
	}
	cout << ans.size() << '\n';
	for (set<int>::iterator it = ans.begin(); it != ans.end(); it++) {
		cout << *it << ' ';
	}
}