/*
 *  BOJ 1600. 말이 되고픈 원숭이
 *
 *  시간복잡도 : O(HWK)
 *
 *  이 문제는 우선 장애물이 있다는 것에 주의하자!
 *  시작점에서 bfs를 하며 인접하게 가거나 말처럼 가거나 한다.
 *  그렇게 하여 끝점에 도착하면 그때의 dist값을 출력해 주면 된다.
 *  dist[201][201][31]이 있는데 [31]은 0~30으로 말처럼 띈 횟수를 뜻한다.
 *  장애물만 없었으면 [31]이 필요가 없다.
 *
 *  [31]이 필요한 예제를 보자.
 *     1 2 3 4 <= 인덱스
 *  1  0 0 1 1
 *  2  1 0 1 1
 *  3  1 0 1 1
 *  4  1 1 1 1
 *  5  1 1 0 0
 *  K가 1이라고 했을 때
 *  시작점에서 끝점으로 가려면 인접하게 (y,x)로 정의! (3, 2)까지 간 다음
 *  말 처럼 이동해 (5, 3)에 가서 인접하게 이동해(5, 4)에 가는 것이 최소 
 *  이동 횟수가 된다. 하지만 시작점에서 말처럼 이동해 (3, 2)에 도달하면
 *  K는 1이라 더 이상 말 처럼 이동 할 수 없게된다. 그러면 끝점에
 *  갈 방법이 없다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <queue>
using namespace std;

class Pos {
public:
	int y, x, k;
	Pos(int _y, int _x, int _k) : y(_y), x(_x), k(_k) {}
};

int K, W, H;
int d;
int area[201][201];
int dist[201][201][31];
int dx[12] = { 2, 2, -2, -2, 1, 1, -1, -1, -1, 0, 1, 0 };
int dy[12] = { 1, -1, 1, -1, 2, -2, 2, -2, 0, 1, 0, -1 };

void bfs(int y, int x) {
	queue<Pos> qu;
	qu.push(Pos(y, x, 0));
	dist[y][x][0] = 1;
	while (!qu.empty()) {
		int curY = qu.front().y;
		int curX = qu.front().x;
		int curK = qu.front().k;
		qu.pop();

		for (int i = 0; i < 12; i++) {
			int ny = curY + dy[i];
			int nx = curX + dx[i];
			if (ny < 0 || ny >= H || nx < 0 || nx >= W || area[ny][nx]) continue;
			if (i < 8) { //말
				if ((curK >= K) || dist[ny][nx][curK + 1]) continue;
				dist[ny][nx][curK + 1] = dist[curY][curX][curK] + 1;
				qu.push(Pos(ny, nx, curK + 1));
				d = curK + 1;
			}
			else { //인접
				if (dist[ny][nx][curK]) continue;
				dist[ny][nx][curK] = dist[curY][curX][curK] + 1;
				qu.push(Pos(ny, nx, curK));
				d = curK;
			}
			if ((ny == H - 1) && (nx == W - 1)) return;
		}
	}
}

int main() {
	fastio();
	cin >> K >> W >> H;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> area[i][j];
		}
	}
	bfs(0, 0);

	if (dist[H - 1][W - 1][d] == 0) cout << -1 << '\n';
	else cout << dist[H - 1][W - 1][d] - 1 << '\n';
	return 0;
}
