#include <iostream>
using namespace std;
#define MXN 1000001
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)

typedef long long ll;

int N, M, K;
// 100만보다 큰 2의 제곱수 : 1048576 -> 최대 약 210만개의 배열이 필요, 대략 데이터의 4배정도면 충분
ll tree[MXN * 4];
int Nidx;// leaf_node가 아닌 노드의 제일 마지막 인덱스를 구한다.

void init() {
	for (int i = 0; i < N * 4; i++) tree[i] = 0LL;
	Nidx = 1; 
	while (Nidx < N) Nidx *= 2;
	Nidx--;
}

void update(int ni, ll delta) {// node_index
	while (ni) {
		tree[ni] += delta;
		ni /= 2;
	}
}

ll sum(int s, int e) {
	ll ret = 0;
	while (s <= e) {
		// if (tree[s] % 2 == 1) ret += tree[s];
		// if (tree[e] % 2 == 0) ret += tree[e];
		// 위에 주석 친 것 처럼 실수를 한다. 주의하자!
		if (s % 2 == 1) ret += tree[s];
		if (e % 2 == 0) ret += tree[e];
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return ret;
}

int main(){
	fastio();
	cin >> N >> M >> K;
	init();// 트리 초기화

	// 인덱스 트리의 리프 노드에 데이터 입력
	for (int i = 1; i <= N; i++) cin >> tree[Nidx + i];

	// 리프 노드가 아닌 노드의 값 생성
	for (int i = Nidx; i >= 1; i--) tree[i] = tree[i * 2] + tree[i * 2 + 1];
	
	ll a, b, c;
	for (int i = 0; i < M + K; i++) {
		cin >> a >> b >> c;
		if (a == 1) {
			ll delta = c - tree[Nidx + b];
			update(Nidx + b, delta);
		}
		else cout << sum(Nidx + b, Nidx + c) << '\n';
	}
}