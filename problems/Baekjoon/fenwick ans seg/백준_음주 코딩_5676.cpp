/*
 *  BOJ 5676. 음주 코딩
 *
 *  시간복잡도 : O(KlogN)
 *
 *  구간 곱의 부호만 구하면 된다. 만약 모든 수의 곱을 구하면 long long으로 해도
 *  overflow를 피할 수 없다. 단말 노드에 입력받은 수의 부호를 집어 넣으면 된다.
 *  나머지는 구간 합 구하기 문제와 동치이다. 해당 문제를 참고하자!
 *
 */

#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
using namespace std;
#define MXN 100002

int N, K;
int tree[MXN * 4];
int pli;

void init() {
	pli = 1;
	while (pli < N) pli *= 2;
	pli--;

	for (int i = 1; i <= pli + 1; i++) tree[pli + i] = 1;
	int in;
	for (int i = 1; i <= N; i++) {
		cin >> in;
		if (in == 0) tree[pli + i] = 0;
		else if (in < 0) tree[pli + i] = -1;
		else tree[pli + i] = 1;
	}

	for (int i = pli; i >= 1; i--) {
		tree[i] = tree[i * 2] * tree[i * 2 + 1];
	}
}

void update(int idx, int b) {
	idx += pli;
	if (b == 0) tree[idx] = 0;
	else if (b < 0) tree[idx] = -1;
	else tree[idx] = 1;
	idx /= 2;
	while (idx) {
		tree[idx] = tree[idx * 2] * tree[idx * 2 + 1];
		idx /= 2;
	}
}

int get_ans(int s, int e) {
	s += pli;
	e += pli;
	int ret = 1;
	while (s <= e) {
		if (s % 2) ret*=tree[s];
		if (e % 2 == 0) ret*=tree[e];
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return ret;
}

int main() {
	fastio();
	int TC = 2;
	while (cin >> N >> K) {
		init();
		char q;
		int a, b;
		while (K--) {
			cin >> q >> a >> b;
			if (q == 'C') {// 변경
				update(a, b);
			}
			else {// 출력
				int ret = get_ans(a, b);
				char ans;
				if (ret == 0) ans = '0';
				else if (ret < 0) ans = '-';
				else ans = '+';
				cout << ans;
			}
		}
		cout << '\n';
	}
	return 0;
}