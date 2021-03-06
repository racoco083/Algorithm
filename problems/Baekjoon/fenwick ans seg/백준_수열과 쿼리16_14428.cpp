/* 
 *  수열과 쿼리15번 문제와 다 똑같다 find_miv 빼고 나머지는 수열과 쿼리15 참고!
 *  find_miv에 대한 설명은 해당 코드에 설명을 하겠습니다.
 *
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;
#define MXN 100002
typedef pair<int, int> pi;

pi tree[MXN * 4];
int N, M;
int pli;
const int INF = 2e9;

bool cmp(pi a, pi b) {
	if (a.first == b.first) return a.second < b.second;
	return a.first < b.first;
}

void init() {
	cin >> N;
	pli = 1;
	while (pli < N) pli *= 2;
	pli--;
	int a;
	for (int i = 1; i <= pli + 1; i++) {
		tree[pli + i] = { INF, 0 };
	}
	for (int i = 1; i <= N; i++) {
		cin >> a;
		tree[pli + i] = { a,i };
	}
	for (int i = pli; i >= 1; i--) {
		tree[i] = cmp(tree[i * 2], tree[i * 2 + 1]) ? tree[i * 2] : tree[i * 2 + 1];
	}
}

void update(int idx) {
	while (idx) {
		tree[idx] = cmp(tree[idx * 2], tree[idx * 2 + 1]) ? tree[idx * 2] : tree[idx * 2 + 1];
		idx /= 2;
	}
}

// s가 짝수라는 것은 s, s+1의 부모가 같다는 것을 뜻한다. 그러면 나중에 부모를 보면 되므로 
// 현재 s의 값을 볼 필요가 없다. 홀수 일때만 값을 봐주면 된다. 위의 레벨로 올라갈 때는 
// s는 봐야하는지 아닌지 체크했으므로 s+1의 부모를 보면 된다. e도 마찬가지로 짝수일 때만
// 봐주면서 e-1의 부모를 보면서 범위를 좁혀나간다. 예를 들어 5 4 3 2 1에서 [2,5]구간의 최소값을
// 구하면, pli = 7, s=2+pli, e=5+pli가 되고 s는 홀수라서 miv와 비교한다. e도 짝수라서 miv와 비교한다.
// 이제 봐줄 것은 [3,4] 구간만 봐주면 된다. s = (s+1)/2 = 5, e = (e-1)/2 = 5
// [3,4]구간의 가장 작은 값을 담은 노드 tree[5]의 값까지 보면 [2,5]구간의 가장 작은 값을 찾을 수 있다. 
int find_miv(int s, int e) {
	s += pli;
	e += pli;
	pi miv = { INF, 0 };
	while (s <= e) {
		if (s % 2 == 1) {
			if (miv.first > tree[s].first) miv = tree[s];
			else if (miv.first == tree[s].first && miv.second > tree[s].second) miv = tree[s];
		}
		if (e % 2 == 0) {
			if (miv.first > tree[e].first) miv = tree[e];
			else if (miv.first == tree[e].first && miv.second > tree[e].second) miv = tree[e];
		}
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return miv.first;
}

int main() {
	fastio();
	init();
	cin >> M;
	int q, a, b;
	for (int i = 0; i < M; i++) {
		cin >> q >> a >> b;
		if (q == 1) {
			tree[pli + a].first = b;
			update((pli + a) / 2);
		}
		else cout << find_miv(a, b) << '\n';
	}
	return 0;
}