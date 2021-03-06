/*
 *  BOJ 16987. 계란으로 계란치기
 *
 *  시간복잡도 : O(N!)
 *
 *  문제 난독증으로 고생했다. 문제 이해력을 기르자!
 *  손에 든 계란으로 전체 계란 중에서 부실 수 있는 것을 부시면 되는데
 *  처음에 무조건 오른쪽 계란만 보았다. 그런 말도 없는데..
 *  그리고 깰 수 있을 때는 무조건 깨면 된다. 맨 왼쪽 계란부터
 *  들어 올리면서 해당 계란이 깰 수 있는 계란을 깨고 다음 계란으로 간다.
 *  만약 깰 수 있는 계란이 없거나 자기가 깨져 있으면 그냥 다음 계란으로 간다.
 *  어떻게 해서든 cur==N이 되어야 깨진 계란의 개수를 세기 때문이다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <string.h>
using namespace std;
#define MXN 10
typedef pair<int, int> pi;

pi egg[MXN + 1];
int N;
int ans;

int max(int a, int b) {
	return a > b ? a : b;
}

void dfs(int cur) {
	// 모든 계란을 다 봤으면 현재 egg배열의 상태를 확인해
	// 깨진 계란의 개수를 세아린다.
	if (cur == N) {
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			if (egg[i].first <= 0) cnt++;
		}
		ans = max(ans, cnt);
		return;
	}

	// 만약 현재 들고 있는 계란이 깨져 있는 계란이라면 
	// 다음 계란을 살피고 현재는 처리하지 않아도 되니 return해 준다.
	if (egg[cur].first <= 0) {
		dfs(cur + 1);
		return;
	}

	pi tmp[MXN + 1];
	memcpy(tmp, egg, sizeof(egg));

	// 현재 계란으로 다른 계란을 깬 경우 true 아니면 false
	bool crack = false;
	// 현재 계란으로 바닥에 놓인 계란을 살피며 깰 수 있으면 깨고dfs한다.
	for (int i = 0; i < N; i++) {
		if (i == cur) continue;
		if (egg[i].first <= 0) continue;
		crack = true;
		egg[i].first -= egg[cur].second;
		egg[cur].first -= egg[i].second;
		dfs(cur + 1);
		memcpy(egg, tmp, sizeof(egg));
	}
	// if (!crack)이 부분을 빼면 틀린다. 문제에서는 칠 수 있는 경우에는
	// 무조건 치고 넘어가야 한다. 하지만 중간에 있는 계란을 들어 올려
	// 깰 수 있는 계란을 찾았는데 없으면 어떻게든 다음 계란을 봐주어야 하는데
	// 깨지 않았으면 다음 계란을 봐주는 것이다.
	if (!crack) dfs(cur + 1);
}

int main() {
	fastio();
	cin >> N;
	int h, w;
	for (int i = 0; i < N; i++) {
		cin >> egg[i].first >> egg[i].second;
	}

	dfs(0);
	cout << ans << '\n';
	return 0;
}