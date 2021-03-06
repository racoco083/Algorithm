/*
 *  BOJ 16234. 인구 이동
 *
 *  시간복잡도 : O(T * N^2), (T : 턴의 횟수)
 *
 *  y,x,n 으로 시작해 bfs를 돌리면서 인접하며 차이가 L과 R사이인
 *  모든 곳을 방문해 방문한 모든 곳의 visited값을 n으로 바꾸어 준다.
 *  이 n은 연합국가의 넘버링한 숫자를 의미하며 1씩 증가한다.
 *  union_num[n]에 연합국가의 총 인구 수 / 칸의 수를 저장한다.
 *  N*N 안에 있는 가능한 모든 연합 국가를 구하고 다시 N*N번
 *  돌면서 visited[i][j]의 저장해 둔 n값을 이용해 union_num에 접근해
 *  연합국가의 평균 인구 수를 area에 저장한다.
 *  연합국가가 생기지 않을 때 까지 위의 과정을 반복하면 된다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#pragma warning(disable:4996)
#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
#define MXN 52
typedef pair<int, int> pi;

int N, L, R;
int area[MXN + 1][MXN + 1];
// bool visited를 해서 2를 넣든 3을 넣든 1로 처리되게 하는 실수를 하였다.
int visited[MXN + 1][MXN + 1];
int union_num[MXN*MXN + 1];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

bool bfs(int y, int x, int num) {
	queue<pi> qu;
	qu.push({ y,x });
	visited[y][x] = num;
	bool isChange = false;
	int popu_cnt = area[y][x];
	int area_cnt = 1;
	while (!qu.empty()) {
		int cy = qu.front().first;
		int cx = qu.front().second;
		qu.pop();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (ny < 0 || ny >= N || nx < 0 || nx >= N || visited[ny][nx]) continue;
			int comv = abs(area[cy][cx] - area[ny][nx]);
			if (comv < L || R < comv) continue;

			isChange = true;
			visited[ny][nx] = num;
			qu.push({ ny, nx });
			area_cnt++;
			popu_cnt += area[ny][nx];
		}
	}
	union_num[num] = popu_cnt / area_cnt;
	return isChange;
}

int main() {
	fastio();
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> area[i][j];
		}
	}

	int ans = 0;// 인구 이동횟수
	while (1) {
		memset(visited, 0, sizeof(visited));
		int number = 0;
		bool isChange = false;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visited[i][j]) continue;
				bool ret = bfs(i, j, ++number);
				if (!isChange) isChange = ret;
			}
		}

		if (!isChange) break;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				area[i][j] = union_num[visited[i][j]];
			}
		}
		ans++;
	}
	cout << ans << '\n';
	return 0;
}