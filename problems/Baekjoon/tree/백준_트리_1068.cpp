// pa[i] : i번째 노드의 부모 노드를 담는다.
// pa[i]를 부모로, 자식을 i로 하여 adj를 통해 방향성 있게 연결합니다.
// 만약 i가 지워야할 노드이면 pa[i]와 i노드를 연결시키는 걸 생략합니다.
// pa[i]가 -1이라는 것은 i가 루트노드이니 이 노드를 시작점으로 하여
// 모든 노드를 탐색해 단말 노드의 개수를 구하였습니다. 

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
using namespace std;
#define MAX 51

int N;
int pa[MAX];
vector<int> adj[MAX];

// v정점의 루트로 시작하여 리프노드의 개수를 구한다.
int dfs(int v) {
	if (adj[v].size() == 0) return 1;

	int ret = 0;
	for (int i = 0; i < adj[v].size(); i++) {
		int n = adj[v][i];
		ret += dfs(n);
	}
	return ret;
}

int main() {
	fastio();
	cin >> N;
	int p, s, d;
	for (int i = 0; i < N; i++) {
		cin >> pa[i];
	}
	cin >> d;
	for (int i = 0; i < N; i++) {
		if (pa[i] == -1) {
			s = i;
			continue;
		}
		if (i == d) continue;
		adj[pa[i]].push_back(i);
	}
	// 루트노드를 지운다면 답이 1이 아닌 0이 되야한다.
	if (d == s) cout << 0 << '\n';
	else cout << dfs(s) << '\n';
	return 0;
}

/*
트리 문제 풀 때 생각할 것
1. 루트노드 지울 때
2. 경사트리에서 답이 되는지
3. 완전이진트리에서 답이 되는지
*/

//////////////////////////틀린 코드//////////////////////////////
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
using namespace std;
#define MAX 51

int N;
vector<int> adj[MAX];

int dfs(int v) {
	if (adj[v].size() == 0) return 1;

	int ret = 0;
	for (int i = 0; i < adj[v].size(); i++) {
		int n = adj[v][i];
		ret += dfs(n);
	}
	return ret;
}

int main() {
	fastio();
	cin >> N;
	int p, s, d;
	for (int i = 0; i < N; i++) {
		cin >> p;
		if (p == -1) {
			s = i;
			continue;
		}
		adj[p].push_back(i);
	}
	cin >> d;
	int ans = dfs(s) - dfs(d);
	cout << ans << '\n';
	return 0;
}

/*
경사트리 예제의 경우
4
-1 0 1 2
2
일 경우 삭제하는 곳을 기점으로 한 단말노드 개수는1이고
루트노드 기점으로 한 단말노드 개수도 1이다.
답이 1이 나와야 하는데 0이 나온다.
*/