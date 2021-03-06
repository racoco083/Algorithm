/*
 *  BOJ 14503. 로봇 청소기
 *
 *  시간복잡도 : O(N*M)
 *
 *  처음에 dfs로 생각했다. 하지만 후진하는 경우에 자식 함수의 방향을 유지하면서
 *  부모로 돌아간다는 것이 어려웠다. 그래서 dfs를 포기하고 while(1)를 돌렸다.
 *  현재 위치가 청소가 되어있지 않으면 청소를 한다. 현재위치에서 상하좌우
 *  4방향을 보면서 후진을 해야하는 경우인지 체크한다. 후진을 해야 하는데
 *  뒤가 벽이면 종료하고 아니면 방향값 d를 수정하지 않고 후진하면 된다.
 *  area[ny][nx]가 청소할 수 있는 공간이면 y,x를 ny, nx로 바꾸어주고
 *  아니면 방향만 왼쪽으로 바꾸어 주면 되다.
 *  처음에 문제 설명대로 2-1,2-2를 먼저 처리하고 2-3, 2-4를 처리하려고 하니
 *  구현이 안 되었다. 2-3, 2-4를 먼저 처리하면 간단하게 구현가능하다.
 *
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;
#define MXN 50

int N, M;
int area[MXN + 1][MXN + 1];
int cleaned[MXN + 1][MXN + 1];
int ry, rx, rd;
int ans;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int gc;

bool back_check(int y, int x) {
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= N || nx < 0 || nx >= M || cleaned[ny][nx] || area[ny][nx]) continue;
		return false;
	}
	return true;
}

int solve(int y, int x, int d) {
	int ret = 0;
	while (1) {
		if (!cleaned[y][x]) {
			ret++;
			cleaned[y][x] = ++gc;
		}

		// 후진해야하는 경우인지 체크한다.
		if (back_check(y, x)) {
			y = y + dy[(d + 2) % 4];
			x = x + dx[(d + 2) % 4];
			// 후진하는데 뒤가 벽이면 break;
			if (area[y][x]) break;
			continue;
		}

		// 여기서 부터는 4방향 중에 청소할 공간이 있다는 뜻이다.
		d = (d + 3) % 4;
		int ny = y + dy[d];
		int nx = x + dx[d];
		if (ny < 0 || ny >= N || nx < 0 || nx >= M || cleaned[ny][nx] || area[ny][nx]) {
			continue;
		}
		// ny, nx가 청소할 수 있는 공간이다.
		y = ny;
		x = nx;
	}
	return ret;
}

void print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << cleaned[i][j] << "  ";
		}
		cout << '\n';
	}
}

int main() {
	fastio();
	cin >> N >> M;
	cin >> ry >> rx >> rd;
	ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> area[i][j];
		}
	}

	cout << solve(ry, rx, rd) << '\n';
	//print();
	return 0;
}