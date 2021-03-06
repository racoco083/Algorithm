/*
 *  BOJ 15684. 사다리 조작
 *
 *  시간복잡도 : O((N+H)C(3))
 *
 *  문제 설명대로 사다리를 놓을 수 있는 곳이면 놓고 dfs를 하면서
 *  모든 사라리의 시작점에서 출발하면 같은 열의 도착점에 도착하는지를
 *  체크해 주면된다. 그냥 짜면 시간초과가 나고 dfs에서 y값을 넘겨서
 *  자식은 행을 탐색할 때 1이 아닌 y부터 탐색하면 된다.
 *  그리고 사다리를 i개 놓을 때 끝날 수 있으므로 사다리를 놓을 수 있는
 *  최대값을 i개만 놓고 dfs를 실행하여 통과하면 i+1,i+2에 대하여
 *  dfs를 수행하지 않아도 되어 시간을 아낄 수 있다.
 *
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#pragma warning(disable:4996)
#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

bool ladder[32][12];
int N, M, H;
bool ans;

bool check() {
	for (int i = 1; i <= N; i++) {
		int s = i;
		for (int j = 1; j <= H; j++) {
			if (ladder[j][s]) s++;
			else if (ladder[j][s - 1]) s--;
		}
		if (s != i) return false;
	}
	return true;
}

void dfs(int y, int x, int pc, int d) { // put_cpunt
	if (ans) return;

	if (d == pc) {
		ans = check();
		return;
	}

	for (int i = y; i <= H; i++) {
		// 다음 행에서는 1부터 시작해야하기 때문에 j=x를 하면 틀린다.
		for (int j = 1; j < N; j++) {
			if (ladder[i][j] || ladder[i][j - 1] || ladder[i][j + 1]) continue;
			ladder[i][j] = true;
			dfs(i, j, pc, d + 1);
			ladder[i][j] = false;
		}
	}
}

int main() {
	fastio();
	cin >> N >> M >> H;
	int a, b;
	ans = false;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		ladder[a][b] = true;
	}

	for (int i = 0; i <= 3; i++) {
		dfs(1, 1, i, 0);
		if (ans) {
			cout << i << '\n';
			return 0;
		}
	}
	cout << -1 << '\n';
	return 0;
}