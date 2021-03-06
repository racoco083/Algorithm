// 현재 노드를 루트로 하는 모든 경로의 합을 ans값에 더해주고, 현재 노드를
// 시작점으로 하는 모든 경로의 합을 s에 더해 나가는 것을 재귀적으로
// 구해주면 된다.

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
using namespace std;
#define MXN 100001
#define MOD 1000000007
typedef long long ll;

class Nw { //next_weight
public:
	int n, w; //next, weight
	Nw(int _n, int _w) : n(_n), w(_w) {}
	Nw() {}
};

vector<Nw> adj[MXN];
int visited[MXN];
int N;
ll ans = 0LL;

ll dfs(ll v) {// vertex
	vector<ll> dist;
	visited[v] = true;
	// dist의 각 원소는 현재 노드와 해당 자식노드를 거쳐 만들어진 모든 경로의 가중치 합이다.
	for (auto it : adj[v]) {
		if (visited[it.n]) continue;
		dist.push_back((dfs(it.n) * it.w) % MOD);
	}

	// s를 return할 때는 이 1은 현재 노드와 부모 사이의 경로의 가중치를 뜻한다.
	// 밑의 각 it값은 dist의 원소로 현재 노드를 루트로 하여 해당 it값을 리턴한 노드로 가는
	// 모든 경로 곱의 합이다. 손자 노드끼리의 경로 계산은 되지 않는다.
	// 하지만 제일 나이가 어린 노드 부터 계산을 하므로 이 노드가 루트가 되어 경로들이 ans에 더해진다.
	// ans에 s*it을 더해나간다. s는 it값을 차례로 더해나간다. 이렇게 하면 현재 노드를 시작점으로 한
	// 모든 경로의 가중치의 합을 구할 수 있다.
	// s는 현재 노드를 시작점으로 한 모든 경로의 가중치의 합이다. 여기에 1은 현재노드와 부모 사이의 경로의 가중치를 나타낸다.
	// 이 s를 구해 리턴해 주는 것을 재귀적으로 처리하면 된다.
	// ans 에는 재귀적으로 현재노드를 기점으로 가능한 모든 경로를 구해 더해나간다.
	// 루트 노드에서 구한 ans의 값이 모든 정점 사이의 경로의 가중치의 합이 된다.


	// 현재 노드로 시작하는 모든 경로의 가중치 합을 s에 더해준다.
	// 현재 노드를 루트로 하는 모든 경로의 가중치 합을 ans에 더해준다.
	ll s = 1LL;// sum
	for (auto it : dist) {
		ans = (ans + (s * it)) % MOD;
		s = (s + it) % MOD;
	}
	return s;
}

int main() {
	fastio();
	cin >> N;
	int a, b, w;
	for (int i = 1; i < N; i++) {
		cin >> a >> b >> w;
		adj[a].push_back(Nw(b, w));
		adj[b].push_back(Nw(a, w));
	}

	dfs(1);
	cout << ans << '\n';
	return 0;
}