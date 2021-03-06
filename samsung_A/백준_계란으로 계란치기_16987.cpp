/*
 *  BOJ 16987. 계란으로 계란치기
 *
 *  시간복잡도 : O(N^N)
 *
 *  문제 설명대로 구현해 주면된다. 한 가지 어려웠던 점은
 *  계란이 3개가 있고 0,1번째 계란이 깨져있을 때 안 깨진 2번째 계란을 들었을 때
 *  dfs를 통해 c == N이 되도록 해야하는데 그래야 계란의 개수를 세아리니까
 *  위와 같은 경우에는 부모로 돌아가 계란 수를 세지 않았다. 그래서 c==N인 경우는
 *  종료하도록 하고, c>=N-1인 경우에 계란의 개수를 세서 최대 개수를 저장하였다.
 *
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;
#define MXN 10
typedef pair<int, int> pi;

pi egg[MXN + 1];
int N;
int ans;

int max(int a, int b) {
	return a > b ? a : b;
}

int calcEggCnt() {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		if (egg[i].first <= 0) {
			ret++;
		}
	}
	return ret;
}

void cutHardness(int a, int b, int ope) {
	egg[a].first += ope * egg[b].second;
	egg[b].first += ope * egg[a].second;
}

void dfs(int c) {
	// 현재 인덱스가 N-1일 때도 최대값을 계산해 주어야 한다.
	// 만약 현재가 가장 오른쪽 계란이고 깰 수 있는 계란이 없을 때는
	// dfs(c+1)로 가지 않는다.
	if (c >= N - 1) {
		ans = max(ans, calcEggCnt());
	}

	// 가장 오른쪽 계란이라 종료. N-1인지 N인지 모르겠네
	if (c == N) return;

	// 계란이 깨져있으면 다음 계란으로 넘어간다.
	if (egg[c].first <= 0) {
		dfs(c + 1);
		return;
	}

	for (int i = 0; i < N; i++) {
		if (i == c || egg[i].first <= 0) continue;
		cutHardness(i, c, -1);
		dfs(c + 1);
		cutHardness(i, c, 1);
	}
}

int main() {
	fastio();
	cin >> N;
	ans = 0;
	for (int i = 0; i < N; i++) {
		cin >> egg[i].first >> egg[i].second;
	}

	dfs(0);

	cout << ans;
	return 0;
}