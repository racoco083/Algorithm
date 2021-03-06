/*
 *  BOJ 16985. Maze
 *
 *  시간복잡도 : O(?)
 *
 *  각 판을 area에 담는다. area에 담긴판을 백트레킹하여 
 *  k번째 판을 gta의 d번째 판으로 만든다. 이 때 이 판을 회전하는 모든경우를 처리한다.
 *  회전하면서 gta[0][0][0]이 지나갈 수 있는 칸이면 bfs를 돌려 gta[N-1][N-1][N-1]칸에
 *  방문할 수 있는 지 체크하고 방문할 수 있을 때 이때의 거리 값을 리턴하여 이 거리 값이
 *  가장 최소화 된 값을 출력한다.
 *
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
#define MXN 5

class Pos {
public:
	int z, y, x;
	Pos() {}
	Pos(int _z, int _y, int _x) : z(_z), y(_y), x(_x) {}
};

int area[MXN + 1][MXN + 1][MXN + 1];
int gta[MXN + 1][MXN + 1][MXN + 1];
int dist[MXN + 1][MXN + 1][MXN + 1];
int N;
int ans;
const int INF = 2e9;
int full;
int tmp[MXN + 1][MXN + 1];
int dz[6] = { 0,0,0,0,1,-1 };
int dy[6] = { -1, 0, 1, 0, 0, 0 };
int dx[6] = { 0, 1, 0, -1, 0, 0 };

int min(int a, int b) {
	return a > b ? b : a;
}

int bfs(int z, int y, int x) {
	queue<Pos> qu;
	qu.push(Pos(z, y, x));
	dist[z][y][x] = 1;

	while (!qu.empty()) {
		int cz = qu.front().z;
		int cy = qu.front().y;
		int cx = qu.front().x;
		qu.pop();

		for (int i = 0; i < 6; i++) {
			int nz = cz + dz[i];
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			// gta사용해야 하는데 area사용했다.
			if (nz < 0 || nz >= N || ny < 0 || ny >= N || nx < 0 || nx >= N 
				|| dist[nz][ny][nx] || !gta[nz][ny][nx]) continue;
			
			dist[nz][ny][nx] = dist[cz][cy][cx] + 1;
			qu.push(Pos(nz, ny, nx));
			if (nz == N - 1 && ny == N - 1 && nx == N - 1) {
				return dist[cz][cy][cx];
			}
		}
	}
	return INF;
}

void dfs(int m, int d) {// mask, depth
	if (m == full) {
		if (gta[0][0][0]) {
			memset(dist, 0, sizeof(dist));
			ans = min(ans, bfs(0, 0, 0));
		}
		return;
	}

	for (int k = 0; k < 5; k++) {
		if (m & (1 << k)) continue;
		for (int i = 0; i < 4; i++) {
			if (i != 0) {
				// 반시계 회전시킨다.
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						tmp[i][j] = area[k][j][N - i - 1];
					}
				}
				// 밑의 이중 포문을 추가시키지 않아 area도 돌려줘야 다음에는
				// 180도가 돌고 다음에는 270도가 될 수 있다. 항상 90도만 돌리기
				// 때문에 area도 돌려줘야 한다.
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						area[k][i][j] = tmp[i][j];
					}
				}

			}

			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					gta[d][i][j] = area[k][i][j];
				}
			}			

			dfs(m | (1 << k), d + 1);
		}
	}
}

int main() {
	fastio();
	N = 5;
	ans = INF;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				cin >> area[i][j][k];
			}
		}
	}

	full = (1 << 5) - 1;
	dfs(0, 0);
	if (ans == INF) cout << -1;
	else cout << ans;
	return 0;
}