/*
 *  BOJ 15683. 감시
 *
 *  시간복잡도 : O(16^N)
 *
 *  각 cctv타입에 대한 회전했을때의 모든 방향의 값을 dir에 담는다.
 *  이 값을 이용해 cctv 벡터에 담긴 순서대로 재귀적으로 cctv를 회전시키고
 *  감시할 수 있는 영역을 체크해 나가면 된다. 이렇게 해서 모든 cctv가
 *  사용되었으면 사각지대의 개수를 체크해 더 작은 개수를 ans에 담아
 *  출력한다.
 *
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#define MXN 9

class Cctv {
public:
	int y, x, t;
	Cctv() {}
	Cctv(int _y, int _x, int _t) : y(_y), x(_x), t(_t) {}
};

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int dir[5][4][4] = {
	{{0,1,0,0},{0,0,1,0},{0,0,0,1},{1,0,0,0}},
	{{0,1,0,1},{1,0,1,0},{0,1,0,1},{1,0,1,0}},
	{{1,1,0,0},{0,1,1,0},{0,0,1,1},{1,0,0,1}},
	{{1,1,0,1},{1,1,1,0},{0,1,1,1},{1,0,1,1}},
	{{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}
};

int N, M;
int area[MXN + 1][MXN + 1];
vector<Cctv> cctv;
int ans;
const int INF = 2e9;

int min(int a, int b) {
	return a > b ? b : a;
}

int calc() {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!area[i][j]) ret++;
		}
	}
	return ret;
}

void print() {
	cout << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << area[i][j] << ' ';
		}
		cout << '\n';
	}
}

void dfs(int c) {
	if (c == cctv.size()) {
		//print();
		ans = min(calc(), ans);
		return;
	}

	int cy = cctv[c].y;
	int cx = cctv[c].x;
	int ct = cctv[c].t;
	int tmp[MXN + 1][MXN + 1];
	memcpy(tmp, area, sizeof(tmp));
	// 회전 for문
	for (int k = 0; k < 4; k++) {
		// 방향 for문
		for (int i = 0; i < 4; i++) {
			if (!dir[ct][k][i]) continue;
			int y = cy;
			int x = cx;
			while (1) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= N || nx < 0 || nx >= M || area[ny][nx] == 6) break;
				area[ny][nx] = 7;
				// cy = ny, cx = nx로 하여 방향을 회전하고도 기준이 바뀐 cy, cx를 사용하여 틀렸다.
				y = ny;
				x = nx;
			}
		}
		dfs(c + 1);
		memcpy(area, tmp, sizeof(tmp));
	}

}

int main() {
	fastio();
	cin >> N >> M;
	ans = INF;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> area[i][j];
			if (1 <= area[i][j] && area[i][j] <= 5) {
				// 배열은 0부터 시작하면서 cctv값은 1부터 시작하므로 area[i][j] - 1
				// 해주어야 하는데 area[i][j] 만 해서 틀렸다.
				cctv.push_back(Cctv(i, j, area[i][j] - 1));
			}
		}
	}

	dfs(0);
	cout << ans << '\n';
	return 0;
}