/*
 *  BOJ 3108. 로고
 *
 *  시간복잡도 : O(N^2)
 *
 *  PU 명령은 연필을 올리는 명령이다. 최대한 연필을 종이에서 안 떨어뜨리고
 *  모든 사각형을 그리면 되는 문제이다. 좌표를 *2씩 하지 않으면
 *  (1,1) (2,2)직사각형과 (1,3) (2,4)직사각형은 영역을 표시하면 붙어 있어
 *  이걸 구분짓기 위해 *2를 하였다.
 *  모든 지사각형 영역을 체크한 다음 전체 좌표의 범위에 대해
 *  flood fill을 하여 영역의 개수를 구한다.
 *  이때 주의해야 할 것이 있는데 거북이는 좌표의 중간에서 위로가니
 *  연필은 내려져 있는 상태다. 거북이가 시작하는 공간에 직사각형 영역이
 *  있으면 이 영역은 개수에 안 세기 위해 bfs를 돌려 visited를 1로 다 돌리고
 *  시작한다. 거북이가 시작하는 공간에 직사각형 영역이 체크되어 있지 않으면
 *  무시하고 넘어간다.
 *  
 *  밑의 사이트에서 예제에 대한 그림을 누가 그려 놓았다. 이해하는데 도움이 된다.
 *  https://icanyoucanwecan.tistory.com/80
 *
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <queue>
using namespace std;
#define MXN 1000
int N;

typedef pair<int, int> pi;
int area[MXN * 2 + 1][MXN * 2 + 1];// 채워진 공간 체크
bool visited[MXN * 2 + 1][MXN * 2 + 1];// 채워진 공간이 방문되었는지 체크
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int min(int a, int b) {
	return a > b ? b : a;
}

int max(int a, int b) {
	return a > b ? a : b;
}

// visited 초기화 신경 쓰기
void bfs(int y, int x) {
	queue<pi> qu;
	qu.push({ y,x });
	visited[y][x] = true;
	while (!qu.empty()) {
		int cy = qu.front().first;
		int cx = qu.front().second;
		qu.pop();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (ny < 0 || ny > MXN*2 || nx < 0 || nx > MXN*2 || !area[ny][nx] || visited[ny][nx]) continue;
			visited[ny][nx] = true;
			qu.push({ ny,nx });
		}
	}
}

int main() {
	fastio();
	cin >> N;
	int a, b, c, d;
	for (int i = 0; i < N; i++) {
		cin >> a >> b >> c >> d;
		
		a += 500, a *= 2;
		b += 500, b *= 2;
		c += 500, c *= 2;
		d += 500, d *= 2;
	
		int x1 = min(a, c), x2 = max(a, c);
		int y1 = min(b, d), y2 = max(b, d);
		for (int i = x1; i <= x2; i++) {
			area[y1][i] = 1;
			area[y2][i] = 1;
		}
		for (int i = y1; i <= y2; i++) {
			area[i][x1] = 1;
			area[i][x2] = 1;
		}
	}
	// 거북이는 1000, 1000에서 시작하며 거북이가 있는 영역이 1 로 체크되어있으면
	// bfs 돌려 해당 영역 visited 1로 만들어 다시 방문 되지 못하도록 한다.
	if (area[1000][1000]) {
		bfs(1000, 1000);
	}
	//이중 포문 후에 bfs횟수구하면 끝
	int ans = 0;
	for (int i = 0; i <= MXN * 2; i++) {
		for (int j = 0; j <= MXN * 2; j++) {
			if (area[i][j] && !visited[i][j]) {
				bfs(i, j);
				ans++;
			}
		}
	}

	cout << ans << '\n';
	return 0;
}