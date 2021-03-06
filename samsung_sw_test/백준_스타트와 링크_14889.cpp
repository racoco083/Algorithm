/*
 *  BOJ 14889. 스타트와 링크
 *
 *  시간복잡도 : O((N)C(N/2) * N^2)
 *
 *  N명은 짝수이며 팀은 두팀으로 동일한 팀수를 갖는다.
 *  00001111을 next_permutation하며 이 때의 0값만
 *  a벡터에 1값만 b벡터에 담아서 a팀과 b팀의 능력치를 구하고
 *  이것의 차이를 최소화한 값을 ans에 담아 출력하면 된다.
 *
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define MXN 21

int N;
int area[MXN + 1][MXN + 1];
int perm[MXN + 1];

// 현재 팀의 능력치를 구한다.
int calc(vector<int> a) {
	int ret = 0;
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			if (i == j) continue;
			ret += area[a[i]][a[j]];
		}
	}
	return ret;
}

int abs(int a) {
	return a < 0 ? -a : a;
}

int min(int a, int b) {
	return a > b ? b : a;
}

int main() {
	fastio();
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> area[i][j];
		}
	}

	for (int i = N/2; i < N; i++) perm[i] = 1;

	int ans = 2e9;

	do {
		vector<int> a;
		vector<int> b;

		for (int i = 0; i < N; i++) {
			if (perm[i]) a.push_back(i);
			else b.push_back(i);
		}

		ans = min(abs(calc(a) - calc(b)), ans);
	} while (next_permutation(perm, perm + N));
	cout << ans << '\n';
	return 0;
}